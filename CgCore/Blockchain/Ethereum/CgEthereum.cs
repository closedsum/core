// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
namespace CgCore
{
    using System;
    using System.Collections;
    using System.Collections.Generic;
    using System.Diagnostics;
    using System.IO;
    using UnityEngine;

    public struct CgEthereumNewAccountInfo
    {
        public string Nickname;
        public string Passphrase;

        public CgEthereumNewAccountInfo(string nickname, string passphrase)
        {
            Nickname = nickname;
            Passphrase = passphrase;
        }
    }

    // TODO: Move to SgEthereum
    public enum ECgEthereumOnBoardState : byte
    {
        // RunningInstance
        Init,
        Start,
        // Console
        Attach,
            // Accounts
        AccountCreatedWorld,
        UnlockAccountWorld,
        AccountCreatedGame,
        UnlockAccountGame,
        AccountCreatedPlayer,
        UnlockAccountPlayer,
        Complete,
        MAX
    }

    public static class ECgEthereumCommand
    {
        public static readonly ECgBlockchainCommand InitBlockchain = EMCgBlockchainCommand.Get().Create("InitBlockchain");
        public static readonly ECgBlockchainCommand SetDataDirectory = EMCgBlockchainCommand.Get().Create("SetDataDirectory");
        public static readonly ECgBlockchainCommand AttachToConsole = EMCgBlockchainCommand.Get().Create("AttachToConsole");
        public static readonly ECgBlockchainCommand ExitConsole = EMCgBlockchainCommand.Get().Create("ExitConsole");
        public static readonly ECgBlockchainCommand NewAccount = EMCgBlockchainCommand.Get().Create("NewAccount");
        public static readonly ECgBlockchainCommand UnlockAccount = EMCgBlockchainCommand.Get().Create("UnlockAccount");
        public static readonly ECgBlockchainCommand ListAccounts = EMCgBlockchainCommand.Get().Create("ListAccounts");
        public static readonly ECgBlockchainCommand SetEtherbase = EMCgBlockchainCommand.Get().Create("SetEtherbase");
        public static readonly ECgBlockchainCommand GetBalanceEther = EMCgBlockchainCommand.Get().Create("GetBalanceEther");
        public static readonly ECgBlockchainCommand GetBalanceWei = EMCgBlockchainCommand.Get().Create("GetBalanceWei");
        public static readonly ECgBlockchainCommand StartMiner = EMCgBlockchainCommand.Get().Create("StartMiner");
        public static readonly ECgBlockchainCommand StopMiner = EMCgBlockchainCommand.Get().Create("StopMiner");

        public static readonly ECgBlockchainCommand MAX = EMCgBlockchainCommand.Get().Create("MAX");
    }

    public class CgEthereum : CgBlockchain
    {
        // Account
        public static CgConsoleVariableLog LogAccountLoad = new CgConsoleVariableLog("log.blockchain.account.load", false, "Log Blockchain (Ethereum) when Accounts get loaded", (int)ECgConsoleVariableFlag.Console);

        public static CgConsoleVariableLog LogAccountSetup = new CgConsoleVariableLog("log.blockchain.account.setup", false, "Log Blockchain (Ethereum) Account Setup", (int)ECgConsoleVariableFlag.Console);

        #region "Data Members"

        public string ConsoleFullPath;
        public string GenesisFilePath;
        public string KeystoreDirectory;

        protected Dictionary<string, CgEthereumKeystore> Keystores;

        public CgRoutine.BoolType IsRunningInstanceCloseFlag;

        protected Dictionary<ECgBlockchainCommand, CgProcessMonitorOutputEvent> MonitorOutputEvents;

        protected CgBlockchainCommandInfo CurrentCommandInfo;
        protected object CurrentCommandOuput;

        // TODO: Move into SgEthereum

        ECgEthereumOnBoardState OnBoardState;
        TCgFlagType<ECgEthereumOnBoardState> OnBoardStateFlag;

        private CgRoutine.BoolType CommandFlag;
        private CgRoutine.BoolType SetupAccountFlag;

        #endregion // Data Members

        public CgEthereum() : base()
        {
            Genesis = new CgEthereumGenesis();

            StorageType = ECgBlockchainType.PrivateSingleNode;

            ConsoleFilename = "geth.exe";
            string path = Application.dataPath;
            path = path.Substring(0, path.Length - 6);

            ConsoleDirectory = path + "Blockchain\\Ethereum\\Geth";
            ConsoleFullPath = ConsoleDirectory + "\\" + ConsoleFilename;
            RootDirectory = path + "Blockchain\\Ethereum";
            GenesisFilePath = RootDirectory + "/genesis.json"; ;

            IsRunningInstanceCloseFlag = new CgRoutine.BoolType();
            IsRunningInstanceCloseFlag.Set(true);

            ChainDirectory = path + "Blockchain\\Ethereum\\chaindata";
            AccountsDirectory = RootDirectory + "\\Accounts";
            KeystoreDirectory = ChainDirectory + "\\keystore";

            Keystores = new Dictionary<string, CgEthereumKeystore>();

            MonitorOutputEvents = new Dictionary<ECgBlockchainCommand, CgProcessMonitorOutputEvent>(new ECgBlockchainCommandEqualityComparer());

            CurrentCommandInfo = new CgBlockchainCommandInfo(ECgEthereumCommand.MAX, null, null);

            // Commands

                // InitBlockchain
            SetCommand(ECgEthereumCommand.InitBlockchain, "--datadir=\"" + ChainDirectory + "\" init \"" + RootDirectory + "\\genesis.json\"");
                // SetDataDirectory
            SetCommand(ECgEthereumCommand.SetDataDirectory, "--datadir=\"" + ChainDirectory + "\" --networkid 15");
            {
                CgStringParagraph p = CgStringParagraphHelper.CreateOneWordParagraph("IPC endpoint opened", ECgStringWordRule.MatchCase);// TODO: also include "url=\\\\.\\pipe\\geth.ipc"?

                CgProcessMonitorOutputEvent e = new CgProcessMonitorOutputEvent(ECgEthereumCommand.SetDataDirectory, p, ECgProcessMonitorOutputEventPurpose.FireOnce);
                e.AddEvent(OnCommandCompleted);

                MonitorOutputEvents.Add(ECgEthereumCommand.SetDataDirectory, e);
            }
                // AttachToConsole
            SetCommand(ECgEthereumCommand.AttachToConsole, "attach ipc:\\\\.\\pipe\\geth.ipc");
            {
                CgStringParagraph p = new CgStringParagraph();
                    p.AddSentence(CgStringParagraphHelper.CreateOneWordSentence("welcome", ECgStringWordRule.Lower));
                    p.AddSentence(CgStringParagraphHelper.CreateOneWordSentence("instance:", ECgStringWordRule.Lower));
                    p.AddSentence(CgStringParagraphHelper.CreateOneWordSentence("modules:", ECgStringWordRule.Lower));

                CgProcessMonitorOutputEvent e = new CgProcessMonitorOutputEvent(ECgEthereumCommand.AttachToConsole, p, ECgProcessMonitorOutputEventPurpose.FireOnce);
                e.AddEvent(OnCommandCompleted);

                MonitorOutputEvents.Add(ECgEthereumCommand.AttachToConsole, e);
            }
                // ExitConsole
            SetCommand(ECgEthereumCommand.ExitConsole, "exit");
                // NewAccount
            SetCommand(ECgEthereumCommand.NewAccount, "personal.newAccount(%s)");
                // UnlockAccount
            SetCommand(ECgEthereumCommand.UnlockAccount, "personal.unlockAccount(%s,%s,%s)");
            {
                CgStringParagraph p = CgStringParagraphHelper.CreateOneWordParagraph("true", ECgStringWordRule.MatchCase);

                CgProcessMonitorOutputEvent e = new CgProcessMonitorOutputEvent(ECgEthereumCommand.UnlockAccount, p, ECgProcessMonitorOutputEventPurpose.FireOnce);
                e.AddEvent(OnCommandCompleted);

                MonitorOutputEvents.Add(ECgEthereumCommand.UnlockAccount, e);
            }
                // ListAccounts
            SetCommand(ECgEthereumCommand.ListAccounts, "personal.listAccounts");
                // SetEtherbase
            SetCommand(ECgEthereumCommand.SetEtherbase, "miner.setEtherbase(%s);");
            {
                CgStringParagraph p = CgStringParagraphHelper.CreateOneWordParagraph("true", ECgStringWordRule.MatchCase);

                CgProcessMonitorOutputEvent e = new CgProcessMonitorOutputEvent(ECgEthereumCommand.SetEtherbase, p, ECgProcessMonitorOutputEventPurpose.FireOnce);
                e.AddEvent(OnCommandCompleted);

                MonitorOutputEvents.Add(ECgEthereumCommand.SetEtherbase, e);
            }
                // GetBalanceEther
            SetCommand(ECgEthereumCommand.GetBalanceEther, "web3.fromWei(eth.getBalance(%s))");
                // StartMiner
            SetCommand(ECgEthereumCommand.StartMiner, "miner.start();");
            {
                CgStringParagraph p = CgStringParagraphHelper.CreateOneWordParagraph("null", ECgStringWordRule.MatchCase);

                CgProcessMonitorOutputEvent e = new CgProcessMonitorOutputEvent(ECgEthereumCommand.StartMiner, p, ECgProcessMonitorOutputEventPurpose.FireOnce);
                e.AddEvent(OnCommandCompleted);

                MonitorOutputEvents.Add(ECgEthereumCommand.StartMiner, e);
            }
                // StopMiner
            SetCommand(ECgEthereumCommand.StopMiner, "miner.stop();");
            {
                CgStringParagraph p = CgStringParagraphHelper.CreateOneWordParagraph("true", ECgStringWordRule.MatchCase);

                CgProcessMonitorOutputEvent e = new CgProcessMonitorOutputEvent(ECgEthereumCommand.StopMiner, p, ECgProcessMonitorOutputEventPurpose.FireOnce);
                e.AddEvent(OnCommandCompleted);

                MonitorOutputEvents.Add(ECgEthereumCommand.StopMiner, e);
            }

            OnBoardState = ECgEthereumOnBoardState.Init;
            OnBoardStateFlag = new TCgFlagType<ECgEthereumOnBoardState>(ECgEthereumOnBoardState.Init, ECgEthereumOnBoardState.MAX);

            CommandFlag = new CgRoutine.BoolType();
            CommandFlag.Set(false);
            SetupAccountFlag = new CgRoutine.BoolType();
            SetupAccountFlag.Set(false);

            CommandCompleted_Event.Add(OnCommandCompleted);
            AccountCreated_Event.Add(OnAccountCreated);

            // Enums

            EMCgProcess.Get().Create("Blockchain");
            ICgManager_Process.Get().CreatePool(EMCgProcess.Get()["Blockchain"], 4);
        }

        public void Log(string msg)
        {
            UnityEngine.Debug.Log(msg);
        }

        public override void Shutdown()
        {
            for (byte i = 0; i < (byte)ECgBlockchainProcessType.MAX; ++i)
            {
                ECgBlockchainProcessType processType = (ECgBlockchainProcessType)i;
                CgProcess p                          = Processes[processType];
                
                if (p != null)
                    p.DeAllocate();
            }
        }

        public override void Rebuild()
        {
            // Delete files in existing directories

            // Accounts
            if (Directory.Exists(AccountsDirectory))
            {
                string[] paths = Directory.GetFiles(AccountsDirectory);

                foreach (string path in paths)
                {
                    File.Delete(path);
                }
                Directory.Delete(AccountsDirectory, true);
            }
            // chaindata
            if (Directory.Exists(ChainDirectory))
            {
                string[] paths = Directory.GetFiles(ChainDirectory);

                foreach (string path in paths)
                {
                    File.Delete(path);
                }
                Directory.Delete(ChainDirectory, true);
            }
            // genesis.json
            if (File.Exists(GenesisFilePath))
                File.Delete(GenesisFilePath);
        }

        public override void SetCommand(ECgBlockchainCommand command, string str)
        {
            string value;
            Commands.TryGetValue(command, out value);

            if (value == "")
            {
                Commands.Add(command, str);
            }
            else
            {
                Commands[command] = str;
            }
        }

        public override void RunCommand(ECgBlockchainProcessType processType, string command)
        {
            CgProcess p = GetProcess(processType);

            // RunningInstance
            if (processType == ECgBlockchainProcessType.RunningInstance)
            {
                if (p == null)
                {
                    CgDebug.Log("CgEthereum.RunCommand: Failed to run command: " + command + ". Process " + processType.ToString() + " has NOT started. Call StartPrivateChain().");
                    return;
                }
            }
            // Console
            if (processType == ECgBlockchainProcessType.Console)
            {
                if (p == null)
                {
                    CgDebug.Log("CgEthereum.RunCommand: Failed to run command: " + command + ". Process " + processType.ToString() + " has NOT started. Call OpenShell().");
                    return;
                }
            }

            if (LogIO.Log())
            {
                if (processType == ECgBlockchainProcessType.RunningInstance)
                    CgDebug.Log("Process (Input): " + command);
                if (processType == ECgBlockchainProcessType.Console)
                    CgDebug.Log("Console (Input): " + command);
            }

            p.RunCommand(command);
        }

        public override void RunCommand(ECgBlockchainProcessType processType, ECgBlockchainCommand command, CgBlockchainCommandArgument[] args = null)
        {
            string value;
            Commands.TryGetValue(command, out value);

            if (value == INVALID_COMMAND)
            {
                CgDebug.LogWarning("CgEthereum.RunCommand: No command set for " + command.Name);
                return;
            }

            // Rebuild command if arguments where passed in
            if (args != null && args.Length > EMPTY)
            {
                // Create list of all string parts
                string[] parts = value.Split(new string[] { "%s" }, StringSplitOptions.None);
                
                // Add in arguments
                if ((parts.Length - 1) == args.Length)
                {
                    value = "";

                    int argumentLength = args.Length;

                    for (int i = 0; i < argumentLength; ++i)
                    {
                        value += parts[i] + args[i].ToStr();
                    }
                    value += parts[argumentLength];
                }
                else
                {
                    UnityEngine.Debug.Log("CgEthereum.RunCommand: Failed to run command: " + command.Name + ". Wildcard count != Argument count (" + (parts.Length-1) + "," + args.Length + ")");
                }
            }

            if (LogIO.Log())
            {
                CgDebug.Log("CgEthereum.RunCommand: Running command: " + command);
            }
            RunCommand(processType, value);
        }

        public void AddMonitorOutputEvenToProcess(ECgBlockchainProcessType processType, CgProcessMonitorOutputEvent e)
        {
            Processes[processType].AddMonitorOuputEvent(e);
        }

        public void AddMonitorOutputEvenToProcess(ECgBlockchainProcessType processType, ECgBlockchainCommand command)
        {
            AddMonitorOutputEvenToProcess(processType, MonitorOutputEvents[command]);
        }

        public void OnCommandCompleted(ECgBlockchainCommand command)
        {
            if (LogCommandCompleted.Log())
            {
                CgDebug.Log("CgEthereum.OnCommandCompleted: Completed command: " + command);
            }

            // SetDataDirectory
            if (command == ECgEthereumCommand.SetDataDirectory)
            {
                OnBoardState = ECgEthereumOnBoardState.Start;
                OnBoardStateFlag.SetEnd(OnBoardState);
            }
            // AttachToConsole
            if (command == ECgEthereumCommand.AttachToConsole)
            {
                OnBoardState = ECgEthereumOnBoardState.Attach;
                OnBoardStateFlag.SetEnd(OnBoardState);
            }
            // UnlockAccount
            if (command == ECgEthereumCommand.UnlockAccount)
            {
                // Get Nickname
                string nickname = (string)CurrentCommandInfo.Payload;

                // World
                if (nickname == "World")
                    OnBoardState = ECgEthereumOnBoardState.UnlockAccountWorld;
                // Game
                else
                if (nickname == "Game")
                    OnBoardState = ECgEthereumOnBoardState.UnlockAccountGame;
                // Player
                else
                if (nickname == "Player")
                    OnBoardState = ECgEthereumOnBoardState.UnlockAccountPlayer;

                OnBoardStateFlag.SetEnd(OnBoardState);
            }
            // SetEtherbase
            if (command == ECgEthereumCommand.SetEtherbase)
            {
                // Get Nickname
                string nickname = (string)CurrentCommandInfo.Payload;
            }
            // GetBalanceEther
            if (command == ECgEthereumCommand.GetBalanceEther)
            {
            }
            CommandFlag.Set(true);
        }

        public void OnCommandCompleted(string name)
        {
            CommandCompleted_Event.Broadcast(EMCgBlockchainCommand.Get()[name]);
        }

        public void OnProcessOutputRecieved(object sender, DataReceivedEventArgs e)
        {
            if (LogIO.Log())
            {
                CgDebug.Log("Process (Output): " + e.Data);
            }
        }

        public void OnProcessErrorRecieved(object sender, DataReceivedEventArgs e)
        {
            if (LogIO.Log())
            {
                CgDebug.Log("Process (Error): " + e.Data);
            }
        }

        public void OnProcessExited(object sender, EventArgs e)
        {
            if (LogIO.Log())
            {
                CgDebug.Log("Blockchain (Process): Exited");
            }

            CgProcess p = Processes[ECgBlockchainProcessType.RunningInstance];

            Processes[ECgBlockchainProcessType.RunningInstance] = null;
            IsRunningInstanceOpen = false;
            IsRunningInstanceCloseFlag.Set(true);
            p.DeAllocate();
        }

        public void OnConsoleOutputRecieved(object sender, DataReceivedEventArgs e)
        {
            string output = e.Data;

            if (LogIO.Log())
            {
                CgDebug.Log("Console (Output): " + output);
            }

            ECgBlockchainCommand command = CurrentCommandInfo.Command;

            // NewAccount
            if (command == ECgEthereumCommand.NewAccount)
            {
                // Check for account address
                if (output.StartsWith("\"0x"))
                {
                    CgEthereumNewAccountInfo info = (CgEthereumNewAccountInfo)CurrentCommandInfo.Payload;

                    string nickname   = info.Nickname;
                    string address    = output.Replace("\"", "");
                    address           = address.Replace("0x", "");
                    string passphrase = info.Passphrase;

                    CgEthereumAccount a = new CgEthereumAccount(nickname, address, passphrase);

                    string json            = a.ToStr();
                    string accountFilePath = AccountsDirectory + "\\" + nickname + "-" + address;

                    File.WriteAllText(accountFilePath, json, System.Text.Encoding.ASCII);

                    if (LogAccountCreated.Log())
                    {
                        CgDebug.Log("Creating Account: " + nickname);
                        CgDebug.Log("-- Address: " + address);
                        CgDebug.Log("-- PassPhrase: " + passphrase);
                        CgDebug.Log("-- writing to: " + accountFilePath);
                    }

                    Accounts.Add(nickname, a);

                    CreateKeystore(a);

                    AccountCreated_Event.Broadcast(a);
                    CommandCompleted_Event.Broadcast(command);
                }
            }
            // GetBalanceEther
            if (command == ECgEthereumCommand.GetBalanceEther)
            {
                int balance;

                if (Int32.TryParse(output, out balance))
                {
                    CurrentCommandOuput = balance;

                    CommandCompleted_Event.Broadcast(command);
                }
            }
        }

        public void OnConsoleErrorRecieved(object sender, DataReceivedEventArgs e)
        {
            if (LogIO.Log())
            {
                UnityEngine.Debug.Log("Console (Error): " + e.Data);
            }
        }

        public void OnConsoleExited(object sender, EventArgs e)
        {
            if (LogIO.Log())
            {
                UnityEngine.Debug.Log("Blockchain (Console): Exited");
            }

            Processes[ECgBlockchainProcessType.Console].DeAllocate();
            Processes[ECgBlockchainProcessType.Console] = null;
            IsConsoleOpen = false;
        }

        public override void SetProcess(ECgBlockchainProcessType processType, CgProcess p)
        {
            Processes[processType] = p;
        }

        public override CgProcess GetProcess(ECgBlockchainProcessType processType)
        {
            return Processes[processType];
        }

        public override void StartProcess(ECgBlockchainProcessType processType, CgBlockchainProcessStartInfo startInfo)
        {
            CgProcess p = GetProcess(processType);

            if (p == null)
            {
                CgProcessPayload payload = ICgManager_Process.Get().AllocatePayload();

                payload.CreateNoWindow = !ShowProcessWindow.Get();
                payload.UseShellExecute = false;
                payload.FileName = startInfo.FileName;
                payload.Arguments = startInfo.Arguments;

                payload.ErrorDialog = false;
                payload.RedirectStandardInput = startInfo.RedirectStandardInput;
                payload.RedirectStandardOutput = true;
                payload.RedirectStandardError = true;
                payload.EnableRaisingEvents = true;

                if (processType == ECgBlockchainProcessType.RunningInstance)
                {
                    payload.ErrorDataRecieved_Event.Add(OnProcessErrorRecieved);
                    payload.OutputDataRecieved_Event.Add(OnProcessOutputRecieved);
                    payload.Exited_Event.Add(OnProcessExited);
                }
                else
                if (processType == ECgBlockchainProcessType.Console)
                {
                    payload.ErrorDataRecieved_Event.Add(OnConsoleErrorRecieved);
                    payload.OutputDataRecieved_Event.Add(OnConsoleOutputRecieved);
                    payload.Exited_Event.Add(OnConsoleExited);
                }

                foreach (CgProcessMonitorOutputEvent e in startInfo.MonitorOutputEvents)
                {
                    payload.AddMonitorOutputEvent(e);
                }

                p = ICgManager_Process.Get().Spawn(EMCgProcess.Get()["Blockchain"], payload);

                SetProcess(processType, p);
            }
            else
            {
                CgDebug.Log("CgEthereum.StartProcess: StartProcess called for running Process: " + processType.ToString() + " before the process exited.");
            }
        }

        public override void StopProcess(ECgBlockchainProcessType processType)
        {
            if (Processes[processType] == null)
                return;
            Processes[processType].DeAllocate();
            Processes[processType] = null;
        }

        public override void OpenRunningInstance()
        {
            if (IsRunningInstanceOpen)
                return;

            ECgBlockchainCommand command = ECgEthereumCommand.SetDataDirectory;

            CgBlockchainProcessStartInfo startInfo = new CgBlockchainProcessStartInfo();
            startInfo.FileName              = ConsoleFullPath;
            startInfo.Arguments             = Commands[command];
            startInfo.RedirectStandardInput = false;
            startInfo.AddMonitorOutputEvent(MonitorOutputEvents[command]);

            ECgBlockchainProcessType processType = ECgBlockchainProcessType.RunningInstance;

            //EnqueueCommand(processType, command);
            StartProcess(processType, startInfo);
            
            IsRunningInstanceOpen = true;
            IsRunningInstanceCloseFlag.Set(false);
        }

        public override void CreatePrivateChain()
        {
            // Create chaindata Directory
            if (!Directory.Exists(ChainDirectory))
                Directory.CreateDirectory(ChainDirectory);

            // Create genesis.json
            string json = Genesis.ToStr();

            File.WriteAllText(GenesisFilePath, json, System.Text.Encoding.ASCII);

            // Create Accounts Directory
            if (!Directory.Exists(AccountsDirectory))
                Directory.CreateDirectory(AccountsDirectory);

            // Init
            IsRunningInstanceOpen = true;
            IsRunningInstanceCloseFlag.Set(false);

            CgBlockchainProcessStartInfo startInfo = new CgBlockchainProcessStartInfo();
            startInfo.FileName = ConsoleFullPath;
            startInfo.Arguments = Commands[ECgEthereumCommand.InitBlockchain];
            startInfo.RedirectStandardInput = false;

            StartProcess(ECgBlockchainProcessType.RunningInstance, startInfo);

            OnBoardState = ECgEthereumOnBoardState.Init;

            if (LogOnBoard.Log())
            {
                Log("CgEthereum.CreatePrivateChain: State Change: -> ECgEthereumOnBoardState.Init.");
            }
        }

        public override void StartPrivateChain()
        {
            CgCoroutineScheduler.Get().Start(ECgCoroutineSchedule.Update, StartPrivateChain_Internal(this));
        }

        public static IEnumerator StartPrivateChain_Internal(CgEthereum eth)
        {
            // Start if the Blockchain has already been initialized
            bool genesisExists = File.Exists(eth.GenesisFilePath);

            if (genesisExists)
            {
                eth.OnBoardStateFlag.SetEnd(ECgEthereumOnBoardState.MAX);
                eth.OnBoardStateFlag.SetStart(ECgEthereumOnBoardState.Start);

                eth.OpenRunningInstance();

                eth.OnBoardState = ECgEthereumOnBoardState.Start;

                if (LogOnBoard.Log())
                {
                    CgDebug.Log("CgEthereum.CreatePrivateChain: State Change: ECgEthereumOnBoardState.Init -> ECgEthereumOnBoardState.Start.");
                }
            }
            // Initialize then Start
            else
            {
                eth.CreatePrivateChain();

                yield return eth.IsRunningInstanceCloseFlag;

                if (LogOnBoard.Log())
                {
                    CgDebug.Log("CgEthereum.CreatePrivateChain: State Change: ECgEthereumOnBoardState.Init -> ECgEthereumOnBoardState.Start.");
                }

                eth.OnBoardStateFlag.SetEnd(ECgEthereumOnBoardState.MAX);
                eth.OnBoardStateFlag.SetStart(ECgEthereumOnBoardState.Start);
               
                eth.OpenRunningInstance();
            }
            // Parse the Genesis file
            eth.Genesis.ParseFromFilePath(eth.GenesisFilePath);

            // Waittill OnBoardState == ECgEthereumOnBoardState.Start
            yield return eth.OnBoardStateFlag;

            // Attach / Open Console
            {
                if (LogOnBoard.Log())
                {
                    CgDebug.Log("CgEthereum.CreatePrivateChain: State Change: ECgEthereumOnBoardState.Start -> ECgEthereumOnBoardState.Attach.");
                }

                eth.OnBoardStateFlag.SetEnd(ECgEthereumOnBoardState.MAX);
                eth.OnBoardStateFlag.SetStart(ECgEthereumOnBoardState.Attach);

                eth.OpenConsole();

                // Waittill OnBoardState == ECgEthereumOnBoardState.Attach
                yield return eth.OnBoardStateFlag;
            }

            eth.LoadAccounts();

            eth.SetupAccount("World");
            // Load Accounts
            /*
            {
                eth.LoadAccounts();

                // Check World Account exists
                {
                    ICgBlockchainAccount iaccount = null;

                    eth.Accounts.TryGetValue("World", out iaccount);

                    if (iaccount == null)
                    {
                        eth.OnBoardStateFlag.SetEnd(ECgEthereumOnBoardState.MAX);
                        eth.OnBoardStateFlag.SetStart(ECgEthereumOnBoardState.AccountCreatedWorld);

                        CgEthereumNewAccountInfo info = new CgEthereumNewAccountInfo("World", "World");

                        eth.NewAccount(info);

                        // Waittill OnBoardState == ECgEthereumOnBoardState.AccountCreatedWorld
                        yield return eth.OnBoardStateFlag;
                    }
                    else
                    {
                        eth.OnBoardState = ECgEthereumOnBoardState.AccountCreatedWorld;
                    }

                    if (LogOnBoard.Log())
                    {
                        CgDebug.Log("CgEthereum.CreatePrivateChain: State Change: ECgEthereumOnBoardState.Attach -> ECgEthereumOnBoardState.AccountCreatedWorld.");
                    }
                }
                // Unlock World Account
                {
                    eth.OnBoardStateFlag.SetEnd(ECgEthereumOnBoardState.MAX);
                    eth.OnBoardStateFlag.SetStart(ECgEthereumOnBoardState.UnlockAccountWorld);

                    eth.UnlockAccount("World");

                    // Waittill OnBoardState == ECgEthereumOnBoardState.UnlockAccountWorld
                    yield return eth.OnBoardStateFlag;

                    if (LogOnBoard.Log())
                    {
                        CgDebug.Log("CgEthereum.CreatePrivateChain: State Change: ECgEthereumOnBoardState.AccountCreatedWorld -> ECgEthereumOnBoardState.UnlockAccountWorld.");
                    }
                }
                // Check Game Account exists
                {
                    ICgBlockchainAccount iaccount = null;

                    eth.Accounts.TryGetValue("Game", out iaccount);

                    if (iaccount == null)
                    {
                        eth.OnBoardStateFlag.SetEnd(ECgEthereumOnBoardState.MAX);
                        eth.OnBoardStateFlag.SetStart(ECgEthereumOnBoardState.AccountCreatedGame);

                        CgEthereumNewAccountInfo info = new CgEthereumNewAccountInfo("Game", "Game");

                        eth.NewAccount(info);

                        // Waittill OnBoardState == ECgEthereumOnBoardState.AccountCreatedGame
                        yield return eth.OnBoardStateFlag;
                    }
                    else
                    {
                        eth.OnBoardState = ECgEthereumOnBoardState.AccountCreatedGame;
                    }

                    if (LogOnBoard.Log())
                    {
                        CgDebug.Log("CgEthereum.CreatePrivateChain: State Change: ECgEthereumOnBoardState.AccountCreatedWorld -> ECgEthereumOnBoardState.AccountCreatedGame.");
                    }
                }
                // Unlock Game Account
                {
                    eth.OnBoardStateFlag.SetEnd(ECgEthereumOnBoardState.MAX);
                    eth.OnBoardStateFlag.SetStart(ECgEthereumOnBoardState.UnlockAccountGame);

                    eth.UnlockAccount("Game");

                    // Waittill OnBoardState == ECgEthereumOnBoardState.UnlockAccountGame
                    yield return eth.OnBoardStateFlag;

                    if (LogOnBoard.Log())
                    {
                        CgDebug.Log("CgEthereum.CreatePrivateChain: State Change: ECgEthereumOnBoardState.AccountCreatedGame -> ECgEthereumOnBoardState.UnlockAccountGame.");
                    }
                }
                // Check Player Account exists
                {
                    ICgBlockchainAccount iaccount = null;

                    eth.Accounts.TryGetValue("Player", out iaccount);

                    if (iaccount == null)
                    {
                        eth.OnBoardStateFlag.SetEnd(ECgEthereumOnBoardState.MAX);
                        eth.OnBoardStateFlag.SetStart(ECgEthereumOnBoardState.AccountCreatedPlayer);

                        CgEthereumNewAccountInfo info = new CgEthereumNewAccountInfo("Player", "Player");

                        eth.NewAccount(info);

                        // Waittill OnBoardState == ECgEthereumOnBoardState.AccountCreatedPlayer
                        yield return eth.OnBoardStateFlag;
                    }
                    else
                    {
                        eth.OnBoardState = ECgEthereumOnBoardState.AccountCreatedPlayer;
                    }

                    if (LogOnBoard.Log())
                    {
                        CgDebug.Log("CgEthereum.CreatePrivateChain: State Change: ECgEthereumOnBoardState.AccountCreatedGame -> ECgEthereumOnBoardState.AccountCreatedPlayer.");
                    }
                }
                // Unlock Player Account
                {
                    eth.OnBoardStateFlag.SetEnd(ECgEthereumOnBoardState.MAX);
                    eth.OnBoardStateFlag.SetStart(ECgEthereumOnBoardState.UnlockAccountPlayer);

                    eth.UnlockAccount("Player");

                    // Waittill OnBoardState == ECgEthereumOnBoardState.UnlockAccountPlayer
                    yield return eth.OnBoardStateFlag;

                    if (LogOnBoard.Log())
                    {
                        CgDebug.Log("CgEthereum.CreatePrivateChain: State Change: ECgEthereumOnBoardState.AccountCreatedPlayer -> ECgEthereumOnBoardState.UnlockAccountPlayer.");
                    }
                }

                {
                    //eth.SetCoinbase("World");
                    eth.GetBalanceEther("World");
                    yield return 2.0f;
                    eth.SetCoinbase("World");
                    yield return 2.0f;
                    eth.StartMiner();

                    yield return 4.0f;

                    eth.StopMiner();

                    yield return 2.0f;
                    eth.GetBalanceEther("World");
                }
            }
            */
            // Check World Balance

            /*
            // Load Accounts, if any
            eth.LoadAccounts();

            // If NO Accounts, delete any old Keystores
            if (eth.Accounts.Count == EMPTY)
            {
                string[] fileNames = Directory.GetFiles(eth.KeystoreDirectory);

                foreach (string name in fileNames)
                {
                    File.Delete(eth.KeystoreDirectory + "\\" + name);
                }
            }

            // Create Accounts for Game, World, and Player
            */

            //eth.ListAccounts();


            //eth.NewAccount("world");
            //eth.StartMiner();

            //yield return 10.0f;

            //eth.Log("start");
            //eth.StartMiner();
            /*
            yield return 2.0f;

            eth.Log("stop");
            eth.StopMiner();
            */
        }

        public override void OpenConsole()
        {
            if (IsConsoleOpen)
                return;

            ECgBlockchainCommand command = ECgEthereumCommand.AttachToConsole;

            CgBlockchainProcessStartInfo startInfo = new CgBlockchainProcessStartInfo();
            startInfo.FileName              = ConsoleFullPath;
            startInfo.Arguments             = Commands[command];
            startInfo.RedirectStandardInput = true;
            startInfo.AddMonitorOutputEvent(MonitorOutputEvents[command]);

            ECgBlockchainProcessType processType = ECgBlockchainProcessType.Console;

            //EnqueueCommand(processType, command);
            StartProcess(processType, startInfo);

            IsConsoleOpen = true;
        }

        public override void CloseConsole()
        {
            if (!IsConsoleOpen)
                return;

            // StopProcess(ECgBlockchainProcessType.Console);

            RunCommand(ECgBlockchainProcessType.Console, ECgEthereumCommand.ExitConsole);

            IsConsoleOpen = false;
        }

        #region "Account"

        public override void LoadAccounts()
        {
            string[] paths = Directory.GetFiles(AccountsDirectory);

            foreach (string path in paths)
            {
                CgEthereumAccount a = new CgEthereumAccount();
                a.ParseFromFilePath(path);
                Accounts.Add(a.Nickname, a);
            }

            // Check there is a matching Keystore for each Account

            paths = Directory.GetFiles(KeystoreDirectory);
            Dictionary<string, ICgBlockchainAccount>.KeyCollection names = Accounts.Keys;
            List<string> invalidAccounts = new List<string>();

            foreach (string path in paths)
            {
                CgEthereumAccount linkedAcccount = null;

                foreach (string name in names)
                {
                    CgEthereumAccount a = (CgEthereumAccount)Accounts[name];

                    if (path.Contains(a.Address))
                    {
                        linkedAcccount = a;
                        break;
                    }
                }

                // Delete the Keystore if it is not linked to an account
                if (linkedAcccount == null)
                {
                    File.Delete(path);

                    if (LogAccountLoad.Get())
                    {
                        string[] parts = path.Split(new string[] {"--"}, StringSplitOptions.None);
                        string address = parts[2];

                        CgDebug.Log("CgEthereum.LoadAccounts: Failed to link Keystore with address: " + address + " to an Account.");
                        CgDebug.Log("-- deleting: " + path);
                    }
                    invalidAccounts.Add(linkedAcccount.Nickname);
                }
                else
                {
                    CreateKeystore(linkedAcccount);
                }
            }
            // Check remaining Accounts that did NOT get matched with a keystore

            foreach (string name in invalidAccounts)
            {
                CgEthereumAccount account = (CgEthereumAccount)Accounts[name];

                // Delete the Account file
                string path = AccountsDirectory + "\\" + name + "--" + account.Address + ".json";

                if (File.Exists(path))
                    File.Delete(path);

                // Remove the Account
                Accounts.Remove(name);

                if (LogAccountLoad.Get())
                {
                    CgDebug.Log("CgEthereum.LoadAccounts: Failed to link Account with Nickname: " + name + " and address: " + account.Address + " to any Keystore.");
                    CgDebug.Log("-- deleting: " + path);
                }
            }
        }

        public override void NewAccount(object payload)
        {
            CgEthereumNewAccountInfo info = (CgEthereumNewAccountInfo)payload;
            
            ICgBlockchainAccount iaccount;
            Accounts.TryGetValue(info.Nickname, out iaccount);

            if (iaccount != null)
            {
                UnityEngine.Debug.LogWarning("CgEthereum.NewAccount: Account with Nickname: " + info.Nickname + " already exists.");
                return;
            }

            CommandFlag.Set(false);

            CgBlockchainCommandArgument[] args = new CgBlockchainCommandArgument[1];
            args[0]                            = new CgBlockchainCommandArgument(ECgBlockchainCommandArgumentType.StringString, info.Passphrase);

            CurrentCommandInfo.Set(ECgEthereumCommand.NewAccount, args, payload);

            RunCommand(ECgBlockchainProcessType.Console, ECgEthereumCommand.NewAccount, args);
        }

        public void OnAccountCreated(ICgBlockchainAccount account)
        {
            if (LogAccountCreated.Log())
            {

            }

            // TODO: Put in SgEthereum

            // World
            if (account.Nickname == "World")
            {
                OnBoardState = ECgEthereumOnBoardState.AccountCreatedWorld;
                OnBoardStateFlag.SetEnd(OnBoardState);
            }
            // Game
            else
            if (account.Nickname == "Game")
            {
                OnBoardState = ECgEthereumOnBoardState.AccountCreatedGame;
                OnBoardStateFlag.SetEnd(OnBoardState);
            }
            // Player
            else
            if (account.Nickname == "Player")
            {
                OnBoardState = ECgEthereumOnBoardState.AccountCreatedPlayer;
                OnBoardStateFlag.SetEnd(OnBoardState);
            }
        }

        public string GetKeystoreFilePath(string address)
        {
            string[] paths = Directory.GetFiles(KeystoreDirectory);

            foreach (string path in paths)
            {
                if (path.Contains(address))
                {
                    return path;
                }
            }
            return "";
        }

        public void CreateKeystore(CgEthereumAccount account)
        {
            string path = GetKeystoreFilePath(account.Address);
            
            if (path == "")
            {
                CgCoroutineScheduler.Get().Start(ECgCoroutineSchedule.Update, CreateKeystore_Internal(this, account));
            }
            else
            {
                CgEthereumKeystore keystore = new CgEthereumKeystore();
                keystore.ParseFromFilePath(path);
                
                Keystores.Add(account.Nickname, keystore);

                if (LogAccountCreated.Log() || LogAccountLoad.Get())
                {
                    CgDebug.Log("CgEthereum.CreateKeystore: Keystore linked to Account with Nickname: " + account.Nickname);
                    CgDebug.Log("-- saved to: " + path);
                }
            }
        }

        public static IEnumerator CreateKeystore_Internal(CgEthereum eth, CgEthereumAccount account)
        {
            string keystoreFilePath = "";

            while (keystoreFilePath == "")
            {
                string[] paths = Directory.GetFiles(eth.KeystoreDirectory);

                foreach (string path in paths)
                {
                    if (path.Contains(account.Address))
                    {
                        keystoreFilePath = path;
                        break;
                    }

                    if (keystoreFilePath != "")
                        break;
                }

                if (keystoreFilePath == "")
                    yield return null;
            }

            CgEthereumKeystore keystore = new CgEthereumKeystore();
            keystore.ParseFromFilePath(keystoreFilePath);

            eth.Keystores.Add(account.Nickname, keystore);

            if (LogAccountCreated.Log())
            {
                CgDebug.Log("CgEthereum.CreateKeystore: Keystore created for Account with Nickname: " + account.Nickname);
                CgDebug.Log("-- saved to: " + keystoreFilePath);
            }
        }

        public override void UnlockAccount(object payload)
        {
            string nickname = (string)payload;

            ICgBlockchainAccount iaccount;
            Accounts.TryGetValue(nickname, out iaccount);

            if (iaccount == null)
            {
                UnityEngine.Debug.LogWarning("CgEthereum.UnlockAccount: Account with Nickname: " + nickname + " does NOT exist.");
                return;
            }

            CommandFlag.Set(false);

            CgEthereumAccount account = (CgEthereumAccount)iaccount;

            CgBlockchainCommandArgument[] args;
            account.CreateUnlockArguments(out args);

            CurrentCommandInfo.Set(ECgEthereumCommand.NewAccount, args, payload);

            AddMonitorOutputEvenToProcess(ECgBlockchainProcessType.Console, ECgEthereumCommand.UnlockAccount);
            RunCommand(ECgBlockchainProcessType.Console, ECgEthereumCommand.UnlockAccount, args);
        }

        public override void ListAccounts()
        {
            RunCommand(ECgBlockchainProcessType.Console, ECgEthereumCommand.ListAccounts, null);
        }

        public void SetCoinbase(object payload)
        {
            CommandFlag.Set(false);

            // payload = nickname
            string nickname           = (string)payload;
            CgEthereumAccount account = (CgEthereumAccount)Accounts[nickname];

            CgBlockchainCommandArgument[] args = new CgBlockchainCommandArgument[1];
            args[0].Value                      = account.Address;
            args[0].ValueType                  = ECgBlockchainCommandArgumentType.StringString;

            CurrentCommandInfo.Set(ECgEthereumCommand.SetEtherbase, args, payload);

            AddMonitorOutputEvenToProcess(ECgBlockchainProcessType.Console, ECgEthereumCommand.SetEtherbase);
            RunCommand(ECgBlockchainProcessType.Console, ECgEthereumCommand.SetEtherbase, args);
        }

        // public void GetBalance(object payload)

        public void GetBalanceEther(string nickname)
        {
            CommandFlag.Set(false);

            CgEthereumAccount account = (CgEthereumAccount)Accounts[nickname];

            CgBlockchainCommandArgument[] args = new CgBlockchainCommandArgument[1];
            args[0].Value                      = account.Address;
            args[0].ValueType                  = ECgBlockchainCommandArgumentType.StringString;
            
            CurrentCommandInfo.Set(ECgEthereumCommand.GetBalanceEther, args, nickname);
            CurrentCommandOuput = null;

            //AddMonitorOutputEvenToProcess(ECgBlockchainProcessType.Console, ECgEthereumCommand.GetBalanceEther);
            RunCommand(ECgBlockchainProcessType.Console, ECgEthereumCommand.GetBalanceEther, args);
        }

        public void SetupAccount(string nickname)
        {
            SetupAccountFlag.Set(false);
            CgCoroutineScheduler.Get().Start(ECgCoroutineSchedule.Update, SetupAccount_Internal(this, nickname));
        }

        public static IEnumerator SetupAccount_Internal(CgEthereum eth, string nickname)
        {
            // Check Account exists
            {
                ICgBlockchainAccount iaccount;

                if (!eth.Accounts.TryGetValue(nickname, out iaccount))
                {
                    CgEthereumNewAccountInfo info = new CgEthereumNewAccountInfo(nickname, nickname);

                    eth.NewAccount(info);

                    // Waittill NewAccount command has completed
                    yield return eth.CommandFlag;

                    if (LogAccountSetup.Log())
                    {
                        CgDebug.Log("CgEthereum.SetupAccount: Created Account for: " + nickname);
                    }
                }
            }
            // Unlock Account
            {
                eth.UnlockAccount(nickname);

                // Waittill UnlockAccount command has completed
                yield return eth.CommandFlag;

                if (LogAccountSetup.Log())
                {
                    CgEthereumAccount account = (CgEthereumAccount)eth.Accounts[nickname];

                    CgDebug.Log("CgEthereum.SetupAccount: Unlocked Account (" + nickname + "): " + account.Address);
                }
            }
            // Check Balance is above Threshold
            {
                eth.GetBalanceEther(nickname);

                // Waittill GetBalanceEther command has completed
                yield return eth.CommandFlag;

                // If the balance is below the threshold, Start Mining
                int balance = (int)eth.CurrentCommandOuput;
                int threshold = 20;
                
                if (balance < threshold)
                {
                    // Set Coinbase
                    eth.SetCoinbase(nickname);

                    // Waittill SetEtherbase command has completed
                    yield return eth.CommandFlag;

                    if (LogAccountSetup.Log())
                    {
                        CgEthereumAccount account = (CgEthereumAccount)eth.Accounts[nickname];

                        CgDebug.Log("CgEthereum.SetupAccount: Setting Account (" + nickname + "): " + account.Address + " as coinbase.");
                    }

                    // Start Mining
                    eth.StartMiner();

                    // Waittill StartMiner command has completed
                    yield return eth.CommandFlag;

                    if (LogAccountSetup.Log())
                    {
                        CgEthereumAccount account = (CgEthereumAccount)eth.Accounts[nickname];

                        CgDebug.Log("CgEthereum.SetupAccount: Account (" + nickname + "): " + account.Address + " balance is: " + balance + " < " + threshold + ". Start mining.");
                    }

                    float interval = 0.5f;

                    while (balance < threshold)
                    {
                        yield return interval;

                        // Check Balance
                        eth.GetBalanceEther(nickname);

                        // Waittill GetBalanceEther command has completed
                        yield return eth.CommandFlag;

                        // If the balance is below the threshold, Start Mining
                        balance = (int)eth.CurrentCommandOuput;

                        if (LogAccountSetup.Log())
                        {
                            CgEthereumAccount account = (CgEthereumAccount)eth.Accounts[nickname];

                            CgDebug.Log("CgEthereum.SetupAccount: Account (" + nickname + "): " + account.Address + " balance is: " + balance);
                        }
                    }

                    // Stop Mining
                    eth.StopMiner();

                    // Waittill StopMiner command has completed
                    yield return eth.CommandFlag;

                    if (LogAccountSetup.Log())
                    {
                        CgEthereumAccount account = (CgEthereumAccount)eth.Accounts[nickname];

                        CgDebug.Log("CgEthereum.SetupAccount: Finished mining.");
                    }
                }
                // Finish
                else
                {
                    if (LogAccountSetup.Log())
                    {
                        CgEthereumAccount account = (CgEthereumAccount)eth.Accounts[nickname];

                        CgDebug.Log("CgEthereum.SetupAccount: Finished setup for Account (" + nickname + "): " + account.Address);
                    }
                }
            }
            eth.SetupAccountFlag.Set(true);
        }

        #endregion // Account

        public override void StartMiner()
        {
            if (IsMining)
                return;

            CommandFlag.Set(false);

            CurrentCommandInfo.Set(ECgEthereumCommand.StartMiner, null, null);
            CurrentCommandOuput = null;

            AddMonitorOutputEvenToProcess(ECgBlockchainProcessType.Console, ECgEthereumCommand.StartMiner);
            RunCommand(ECgBlockchainProcessType.Console, ECgEthereumCommand.StartMiner, null);
            IsMining = true;
        }

        public override void StopMiner()
        {
            if (!IsMining)
                return;

            CommandFlag.Set(false);

            CurrentCommandInfo.Set(ECgEthereumCommand.StopMiner, null, null);
            CurrentCommandOuput = null;

            AddMonitorOutputEvenToProcess(ECgBlockchainProcessType.Console, ECgEthereumCommand.StopMiner);
            RunCommand(ECgBlockchainProcessType.Console, ECgEthereumCommand.StopMiner, null);

            IsMining = false;
        }
    }
}

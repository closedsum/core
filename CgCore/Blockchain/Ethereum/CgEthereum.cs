// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
namespace CgCore
{
    using System;
    using System.Collections;
    using System.Collections.Generic;
    using System.Diagnostics;
    using System.IO;
    using UnityEngine;

    using Sg;

    public enum ECgEthereumOnBoardState : byte
    {
        Init,
        Start,
        Attach,
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
        public static readonly ECgBlockchainCommand StartMiner = EMCgBlockchainCommand.Get().Create("StartMiner");
        public static readonly ECgBlockchainCommand StopMiner = EMCgBlockchainCommand.Get().Create("StopMiner");

        public static readonly ECgBlockchainCommand MAX = EMCgBlockchainCommand.Get().Create("MAX");
    }

    public class CgEthereum : CgBlockchain
    {
        #region "Data Members"

        public string ConsoleFullPath;
        public string GenesisFullPath;

        public CgRoutine.BoolType IsRunningInstanceCloseFlag;

        ECgEthereumOnBoardState OnBoardState;
        TCgFlagType<ECgEthereumOnBoardState> OnBoardStateFlag;

        Dictionary<ECgBlockchainCommand, CgProcessMonitorOutputEvent> MonitorOutputEvents;

        #endregion // Data Members

        public CgEthereum()
        {
            Genesis = new CgEthereumGenesis();

            StorageType = ECgBlockchainStorageType.Private;

            Processes = new Dictionary<ECgBlockchainProcessType, CgProcess>(new ECgBlockchainProcessTypeEqualityComparer());

            for (byte i = 0; i < (byte)ECgBlockchainProcessType.MAX; ++i)
            {
                Processes.Add((ECgBlockchainProcessType)i, null);
            }

            ConsoleFilename = "geth.exe";
            string path = Application.dataPath;
            path = path.Substring(0, path.Length - 6);

            ConsoleDirectory = path + "Blockchain\\Ethereum\\Geth";
            ConsoleFullPath = ConsoleDirectory + "\\" + ConsoleFilename;
            RootDirectory = path + "Blockchain\\Ethereum";
            GenesisFullPath = RootDirectory + "/genesis.json"; ;

            IsRunningInstanceCloseFlag = new CgRoutine.BoolType();
            IsRunningInstanceCloseFlag.Set(true);

            ChainDirectory = path + "Blockchain\\Ethereum\\chaindata";

            Commands = new Dictionary<ECgBlockchainCommand, string>(new ECgBlockchainCommandEqualityComparer());

            CommandRequests = new Dictionary<ECgBlockchainProcessType, Dictionary<ECgBlockchainCommand, CgBlockchainCommandRequest>>(new ECgBlockchainProcessTypeEqualityComparer());

            for (byte i = 0; i < (byte)ECgBlockchainProcessType.MAX; ++i)
            {
                ECgBlockchainProcessType processType = (ECgBlockchainProcessType)i;

                CommandRequests.Add(processType, new Dictionary<ECgBlockchainCommand, CgBlockchainCommandRequest>(new ECgBlockchainCommandEqualityComparer()));
            }

            CurrentCommandRequests = new Dictionary<ECgBlockchainProcessType, CgBlockchainCommandRequest>(new ECgBlockchainProcessTypeEqualityComparer());

            for (byte i = 0; i < (byte)ECgBlockchainProcessType.MAX; ++i)
            {
                ECgBlockchainProcessType processType = (ECgBlockchainProcessType)i;

                CurrentCommandRequests.Add(processType, null);
            }

            CommandRequestQueue = new Dictionary<ECgBlockchainProcessType, Queue<CgBlockchainCommandRequest>>(new ECgBlockchainProcessTypeEqualityComparer());

            for (byte i = 0; i < (byte)ECgBlockchainProcessType.MAX; ++i)
            {
                ECgBlockchainProcessType processType = (ECgBlockchainProcessType)i;

                CommandRequestQueue.Add(processType, new Queue<CgBlockchainCommandRequest>());
            }

            Accounts = new Dictionary<string, ICgBlockchainAccount>();

            MonitorOutputEvents = new Dictionary<ECgBlockchainCommand, CgProcessMonitorOutputEvent>(new ECgBlockchainCommandEqualityComparer());

            // Commands

            //SetCommand(ECgEthereumCommand.InitBlockchain, "\"" + ConsoleFullPath + "\" --datadir=\"" + ChainDirectory + "\" init \"" + RootDirectory + "\\genesis.json\"");
            //SetCommand(ECgEthereumCommand.SetDataDirectory, "\"" + ConsoleFullPath + "\" --datadir=\"" + ChainDirectory + "\" --networkid 15");
            SetCommand(ECgEthereumCommand.InitBlockchain, "--datadir=\"" + ChainDirectory + "\" init \"" + RootDirectory + "\\genesis.json\"");
            SetCommand(ECgEthereumCommand.SetDataDirectory, "--datadir=\"" + ChainDirectory + "\" --networkid 15");
            {
                CgStringSentence sentence = new CgStringSentence();
                    CgStringPhrase phrase = new CgStringPhrase();
                    phrase.AddAndToWord(0, "IPC endpoint opened", ECgStringWordRule.None);
                    sentence.AddPhrase(phrase);

                CgProcessMonitorOutputEvent e = new CgProcessMonitorOutputEvent(ECgEthereumCommand.SetDataDirectory, sentence, ECgProcessMonitorOutputEventPurpose.FireOnce);
                e.AddEvent(OnCommandCompleted);

                MonitorOutputEvents.Add(ECgEthereumCommand.SetDataDirectory, e);

                CgBlockchainCommandRequest request = new CgBlockchainCommandRequest(ECgEthereumCommand.SetDataDirectory, null);
                    request.AddFulfillment(ECgBlockchainCommandFulfillmentRule.Contain, "IPC endpoint opened"); // TODO: also include "url=\\\\.\\pipe\\geth.ipc"?
                    request.RunWhenRelevant = false;
                    request.Completed_Event.Add(OnCommandCompleted);
                CommandRequests[ECgBlockchainProcessType.RunningInstance].Add(ECgEthereumCommand.SetDataDirectory, request);
            }
            //SetCommand(ECgEthereumCommand.ChangeToRootDirectory, "cd /d \"" + RootDirectory + "\"");
            //SetCommand(ECgEthereumCommand.AttachToConsole, "\"" + ConsoleFullPath + "\" attach ipc:\\\\.\\pipe\\geth.ipc");
            SetCommand(ECgEthereumCommand.AttachToConsole, "attach ipc:\\\\.\\pipe\\geth.ipc");
            {
                CgBlockchainCommandRequest request = new CgBlockchainCommandRequest(ECgEthereumCommand.AttachToConsole, null);
                    request.AddFulfillment(ECgBlockchainCommandFulfillmentRule.Contain, "welcome");
                    request.AddFulfillment(ECgBlockchainCommandFulfillmentRule.None, "");
                    request.AddFulfillment(ECgBlockchainCommandFulfillmentRule.Contain, "instance:");
                    request.AddFulfillment(ECgBlockchainCommandFulfillmentRule.Contain, "modules:");
                    request.AddFulfillment(ECgBlockchainCommandFulfillmentRule.None, "");
                    request.RunWhenRelevant = false;
                    request.Completed_Event.Add(OnCommandCompleted);
                CommandRequests[ECgBlockchainProcessType.Console].Add(ECgEthereumCommand.AttachToConsole, request);

            }
            SetCommand(ECgEthereumCommand.ExitConsole, "exit");
            SetCommand(ECgEthereumCommand.NewAccount, "personal.newAccount(%s)");
            SetCommand(ECgEthereumCommand.UnlockAccount, "personal.unlockAccount(%s,%s,%s)");
            SetCommand(ECgEthereumCommand.ListAccounts, "personal.listAccounts");
            SetCommand(ECgEthereumCommand.StartMiner, "miner.start();");
            {
                CgBlockchainCommandRequest request = new CgBlockchainCommandRequest(ECgEthereumCommand.StartMiner, null);
                request.AddFulfillment(ECgBlockchainCommandFulfillmentRule.None, "");
                request.Completed_Event.Add(OnCommandCompleted);
                CommandRequests[ECgBlockchainProcessType.Console].Add(ECgEthereumCommand.StartMiner, request);
            }
            SetCommand(ECgEthereumCommand.StopMiner, "miner.stop();");
            {
                CgBlockchainCommandRequest request = new CgBlockchainCommandRequest(ECgEthereumCommand.StopMiner, null);
                request.AddFulfillment(ECgBlockchainCommandFulfillmentRule.None, "");
                request.Completed_Event.Add(OnCommandCompleted);
                CommandRequests[ECgBlockchainProcessType.Console].Add(ECgEthereumCommand.StopMiner, request);
            }

            OnBoardState = ECgEthereumOnBoardState.Init;
            OnBoardStateFlag = new TCgFlagType<ECgEthereumOnBoardState>(ECgEthereumOnBoardState.Init, ECgEthereumOnBoardState.MAX);

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
                List<string> parts = new List<string>();
                parts.Add("");
                int index = 0;

                int commandLength = value.Length;

                for (int i = 0; i < commandLength; ++i)
                {
                    char c = value[i];

                    // Check for Wildcards
                    if (c == '%')
                    {
                        // Check for type
                        if (i < commandLength - 1)
                        {
                            char w = value[i + 1];

                            if (w == 's')
                            {
                                parts.Add("");
                                ++index;
                                ++i;
                            }
                        }
                        else
                        {
                            parts[index] += c;
                        }
                    }
                    else
                    {
                        parts[index] += c;
                    }
                }

                // Add in arguments
                if ((parts.Count - 1) == args.Length)
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
                    UnityEngine.Debug.Log("CgEthereum.RunCommand: Failed to run command: " + command.Name + ". Wildcard count != Argument count (" + (parts.Count-1) + "," + args.Length + ")");
                }
            }
            RunCommand(processType, value);
        }

        public override void EnqueueCommand(ECgBlockchainProcessType processType, CgBlockchainCommandRequest request)
        {
            CommandRequestQueue[processType].Enqueue(request);

            if (CurrentCommandRequests[processType] == null)
            {
                CurrentCommandRequests[processType] = CommandRequestQueue[processType].Peek();

                if (request.RunWhenRelevant)
                    RunCommand(processType, request.Command, request.Arguments);
            }
        }

        public override void EnqueueCommand(ECgBlockchainProcessType processType, ECgBlockchainCommand command)
        {
            EnqueueCommand(processType, CommandRequests[processType][command]);
        }

        public void OnCommandCompleted(CgBlockchainCommandRequest request)
        {
            if (LogCommandCompleted.Log())
            {
                CgDebug.Log("CgEthereum.OnCommandCompleted: Completed command: " + request.Command);
            }

            // SetDataDirectory
            if (request.Command == ECgEthereumCommand.SetDataDirectory)
            {
                OnBoardState = ECgEthereumOnBoardState.Start;
                OnBoardStateFlag.SetEnd(ECgEthereumOnBoardState.Start);
            }
            // AttachToConsole
            if (request.Command == ECgEthereumCommand.AttachToConsole)
            {
                OnBoardState = ECgEthereumOnBoardState.Attach;
                OnBoardStateFlag.SetEnd(ECgEthereumOnBoardState.Attach);
            }
        }

        public void OnCommandCompleted(string name)
        {
            if (LogCommandCompleted.Log())
            {
                CgDebug.Log("CgEthereum.OnCommandCompleted: Completed command: " + name);
            }

            // SetDataDirectory
            if (name == ECgEthereumCommand.SetDataDirectory)
            {
                OnBoardState = ECgEthereumOnBoardState.Start;
                OnBoardStateFlag.SetEnd(ECgEthereumOnBoardState.Start);
            }
        }

        public void OnProcessOutputRecieved(object sender, DataReceivedEventArgs e)
        {
            if (LogIO.Log())
            {
                CgDebug.Log("Process (Output): " + e.Data);
            }
            CheckCommandRequestQueue(ECgBlockchainProcessType.RunningInstance, e.Data);
        }

        public void OnProcessErrorRecieved(object sender, DataReceivedEventArgs e)
        {
            if (LogIO.Log())
            {
                CgDebug.Log("Process (Error): " + e.Data);
            }
            CheckCommandRequestQueue(ECgBlockchainProcessType.RunningInstance, e.Data);
        }

        public void CheckCommandRequestQueue(ECgBlockchainProcessType processType, string output)
        {
            if (CurrentCommandRequests[processType] == null)
                return;

            if (CurrentCommandRequests[processType].HasCompleted(output))
            {
                CommandRequestQueue[processType].Dequeue();

                if (CommandRequestQueue[processType].Count > EMPTY)
                {
                    CgBlockchainCommandRequest request = CommandRequestQueue[processType].Peek();

                    if (request.RunWhenRelevant)
                        RunCommand(processType, request.Command, request.Arguments);
                }
                else
                {
                    CurrentCommandRequests[processType] = null;
                }
            }
        }

        public void OnConsoleOutputRecieved(object sender, DataReceivedEventArgs e)
        {
            if (LogIO.Log())
            {
                UnityEngine.Debug.Log("Console (Output): " + e.Data);
            }
            CheckCommandRequestQueue(ECgBlockchainProcessType.Console, e.Data);
        }

        public void OnConsoleErrorRecieved(object sender, DataReceivedEventArgs e)
        {
            if (LogIO.Log())
            {
                UnityEngine.Debug.Log("Console (Error): " + e.Data);
            }
            CheckCommandRequestQueue(ECgBlockchainProcessType.Console, e.Data);
        }

        public void OnProcessExited(object sender, EventArgs e)
        {
            if(LogIO.Log())
            {
                UnityEngine.Debug.Log("Blockchain (Process): Exited");
            }

            Processes[ECgBlockchainProcessType.RunningInstance].DeAllocate();
            Processes[ECgBlockchainProcessType.RunningInstance] = null;
            IsRunningInstanceOpen = false;
            IsRunningInstanceCloseFlag.Set(true);
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

                p = ICgManager_Process.Get().Spawn(EMCgProcess.Get()["Blockchain"], payload);

                SetProcess(processType, p);
            }
            else
            {
                CgDebug.Log("CgEthereum.StartProcess: StartProcess called for running Process: " + processType.ToString() + " before the process exited.");
            }
            /*
            p = new Process();

            

            // ProcessStartInfo
            ProcessStartInfo psi    = p.StartInfo;
            psi.CreateNoWindow      = !ShowProcessWindow.Get();
            psi.UseShellExecute     = false;
            psi.FileName            = startInfo.FileName;
            psi.Arguments           = startInfo.Arguments;
            psi.ErrorDialog         = false;
            psi.RedirectStandardInput = startInfo.RedirectStandardInput;
            psi.RedirectStandardOutput = true;
            psi.RedirectStandardError = true;
            p.EnableRaisingEvents = true;

            if (processType == ECgBlockchainProcessType.Console)
            {
                p.OutputDataReceived += ConsoleOutputRecieved;
                p.ErrorDataReceived += ConsoleErrorRecieved;
                p.Exited += OnConsoleExited;
            }
            else
            {
                p.OutputDataReceived += ProcessOutputRecieved;
                p.ErrorDataReceived += ProcessErrorRecieved;
                p.Exited += OnProcessExited;
            }

            p.Start();
            p.BeginErrorReadLine();
            p.BeginOutputReadLine();
            */
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

            ECgBlockchainProcessType processType = ECgBlockchainProcessType.RunningInstance;

            //EnqueueCommand(processType, command);

            Processes[processType].AddMonitorOuputEvent(MonitorOutputEvents[command]);

            StartProcess(processType, startInfo);
            
            IsRunningInstanceOpen = true;
            IsRunningInstanceCloseFlag.Set(false);
        }

        public override void CreatePrivateChain()
        {
            // Create chaindata Directory
            if (!Directory.Exists(ChainDirectory))
            {
                Directory.CreateDirectory(ChainDirectory);
            }

            // Create genesis.json
            string json = Genesis.ToStr();

            File.WriteAllText(GenesisFullPath, json, System.Text.Encoding.ASCII);

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
            bool genesisExists = File.Exists(eth.GenesisFullPath);

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
            eth.Genesis.ParseFromFile(eth.GenesisFullPath);

            // Waittill OnBoardState == ECgEthereumOnBoardState.Start
            yield return eth.OnBoardStateFlag;

            // Attach / Open Console

            if (LogOnBoard.Log())
            {
                CgDebug.Log("CgEthereum.CreatePrivateChain: State Change: ECgEthereumOnBoardState.Start -> ECgEthereumOnBoardState.Attach.");
            }

            eth.OnBoardStateFlag.SetEnd(ECgEthereumOnBoardState.MAX);
            eth.OnBoardStateFlag.SetStart(ECgEthereumOnBoardState.Attach);

            eth.OpenConsole();

            yield return eth.OnBoardStateFlag;

            CgDebug.Log("here");
            eth.ListAccounts();
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

            ECgBlockchainProcessType processType = ECgBlockchainProcessType.Console;

            EnqueueCommand(processType, command);
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

        public override void NewAccount(object payload)
        {
            string nickname = (string)payload;
            
            ICgBlockchainAccount iaccount;
            Accounts.TryGetValue(nickname, out iaccount);

            if (iaccount != null)
            {
                UnityEngine.Debug.LogWarning("CgEthereum.NewAccount: Account with Nickname: " + nickname + " already exists.");
                return;
            }

            CgBlockchainCommandArgument[] args = new CgBlockchainCommandArgument[1];
            args[0]                            = new CgBlockchainCommandArgument(ECgBlockchainCommandArgumentType.StringString, nickname);

            RunCommand(ECgBlockchainProcessType.Console, ECgEthereumCommand.NewAccount, args);
            // TODO: Need to fill in account details in ProcessOutputRecieved
            Accounts.Add(nickname, new CgEthereumAccount(nickname));
        }

        public override void UnlockAccount(object payload)
        {
            string nickname = (string)payload;

            ICgBlockchainAccount iaccount;
            Accounts.TryGetValue(nickname, out iaccount);

            if (iaccount != null)
            {
                UnityEngine.Debug.LogWarning("CgEthereum.UnlockAccount: Account with Nickname: " + nickname + " does NOT exist.");
                return;
            }

            CgEthereumAccount account = (CgEthereumAccount)iaccount;

            CgBlockchainCommandArgument[] args;
            account.CreateUnlockArguments(out args);

            RunCommand(ECgBlockchainProcessType.Console, ECgEthereumCommand.UnlockAccount, args);
        }

        public override void ListAccounts()
        {
            RunCommand(ECgBlockchainProcessType.Console, ECgEthereumCommand.ListAccounts, null);
        }

        public override void StartMiner()
        {
            if (IsMining)
                return;
            //if (!IsConsoleOpen)
            //   OpenConsole();
            //RunCommand(ECgBlockchainProcessType.Console,"personal.listAccounts");
            RunCommand(ECgBlockchainProcessType.Console, ECgEthereumCommand.StartMiner, null);
            IsMining = true;
        }

        public override void StopMiner()
        {
            if (!IsMining)
                return;

            RunCommand(ECgBlockchainProcessType.Console, ECgEthereumCommand.StopMiner, null);

            IsMining = false;
        }
    }
}

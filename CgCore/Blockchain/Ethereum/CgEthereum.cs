// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
namespace CgCore
{
    using System;
    using System.Collections;
    using System.Collections.Generic;
    using System.Diagnostics;
    using System.IO;
    using System.Linq;
    using UnityEngine;

    public struct CgEthereumAccountInfo
    {
        public string Nickname;
        public string Passphrase;

        public CgEthereumAccountInfo(string nickname, string passphrase)
        {
            Nickname = nickname;
            Passphrase = passphrase;
        }
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
        public static readonly ECgBlockchainCommand DeployContract = EMCgBlockchainCommand.Get().Create("DeployContract");
        public static readonly ECgBlockchainCommand LoadScript = EMCgBlockchainCommand.Get().Create("LoadScript");
        public static readonly ECgBlockchainCommand CreateContractABI = EMCgBlockchainCommand.Get().Create("CreateContractABI");
        public static readonly ECgBlockchainCommand CreateContractInstance = EMCgBlockchainCommand.Get().Create("CreateContractInstance");
        public static readonly ECgBlockchainCommand RunContractConstantFunction = EMCgBlockchainCommand.Get().Create("RunContractConstantFunction");
        public static readonly ECgBlockchainCommand RunContractStateChangeFunction = EMCgBlockchainCommand.Get().Create("RunContractStateChangeFunction");
        public static readonly ECgBlockchainCommand GetGasEstimate = EMCgBlockchainCommand.Get().Create("GetGasEstimate");

        public static readonly ECgBlockchainCommand MAX = EMCgBlockchainCommand.Get().Create("MAX");
    }

    public sealed class ECgEthereumJavascript : ECgEnum_byte
    {
        public ECgEthereumJavascript(byte value, string name) : base(value, name) { }
    }

    public sealed class ECgEthereumJavascriptEqualityComparer : IEqualityComparer<ECgEthereumJavascript>
    {
        public bool Equals(ECgEthereumJavascript lhs, ECgEthereumJavascript rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(ECgEthereumJavascript x)
        {
            return x.GetHashCode();
        }
    }

    public class EMCgEthereumJavascript : ECgEnumMap<ECgEthereumJavascript, byte>
    {
        private static EMCgEthereumJavascript _Instance;
        public static EMCgEthereumJavascript Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new EMCgEthereumJavascript();
                }
                return _Instance;
            }
        }

        public static EMCgEthereumJavascript Get()
        {
            return Instance;
        }
    }

    public struct CgEthereumJavascriptContractLink
    {
        public readonly ECgBlockchainContract Contract;
        public readonly string Link;

        public CgEthereumJavascriptContractLink(ECgBlockchainContract contract, string link)
        {
            Contract = contract;
            Link = link;
        }
    }

    public class CgEthereum : CgBlockchain
    {
        #region "CVars"

        // Account
        public static CgConsoleVariableLog LogAccountLoad = new CgConsoleVariableLog("log.blockchain.account.load", false, "Log Blockchain (Ethereum) when Accounts get loaded", (int)ECgConsoleVariableFlag.Console);

        public static CgConsoleVariableLog LogAccountSetup = new CgConsoleVariableLog("log.blockchain.account.setup", false, "Log Blockchain (Ethereum) Account Setup", (int)ECgConsoleVariableFlag.Console);

        #endregion // CVars

        #region "Data Members"

        public string ConsoleFullPath;
        public string GenesisFilePath;
        public string KeystoreDirectory;

        protected Dictionary<string, CgEthereumKeystore> Keystores;

        public string ABIDirectory;
        protected Dictionary<ECgBlockchainContract, string> ABISnippets;

        public string Web3DeployDirectory;
        protected Dictionary<ECgBlockchainContract, string> Web3DeploySnippets;

        public string Web3DeployLinkedDirectory;
        protected Dictionary<ECgBlockchainContract, string> Web3DeployLinkedSnippets;

        protected Dictionary<ECgBlockchainContract, List<CgEthereumWeb3DeployLink>> Web3DeployLinks;

        public string JavascriptDirectory;
        public string JavascriptLinkedDirectory;
        protected Dictionary<ECgEthereumJavascript, string> ScriptPaths;
        protected Dictionary<ECgBlockchainContract, string> ScriptLinkedPaths;
        protected Dictionary<ECgBlockchainContract, List<CgEthereumJavascriptContractLink>> ScriptContractLinks;

        protected Dictionary<ECgBlockchainContract, Dictionary<ECgBlockchainContractFunction, CgBlockchainContractFunction>> ContractFunctions;

        public CgRoutine.BoolType IsRunningInstanceCloseFlag;

        protected Dictionary<ECgBlockchainCommand, CgProcessMonitorOutputEvent> MonitorOutputEvents;

        protected CgBlockchainCommandInfo CurrentCommandInfo;
        protected object CurrentCommandOuput;

        protected CgRoutine.BoolType CommandFlag;
        protected CgRoutine.BoolType SetupAccountFlag;
        protected CgRoutine.BoolType DeployContractFlag;
        protected CgRoutine.BoolType LoadContractsFlag;
        protected CgRoutine.BoolType SetupContractFlag;
        protected CgRoutine.BoolType RunContractStageChangeFunctionFlag;

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

            ContractsDirectory = RootDirectory + "\\Contracts";
            ContractsDeployedDirectory = ContractsDirectory + "\\Deployed";

            ABIDirectory = ContractsDirectory + "\\ABI";
            ABISnippets = new Dictionary<ECgBlockchainContract, string>(new ECgBlockchainContractEqualityComparer());

            Web3DeployDirectory = ContractsDirectory + "\\Web3Deploy";
            Web3DeploySnippets = new Dictionary<ECgBlockchainContract, string>(new ECgBlockchainContractEqualityComparer());

            Web3DeployLinkedDirectory = Web3DeployDirectory + "\\Linked";
            Web3DeployLinkedSnippets = new Dictionary<ECgBlockchainContract, string>(new ECgBlockchainContractEqualityComparer());

            Web3DeployLinks = new Dictionary<ECgBlockchainContract, List<CgEthereumWeb3DeployLink>>(new ECgBlockchainContractEqualityComparer());

            JavascriptDirectory = RootDirectory + "\\Javascript";
            JavascriptLinkedDirectory = JavascriptDirectory + "\\Linked";
            ScriptPaths = new Dictionary<ECgEthereumJavascript, string>(new ECgEthereumJavascriptEqualityComparer());
            ScriptLinkedPaths = new Dictionary<ECgBlockchainContract, string>(new ECgBlockchainContractEqualityComparer());
            ScriptContractLinks = new Dictionary<ECgBlockchainContract, List<CgEthereumJavascriptContractLink>>(new ECgBlockchainContractEqualityComparer());

            ContractFunctions = new Dictionary<ECgBlockchainContract, Dictionary<ECgBlockchainContractFunction, CgBlockchainContractFunction>>(new ECgBlockchainContractEqualityComparer());

            MonitorOutputEvents = new Dictionary<ECgBlockchainCommand, CgProcessMonitorOutputEvent>(new ECgBlockchainCommandEqualityComparer());

            CurrentCommandInfo = new CgBlockchainCommandInfo(ECgEthereumCommand.MAX, null, null);

            // Commands

                // InitBlockchain
            SetCommand(ECgEthereumCommand.InitBlockchain, "--datadir=\"" + ChainDirectory + "\" init \"" + RootDirectory + "\\genesis.json\"");
                // SetDataDirectory
            SetCommand(ECgEthereumCommand.SetDataDirectory, "--datadir=\"" + ChainDirectory + "\" --networkid 15 --gcmode archive");
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
                // LoadScript
            SetCommand(ECgEthereumCommand.LoadScript, "loadScript(%s)");
            {
                CgStringParagraph p = CgStringParagraphHelper.CreateOneWordParagraph("true", ECgStringWordRule.MatchCase);

                CgProcessMonitorOutputEvent e = new CgProcessMonitorOutputEvent(ECgEthereumCommand.LoadScript, p, ECgProcessMonitorOutputEventPurpose.FireOnce);
                e.AddEvent(OnCommandCompleted);

                MonitorOutputEvents.Add(ECgEthereumCommand.LoadScript, e);
            }
                // CreateContractABI
            SetCommand(ECgEthereumCommand.CreateContractABI, "%s");
            {
                CgStringParagraph p = CgStringParagraphHelper.CreateOneWordParagraph("", ECgStringWordRule.MatchCase);

                CgProcessMonitorOutputEvent e = new CgProcessMonitorOutputEvent(ECgEthereumCommand.CreateContractABI, p, ECgProcessMonitorOutputEventPurpose.FireOnce);
                e.AddEvent(OnCommandCompleted);

                MonitorOutputEvents.Add(ECgEthereumCommand.CreateContractABI, e);
            }
                // CreateContractInstance
            SetCommand(ECgEthereumCommand.CreateContractInstance, "var %s = %s.at(%s)");
            {
                CgStringParagraph p = CgStringParagraphHelper.CreateOneWordParagraph("undefined", ECgStringWordRule.MatchCase);

                CgProcessMonitorOutputEvent e = new CgProcessMonitorOutputEvent(ECgEthereumCommand.CreateContractInstance, p, ECgProcessMonitorOutputEventPurpose.FireOnce);
                e.AddEvent(OnCommandCompleted);

                MonitorOutputEvents.Add(ECgEthereumCommand.CreateContractInstance, e);
            }

            CommandFlag = new CgRoutine.BoolType();
            CommandFlag.Set(false);
            SetupAccountFlag = new CgRoutine.BoolType();
            SetupAccountFlag.Set(false);
            DeployContractFlag = new CgRoutine.BoolType();
            DeployContractFlag.Set(false);
            LoadContractsFlag = new CgRoutine.BoolType();
            LoadContractsFlag.Set(false);
            SetupContractFlag = new CgRoutine.BoolType();
            SetupContractFlag.Set(false);
            RunContractStageChangeFunctionFlag = new CgRoutine.BoolType();
            RunContractStageChangeFunctionFlag.Set(false);

            CommandCompleted_Event.Add(OnCommandCompleted);
            AccountCreated_Event.Add(OnAccountCreated);

            // Enums

            EMCgProcess.Get().Create("Blockchain");
            ICgManager_Process.Get().CreatePool(EMCgProcess.Get()["Blockchain"], 4);
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

        public override void Start()
        {
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
            // Contracts Deployed
            if (Directory.Exists(ContractsDeployedDirectory))
            {
                string[] paths = Directory.GetFiles(ContractsDeployedDirectory);

                foreach (string path in paths)
                {
                    File.Delete(path);
                }
            }
            // Web3Deploy Linked
            if (Directory.Exists(Web3DeployLinkedDirectory))
            {
                string[] paths = Directory.GetFiles(Web3DeployLinkedDirectory);

                foreach (string path in paths)
                {
                    File.Delete(path);
                }
            }
            // Javascript Contract Linked
            if (Directory.Exists(JavascriptLinkedDirectory))
            {
                string[] paths = Directory.GetFiles(JavascriptLinkedDirectory);

                foreach (string path in paths)
                {
                    File.Delete(path);
                }
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

        public override void RunCommand(int consoleIndex, string command)
        {
            CgProcess p = GetProcess(ECgBlockchainProcessType.Console, consoleIndex);

            if (p == null)
            {
                CgDebug.Log("CgEthereum.RunCommand: Failed to run command: " + command + ". Process Console has NOT started. Call OpenShell().");
                return;
            }

            if (LogIO.Log() || LogIOConsole.Log())
            {
                CgDebug.Log("Console (Input): " + command);
            }

            p.RunCommand(command);
        }

        public override void RunCommand(int consoleIndex, ECgBlockchainCommand command, CgBlockchainCommandArgument[] args = null)
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
                    CgDebug.Log("CgEthereum.RunCommand: Failed to run command: " + command.Name + ". Wildcard count != Argument count (" + (parts.Length-1) + "," + args.Length + ")");
                }
            }

            if (LogIO.Log() || LogIOConsole.Log())
            {
                CgDebug.Log("CgEthereum.RunCommand: Running command: " + command);
            }
            RunCommand(consoleIndex, value);
        }

        public void AddMonitorOutputEvenToProcess(ECgBlockchainProcessType processType, int index, CgProcessMonitorOutputEvent e)
        {
            // TODO: Later handle PrivateMultiNode
            Processes[processType].AddMonitorOuputEvent(e);
        }

        public void AddMonitorOutputEvenToProcess(ECgBlockchainProcessType processType, int index, ECgBlockchainCommand command)
        {
            // TODO: Later handle PrivateMultiNode
            AddMonitorOutputEvenToProcess(processType, index, MonitorOutputEvents[command]);
        }

        public virtual void OnCommandCompleted(ECgBlockchainCommand command)
        {
            if (LogCommandCompleted.Log())
            {
                CgDebug.Log("CgEthereum.OnCommandCompleted: Completed command: " + command);
            }

            // SetDataDirectory
            if (command == ECgEthereumCommand.SetDataDirectory)
            {
            }
            // AttachToConsole
            if (command == ECgEthereumCommand.AttachToConsole)
            {
            }
            // UnlockAccount
            if (command == ECgEthereumCommand.UnlockAccount)
            {
            }
            // SetEtherbase
            if (command == ECgEthereumCommand.SetEtherbase)
            {
                // Get Nickname
                //string nickname = (string)CurrentCommandInfo.Payload;
            }
            // GetBalanceEther
            if (command == ECgEthereumCommand.GetBalanceEther)
            {
            }
            CommandFlag.Set(true);
        }

        public virtual void OnCommandCompleted(string name)
        {
            CommandCompleted_Event.Broadcast(EMCgBlockchainCommand.Get()[name]);
        }

        #region "Process"

            #region "I/O"

        public virtual void OnProcessOutputRecieved(object sender, DataReceivedEventArgs e)
        {
            if (LogIO.Log() || LogIOProcess.Log())
            {
                CgDebug.Log("Process (Output): " + e.Data);
            }
        }

        public virtual void OnProcessErrorRecieved(object sender, DataReceivedEventArgs e)
        {
            if (LogIO.Log() || LogIOProcess.Log())
            {
                CgDebug.Log("Process (Error): " + e.Data);
            }
        }

        public virtual void OnProcessExited(object sender, EventArgs e)
        {
            if (LogIO.Log() || LogIOProcess.Log())
            {
                CgDebug.Log("Blockchain (Process): Exited");
            }

            CgProcess p = Processes[ECgBlockchainProcessType.RunningInstance];

            Processes[ECgBlockchainProcessType.RunningInstance] = null;
            IsRunningInstanceOpen = false;
            IsRunningInstanceCloseFlag.Set(true);
            p.DeAllocate();
        }

        public virtual void OnConsoleOutputRecieved(object sender, DataReceivedEventArgs e)
        {
            string output = e.Data;

            if (LogIO.Log() || LogIOConsole.Log())
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
                    CgEthereumAccountInfo info = (CgEthereumAccountInfo)CurrentCommandInfo.Payload;

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
                float balance;

                if (float.TryParse(output, out balance))
                {
                    CurrentCommandOuput = balance;

                    CommandCompleted_Event.Broadcast(command);
                }
            }
            // DeployContract
            if (command == ECgEthereumCommand.DeployContract)
            {
                string mined = "Contract mined! address: ";

                if (output.StartsWith(mined))
                {
                    // Remove "Contract minded! address: 0x"
                    string right = output.Remove(0, mined.Length + 2);
                    // Get the first 40 characters for the address
                    string address = right.Substring(0, 40);

                    // Update Contract with the address
                    ECgBlockchainContract econtract = (ECgBlockchainContract)CurrentCommandInfo.Payload;

                    CgEthereumContract contract = (CgEthereumContract)Contracts[econtract];
                    contract.Address            = address;

                    CurrentCommandOuput = address;

                    CommandCompleted_Event.Broadcast(command);
                }
            }
            // RunContractConstantFunction
            if (command == ECgEthereumCommand.RunContractConstantFunction)
            {
                if (!output.StartsWith(">"))
                {
                    CurrentCommandOuput = output;

                    CommandCompleted_Event.Broadcast(command);
                }
            }
            // RunContractStateChangeFunction
            if (command == ECgEthereumCommand.RunContractStateChangeFunction)
            {
                if (!output.StartsWith(">"))
                {
                    CurrentCommandOuput = output;

                    CommandCompleted_Event.Broadcast(command);
                }
            }
            // GetGasEstimate
            if (command == ECgEthereumCommand.GetGasEstimate)
            {
                int estimate;

                if (int.TryParse(output, out estimate))
                {
                    CurrentCommandOuput = estimate;

                    CommandCompleted_Event.Broadcast(command);
                }
            }
        }

        public virtual void OnConsoleErrorRecieved(object sender, DataReceivedEventArgs e)
        {
            if (LogIO.Log() || LogIOConsole.Log())
            {
                CgDebug.Log("Console (Error): " + e.Data);
            }
        }

        public virtual void OnConsoleExited(object sender, EventArgs e)
        {
            if (LogIO.Log() || LogIOConsole.Log())
            {
                CgDebug.Log("Blockchain (Console): Exited");
            }

            Processes[ECgBlockchainProcessType.Console].DeAllocate();
            Processes[ECgBlockchainProcessType.Console] = null;
            IsConsoleOpen = false;
        }

            #endregion // I/O

        public override void SetProcess(ECgBlockchainProcessType processType, int index, CgProcess p)
        {
            // TODO: Later handle PrivateMultiNode
            Processes[processType] = p;
        }

        public override CgProcess GetProcess(ECgBlockchainProcessType processType, int index)
        {
            // TODO: Later handle PrivateMultiNode
            return Processes[processType];
        }

        public override void StartProcess(ECgBlockchainProcessType processType, int index, CgBlockchainProcessStartInfo startInfo)
        {
            CgProcess p = GetProcess(processType, index);

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

                if (LogProcessStart.Log())
                {
                    CgDebug.Log("CgEthereum.StartProcess: Starting Process (" + processType.ToString() + "): " + startInfo.FileName + " " + startInfo.Arguments);
                }

                p = ICgManager_Process.Get().Spawn(EMCgProcess.Get()["Blockchain"], payload);

                SetProcess(processType, index, p);
            }
            else
            {
                CgDebug.Log("CgEthereum.StartProcess: StartProcess called for running Process: " + processType.ToString() + " before the process exited.");
            }
        }

        public override void StopProcess(ECgBlockchainProcessType processType, int index)
        {
            // TODO: Later handle PrivateMultiNode
            if (Processes[processType] == null)
                return;
            Processes[processType].DeAllocate();
            Processes[processType] = null;
        }

        #endregion // Process

        public override void OpenRunningInstance()
        {
            if (IsRunningInstanceOpen)
                return;

            CommandFlag.Set(false);

            ECgBlockchainCommand command = ECgEthereumCommand.SetDataDirectory;

            CgBlockchainProcessStartInfo startInfo = new CgBlockchainProcessStartInfo();
            startInfo.FileName              = ConsoleFullPath;
            startInfo.Arguments             = Commands[command];
            startInfo.RedirectStandardInput = false;
            startInfo.AddMonitorOutputEvent(MonitorOutputEvents[command]);

            ECgBlockchainProcessType processType = ECgBlockchainProcessType.RunningInstance;

            //EnqueueCommand(processType, command);
            StartProcess(processType, 0, startInfo);
            
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

            CommandFlag.Set(false);

            // Init
            IsRunningInstanceOpen = true;
            IsRunningInstanceCloseFlag.Set(false);

            CgBlockchainProcessStartInfo startInfo = new CgBlockchainProcessStartInfo();
            startInfo.FileName              = ConsoleFullPath;
            startInfo.Arguments             = Commands[ECgEthereumCommand.InitBlockchain];
            startInfo.RedirectStandardInput = false;

            StartProcess(ECgBlockchainProcessType.RunningInstance, 0, startInfo);
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
                eth.OpenRunningInstance();
            }
            // Initialize then Start
            else
            {
                eth.CreatePrivateChain();

                yield return eth.IsRunningInstanceCloseFlag;

                eth. PrivateChainCreated_Event.Broadcast(SINGLE_NODE_INDEX);

                eth.OpenRunningInstance();
            }
            // Parse the Genesis file
            eth.Genesis.ParseFromFilePath(eth.GenesisFilePath);

            // Waittill DataDirectory has been set
            yield return eth.CommandFlag;

            eth.PrivateChainStarted_Event.Broadcast(SINGLE_NODE_INDEX);
        }

        public override void OpenConsole()
        {
            if (IsConsoleOpen)
                return;

            IsConsoleOpen = true;

            CommandFlag.Set(false);

            CgCoroutineScheduler.Get().Start(ECgCoroutineSchedule.Update, OpenConsole_Internal(this));
        }

        public static IEnumerator OpenConsole_Internal(CgEthereum eth)
        {
            ECgBlockchainCommand command = ECgEthereumCommand.AttachToConsole;

            CgBlockchainProcessStartInfo startInfo = new CgBlockchainProcessStartInfo();
            startInfo.FileName              = eth.ConsoleFullPath;
            startInfo.Arguments             = eth.Commands[command];
            startInfo.RedirectStandardInput = true;
            startInfo.AddMonitorOutputEvent(eth.MonitorOutputEvents[command]);

            ECgBlockchainProcessType processType = ECgBlockchainProcessType.Console;

            eth.StartProcess(processType, SINGLE_NODE_INDEX, startInfo);

            // Waittill Console has opened
            yield return eth.CommandFlag;

            eth.ConsoleOpened_Event.Broadcast(SINGLE_NODE_INDEX);
        }

        public override void CloseConsole()
        {
            // TODO: Later handle PrivateMultiNode
            if (!IsConsoleOpen)
                return;

            RunCommand(SINGLE_NODE_INDEX, ECgEthereumCommand.ExitConsole);

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
            CgEthereumAccountInfo info = (CgEthereumAccountInfo)payload;
            
            ICgBlockchainAccount iaccount;
            Accounts.TryGetValue(info.Nickname, out iaccount);

            if (iaccount != null)
            {
                CgDebug.LogWarning("CgEthereum.NewAccount: Account with Nickname: " + info.Nickname + " already exists.");
                return;
            }

            CommandFlag.Set(false);

            CgBlockchainCommandArgument[] args = new CgBlockchainCommandArgument[1];
            args[0]                            = new CgBlockchainCommandArgument(ECgBlockchainCommandArgumentType.StringString, info.Passphrase);

            CurrentCommandInfo.Set(ECgEthereumCommand.NewAccount, args, payload);

            RunCommand(SINGLE_NODE_INDEX, ECgEthereumCommand.NewAccount, args);
        }

        public void OnAccountCreated(ICgBlockchainAccount account)
        {
            if (LogAccountCreated.Log())
            {

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
            
            if (path == EMPTY_PATH)
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
            string keystoreFilePath = EMPTY_PATH;

            while (keystoreFilePath == EMPTY_PATH)
            {
                string[] paths = Directory.GetFiles(eth.KeystoreDirectory);

                foreach (string path in paths)
                {
                    if (path.Contains(account.Address))
                    {
                        keystoreFilePath = path;
                        break;
                    }

                    if (keystoreFilePath != EMPTY_PATH)
                        break;
                }

                if (keystoreFilePath == EMPTY_PATH)
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
                CgDebug.LogWarning("CgEthereum.UnlockAccount: Account with Nickname: " + nickname + " does NOT exist.");
                return;
            }

            CommandFlag.Set(false);

            CgEthereumAccount account = (CgEthereumAccount)iaccount;

            CgBlockchainCommandArgument[] args;
            account.CreateUnlockArguments(out args);

            CurrentCommandInfo.Set(ECgEthereumCommand.NewAccount, args, payload);

            AddMonitorOutputEvenToProcess(ECgBlockchainProcessType.Console, SINGLE_NODE_INDEX, ECgEthereumCommand.UnlockAccount);
            RunCommand(SINGLE_NODE_INDEX, ECgEthereumCommand.UnlockAccount, args);
        }

        public override void ListAccounts()
        {
            RunCommand(SINGLE_NODE_INDEX, ECgEthereumCommand.ListAccounts, null);
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

            AddMonitorOutputEvenToProcess(ECgBlockchainProcessType.Console, SINGLE_NODE_INDEX, ECgEthereumCommand.SetEtherbase);
            RunCommand(SINGLE_NODE_INDEX, ECgEthereumCommand.SetEtherbase, args);
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

            RunCommand(SINGLE_NODE_INDEX, ECgEthereumCommand.GetBalanceEther, args);
        }

        public void SetupAccount(object payload)
        {
            SetupAccountFlag.Set(false);
            CgCoroutineScheduler.Get().Start(ECgCoroutineSchedule.Update, SetupAccount_Internal(this, payload));
        }

        public static IEnumerator SetupAccount_Internal(CgEthereum eth, object payload)
        {
            CgEthereumAccountInfo info = (CgEthereumAccountInfo)payload;
            string nickname            = info.Nickname;

            // Check Account exists
            {
                ICgBlockchainAccount iaccount;

                if (!eth.Accounts.TryGetValue(nickname, out iaccount))
                {
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
                float balance = (float)eth.CurrentCommandOuput;
                float threshold = 20.0f;
                
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
                        balance = (float)eth.CurrentCommandOuput;

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

        #region Miner

        public override void StartMiner()
        {
            if (IsMining)
                return;

            CommandFlag.Set(false);

            CurrentCommandInfo.Set(ECgEthereumCommand.StartMiner, null, null);
            CurrentCommandOuput = null;

            AddMonitorOutputEvenToProcess(ECgBlockchainProcessType.Console, SINGLE_NODE_INDEX, ECgEthereumCommand.StartMiner);
            RunCommand(SINGLE_NODE_INDEX, ECgEthereumCommand.StartMiner, null);
            IsMining = true;
        }

        public override void StopMiner()
        {
            if (!IsMining)
                return;

            CommandFlag.Set(false);

            CurrentCommandInfo.Set(ECgEthereumCommand.StopMiner, null, null);
            CurrentCommandOuput = null;

            AddMonitorOutputEvenToProcess(ECgBlockchainProcessType.Console, SINGLE_NODE_INDEX, ECgEthereumCommand.StopMiner);
            RunCommand(SINGLE_NODE_INDEX, ECgEthereumCommand.StopMiner, null);

            IsMining = false;
        }

        #endregion // Miner

        #region Contract

        public void DeployContract(ECgBlockchainContract econtract, CgBlockchainContractArgument[] args = null)
        {
            DeployContractFlag.Set(false);
            CgCoroutineScheduler.Get().Start(ECgCoroutineSchedule.Update, DeployContract_Internal(this, econtract, args));
        }

        public static IEnumerator DeployContract_Internal(CgEthereum eth, ECgBlockchainContract econtract, CgBlockchainContractArgument[] args = null)
        {
            // Start Miner
            eth.StartMiner();
            yield return eth.CommandFlag;

            // Setup Contract with the correct arguments
            string snippet = eth.Web3DeployLinkedSnippets[econtract];

            if (args != null)
            {
                foreach (CgBlockchainContractArgument a in args)
                {
                    snippet = snippet.Replace(a.Name, a.ToStr());
                }
            }

            // Deploy Contract
            eth.CommandFlag.Set(false);
            eth.CurrentCommandInfo.Set(ECgEthereumCommand.DeployContract, null, econtract);
            eth.CurrentCommandOuput = null;
            eth.RunCommand(SINGLE_NODE_INDEX, snippet);

            // Waittill Contract has been mined
            yield return eth.CommandFlag;

            // Write out pertinent detail of Contract
            CgEthereumContract contract = (CgEthereumContract)eth.Contracts[econtract];

            File.WriteAllText(eth.ContractsDeployedDirectory + "\\" + contract.Address + "-" + econtract + ".txt", contract.ToStr(), System.Text.Encoding.ASCII);

            // Stop Miner
            eth.StopMiner();
            yield return eth.CommandFlag;

            eth.DeployContractFlag.Set(true);
        }

        public void LoadContract(ECgBlockchainContract econtract, ECgEthereumJavascript escript)
        {
            ICgBlockchainContract c = null;
            Contracts.TryGetValue(econtract, out c);

            if (c == null)
            {
                CgDebug.LogWarning("CgEthereum.LoadContract: Contract with name: " + econtract + " does NOT exist. Make sure a Contract was initialized with name: " + econtract + " in the constructor.");
                return;
            }

            CgEthereumContract contract = (CgEthereumContract)c;

            // Check if Contract file exists
            var filePaths = Directory.GetFiles(ContractsDeployedDirectory, "*.*", SearchOption.TopDirectoryOnly).Where(s => s.Contains(econtract + ".txt"));

            foreach (var path in filePaths)
            {
                contract.ParseFromFilePath(path);
                break;
            }

            // Check if Contract ABI file exists
            string abiPath = ABIDirectory + "\\" + econtract + ".txt";

            if (File.Exists(abiPath))
            {
                ABISnippets.Add(econtract, File.ReadAllText(abiPath));
            }
            else
            {
                CgDebug.LogWarning("CgEthereum.LoadContract: Failed to find ABI for Contract: " + econtract + " at: " + abiPath);
            }

            // If Contract is "new", setup Web3Deploy and Javascript file
            if (!contract.IsValid())
            {
                // Check if Contract Web3Deploy file exists
                string web3DeployPath = Web3DeployDirectory + "\\" + econtract + ".txt";

                if (File.Exists(web3DeployPath))
                {
                    Web3DeploySnippets.Add(econtract, File.ReadAllText(web3DeployPath));
                }
                else
                {
                    CgDebug.LogWarning("CgEthereum.LoadContract: Failed to find Web3Deploy for Contract: " + econtract + " at: " + web3DeployPath);
                }

                // Check if Contract Web3Deploy Linked (Libraries linked) file exists

                string web3DeployLinkedPath = Web3DeployLinkedDirectory + "\\" + econtract + ".txt";

                if (File.Exists(web3DeployLinkedPath))
                    Web3DeployLinkedSnippets.Add(econtract, File.ReadAllText(web3DeployLinkedPath));

                CreatedWeb3DeployLinked(econtract);
                CreatedJavascriptContractLinked(econtract, escript);
            }
            else
            {
                string web3DeployLinkedPath = Web3DeployLinkedDirectory + "\\" + econtract + ".txt";

                if (!File.Exists(web3DeployLinkedPath))
                {
                    CgDebug.LogWarning("CgEthereum.LoadContract: Failed to find Web3DeployLinkedPath for Contract: " + econtract + " at: " + web3DeployLinkedPath);
                }
                Web3DeployLinkedSnippets.Add(econtract, File.ReadAllText(web3DeployLinkedPath));
            }
        }

        public void CreatedWeb3DeployLinked(ECgBlockchainContract econtract)
        {
            string snippet = Web3DeploySnippets[econtract];

            // Update all Links with the appropriate addresses
            /*
            List<CgEthereumWeb3DeployLink> links = Web3DeployLinks[econtract];

            if (links != null)
            {
                foreach (CgEthereumWeb3DeployLink l in links)
                {
                    CgEthereumContract contract = (CgEthereumContract)Contracts[l.Contract];

                    snippet = snippet.Replace(l.Link, contract.Address);
                }
            }
            */
            // Change eth.accounts[0] to eth.coinbase
            snippet = snippet.Replace("eth.accounts[0]", "eth.coinbase");

            string path = Web3DeployLinkedDirectory + "\\" + econtract + ".txt";

            //snippet = snippet.Replace("\r", "");
            //snippet = snippet.Replace("\n", "");

            File.WriteAllText(path, snippet, System.Text.Encoding.ASCII);

            string str;

            if (!Web3DeployLinkedSnippets.TryGetValue(econtract, out str))
            {
                Web3DeployLinkedSnippets.Add(econtract, snippet);
            }
            else
            {
                Web3DeployLinkedSnippets[econtract] = snippet;
            }
        }

        public void CreatedJavascriptContractLinked(ECgBlockchainContract econtract, ECgEthereumJavascript escript)
        {
            string path = "";

            if (!ScriptPaths.TryGetValue(escript, out path))
            {
                CgDebug.LogWarning("CgEthereum.CreatedJavascriptContractLinked: No script path set for script: " + escript + ". Make sure a ScriptPath is set for: " + escript + " in the constructor.");
                return;
            }

            string script = File.ReadAllText(path);

            // Update all Links with the appropriate addresses
            List<CgEthereumJavascriptContractLink> links = ScriptContractLinks[econtract];

            if (links != null)
            {
                foreach (CgEthereumJavascriptContractLink l in links)
                {
                    CgEthereumContract contract = (CgEthereumContract)Contracts[l.Contract];

                    script = script.Replace(l.Link, contract.Address);
                }
            }

            File.WriteAllText(ScriptLinkedPaths[econtract], script, System.Text.Encoding.ASCII);
        }

        public void CreateContractABI(ECgBlockchainContract econtract)
        {
            CommandFlag.Set(false);

            // %s
            byte ARGUMENTS = 1;
            byte ABI = 0;

            CgBlockchainCommandArgument[] args  = new CgBlockchainCommandArgument[ARGUMENTS];
            args[ABI].Value                     = ABISnippets[econtract];
            args[ABI].ValueType                 = ECgBlockchainCommandArgumentType.String;

            CurrentCommandInfo.Set(ECgEthereumCommand.CreateContractABI, args, econtract);
            CurrentCommandOuput = null;

            AddMonitorOutputEvenToProcess(ECgBlockchainProcessType.Console, SINGLE_NODE_INDEX, ECgEthereumCommand.CreateContractABI);
            RunCommand(SINGLE_NODE_INDEX, ECgEthereumCommand.CreateContractABI, args);
        }

        public void CreateContractInstance(ECgBlockchainContract econtract, string address = "")
        {
            CommandFlag.Set(false);

            // var %s = %s.at(%s)
            byte ARGUMENTS = 3;
            byte INSTANCE = 0;
            byte ABI = 1;
            byte ADDRESS = 2;

            CgEthereumContract contract = (CgEthereumContract)Contracts[econtract];

            CgBlockchainCommandArgument[] args  = new CgBlockchainCommandArgument[ARGUMENTS];
            args[INSTANCE].Value                = contract.InstanceVariableName;
            args[INSTANCE].ValueType            = ECgBlockchainCommandArgumentType.String;
            args[ABI].Value                     = contract.ContractVariableName;
            args[ABI].ValueType                 = ECgBlockchainCommandArgumentType.String;
            args[ADDRESS].Value                 = address == "" ? contract.AddressAsArg() : address;
            args[ADDRESS].ValueType             = ECgBlockchainCommandArgumentType.String;

            CurrentCommandInfo.Set(ECgEthereumCommand.CreateContractInstance, args, econtract);
            CurrentCommandOuput = null;

            AddMonitorOutputEvenToProcess(ECgBlockchainProcessType.Console, SINGLE_NODE_INDEX, ECgEthereumCommand.CreateContractInstance);
            RunCommand(SINGLE_NODE_INDEX, ECgEthereumCommand.CreateContractInstance, args);
        }

        public void SetupContract(ECgBlockchainContract econtract, ECgEthereumJavascript escript)
        {
            SetupContractFlag.Set(false);
            CgCoroutineScheduler.Get().Start(ECgCoroutineSchedule.Update, SetupContract_Internal(this, econtract, escript));
        }

        public static IEnumerator SetupContract_Internal(CgEthereum eth, ECgBlockchainContract econtract, ECgEthereumJavascript escript)
        {
            eth.LoadContract(econtract, escript);
            eth.LoadScript(escript, eth.ScriptLinkedPaths[econtract]);
            yield return eth.CommandFlag;

            if (!eth.Contracts[econtract].IsValid())
            {
                eth.DeployContract(econtract);
                yield return eth.DeployContractFlag;
            }
            else
            {
                eth.CreateContractABI(econtract);
                yield return eth.CommandFlag;
                eth.CreateContractInstance(econtract);
                yield return eth.CommandFlag;
            }
            eth.SetupContractFlag.Set(true);
        }

        public void RunContractConstantFunction(ECgBlockchainContract econtract, ECgBlockchainContractFunction efn, CgBlockchainContractFunctionArgument[] args = null)
        {
            CommandFlag.Set(false);

            CgBlockchainContractFunction fn = ContractFunctions[econtract][efn];
            fn.Arguments = args;
            string command = fn.BuildConstantFunction();

            CurrentCommandInfo.Set(ECgEthereumCommand.RunContractConstantFunction, null, null);
            CurrentCommandOuput = null;

            if (LogIO.Log() || LogIOConsole.Log())
            {
                CgDebug.Log("CgEthereum.RunContractConstantFunction: Running command: " + ECgEthereumCommand.RunContractConstantFunction);
            }
            RunCommand(SINGLE_NODE_INDEX, command);
        }

        public void RunContractStateChangeFunction(ECgBlockchainContract econtract, string address, ECgBlockchainContractFunction efn, CgBlockchainContractFunctionArgument[] args = null)
        {
            RunContractStageChangeFunctionFlag.Set(false);
            CgCoroutineScheduler.Get().Start(ECgCoroutineSchedule.Update, RunContractStateChangeFunction_Internal(this, econtract, address, efn, args));
        }

        public static IEnumerator RunContractStateChangeFunction_Internal(CgEthereum eth, ECgBlockchainContract econtract, string address, ECgBlockchainContractFunction efn, CgBlockchainContractFunctionArgument[] args = null)
        {
            // GetGasEstimage
            eth.GetGasEstimate(econtract, address, efn, args);
            yield return eth.CommandFlag;

            int gas = (int)eth.CurrentCommandOuput;

            // Start Miner
            eth.StartMiner();
            yield return eth.CommandFlag;

            // Run State Change Function
            eth.CommandFlag.Set(false);

            CgBlockchainContractFunction fn = eth.ContractFunctions[econtract][efn];
            fn.Arguments                    = args;
            string command                  = fn.BuildStateChangeFunction(address, gas);

            eth.CurrentCommandInfo.Set(ECgEthereumCommand.RunContractStateChangeFunction, null, null);
            eth.CurrentCommandOuput = null;

            if (LogIO.Log() || LogIOConsole.Log())
            {
                CgDebug.Log("CgEthereum.RunContractStateChangeFunction_Internal: Running command: " + ECgEthereumCommand.RunContractStateChangeFunction);
            }
            eth.RunCommand(SINGLE_NODE_INDEX, command);

            yield return eth.CommandFlag;

            // Stop Miner
            eth.StopMiner();
            yield return eth.CommandFlag;

            eth.RunContractStageChangeFunctionFlag.Set(true);
        }

        public void GetGasEstimate(ECgBlockchainContract econtract, string address, ECgBlockchainContractFunction efn, CgBlockchainContractFunctionArgument[] args = null)
        {
            CommandFlag.Set(false);

            CgBlockchainContractFunction fn = ContractFunctions[econtract][efn];
            fn.Arguments                    = args;
            string command                  = fn.BuildEstimateFunction(address);

            CurrentCommandInfo.Set(ECgEthereumCommand.GetGasEstimate, null, null);
            CurrentCommandOuput = null;

            if (LogIO.Log() || LogIOConsole.Log())
            {
                CgDebug.Log("CgEthereum.GetGasEstimate: Running command: " + ECgEthereumCommand.GetGasEstimate);
            }
            RunCommand(SINGLE_NODE_INDEX, command);
        }

        #endregion // Contract

        public virtual void LoadScript(ECgEthereumJavascript escript, string path)
        {
            CommandFlag.Set(false);

            // loadScript(% s)
            byte ARGUMENTS = 1;
            byte PATH = 0;

            CgBlockchainCommandArgument[] args  = new CgBlockchainCommandArgument[ARGUMENTS];
            args[PATH].Value                    = "'" + path + "'";
            args[PATH].ValueType                = ECgBlockchainCommandArgumentType.String;

            CurrentCommandInfo.Set(ECgEthereumCommand.LoadScript, args, escript);
            CurrentCommandOuput = null;

            AddMonitorOutputEvenToProcess(ECgBlockchainProcessType.Console, SINGLE_NODE_INDEX, ECgEthereumCommand.LoadScript);
            RunCommand(SINGLE_NODE_INDEX, ECgEthereumCommand.LoadScript, args);
        }
    }
}

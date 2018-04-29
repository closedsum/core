namespace CgCore
{
    using System;
    using System.Collections;
    using System.Collections.Generic;
    using System.Diagnostics;
    using System.IO;
    using UnityEngine;

    public static class ECgEthereumCommand
    {
        public static readonly ECgBlockchainCommand InitBlockchain = new ECgBlockchainCommand(0, "InitBlockchain");
        public static readonly ECgBlockchainCommand SetDataDirectory = new ECgBlockchainCommand(1, "SetDataDirectory");
        public static readonly ECgBlockchainCommand ChangeToRootDirectory = new ECgBlockchainCommand(2, "ChangeToRootDirectory");
        public static readonly ECgBlockchainCommand AttachToConsole = new ECgBlockchainCommand(3, "AttachToConsole");
        public static readonly ECgBlockchainCommand ExitConsole = new ECgBlockchainCommand(4, "ExitConsole");
        public static readonly ECgBlockchainCommand NewAccount = new ECgBlockchainCommand(5, "NewAccount");
        public static readonly ECgBlockchainCommand UnlockAccount = new ECgBlockchainCommand(6, "UnlockAccount");
    }

    public class CgEthereum : CgBlockchain
    {
        #region "Data Members"

        private static CgEthereum instance;
        public static CgEthereum Instance
        {
            get
            {
                if (instance == null)
                {
                    instance = new CgEthereum();
                }
                return instance;
            }
        }

        public string ConsoleFullPath;

        #endregion // Data Members

        public CgEthereum()
        {
            Init();
        }

        protected override void Init()
        {
            Get = _Get;

            Genesis = (ICgBlockchainGenesis)(new CgEthereumGenesis());

            StorageType = ECgBlockchainStorageType.Private;
            
            // TODO: Need to check platform
            ShellFilename = "cmd.exe";
            // Run Command and then return to the CMD prompt.
            ShellArguments  = "/K";
            ConsoleFilename = "geth.exe";
            ConsoleDirectory = Application.dataPath + "\\Blockchain\\Ethereum\\Geth";
            ConsoleFullPath = ConsoleDirectory + "\\" + ConsoleFilename;
            RootDirectory   = Application.dataPath + "\\Blockchain\\Ethereum";
            ChainDirectory  = Application.dataPath + "\\Blockchain\\Ethereum\\chaindata";

            Commands = new Dictionary<ECgBlockchainCommand, string>(new ECgBlockchainCommandEqualityComparer());
            Accounts = new Dictionary<string, ICgBlockchainAccount>();

            SetCommand(ECgEthereumCommand.InitBlockchain, "\"" + ConsoleFullPath + "\" --datadir=\"" + ChainDirectory + "\" init \"" + RootDirectory + "\\genesis.json\"");
            SetCommand(ECgEthereumCommand.SetDataDirectory, "\"" + ConsoleFullPath + "\" --datadir=\"" + ChainDirectory + "\"");
            SetCommand(ECgEthereumCommand.ChangeToRootDirectory, "cd /d \"" + RootDirectory + "\"");
            SetCommand(ECgEthereumCommand.AttachToConsole, "\"" + ConsoleFullPath + "\" attach ipc:\\\\.\\pipe\\geth.ipc");
            SetCommand(ECgEthereumCommand.ExitConsole, "exit");
            SetCommand(ECgEthereumCommand.NewAccount, "personal.newAccount(%s)");
            SetCommand(ECgEthereumCommand.UnlockAccount, "personal.unlockAccount(%s,%s,%s)");
        }

        private CgBlockchain _Get()
        {
            return Instance;
        }

        public void Log(string msg)
        {
            UnityEngine.Debug.Log(msg);
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
            // RunningInstance
            if (processType == ECgBlockchainProcessType.RunningInstance)
            {
                if (RunningInstance == null)
                    OpenRunningInstance();
            }
            // Console
            if (processType == ECgBlockchainProcessType.Console)
            {
                if (!IsConsoleOpen)
                    OpenConsole();
            }

            if (LogIO.Log())
            {
                UnityEngine.Debug.Log("Blockchain (Input): " + command);
            }

            Process p = GetProcess(processType);

            // Convert string command to bytes
            byte[] buffer = System.Text.Encoding.ASCII.GetBytes(command);
            p.StandardInput.BaseStream.Write(buffer, 0, buffer.Length);
            // Add new line
            buffer = System.Text.Encoding.ASCII.GetBytes("\n");
            p.StandardInput.BaseStream.Write(buffer, 0, buffer.Length);
            // Flush command to be processed
            p.StandardInput.BaseStream.Flush();
        }

        public override void RunCommand(ECgBlockchainProcessType processType, ECgBlockchainCommand command, CgBlockchainCommandArgument[] args = null)
        {
            string value;
            Commands.TryGetValue(command, out value);

            if (value == INVALID_COMMAND)
            {
                UnityEngine.Debug.LogWarning("CgEthereum.RunCommand: No command set for " + command.Name);
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
                if (parts.Count == args.Length)
                {
                    value = "";

                    int argumentLength = args.Length;

                    for (int i = 0; i < argumentLength; ++i)
                    {
                        value += parts[i] + args[i].ToStr();
                    }
                }
                else
                {
                    UnityEngine.Debug.Log("CgEthereum.RunCommand: Failed to run command: " + command.Name + ". Wildcard count != Argument count (" + parts.Count + "," + args.Length + ")");
                }
            }
            RunCommand(processType, value);
        }

        public override Process GetProcess(ECgBlockchainProcessType processType)
        {
            if (processType == ECgBlockchainProcessType.RunningInstance)
                return RunningInstance;
            if (processType == ECgBlockchainProcessType.Console)
                return Shell;
            return null;
        }

        public override void StartProcess(ECgBlockchainProcessType processType)
        {
            if (processType == ECgBlockchainProcessType.RunningInstance &&
                RunningInstance != null)
            {
                return;
            }
            if (processType == ECgBlockchainProcessType.Console &&
                Shell != null)
            {
                return;
            }

            Process p = new Process();

            if (processType == ECgBlockchainProcessType.RunningInstance)
            {
                RunningInstance = p;
                IsRunningInstance = true;
            }
            if (processType == ECgBlockchainProcessType.Console)
            {
                Shell = p;
                IsShellOpen = true;
            }

            // ProcessStartInfo
            ProcessStartInfo psi    = p.StartInfo;
            psi.CreateNoWindow      = ShowShellWindow.Get();
            psi.UseShellExecute     = false;
            psi.FileName            = ShellFilename;
            psi.Arguments           = ShellArguments;
            psi.RedirectStandardInput = true;
            psi.RedirectStandardOutput = true;
            p.OutputDataReceived    += ShellOutputRecieved;

            p.Start();
            p.BeginOutputReadLine();

            RunCommand(processType, ECgEthereumCommand.ChangeToRootDirectory);
        }

        public override void OpenRunningInstance()
        {
            StartProcess(ECgBlockchainProcessType.RunningInstance);
        }

        public override void CreatePrivateChain()
        {
            if (RunningInstance == null)
                OpenRunningInstance();

            // Check if Blockchain directory exists
            if (!Directory.Exists(Application.dataPath + "\\Blockchain"))
            {
                Directory.CreateDirectory(Application.dataPath + "\\Blockchain");
            }
            // Check if Ethereum director exists
            if (!Directory.Exists(RootDirectory))
            {
                Directory.CreateDirectory(RootDirectory);
            }
            // Check if genesis.json has been created
            bool GenesisExists = File.Exists(RootDirectory + "/genesis.json");

            // Link chaindata
            if (GenesisExists)
                RunCommand(ECgBlockchainProcessType.RunningInstance, ECgEthereumCommand.SetDataDirectory);
            else
                RunCommand(ECgBlockchainProcessType.RunningInstance, ECgEthereumCommand.InitBlockchain);
        }

        public override void StartPrivateChain()
        {
            CreatePrivateChain();
            //Genesis.Parse(ChainDirectory + "/genesis.json");
        }

        public override void OpenShell()
        {
            StartProcess(ECgBlockchainProcessType.Console); ;
        }

        static public void ShellOutputRecieved(object sender, DataReceivedEventArgs e)
        {
            if (LogIO.Log())
            {
                UnityEngine.Debug.Log("Blockchain (Output): " + e.Data);
            }
        }

        public override void CloseShell()
        {
            if (Shell == null)
                return;

            if (IsMining)
                StopMiner();
            if (IsConsoleOpen)
                CloseConsole();

            Shell.Kill();

            IsShellOpen = false;
        }

        public override void OpenConsole()
        {
            if (IsConsoleOpen)
                return;
            if (Shell == null)
                OpenShell();

            RunCommand(ECgBlockchainProcessType.RunningInstance, ECgEthereumCommand.AttachToConsole);

            IsConsoleOpen = true;
        }

        public override void CloseConsole()
        {
            if (!IsConsoleOpen)
                return;

            RunCommand(ECgBlockchainProcessType.RunningInstance, ECgEthereumCommand.ExitConsole);
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
            // TODO: Need to fill in account details in ShellOutputRecieved
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

        public override void StartMiner()
        {
            if (IsMining)
                return;
            if (!IsConsoleOpen)
                OpenConsole();

            //RunCommand("miner.start();");
            IsMining = true;
        }

        public override void StopMiner()
        {
            if (!IsMining)
                return;

            //RunCommand("miner.stop();");

            IsMining = false;
        }
    }
}

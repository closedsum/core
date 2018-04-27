namespace CgCore
{
    using System.Diagnostics;
    using System.IO;
    using UnityEngine;

    public static class ECgEthereumCommand
    {
        /*
        public static readonly ECgInputAction MoveForward = new ECgInputAction(0, "MoveForward");
        public static readonly ECgInputAction MoveBackward = new ECgInputAction(1, "MoveBackward");
        public static readonly ECgInputAction MoveRight = new ECgInputAction(2, "MoveRight");
        public static readonly ECgInputAction MoveLeft = new ECgInputAction(3, "MoveLeft");
        public static readonly ECgInputAction MAX = new ECgInputAction(4, "MAX");
        */
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

        public override void Init()
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
            ConsoleFullPath = ConsoleDirectory + "\\" + ConsoleFullPath;
            RootDirectory   = Application.dataPath + "\\Blockchain\\Ethereum";
            ChainDirectory  = Application.dataPath + "\\Blockchain\\Ethereum\\chaindata";
        }

        private CgBlockchain _Get()
        {
            return Instance;
        }

        public void Log(string msg)
        {
            UnityEngine.Debug.Log(msg);
        }

        public override void StartProcess(ECgBlockchainProcessType ProcessType)
        {
            if (ProcessType == ECgBlockchainProcessType.RunningInstance &&
                RunningInstance != null)
            {
                return;
            }
            if (ProcessType == ECgBlockchainProcessType.Console &&
                Shell != null)
            {
                return;
            }

            Process p = new Process();
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

            IsShellOpen = true;

            p.BeginOutputReadLine();

            RunCommand("cd /d " + RootDirectory);

            if (ProcessType == ECgBlockchainProcessType.RunningInstance)
                RunningInstance = p;
            if (ProcessType == ECgBlockchainProcessType.Console)
                Shell = p;
        }

        public override void CreatePrivateChain()
        {
            // Check if Blockchain directory exists
            if (!Directory.Exists(Application.dataPath + "\\Blockchain"))
            {
                Directory.CreateDirectory(Application.dataPath + "\\Blockchain");
            }
            // Check if Ethereum director exists
            if (!Directory.Exists(Application.dataPath + "\\Blockchain\\Ethereum"))
            {
                Directory.CreateDirectory(Application.dataPath + "\\Blockchain\\Ethereum");
            }
            // Check if genesis.json has been created
            bool GenesisExists = false;

            if (Directory.Exists(ChainDirectory))
            {
                string[] files = Directory.GetFiles(ChainDirectory, "genesis*");
                GenesisExists = files.Length > EMPTY;
            }
            // Link chaindata
           // if (GenesisExists)
            //    ProcessCommand(ConsoleDirectory + " --datadir=" + ChainDirectory);
           // else
            {
                UnityEngine.Debug.Log(ConsoleDirectory + "\\" + ConsoleFilename + " --datadir=" + ChainDirectory + " init " + RootDirectory + "\\genesis.json");
               // ProcessCommand(ConsoleDirectory + " --datadir=" + ChainDirectory + " init " + ChainDirectory + "\\genesis.json");
            }
        }

        public override void StartPrivateChain()
        {
            StartProcess(ECgBlockchainProcessType.RunningInstance);
            //CreatePrivateChain();
            //Genesis.Parse(ChainDirectory + "/genesis.json");
        }

        public override void OpenShell()
        {
            if (Shell != null)
                return;

            Shell = new Process();

            ProcessStartInfo psi        = Shell.StartInfo;
            psi.CreateNoWindow          = ShowShellWindow.Get();
            psi.UseShellExecute         = false;
            psi.FileName                = ShellFilename;
            psi.Arguments               = ShellArguments;
            psi.RedirectStandardInput   = true;
            psi.RedirectStandardOutput  = true;
            Shell.OutputDataReceived   += ShellOutputRecieved;
            Shell.Start();

            IsShellOpen = true;

            Shell.BeginOutputReadLine();

            RunCommand("cd /d " + RootDirectory);
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

        /* Opens the console for the Blockchain program.
         * From the console the user may execute any console commands.
        */
        public override void OpenConsole()
        {
            if (IsConsoleOpen)
                return;
            if (Shell == null)
                OpenShell();

            RunCommand(ConsoleFullPath + " attach ipc:\\\\.\\pipe\\geth.ipc");

            IsConsoleOpen = true;
        }


        public override void CloseConsole()
        {
            if (!IsConsoleOpen)
                return;

            RunCommand("exit");
        }

        public override void RunCommand(string command)
        {
            if (!IsConsoleOpen)
                OpenConsole();

            if (LogIO.Log())
            {
                UnityEngine.Debug.Log("Blockchain (Input): " + command);
            }

            // Convert string command to bytes
            byte[] buffer = System.Text.Encoding.ASCII.GetBytes(command);
            Shell.StandardInput.BaseStream.Write(buffer, 0, buffer.Length);
            // Add new line
            buffer = System.Text.Encoding.ASCII.GetBytes("\n");
            Shell.StandardInput.BaseStream.Write(buffer, 0, buffer.Length);
            // Flush command to be processed
            Shell.StandardInput.BaseStream.Flush();
        }
         
        public override void StartMiner()
        {
            if (IsMining)
                return;
            if (!IsConsoleOpen)
                OpenConsole();

            RunCommand("miner.start();");
            IsMining = true;
        }

        public override void StopMiner()
        {
            if (!IsMining)
                return;

            RunCommand("miner.stop();");

            IsMining = false;
        }
    }
}

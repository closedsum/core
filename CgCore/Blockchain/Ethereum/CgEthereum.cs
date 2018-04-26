namespace CgCore
{
    using System.Diagnostics;
    using System.IO;
    using UnityEngine;

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

        public override void OpenShell()
        {
            if (Shell != null)
                return;

            Shell = new Process();
            ProcessStartInfo psi = Shell.StartInfo;

            psi.CreateNoWindow = ShowShellWindow.Get();
            psi.UseShellExecute = false;
            psi.FileName = ShellFilename;
            psi.Arguments = ShellArguments;
            psi.RedirectStandardInput = true;
            psi.RedirectStandardOutput = true;
            Shell.OutputDataReceived += ShellOutputRecieved;
            Shell.Start();

            IsShellOpen = true;

            Shell.BeginOutputReadLine();

            ProcessCommand("cd /d " + RootDirectory);
        }

        static public void ShellOutputRecieved(object sender, DataReceivedEventArgs e)
        {
            if (LogIO.Log())
            {
                UnityEngine.Debug.Log("Blockchain(Output): " + e.Data);
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

            ProcessCommand(ConsoleFullPath + " attach ipc:\\\\.\\pipe\\geth.ipc");

            IsConsoleOpen = true;
        }


        public override void CloseConsole()
        {
            if (!IsConsoleOpen)
                return;

            ProcessCommand("exit");
        }

        public override void ProcessCommand(string command)
        {
            if (!IsConsoleOpen)
                OpenConsole();

            // Convert string command to bytes
            byte[] buffer = System.Text.Encoding.ASCII.GetBytes(command);
            Shell.StandardInput.BaseStream.Write(buffer, 0, buffer.Length);
            // Add new line
            buffer = System.Text.Encoding.ASCII.GetBytes("\n");
            Shell.StandardInput.BaseStream.Write(buffer, 0, buffer.Length);
            // Flush command to be processed
            Shell.StandardInput.BaseStream.Flush();
        }

        public override void CreatePrivateChain()
        {
            // Check if genesis.json has been created
            bool GenesisExists  = false;
            string[] files      = Directory.GetFiles(ChainDirectory, "genesis*");
            GenesisExists       = files.Length > EMPTY;
            // Link chain
            if (GenesisExists)
                ProcessCommand(ConsoleDirectory + " --datadir=" + ChainDirectory);
            else
                ProcessCommand(ConsoleDirectory + " --datadir=" + ChainDirectory + " init " + ChainDirectory + "\\genesis.json");
        }
         
        public override void StartMiner()
        {
            if (IsMining)
                return;
            if (!IsConsoleOpen)
                OpenConsole();

            ProcessCommand("miner.start();");
            IsMining = true;
        }

        public override void StopMiner()
        {
            if (!IsMining)
                return;

            ProcessCommand("miner.stop();");

            IsMining = false;
        }
    }
}

namespace CgCore
{
    using System.Diagnostics;
    using System.Collections;
    using System.Collections.Generic;

    public enum ECgBlockchainStorageType
    {
        Private,
        Local,
        Server,
        MAX
    }

    public interface ICgBlockchain
    {
        #region "Data Members"

        ECgBlockchainStorageType StorageType { get; set; }

            #region "Private / Local Storage"

        string RootDirectory { get; set; }
        string ChainDirectory { get; set; }
        string ShellFilename { get; set; }
        string ShellArguments { get; set; }
        string ConsoleFilename { get; set; }
        string ConsoleDirectory { get; set; }
        bool IsShellOpen { get; set; }
        bool IsConsoleOpen { get; set; }
        bool IsMining { get; set; }

        Process Shell { get; set; }

            #endregion // Private / Local Storage

        Dictionary<CgBlockchainContractKey, ICgBlockchainContract> Contracts { get; set; }

        #endregion // Data Members

        void Init();

        /* Opens the shell from which to start any Blockchain program */
        void OpenShell();
        void CloseShell();
        /* Opens the console for the Blockchain program.
         * From the console the user may execute any console commands.
        */
        void OpenConsole();
        void CloseConsole();
        void ProcessCommand(string command);

        /* Starts a miner */
        void StartMiner();
        /* Stops a miner */
        void StopMiner();
    }

    public abstract class CgBlockchain : ICgBlockchain
    {
        public static CgConsoleVariableLog LogIO = new CgConsoleVariableLog("log.blockchain.io", false, "Log Blockchain Input / Output Messages", (int)ECgConsoleVariableFlag.Console);
        public static TCgConsoleVariable<bool> ShowShellWindow = new CgConsoleVariableLog("show.blockchain.shellwindow", false, "Show Blockchain Shell Window", (int)ECgConsoleVariableFlag.Console);

        public delegate CgBlockchain Getter();

        #region "Constants"

        protected static readonly int EMPTY = 0;

        #endregion // Constants

        #region "Data Members"

        #region "Interface"

        private ECgBlockchainStorageType _StorageType;
        public ECgBlockchainStorageType StorageType
        {
            get { return _StorageType; }
            set { _StorageType = value; }
        }

        private string _RootDirectory;
        public string RootDirectory
        {
            get { return _RootDirectory; }
            set { _RootDirectory = value; }
        }

        private string _ChainDirectory;
        public string ChainDirectory
        {
            get { return _ChainDirectory; }
            set { _ChainDirectory = value; }
        }

        private string _ShellFilename;
        public string ShellFilename
        {
            get { return _ShellFilename; }
            set { _ShellFilename = value; }
        }

        private string _ShellArguments;
        public string ShellArguments
        {
            get { return _ShellArguments; }
            set { _ShellArguments = value; }
        }

        private string _ConsoleFilename;
        public string ConsoleFilename
        {
            get { return _ConsoleFilename; }
            set { _ConsoleFilename = value; }
        }

        private string _ConsoleDirectory;
        public string ConsoleDirectory
        {
            get { return _ConsoleDirectory; }
            set { _ConsoleDirectory = value; }
        }

        private bool _IsShellOpen;
        public bool IsShellOpen
        {
            get { return _IsShellOpen; }
            set { _IsShellOpen = value; }
        }

        private bool _IsConsoleOpen;
        public bool IsConsoleOpen
        {
            get { return _IsConsoleOpen; }
            set { _IsConsoleOpen = value; }
        }

        private bool _IsMining;
        public bool IsMining
        {
            get { return _IsMining; }
            set { _IsMining = value; }
        }

        private Process _Shell;
        public Process Shell
        {
            get { return _Shell; }
            set { _Shell = value; }
        }

        private Dictionary<CgBlockchainContractKey, ICgBlockchainContract> _Contracts;
        public Dictionary<CgBlockchainContractKey, ICgBlockchainContract> Contracts
        {
            get { return _Contracts; }
            set { Contracts = _Contracts; }
        }

        #endregion // Interface

        public Getter Get;

        #endregion // Data Members

        public abstract void Init();
        public abstract void OpenShell();
        public abstract void CloseShell();
        public abstract void OpenConsole();
        public abstract void CloseConsole();
        public abstract void ProcessCommand(string command);
        public abstract void CreatePrivateChain();
        public abstract void StartMiner();
        public abstract void StopMiner();
    }

}
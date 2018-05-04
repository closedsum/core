﻿namespace CgCore
{
    using System;
    using System.Collections.Generic;
    using System.Diagnostics;
    using System.Reflection;

    public enum ECgBlockchainStorageType : byte
    {
        Private,
        Local,
        Server,
        MAX
    }

    public enum ECgBlockchainProcessType : byte
    {
        RunningInstance,
        Console,
        MAX
    }

    public sealed class ECgBlockchainProcessTypeEqualityComparer : IEqualityComparer<ECgBlockchainProcessType>
    {
        public bool Equals(ECgBlockchainProcessType lhs, ECgBlockchainProcessType rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(ECgBlockchainProcessType x)
        {
            return x.GetHashCode();
        }
    }

    public class CgBlockchainProcessStartInfo
    {
        public string FileName;
        public string Arguments;
        public bool RedirectStandardInput;
        public List<CgProcessMonitorOutputEvent> MonitorOutputEvents;

        public CgBlockchainProcessStartInfo()
        {
            FileName = "";
            Arguments = "";
            RedirectStandardInput = false;
            MonitorOutputEvents = new List<CgProcessMonitorOutputEvent>();
        }

        public void AddMonitorOutputEvent(CgProcessMonitorOutputEvent e)
        {
            MonitorOutputEvents.Add(e);
        }
    }

    public sealed class ECgBlockchainCommand : ECgEnum_byte
    {
        public ECgBlockchainCommand(byte value, string name) : base(value, name) { }
    }

    public sealed class ECgBlockchainCommandEqualityComparer : IEqualityComparer<ECgBlockchainCommand>
    {
        public bool Equals(ECgBlockchainCommand lhs, ECgBlockchainCommand rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(ECgBlockchainCommand x)
        {
            return x.GetHashCode();
        }
    }

    public class EMCgBlockchainCommand : ECgEnumMap<ECgBlockchainCommand, byte>
    {
        private static EMCgBlockchainCommand _Instance;
        public static EMCgBlockchainCommand Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new EMCgBlockchainCommand();
                }
                return _Instance;
            }
        }

        public static EMCgBlockchainCommand Get()
        {
            return Instance;
        }
    }

    public enum ECgBlockchainCommandArgumentType : byte
    {
        Number,
        String,
        StringString,
        MAX
    }

    public struct CgBlockchainCommandArgument
    {
        public ECgBlockchainCommandArgumentType ValueType;
        public object Value;

        public CgBlockchainCommandArgument(ECgBlockchainCommandArgumentType valueType, object value)
        {
            ValueType = valueType;
            Value     = value;
        }

        public string ToStr()
        {
            // Number
            if (ValueType == ECgBlockchainCommandArgumentType.Number)
                return CgCommon.NumericTypeToString(Value);
            // String
            if (ValueType == ECgBlockchainCommandArgumentType.String)
                return (string)Value;
            // StringString
            if (ValueType == ECgBlockchainCommandArgumentType.StringString)
                return "\"" + (string)Value + "\"";
            return "";
        }
    }

    public struct CgBlockchainCommandInfo
    {
        public ECgBlockchainCommand Command;
        public CgBlockchainCommandArgument[] Arguments;
        public object Payload;

        public CgBlockchainCommandInfo(ECgBlockchainCommand command, CgBlockchainCommandArgument[] args = null, object payload = null)
        {
            Command   = command;
            Arguments = args;
            Payload = payload;
        }

        public void Set(ECgBlockchainCommand command, CgBlockchainCommandArgument[] args = null, object payload = null)
        {
            Command = command;
            Arguments = args;
            Payload = payload;
        }
    }

    public static class ICgBlockchainInterface
    {
        public static void Init(Type type)
        {
            if (Get() != null)
                return;

            CgBlockchain.Init(type);
        }

        public static ICgBlockchain Get()
        {
            if (CgBlockchain.Get() != null)
                return CgBlockchain.Get();
            return null;
        }

        public static T Get<T>() where T : ICgBlockchain
        {
            return (T)Get();
        }
    }

    public interface ICgBlockchain
    {
        #region "Data Members"

        ECgBlockchainStorageType StorageType { get; set; }

            #region "Private / Local Storage"

        string RootDirectory { get; set; }
        string ChainDirectory { get; set; }
        string AccountsDirectory { get; set; }

        Dictionary<ECgBlockchainProcessType, CgProcess> Processes { get; set; }

                #region "Running Instance"

        bool IsRunningInstanceOpen { get; set; }

                #endregion // Running Instance

                #region "Console"

        string ConsoleFilename { get; set; }
        string ConsoleDirectory { get; set; }

        bool IsConsoleOpen { get; set; }
        bool IsMining { get; set; }

                #endregion // Console

            #endregion // Private / Local Storage

        ICgBlockchainGenesis Genesis { get; set; }
        Dictionary<CgBlockchainContractKey, ICgBlockchainContract> Contracts { get; set; }
        Dictionary<ECgBlockchainCommand, string> Commands { get; set; }

        Dictionary<string, ICgBlockchainAccount> Accounts { get; set; }

        #endregion // Data Members

        void Shutdown();

        void SetCommand(ECgBlockchainCommand command, string str);
        void RunCommand(ECgBlockchainProcessType processType, string command);
        void RunCommand(ECgBlockchainProcessType processType, ECgBlockchainCommand command, CgBlockchainCommandArgument[] args = null);

        void SetProcess(ECgBlockchainProcessType processType, CgProcess p);
        CgProcess GetProcess(ECgBlockchainProcessType processType);
        void StartProcess(ECgBlockchainProcessType processType, CgBlockchainProcessStartInfo startInfo);
        void StopProcess(ECgBlockchainProcessType processType);

        void OpenRunningInstance();
        /* Setup chaindata and genesis.json for private chain */
        void CreatePrivateChain();
        /* Start running / polling the current private chain */
        void StartPrivateChain();

        /* Opens the console for the Blockchain program.
         * From the console the user may execute any console commands.
        */
        void OpenConsole();
        void CloseConsole();

        #region "Account"

        void LoadAccounts();
        void NewAccount(object payload);
        void UnlockAccount(object payload);

        #endregion // Account

        /* Starts a miner */
        void StartMiner();
        /* Stops a miner */
        void StopMiner();
    }

    public abstract class CgBlockchain : ICgBlockchain
    {
        #region "CVars"

        public static CgConsoleVariableLog LogIO = new CgConsoleVariableLog("log.blockchain.io", false, "Log Blockchain Input / Output Messages", (int)ECgConsoleVariableFlag.Console);
        public static TCgConsoleVariable<bool> ShowProcessWindow = new TCgConsoleVariable<bool>("show.blockchain.processwindow", false, "Show Blockchain Process Window", (int)ECgConsoleVariableFlag.Console);
        public static CgConsoleVariableLog LogOnBoard = new CgConsoleVariableLog("log.blockchain.onboard", false, "Log Blockchain OnBoard Process", (int)ECgConsoleVariableFlag.Console);
        // Command
        public static CgConsoleVariableLog LogCommandCompleted = new CgConsoleVariableLog("log.blockchain.command.completed", false, "Log Blockchain Command Completed", (int)ECgConsoleVariableFlag.Console);
        // Account
        public static CgConsoleVariableLog LogAccountCreated = new CgConsoleVariableLog("log.blockchain.account.created", false, "Log Blockchain Account Created", (int)ECgConsoleVariableFlag.Console);

        public class CommandCompleted : TCgMulticastDelegate_OneParam<ECgBlockchainCommand> { }
        public class AccountCreated : TCgMulticastDelegate_OneParam<ICgBlockchainAccount>{ }

        #endregion // CVars

        #region "Constants"

        protected static readonly int EMPTY = 0;
        protected static readonly string INVALID_COMMAND = "";

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

        private string _AccountsDirectory;
        public string AccountsDirectory
        {
            get { return _AccountsDirectory; }
            set { _AccountsDirectory = value; }
        }

        private Dictionary<ECgBlockchainProcessType, CgProcess> _Processes;
        public Dictionary<ECgBlockchainProcessType, CgProcess> Processes
        {
            get { return _Processes; }
            set { _Processes = value; }
        }

                #region "Running Instance"

        private bool _IsRunningInstanceOpen;
        public bool IsRunningInstanceOpen
        {
            get { return _IsRunningInstanceOpen; }
            set { _IsRunningInstanceOpen = value; }
        }

                #endregion // Running Instance

                #region "Console"

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

                #endregion // Console

        private ICgBlockchainGenesis _Genesis;
        public ICgBlockchainGenesis Genesis
        {
            get { return _Genesis; }
            set { _Genesis = value; }
        }

        private Dictionary<CgBlockchainContractKey, ICgBlockchainContract> _Contracts;
        public Dictionary<CgBlockchainContractKey, ICgBlockchainContract> Contracts
        {
            get { return _Contracts; }
            set { _Contracts = value; }
        }

        private Dictionary<ECgBlockchainCommand, string> _Commands;
        public Dictionary<ECgBlockchainCommand, string> Commands
        {
            get { return _Commands; }
            set { _Commands = value; }
        }

        private Dictionary<string, ICgBlockchainAccount> _Accounts;
        public Dictionary<string, ICgBlockchainAccount> Accounts
        {
            get { return _Accounts; }
            set { _Accounts = value; }
        }

            #endregion // Interface

        private static ICgBlockchain _Instance;

        public CommandCompleted CommandCompleted_Event;
        public AccountCreated AccountCreated_Event;

        #endregion // Data Members

        public CgBlockchain()
        {
            Processes = new Dictionary<ECgBlockchainProcessType, CgProcess>(new ECgBlockchainProcessTypeEqualityComparer());

            for (byte i = 0; i < (byte)ECgBlockchainProcessType.MAX; ++i)
            {
                Processes.Add((ECgBlockchainProcessType)i, null);
            }

            Commands = new Dictionary<ECgBlockchainCommand, string>(new ECgBlockchainCommandEqualityComparer());
            
            Accounts = new Dictionary<string, ICgBlockchainAccount>();

            CommandCompleted_Event = new CommandCompleted();
            AccountCreated_Event = new AccountCreated();
        }

        public static ICgBlockchain Get()
        {
            return _Instance;
        }

        public static T Get<T>() where T : ICgBlockchain
        {
            return (T)_Instance;
        }

        public static void Init(Type type)
        {
            if (_Instance != null)
                return;

            if (!type.IsSubclassOf(typeof(CgBlockchain)))
            {
                CgDebug.Log("CgBlockchain.Init: Passed in Type of " + type.GetType().Name + " is NOT a SubclassOf CgBlockchain");
                return;
            }
            ConstructorInfo constructor = type.GetConstructor(Type.EmptyTypes);
            _Instance                   = (ICgBlockchain)constructor.Invoke(Type.EmptyTypes);
        }

        public abstract void Shutdown();

        public abstract void Rebuild();

        public abstract void SetCommand(ECgBlockchainCommand command, string str);
        public abstract void RunCommand(ECgBlockchainProcessType processType, string command);
        public abstract void RunCommand(ECgBlockchainProcessType processType, ECgBlockchainCommand command, CgBlockchainCommandArgument[] args = null);

        public abstract void SetProcess(ECgBlockchainProcessType processType, CgProcess p);
        public abstract CgProcess GetProcess(ECgBlockchainProcessType processType);
        public abstract void StartProcess(ECgBlockchainProcessType processType, CgBlockchainProcessStartInfo startInfo);
        public abstract void StopProcess(ECgBlockchainProcessType processType);

        public abstract void OpenRunningInstance();
        public abstract void CreatePrivateChain();
        public abstract void StartPrivateChain();

        public abstract void OpenConsole();
        public abstract void CloseConsole();

        #region "Account"

        public abstract void LoadAccounts();
        public abstract void NewAccount(object payload);
        public abstract void UnlockAccount(object payload);
        public abstract void ListAccounts();

        #endregion // Account

        public abstract void StartMiner();
        public abstract void StopMiner();
    }

}
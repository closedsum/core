namespace CgCore
{
    using System;
    using System.Collections;
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

    public struct CgBlockchainProcessStartInfo
    {
        public string FileName;
        public string Arguments;
        public bool RedirectStandardInput;

        public CgBlockchainProcessStartInfo(string fileName, string arguments, bool redirectedStandardInput)
        {
            FileName = fileName;
            Arguments = arguments;
            RedirectStandardInput = redirectedStandardInput;
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

    public enum ECgBlockchainCommandFullfillmentRule : byte
    {
        None,
        Contain,
        Match,
        MAX
    }

    public class CgBlockchainCommandFullfillment
    {
        public bool Completed;
        public ECgBlockchainCommandFullfillmentRule Rule;
        public string Response;

        public CgBlockchainCommandFullfillment(ECgBlockchainCommandFullfillmentRule rule, string response)
        {
            Completed = false;
            Rule = rule;
            Response = response.ToLower();
        }

        public bool HasCompleted(string input)
        {
            if (Completed)
                return Completed;

            if (Rule == ECgBlockchainCommandFullfillmentRule.None)
                Completed = true;
            else
            if (Rule == ECgBlockchainCommandFullfillmentRule.Contain)
                Completed = input.ToLower().Contains(Response);
            else
            if (Rule == ECgBlockchainCommandFullfillmentRule.Match)
                Completed = Response == input.ToLower();
            return Completed;
        }
    }

    public class CgBlockchainCommandRequest
    {
        public float StartTime;
        public ECgBlockchainCommand Command;
        public CgBlockchainCommandArgument[] Arguments;
        public Queue<List<CgBlockchainCommandFullfillment>> FullfillmentQueue;

        public CgBlockchainCommandRequest(float startTime, ECgBlockchainCommand command, CgBlockchainCommandArgument[] arguments = null)
        {
            StartTime = startTime;
            Command   = command;

            if (arguments == null || arguments.Length == 0)
            {
                Arguments = null;
            }
            else
            {
                int len   = arguments.Length;
                Arguments = new CgBlockchainCommandArgument[len];

                for (int i = 0; i < len; ++i)
                {
                    Arguments[i] = arguments[i];
                }
            }

            FullfillmentQueue = new Queue<List<CgBlockchainCommandFullfillment>>();
        }

        public void AddFullfillment(ECgBlockchainCommandFullfillmentRule rule, string response)
        {
            List<CgBlockchainCommandFullfillment> fullfillments = new List<CgBlockchainCommandFullfillment>();
            fullfillments.Add(new CgBlockchainCommandFullfillment(rule, response));
            FullfillmentQueue.Enqueue(fullfillments);
        }

        public bool HasCompleted(string input)
        {
            List<CgBlockchainCommandFullfillment> head = FullfillmentQueue.Peek();

            bool completed = true;

            int count = head.Count;

            for (int i = 0; i < count; ++i)
            {
                completed |= head[i].HasCompleted(input);
            }

            if (completed)
                FullfillmentQueue.Dequeue();
            return completed;
        }
    }

    public static class ICgBlockchainInterface
    {
        public static void Init(Type type)
        {
            if (Get() != null)
                return;

            PropertyInfo p   = type.GetProperty("Instance", BindingFlags.Public | BindingFlags.Static | BindingFlags.Instance | BindingFlags.FlattenHierarchy);
            ICgBlockchain bc = (ICgBlockchain)(p.GetValue(null, null));

            if (bc != null)
                return;
        }

        public static ICgBlockchain Get()
        {
            if (CgBlockchain.Get != null)
                return CgBlockchain.Get();
            return null;
        }
    }

    public interface ICgBlockchain
    {
        #region "Data Members"

        ECgBlockchainStorageType StorageType { get; set; }

            #region "Private / Local Storage"

        string RootDirectory { get; set; }
        string ChainDirectory { get; set; }

        Dictionary<ECgBlockchainProcessType, Process> Processes { get; set; }
        Dictionary<ECgBlockchainProcessType, bool> ProcessFlags { get; set; }

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

        Dictionary<ECgBlockchainProcessType, Queue<CgBlockchainCommandRequest>> CommandRequests { get; set; }
        CgBlockchainCommandRequest CurrentCommandRequest { get; set; }

        Dictionary<string, ICgBlockchainAccount> Accounts { get; set; }

        #endregion // Data Members

        void Shutdown();

        void SetCommand(ECgBlockchainCommand command, string str);
        void RunCommand(ECgBlockchainProcessType processType, string command);
        void RunCommand(ECgBlockchainProcessType processType, ECgBlockchainCommand command, CgBlockchainCommandArgument[] args = null);

        void SetProcess(ECgBlockchainProcessType processType, Process p);
        Process GetProcess(ECgBlockchainProcessType processType);
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

        void NewAccount(object payload);
        void UnlockAccount(object payload);

        /* Starts a miner */
        void StartMiner();
        /* Stops a miner */
        void StopMiner();
    }

    public abstract class CgBlockchain : ICgBlockchain
    {
        public static CgConsoleVariableLog LogIO = new CgConsoleVariableLog("log.blockchain.io", false, "Log Blockchain Input / Output Messages", (int)ECgConsoleVariableFlag.Console);
        public static TCgConsoleVariable<bool> ShowProcessWindow = new TCgConsoleVariable<bool>("show.blockchain.processwindow", false, "Show Blockchain Process Window", (int)ECgConsoleVariableFlag.Console);
        public static CgConsoleVariableLog LogOnBoard = new CgConsoleVariableLog("log.blockchain.onboard", false, "Log Blockchain OnBoard Process", (int)ECgConsoleVariableFlag.Console);

        public delegate ICgBlockchain Getter();

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

        private Dictionary<ECgBlockchainProcessType, Process> _Processes;
        public Dictionary<ECgBlockchainProcessType, Process> Processes
        {
            get { return _Processes; }
            set { _Processes = value; }
        }

        private Dictionary<ECgBlockchainProcessType, bool> _ProcessFlags;
        public Dictionary<ECgBlockchainProcessType, bool> ProcessFlags
        {
            get { return _ProcessFlags; }
            set { _ProcessFlags = value; }
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

        private Dictionary<ECgBlockchainProcessType, Queue<CgBlockchainCommandRequest>> _CommandRequests;
        public Dictionary<ECgBlockchainProcessType, Queue<CgBlockchainCommandRequest>> CommandRequests
        {
            get { return _CommandRequests; }
            set { _CommandRequests = value; }
        }

        private CgBlockchainCommandRequest _CurrentCommandRequest;
        public CgBlockchainCommandRequest CurrentCommandRequest
        {
            get { return _CurrentCommandRequest; }
            set { _CurrentCommandRequest = value; }
        }

        private Dictionary<string, ICgBlockchainAccount> _Accounts;
        public Dictionary<string, ICgBlockchainAccount> Accounts
        {
            get { return _Accounts; }
            set { _Accounts = value; }
        }

            #endregion // Interface

        public static Getter Get;

        #endregion // Data Members

        protected abstract void Init();

        public abstract void Shutdown();

        public abstract void SetCommand(ECgBlockchainCommand command, string str);
        public abstract void RunCommand(ECgBlockchainProcessType processType, string command);
        public abstract void RunCommand(ECgBlockchainProcessType processType, ECgBlockchainCommand command, CgBlockchainCommandArgument[] args = null);
        public abstract void AddCommandRequest(ECgBlockchainProcessType processType, CgBlockchainCommandRequest request);

        public abstract void SetProcess(ECgBlockchainProcessType processType, Process p);
        public abstract Process GetProcess(ECgBlockchainProcessType processType);
        public abstract void StartProcess(ECgBlockchainProcessType processType, CgBlockchainProcessStartInfo startInfo);
        public abstract void StopProcess(ECgBlockchainProcessType processType);

        public abstract void OpenRunningInstance();
        public abstract void CreatePrivateChain();
        public abstract void StartPrivateChain();

        public abstract void OpenConsole();
        public abstract void CloseConsole();

        public abstract void NewAccount(object payload);
        public abstract void UnlockAccount(object payload);

        public abstract void StartMiner();
        public abstract void StopMiner();
    }

}
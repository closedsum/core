namespace CgCore
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

    public enum ECgBlockchainCommandFulfillmentRule : byte
    {
        None,
        Contain,
        Match,
        MAX
    }

    public class CgBlockchainCommandFulfillment
    {
        private bool Completed;
        public ECgBlockchainCommandFulfillmentRule Rule;
        public string Response;

        public CgBlockchainCommandFulfillment(ECgBlockchainCommandFulfillmentRule rule, string response)
        {
            Completed = false;
            Rule = rule;
            Response = response.ToLower();
        }

        public bool HasCompleted(string input)
        {
            if (Completed)
                return Completed;

            if (Rule == ECgBlockchainCommandFulfillmentRule.None)
                Completed = true;
            else
            if (Rule == ECgBlockchainCommandFulfillmentRule.Contain)
                Completed = input.ToLower().Contains(Response);
            else
            if (Rule == ECgBlockchainCommandFulfillmentRule.Match)
                Completed = Response == input.ToLower();
            return Completed;
        }

        public void Clear()
        {
            Completed = false;
        }
    }

    public class CgBlockchainCommandRequest
    {
        public sealed class Completed : TCgMulticastDelegate_OneParam<CgBlockchainCommandRequest>{}

        #region "Constants"

        private static readonly int EMPTY = 0;

        #endregion // Constants

        #region "Data Members

        public bool RunWhenRelevant;

        public float StartTime;
        public ECgBlockchainCommand Command;
        public CgBlockchainCommandArgument[] Arguments;
        public List<List<CgBlockchainCommandFulfillment>> FulfillmentList;
        private int Index;

        public Completed Completed_Event;

        #endregion // Data Members

        public CgBlockchainCommandRequest(ECgBlockchainCommand command, CgBlockchainCommandArgument[] arguments = null)
        {
            RunWhenRelevant = true;
            StartTime = 0.0f;
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

            FulfillmentList = new List<List<CgBlockchainCommandFulfillment>>();
            Index = 0;
            Completed_Event = new Completed();
        }

        public void AddFulfillment(ECgBlockchainCommandFulfillmentRule rule, string response)
        {
            List<CgBlockchainCommandFulfillment> Fulfillments = new List<CgBlockchainCommandFulfillment>();
            Fulfillments.Add(new CgBlockchainCommandFulfillment(rule, response));
            FulfillmentList.Add(Fulfillments);
        }

        public void AddFulfillments(List<CgBlockchainCommandFulfillment> Fulfillments)
        {
            FulfillmentList.Add(Fulfillments);
        }

        public bool HasCompleted(string input)
        {
            if (FulfillmentList.Count == EMPTY)
                return true;

            List<CgBlockchainCommandFulfillment> current = FulfillmentList[Index];

            if (CgProcess.LogCommandRequest.Log())
            {
                CgDebug.Log("CgBlockchainCommandRequest.HasCompleted: Start checking input: \"" + input + "\"");
                CgDebug.Log("CgBlockchainCommandRequest.HasCompleted: -- Checking Fulfillment[" + Index + "] of " + FulfillmentList.Count);
            }

            bool completed = true;

            int count = current.Count;

            for (int i = 0; i < count; ++i)
            {
                bool hasCompleted = current[i].HasCompleted(input);
                completed        &= hasCompleted;

                if (CgProcess.LogCommandRequest.Log())
                {
                    string rule     = current[i].Rule.ToString();
                    string response = current[i].Response;
                    string completion = hasCompleted ? "" : "NOT";

                    CgDebug.Log("CgBlockchainCommandRequest.HasCompleted: -- Checking Fulfillment[" + Index + "][" + i + "] with Rule: " + rule + " and Response: \"" + response + "\" has " + completion + " completed");
                }
            }

            if (completed)
                ++Index;

            if (Index >= FulfillmentList.Count)
                Completed_Event.Broadcast(this);
            return completed && Index >= FulfillmentList.Count;
        }

        public void Clear()
        {
            int iMax = FulfillmentList.Count;

            for (int i = 0; i < iMax; ++i)
            {
                int jMax = FulfillmentList[i].Count;

                for (int j = 0; j < jMax; ++j)
                {
                    FulfillmentList[i][j].Clear();
                }
            }
            Index = 0;
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
    }

    public interface ICgBlockchain
    {
        #region "Data Members"

        ECgBlockchainStorageType StorageType { get; set; }

            #region "Private / Local Storage"

        string RootDirectory { get; set; }
        string ChainDirectory { get; set; }

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

        Dictionary<ECgBlockchainProcessType, Dictionary<ECgBlockchainCommand, CgBlockchainCommandRequest>> CommandRequests { get; set; }
        Dictionary<ECgBlockchainProcessType, CgBlockchainCommandRequest> CurrentCommandRequests { get; set; }
        Dictionary<ECgBlockchainProcessType, Queue<CgBlockchainCommandRequest>> CommandRequestQueue { get; set; }

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
        public static CgConsoleVariableLog LogCommandCompleted = new CgConsoleVariableLog("log.blockchain.command.completed", false, "Log Blockchain Command Completed", (int)ECgConsoleVariableFlag.Console);

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

        private Dictionary<ECgBlockchainProcessType, Dictionary<ECgBlockchainCommand, CgBlockchainCommandRequest>> _CommandRequests;
        public Dictionary<ECgBlockchainProcessType, Dictionary<ECgBlockchainCommand, CgBlockchainCommandRequest>> CommandRequests
        {
            get { return _CommandRequests; }
            set { _CommandRequests = value; }
        }

        private Dictionary<ECgBlockchainProcessType, CgBlockchainCommandRequest> _CurrentCommandRequests;
        public Dictionary<ECgBlockchainProcessType, CgBlockchainCommandRequest> CurrentCommandRequests
        {
            get { return _CurrentCommandRequests; }
            set { _CurrentCommandRequests = value; }
        }

        private Dictionary<ECgBlockchainProcessType, Queue<CgBlockchainCommandRequest>> _CommandRequestQueue;
        public Dictionary<ECgBlockchainProcessType, Queue<CgBlockchainCommandRequest>> CommandRequestQueue
        {
            get { return _CommandRequestQueue; }
            set { _CommandRequestQueue = value; }
        }

        private Dictionary<string, ICgBlockchainAccount> _Accounts;
        public Dictionary<string, ICgBlockchainAccount> Accounts
        {
            get { return _Accounts; }
            set { _Accounts = value; }
        }

            #endregion // Interface

        private static ICgBlockchain _Instance;

        #endregion // Data Members

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

        public abstract void SetCommand(ECgBlockchainCommand command, string str);
        public abstract void RunCommand(ECgBlockchainProcessType processType, string command);
        public abstract void RunCommand(ECgBlockchainProcessType processType, ECgBlockchainCommand command, CgBlockchainCommandArgument[] args = null);
        public abstract void EnqueueCommand(ECgBlockchainProcessType processType, CgBlockchainCommandRequest request);
        public abstract void EnqueueCommand(ECgBlockchainProcessType processType, ECgBlockchainCommand command);

        public abstract void SetProcess(ECgBlockchainProcessType processType, CgProcess p);
        public abstract CgProcess GetProcess(ECgBlockchainProcessType processType);
        public abstract void StartProcess(ECgBlockchainProcessType processType, CgBlockchainProcessStartInfo startInfo);
        public abstract void StopProcess(ECgBlockchainProcessType processType);

        public abstract void OpenRunningInstance();
        public abstract void CreatePrivateChain();
        public abstract void StartPrivateChain();

        public abstract void OpenConsole();
        public abstract void CloseConsole();

        public abstract void NewAccount(object payload);
        public abstract void UnlockAccount(object payload);
        public abstract void ListAccounts();

        public abstract void StartMiner();
        public abstract void StopMiner();
    }

}
// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Managers/Process/CsProcess.h"
#include "Blockchain/CsBlockchainContract.h"
#include "CsBlockchain.generated.h"

UENUM(BlueprintType)
namespace ECgBlockchainType
{
	enum Type
	{
		PrivateSingleNode		UMETA(DisplayName = "Private Single Node"),
		Local					UMETA(DisplayName = "Local"),
		Server					UMETA(DisplayName = "Server"),
		ECgBlockchainType_MAX	UMETA(Hidden),
	};
}

#define ECS_BLOCKCHAIN_TYPE_MAX (uint8)ECgBlockchainType::ECgBlockchainType_MAX
typedef ECgBlockchainType::Type TCgBlockchainType;

namespace ECgBlockchainType
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_TwoParams TCsString;

	namespace Str
	{
		const TCsString PrivateSingleNode = TCsString(TEXT("PrivateSingleNode"), TEXT("privatesinglenode"));
		const TCsString Local = TCsString(TEXT("Local"), TEXT("local"));
		const TCsString Server = TCsString(TEXT("Server"), TEXT("server"));
	}

	namespace Ref
	{
		const Type PrivateSingleNode = Type::PrivateSingleNode;
		const Type Local = Type::Local;
		const Type Server = Type::Server;
		const Type ECgBlockchainType_MAX = Type::ECgBlockchainType_MAX;
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		if (EType == Type::PrivateSingleNode) { return Str::PrivateSingleNode.Value; }
		if (EType == Type::Local) { return Str::Local.Value; }
		if (EType == Type::Server) { return Str::Server.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE const Type& ToType(const FString &InString)
	{
		if (InString == Str::PrivateSingleNode) { return Ref::PrivateSingleNode; }
		if (InString == Str::Local) { return Ref::Local; }
		if (InString == Str::Server) { return Ref::Server; }
		return Ref::ECgBlockchainType_MAX;
	}
}

UENUM(BlueprintType)
namespace ECgBlockchainProcessType
{
	enum Type
	{
		RunningInstance					UMETA(DisplayName = "Running Instance"),
		Console							UMETA(DisplayName = "Console"),
		ECgBlockchainProcessType_MAX	UMETA(Hidden),
	};
}

#define ECS_BLOCKCHAIN_PROCESS_TYPE_MAX (uint8)ECgBlockchainProcessType::ECgBlockchainProcessType_MAX
typedef ECgBlockchainProcessType::Type TCgBlockchainProcessType;

namespace ECgBlockchainProcessType
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_TwoParams TCsString;

	namespace Str
	{
		const TCsString RunningInstance = TCsString(TEXT("RunningInstance"), TEXT("runninginstance"));
		const TCsString Console = TCsString(TEXT("Console"), TEXT("console"));
	}

	namespace Ref
	{
		const Type RunningInstance = Type::RunningInstance;
		const Type Console = Type::Console;
		const Type ECgBlockchainProcessType_MAX = Type::ECgBlockchainProcessType_MAX;
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		if (EType == Type::RunningInstance) { return Str::RunningInstance.Value; }
		if (EType == Type::Console) { return Str::Console.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE const Type& ToType(const FString &InString)
	{
		if (InString == Str::RunningInstance) { return Ref::RunningInstance; }
		if (InString == Str::Console) { return Ref::Console; }
		return Ref::ECgBlockchainProcessType_MAX;
	}
}

USTRUCT(BlueprintType)
struct FCsBlockchainProcessStartInfo
{
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	FString FileName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	FString Arguments;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	bool RedirectStandardInput;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	TArray<FCsProcessMonitorOutputEvent> MonitorOutputEvents;

	FCsBlockchainProcessStartInfo(){}
	~FCsBlockchainProcessStartInfo(){}

	void AddMonitorOutputEvent(const FCsProcessMonitorOutputEvent &e)
	{
		MonitorOutputEvents.Add(e);
	}
}

UCLASS(transient)
class CSCORE_API UCsBlockchain: public UObject
{
	GENERATED_UCLASS_BODY()

// Singleton
#pragma region
public:

	UClass* SpawnClass;

	static UCsBlockchain* Get();
	template<typename T>
	static T* Get()
	{
		Cast<T>(Get());
	}

	static void Init(UClass* InSpawnClass);
	static void Shutdown();

protected:

	void Initialize();
	void CleanUp();

private:
	// Singleton data
	static UCsBlockchain* s_blockchainSingleton;
	static bool s_bBlockchainHasShutdown;

#pragma endregion Singleton

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blockchain")
	TEnumAsByte<ECsBlockchainType::Type> StorageType;

// Paths
#pragma region
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blockchain")
	FString RootDirectory;

	UFUNCTION(BlueprintCallable, Category = "Blockchain")
	virtual void SetRootDirectory(const FString &Path);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blockchain")
	FString ChainDirectory;

	UFUNCTION(BlueprintCallable, Category = "Blockchain")
	virtual void SetChainDirectory(const FString &Path);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blockchain")
	FString AccountsDirectory;

	UFUNCTION(BlueprintCallable, Category = "Blockchain")
	virtual void SetAccountsDirectory(const FString &Path);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blockchain")
	FString ContractsDirectory;

	UFUNCTION(BlueprintCallable, Category = "Blockchain")
	virtual void SetContractsDirectory(const FString &Path);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blockchain")
	FString ContractsDeployedDirectory;

	UFUNCTION(BlueprintCallable, Category = "Blockchain")
	virtual void SetContractsDeployedDirectory(const FString &Path);

#pragma endregion Paths

// Process
#pragma region
public:

	TMap<TCgBlockchainProcessType, UCsProcess*> Processes;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blockchain")
	FString ConsoleFilename;

	UFUNCTION(BlueprintCallable, Category = "Blockchain")
	virtual void SetConsoleFilename(const FString &Filename);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blockchain")
	FString ConsoleDirectory;

	UFUNCTION(BlueprintCallable, Category = "Blockchain")
	virtual void SetConsoleDirectory(const FString &Path);

#pragma endregion Process

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blockchain")
	bool IsMining;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blockchain")
	class UCsBlockchainGenesis* Genesis;

	TMap<FECgBlockchainContract, ICsBlockchainContract*> Contracts;
};

public interface ICgBlockchain
{

	bool IsConsoleOpen{ get; set; }
	bool IsMining{ get; set; }

		#endregion // Console

		#endregion // Private / Local Storage

		ICgBlockchainGenesis Genesis{ get; set; }
	Dictionary<ECgBlockchainContract, ICgBlockchainContract> Contracts{ get; set; }
	Dictionary<ECgBlockchainCommand, string> Commands{ get; set; }

	Dictionary<string, ICgBlockchainAccount> Accounts{ get; set; }

		#endregion // Data Members

		void Shutdown();

	void Start();

	void SetCommand(ECgBlockchainCommand command, string str);
	void RunCommand(int consoleIndex, string command);
	void RunCommand(int consoleIndex, ECgBlockchainCommand command, CgBlockchainCommandArgument[] args = null);

	void SetProcess(ECgBlockchainProcessType processType, int index, CgProcess p);
	CgProcess GetProcess(ECgBlockchainProcessType processType, int index);
	void StartProcess(ECgBlockchainProcessType processType, int index, CgBlockchainProcessStartInfo startInfo);
	void StopProcess(ECgBlockchainProcessType processType, int index);

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
	void UnlockAccount(ICgBlockchainAccount iaccount);

	#endregion // Account

			   /* Starts a miner */
		void StartMiner();
	/* Stops a miner */
	void StopMiner();
}

public abstract class CgBlockchain : ICgBlockchain
{
	#region "CVars"

		public static CgConsoleVariableLog LogIO = new CgConsoleVariableLog("log.blockchain.io", false, "Log All Blockchain Input / Output Messages", (int)ECgConsoleVariableFlag.Console);
	public static CgConsoleVariableLog LogIOProcess = new CgConsoleVariableLog("log.blockchain.io.process", false, "Log Process Blockchain Input / Output Messages", (int)ECgConsoleVariableFlag.Console);
	public static CgConsoleVariableLog LogIOConsole = new CgConsoleVariableLog("log.blockchain.io.console", false, "Log Console Blockchain Input / Output Messages", (int)ECgConsoleVariableFlag.Console);
	// Process
	public static TCgConsoleVariable<bool> ShowProcessWindow = new TCgConsoleVariable<bool>("show.blockchain.processwindow", false, "Show Blockchain Process Window", (int)ECgConsoleVariableFlag.Console);
	public static CgConsoleVariableLog LogProcessStart = new CgConsoleVariableLog("log.blockchain.process.start", false, "Log Blockchain Process Starting", (int)ECgConsoleVariableFlag.Console);
	// Command
	public static CgConsoleVariableLog LogCommandCompleted = new CgConsoleVariableLog("log.blockchain.command.completed", false, "Log Blockchain Command Completed", (int)ECgConsoleVariableFlag.Console);
	// Account
	public static CgConsoleVariableLog LogAccountCreated = new CgConsoleVariableLog("log.blockchain.account.created", false, "Log Blockchain Account Created", (int)ECgConsoleVariableFlag.Console);

	#endregion // CVars

		public class PrivateChainCreated : TCgMulticastDelegate_OneParam<int> { }
	public class PrivateChainStarted : TCgMulticastDelegate_OneParam<int> { }
	public class ConsoleOpened : TCgMulticastDelegate_OneParam<int> { }
	public class CommandCompleted : TCgMulticastDelegate_OneParam<ECgBlockchainCommand> { }
	public class AccountCreated : TCgMulticastDelegate_OneParam<ICgBlockchainAccount> { }
	public class CoinbaseSet : TCgDelegate_OneParam<ICgBlockchainAccount> { }
	public class ContractFunctionCompleted : TCgMulticastDelegate_TwoParams<ECgBlockchainContract, ECgBlockchainContractFunction> { }

	#region "Constants"

		protected static readonly int EMPTY = 0;
	protected static readonly string INVALID_COMMAND = "";
	protected static readonly int SINGLE_NODE_INDEX = 0;
	protected static readonly string EMPTY_PATH = "";

	#endregion // Constants

		#region "Data Members"

		#region "Interface"

		private ECgBlockchainType _StorageType;
	public ECgBlockchainType StorageType
	{
		get{ return _StorageType; }
	set{ _StorageType = value; }
	}

	private string _RootDirectory;
	public string RootDirectory
	{
		get{ return _RootDirectory; }
	set{ _RootDirectory = value; }
	}

	private string _ChainDirectory;
	public string ChainDirectory
	{
		get{ return _ChainDirectory; }
	set{ _ChainDirectory = value; }
	}

	private string _AccountsDirectory;
	public string AccountsDirectory
	{
		get{ return _AccountsDirectory; }
	set{ _AccountsDirectory = value; }
	}

	private string _ContractsDirectory;
	public string ContractsDirectory
	{
		get{ return _ContractsDirectory; }
	set{ _ContractsDirectory = value; }
	}

	private string _ContractsDeployedDirectory;
	public string ContractsDeployedDirectory
	{
		get{ return _ContractsDeployedDirectory; }
	set{ _ContractsDeployedDirectory = value; }
	}

	private Dictionary<ECgBlockchainProcessType, CgProcess> _Processes;
	public Dictionary<ECgBlockchainProcessType, CgProcess> Processes
	{
		get{ return _Processes; }
	set{ _Processes = value; }
	}

		#region "Running Instance"

		private bool _IsRunningInstanceOpen;
	public bool IsRunningInstanceOpen
	{
		get{ return _IsRunningInstanceOpen; }
	set{ _IsRunningInstanceOpen = value; }
	}

		#endregion // Running Instance

		#region "Console"

		private string _ConsoleFilename;
	public string ConsoleFilename
	{
		get{ return _ConsoleFilename; }
	set{ _ConsoleFilename = value; }
	}

	private string _ConsoleDirectory;
	public string ConsoleDirectory
	{
		get{ return _ConsoleDirectory; }
	set{ _ConsoleDirectory = value; }
	}

	private bool _IsConsoleOpen;
	public bool IsConsoleOpen
	{
		get{ return _IsConsoleOpen; }
	set{ _IsConsoleOpen = value; }
	}

	private bool _IsMining;
	public bool IsMining
	{
		get{ return _IsMining; }
	set{ _IsMining = value; }
	}

		#endregion // Console

		private ICgBlockchainGenesis _Genesis;
	public ICgBlockchainGenesis Genesis
	{
		get{ return _Genesis; }
	set{ _Genesis = value; }
	}

	private Dictionary<ECgBlockchainContract, ICgBlockchainContract> _Contracts;
	public Dictionary<ECgBlockchainContract, ICgBlockchainContract> Contracts
	{
		get{ return _Contracts; }
	set{ _Contracts = value; }
	}

	private Dictionary<ECgBlockchainCommand, string> _Commands;
	public Dictionary<ECgBlockchainCommand, string> Commands
	{
		get{ return _Commands; }
	set{ _Commands = value; }
	}

	private Dictionary<string, ICgBlockchainAccount> _Accounts;
	public Dictionary<string, ICgBlockchainAccount> Accounts
	{
		get{ return _Accounts; }
	set{ _Accounts = value; }
	}

		#endregion // Interface

		private static ICgBlockchain _Instance;

	public PrivateChainCreated PrivateChainCreated_Event;
	public PrivateChainStarted PrivateChainStarted_Event;
	public ConsoleOpened ConsoleOpened_Event;
	public CommandCompleted CommandCompleted_Event;
	public AccountCreated AccountCreated_Event;
	public CoinbaseSet CoinbaseSet_Event;
	public ContractFunctionCompleted ContractFunctionCompleted_Event;

	#endregion // Data Members

		public CgBlockchain()
	{
		Processes = new Dictionary<ECgBlockchainProcessType, CgProcess>(new ECgBlockchainProcessTypeEqualityComparer());

		for (byte i = 0; i < (byte)ECgBlockchainProcessType.MAX; ++i)
		{
			Processes.Add((ECgBlockchainProcessType)i, null);
		}

		Contracts = new Dictionary<ECgBlockchainContract, ICgBlockchainContract>();
		Commands = new Dictionary<ECgBlockchainCommand, string>(new ECgBlockchainCommandEqualityComparer());

		Accounts = new Dictionary<string, ICgBlockchainAccount>();

		PrivateChainCreated_Event = new PrivateChainCreated();
		PrivateChainStarted_Event = new PrivateChainStarted();
		ConsoleOpened_Event = new ConsoleOpened();
		CommandCompleted_Event = new CommandCompleted();
		AccountCreated_Event = new AccountCreated();
		CoinbaseSet_Event = new CoinbaseSet();
		ContractFunctionCompleted_Event = new ContractFunctionCompleted();
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
		_Instance = (ICgBlockchain)constructor.Invoke(Type.EmptyTypes);
	}

	public abstract void Shutdown();

	public abstract void Start();

	public abstract void Rebuild();

	public abstract void SetCommand(ECgBlockchainCommand command, string str);
	public abstract void RunCommand(int consoleIndex, string command);
	public abstract void RunCommand(int consoleIndex, ECgBlockchainCommand command, CgBlockchainCommandArgument[] args = null);

	public abstract void SetProcess(ECgBlockchainProcessType processType, int index, CgProcess p);
	public abstract CgProcess GetProcess(ECgBlockchainProcessType processType, int index);
	public abstract void StartProcess(ECgBlockchainProcessType processType, int index, CgBlockchainProcessStartInfo startInfo);
	public abstract void StopProcess(ECgBlockchainProcessType processType, int index);

	public abstract void OpenRunningInstance();
	public abstract void CreatePrivateChain();
	public abstract void StartPrivateChain();

	public abstract void OpenConsole();
	public abstract void CloseConsole();

	#region "Account"

		public abstract void LoadAccounts();
	public abstract void NewAccount(object payload);
	public abstract void UnlockAccount(ICgBlockchainAccount iaccount);
	public abstract void ListAccounts();

	#endregion // Account

		public abstract void StartMiner();
	public abstract void StopMiner();
}
// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Managers/Process/CsProcess.h"
#include "Blockchain/CsBlockchainContract.h"
#include "Blockchain/CsBlockchainCommand.h"
#include "CsBlockchain.generated.h"

UENUM(BlueprintType)
namespace ECsBlockchainType
{
	enum Type
	{
		PrivateSingleNode		UMETA(DisplayName = "Private Single Node"),
		Local					UMETA(DisplayName = "Local"),
		Server					UMETA(DisplayName = "Server"),
		ECsBlockchainType_MAX	UMETA(Hidden),
	};
}

#define ECS_BLOCKCHAIN_TYPE_MAX (uint8)ECsBlockchainType::ECsBlockchainType_MAX
typedef ECsBlockchainType::Type TCsBlockchainType;

namespace ECsBlockchainType
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
		const Type ECsBlockchainType_MAX = Type::ECsBlockchainType_MAX;
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
		return Ref::ECsBlockchainType_MAX;
	}
}

UENUM(BlueprintType)
namespace ECsBlockchainProcessType
{
	enum Type
	{
		RunningInstance					UMETA(DisplayName = "Running Instance"),
		Console							UMETA(DisplayName = "Console"),
		ECsBlockchainProcessType_MAX	UMETA(Hidden),
	};
}

#define ECS_BLOCKCHAIN_PROCESS_TYPE_MAX (uint8)ECsBlockchainProcessType::ECsBlockchainProcessType_MAX
typedef ECsBlockchainProcessType::Type TCsBlockchainProcessType;

namespace ECsBlockchainProcessType
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
		const Type ECsBlockchainProcessType_MAX = Type::ECsBlockchainProcessType_MAX;
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
		return Ref::ECsBlockchainProcessType_MAX;
	}
}

USTRUCT(BlueprintType)
struct FCsBlockchainProcessStartInfo
{
	GENERATED_USTRUCT_BODY()

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

	FCsBlockchainProcessStartInfo& operator=(const FCsBlockchainProcessStartInfo& B)
	{
		FileName = B.FileName;
		Arguments = B.Arguments;
		RedirectStandardInput = B.RedirectStandardInput;

		MonitorOutputEvents.Reset();

		const int32 Count = B.MonitorOutputEvents.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			MonitorOutputEvents.Add(B.MonitorOutputEvents[I]);
		}
		return *this;
	}

	bool operator==(const FCsBlockchainProcessStartInfo& B) const
	{
		if (FileName != B.FileName)
			return false;
		if (Arguments != B.Arguments)
			return false;
		if (RedirectStandardInput != B.RedirectStandardInput)
			return false;

		if (MonitorOutputEvents.Num() != B.MonitorOutputEvents.Num())
			return false;

		const int32 Count = B.MonitorOutputEvents.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			if (MonitorOutputEvents[I] != B.MonitorOutputEvents[I])
				return false;
		}
		return true;
	}

	bool operator!=(const FCsBlockchainProcessStartInfo& B) const
	{
		return !(*this == B);
	}

	void AddMonitorOutputEvent(const FCsProcessMonitorOutputEvent &e)
	{
		MonitorOutputEvents.Add(e);
	}
};

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

	TMap<TCsBlockchainProcessType, UCsProcess*> Processes;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blockchain")
	FString ConsoleFilename;

	UFUNCTION(BlueprintCallable, Category = "Blockchain")
	virtual void SetConsoleFilename(const FString &Filename);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blockchain")
	FString ConsoleDirectory;

	UFUNCTION(BlueprintCallable, Category = "Blockchain")
	virtual void SetConsoleDirectory(const FString &Path);

#pragma endregion Process

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blockchain")
	bool IsMining;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blockchain")
	class UCsBlockchainGenesis* Genesis;

	TMap<FECsBlockchainContract, class ICsBlockchainContract*> Contracts;
	TMap<FECsBlockchainCommand, FString> Commands;
	TMap<FString, class ICsBlockchainAccount*> Accounts;

	UFUNCTION(BlueprintCallable, Category = "Blockchain")
	virtual void Start();

	UFUNCTION(BlueprintCallable, Category = "Blockchain")
	virtual void SetCommand(const FECsBlockchainCommand &Command, const FString &Str);

	UFUNCTION(BlueprintCallable, Category = "Blockchain")
	virtual void RunCommand(const int32 &ConsoleIndex, const FECsBlockchainCommand &Command, TArray<FCsBlockchainCommandArgument> &Arguments);
	virtual void RunCommand(const int32 &ConsoleIndex, const FString &Command);
	UFUNCTION(BlueprintCallable, Category = "Blockchain")
	void RunCommandEX(const int32 &ConsoleIndex, const FString &Command);

	UFUNCTION(BlueprintCallable, Category = "Blockchain")
	virtual void SetProcess(const TEnumAsByte<ECsBlockchainProcessType::Type> &ProcessType, const int32 &Index, class UCsProcess* Process);
	
	UFUNCTION(BlueprintCallable, Category = "Blockchain")
	virtual class UCsProcess* GetProcess(const TEnumAsByte<ECsBlockchainProcessType::Type> &ProcessType, const int32 &Index);

	UFUNCTION(BlueprintCallable, Category = "Blockchain")
	virtual void StartProcess(const TEnumAsByte<ECsBlockchainProcessType::Type> &ProcessType, const int32 &Index, const FCsBlockchainProcessStartInfo &StartInfo);

	UFUNCTION(BlueprintCallable, Category = "Blockchain")
	virtual void StopProcess(const TEnumAsByte<ECsBlockchainProcessType::Type> &ProcessType, const int32 &Index);

	UFUNCTION(BlueprintCallable, Category = "Blockchain")
	virtual void OpenRunningInstance();
	/* Setup chaindata and genesis.json for private chain */
	UFUNCTION(BlueprintCallable, Category = "Blockchain")
	virtual void CreatePrivateChain();
	/* Start running / polling the current private chain */
	UFUNCTION(BlueprintCallable, Category = "Blockchain")
	virtual void StartPrivateChain();


	/* Opens the console for the Blockchain program.
	 * From the console the user may execute any console commands.
	 */
	UFUNCTION(BlueprintCallable, Category = "Blockchain")
	virtual void OpenConsole();
	UFUNCTION(BlueprintCallable, Category = "Blockchain")
	virtual void CloseConsole();

// Account
#pragma region

	UFUNCTION(BlueprintCallable, Category = "Blockchain")
	virtual void LoadAccounts();

	virtual void NewAccount(void* Payload);
	virtual void UnlockAccount(class ICsBlockchainAccount* IAccount);

#pragma endregion Account

// Miner
#pragma region

	UFUNCTION(BlueprintCallable, Category = "Blockchain")
	virtual void StartMiner();

	UFUNCTION(BlueprintCallable, Category = "Blockchain")
	virtual void StopMiner();

#pragma endregion Miner
};

/*

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

*/
/*
public interface ICgBlockchain
{

	bool IsConsoleOpen{ get; set; }
	bool IsMining{ get; set; }
}
*/
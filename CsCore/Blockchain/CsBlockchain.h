// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Managers/Process/CsProcess.h"
#include "Blockchain/CsBlockchainContract.h"
#include "Blockchain/CsBlockchainCommand.h"
#include "CsBlockchain.generated.h"

UENUM(BlueprintType)
enum class ECsBlockchainType : uint8
{
	PrivateSingleNode		UMETA(DisplayName = "Private Single Node"),
	Local					UMETA(DisplayName = "Local"),
	Server					UMETA(DisplayName = "Server"),
	ECsBlockchainType_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsBlockchainType : public TCsEnumMap<ECsBlockchainType>
{
protected:
	EMCsBlockchainType() {}
	EMCsBlockchainType(const EMCsBlockchainType &) = delete;
	EMCsBlockchainType(EMCsBlockchainType &&) = delete;
public:
	~EMCsBlockchainType() {}
private:
	static EMCsBlockchainType* Instance;

public:
	static EMCsBlockchainType& Get();
};

namespace NCsBlockchainType
{
	namespace Ref
	{
		typedef ECsBlockchainType Type;

		extern CSCORE_API const Type PrivateSingleNode;
		extern CSCORE_API const Type Local;
		extern CSCORE_API const Type Server;
		extern CSCORE_API const Type ECsBlockchainType_MAX;
	}
}

UENUM(BlueprintType)
enum class ECsBlockchainProcessType : uint8
{
	RunningInstance					UMETA(DisplayName = "Running Instance"),
	Console							UMETA(DisplayName = "Console"),
	ECsBlockchainProcessType_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsBlockchainProcessType : public TCsEnumMap<ECsBlockchainProcessType>
{
protected:
	EMCsBlockchainProcessType() {}
	EMCsBlockchainProcessType(const EMCsBlockchainProcessType &) = delete;
	EMCsBlockchainProcessType(EMCsBlockchainProcessType &&) = delete;
public:
	~EMCsBlockchainProcessType() {}
private:
	static EMCsBlockchainProcessType* Instance;

public:
	static EMCsBlockchainProcessType& Get();
};

namespace NCsBlockchainProcessType
{
	namespace Ref
	{
		typedef ECsBlockchainProcessType Type;

		extern CSCORE_API const Type RunningInstance;
		extern CSCORE_API const Type Console;
		extern CSCORE_API const Type ECsBlockchainProcessType_MAX;
	}
}

USTRUCT(BlueprintType)
struct FCsBlockchainProcessStartInfo
{
	GENERATED_USTRUCT_BODY()

	/** URL - executable name */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	FString Filename;
	/** Params - command line arguments */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	FString Arguments;
	/** WritePipe - whether to use WritePipe */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	bool RedirectStandardInput;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	TArray<FCsProcessMonitorOutputEvent> MonitorOutputEvents;

	FCsBlockchainProcessStartInfo(){}
	~FCsBlockchainProcessStartInfo(){}

	FORCEINLINE FCsBlockchainProcessStartInfo& operator=(const FCsBlockchainProcessStartInfo& B)
	{
		Filename = B.Filename;
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

	FORCEINLINE bool operator==(const FCsBlockchainProcessStartInfo& B) const
	{
		if (Filename != B.Filename)
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

	FORCEINLINE bool operator!=(const FCsBlockchainProcessStartInfo& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE void AddMonitorOutputEvent(const FCsProcessMonitorOutputEvent &e)
	{
		MonitorOutputEvents.Add(e);
	}
};

USTRUCT(BlueprintType)
struct FCsBlockchainCommandInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	FECsBlockchainCommand Command;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	TArray<FCsBlockchainCommandArgument> Arguments;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	bool Payload_bool;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	int32 Payload_int32;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	float Payload_float;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	FString Payload_FString;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	FECsBlockchainContract Payload_Contract;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blockchain")
	FCsBlockchainContractFunctionPayload Payload_ContractFunction;

	void* Payload_ptr;

	FCsBlockchainCommandInfo() {}

	FCsBlockchainCommandInfo(const FECsBlockchainCommand &InCommand)
	{
		Command = InCommand;
	}

	FCsBlockchainCommandInfo(const FECsBlockchainCommand &InCommand, const TArray<FCsBlockchainCommandArgument> &Args)
	{
		Command = InCommand;
		SetArguments(Args);
	}

	FCsBlockchainCommandInfo(const FECsBlockchainCommand &InCommand, const TArray<FCsBlockchainCommandArgument> &Args, void* Payload)
	{
		Command = InCommand;
		SetArguments(Args);
		Payload_ptr = Payload;
	}

	FCsBlockchainCommandInfo(const FECsBlockchainCommand &InCommand, const TArray<FCsBlockchainCommandArgument> &Args, const bool &Payload)
	{
		Command = InCommand;
		SetArguments(Args);
		Payload_bool = Payload;
	}

	FCsBlockchainCommandInfo(const FECsBlockchainCommand &InCommand, const TArray<FCsBlockchainCommandArgument> &Args, const int32 &Payload)
	{
		Command = InCommand;
		SetArguments(Args);
		Payload_int32 = Payload;
	}

	FCsBlockchainCommandInfo(const FECsBlockchainCommand &InCommand, const TArray<FCsBlockchainCommandArgument> &Args, const float &Payload)
	{
		Command = InCommand;
		SetArguments(Args);
		Payload_float = Payload;
	}

	FCsBlockchainCommandInfo(const FECsBlockchainCommand &InCommand, const TArray<FCsBlockchainCommandArgument> &Args, const FString &Payload)
	{
		Command = InCommand;
		SetArguments(Args);
		Payload_FString = Payload;
	}

	~FCsBlockchainCommandInfo() {}

	FORCEINLINE void SetArguments(const TArray<FCsBlockchainCommandArgument> &Args)
	{
		Arguments.Reset();

		const int32 Count = Args.Num();

		for (const FCsBlockchainCommandArgument& Arg : Args)
		{
			Arguments.Add(Arg);
		}
	}

	FORCEINLINE FCsBlockchainCommandInfo& operator=(const FCsBlockchainCommandInfo& B)
	{
		Command = B.Command;

		Arguments.Reset();

		for (const FCsBlockchainCommandArgument& Arg : B.Arguments)
		{
			Arguments.Add(Arg);
		}

		Payload_bool = B.Payload_bool;
		Payload_int32 = B.Payload_int32;
		Payload_float = B.Payload_float;
		Payload_FString = B.Payload_FString;
		Payload_ptr = B.Payload_ptr;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsBlockchainCommandInfo& B) const
	{
		if (Command != B.Command)
			return false;

		if (Arguments.Num() != B.Arguments.Num())
			return false;

		const int32 Count = Arguments.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			if (Arguments[I] != B.Arguments[I])
				return false;
		}

		if (Payload_bool != B.Payload_bool)
			return false;
		if (Payload_int32 != B.Payload_int32)
			return false;
		if (Payload_float != B.Payload_float)
			return false;
		if (Payload_FString != B.Payload_FString)
			return false;
		if (Payload_ptr != B.Payload_ptr)
			return false;
		return true;
	}

	FORCEINLINE bool operator!=(const FCsBlockchainCommandInfo& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE void Set(const FECsBlockchainCommand& InCommand)
	{
		Command = InCommand;
	}

	FORCEINLINE void Set(const FECsBlockchainCommand& InCommand, const TArray<FCsBlockchainCommandArgument> &Args)
	{
		Command = InCommand;
		SetArguments(Args);
	}

	FORCEINLINE void Set(const FECsBlockchainCommand& InCommand, const TArray<FCsBlockchainCommandArgument> &Args, const bool &Payload)
	{
		Command = InCommand;
		SetArguments(Args);
		Payload_bool = Payload;
	}

	FORCEINLINE void Set(const FECsBlockchainCommand& InCommand, const TArray<FCsBlockchainCommandArgument> &Args, const int32 &Payload)
	{
		Command = InCommand;
		SetArguments(Args);
		Payload_int32 = Payload;
	}

	FORCEINLINE void Set(const FECsBlockchainCommand& InCommand, const TArray<FCsBlockchainCommandArgument> &Args, const float &Payload)
	{
		Command = InCommand;
		SetArguments(Args);
		Payload_float = Payload;
	}

	FORCEINLINE void Set(const FECsBlockchainCommand& InCommand, const TArray<FCsBlockchainCommandArgument> &Args, const FString &Payload)
	{
		Command = InCommand;
		SetArguments(Args);
		Payload_FString = Payload;
	}

	FORCEINLINE void Set(const FECsBlockchainCommand& InCommand, const TArray<FCsBlockchainCommandArgument> &Args, const FECsBlockchainContract &Payload)
	{
		Command = InCommand;
		SetArguments(Args);
		Payload_Contract = Payload;
	}

	FORCEINLINE void Set(const FECsBlockchainCommand& InCommand, const TArray<FCsBlockchainCommandArgument> &Args, const FCsBlockchainContractFunctionPayload &Payload)
	{
		Command = InCommand;
		SetArguments(Args);
		Payload_ContractFunction = Payload;
	}

	FORCEINLINE void Set(const FECsBlockchainCommand& InCommand, const TArray<FCsBlockchainCommandArgument> &Args, void* Payload)
	{
		Command = InCommand;
		SetArguments(Args);
		Payload_ptr = Payload;
	}

	FORCEINLINE void Reset()
	{
		Arguments.Reset();

		Payload_bool = false;
		Payload_int32 = 0;
		Payload_float = 0.0f;
		Payload_FString = ECsCached::Str::Empty;
		Payload_ptr = nullptr;
	}
};

// Cache
#pragma region

namespace ECsBlockchainCached
{
	namespace Var
	{
		const TArray<FCsBlockchainContractFunctionArgument> ContractFunctionEmptyArgs;
	};
}

#pragma endregion Cache

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsBlockchain_PrivateChainCreated, const int32&, Index);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsBlockchain_PrivateChainStarted, const int32&, Index);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsBlockchain_ConsoleOpened, const int32&, Index);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsBlockchain_CommandCompleted, const FECsBlockchainCommand&, Command);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsBlockchain_AccountCreated, const FString&, Nickname);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsBlockchain_CoinbaseSet, const FString&, Nickname);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsBlockchain_ContractFunctionCompleted, const FECsBlockchainCommand&, Command, const FECsBlockchainContractFunction&, Function);

#define CS_BLOCKCHAIN_SINGLE_NODE_INDEX 0

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

	virtual void Initialize();
	virtual void CleanUp();

private:
	// Singleton data
	static UCsBlockchain* s_blockchainSingleton;
	static bool s_bBlockchainHasShutdown;

#pragma endregion Singleton

public:

	DECLARE_MULTICAST_DELEGATE_OneParam(FPrivateChainCreated, const int32&);
	DECLARE_MULTICAST_DELEGATE_OneParam(FPrivateChainStarted, const int32&);
	DECLARE_MULTICAST_DELEGATE_OneParam(FConsoleOpened, const int32&);
	DECLARE_MULTICAST_DELEGATE_OneParam(FCommandCompleted, const FECsBlockchainCommand&);
	DECLARE_MULTICAST_DELEGATE_OneParam(FAccountCreated, class ICsBlockchainAccount*);
	DECLARE_MULTICAST_DELEGATE_OneParam(FCoinbaseSet, class ICsBlockchainAccount*);
	DECLARE_MULTICAST_DELEGATE_TwoParams(FContractFunctionCompleted, const FECsBlockchainContract&, const FECsBlockchainContractFunction&);

	FPrivateChainCreated PrivateChainCreated_Event;
#if WITH_EDITORONLY_DATA
	UPROPERTY(BlueprintAssignable, Category = "Blockchain")
	FBindableDynEvent_CsBlockchain_PrivateChainCreated PrivateChainCreated_ScriptEvent;
#endif // #if WITH_EDITORONLY_DATA

	FPrivateChainStarted PrivateChainStarted_Event;
#if WITH_EDITORONLY_DATA
	UPROPERTY(BlueprintAssignable, Category = "Blockchain")
	FBindableDynEvent_CsBlockchain_PrivateChainStarted PrivateChainStarted_ScriptEvent;
#endif // #if WITH_EDITORONLY_DATA

	FConsoleOpened ConsoleOpened_Event;
#if WITH_EDITORONLY_DATA
	UPROPERTY(BlueprintAssignable, Category = "Blockchain")
	FBindableDynEvent_CsBlockchain_ConsoleOpened ConsoleOpened_ScriptEvent;
#endif // #if WITH_EDITORONLY_DATA

	FCommandCompleted CommandCompleted_Event;
#if WITH_EDITORONLY_DATA
	UPROPERTY(BlueprintAssignable, Category = "Blockchain")
	FBindableDynEvent_CsBlockchain_CommandCompleted CommandCompleted_ScriptEvent;
#endif // #if WITH_EDITORONLY_DATA

	FAccountCreated AccountCreated_Event;
#if WITH_EDITORONLY_DATA
	UPROPERTY(BlueprintAssignable, Category = "Blockchain")
	FBindableDynEvent_CsBlockchain_AccountCreated AccountCreated_ScriptEvent;
#endif // #if WITH_EDITORONLY_DATA

	FCoinbaseSet CoinbaseSet_Event;
#if WITH_EDITORONLY_DATA
	UPROPERTY(BlueprintAssignable, Category = "Blockchain")
	FBindableDynEvent_CsBlockchain_CoinbaseSet CoinbaseSet_ScriptEvent;
#endif // #if WITH_EDITORONLY_DATA

	FContractFunctionCompleted ContractFunctionCompleted_Event;
#if WITH_EDITORONLY_DATA
	UPROPERTY(BlueprintAssignable, Category = "Blockchain")
	FBindableDynEvent_CsBlockchain_ContractFunctionCompleted ContractFunctionCompleted_ScriptEvent;
#endif // #if WITH_EDITORONLY_DATA

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blockchain")
	ECsBlockchainType StorageType;

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

	TMap<ECsBlockchainProcessType, UCsProcess*> Processes;

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

	virtual void RunCommand(const int32 &ConsoleIndex, const FString &Command);
	UFUNCTION(BlueprintCallable, Category = "Blockchain")
	void RunCommandEX(const int32 &ConsoleIndex, const FString &Command);
	UFUNCTION(BlueprintCallable, Category = "Blockchain")
	virtual void RunCommand(const int32 &ConsoleIndex, const FECsBlockchainCommand &Command, TArray<FCsBlockchainCommandArgument> &Arguments);

	UFUNCTION(BlueprintCallable, Category = "Blockchain")
	virtual void SetProcess(const ECsBlockchainProcessType &ProcessType, const int32 &Index, class UCsProcess* Process);
	
	UFUNCTION(BlueprintCallable, Category = "Blockchain")
	virtual class UCsProcess* GetProcess(const ECsBlockchainProcessType &ProcessType, const int32 &Index);

	UFUNCTION(BlueprintCallable, Category = "Blockchain")
	virtual void StartProcess(const ECsBlockchainProcessType &ProcessType, const int32 &Index, const FCsBlockchainProcessStartInfo &StartInfo);

	UFUNCTION(BlueprintCallable, Category = "Blockchain")
	virtual void StopProcess(const ECsBlockchainProcessType &ProcessType, const int32 &Index);

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

	UFUNCTION(BlueprintCallable, Category = "Blockchain")
	virtual void ListAccounts();

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
public interface ICgBlockchain
{

	bool IsConsoleOpen{ get; set; }
	bool IsMining{ get; set; }
}
*/
// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Blockchain/CsBlockchain.h"
#include "Blockchain/Ethereum/CsEthereumContract.h"
#include "Blockchain/Ethereum/CsEthereumKeystore.h"
#include "Types/CsTypes_Coroutine.h"
#include "CsEthereum.generated.h"

USTRUCT(BlueprintType)
struct FCsEthereumAccountInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ethereum")
	FString Nickname;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ethereum")
	FString Passphrase;

	FCsEthereumAccountInfo(){}
	FCsEthereumAccountInfo(const FString &InNickname, const FString &InPassphrase)
	{
		Nickname = InNickname;
		Passphrase = InPassphrase;
	}

	~FCsEthereumAccountInfo(){}

	FCsEthereumAccountInfo& operator=(const FCsEthereumAccountInfo& B)
	{
		Nickname = B.Nickname;
		Passphrase = B.Passphrase;
		return *this;
	}

	bool operator==(const FCsEthereumAccountInfo& B) const
	{
		return Nickname == B.Nickname && Passphrase == B.Passphrase;
	}

	bool operator!=(const FCsEthereumAccountInfo& B) const
	{
		return !(*this == B);
	}

	void Set(const FString &InNickname, const FString &InPassphrase)
	{
		Nickname = InNickname;
		Passphrase = InPassphrase;
	}
};

// Enums
#pragma region

namespace ECsEthereumCommand
{
	extern const FECsBlockchainCommand InitBlockchain;
	extern const FECsBlockchainCommand SetDataDirectory;
	extern const FECsBlockchainCommand AttachToConsole;
	extern const FECsBlockchainCommand ExitConsole;
	extern const FECsBlockchainCommand NewAccount;
	extern const FECsBlockchainCommand UnlockAccount;
	extern const FECsBlockchainCommand ListAccounts;
	extern const FECsBlockchainCommand SetEtherbase;
	extern const FECsBlockchainCommand GetBalanceEther;
	extern const FECsBlockchainCommand GetBalanceWei;
	extern const FECsBlockchainCommand StartMiner;
	extern const FECsBlockchainCommand StopMiner;
	extern const FECsBlockchainCommand DeployContract;
	extern const FECsBlockchainCommand LoadScript;
	extern const FECsBlockchainCommand CreateContractABI;
	extern const FECsBlockchainCommand CreateContractInstance;
	extern const FECsBlockchainCommand RunContractConstantFunction;
	extern const FECsBlockchainCommand RunContractStateChangeFunction;
	extern const FECsBlockchainCommand GetGasEstimate;
	extern const FECsBlockchainCommand GetTransactionReceipt;

	extern const FECsBlockchainCommand MAX;
}

namespace ECsEthereumRoutine
{
	enum Type
	{
		StartPrivateChain_Internal,
		CreateKeystore_Internal,
		SetupAccount_Internal,
		BringBalanceToThreshold_Internal,
		DeployContract_Internal,
		SetupContract_Internal,
		RunContractStateChangeFunction_Internal,
		CheckTransactionHasBeenMined_Internal,
		ECsEthereumRoutine_MAX,
	};
}

namespace ECsEthereumRoutine
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_TwoParams TCsString;

	namespace Str
	{
		extern const TCsString StartPrivateChain_Internal;
		extern const TCsString CreateKeystore_Internal;
		extern const TCsString SetupAccount_Internal;
		extern const TCsString BringBalanceToThreshold_Internal;
		extern const TCsString DeployContract_Internal;
		extern const TCsString SetupContract_Internal;
		extern const TCsString RunContractStateChangeFunction_Internal;
		extern const TCsString CheckTransactionHasBeenMined_Internal;
	}

	namespace Ref
	{
		extern const Type StartPrivateChain_Internal;
		extern const Type CreateKeystore_Internal;
		extern const Type SetupAccount_Internal;
		extern const Type BringBalanceToThreshold_Internal;
		extern const Type DeployContract_Internal;
		extern const Type SetupContract_Internal;
		extern const Type RunContractStateChangeFunction_Internal;
		extern const Type CheckTransactionHasBeenMined_Internal;
		extern const Type ECsEthereumRoutine_MAX;
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		if (EType == Type::StartPrivateChain_Internal) { return Str::StartPrivateChain_Internal.Value; }
		if (EType == Type::CreateKeystore_Internal) { return Str::CreateKeystore_Internal.Value; }
		if (EType == Type::SetupAccount_Internal) { return Str::SetupAccount_Internal.Value; }
		if (EType == Type::BringBalanceToThreshold_Internal) { return Str::BringBalanceToThreshold_Internal.Value; }
		if (EType == Type::DeployContract_Internal) { return Str::DeployContract_Internal.Value; }
		if (EType == Type::SetupContract_Internal) { return Str::SetupContract_Internal.Value; }
		if (EType == Type::RunContractStateChangeFunction_Internal) { return Str::RunContractStateChangeFunction_Internal.Value; }
		if (EType == Type::CheckTransactionHasBeenMined_Internal) { return Str::CheckTransactionHasBeenMined_Internal.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE const Type& ToType(const FString &String)
	{
		if (String == Str::StartPrivateChain_Internal) { return Ref::StartPrivateChain_Internal; }
		if (String == Str::CreateKeystore_Internal) { return Ref::CreateKeystore_Internal; }
		if (String == Str::SetupAccount_Internal) { return Ref::SetupAccount_Internal; }
		if (String == Str::BringBalanceToThreshold_Internal) { return Ref::BringBalanceToThreshold_Internal; }
		if (String == Str::DeployContract_Internal) { return Ref::DeployContract_Internal; }
		if (String == Str::SetupContract_Internal) { return Ref::SetupContract_Internal; }
		if (String == Str::RunContractStateChangeFunction_Internal) { return Ref::RunContractStateChangeFunction_Internal; }
		if (String == Str::CheckTransactionHasBeenMined_Internal) { return Ref::CheckTransactionHasBeenMined_Internal; }
		return Ref::ECsEthereumRoutine_MAX;
	}
}

#define ECS_ETHEREUM_ROUTINE_MAX (uint8)ECsEthereumRoutine::ECsEthereumRoutine_MAX
typedef ECsEthereumRoutine::Type TCsEthereumRoutine;

#pragma endregion Enums

USTRUCT(BlueprintType)
struct FECsEthereumJavascript : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

public:
	FECsEthereumJavascript() {}
	FECsEthereumJavascript(const uint8 &InValue, const FString &InName, const FString &InDisplayName) : FECsEnum_uint8(InValue, InName, InDisplayName) {}
	FECsEthereumJavascript(const uint8 &InValue, const FString &InName) : FECsEnum_uint8(InValue, InName) {}
	~FECsEthereumJavascript() {}
};

FORCEINLINE uint32 GetTypeHash(const FECsEthereumJavascript& b)
{
	return GetTypeHash(b.Name) ^ GetTypeHash(b.Value);
}

struct CSCORE_API EMCsEthereumJavascript : public TCsEnumMap<FECsEthereumJavascript, uint8>
{
protected:
	EMCsEthereumJavascript() {}
	EMCsEthereumJavascript(const EMCsEthereumJavascript &) = delete;
	EMCsEthereumJavascript(EMCsEthereumJavascript &&) = delete;
public:
	~EMCsEthereumJavascript() {}
private:
	static EMCsEthereumJavascript* Instance;

public:
	static EMCsEthereumJavascript& Get();
};

USTRUCT(BlueprintType)
struct FCsEthereumJavascriptContractLink
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ethereum")
	FECsBlockchainContract Contract;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ethereum")
	FString Link;

	FCsEthereumJavascriptContractLink(){}
	FCsEthereumJavascriptContractLink(const FECsBlockchainContract &InContract, const FString &InLink)
	{
		Contract = InContract;
		Link = InLink;
	}

	~FCsEthereumJavascriptContractLink(){}

	FCsEthereumJavascriptContractLink& operator=(const FCsEthereumJavascriptContractLink& B)
	{
		Contract = B.Contract;
		Link = B.Link;
		return *this;
	}

	bool operator==(const FCsEthereumJavascriptContractLink& B) const
	{
		return Contract == B.Contract && Link == B.Link;
	}

	bool operator!=(const FCsEthereumJavascriptContractLink& B) const
	{
		return !(*this == B);
	}
};

UCLASS(transient)
class CSCORE_API UCsEthereum : public UCsBlockchain
{
	GENERATED_UCLASS_BODY()

// Singleton
#pragma region
protected:

	virtual void Initialize() override;
	virtual void CleanUp() override;

#pragma endregion Singleton

// Interface
#pragma region

// Paths
#pragma region
public:


	virtual void SetRootDirectory(const FString &Path) override;
	virtual void SetChainDirectory(const FString &Path) override;
	virtual void SetAccountsDirectory(const FString &Path) override;
	virtual void SetContractsDirectory(const FString &Path) override;
	virtual void SetContractsDeployedDirectory(const FString &Path) override;

#pragma endregion Paths

// Process
#pragma region
public:

	virtual void SetConsoleFilename(const FString &Filename) override;
	virtual void SetConsoleDirectory(const FString &Path) override;

#pragma endregion Process

public:

	virtual void Start() override;

	virtual void SetCommand(const FECsBlockchainCommand &Command, const FString &Str) override;
	virtual void RunCommand(const int32 &ConsoleIndex, const FString &Command) override;
	virtual void RunCommand(const int32 &ConsoleIndex, const FECsBlockchainCommand &Command, TArray<FCsBlockchainCommandArgument> &Arguments) override;

	virtual void SetProcess(const TEnumAsByte<ECsBlockchainProcessType::Type> &ProcessType, const int32 &Index, class UCsProcess* Process) override;
	virtual class UCsProcess* GetProcess(const TEnumAsByte<ECsBlockchainProcessType::Type> &ProcessType, const int32 &Index) override;
	virtual void StartProcess(const TEnumAsByte<ECsBlockchainProcessType::Type> &ProcessType, const int32 &Index, const FCsBlockchainProcessStartInfo &StartInfo) override;
	virtual void StopProcess(const TEnumAsByte<ECsBlockchainProcessType::Type> &ProcessType, const int32 &Index) override;

	virtual void OpenRunningInstance() override;
	virtual void CreatePrivateChain() override;

	virtual void StartPrivateChain() override;
	static char StartPrivateChain_Internal(FCsRoutine* r);
	FCsRoutine* StartPrivateChain_Internal_Routine;

	virtual void OpenConsole() override;
	virtual void CloseConsole() override;

// Account
#pragma region
public:

	virtual void LoadAccounts() override;
	virtual void NewAccount(void* Payload) override;
	virtual void UnlockAccount(class ICsBlockchainAccount* IAccount) override;
	virtual void ListAccounts() override;

#pragma endregion Account

// Miner
#pragma region
public:

	virtual void StartMiner() override;
	virtual void StopMiner() override;

#pragma endregion Miner

#pragma endregion Interface

// Routines
#pragma region
public:

	static void AddRoutine(UObject* InBlockchain, struct FCsRoutine* Routine, const uint8 &Type);
	virtual bool AddRoutine_Internal(struct FCsRoutine* Routine, const uint8 &Type);

	static void RemoveRoutine(UObject* InBlockchain, struct FCsRoutine* Routine, const uint8 &Type);
	virtual bool RemoveRoutine_Internal(struct FCsRoutine* Routine, const uint8 &Type);

#pragma endregion Routines

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ethereum")
	FString ConsoleFullPath;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ethereum")
	FString GenesisFilePath;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ethereum")
	FString KeystoreDirectory;

	TMap<FString, FCsEthereumKeystore> Keystores;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ethereum")
	FString ABIDirectory;
protected:
	TMap<FECsBlockchainContract, FString> ABISnippets;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ethereum")
	FString Web3DeployDirectory;
protected:
	TMap<FECsBlockchainContract, FString> Web3DeploySnippets;
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ethereum")
	FString Web3DeployLinkedDirectory;

	TMap<FECsBlockchainContract, FString> Web3DeployLinkedSnippets;
	TMap<FECsBlockchainContract, TArray<FCsEthereumWeb3DeployLink>> Web3DeployLinks;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ethereum")
	FString JavascriptDirectory;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ethereum")
	FString JavascriptLinkedDirectory;

	/* Path for any Javascript */
	TMap<FECsEthereumJavascript, FString> ScriptPaths;
	/* Path for any Contract Javascript functions that need to get procedural updated */
	TMap<FECsBlockchainContract, FString> ScriptLinkedPaths;
	/* Any links, code, and/or information related to a Contract javascript function that needs to get procedurally updated */
	TMap<FECsBlockchainContract, TArray<FCsEthereumJavascriptContractLink>> ScriptContractLinks;

	TMap<FECsBlockchainContract, TMap<FECsBlockchainContractFunction, FCsBlockchainContractFunction>> ContractFunctions;

	bool IsRunningInstanceCloseFlag;

	TMap<FECsBlockchainCommand, FCsProcessMonitorOutputEvent> MonitorOutputEvents;

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ethereum")
	FCsBlockchainCommandInfo CurrentCommandInfo;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ethereum")
	FCsBlockchainCommandOutput CurrentCommandOuput;

	FCsEthereumAccountInfo CurrentAccountInfo;

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ethereum")
	bool CommandFlag;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ethereum")
	bool SetupAccountFlag;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ethereum")
	bool BringBalanceToThresholdFlag;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ethereum")
	bool DeployContractFlag;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ethereum")
	bool LoadContractsFlag;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ethereum")
	bool SetupContractFlag;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ethereum")
	bool RunContractStateChangeFunctionFlag;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ethereum")
	bool TransactionMinedFlag;

public:

	UFUNCTION(BlueprintCallable, Category = "Ethereum")
	virtual void Rebuild();

// Process
#pragma region
public:

	void AddMonitorOutputEvenToProcess(const TEnumAsByte<ECsBlockchainProcessType::Type> &ProcessType, const int32 &Index, const FCsProcessMonitorOutputEvent &Event);
	UFUNCTION(BlueprintCallable, Category = "Ethereum")
	void AddMonitorOutputEvenToProcess(const TEnumAsByte<ECsBlockchainProcessType::Type> &ProcessType, const int32 &Index, const FECsBlockchainCommand& Command);

	virtual void OnCommandCompleted(const FECsBlockchainCommand &Command);
	virtual void OnCommandCompleted(const FString &Name);

	// I/O
#pragma region
public:

	virtual void OnProcessOutputRecieved(const FString &Output);
	virtual void OnProcessExited();
	virtual void OnConsoleOutputRecieved(const FString &Output);
	virtual void OnConsoleExited();

#pragma endregion I/O

#pragma endregion Process

// Accounts
#pragma region
public:

	FString GetKeystoreFilePath(const FString &Address);

	void CreateKeystore(class CsEthereumAccount* Account);
	static char CreateKeystore_Internal(FCsRoutine* r);
	FCsRoutine* CreateKeystore_Internal_Routine;

	void SetCoinbase(class ICsBlockchainAccount* IAccount);
	void GetBalanceEther(class ICsBlockchainAccount* IAccount);

	void SetupAccount(void* Payload);
	static char SetupAccount_Internal(FCsRoutine* r);
	FCsRoutine* SetupAccount_Internal_Routine;

	void BringBalanceToThreshold(class ICsBlockchainAccount* IAccount, const int32 &Threshold);
	static char BringBalanceToThreshold_Internal(FCsRoutine* r);
	FCsRoutine* BringBalanceToThreshold_Internal_Routine;

#pragma endregion Accounts

// Contracct
#pragma region
public:

	void DeployContract(const FECsBlockchainContract &EContract, TArray<FCsBlockchainContractArgument> &Args);
	static char DeployContract_Internal(FCsRoutine* r);
	FCsRoutine* DeployContract_Internal_Routine;

	void LoadContract(const FECsBlockchainContract &EContract, const FECsEthereumJavascript &EScript);
	void CreatedWeb3DeployLinked(const FECsBlockchainContract &EContract);
	void CreatedJavascriptContractLinked(const FECsBlockchainContract &EContract, const FECsEthereumJavascript &EScript);
	void CreateContractABI(const FECsBlockchainContract &EContract);
	void CreateContractInstance(class ICsBlockchainContract* IContract);

	void SetupContract(const FECsBlockchainContract &EContract, const FECsEthereumJavascript &EScript);
	static char SetupContract_Internal(FCsRoutine* r);
	FCsRoutine* SetupContract_Internal_Routine;

	void RunContractConstantFunction(const FECsBlockchainContract &EContract, const FECsBlockchainContractFunction &EFn, const TArray<FCsBlockchainContractFunctionArgument> &Args);

	void RunContractStateChangeFunction(const FECsBlockchainContract &EContract, class ICsBlockchainAccount* IAccount, const FECsBlockchainContractFunction &EFn, TArray<FCsBlockchainContractFunctionArgument> &Args);
	static char RunContractStateChangeFunction_Internal(FCsRoutine* r);
	FCsRoutine* RunContractStateChangeFunction_Internal_Routine;

	void GetGasEstimate(const FECsBlockchainContract &EContract, class ICsBlockchainAccount* IAccount, const FECsBlockchainContractFunction &EFn, const TArray<FCsBlockchainContractFunctionArgument> &Args);

	void GetTransactionReceipt(const FString &TransactionHash);

	void CheckTransactionHasBeenMined(const FString &TransactionHash);
	static char CheckTransactionHasBeenMined_Internal(FCsRoutine* r);
	FCsRoutine* CheckTransactionHasBeenMined_Internal_Routine;

#pragma endregion Contract

public:

	virtual void LoadScript(const FECsEthereumJavascript &EScript, const FString &Path);
};
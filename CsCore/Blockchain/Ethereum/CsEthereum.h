// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Blockchain/CsBlockchain.h"
#include "Blockchain/Ethereum/CsEthereumContract.h"
#include "Blockchain/Ethereum/CsEthereumKeystore.h"
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
};

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

USTRUCT(BlueprintType)
struct FECsEthereumJavascript : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

public:
	FECsEthereumJavascript() {}
	FECsEthereumJavascript(const uint8 &InValue, const FString &InName) : FECsEnum_uint8(InValue, InName) {}
	~FECsEthereumJavascript() {}
};

FORCEINLINE uint32 GetTypeHash(const FECsEthereumJavascript& b)
{
	return FCrc::MemCrc_DEPRECATED(&b, sizeof(FECsEthereumJavascript));
}

struct EMCsEthereumJavascript : public TCsEnumMap<FECsEthereumJavascript, uint8>
{
protected:
	EMCsEthereumJavascript() {}
	EMCsEthereumJavascript(const EMCsEthereumJavascript &) = delete;
	EMCsEthereumJavascript(EMCsEthereumJavascript &&) = delete;
public:
	~EMCsEthereumJavascript() {}

	static EMCsEthereumJavascript& Get()
	{
		static EMCsEthereumJavascript Instance;
		return Instance;
	}
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

	virtual void OpenConsole() override;
	virtual void CloseConsole() override;

// Account
#pragma region
public:

	virtual void LoadAccounts() override;
	virtual void NewAccount(void* Payload) override;
	virtual void UnlockAccount(class ICsBlockchainAccount* IAccount) override;

#pragma endregion Account

// Miner
#pragma region
public:

	virtual void StartMiner() override;
	virtual void StopMiner() override;

#pragma endregion Miner

#pragma endregion Interface

public:

	FString ConsoleFullPath;
	FString GenesisFilePath;
	FString KeystoreDirectory;

	TMap<FString, FCsEthereumKeystore> Keystores;

	FString ABIDirectory;
protected:
	TMap<FECsBlockchainContract, FString> ABISnippets;

public:
	FString Web3DeployDirectory;
protected:
	TMap<FECsBlockchainContract, FString> Web3DeploySnippets;
public:
	FString Web3DeployLinkedDirectory;
protected:
	TMap<FECsBlockchainContract, FString> Web3DepolyLinkedSnippets;
	TMap<FECsBlockchainContract, TArray<FCsEthereumWeb3DeployLink>> Web3DeployLinks;

public:
	FString JavascriptDirectory;
	FString JavascriptLinkedDirectory;

protected:
	/* Path for any Javascript */
	TMap<FECsEthereumJavascript, FString> ScriptPaths;
	/* Path for any Contract Javascript functions that need to get procedural updated */
	TMap<FECsBlockchainContract, FString> ScriptLinkedPaths;
	/* Any links, code, and/or information related to a Contract javascript function that needs to get procedurally updated */
	TMap<FECsBlockchainContract, TArray<FCsEthereumJavascriptContractLink>> ScriptContractLinks;

	TMap<FECsBlockchainContract, TMap<FECsBlockchainContractFunction, FCsBlockchainContractFunction>> ContractFunctions;

	TMap<FECsBlockchainCommand, FCsProcessMonitorOutputEvent> MonitorOutputEvents;

	FCsBlockchainCommandInfo CurrentCommandInfo;
	void* CurrentCommandOuput;

	bool CommandFlag;
	bool SetupAccountFlag;
	bool BringBalanceToThresholdFlag;
	bool DeployContractFlag;
	bool SetupContractFlag;
	bool RunContractStateChangeFunctionFlag;
	bool TransactionMinedFlag;

public:

	UFUNCTION(BlueprintCallable, Category = "Ethereum")
	virtual void Rebuild();

// Process
#pragma region
public:

	void AddMonitorOutputEvenToProcess(const TEnumAsByte<ECsBlockchainProcessType::Type> &ProcessType, const int32 &Index, const FCsProcessMonitorOutputEvent &E);
	UFUNCTION(BlueprintCallable, Category = "Ethereum")
	void AddMonitorOutputEvenToProcess(const TEnumAsByte<ECsBlockchainProcessType::Type> &ProcessType, const int32 &Index, const FECsBlockchainCommand& Command);

	virtual void OnCommandCompleted(const FECsBlockchainCommand &Command);
	virtual void OnCommandCompleted(const FString &Name);

	// I/O
#pragma region
public:

	virtual void OnProcessOutputRecieved(const FString &Ouput);
	virtual void OnProcessErrorRecieved(const FString &Output);
	virtual void OnProcessExited(const FString &Output);
	virtual void OnConsoleOutputRecieved(const FString &Output);
	virtual void OnConsoleErrorRecieved(const FString &Output);
	virtual void OnConsoleExited(const FString &Output);

#pragma endregion I/O

#pragma endregion Process
};
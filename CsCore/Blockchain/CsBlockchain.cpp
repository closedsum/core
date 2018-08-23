// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Blockchain/CsBlockchain.h"
#include "CsCore.h"

#include "Blockchain/CsBlockchainAccount.h"
#include "Blockchain/CsBlockchainContract.h"

// static initializations
UCsBlockchain* UCsBlockchain::s_blockchainSingleton;
bool UCsBlockchain::s_bBlockchainHasShutdown = false;

// Enums
#pragma region

// BlockchainType
EMCsBlockchainType* EMCsBlockchainType::Instance;

EMCsBlockchainType& EMCsBlockchainType::Get()
{
	if (!Instance)
		Instance = new EMCsBlockchainType();
	return *Instance;
}

namespace NCsBlockchainType
{
	namespace Ref
	{
		CSCORE_API const Type PrivateSingleNode = EMCsBlockchainType::Get().Add(Type::PrivateSingleNode, TEXT("PrivateSingleNode"), TEXT("Private Single Node"));
		CSCORE_API const Type Local = EMCsBlockchainType::Get().Add(Type::Local, TEXT("Local"));
		CSCORE_API const Type Server = EMCsBlockchainType::Get().Add(Type::Server, TEXT("Server"));
		CSCORE_API const Type ECsBlockchainType_MAX = EMCsBlockchainType::Get().Add(Type::ECsBlockchainType_MAX, TEXT("ECsBlockchainType_MAX"), TEXT("MAX"));
	}
}

// BlockchainProcessType
EMCsBlockchainProcessType* EMCsBlockchainProcessType::Instance;

EMCsBlockchainProcessType& EMCsBlockchainProcessType::Get()
{
	if (!Instance)
		Instance = new EMCsBlockchainProcessType();
	return *Instance;
}

namespace NCsBlockchainProcessType
{
	namespace Ref
	{
		CSCORE_API const Type RunningInstance = EMCsBlockchainProcessType::Get().Add(Type::RunningInstance, TEXT("RunningInstance"), TEXT("Running Instance"));
		CSCORE_API const Type Console = EMCsBlockchainProcessType::Get().Add(Type::Console, TEXT("Console"));
		CSCORE_API const Type ECsBlockchainProcessType_MAX = EMCsBlockchainProcessType::Get().Add(Type::ECsBlockchainProcessType_MAX, TEXT("ECsBlockchainProcessType_MAX"), TEXT("MAX"));
	}
}

#pragma endregion Enums

UCsBlockchain::UCsBlockchain(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

// Singleton
#pragma region

/*static*/ UCsBlockchain* UCsBlockchain::Get()
{
	if (s_bBlockchainHasShutdown)
		return nullptr;

	return s_blockchainSingleton;
}

/*static*/ void UCsBlockchain::Init(UClass* InSpawnClass)
{
	s_bBlockchainHasShutdown = false;

	if (!s_blockchainSingleton)
	{
		s_blockchainSingleton = NewObject<UCsBlockchain>(GetTransientPackage(), InSpawnClass, TEXT("Blockchain_Singleton"), RF_Transient | RF_Public);
		s_blockchainSingleton->SpawnClass = InSpawnClass;
		s_blockchainSingleton->AddToRoot();
		s_blockchainSingleton->Initialize();
	}
}

/*static*/ void UCsBlockchain::Shutdown()
{
	if (!s_blockchainSingleton)
		return;

	s_blockchainSingleton->CleanUp();
	s_blockchainSingleton->RemoveFromRoot();
	s_blockchainSingleton = nullptr;
}

void UCsBlockchain::Initialize()
{
	for (int32 I = 0; I < EMCsBlockchainProcessType::Get().Num(); ++I)
	{
		Processes.Add(EMCsBlockchainProcessType::Get().GetEnumAt(I), nullptr);
	}
}

void UCsBlockchain::CleanUp()
{
	// Processes
	{
		Processes.Reset();
	}
	// Accounts
	{
		TArray<FString> Keys;
		Accounts.GetKeys(Keys);

		const int32 Count = Keys.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			delete Accounts[Keys[I]];
		}
		Accounts.Reset();
	}
	// Contracts
	{
		TArray<FECsBlockchainContract> Keys;
		Contracts.GetKeys(Keys);

		const int32 Count = Keys.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			delete Contracts[Keys[I]];
		}
		Contracts.Reset();
	}
}

#pragma endregion Singleton

// Paths
#pragma region

void UCsBlockchain::SetRootDirectory(const FString &Path){}
void UCsBlockchain::SetChainDirectory(const FString &Path){}
void UCsBlockchain::SetAccountsDirectory(const FString &Path){}
void UCsBlockchain::SetContractsDirectory(const FString &Path){}
void UCsBlockchain::SetContractsDeployedDirectory(const FString &Path){}

#pragma endregion Paths

// Process
#pragma region

void UCsBlockchain::SetConsoleFilename(const FString &Filename){}
void UCsBlockchain::SetConsoleDirectory(const FString &Path){}

#pragma endregion Process

void UCsBlockchain::Start() {}

void UCsBlockchain::SetCommand(const FECsBlockchainCommand &Command, const FString &Str){}
void UCsBlockchain::RunCommand(const int32 &ConsoleIndex, const FString &Command) {}
void UCsBlockchain::RunCommandEX(const int32 &ConsoleIndex, const FString &Command) { RunCommand(ConsoleIndex, Command); }
void UCsBlockchain::RunCommand(const int32 &ConsoleIndex, const FECsBlockchainCommand &Command, TArray<FCsBlockchainCommandArgument> &Arguments){}

void UCsBlockchain::SetProcess(const ECsBlockchainProcessType &ProcessType, const int32 &Index, class UCsProcess* Process){}
UCsProcess* UCsBlockchain::GetProcess(const ECsBlockchainProcessType &ProcessType, const int32 &Index) { return nullptr; }
void UCsBlockchain::StartProcess(const ECsBlockchainProcessType &ProcessType, const int32 &Index, const FCsBlockchainProcessStartInfo &StartInfo){}
void UCsBlockchain::StopProcess(const ECsBlockchainProcessType &ProcessType, const int32 &Index){}

void UCsBlockchain::OpenRunningInstance(){}
void UCsBlockchain::CreatePrivateChain(){}
void UCsBlockchain::StartPrivateChain(){}

void UCsBlockchain::OpenConsole(){}
void UCsBlockchain::CloseConsole(){}

// Account
#pragma region

void UCsBlockchain::LoadAccounts(){}
void UCsBlockchain::NewAccount(void* Payload){}
void UCsBlockchain::UnlockAccount(class ICsBlockchainAccount* IAccount){}
void UCsBlockchain::ListAccounts(){}

#pragma endregion Account

// Miner
#pragma region

void UCsBlockchain::StartMiner(){}
void UCsBlockchain::StopMiner(){}

#pragma endregion Miner
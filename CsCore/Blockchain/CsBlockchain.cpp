// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Blockchain/CsBlockchain.h"
#include "CsCore.h"

// static initializations
UCsBlockchain* UCsBlockchain::s_blockchainSingleton;
bool UCsBlockchain::s_bBlockchainHasShutdown = false;

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
}

void UCsBlockchain::CleanUp()
{
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
void UCsBlockchain::RunCommand(const int32 &ConsoleIndex, const FECsBlockchainCommand &Command, TArray<FCsBlockchainCommandArgument> &Arguments){}
void UCsBlockchain::RunCommand(const int32 &ConsoleIndex, const FString &Command){}
void UCsBlockchain::RunCommandEX(const int32 &ConsoleIndex, const FString &Command) { RunCommand(ConsoleIndex, Command); }

void UCsBlockchain::SetProcess(const TEnumAsByte<ECsBlockchainProcessType::Type> &ProcessType, const int32 &Index, class UCsProcess* Process){}
UCsProcess* UCsBlockchain::GetProcess(const TEnumAsByte<ECsBlockchainProcessType::Type> &ProcessType, const int32 &Index) { return nullptr; }
void UCsBlockchain::StartProcess(const TEnumAsByte<ECsBlockchainProcessType::Type> &ProcessType, const int32 &Index, const FCsBlockchainProcessStartInfo &StartInfo){}
void UCsBlockchain::StopProcess(const TEnumAsByte<ECsBlockchainProcessType::Type> &ProcessType, const int32 &Index){}

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

#pragma endregion Account

// Miner
#pragma region

void UCsBlockchain::StartMiner(){}
void UCsBlockchain::StopMiner(){}

#pragma endregion Miner
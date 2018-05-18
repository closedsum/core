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
		SpawnClass = InSpawnClass;

		s_blockchainSingleton = NewObject<UCsBlockchain>(GetTransientPackage(), SpawnClass, TEXT("Blockchain_Singleton"), RF_Transient | RF_Public);
		s_blockchainSingleton->AddToRoot();
		s_blockchainSingleton->Initialize();
	}
}

/*static*/ void UCsBlockchain::Shutdown()
{
	if (!s_coroutineSchedulerSingleton)
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
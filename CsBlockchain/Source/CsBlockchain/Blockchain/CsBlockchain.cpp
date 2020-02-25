// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Blockchain/CsBlockchain.h"
#include "CsBlockchain.h"

#include "Blockchain/CsGetBlockchain.h"
#include "Blockchain/CsBlockchainAccount.h"
#include "Blockchain/CsBlockchainContract.h"

#if WITH_EDITOR
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Managers/Time/CsGetManagerTime.h"
#endif // #if WITH_EDITOR

// static initializations
UCsBlockchain* UCsBlockchain::s_Instance;
bool UCsBlockchain::s_bShutdown = false;

// Enums
#pragma region

// BlockchainType
namespace NCsBlockchainType
{
	namespace Ref
	{
		CSBLOCKCHAIN_API const Type PrivateSingleNode = EMCsBlockchainType::Get().Add(Type::PrivateSingleNode, TEXT("PrivateSingleNode"), TEXT("Private Single Node"));
		CSBLOCKCHAIN_API const Type Local = EMCsBlockchainType::Get().Add(Type::Local, TEXT("Local"));
		CSBLOCKCHAIN_API const Type Server = EMCsBlockchainType::Get().Add(Type::Server, TEXT("Server"));
		CSBLOCKCHAIN_API const Type ECsBlockchainType_MAX = EMCsBlockchainType::Get().Add(Type::ECsBlockchainType_MAX, TEXT("ECsBlockchainType_MAX"), TEXT("MAX"));
	}
}

// BlockchainProcessType
namespace NCsBlockchainProcessType
{
	namespace Ref
	{
		CSBLOCKCHAIN_API const Type RunningInstance = EMCsBlockchainProcessType::Get().Add(Type::RunningInstance, TEXT("RunningInstance"), TEXT("Running Instance"));
		CSBLOCKCHAIN_API const Type Console = EMCsBlockchainProcessType::Get().Add(Type::Console, TEXT("Console"));
		CSBLOCKCHAIN_API const Type ECsBlockchainProcessType_MAX = EMCsBlockchainProcessType::Get().Add(Type::ECsBlockchainProcessType_MAX, TEXT("ECsBlockchainProcessType_MAX"), TEXT("MAX"));
	}
}

#pragma endregion Enums

UCsBlockchain::UCsBlockchain(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

// Singleton
#pragma region

/*static*/ UCsBlockchain* UCsBlockchain::Get(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetBlockchain(InRoot)->GetBlockchain();
#else
	if (s_bShutdown)
		return nullptr;

	return s_Instance;
#endif // #if WITH_EDITOR
}

/*static*/ void UCsBlockchain::Init(UObject* InRoot, UClass* BlockchainClass)
{
#if WITH_EDITOR
	ICsGetBlockchain* GetBlockchain = Get_GetBlockchain(InRoot);

	UCsBlockchain* Blockchain = NewObject<UCsBlockchain>(InRoot, BlockchainClass, TEXT("Blockchain_Singleton"), RF_Transient | RF_Public);

	GetBlockchain->SetBlockchain(Blockchain);

	Blockchain->SetMyRoot(InRoot);
	Blockchain->Initialize();
#else
	s_bShutdown = false;

	if (!s_Instance)
	{
		s_Instance = NewObject<UCsBlockchain>(GetTransientPackage(), BlockchainClass, TEXT("Blockchain_Singleton"), RF_Transient | RF_Public);
		s_Instance->AddToRoot();
		s_Instance->Initialize();
	}
#endif // #if WITH_EDITOR
}

/*static*/ void UCsBlockchain::Shutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetBlockchain* GetBlockchain = Get_GetBlockchain(InRoot);
	UCsBlockchain* Blockchain		= GetBlockchain->GetBlockchain();
	Blockchain->CleanUp();

	GetBlockchain->SetBlockchain(nullptr);
#else
	if (!s_bShutdown)
		return;

	s_Instance->CleanUp();
	s_Instance->RemoveFromRoot();
	s_Instance = nullptr;
#endif // #if WITH_EDITOR
}

#if WITH_EDITOR

/*static*/ ICsGetBlockchain* UCsBlockchain::Get_GetBlockchain(UObject* InRoot)
{
	checkf(InRoot, TEXT("UCsBlockchain::Get_GetBlockchain: InRoot is NULL."));

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("UCsBlockchain::Get_GetBlockchain: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("UCsBlockchain::Get_GetBlockchain: Manager_Singleton is NULL."));

	ICsGetBlockchain* GetBlockchain = Cast<ICsGetBlockchain>(Manager_Singleton);

	checkf(GetBlockchain, TEXT("UCsBlockchain::Get_GetBlockchain: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsGetBlockchain."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

	return GetBlockchain;
}

#endif // #if WITH_EDITOR

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
// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Coordinators/ConsoleCommand/CsCoordinator_ConsoleCommand.h"
#include "CsCore.h"

// Managers
#include "Managers/ConsoleCommand/CsManager_ConsoleCommand.h"

#if WITH_EDITOR
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Coordinators/ConsoleCommand/CsGetCoordinatorConsoleCommand.h"

#include "Engine/World.h"
#include "Engine/Engine.h"

#include "GameFramework/GameStateBase.h"
#endif // #if WITH_EDITOR

// static initializations
UCsCoordinator_ConsoleCommand* UCsCoordinator_ConsoleCommand::s_Instance;
bool UCsCoordinator_ConsoleCommand::s_bShutdown = false;

UCsCoordinator_ConsoleCommand::UCsCoordinator_ConsoleCommand(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

// Singleton
#pragma region

#if WITH_EDITOR
/*static*/ UCsCoordinator_ConsoleCommand* UCsCoordinator_ConsoleCommand::Get(UObject* InRoot /*=nullptr*/)
{
	return Get_GetCoordinatorConsoleCommand(InRoot)->GetCoordinator_ConsoleCommand();
}
#endif // #if WITH_EDITOR

#if WITH_EDITOR
/*static*/ bool UCsCoordinator_ConsoleCommand::IsValid(UObject* InRoot /*=nullptr*/)
{
	return Get_GetCoordinatorConsoleCommand(InRoot)->GetCoordinator_ConsoleCommand() != nullptr;
}
#endif // #if WITH_EDITOR

/*static*/ void UCsCoordinator_ConsoleCommand::Init(UObject* InRoot)
{
#if WITH_EDITOR
	ICsGetCoordinatorConsoleCommand* GetCoordinatorConsoleCommand = Get_GetCoordinatorConsoleCommand(InRoot);

	UCsCoordinator_ConsoleCommand* Coordinator_ConsoleCommand = GetCoordinatorConsoleCommand->GetCoordinator_ConsoleCommand();

	if (!Coordinator_ConsoleCommand)
	{
		Coordinator_ConsoleCommand = NewObject<UCsCoordinator_ConsoleCommand>(InRoot, UCsCoordinator_ConsoleCommand::StaticClass(), TEXT("Coorindator_ConsoleCommand_Singleton"), RF_Transient | RF_Public);

		GetCoordinatorConsoleCommand->SetCoordinator_ConsoleCommand(Coordinator_ConsoleCommand);

		Coordinator_ConsoleCommand->SetMyRoot(InRoot);
		Coordinator_ConsoleCommand->Initialize();
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsCoordinator_ConsoleCommand::Init: Init has already been called."));
	}
#else
	s_bShutdown = false;

	if (!s_Instance)
	{
		s_Instance = NewObject<UCsCoordinator_ConsoleCommand>(GetTransientPackage(), UCsCoordinator_ConsoleCommand::StaticClass(), TEXT("Coorindator_ConsoleCommand_Singleton"), RF_Transient | RF_Public);
		s_Instance->AddToRoot();
		s_Instance->SetMyRoot(InRoot);
		s_Instance->Initialize();
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsCoordinator_ConsoleCommand::Init: Init has already been called."));
	}
#endif // #if WITH_EDITOR
}

/*static*/ void UCsCoordinator_ConsoleCommand::Shutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetCoordinatorConsoleCommand* GetCoordinatorConsoleCommand = Get_GetCoordinatorConsoleCommand(InRoot);
	UCsCoordinator_ConsoleCommand* Coordinator_ConsoleCommand     = GetCoordinatorConsoleCommand->GetCoordinator_ConsoleCommand();
	Coordinator_ConsoleCommand->CleanUp();

	GetCoordinatorConsoleCommand->SetCoordinator_ConsoleCommand(nullptr);
#else
	if (!s_Instance)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsCoordinator_ConsoleCommand::Shutdown: Coorindator has already been shutdown."));
		return;
	}

	s_Instance->CleanUp();
	s_Instance->RemoveFromRoot();
	s_Instance = nullptr;
	s_bShutdown = true;
#endif // #if WITH_EDITOR
}

/*static*/ bool UCsCoordinator_ConsoleCommand::HasShutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetCoordinatorConsoleCommand(InRoot)->GetCoordinator_ConsoleCommand() == nullptr;
#else
	return s_bShutdown;
#endif // #if WITH_EDITOR
}

#if WITH_EDITOR

/*static*/ ICsGetCoordinatorConsoleCommand* UCsCoordinator_ConsoleCommand::Get_GetCoordinatorConsoleCommand(UObject* InRoot)
{
	checkf(InRoot, TEXT("UCsCoordinator_ConsoleCommand::Get_GetCoordinatorConsoleCommand: InRoot is NULL."));

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("UCsCoordinator_ConsoleCommand::Get_GetCoordinatorConsoleCommand: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("UCsCoordinator_ConsoleCommand::Get_GetCoordinatorConsoleCommand: Manager_Singleton is NULL."));

	ICsGetCoordinatorConsoleCommand* GetCoorindatorGameEvent = Cast<ICsGetCoordinatorConsoleCommand>(Manager_Singleton);

	checkf(GetCoorindatorGameEvent, TEXT("UCsCoordinator_ConsoleCommand::Get_GetCoordinatorConsoleCommand: Manager_Singleton: %s with Class: %s does NOT implement interface: ICGetCoordinatorConsoleCommand."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

	return GetCoorindatorGameEvent;
}

/*static*/ ICsGetCoordinatorConsoleCommand* UCsCoordinator_ConsoleCommand::GetSafe_GetCoordinatorConsoleCommand(UObject* Object)
{
	if (!Object)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsStatusEffectCoordinator::GetSafe_GetCoordinatorConsoleCommand: Object is NULL."));
		return nullptr;
	}

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(Object);

	if (!GetManagerSingleton)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Damage::GetSafe_GetCoordinatorConsoleCommand: Object: %s does NOT implement the interface: ICsGetManagerSingleton."), *(Object->GetName()));
		return nullptr;
	}

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	if (!Manager_Singleton)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Damage::GetSafe_GetCoordinatorConsoleCommand: Failed to get object of type: UCsManager_Singleton from Object: %s."), *(Object->GetName()));
		return nullptr;
	}

	return Cast<ICsGetCoordinatorConsoleCommand>(Manager_Singleton);
}

/*static*/ UCsCoordinator_ConsoleCommand* UCsCoordinator_ConsoleCommand::GetSafe(UObject* Object)
{
	if (ICsGetCoordinatorConsoleCommand* GetCoordinatorConsoleCommand = GetSafe_GetCoordinatorConsoleCommand(Object))
		return GetCoordinatorConsoleCommand->GetCoordinator_ConsoleCommand();
	return nullptr;
}

/*static*/ UCsCoordinator_ConsoleCommand* UCsCoordinator_ConsoleCommand::GetFromWorldContextObject(const UObject* WorldContextObject)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		// Game State
		if (UCsCoordinator_ConsoleCommand* Coordinator = GetSafe(World->GetGameInstance()))
			return Coordinator;

		UE_LOG(LogCs, Warning, TEXT("UCsCoordinator_ConsoleCommand::GetFromWorldContextObject: Failed to find Coordinator of type UCsCoordinator_ConsoleCommand from GameInstance."));

		return nullptr;
	}
	else
	{
		return nullptr;
	}
}

#endif // #if WITH_EDITOR

void UCsCoordinator_ConsoleCommand::Initialize()
{
	bInitialized = true;
}

/*static*/ bool UCsCoordinator_ConsoleCommand::HasInitialized(UObject* InRoot)
{
	if (!HasShutdown(InRoot))
		return Get(InRoot)->bInitialized;
	return false;
}

void UCsCoordinator_ConsoleCommand::CleanUp()
{
	bInitialized = false;
}

	// Root
#pragma region

void UCsCoordinator_ConsoleCommand::SetMyRoot(UObject* InRoot)
{
	MyRoot = InRoot;
}

#pragma endregion Root

#pragma endregion Singleton

bool UCsCoordinator_ConsoleCommand::Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Out /*=*GLog*/)
{
	typedef NCsConsoleCommand::NManager::FHandle HandleType;
	typedef NCsConsoleCommand::NManager::IManager ManagerType;

	for (TPair<HandleType, ManagerType*>& Pair : ManagerMap)
	{
		ManagerType* Manager = Pair.Value;

		if (Manager->Exec(InWorld, Cmd, Out))
			return true;
	}
	return false;
}

#define HandleType NCsConsoleCommand::NManager::FHandle
#define ManagerType NCsConsoleCommand::NManager::IManager
HandleType UCsCoordinator_ConsoleCommand::AddManager(ManagerType* Manager)
{
	HandleType Handle;
	Handle.New();

	ManagerMap.Add(Handle, Manager);

	return Handle;
}
#undef HandleType
#undef ManagerType

#define HandleType NCsConsoleCommand::NManager::FHandle
#define ManagerType NCsConsoleCommand::NManager::IManager
void UCsCoordinator_ConsoleCommand::OnDeconstructManager(ManagerType* Manager, const HandleType& Handle)
{
#undef HandleType
#undef ManagerType

#if WITH_EDITOR
	if (this)
#endif // #if WITH_EDITOR
	{
		RemoveManager(Handle);
	}
}

#define HandleType NCsConsoleCommand::NManager::FHandle
void UCsCoordinator_ConsoleCommand::RemoveManager(const HandleType& Handle)
{
#undef HandleType
	ManagerMap.Remove(Handle);
}
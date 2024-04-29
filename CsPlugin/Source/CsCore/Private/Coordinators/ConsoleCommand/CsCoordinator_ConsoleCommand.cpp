// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Coordinators/ConsoleCommand/CsCoordinator_ConsoleCommand.h"
#include "CsCore.h"

// Types
#include "CsMacro_Misc.h"
// Managers
#include "Managers/ConsoleCommand/CsManager_ConsoleCommand.h"
// Package
#include "UObject/Package.h"

#if WITH_EDITOR
// Library
#include "Game/CsLibrary_GameInstance.h"
// Managers
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Coordinators/ConsoleCommand/CsGetCoordinatorConsoleCommand.h"

#include "Engine/World.h"

#include "GameFramework/GameStateBase.h"
#endif // #if WITH_EDITOR

// Cached
#pragma region

namespace NCsCoordinatorConsoleCommand
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsCoordinator_ConsoleCommand, GetFromWorldContextObject);
		}
	}
}

#pragma endregion Cached

// static initializations
UCsCoordinator_ConsoleCommand* UCsCoordinator_ConsoleCommand::s_Instance;
bool UCsCoordinator_ConsoleCommand::s_bShutdown = false;

UCsCoordinator_ConsoleCommand::UCsCoordinator_ConsoleCommand(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

#define USING_NS_CACHED using namespace NCsCoordinatorConsoleCommand::NCached;
#define SET_CONTEXT(__FunctionName) using namespace NCsCoordinatorConsoleCommand::NCached; \
	const FString& Context = Str::__FunctionName
#define GameInstanceLibrary NCsGameInstance::FLibrary

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
	SET_CONTEXT(GetFromWorldContextObject);

	if (UObject* GameInstance = GameInstanceLibrary::GetSafeAsObject(WorldContextObject))
	{
		// Game State
		if (UCsCoordinator_ConsoleCommand* Coordinator = GetSafe(GameInstance))
			return Coordinator;

		UE_LOG(LogCs, Warning, TEXT("%s: Failed to find Coordinator of type UCsCoordinator_ConsoleCommand from GameInstance."), *Context);

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

	// TODO: HACK: Need look into why this needs to be checked
	if (this)
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

void UCsCoordinator_ConsoleCommand::GetCategories(TArray<FString>& OutCategories)
{
	typedef NCsConsoleCommand::NManager::FHandle HandleType;
	typedef NCsConsoleCommand::NManager::IManager ManagerType;

	OutCategories.Reset(ManagerMap.Num());

	for (TPair<HandleType, ManagerType*>& Pair : ManagerMap)
	{
		ManagerType* Manager = Pair.Value;

		OutCategories.Add(Manager->GetCategoryName());
	}
}

#define InfoType NCsConsoleCommand::FInfo
const TArray<InfoType>* UCsCoordinator_ConsoleCommand::GetConsoleCommandInfos(const FString& Category)
{
#undef InfoType

	typedef NCsConsoleCommand::NManager::FHandle HandleType;
	typedef NCsConsoleCommand::NManager::IManager ManagerType;

	for (TPair<HandleType, ManagerType*>& Pair : ManagerMap)
	{
		ManagerType* Manager = Pair.Value;

		if (Category == Manager->GetCategoryName())
		{
			return &(Manager->GetCommandInfos());
		}
	}
	return nullptr;
}

#undef USING_NS_CACHED
#undef SET_CONTEXT
#undef GameInstanceLibrary
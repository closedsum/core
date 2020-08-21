// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Coordinators/GameEvent/CsCoordinator_GameEvent.h"
#include "CsCore.h"

// CVar
//#include "Coordinator/CsCVars_StatusEffectCoordinator.h"
// Library
#include "Library/CsLibrary_Common.h"

#if WITH_EDITOR
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Coordinators/GameEvent/CsGetCoordinatorGameEvent.h"

#include "Library/CsLibrary_Common.h"

#include "Classes/Engine/World.h"
#include "Classes/Engine/Engine.h"

#include "GameFramework/GameStateBase.h"
#endif // #if WITH_EDITOR

// Cached
#pragma region

namespace NCsStatusEffectCoordinatorCached
{
	namespace Str
	{
		const FString GetTypeFromEvent = TEXT("UCsStatusEffectCoordinator::GetTypeFromEvent");
		const FString ProcessStatusEffectEvent = TEXT("UCsStatusEffectCoordinator::ProcessStatusEffectEvent");
		const FString ProcessStatusEffectEventContainer = TEXT("UCsStatusEffectCoordinator::ProcessStatusEffectEventContainer");
	}
}

#pragma endregion Cached

// static initializations
UCsCoordinator_GameEvent* UCsCoordinator_GameEvent::s_Instance;
bool UCsCoordinator_GameEvent::s_bShutdown = false;

UCsCoordinator_GameEvent::UCsCoordinator_GameEvent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

// Singleton
#pragma region

/*static*/ UCsCoordinator_GameEvent* UCsCoordinator_GameEvent::Get(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetCoordinatorGameEvent(InRoot)->GetCoordinator_GameEvent();
#else
	if (s_bShutdown)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsCoordinator_GameEvent::Get: Coordinator has already shutdown."));
		return nullptr;
	}
	return s_Instance;
#endif // #if WITH_EDITOR
}

/*static*/ bool UCsCoordinator_GameEvent::IsValid(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetCoordinatorGameEvent(InRoot)->GetCoordinator_GameEvent() != nullptr;
#else
	return s_Instance != nullptr;
#endif // #if WITH_EDITOR
}

/*static*/ void UCsCoordinator_GameEvent::Init(UObject* InRoot, TSubclassOf<UCsCoordinator_GameEvent> CoordinatorGameEventClass, UObject* InOuter /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetCoordinatorGameEvent* GetCoordinatorGameEvent = Get_GetCoordinatorGameEvent(InRoot);

	UCsCoordinator_GameEvent* Coordinator_GameEvent = GetCoordinatorGameEvent->GetCoordinator_GameEvent();

	if (!Coordinator_GameEvent)
	{
		Coordinator_GameEvent = NewObject<UCsCoordinator_GameEvent>(InOuter ? InOuter : InRoot, CoordinatorGameEventClass, TEXT("Coorindator_Game_Event_Singleton"), RF_Transient | RF_Public);

		GetCoordinatorGameEvent->SetCoordinator_GameEvent(Coordinator_GameEvent);

		Coordinator_GameEvent->SetMyRoot(InRoot);
		Coordinator_GameEvent->Initialize();
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsCoordinator_GameEvent::Init: Init has already been called."));
	}
#else
	s_bShutdown = false;

	if (!s_Instance)
	{
		s_Instance = NewObject<UCsCoordinator_GameEvent>(GetTransientPackage(), CoordinatorGameEventClass, TEXT("Coorindator_Game_Event_Singleton"), RF_Transient | RF_Public);
		s_Instance->AddToRoot();
		s_Instance->SetMyRoot(InRoot);
		s_Instance->Initialize();
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsCoordinator_GameEvent::Init: Init has already been called."));
	}
#endif // #if WITH_EDITOR
}

/*static*/ void UCsCoordinator_GameEvent::Shutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetCoordinatorGameEvent* GetCoordinatorGameEvent = Get_GetCoordinatorGameEvent(InRoot);
	UCsCoordinator_GameEvent* Coordinator_GameEvent     = GetCoordinatorGameEvent->GetCoordinator_GameEvent();
	Coordinator_GameEvent->CleanUp();

	GetCoordinatorGameEvent->SetCoordinator_GameEvent(nullptr);
#else
	if (!s_Instance)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsCoordinator_GameEvent::Shutdown: Coorindator has already been shutdown."));
		return;
	}

	s_Instance->CleanUp();
	s_Instance->RemoveFromRoot();
	s_Instance = nullptr;
	s_bShutdown = true;
#endif // #if WITH_EDITOR
}

/*static*/ bool UCsCoordinator_GameEvent::HasShutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetCoordinatorGameEvent(InRoot)->GetCoordinator_GameEvent() == nullptr;
#else
	return s_bShutdown;
#endif // #if WITH_EDITOR
}

#if WITH_EDITOR

/*static*/ ICsGetCoordinatorGameEvent* UCsCoordinator_GameEvent::Get_GetCoordinatorGameEvent(UObject* InRoot)
{
	checkf(InRoot, TEXT("UCsCoordinator_GameEvent::Get_GetCoordinatorGameEvent: InRoot is NULL."));

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("UCsCoordinator_GameEvent::Get_GetCoordinatorGameEvent: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("UCsCoordinator_GameEvent::Get_GetCoordinatorGameEvent: Manager_Singleton is NULL."));

	ICsGetCoordinatorGameEvent* GetCoorindatorGameEvent = Cast<ICsGetCoordinatorGameEvent>(Manager_Singleton);

	checkf(GetCoorindatorGameEvent, TEXT("UCsCoordinator_GameEvent::Get_GetCoordinatorGameEvent: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsGetCoordinatorGameEvent."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

	return GetCoorindatorGameEvent;
}

/*static*/ ICsGetCoordinatorGameEvent* UCsCoordinator_GameEvent::GetSafe_GetCoordinatorGameEvent(UObject* Object)
{
	if (!Object)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsStatusEffectCoordinator::GetSafe_GetCoordinatorGameEvent: Object is NULL."));
		return nullptr;
	}

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(Object);

	if (!GetManagerSingleton)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Damage::GetSafe_GetCoordinatorGameEvent: Object: %s does NOT implement the interface: ICsGetManagerSingleton."), *(Object->GetName()));
		return nullptr;
	}

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	if (!Manager_Singleton)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Damage::GetSafe_GetCoordinatorGameEvent: Failed to get object of type: UCsManager_Singleton from Object: %s."), *(Object->GetName()));
		return nullptr;
	}

	return Cast<ICsGetCoordinatorGameEvent>(Manager_Singleton);
}

/*static*/ UCsCoordinator_GameEvent* UCsCoordinator_GameEvent::GetSafe(UObject* Object)
{
	if (ICsGetCoordinatorGameEvent* GetCoordinatorGameEvent = GetSafe_GetCoordinatorGameEvent(Object))
		return GetCoordinatorGameEvent->GetCoordinator_GameEvent();
	return nullptr;
}

/*static*/ UCsCoordinator_GameEvent* UCsCoordinator_GameEvent::GetFromWorldContextObject(const UObject* WorldContextObject)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		// Game State
		if (UCsCoordinator_GameEvent* Coordinator = GetSafe(World->GetGameInstance()))
			return Coordinator;

		UE_LOG(LogCs, Warning, TEXT("UCsCoordinator_GameEvent::GetFromWorldContextObject: Failed to find Coordinator of type UCsCoordinator_GameEvent from GameInstance."));

		return nullptr;
	}
	else
	{
		return nullptr;
	}
}

#endif // #if WITH_EDITOR

void UCsCoordinator_GameEvent::Initialize()
{
}

/*static*/ bool UCsCoordinator_GameEvent::HasInitialized(UObject* InRoot)
{
	if (!HasShutdown(InRoot))
		return Get(InRoot)->bInitialized;
	return false;
}

void UCsCoordinator_GameEvent::CleanUp()
{
	bInitialized = false;
}

	// Root
#pragma region

void UCsCoordinator_GameEvent::SetMyRoot(UObject* InRoot)
{
	MyRoot = InRoot;
}

#pragma endregion Root

#pragma endregion Singleton
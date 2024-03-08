// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Coordinators/GameEvent/CsCoordinator_GameEvent.h"
#include "CsCore.h"

// CVar
#include "Coordinators/GameEvent/CsCVars_Coordinator_GameEvent.h"
// Console Command
#include "Coordinators/GameEvent/CsConsoleCommand_Coordinator_GameEvent.h"
// Library
#include "Coordinators/GameEvent/CsLibrary_Coordinator_GameEvent.h"
	// Common
#include "Library/CsLibrary_World.h"

#if WITH_EDITOR
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Coordinators/GameEvent/CsGetCoordinatorGameEvent.h"
#endif // #if WITH_EDITOR

// Cached
#pragma region

namespace NCsCoordinatorGameEvent
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsCoordinator_GameEvent, Init);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsCoordinator_GameEvent, GetFromWorldContextObject);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsCoordinator_GameEvent, ProcessGameEventInfo);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsCoordinator_GameEvent, QueueGameEventInfo);
		}
	}
}

#pragma endregion Cached

// static initializations
UCsCoordinator_GameEvent* UCsCoordinator_GameEvent::s_Instance;
bool UCsCoordinator_GameEvent::s_bShutdown = false;

UCsCoordinator_GameEvent::UCsCoordinator_GameEvent(const FObjectInitializer& ObjectInitializer) : 
	Super(ObjectInitializer),
	// Console Command
	Manager_ConsoleCommand(nullptr),
	OnProcessGameEventInfo_Events(),
	OnProcessGameEventInfo_ManagerInput0_ScriptEvent()
{
}

// Singleton
#pragma region

#if WITH_EDITOR
/*static*/ UCsCoordinator_GameEvent* UCsCoordinator_GameEvent::Get(UObject* InRoot /*=nullptr*/)
{
	return Get_GetCoordinatorGameEvent(InRoot)->GetCoordinator_GameEvent();
}
#endif // #if WITH_EDITOR

/*static*/ bool UCsCoordinator_GameEvent::IsValid(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetCoordinatorGameEvent(InRoot)->GetCoordinator_GameEvent() != nullptr;
#else
	return s_Instance != nullptr;
#endif // #if WITH_EDITOR
}

/*static*/ void UCsCoordinator_GameEvent::Init(UObject* InRoot /*=nullptr*/, TSubclassOf<UCsCoordinator_GameEvent> CoordinatorClass /*=TSubclassOf<UCsCoordinator_GameEvent>(UCsCoordinator_GameEvent::StaticClass())*/)
{
	using namespace NCsCoordinatorGameEvent::NCached;

	const FString& Context = Str::Init;

	checkf(CoordinatorClass.Get(), TEXT("%s: CoordinatorClass is NULL."), *Context);

#if WITH_EDITOR
	ICsGetCoordinatorGameEvent* GetCoordinatorGameEvent = Get_GetCoordinatorGameEvent(InRoot);

	UCsCoordinator_GameEvent* Coordinator_GameEvent = GetCoordinatorGameEvent->GetCoordinator_GameEvent();

	if (!Coordinator_GameEvent)
	{
		Coordinator_GameEvent = NewObject<UCsCoordinator_GameEvent>(InRoot, CoordinatorClass, TEXT("Coorindator_Game_Event_Singleton"), RF_Transient | RF_Public);

		GetCoordinatorGameEvent->SetCoordinator_GameEvent(Coordinator_GameEvent);

		Coordinator_GameEvent->SetMyRoot(InRoot);
		Coordinator_GameEvent->Initialize();
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("%s: Init has already been called."), *Context);
	}
#else
	s_bShutdown = false;

	if (!s_Instance)
	{
		s_Instance = NewObject<UCsCoordinator_GameEvent>(GetTransientPackage(), CoordinatorClass, TEXT("Coorindator_Game_Event_Singleton"), RF_Transient | RF_Public);
		s_Instance->AddToRoot();
		s_Instance->SetMyRoot(InRoot);
		s_Instance->Initialize();
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("%s: Init has already been called."), *Context);
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

/*static*/ UCsCoordinator_GameEvent* UCsCoordinator_GameEvent::GetFromWorldContextObject(UObject* WorldContextObject)
{
	using namespace NCsCoordinatorGameEvent::NCached;

	const FString& Context = Str::GetFromWorldContextObject;

	typedef NCsGameEvent::NCoordinator::FLibrary GameEventCoordinatorLibrary;

	if (UObject* ContextRoot = GameEventCoordinatorLibrary::GetSafeContextRoot(Context, WorldContextObject))
	{
		// Game State
		if (UCsCoordinator_GameEvent* Coordinator = GetSafe(ContextRoot))
			return Coordinator;

		UE_LOG(LogCs, Warning, TEXT("%s: Failed to find Coordinator of type UCsCoordinator_GameEvent from ContextRoot."), *(ContextRoot->GetName()));
	}
	return nullptr;
}

#endif // #if WITH_EDITOR

void UCsCoordinator_GameEvent::Initialize()
{
	typedef NCsGameEvent::NCoordinator::FConsoleCommand ConsoleCommandManagerType;

	Manager_ConsoleCommand = new ConsoleCommandManagerType(MyRoot);

	// OnProcessGameEventInfo_Events
	{
		const int32& Count = EMCsGameEventCoordinatorGroup::Get().Num();

		OnProcessGameEventInfo_Events.Reset(Count);
		OnProcessGameEventInfo_Events.AddDefaulted(Count);
	}
	// QueuedGameEventInfosByGroupMap
	{
		typedef EMCsGameEventCoordinatorGroup GroupMapType;
		typedef FECsGameEventCoordinatorGroup GroupType;

		for (const GroupType& Group : GroupMapType::Get())
		{
			QueuedGameEventInfosByGroupMap.Add(Group);
		}
	}
}

/*static*/ bool UCsCoordinator_GameEvent::HasInitialized(UObject* InRoot)
{
	if (!HasShutdown(InRoot))
		return Get(InRoot)->bInitialized;
	return false;
}

void UCsCoordinator_GameEvent::CleanUp()
{
	delete Manager_ConsoleCommand;
	Manager_ConsoleCommand = nullptr;

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

// StartPlay
#pragma region

void UCsCoordinator_GameEvent::StartPlay()
{
	ReceiveStartPlay();
}

#pragma endregion StartPlay

// Update
#pragma region

void UCsCoordinator_GameEvent::Update(const FCsDeltaTime& DeltaTime)
{
	ReceiveUpdate(DeltaTime);
}

#pragma endregion Update

UObject* UCsCoordinator_GameEvent::GetWorldContext() const
{
	typedef NCsWorld::FLibrary WorldLibrary;

	return WorldLibrary::GetSafe(MyRoot);
}

void UCsCoordinator_GameEvent::OnGameEventInfo_ManagerInput0(const FCsGameEventInfo& Info)
{
	ProcessGameEventInfo(NCsGameEventCoordinatorGroup::ManagerInput0, Info);
}

void UCsCoordinator_GameEvent::OnGameEventInfo_ManagerInput1(const FCsGameEventInfo& Info)
{
	ProcessGameEventInfo(NCsGameEventCoordinatorGroup::ManagerInput1, Info);
}

void UCsCoordinator_GameEvent::ProcessGameEventInfo(const FECsGameEventCoordinatorGroup& Group, const FCsGameEventInfo& Info)
{
	using namespace NCsCoordinatorGameEvent::NCached;

	const FString& Context = Str::ProcessGameEventInfo;

	check(EMCsGameEventCoordinatorGroup::Get().IsValidEnumChecked(Context, Group));

	OnProcessGameEventInfo_Events[Group.GetValue()].Broadcast(Group, Info);

	if (Group == NCsGameEventCoordinatorGroup::ManagerInput0)
		OnProcessGameEventInfo_ManagerInput0_ScriptEvent.Broadcast(Group, Info);

	OnProcessGameEventInfo_ScriptEvent.Broadcast(Group, Info);
}

void UCsCoordinator_GameEvent::QueueGameEventInfo(const FECsGameEventCoordinatorGroup& Group, const FCsGameEventInfo& Info)
{
	using namespace NCsCoordinatorGameEvent::NCached;

	const FString& Context = Str::QueueGameEventInfo;

	check(EMCsGameEventCoordinatorGroup::Get().IsValidEnumChecked(Context, Group));

	QueuedGameEventInfosByGroupMap[Group].Add(Info);
}

void UCsCoordinator_GameEvent::OnPostProcessInput_ManagerInput0(const float& DeltaTime, const bool bGamePaused)
{
	ProcessQueuedGameEventInfos(NCsGameEventCoordinatorGroup::ManagerInput0);
}

void UCsCoordinator_GameEvent::OnPostProcessInput_ManagerInput1(const float& DeltaTime, const bool bGamePaused)
{
	ProcessQueuedGameEventInfos(NCsGameEventCoordinatorGroup::ManagerInput1);
}

void UCsCoordinator_GameEvent::ProcessQueuedGameEventInfos(const FECsGameEventCoordinatorGroup& Group)
{
	TArray<FCsGameEventInfo>& Infos = QueuedGameEventInfosByGroupMap[Group];

	for (const FCsGameEventInfo& Info : Infos)
	{
		ProcessGameEventInfo(Group, Info);
	}
	Infos.Reset(Infos.Max());
}
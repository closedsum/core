// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Coordinators/GameplayTag/CsCoordinator_GameplayTag.h"
#include "CsGameplayTags.h"

// CVar
#include "Coordinators/GameplayTag/CsCVars_Coordinator_GameplayTag.h"
// Types
#include "CsMacro_Misc.h"
// Library
#include "Coordinators/GameplayTag/CsLibrary_Coordinator_GameplayTag.h"
	// Common
#include "CsLibrary_GameplayTags.h"
#include "Library/CsLibrary_World.h"
#include "Library/CsLibrary_Valid.h"
// Settings
#include "Coordinators/GameplayTag/CsSettings_Coordinator_GameplayTag.h"
// Package
#include "UObject/Package.h"

#if WITH_EDITOR
#include "Singleton/CsGetManagerSingleton.h"
#include "Singleton/CsManager_Singleton.h"
#include "Coordinators/GameplayTag/CsGetCoordinatorGameplayTag.h"
#endif // #if WITH_EDITOR

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsCoordinator_GameplayTag)

// Cached
#pragma region

namespace NCsCoordinatorGameplayTag
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsCoordinator_GameplayTag, Init);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsCoordinator_GameplayTag, GetFromWorldContextObject);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsCoordinator_GameplayTag, ProcessGameplayTagEvent);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsCoordinator_GameplayTag, QueueGameplayTagEvent);
		}
	}
}

#pragma endregion Cached

// static initializations
UCsCoordinator_GameplayTag* UCsCoordinator_GameplayTag::s_Instance;
bool UCsCoordinator_GameplayTag::s_bShutdown = false;

UCsCoordinator_GameplayTag::UCsCoordinator_GameplayTag(const FObjectInitializer& ObjectInitializer) : 
	Super(ObjectInitializer),
	OnProcessGameplayTagEvent_Events(),
	OnProcessGameplayTagEvent_ManagerInput0_ScriptEvent()
{
}

#define USING_NS_CACHED using namespace NCsCoordinatorGameplayTag::NCached;
#define SET_CONTEXT(__FunctionName) using namespace NCsCoordinatorGameplayTag::NCached; \
	const FString& Context = Str::__FunctionName
#define GameplayTagsLibrary NCsGameplayTags::FLibrary

// Singleton
#pragma region

#if WITH_EDITOR
/*static*/ UCsCoordinator_GameplayTag* UCsCoordinator_GameplayTag::Get(UObject* InRoot /*=nullptr*/)
{
	return Get_GetCoordinatorGameplayTag(InRoot)->GetCoordinator_GameplayTag();
}
#endif // #if WITH_EDITOR

/*static*/ bool UCsCoordinator_GameplayTag::IsValid(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetCoordinatorGameplayTag(InRoot)->GetCoordinator_GameplayTag() != nullptr;
#else
	return s_Instance != nullptr;
#endif // #if WITH_EDITOR
}

/*static*/ void UCsCoordinator_GameplayTag::Init(UObject* InRoot /*=nullptr*/, TSubclassOf<UCsCoordinator_GameplayTag> CoordinatorClass)
{
	SET_CONTEXT(Init);

	CS_IS_SUBCLASS_OF_NULL_CHECKED(CoordinatorClass, UCsCoordinator_GameplayTag)

#if WITH_EDITOR
	ICsGetCoordinatorGameplayTag* GetCoordinatorGameplayTag = Get_GetCoordinatorGameplayTag(InRoot);
	UCsCoordinator_GameplayTag* Coordinator_GameplayTag		= GetCoordinatorGameplayTag->GetCoordinator_GameplayTag();

	if (!Coordinator_GameplayTag)
	{
		Coordinator_GameplayTag = NewObject<UCsCoordinator_GameplayTag>(InRoot, CoordinatorClass, TEXT("Coorindator_GameplayTag_Singleton"), RF_Transient | RF_Public);

		GetCoordinatorGameplayTag->SetCoordinator_GameplayTag(Coordinator_GameplayTag);

		Coordinator_GameplayTag->SetMyRoot(InRoot);
		Coordinator_GameplayTag->Initialize();
	}
	else
	{
		UE_LOG(LogCsGameplayTags, Warning, TEXT("%s: Init has already been called."), *Context);
	}
#else
	s_bShutdown = false;

	if (!s_Instance)
	{
		s_Instance = NewObject<UCsCoordinator_GameplayTag>(GetTransientPackage(), CoordinatorClass, TEXT("Coorindator_GameplayTag_Singleton"), RF_Transient | RF_Public);
		s_Instance->AddToRoot();
		s_Instance->SetMyRoot(InRoot);
		s_Instance->Initialize();
	}
	else
	{
		UE_LOG(LogCsGameplayTags, Warning, TEXT("%s: Init has already been called."), *Context);
	}
#endif // #if WITH_EDITOR
}

/*static*/ void UCsCoordinator_GameplayTag::Init(UObject* InRoot)
{
	SET_CONTEXT(Init);

	const FCsSettings_Coordinator_GameplayTag& Settings = FCsSettings_Coordinator_GameplayTag::Get();

	Init(InRoot, Settings.LoadClassChecked(Context));
}

/*static*/ void UCsCoordinator_GameplayTag::Shutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetCoordinatorGameplayTag* GetCoordinatorGameplayTag = Get_GetCoordinatorGameplayTag(InRoot);
	UCsCoordinator_GameplayTag* Coordinator_GameplayTag     = GetCoordinatorGameplayTag->GetCoordinator_GameplayTag();
	Coordinator_GameplayTag->CleanUp();

	GetCoordinatorGameplayTag->SetCoordinator_GameplayTag(nullptr);
#else
	if (!s_Instance)
	{
		UE_LOG(LogCsGameplayTags, Warning, TEXT("UCsCoordinator_GameplayTag::Shutdown: Coorindator has already been shutdown."));
		return;
	}

	s_Instance->CleanUp();
	s_Instance->RemoveFromRoot();
	s_Instance = nullptr;
	s_bShutdown = true;
#endif // #if WITH_EDITOR
}

/*static*/ bool UCsCoordinator_GameplayTag::HasShutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetCoordinatorGameplayTag(InRoot)->GetCoordinator_GameplayTag() == nullptr;
#else
	return s_bShutdown;
#endif // #if WITH_EDITOR
}

#if WITH_EDITOR

/*static*/ ICsGetCoordinatorGameplayTag* UCsCoordinator_GameplayTag::Get_GetCoordinatorGameplayTag(UObject* InRoot)
{
	checkf(InRoot, TEXT("UCsCoordinator_GameplayTag::Get_GetCoordinatorGameplayTag: InRoot is NULL."));

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("UCsCoordinator_GameplayTag::Get_GetCoordinatorGameplayTag: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("UCsCoordinator_GameplayTag::Get_GetCoordinatorGameplayTag: Manager_Singleton is NULL."));

	ICsGetCoordinatorGameplayTag* GetCoorindatorGameplayTag = Cast<ICsGetCoordinatorGameplayTag>(Manager_Singleton);

	checkf(GetCoorindatorGameplayTag, TEXT("UCsCoordinator_GameplayTag::Get_GetCoordinatorGameplayTag: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsGetCoordinatorGameplayTag."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));
	return GetCoorindatorGameplayTag;
}

/*static*/ ICsGetCoordinatorGameplayTag* UCsCoordinator_GameplayTag::GetSafe_GetCoordinatorGameplayTag(UObject* Object)
{
	if (!Object)
	{
		UE_LOG(LogCsGameplayTags, Warning, TEXT("UCsCoordinator_GameplayTag::GetSafe_GetCoordinatorGameplayTag: Object is NULL."));
		return nullptr;
	}

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(Object);

	if (!GetManagerSingleton)
	{
		UE_LOG(LogCsGameplayTags, Warning, TEXT("UCsCoordinator_GameplayTag::GetSafe_GetCoordinatorGameplayTag: Object: %s does NOT implement the interface: ICsGetManagerSingleton."), *(Object->GetName()));
		return nullptr;
	}

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	if (!Manager_Singleton)
	{
		UE_LOG(LogCsGameplayTags, Warning, TEXT("UCsCoordinator_GameplayTag::GetSafe_GetCoordinatorGameplayTag: Failed to get object of type: UCsManager_Singleton from Object: %s."), *(Object->GetName()));
		return nullptr;
	}

	return Cast<ICsGetCoordinatorGameplayTag>(Manager_Singleton);
}

/*static*/ UCsCoordinator_GameplayTag* UCsCoordinator_GameplayTag::GetSafe(UObject* Object)
{
	if (ICsGetCoordinatorGameplayTag* GetCoordinatorGameplayTag = GetSafe_GetCoordinatorGameplayTag(Object))
		return GetCoordinatorGameplayTag->GetCoordinator_GameplayTag();
	return nullptr;
}

/*static*/ UCsCoordinator_GameplayTag* UCsCoordinator_GameplayTag::GetFromWorldContextObject(UObject* WorldContextObject)
{
	SET_CONTEXT(GetFromWorldContextObject);

	typedef NCsGameplayTag::NCoordinator::FLibrary GameplayTagCoordinatorLibrary;

	if (UObject* ContextRoot = GameplayTagCoordinatorLibrary::GetSafeContextRoot(Context, WorldContextObject))
	{
		// Game State
		if (UCsCoordinator_GameplayTag* Coordinator = GetSafe(ContextRoot))
			return Coordinator;
		UE_LOG(LogCsGameplayTags, Warning, TEXT("%s: Failed to find Coordinator of type UCsCoordinator_GameplayTag from ContextRoot."), *(ContextRoot->GetName()));
	}
	return nullptr;
}

#endif // #if WITH_EDITOR

void UCsCoordinator_GameplayTag::Initialize()
{
	// OnProcessGameplayTagEvent_Events
	{
		const int32& Count = EMCsGameplayTagCoordinatorGroup::Get().Num();

		OnProcessGameplayTagEvent_Events.Reset(Count);
		OnProcessGameplayTagEvent_Events.AddDefaulted(Count);
	}
	// QueuedGameplayTagEventsByGroupMap
	{
		typedef EMCsGameplayTagCoordinatorGroup GroupMapType;
		typedef FECsGameplayTagCoordinatorGroup GroupType;

		for (const GroupType& Group : GroupMapType::Get())
		{
			QueuedGameplayTagEventsByGroupMap.Add(Group);
		}
	}
}

/*static*/ bool UCsCoordinator_GameplayTag::HasInitialized(UObject* InRoot)
{
	if (!HasShutdown(InRoot))
		return Get(InRoot)->bInitialized;
	return false;
}

void UCsCoordinator_GameplayTag::CleanUp()
{
	bInitialized = false;
}

	// Root
#pragma region

void UCsCoordinator_GameplayTag::SetMyRoot(UObject* InRoot)
{
	MyRoot = InRoot;
}

#pragma endregion Root

#pragma endregion Singleton

// StartPlay
#pragma region

void UCsCoordinator_GameplayTag::StartPlay()
{
	ReceiveStartPlay();
}

#pragma endregion StartPlay

// Update
#pragma region

void UCsCoordinator_GameplayTag::Update(const FCsDeltaTime& DeltaTime)
{
	ReceiveUpdate(DeltaTime);
}

#pragma endregion Update

UObject* UCsCoordinator_GameplayTag::GetWorldContext() const
{
	return CsWorldLibrary::GetSafeAsObject(MyRoot);
}

// Tag
#pragma region

void UCsCoordinator_GameplayTag::GetOwnedTags(FGameplayTagContainer& OutTagContainer) const
{
	GameplayTagsLibrary::Copy(GetOwnedTags(), OutTagContainer);
}

void UCsCoordinator_GameplayTag::UpdateTagMap_Internal(const FGameplayTagContainer& Container, const int32& CountDelta)
{
	// For removal, reorder calls so that FillParentTags is only called once
	if (CountDelta > 0)
	{
		for (auto TagIt = Container.CreateConstIterator(); TagIt; ++TagIt)
		{
			const FGameplayTag& Tag = *TagIt;

			if (CountContainer.UpdateTagCount(Tag, CountDelta))
			{
				OnTagUpdated(Tag, true);
			}
		}
	}
	else 
	if (CountDelta < 0)
	{
		// Defer FillParentTags and calling delegates until all Tags have been removed
		static TArray<FGameplayTag> RemovedTags;
		RemovedTags.Reset(FMath::Max(RemovedTags.Max(), Container.Num())); // pre-allocate max number (if all are removed)

		typedef NCsGameplayTag::NCount::FOnDeferredChange OnDeferredChangeEventType;

		static TArray<OnDeferredChangeEventType> DeferredTagChangeDelegates;

		DeferredTagChangeDelegates.Reset(DeferredTagChangeDelegates.Max());

		for (auto TagIt = Container.CreateConstIterator(); TagIt; ++TagIt)
		{
			const FGameplayTag& Tag = *TagIt;
			if (CountContainer.UpdateTagCount_DeferredParentRemoval(Tag, CountDelta, DeferredTagChangeDelegates))
			{
				RemovedTags.Add(Tag);
			}
		}

		// Now do the work that was deferred
		if (RemovedTags.Num() > 0)
		{
			// TODO: NOTE: Put into Library and optimize
			CountContainer.FillParentTags();
		}

		for (OnDeferredChangeEventType& Delegate : DeferredTagChangeDelegates)
		{
			Delegate.Execute();
		}

		// Notify last in case OnTagUpdated queries this container
		for (FGameplayTag& Tag : RemovedTags)
		{
			OnTagUpdated(Tag, false);
		}
	}
}

void UCsCoordinator_GameplayTag::OnTagUpdated(const FGameplayTag& Tag, const bool& TagExists)
{
}

#pragma endregion

// Events
#pragma region

void UCsCoordinator_GameplayTag::OnTagEvent_ManagerInput0(const FCsGameplayTagEvent& Event)
{
	ProcessGameplayTagEvent(NCsGameplayTagCoordinatorGroup::ManagerInput0, Event);
}

void UCsCoordinator_GameplayTag::OnTagEvent_ManagerInput1(const FCsGameplayTagEvent& Event)
{
	ProcessGameplayTagEvent(NCsGameplayTagCoordinatorGroup::ManagerInput1, Event);
}

void UCsCoordinator_GameplayTag::ProcessGameplayTagEvent(const FECsGameplayTagCoordinatorGroup& Group, const FCsGameplayTagEvent& Event)
{
	SET_CONTEXT(ProcessGameplayTagEvent);

	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsGameplayTagCoordinatorGroup, Group)

	OnProcessGameplayTagEvent_Events[Group.GetValue()].Broadcast(Group, Event);

	if (Group == NCsGameplayTagCoordinatorGroup::ManagerInput0)
		OnProcessGameplayTagEvent_ManagerInput0_ScriptEvent.Broadcast(Group, Event);
	OnProcessGameplayTagEvent_ScriptEvent.Broadcast(Group, Event);
}

void UCsCoordinator_GameplayTag::QueueGameplayTagEvent(const FECsGameplayTagCoordinatorGroup& Group, const FCsGameplayTagEvent& Event)
{
	SET_CONTEXT(QueueGameplayTagEvent);

	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsGameplayTagCoordinatorGroup, Group)

	QueuedGameplayTagEventsByGroupMap[Group].Add(Event);
}

void UCsCoordinator_GameplayTag::OnPostProcessInput_ManagerInput0(const float& DeltaTime, const bool bGamePaused)
{
	ProcessQueuedGameplayTagEvents(NCsGameplayTagCoordinatorGroup::ManagerInput0);
}

void UCsCoordinator_GameplayTag::OnPostProcessInput_ManagerInput1(const float& DeltaTime, const bool bGamePaused)
{
	ProcessQueuedGameplayTagEvents(NCsGameplayTagCoordinatorGroup::ManagerInput1);
}

void UCsCoordinator_GameplayTag::ProcessQueuedGameplayTagEvents(const FECsGameplayTagCoordinatorGroup& Group)
{
	TArray<FCsGameplayTagEvent>& Events = QueuedGameplayTagEventsByGroupMap[Group];

	for (const FCsGameplayTagEvent& Event : Events)
	{
		ProcessGameplayTagEvent(Group, Event);
	}
	Events.Reset(Events.Max());
}

#pragma endregion Events

#undef USING_NS_CACHED
#undef SET_CONTEXT
#undef GameplayTagsLibrary
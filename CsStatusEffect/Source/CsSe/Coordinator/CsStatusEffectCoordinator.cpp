// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Coordinator/CsStatusEffectCoordinator.h"
#include "CsSe.h"

// CVar
#include "Coordinator/CsCVars_StatusEffectCoordinator.h"
// Library
#include "Library/CsLibrary_Common.h"
#include "CsLibrary_StatusEffect.h"
#include "Event/CsLibrary_StatusEffectEvent.h"
// Managers
#include "Managers/Damage/CsManager_Damage.h"
// StatusEffect
#include "CsReceiveStatusEffect.h"
#include "Damage/CsStatusEffect_Damage.h"
#include "Event/CsStatusEffectEventImpl.h"
#include "Event/CsStatusEffectEvent_DamageImpl.h"
// Unique
#include "UniqueObject/CsUniqueObject.h"

#if WITH_EDITOR
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Coordinator/CsGetStatusEffectCoordinator.h"

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
UCsStatusEffectCoordinator* UCsStatusEffectCoordinator::s_Instance;
bool UCsStatusEffectCoordinator::s_bShutdown = false;

UCsStatusEffectCoordinator::UCsStatusEffectCoordinator(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

// Singleton
#pragma region

/*static*/ UCsStatusEffectCoordinator* UCsStatusEffectCoordinator::Get(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetStatusEffectCoordinator(InRoot)->GetStatusEffectCoordinator();
#else
	if (s_bShutdown)
	{
		UE_LOG(LogCsSe, Warning, TEXT("UCsStatusEffectCoordinator::Get: Coordinator has already shutdown."));
		return nullptr;
	}
	return s_Instance;
#endif // #if WITH_EDITOR
}

/*static*/ bool UCsStatusEffectCoordinator::IsValid(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetStatusEffectCoordinator(InRoot)->GetStatusEffectCoordinator() != nullptr;
#else
	return s_Instance != nullptr;
#endif // #if WITH_EDITOR
}

/*static*/ void UCsStatusEffectCoordinator::Init(UObject* InRoot, TSubclassOf<UCsStatusEffectCoordinator> StatusEffectCoordinatorClass, UObject* InOuter /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetStatusEffectCoordinator* GetStatusEffectCoordinator = Get_GetStatusEffectCoordinator(InRoot);

	UCsStatusEffectCoordinator* StatusEffectCoordinator = GetStatusEffectCoordinator->GetStatusEffectCoordinator();

	if (!StatusEffectCoordinator)
	{
		StatusEffectCoordinator = NewObject<UCsStatusEffectCoordinator>(InOuter ? InOuter : InRoot, StatusEffectCoordinatorClass, TEXT("Status_Effect_Coorindator_Singleton"), RF_Transient | RF_Public);

		GetStatusEffectCoordinator->SetStatusEffectCoordinator(StatusEffectCoordinator);

		StatusEffectCoordinator->SetMyRoot(InRoot);
		StatusEffectCoordinator->Initialize();
	}
	else
	{
		UE_LOG(LogCsSe, Warning, TEXT("UCsStatusEffectCoordinator::Init: Init has already been called."));
	}
#else
	s_bShutdown = false;

	if (!s_Instance)
	{
		s_Instance = NewObject<UCsStatusEffectCoordinator>(GetTransientPackage(), StatusEffectCoordinatorClass, TEXT("Status_Effect_Coorindator_Singleton"), RF_Transient | RF_Public);
		s_Instance->AddToRoot();
		s_Instance->SetMyRoot(InRoot);
		s_Instance->Initialize();
	}
	else
	{
		UE_LOG(LogCsSe, Warning, TEXT("UCsStatusEffectCoordinator::Init: Init has already been called."));
	}
#endif // #if WITH_EDITOR
}

/*static*/ void UCsStatusEffectCoordinator::Shutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetStatusEffectCoordinator* GetStatusEffectCoordinator = Get_GetStatusEffectCoordinator(InRoot);
	UCsStatusEffectCoordinator* StatusEffectCoordinator		  = GetStatusEffectCoordinator->GetStatusEffectCoordinator();
	StatusEffectCoordinator->CleanUp();

	GetStatusEffectCoordinator->SetStatusEffectCoordinator(nullptr);
#else
	if (!s_Instance)
	{
		UE_LOG(LogCsSe, Warning, TEXT("UCsStatusEffectCoordinator::Shutdown: Coorindator has already been shutdown."));
		return;
	}

	s_Instance->CleanUp();
	s_Instance->RemoveFromRoot();
	s_Instance = nullptr;
	s_bShutdown = true;
#endif // #if WITH_EDITOR
}

/*static*/ bool UCsStatusEffectCoordinator::HasShutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetStatusEffectCoordinator(InRoot)->GetStatusEffectCoordinator() == nullptr;
#else
	return s_bShutdown;
#endif // #if WITH_EDITOR
}

#if WITH_EDITOR

/*static*/ ICsGetStatusEffectCoordinator* UCsStatusEffectCoordinator::Get_GetStatusEffectCoordinator(UObject* InRoot)
{
	checkf(InRoot, TEXT("UCsStatusEffectCoordinator::Get_GetStatusEffectCoordinator: InRoot is NULL."));

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("UCsStatusEffectCoordinator::Get_GetStatusEffectCoordinator: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("UCsStatusEffectCoordinator::Get_GetStatusEffectCoordinator: Manager_Singleton is NULL."));

	ICsGetStatusEffectCoordinator* GetStatusEffectCoorindator = Cast<ICsGetStatusEffectCoordinator>(Manager_Singleton);

	checkf(GetStatusEffectCoorindator, TEXT("UCsStatusEffectCoordinator::Get_GetStatusEffectCoordinator: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsGetStatusEffectCoordinator."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

	return GetStatusEffectCoorindator;
}

/*static*/ ICsGetStatusEffectCoordinator* UCsStatusEffectCoordinator::GetSafe_GetStatusEffectCoordinator(UObject* Object)
{
	if (!Object)
	{
		UE_LOG(LogCsSe, Warning, TEXT("UCsStatusEffectCoordinator::GetSafe_GetStatusEffectCoordinator: Object is NULL."));
		return nullptr;
	}

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(Object);

	if (!GetManagerSingleton)
	{
		UE_LOG(LogCsSe, Warning, TEXT("UCsManager_Damage::GetSafe_GetStatusEffectCoordinator: Object: %s does NOT implement the interface: ICsGetManagerSingleton."), *(Object->GetName()));
		return nullptr;
	}

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	if (!Manager_Singleton)
	{
		UE_LOG(LogCsSe, Warning, TEXT("UCsManager_Damage::GetSafe_GetStatusEffectCoordinator: Failed to get object of type: UCsManager_Singleton from Object: %s."), *(Object->GetName()));
		return nullptr;
	}

	return Cast<ICsGetStatusEffectCoordinator>(Manager_Singleton);
}

/*static*/ UCsStatusEffectCoordinator* UCsStatusEffectCoordinator::GetSafe(UObject* Object)
{
	if (ICsGetStatusEffectCoordinator* GetStatusEffectCoordinator = GetSafe_GetStatusEffectCoordinator(Object))
		return GetStatusEffectCoordinator->GetStatusEffectCoordinator();
	return nullptr;
}

/*static*/ UCsStatusEffectCoordinator* UCsStatusEffectCoordinator::GetFromWorldContextObject(const UObject* WorldContextObject)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		// Game State
		if (UCsStatusEffectCoordinator* Manager = GetSafe(World->GetGameState()))
			return Manager;

		UE_LOG(LogCsSe, Warning, TEXT("UCsStatusEffectCoordinator::GetFromWorldContextObject: Failed to Manager Item of type UCsStatusEffectCoordinator from GameState."));

		return nullptr;
	}
	else
	{
		return nullptr;
	}
}

#endif // #if WITH_EDITOR

void UCsStatusEffectCoordinator::Initialize()
{
	// TODO: Poll config in future

	const int32& Count = EMCsStatusEffectEvent::Get().Num();

	Manager_Events.Reserve(Count);
	Manager_Events.AddDefaulted(Count);

	for (const FECsStatusEffectEvent& Event : EMCsStatusEffectEvent::Get())
	{
		FCsManager_StatusEffectEvent& Manager = Manager_Events[Event.GetValue()];
		
		const FString Name = FString::Printf(TEXT("UCsStatusEffectCoordinator::FCsManager_StatusEffectEvent[%s]"), Event.ToChar());

		Manager.SetName(Name);
		Manager.SetDeconstructResourcesOnShutdown();

		const int32 PoolSize = 64;

		Manager.CreatePool(PoolSize);

		for (int32 I = 0; I < PoolSize; ++I)
		{
			ICsStatusEffectEvent* IEvent = ConstructEvent(Event);

			checkf(IEvent, TEXT("UCsStatusEffectCoordinator::Initialize: Failed to construct event for type: %s."), Event.ToChar());

			Manager.Add(IEvent);
		} 
	}
}

void UCsStatusEffectCoordinator::CleanUp()
{
}

	// Root
#pragma region

void UCsStatusEffectCoordinator::SetMyRoot(UObject* InRoot)
{
	MyRoot = InRoot;
}

#pragma endregion Root

#pragma endregion Singleton

// Receive Status Effect
#pragma region

void UCsStatusEffectCoordinator::Add(ICsReceiveStatusEffect* Object)
{
	checkf(Object, TEXT("UCsStatusEffectCoordinator::Add: Object is NULL."));

	UObject* O = Object->_getUObject();

	checkf(O, TEXT("UCsStatusEffectCoordinator::Add: Object is NOT a UObject."));

	UClass* Class = O->GetClass();

	checkf(Class->ImplementsInterface(UCsUniqueObject::StaticClass()), TEXT("UCsStatusEffectCoordinator::Add: Object: %s with Class: %s does NOT implement interface: ICsUniqueObject."), *(O->GetName()), *(Class->GetName()));

	// TODO: Need to look at script objects
	ICsUniqueObject* UniqueObject = Cast<ICsUniqueObject>(O);

	checkf(UniqueObject, TEXT("UCsStatusEffectCoordinator::Add: Object: %s with Class: %s does NOT implement interface: ICsUniqueObject."), *(O->GetName()), *(Class->GetName()));

	const FCsUniqueObjectId& Id = UniqueObject->GetId();

	ReceiveStatusEffectMap.Add(Id, Object);
}

void UCsStatusEffectCoordinator::Remove(ICsReceiveStatusEffect* Object)
{
	checkf(Object, TEXT("UCsStatusEffectCoordinator::Remove: Object is NULL."));

	UObject* O = Object->_getUObject();

	checkf(O, TEXT("UCsStatusEffectCoordinator::Remove: Object is NOT a UObject."));

	UClass* Class = O->GetClass();

	checkf(Class->ImplementsInterface(UCsUniqueObject::StaticClass()), TEXT("UCsStatusEffectCoordinator::Remove: Object: %s with Class: %s does NOT implement interface: ICsUniqueObject."), *(O->GetName()), *(Class->GetName()));

	// TODO: Need to look at script objects
	ICsUniqueObject* UniqueObject = Cast<ICsUniqueObject>(O);

	checkf(UniqueObject, TEXT("UCsStatusEffectCoordinator::Remove: Object: %s with Class: %s does NOT implement interface: ICsUniqueObject."), *(O->GetName()), *(Class->GetName()));

	const FCsUniqueObjectId& Id = UniqueObject->GetId();

	ReceiveStatusEffectMap.Remove(Id);
}

#pragma endregion Receive Damage

// Event
#pragma region

ICsStatusEffectEvent* UCsStatusEffectCoordinator::ConstructEvent(const FECsStatusEffectEvent& Type)
{
	// Default
	if (Type == NCsStatusEffectEvent::Default)
		return new FCsStatusEffectEventImpl();
	// Damage
	if (Type == NCsStatusEffectEvent::Damage)
		return new FCsStatusEffectEvent_DamageImpl();
	return nullptr;
}

FCsResource_StatusEffectEvent* UCsStatusEffectCoordinator::AllocateEvent(const FECsStatusEffectEvent& Type)
{
	return Manager_Events[Type.GetValue()].Allocate();
}

const FECsStatusEffectEvent& UCsStatusEffectCoordinator::GetTypeFromEvent(ICsStatusEffectEvent* Event)
{
	using namespace NCsStatusEffectCoordinatorCached;

	checkf(Event, TEXT("UCsStatusEffectCoordinator::GetTypeFromEvent: Event is NULL."));

	// Damage
	if (FCsLibrary_StatusEffectEvent::GetSafeInterfaceChecked<ICsStatusEffectEvent_Damage>(Str::GetTypeFromEvent, Event))
		return NCsStatusEffectEvent::Damage;
	return NCsStatusEffectEvent::Default;
}

const FECsStatusEffectEvent& UCsStatusEffectCoordinator::GetTypeFromEvent(FCsResource_StatusEffectEvent* Event)
{
	checkf(Event, TEXT("UCsStatusEffectCoordinator::GetTypeFromEvent: Event is NULL."));

	return GetTypeFromEvent(Event->Get());
}

void UCsStatusEffectCoordinator::ProcessStatusEffectEvent(const ICsStatusEffectEvent* Event)
{
	using namespace NCsStatusEffectCoordinatorCached;

	checkf(Event, TEXT("UCsStatusEffectCoordinator::ProcessStatusEffectEvent: Event is NULL."));

	ICsStatusEffect* StatusEffect = Event->GetStatusEffect();

	checkf(StatusEffect, TEXT("UCsStatusEffectCoordinator::ProcessStatusEffectEvent: StatusEffect is NULL. No Status Effect found for Event."));

	// ICsStatusEffectEvent_Damage
	if (ICsStatusEffectEvent_Damage* SeDamageEvent = FCsLibrary_StatusEffectEvent::GetSafeInterfaceChecked<ICsStatusEffectEvent_Damage>(Str::ProcessStatusEffectEvent, const_cast<ICsStatusEffectEvent*>(Event)))
	{
		// Get the DamageEVent
		ICsDamageEvent* DamageEvent = SeDamageEvent->GetDamageEvent();

		checkf(DamageEvent, TEXT("UCsStatusEffectCoordinator::ProcessStatusEffectEvent: DamageEvent is NULL. No Damage Event found for Event implementing interface: ICsStatusEffectEvent_Damage."));
		
		// Get the implementation to get the container (for quick deallocation).
		if (FCsStatusEffectEvent_DamageImpl* SetDamageEventImpl = FCsLibrary_StatusEffectEvent::SafePureStaticCastChecked<FCsStatusEffectEvent_DamageImpl>(Str::ProcessStatusEffectEvent, const_cast<ICsStatusEffectEvent*>(Event)))
		{
			FCsResource_DamageEvent* DamageEventContainer = SetDamageEventImpl->DamageEventContainer;

			checkf(DamageEventContainer, TEXT("UCsStatusEffectCoordinator::ProcessStatusEffectEvent: DamageEventContainer is NULL."));

			UCsManager_Damage::Get(MyRoot)->ProcessDamageEventContainer(DamageEventContainer);
		}
		else
		{
			UCsManager_Damage::Get(MyRoot)->ProcessDamageEvent(DamageEvent);
		}
	}
}

void UCsStatusEffectCoordinator::ProcessStatusEffectEventContainer(const FCsResource_StatusEffectEvent* Event)
{
	using namespace NCsStatusEffectCoordinatorCached;

	// Get Type
	const FECsStatusEffectEvent& Type = GetTypeFromEvent(const_cast<FCsResource_StatusEffectEvent*>(Event));

	FCsManager_StatusEffectEvent& Manager_Event = Manager_Events[Type.GetValue()];

	check(Manager_Event.IsValidChecked(Str::ProcessStatusEffectEventContainer, Event));

	const ICsStatusEffectEvent* IEvent = Event->Get();
	// Process Event
	ProcessStatusEffectEvent(IEvent);
	// Deallocate Event when finished
	Manager_Event.Deallocate(const_cast<FCsResource_StatusEffectEvent*>(Event));
}

#pragma endregion Event

// Log
#pragma region

/*
void UCsStatusEffectCoordinator::LogEventPoint(const ICsDamageEvent* Event)
{
	ICsDamageExpression* Expression = Event->GetExpression();

	if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerDamageEvents))
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Damage::OnEvent:"));
		// Expression
		UE_LOG(LogCs, Warning, TEXT("- Expression: Point"));
		UE_LOG(LogCs, Warning, TEXT("-- Damage: %f"), Expression->GetDamage());
		UE_LOG(LogCs, Warning, TEXT("-- Type: %s"), Expression->GetType().ToChar());
		// Instigator
		UE_LOG(LogCs, Warning, TEXT("- Instigator: %s"), Event->GetInstigator() ? *(Event->GetInstigator()->GetName()) : TEXT("None"));
		// Causer
		UE_LOG(LogCs, Warning, TEXT("- Causer: %s"), Event->GetCauser() ? *(Event->GetCauser()->GetName()) : TEXT("None"));
		// HitResult
		const FHitResult& HitResult = Event->GetHitResult();

		UE_LOG(LogCs, Warning, TEXT("- HitResult"));
		UE_LOG(LogCs, Warning, TEXT("-- bBlockingHit: %s"), HitResult.bBlockingHit ? TEXT("True") : TEXT("False"));
		UE_LOG(LogCs, Warning, TEXT("-- bStartPenetrating"), HitResult.bStartPenetrating ? TEXT("True") : TEXT("False"));
		UE_LOG(LogCs, Warning, TEXT("-- Time: %f"), HitResult.Time);
		UE_LOG(LogCs, Warning, TEXT("-- Location: %s"), *(HitResult.Location.ToString()));
		UE_LOG(LogCs, Warning, TEXT("-- ImpactPoint: %s"), *(HitResult.ImpactPoint.ToString()));
		UE_LOG(LogCs, Warning, TEXT("-- Normal: %s"), *(HitResult.Normal.ToString()));
		UE_LOG(LogCs, Warning, TEXT("-- ImpactNormal: %s"), *(HitResult.ImpactNormal.ToString()));
		UE_LOG(LogCs, Warning, TEXT("-- TraceStart: %s"), *(HitResult.TraceStart.ToString()));
		UE_LOG(LogCs, Warning, TEXT("-- TraceEnd: %s"), *(HitResult.TraceEnd.ToString()));
		UE_LOG(LogCs, Warning, TEXT("-- PenetrationDepth: %f"), HitResult.PenetrationDepth);
		UE_LOG(LogCs, Warning, TEXT("-- Item: %d"), HitResult.Item);
		UE_LOG(LogCs, Warning, TEXT("-- PhysMaterial: %s"), HitResult.PhysMaterial.IsValid() ? *(HitResult.PhysMaterial->GetName()) : TEXT("None"));
		UE_LOG(LogCs, Warning, TEXT("-- Actor: %s"), HitResult.Actor.IsValid() ? *(HitResult.Actor->GetName()) : TEXT("None"));
		UE_LOG(LogCs, Warning, TEXT("-- Component: %s"), HitResult.Component.IsValid() ? *(HitResult.Component->GetName()) : TEXT("None"));
		UE_LOG(LogCs, Warning, TEXT("-- BoneName: %s"), HitResult.BoneName.IsValid() ? *(HitResult.BoneName.ToString()) : TEXT("None"));
		UE_LOG(LogCs, Warning, TEXT("-- FaceIndex: %d"), HitResult.FaceIndex);
	}
}
*/
#pragma endregion Log
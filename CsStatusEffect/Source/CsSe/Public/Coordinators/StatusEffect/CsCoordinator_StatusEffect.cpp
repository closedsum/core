// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Coordinators/StatusEffect/CsCoordinator_StatusEffect.h"
#include "CsSe.h"

// CVar
#include "Coordinators/StatusEffect/CsCVars_Coordinator_StatusEffect.h"
// Library
#include "Library/CsLibrary_Common.h"
#include "Data/CsLibrary_Data_StatusEffect.h"
#include "Event/CsLibrary_StatusEffectEvent.h"
// Managers
#include "Managers/StatusEffect/CsManager_StatusEffect.h"
#include "Managers/StatusEffect/CsGetManagerStatusEffect.h"
#include "Managers/Damage/CsManager_Damage.h"
// StatusEffect
#include "Data/Shape/CsData_StatusEffect_Shape.h"
#include "CsReceiveStatusEffect.h"
#include "Data/Damage/CsData_StatusEffect_Damage.h"
#include "Event/CsStatusEffectEventImpl.h"
#include "Event/Damage/CsStatusEffectEvent_DamageImpl.h"
// Unique
#include "UniqueObject/CsUniqueObject.h"

#if WITH_EDITOR
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Coordinators/StatusEffect/CsGetCoordinatorStatusEffect.h"

#include "Library/CsLibrary_Common.h"

#include "Engine/World.h"
#include "Engine/Engine.h"

#include "GameFramework/GameStateBase.h"
#endif // #if WITH_EDITOR

// Cached
#pragma region

namespace NCsCoordinator_StatusEffectCached
{
	namespace Str
	{
		CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsCoordinator_StatusEffect, GetTypeFromEvent);
		CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsCoordinator_StatusEffect, ProcessStatusEffectEvent);
		CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsCoordinator_StatusEffect, ProcessStatusEffectEventContainer);
	}
}

#pragma endregion Cached

// static initializations
UCsCoordinator_StatusEffect* UCsCoordinator_StatusEffect::s_Instance;
bool UCsCoordinator_StatusEffect::s_bShutdown = false;

UCsCoordinator_StatusEffect::UCsCoordinator_StatusEffect(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

// Singleton
#pragma region

/*static*/ UCsCoordinator_StatusEffect* UCsCoordinator_StatusEffect::Get(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetCoordinatorStatusEffect(InRoot)->GetCoordinator_StatusEffect();
#else
	if (s_bShutdown)
	{
		UE_LOG(LogCsSe, Warning, TEXT("UCsCoordinator_StatusEffect::Get: Coordinator has already shutdown."));
		return nullptr;
	}
	return s_Instance;
#endif // #if WITH_EDITOR
}

/*static*/ bool UCsCoordinator_StatusEffect::IsValid(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetCoordinatorStatusEffect(InRoot)->GetCoordinator_StatusEffect() != nullptr;
#else
	return s_Instance != nullptr;
#endif // #if WITH_EDITOR
}

/*static*/ void UCsCoordinator_StatusEffect::Init(UObject* InRoot, TSubclassOf<UCsCoordinator_StatusEffect> CoordinatorStatusEffectClass, UObject* InOuter /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetCoordinatorStatusEffect* GetCoordinatorStatusEffect = Get_GetCoordinatorStatusEffect(InRoot);

	UCsCoordinator_StatusEffect* Coordinator_StatusEffect = GetCoordinatorStatusEffect->GetCoordinator_StatusEffect();

	if (!Coordinator_StatusEffect)
	{
		Coordinator_StatusEffect = NewObject<UCsCoordinator_StatusEffect>(InOuter ? InOuter : InRoot, CoordinatorStatusEffectClass, TEXT("Coorindator_Status_Effect_Singleton"), RF_Transient | RF_Public);

		GetCoordinatorStatusEffect->SetCoordinator_StatusEffect(Coordinator_StatusEffect);

		Coordinator_StatusEffect->SetMyRoot(InRoot);
		Coordinator_StatusEffect->Initialize();
	}
	else
	{
		UE_LOG(LogCsSe, Warning, TEXT("UCsCoordinator_StatusEffect::Init: Init has already been called."));
	}
#else
	s_bShutdown = false;

	if (!s_Instance)
	{
		s_Instance = NewObject<UCsCoordinator_StatusEffect>(GetTransientPackage(), CoordinatorStatusEffectClass, TEXT("Coorindator_Status_Effect_Singleton"), RF_Transient | RF_Public);
		s_Instance->AddToRoot();
		s_Instance->SetMyRoot(InRoot);
		s_Instance->Initialize();
	}
	else
	{
		UE_LOG(LogCsSe, Warning, TEXT("UCsCoordinator_StatusEffect::Init: Init has already been called."));
	}
#endif // #if WITH_EDITOR
}

/*static*/ void UCsCoordinator_StatusEffect::Shutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetCoordinatorStatusEffect* GetCoordinatorStatusEffect = Get_GetCoordinatorStatusEffect(InRoot);
	UCsCoordinator_StatusEffect* Coordinator_StatusEffect	  = GetCoordinatorStatusEffect->GetCoordinator_StatusEffect();
	Coordinator_StatusEffect->CleanUp();

	GetCoordinatorStatusEffect->SetCoordinator_StatusEffect(nullptr);
#else
	if (!s_Instance)
	{
		UE_LOG(LogCsSe, Warning, TEXT("UCsCoordinator_StatusEffect::Shutdown: Coorindator has already been shutdown."));
		return;
	}

	s_Instance->CleanUp();
	s_Instance->RemoveFromRoot();
	s_Instance = nullptr;
	s_bShutdown = true;
#endif // #if WITH_EDITOR
}

/*static*/ bool UCsCoordinator_StatusEffect::HasShutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetCoordinatorStatusEffect(InRoot)->GetCoordinator_StatusEffect() == nullptr;
#else
	return s_bShutdown;
#endif // #if WITH_EDITOR
}

#if WITH_EDITOR

/*static*/ ICsGetCoordinatorStatusEffect* UCsCoordinator_StatusEffect::Get_GetCoordinatorStatusEffect(UObject* InRoot)
{
	checkf(InRoot, TEXT("UCsCoordinator_StatusEffect::Get_GetCoordinatorStatusEffect: InRoot is NULL."));

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("UCsCoordinator_StatusEffect::Get_GetCoordinatorStatusEffect: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("UCsCoordinator_StatusEffect::Get_GetCoordinatorStatusEffect: Manager_Singleton is NULL."));

	ICsGetCoordinatorStatusEffect* GetCoorindatorStatusEffect = Cast<ICsGetCoordinatorStatusEffect>(Manager_Singleton);

	checkf(GetCoorindatorStatusEffect, TEXT("UCsCoordinator_StatusEffect::Get_GetCoordinatorStatusEffect: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsGetCoordinatorStatusEffect."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

	return GetCoorindatorStatusEffect;
}

/*static*/ ICsGetCoordinatorStatusEffect* UCsCoordinator_StatusEffect::GetSafe_GetCoordinatorStatusEffect(UObject* Object)
{
	if (!Object)
	{
		UE_LOG(LogCsSe, Warning, TEXT("UCsCoordinator_StatusEffect::GetSafe_GetCoordinatorStatusEffect: Object is NULL."));
		return nullptr;
	}

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(Object);

	if (!GetManagerSingleton)
	{
		UE_LOG(LogCsSe, Warning, TEXT("UCsManager_Damage::GetSafe_GetCoordinatorStatusEffect: Object: %s does NOT implement the interface: ICsGetManagerSingleton."), *(Object->GetName()));
		return nullptr;
	}

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	if (!Manager_Singleton)
	{
		UE_LOG(LogCsSe, Warning, TEXT("UCsManager_Damage::GetSafe_GetCoordinatorStatusEffect: Failed to get object of type: UCsManager_Singleton from Object: %s."), *(Object->GetName()));
		return nullptr;
	}

	return Cast<ICsGetCoordinatorStatusEffect>(Manager_Singleton);
}

/*static*/ UCsCoordinator_StatusEffect* UCsCoordinator_StatusEffect::GetSafe(UObject* Object)
{
	if (ICsGetCoordinatorStatusEffect* GetCoordinatorStatusEffect = GetSafe_GetCoordinatorStatusEffect(Object))
		return GetCoordinatorStatusEffect->GetCoordinator_StatusEffect();
	return nullptr;
}

/*static*/ UCsCoordinator_StatusEffect* UCsCoordinator_StatusEffect::GetFromWorldContextObject(const UObject* WorldContextObject)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		// Game State
		if (UCsCoordinator_StatusEffect* Manager = GetSafe(World->GetGameState()))
			return Manager;

		UE_LOG(LogCsSe, Warning, TEXT("UCsCoordinator_StatusEffect::GetFromWorldContextObject: Failed to Manager Item of type UCsCoordinator_StatusEffect from GameState."));

		return nullptr;
	}
	else
	{
		return nullptr;
	}
}

#endif // #if WITH_EDITOR

void UCsCoordinator_StatusEffect::Initialize()
{
	// TODO: Poll config in future

	const int32& Count = EMCsStatusEffectEvent::Get().Num();

	Manager_Events.Reset(Count);
	Manager_Events.AddDefaulted(Count);

	for (const FECsStatusEffectEvent& Event : EMCsStatusEffectEvent::Get())
	{
		FCsManager_StatusEffectEvent& Manager = Manager_Events[Event.GetValue()];
		
		const FString Name = FString::Printf(TEXT("UCsCoordinator_StatusEffect::FCsManager_StatusEffectEvent[%s]"), Event.ToChar());

		Manager.SetName(Name);
		Manager.SetDeconstructResourcesOnShutdown();

		const int32 PoolSize = 64;

		Manager.CreatePool(PoolSize);

		for (int32 I = 0; I < PoolSize; ++I)
		{
			typedef NCsStatusEffect::NEvent::IEvent EventInterfaceType;

			EventInterfaceType* IEvent = ConstructEvent(Event);

			checkf(IEvent, TEXT("UCsCoordinator_StatusEffect::Initialize: Failed to construct event for type: %s."), Event.ToChar());

			Manager.Add(IEvent);
		} 
	}

	bInitialized = true;
}

/*static*/ bool UCsCoordinator_StatusEffect::HasInitialized(UObject* InRoot)
{
	if (!HasShutdown(InRoot))
		return Get(InRoot)->bInitialized;
	return false;
}

void UCsCoordinator_StatusEffect::CleanUp()
{
	for (const FECsStatusEffectEvent& Event : EMCsStatusEffectEvent::Get())
	{
		FCsManager_StatusEffectEvent& Manager = Manager_Events[Event.GetValue()];

		Manager.Shutdown();
	}
	Manager_Events.Reset();

	bInitialized = false;
}

	// Root
#pragma region

void UCsCoordinator_StatusEffect::SetMyRoot(UObject* InRoot)
{
	MyRoot = InRoot;
}

#pragma endregion Root

#pragma endregion Singleton

// Receive Status Effect
#pragma region

void UCsCoordinator_StatusEffect::Add(ICsReceiveStatusEffect* Object)
{
	checkf(Object, TEXT("UCsCoordinator_StatusEffect::Add: Object is NULL."));

	UObject* O = Object->_getUObject();

	checkf(O, TEXT("UCsCoordinator_StatusEffect::Add: Object is NOT a UObject."));

	UClass* Class = O->GetClass();

	checkf(Class->ImplementsInterface(UCsUniqueObject::StaticClass()), TEXT("UCsCoordinator_StatusEffect::Add: Object: %s with Class: %s does NOT implement interface: ICsUniqueObject."), *(O->GetName()), *(Class->GetName()));

	// TODO: Need to look at script objects
	ICsUniqueObject* UniqueObject = Cast<ICsUniqueObject>(O);

	checkf(UniqueObject, TEXT("UCsCoordinator_StatusEffect::Add: Object: %s with Class: %s does NOT implement interface: ICsUniqueObject."), *(O->GetName()), *(Class->GetName()));

	const FCsUniqueObjectId& Id = UniqueObject->GetId();

	ReceiveStatusEffectMap.Add(Id, Object);
}

void UCsCoordinator_StatusEffect::Remove(ICsReceiveStatusEffect* Object)
{
	checkf(Object, TEXT("UCsCoordinator_StatusEffect::Remove: Object is NULL."));

	UObject* O = Object->_getUObject();

	checkf(O, TEXT("UCsCoordinator_StatusEffect::Remove: Object is NOT a UObject."));

	UClass* Class = O->GetClass();

	checkf(Class->ImplementsInterface(UCsUniqueObject::StaticClass()), TEXT("UCsCoordinator_StatusEffect::Remove: Object: %s with Class: %s does NOT implement interface: ICsUniqueObject."), *(O->GetName()), *(Class->GetName()));

	// TODO: Need to look at script objects
	ICsUniqueObject* UniqueObject = Cast<ICsUniqueObject>(O);

	checkf(UniqueObject, TEXT("UCsCoordinator_StatusEffect::Remove: Object: %s with Class: %s does NOT implement interface: ICsUniqueObject."), *(O->GetName()), *(Class->GetName()));

	const FCsUniqueObjectId& Id = UniqueObject->GetId();

	ReceiveStatusEffectMap.Remove(Id);
}

#pragma endregion Receive Damage

// Event
#pragma region

NCsStatusEffect::NEvent::IEvent* UCsCoordinator_StatusEffect::ConstructEvent(const FECsStatusEffectEvent& Type)
{
	// Default
	if (Type == NCsStatusEffectEvent::Default)
		return new NCsStatusEffect::NEvent::FImpl();
	// Damage
	if (Type == NCsStatusEffectEvent::Damage)
		return new NCsStatusEffect::NEvent::NDamage::FImpl();
	return nullptr;
}

FCsResource_StatusEffectEvent* UCsCoordinator_StatusEffect::AllocateEvent(const FECsStatusEffectEvent& Type)
{
	return Manager_Events[Type.GetValue()].Allocate();
}

const FECsStatusEffectEvent& UCsCoordinator_StatusEffect::GetEventType(const FString& Context, const NCsStatusEffect::NEvent::IEvent* Event)
{
	checkf(Event, TEXT("%s: Event is NULL."), *Context);

	// Damage
	if (FCsLibrary_StatusEffectEvent::GetSafeInterfaceChecked<NCsStatusEffect::NEvent::NDamage::IDamage>(Context, Event))
		return NCsStatusEffectEvent::Damage;
	return NCsStatusEffectEvent::Default;
}

const FECsStatusEffectEvent& UCsCoordinator_StatusEffect::GetEventType(const FString& Context, const FCsResource_StatusEffectEvent* Event)
{
	checkf(Event, TEXT("%s: Event is NULL."), *Context);

	return GetEventType(Context, Event->Get());
}

void UCsCoordinator_StatusEffect::DeallocateEvent(const FString& Context, FCsResource_StatusEffectEvent* Event)
{
	const FECsStatusEffectEvent& Type = GetEventType(Context, Event);

	// Reset
	if (ICsReset* IReset = FCsLibrary_StatusEffectEvent::GetSafeInterfaceChecked<ICsReset>(Context, Event->Get()))
		IReset->Reset();

	Manager_Events[Type.GetValue()].Deallocate(Event);
}

bool UCsCoordinator_StatusEffect::CopyEvent(const FString& Context, const NCsStatusEffect::NEvent::IEvent* From, NCsStatusEffect::NEvent::IEvent* To)
{
	return FCsLibrary_StatusEffectEvent::CopyChecked(Context, From, To);
}

FCsResource_StatusEffectEvent* UCsCoordinator_StatusEffect::CreateCopyOfEvent(const FString& Context, const NCsStatusEffect::NEvent::IEvent* Event)
{
	const FECsStatusEffectEvent& EventType = GetEventType(Context, Event);

	checkf(EMCsStatusEffectEvent::Get().IsValidEnum(EventType), TEXT("%s: EventType: %s is NOT Valid."), EventType.ToChar());

	FCsResource_StatusEffectEvent* Container = AllocateEvent(EventType);
	NCsStatusEffect::NEvent::IEvent* Copy	 = Container->Get();

	bool Success = CopyEvent(Context, Event, Copy);

	checkf(Success, TEXT("%s: Failed to create copy of Event."), *Context);

	return Container;
}

FCsResource_StatusEffectEvent* UCsCoordinator_StatusEffect::CreateCopyOfEvent(const FString& Context, const FCsResource_StatusEffectEvent* Event)
{
	return CreateCopyOfEvent(Context, Event->Get());
}

void UCsCoordinator_StatusEffect::ProcessStatusEffectEvent(const NCsStatusEffect::NEvent::IEvent* Event)
{
	using namespace NCsCoordinator_StatusEffectCached;

	const FString& Context = Str::ProcessStatusEffectEvent;

	checkf(Event, TEXT("%s: Event is NULL."), *Context);

	ICsData_StatusEffect* Data = Event->GetData();

	checkf(Data, TEXT("%s: Data is NULL. No Status Effect found for Event."), *Context);

	const FCsStatusEffectTriggerFrequencyParams& TriggerParams   = Data->GetTriggerFrequencyParams();
	const FCsStatusEffectTransferFrequencyParams& TransferParams = Data->GetTransferFrequencyParams();

	// TODO: Need to check for Shape

	// Check for Status Effects will no transfer / pass through and will be consumed immediately
	if (TriggerParams.Type == ECsStatusEffectTriggerFrequency::Once &&
		TransferParams.Type == ECsStatusEffectTransferFrequency::None)
	{
		// NCsStatusEffect::NEvent::NDamage::IDamage
		if (const NCsStatusEffect::NEvent::NDamage::IDamage* SeDamageEvent = FCsLibrary_StatusEffectEvent::GetSafeInterfaceChecked<NCsStatusEffect::NEvent::NDamage::IDamage>(Context, Event))
		{
			// Get the DamageEvent
			const NCsDamage::NEvent::IEvent* DamageEvent = SeDamageEvent->GetDamageEvent();

			checkf(DamageEvent, TEXT("%s: DamageEvent is NULL. No Damage Event found for Event implementing interface: NCsStatusEffect::NEvent::NDamage::IDamage."), *Context);

			UCsManager_Damage::Get(MyRoot)->ProcessDamageEvent(DamageEvent);
		}
		else
		{

		}
	}
	else
	{
		// ICsData_StatusEffect_Shape
		if (ICsData_StatusEffect_Shape* ShapeData = FCsLibrary_Data_StatusEffect::GetSafeInterfaceChecked<ICsData_StatusEffect_Shape>(Context, Data))
		{

		}
		// Point
		else
		{
			if (UObject* Receiver = Event->GetReceiver())
			{
				if (Receiver->GetClass()->ImplementsInterface(UCsReceiveStatusEffect::StaticClass()))
				{
					Local_Receivers.AddDefaulted();
					Local_Receivers.Last().SetObject(Receiver);

					// Copy the Event
					FCsResource_StatusEffectEvent* EventContainer = CreateCopyOfEvent(Context, Event);

					Local_Events.Add(EventContainer);
				}
			}
		}
	}

	const int32 Count = Local_Receivers.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		FCsReceiveStatusEffect& Receiver			  = Local_Receivers[I];
		FCsResource_StatusEffectEvent* EventContainer = Local_Events[I];

		NCsStatusEffect::NEvent::IEvent* Evt = EventContainer->Get();

		if (Receiver.Implements_ICsGetManagerStatusEffect())
		{
			UCsManager_StatusEffect* Manager_StatusEffect = Receiver.GetManager_StatusEffect();

			Manager_StatusEffect->ApplyStatusEffect(const_cast<NCsStatusEffect::NEvent::IEvent*>(Event));
		}
		else
		{
			Receiver.ApplyStatusEffect(Event);
		}

#if !UE_BUILD_SHIPPING
		//LogEvent(Evt);
#endif // #if !UE_BUILD_SHIPPING

		//OnProcessDamageEvent_Event.Broadcast(Evt);
		DeallocateEvent(Context, EventContainer);

		Local_Events[I] = nullptr;
	}

	Local_Receivers.Reset(Local_Receivers.Max());
	Local_Events.Reset(Local_Events.Max());
}

void UCsCoordinator_StatusEffect::ProcessStatusEffectEventContainer(const FCsResource_StatusEffectEvent* Event)
{
	using namespace NCsCoordinator_StatusEffectCached;

	const FString& Context = Str::ProcessStatusEffectEventContainer;

	// Get Type
	const FECsStatusEffectEvent& Type			= GetEventType(Context, Event);
	FCsManager_StatusEffectEvent& Manager_Event = Manager_Events[Type.GetValue()];

	check(Manager_Event.IsValidChecked(Context, Event));

	const NCsStatusEffect::NEvent::IEvent* IEvent = Event->Get();
	// Process Event
	ProcessStatusEffectEvent(IEvent);
	// Deallocate Event when finished
	DeallocateEvent(Context, const_cast<FCsResource_StatusEffectEvent*>(Event));
}

#pragma endregion Event

// Log
#pragma region

/*
void UCsCoordinator_StatusEffect::LogEventPoint(const NCsDamage::NEvent::IEvent* Event)
{
	ICsData_Damage* Data = Event->GetData();

	if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerDamageEvents))
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Damage::OnEvent:"));
		// Data
		UE_LOG(LogCs, Warning, TEXT("- Data: Point"));
		UE_LOG(LogCs, Warning, TEXT("-- Damage: %f"), Data->GetDamage());
		UE_LOG(LogCs, Warning, TEXT("-- Type: %s"), Data->GetType().ToChar());
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
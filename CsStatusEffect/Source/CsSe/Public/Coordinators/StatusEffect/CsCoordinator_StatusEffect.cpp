// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Coordinators/StatusEffect/CsCoordinator_StatusEffect.h"
#include "CsSe.h"

// CVar
#include "Coordinators/StatusEffect/CsCVars_Coordinator_StatusEffect.h"
// Library
#include "Data/CsLibrary_Data_StatusEffect.h"
#include "Event/CsLibrary_StatusEffectEvent.h"
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/StatusEffect/CsManager_StatusEffect.h"
#include "Managers/StatusEffect/CsGetManagerStatusEffect.h"
#include "Managers/Damage/CsManager_Damage.h"
// Data
#include "Data/Trigger/CsData_StatusEffect_Trigger.h"
#include "Data/Shape/CsData_StatusEffect_Shape.h"
#include "Data/Damage/CsData_StatusEffect_Damage.h"
// StatusEffect
#include "CsReceiveStatusEffect.h"
#include "Event/CsStatusEffectEventImpl.h"
#include "Event/Damage/CsStatusEffectEvent_DamageImpl.h"
// Unique
#include "UniqueObject/CsUniqueObject.h"

#if WITH_EDITOR
// Library
#include "Coordinators/StatusEffect/CsLibrary_Coordinator_StatusEffect.h"
// Singleton
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Coordinators/StatusEffect/CsGetCoordinatorStatusEffect.h"
#endif // #if WITH_EDITOR

// Cached
#pragma region

namespace NCsCoordinatorStatusEffect
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsCoordinator_StatusEffect, GetTypeFromEvent);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsCoordinator_StatusEffect, ProcessStatusEffectEvent);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsCoordinator_StatusEffect, ProcessStatusEffectEventContainer);
		}
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

#if WITH_EDITOR

/*static*/ UCsCoordinator_StatusEffect* UCsCoordinator_StatusEffect::Get(const UObject* InRoot /*=nullptr*/)
{
	return Get_GetCoordinatorStatusEffect(InRoot)->GetCoordinator_StatusEffect();
}

/*static*/ UCsCoordinator_StatusEffect* UCsCoordinator_StatusEffect::GetSafe(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) /*=nullptr*/)
{
	if (ICsGetCoordinatorStatusEffect* GetCoordinatorStatusEffect = GetSafe_GetCoordinatorStatusEffect(Context, InRoot, Log))
		return GetCoordinatorStatusEffect->GetCoordinator_StatusEffect();
	return nullptr;
}

/*static*/ bool UCsCoordinator_StatusEffect::IsValid(const UObject* InRoot /*=nullptr*/)
{
	return Get_GetCoordinatorStatusEffect(InRoot)->GetCoordinator_StatusEffect() != nullptr;
}

#endif // #if WITH_EDITOR

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

/*static*/ void UCsCoordinator_StatusEffect::Shutdown(const UObject* InRoot /*=nullptr*/)
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

/*static*/ bool UCsCoordinator_StatusEffect::HasShutdown(const UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetCoordinatorStatusEffect(InRoot)->GetCoordinator_StatusEffect() == nullptr;
#else
	return s_bShutdown;
#endif // #if WITH_EDITOR
}

#if WITH_EDITOR

/*static*/ ICsGetCoordinatorStatusEffect* UCsCoordinator_StatusEffect::Get_GetCoordinatorStatusEffect(const UObject* InRoot)
{
	checkf(InRoot, TEXT("UCsCoordinator_StatusEffect::Get_GetCoordinatorStatusEffect: InRoot is NULL."));

	const ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("UCsCoordinator_StatusEffect::Get_GetCoordinatorStatusEffect: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("UCsCoordinator_StatusEffect::Get_GetCoordinatorStatusEffect: Manager_Singleton is NULL."));

	ICsGetCoordinatorStatusEffect* GetCoorindatorStatusEffect = Cast<ICsGetCoordinatorStatusEffect>(Manager_Singleton);

	checkf(GetCoorindatorStatusEffect, TEXT("UCsCoordinator_StatusEffect::Get_GetCoordinatorStatusEffect: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsGetCoordinatorStatusEffect."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

	return GetCoorindatorStatusEffect;
}

/*static*/ ICsGetCoordinatorStatusEffect* UCsCoordinator_StatusEffect::GetSafe_GetCoordinatorStatusEffect(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) /*=nullptr*/)
{
	CS_IS_PTR_NULL_RET_NULL(InRoot)

	const ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	if (!GetManagerSingleton)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *Context, *(InRoot->GetName()), *(InRoot->GetClass()->GetName())));
		return nullptr;
	}

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	if (!Manager_Singleton)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Manager_Singleton from InRoot: %s with Class: %s."), *Context, *(InRoot->GetName()), *(InRoot->GetClass()->GetName())));
		return nullptr;
	}
	return Cast<ICsGetCoordinatorStatusEffect>(Manager_Singleton);
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
		typedef NCsStatusEffect::NEvent::FManager EventManagerType;

		EventManagerType& Manager = Manager_Events[Event.GetValue()];
		
		const FString Name = FString::Printf(TEXT("UCsCoordinator_StatusEffect::Manager_Events[%s]"), Event.ToChar());

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

/*static*/ bool UCsCoordinator_StatusEffect::HasInitialized(const UObject* InRoot)
{
	if (!HasShutdown(InRoot))
		return Get(InRoot)->bInitialized;
	return false;
}

void UCsCoordinator_StatusEffect::CleanUp()
{
	typedef NCsStatusEffect::NEvent::FManager EventManagerType;

	for (const FECsStatusEffectEvent& Event : EMCsStatusEffectEvent::Get())
	{
		EventManagerType& Manager = Manager_Events[Event.GetValue()];

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

#define EventResourceType NCsStatusEffect::NEvent::FResource
#define EventType NCsStatusEffect::NEvent::IEvent

EventType* UCsCoordinator_StatusEffect::ConstructEvent(const FECsStatusEffectEvent& Type)
{
	// Default
	if (Type == NCsStatusEffectEvent::Default)
		return new NCsStatusEffect::NEvent::FImpl();
	// Damage
	if (Type == NCsStatusEffectEvent::Damage)
		return new NCsStatusEffect::NEvent::NDamage::FImpl();
	return nullptr;
}

EventResourceType* UCsCoordinator_StatusEffect::AllocateEvent(const FECsStatusEffectEvent& Type)
{
	return Manager_Events[Type.GetValue()].Allocate();
}

const FECsStatusEffectEvent& UCsCoordinator_StatusEffect::GetEventType(const FString& Context, const NCsStatusEffect::NEvent::IEvent* Event)
{
	typedef NCsStatusEffect::NEvent::FLibrary SeEventLibrary;

	// Damage
	if (SeEventLibrary::GetSafeInterfaceChecked<NCsStatusEffect::NEvent::NDamage::IDamage>(Context, Event))
		return NCsStatusEffectEvent::Damage;
	return NCsStatusEffectEvent::Default;
}

const FECsStatusEffectEvent& UCsCoordinator_StatusEffect::GetEventType(const FString& Context, const EventResourceType* Event)
{
	CS_IS_PTR_NULL_CHECKED(Event)

	return GetEventType(Context, Event->Get());
}

void UCsCoordinator_StatusEffect::DeallocateEvent(const FString& Context, EventResourceType* Event)
{
	const FECsStatusEffectEvent& Type = GetEventType(Context, Event);

	typedef NCsStatusEffect::NEvent::FLibrary SeEventLibrary;

	// Reset
	if (ICsReset* IReset = SeEventLibrary::GetSafeInterfaceChecked<ICsReset>(Context, Event->Get()))
		IReset->Reset();

	Manager_Events[Type.GetValue()].Deallocate(Event);
}

bool UCsCoordinator_StatusEffect::CopyEvent(const FString& Context, const EventType* From, EventType* To)
{
	return NCsStatusEffect::NEvent::FLibrary::CopyChecked(Context, From, To);
}

EventResourceType* UCsCoordinator_StatusEffect::CreateCopyOfEvent(const FString& Context, const EventType* Event)
{
	const FECsStatusEffectEvent& Type = GetEventType(Context, Event);

	checkf(EMCsStatusEffectEvent::Get().IsValidEnum(Type), TEXT("%s: EventType: %s is NOT Valid."), Type.ToChar());

	EventResourceType* Container = AllocateEvent(Type);
	EventType* Copy				 = Container->Get();

	bool Success = CopyEvent(Context, Event, Copy);

	checkf(Success, TEXT("%s: Failed to create copy of Event."), *Context);

	return Container;
}

EventResourceType* UCsCoordinator_StatusEffect::CreateCopyOfEvent(const FString& Context, const EventResourceType* Event)
{
	CS_IS_PTR_NULL_CHECKED(Event)

	return CreateCopyOfEvent(Context, Event->Get());
}

void UCsCoordinator_StatusEffect::ProcessStatusEffectEvent(const EventType* Event)
{
	using namespace NCsCoordinatorStatusEffect::NCached;

	const FString& Context = Str::ProcessStatusEffectEvent;

	CS_IS_PTR_NULL_CHECKED(Event)

	typedef NCsStatusEffect::NData::IData DataType;

	DataType* Data = Event->GetData();

	checkf(Data, TEXT("%s: Data is NULL. No Status Effect found for Event."), *Context);

	typedef NCsStatusEffect::NData::FLibrary SeDataLibrary;
	typedef NCsStatusEffect::NData::NTrigger::ITrigger TriggerDataType;

	if (TriggerDataType* TriggerData = SeDataLibrary::GetInterfaceChecked<TriggerDataType>(Context, Data))
	{
		typedef NCsStatusEffect::NTrigger::FFrequencyParams TriggerFrequencyParamsType;
		typedef NCsStatusEffect::NTransfer::FFrequencyParams TransferFrequencyParamsType;

		const TriggerFrequencyParamsType& TriggerParams = TriggerData->GetTriggerFrequencyParams();
		const TransferFrequencyParamsType& TransferParams = TriggerData->GetTransferFrequencyParams();

		// TODO: Need to check for Shape

		// Check for Status Effects will no transfer / pass through and will be consumed immediately
		typedef NCsStatusEffect::NTrigger::EFrequency TriggerFrequencyType;
		typedef NCsStatusEffect::NTransfer::EFrequency TransferFrequencyType;

		if (TriggerParams.Type == TriggerFrequencyType::Once &&
			TransferParams.Type == TransferFrequencyType::None)
		{
			// SeDamageEventType (NCsStatusEffect::NEvent::NDamage::IDamage)

			typedef NCsStatusEffect::NEvent::FLibrary SeEventLibrary;
			typedef NCsStatusEffect::NEvent::NDamage::IDamage SeDamageEventType;

			if (const SeDamageEventType* SeDamageEvent = SeEventLibrary::GetSafeInterfaceChecked<SeDamageEventType>(Context, Event))
			{
				// Get the DamageEvent
				typedef NCsDamage::NEvent::IEvent DamageEventType;

				const DamageEventType* DamageEvent = SeDamageEvent->GetDamageEvent();

				checkf(DamageEvent, TEXT("%s: DamageEvent is NULL. No Damage Event found for Event implementing interface: NCsStatusEffect::NEvent::NDamage::IDamage."), *Context);

				UCsManager_Damage::Get(MyRoot)->ProcessDamageEvent(DamageEvent);
			}
			else
			{

			}
		}
	}
	else
	{
		// ShapeDataType
		typedef NCsStatusEffect::NData::NShape::IShape ShapeDataType;

		if (ShapeDataType* ShapeData = SeDataLibrary::GetSafeInterfaceChecked<ShapeDataType>(Context, Data))
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
					EventResourceType* EventContainer = CreateCopyOfEvent(Context, Event);

					Local_Events.Add(EventContainer);
				}
			}
		}
	}

	const int32 Count = Local_Receivers.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		FCsReceiveStatusEffect& Receiver  = Local_Receivers[I];
		EventResourceType* EventContainer = Local_Events[I];

		EventType* Evt = EventContainer->Get();

		if (Receiver.Implements_ICsGetManagerStatusEffect())
		{
			UCsManager_StatusEffect* Manager_StatusEffect = Receiver.GetManager_StatusEffect();

			Manager_StatusEffect->ApplyStatusEffect(const_cast<EventType*>(Event));
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

void UCsCoordinator_StatusEffect::ProcessStatusEffectEventContainer(const EventResourceType* Event)
{
	using namespace NCsCoordinatorStatusEffect::NCached;

	const FString& Context = Str::ProcessStatusEffectEventContainer;

	typedef NCsStatusEffect::NEvent::FManager EventManagerType;

	// Get Type
	const FECsStatusEffectEvent& Type = GetEventType(Context, Event);
	EventManagerType& Manager_Event   = Manager_Events[Type.GetValue()];

	check(Manager_Event.IsValidChecked(Context, Event));

	const EventType* IEvent = Event->Get();
	// Process Event
	ProcessStatusEffectEvent(IEvent);
	// Deallocate Event when finished
	DeallocateEvent(Context, const_cast<EventResourceType*>(Event));
}

#undef EventResourceType
#undef EventType

#pragma endregion Event

// Log
#pragma region

/*
void UCsCoordinator_StatusEffect::LogEventPoint(const NCsDamage::NEvent::IEvent* Event)
{
	ICsData_Damage* Data = Event->GetData();

	if (CS_CVAR_LOG_IS_SHOWING(LogManagerDamageEvents))
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
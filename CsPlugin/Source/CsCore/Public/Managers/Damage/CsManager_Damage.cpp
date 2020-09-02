// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/CsManager_Damage.h"
#include "CsCore.h"

// CVar
#include "Managers/Damage/CsCVars_Manager_Damage.h"
// Library
#include "Library/CsLibrary_Common.h"
#include "Managers/Damage/Data/CsLibrary_Data_Damage.h"
#include "Managers/Damage/Value/CsLibrary_DamageValue.h"
#include "Managers/Damage/Range/CsLibrary_DamageRange.h"
#include "Managers/Damage/Event/CsLibrary_DamageEvent.h"
#include "managers/Damage/Modifier/CsLibrary_DamageModifier.h"
// Settings
#include "Settings/CsDeveloperSettings.h"
// Reset
#include "Reset/CsReset.h"
// Damage
#include "Managers/Damage/Event/CsDamageEventImpl.h"
#include "Managers/Damage/Data/CsData_Damage.h"
#include "Managers/Damage/Data/Shape/CsData_DamageShape.h"
#include "Managers/Damage/Value/Point/CsDamageValuePointImpl.h"
#include "Managers/Damage/Value/Range/CsDamageValueRangeImpl.h"
#include "Managers/Damage/Range/CsDamageRangeImpl.h"
// Unique
#include "UniqueObject/CsUniqueObject.h"

#if WITH_EDITOR
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Managers/Damage/CsGetManagerDamage.h"

#include "Library/CsLibrary_Common.h"

#include "Engine/World.h"
#include "Engine/Engine.h"

#include "GameFramework/GameStateBase.h"
#endif // #if WITH_EDITOR

// Cached
#pragma region

namespace NCsManagerDamageCached
{
	namespace Str
	{
		const FString ProcessDamageEvent = TEXT("UCsManager_Damage::ProcessDamageEvent");
		const FString ProcessDamageEventContainer = TEXT("UCsManager_Damage::ProcessDamageEventContainer");
		const FString LogEvent = TEXT("UCsManager_Damage::LogEvent");
	}
}

#pragma endregion Cached

// static initializations
UCsManager_Damage* UCsManager_Damage::s_Instance;
bool UCsManager_Damage::s_bShutdown = false;

UCsManager_Damage::UCsManager_Damage(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

// Singleton
#pragma region

/*static*/ UCsManager_Damage* UCsManager_Damage::Get(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerDamage(InRoot)->GetManager_Damage();
#else
	if (s_bShutdown)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Damage::Get: Manager has already shutdown."));
		return nullptr;
	}
	return s_Instance;
#endif // #if WITH_EDITOR
}

/*static*/ bool UCsManager_Damage::IsValid(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerDamage(InRoot)->GetManager_Damage() != nullptr;
#else
	return s_Instance != nullptr;
#endif // #if WITH_EDITOR
}

/*static*/ void UCsManager_Damage::Init(UObject* InRoot, TSubclassOf<UCsManager_Damage> ManagerDamageClass, UObject* InOuter /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerDamage* GetManagerDamage = Get_GetManagerDamage(InRoot);

	UCsManager_Damage* Manager_Damage = GetManagerDamage->GetManager_Damage();

	if (!Manager_Damage)
	{
		Manager_Damage = NewObject<UCsManager_Damage>(InOuter ? InOuter : InRoot, ManagerDamageClass, TEXT("Manager_Damage_Singleton"), RF_Transient | RF_Public);

		GetManagerDamage->SetManager_Damage(Manager_Damage);

		Manager_Damage->SetMyRoot(InRoot);
		Manager_Damage->Initialize();
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Damage::Init: Init has already been called."));
	}
#else
	s_bShutdown = false;

	if (!s_Instance)
	{
		s_Instance = NewObject<UCsManager_Damage>(GetTransientPackage(), ManagerDamageClass, TEXT("Manager_Damage_Singleton"), RF_Transient | RF_Public);
		s_Instance->AddToRoot();
		s_Instance->SetMyRoot(InRoot);
		s_Instance->Initialize();
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Damage::Init: Init has already been called."));
	}
#endif // #if WITH_EDITOR
}

/*static*/ void UCsManager_Damage::Shutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerDamage* GetManagerDamage = Get_GetManagerDamage(InRoot);
	UCsManager_Damage* Manager_Damage	  = GetManagerDamage->GetManager_Damage();
	Manager_Damage->CleanUp();

	GetManagerDamage->SetManager_Damage(nullptr);
#else
	if (!s_Instance)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Damage::Shutdown: Manager has already been shutdown."));
		return;
	}

	s_Instance->CleanUp();
	s_Instance->RemoveFromRoot();
	s_Instance = nullptr;
	s_bShutdown = true;
#endif // #if WITH_EDITOR
}

/*static*/ bool UCsManager_Damage::HasShutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerDamage(InRoot)->GetManager_Damage() == nullptr;
#else
	return s_bShutdown;
#endif // #if WITH_EDITOR
}

#if WITH_EDITOR

/*static*/ ICsGetManagerDamage* UCsManager_Damage::Get_GetManagerDamage(UObject* InRoot)
{
	checkf(InRoot, TEXT("UCsManager_Damage::Get_GetManagerDamage: InRoot is NULL."));

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("UCsManager_Damage::Get_GetManagerDamage: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("UCsManager_Damage::Get_GetManagerDamage: Manager_Singleton is NULL."));

	ICsGetManagerDamage* GetManagerDamage = Cast<ICsGetManagerDamage>(Manager_Singleton);

	checkf(GetManagerDamage, TEXT("UCsManager_Damage::Get_GetManagerDamage: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsGetManagerDamage."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

	return GetManagerDamage;
}

/*static*/ ICsGetManagerDamage* UCsManager_Damage::GetSafe_GetManagerDamage(UObject* Object)
{
	if (!Object)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Damage::GetSafe_GetManagerDamage: Object is NULL."));
		return nullptr;
	}

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(Object);

	if (!GetManagerSingleton)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Damage::GetSafe_GetManagerDamage: Object: %s does NOT implement the interface: ICsGetManagerSingleton."), *(Object->GetName()));
		return nullptr;
	}

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	if (!Manager_Singleton)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Damage::GetSafe_GetManagerDamage: Failed to get object of type: UCsManager_Singleton from Object: %s."), *(Object->GetName()));
		return nullptr;
	}

	return Cast<ICsGetManagerDamage>(Manager_Singleton);
}

/*static*/ UCsManager_Damage* UCsManager_Damage::GetSafe(UObject* Object)
{
	if (ICsGetManagerDamage* GetManagerDamage = GetSafe_GetManagerDamage(Object))
		return GetManagerDamage->GetManager_Damage();
	return nullptr;
}

/*static*/ UCsManager_Damage* UCsManager_Damage::GetFromWorldContextObject(const UObject* WorldContextObject)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		// Game State
		if (UCsManager_Damage* Manager = GetSafe(World->GetGameState()))
			return Manager;

		UE_LOG(LogCs, Warning, TEXT("UCsManager_Damage::GetFromWorldContextObject: Failed to Manager Item of type UCsManager_Damage from GameState."));

		return nullptr;
	}
	else
	{
		return nullptr;
	}
}

#endif // #if WITH_EDITOR

void UCsManager_Damage::Initialize()
{
	UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>();

	// Event
	{
		// Bind Construct Resource Impl
		Manager_Event.ConstructResourceType_Impl.BindUObject(this, &UCsManager_Damage::ConstructEvent);

		// Create Pool
		const int32& PoolSize = Settings->Manager_Damage.Event.PoolSize;

		Manager_Event.CreatePool(PoolSize);
	}
	// Value
	{
		const int32& Count = EMCsDamageValue::Get().Num();
		
		Manager_Values.Reserve(Count);
		Manager_Values.AddDefaulted(Count);
		
			// Create Pool
		const int32& PoolSize = Settings->Manager_Damage.Value.PoolSize;

		for (const FECsDamageValue& Value : EMCsDamageValue::Get())
		{
			FCsManager_DamageValue& Manager = Manager_Values[Value.GetValue()];

			Manager.SetDeconstructResourcesOnShutdown();
			Manager.CreatePool(PoolSize);

			for (int32 I = 0; I < PoolSize; ++I)
			{
				Manager.Add(ConstructValue(Value));
			}
		}
	}
	// Range
	{
		// Bind Construct Resource Impl
		Manager_Range.ConstructResourceType_Impl.BindUObject(this, &UCsManager_Damage::ConstructRange);

		// Create Pool
		const int32& PoolSize = Settings->Manager_Damage.Range.PoolSize;

		Manager_Range.CreatePool(PoolSize);
	}
	bInitialized = true;
}

/*static*/ bool UCsManager_Damage::HasInitialized(UObject* InRoot)
{
	if (!HasShutdown(InRoot))
		return Get(InRoot)->bInitialized;
	return false;
}

void UCsManager_Damage::CleanUp()
{
	// Event
	Manager_Event.Shutdown();
	// Value
	{
		for (const FECsDamageValue& Value : EMCsDamageValue::Get())
		{
			FCsManager_DamageValue& Manager = Manager_Values[Value.GetValue()];

			Manager.Shutdown();
		}
	}
	// Range
	Manager_Range.Shutdown();

	bInitialized = false;
}

	// Root
#pragma region

void UCsManager_Damage::SetMyRoot(UObject* InRoot)
{
	MyRoot = InRoot;
}

#pragma endregion Root

#pragma endregion Singleton

// Receive Damage
#pragma region

void UCsManager_Damage::Add(ICsReceiveDamage* Object)
{
	checkf(Object, TEXT("UCsManager_Damage::Add: Object is NULL."));

	UObject* O = Object->_getUObject();

	checkf(O, TEXT("UCsManager_Damage::Add: Object is NOT a UObject."));

	UClass* Class = O->GetClass();

	checkf(Class->ImplementsInterface(UCsUniqueObject::StaticClass()), TEXT("UCsManager_Damage::Add: Object: %s with Class: %s does NOT implement interface: ICsUniqueObject."), *(O->GetName()), *(Class->GetName()));

	// TODO: Need to look at script objects
	ICsUniqueObject* UniqueObject = Cast<ICsUniqueObject>(O);

	checkf(UniqueObject, TEXT("UCsManager_Damage::Add: Object: %s with Class: %s does NOT implement interface: ICsUniqueObject."), *(O->GetName()), *(Class->GetName()));

	const FCsUniqueObjectId& Id = UniqueObject->GetId();

	ReceiveDamageMap.Add(Id, Object);
}

void UCsManager_Damage::Remove(ICsReceiveDamage* Object)
{
	checkf(Object, TEXT("UCsManager_Damage::Remove: Object is NULL."));

	UObject* O = Object->_getUObject();

	checkf(O, TEXT("UCsManager_Damage::Remove: Object is NOT a UObject."));

	UClass* Class = O->GetClass();

	checkf(Class->ImplementsInterface(UCsUniqueObject::StaticClass()), TEXT("UCsManager_Damage::Remove: Object: %s with Class: %s does NOT implement interface: ICsUniqueObject."), *(O->GetName()), *(Class->GetName()));

	// TODO: Need to look at script objects
	ICsUniqueObject* UniqueObject = Cast<ICsUniqueObject>(O);

	checkf(UniqueObject, TEXT("UCsManager_Damage::Remove: Object: %s with Class: %s does NOT implement interface: ICsUniqueObject."), *(O->GetName()), *(Class->GetName()));

	const FCsUniqueObjectId& Id = UniqueObject->GetId();

	ReceiveDamageMap.Remove(Id);
}

#pragma endregion Receive Damage

// Event
#pragma region

ICsDamageEvent* UCsManager_Damage::ConstructEvent()
{
	return new FCsDamageEventImpl();
}

FCsResource_DamageEvent* UCsManager_Damage::AllocateEvent()
{
	return Manager_Event.Allocate();
}

void UCsManager_Damage::DeallocateEvent(const FString& Context, FCsResource_DamageEvent* Event)
{
	// Reset
	if (ICsReset* IReset = FCsLibrary_DamageEvent::GetSafeInterfaceChecked<ICsReset>(Context, Event->Get()))
		IReset->Reset();

	Manager_Event.Deallocate(Event);
}

bool UCsManager_Damage::CopyEvent(const FString& Context, const ICsDamageEvent* From, ICsDamageEvent* To)
{
	return FCsLibrary_DamageEvent::CopyChecked(Context, From, To);
}

FCsResource_DamageEvent* UCsManager_Damage::CreateCopyOfEvent(const FString& Context, const ICsDamageEvent* Event)
{
	FCsResource_DamageEvent* Container = AllocateEvent();
	ICsDamageEvent* Copy			   = Container->Get();

	bool Success = CopyEvent(Context, Event, Copy);

	checkf(Success, TEXT("%s: Failed to create copy of Event."), *Context);

	return Container;
}

FCsResource_DamageEvent* UCsManager_Damage::CreateCopyOfEvent(const FString& Context, const FCsResource_DamageEvent* Event)
{
	return CreateCopyOfEvent(Context, Event->Get());
}

void UCsManager_Damage::ProcessDamageEvent(const ICsDamageEvent* Event)
{
	using namespace NCsManagerDamageCached;

	const FString& Context = Str::ProcessDamageEvent;

	checkf(Event, TEXT("%s: Event is NULL."), *Context);

	ICsData_Damage* Data = Event->GetData();

	checkf(Data, TEXT("%s: Data is NULL. No Damage Data found for Event."), *Context);

	// ICsData_DamageShape
	if (ICsData_DamageShape* Shape = FCsLibrary_Data_Damage::GetSafeInterfaceChecked<ICsData_DamageShape>(Context, Data))
	{

	}
	// Point
	else
	{
		const FHitResult& HitResult = Event->GetHitResult();
		
		bool ShouldCopyEvent = false;
		
		// Actor
		if (AActor* Actor = HitResult.GetActor())
		{
			// Check if Actor implements interface: ICsReceiveDamage
			UClass* Class = Actor->GetClass();
			
			if (Class->ImplementsInterface(UCsReceiveDamage::StaticClass()))
			{
				Local_Receivers.AddDefaulted();
				Local_Receivers.Last().SetObject(Actor);

				ShouldCopyEvent = true;
			}
		}
		// Component
		else
		if (UPrimitiveComponent* Component = HitResult.GetComponent())
		{
			// Check if Component implements interface: ICsReceiveDamage
			UClass* Class = Component->GetClass();

			if (Class->ImplementsInterface(UCsReceiveDamage::StaticClass()))
			{
				Local_Receivers.AddDefaulted();
				Local_Receivers.Last().SetObject(Component);

				ShouldCopyEvent = true;
			}
		}

		if (ShouldCopyEvent)
		{
			// Copy the Event
			FCsResource_DamageEvent* EventContainer = CreateCopyOfEvent(Context, Event);
			ICsDamageEvent* Evt						= EventContainer->Get();

			// Set the Damage
			FCsLibrary_DamageEvent::SetDamageChecked(Context, Evt);

			Local_Events.Add(EventContainer);
		}
	}

	const int32 Count = Local_Receivers.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		FCsReceiveDamage& Receiver				= Local_Receivers[I];
		FCsResource_DamageEvent* EventContainer = Local_Events[I];

		ICsDamageEvent* Evt = EventContainer->Get();

		Receiver.Damage(Evt);

#if !UE_BUILD_SHIPPING
		LogEvent(Evt);
#endif // #if !UE_BUILD_SHIPPING

		OnProcessDamageEvent_Event.Broadcast(Evt);
		DeallocateEvent(Context, EventContainer);

		Local_Events[I] = nullptr;
	}

	Local_Receivers.Reset(Local_Receivers.Max());
	Local_Events.Reset(Local_Events.Max());
}

void UCsManager_Damage::ProcessDamageEventContainer(const FCsResource_DamageEvent* Event)
{
	using namespace NCsManagerDamageCached;

	const FString& Context = Str::ProcessDamageEventContainer;

	check(Manager_Event.IsValidChecked(Context, Event));

	const ICsDamageEvent* IEvent = Event->Get();

	ProcessDamageEvent(IEvent);
	DeallocateEvent(Context, const_cast<FCsResource_DamageEvent*>(Event));
}

#pragma endregion Event

// Value
#pragma region

ICsDamageValue* UCsManager_Damage::ConstructValue(const FECsDamageValue& Type)
{
	// Point | ICsDamageValuePoint (FCsDamageValuePointImpl)
	if (Type == NCsDamageValue::Point)
		return new FCsDamageValuePointImpl();
	// Point | ICsDamagePointRange (FCsDamageValueRangeImpl)
	if (Type == NCsDamageValue::Range)
		return new FCsDamageValueRangeImpl();
	return nullptr;
}

FCsResource_DamageValue* UCsManager_Damage::AllocateValue(const FECsDamageValue& Type)
{
	checkf(EMCsDamageValue::Get().IsValidEnum(Type), TEXT("UCsManager_Damage::AllocateValue: Type: %s is NOT Valid."), Type.ToChar());

	return Manager_Values[Type.GetValue()].Allocate();
}

void UCsManager_Damage::DeallocateValue(const FString& Context, const FECsDamageValue& Type, FCsResource_DamageValue* Value)
{
	checkf(EMCsDamageValue::Get().IsValidEnum(Type), TEXT("UCsManager_Damage::DeallocateValue: Type: %s is NOT Valid."), Type.ToChar());

	// Reset
	if (ICsReset* IReset = FCsLibrary_DamageValue::GetSafeInterfaceChecked<ICsReset>(Context, Value->Get()))
		IReset->Reset();

	Manager_Values[Type.GetValue()].Deallocate(Value);
}

void UCsManager_Damage::DeallocateValue(const FString& Context, FCsResource_DamageValue* Value)
{
	// Point
	if (ICsDamageValuePoint* Point = FCsLibrary_DamageValue::GetSafeInterfaceChecked<ICsDamageValuePoint>(Context, Value->Get()))
	{
		DeallocateValue(NCsDamageValue::Point, Value);
	}
	// Range
	else
	if (ICsDamageValueRange* Range = FCsLibrary_DamageValue::GetSafeInterfaceChecked<ICsDamageValueRange>(Context, Value->Get()))
	{
		DeallocateValue(NCsDamageValue::Range, Value);
	}
}

const FECsDamageValue& UCsManager_Damage::GetValueType(const FString& Context, const ICsDamageValue* Value)
{
	checkf(Value, TEXT("%s: Value is NULL."), *Context);

	// Point
	if (FCsLibrary_DamageValue::GetSafeInterfaceChecked<ICsDamageValuePoint>(Context, Value))
		return NCsDamageValue::Point;
	// Range
	if (FCsLibrary_DamageValue::GetSafeInterfaceChecked<ICsDamageValueRange>(Context, Value))
		return NCsDamageValue::Range;

	return EMCsDamageValue::Get().GetMAX();
}

FCsResource_DamageValue* UCsManager_Damage::CreateCopyOfValue(const FString& Context, const ICsDamageValue* Value)
{
	const FECsDamageValue& ValueType = GetValueType(Context, Value);

	checkf(EMCsDamageValue::Get().IsValidEnum(ValueType), TEXT("%s: ValueType: %s is NOT Valid."), ValueType.ToChar());

	FCsResource_DamageValue* Container = AllocateValue(ValueType);
	ICsDamageValue* Copy			   = Container->Get();

	bool Success = FCsLibrary_DamageValue::CopyChecked(Context, Value, Copy);

	checkf(Success, TEXT("%s: Failed to create copy of Event."), *Context);

	return Container;
}

FCsResource_DamageValue* UCsManager_Damage::CreateCopyOfValue(const FString& Context, const FCsResource_DamageValue* Value)
{
	return CreateCopyOfValue(Context, Value->Get());
}

#pragma endregion Value

// Range
#pragma region

ICsDamageRange* UCsManager_Damage::ConstructRange()
{
	return new FCsDamageRangeImpl();
}

FCsResource_DamageRange* UCsManager_Damage::AllocateRange()
{
	return Manager_Range.Allocate();
}

void UCsManager_Damage::DeallocateRange(const FString& Context, FCsResource_DamageRange* Range)
{
	// Reset
	if (ICsReset* IReset = FCsLibrary_DamageRange::GetSafeInterfaceChecked<ICsReset>(Context, Range->Get()))
		IReset->Reset();

	Manager_Range.Deallocate(Range);
}

FCsResource_DamageRange* UCsManager_Damage::CreateCopyOfRange(const FString& Context, const ICsDamageRange* Range)
{
	FCsResource_DamageRange* Container = AllocateRange();
	ICsDamageRange* Copy			   = Container->Get();

	bool Success = FCsLibrary_DamageRange::CopyChecked(Context, Range, Copy);

	checkf(Success, TEXT("%s: Failed to create copy of Event."), *Context);

	return Container;
}

FCsResource_DamageRange* UCsManager_Damage::CreateCopyOfRange(const FString& Context, const FCsResource_DamageRange* Range)
{
	return CreateCopyOfRange(Context, Range->Get());
}

const ICsDamageRange* UCsManager_Damage::GetRange(const FString& Context, const ICsData_Damage* Data)
{
	if (const ICsDamageRange* Value = FCsLibrary_Data_Damage::GetRangeChecked(Context, Data))
	{
		return Value;
	}
	return nullptr;
}

#pragma endregion  Range

// Modifier
#pragma region

ICsDamageModifier* UCsManager_Damage::ConstructModifier()
{
	return nullptr;
}

FCsResource_DamageModifier* UCsManager_Damage::AllocateModifier()
{
	return nullptr;
}

void UCsManager_Damage::DeallocateModifier(const FString& Context, FCsResource_DamageModifier* Modifier)
{

}

FCsResource_DamageModifier* UCsManager_Damage::CreateCopyOfModifier(const FString& Context, const ICsDamageModifier* Modifier)
{
	FCsResource_DamageModifier* Container = AllocateModifier();
	ICsDamageModifier* Copy				  = Container->Get();

	bool Success = FCsLibrary_DamageModifier::CopyChecked(Context, Modifier, Copy);

	checkf(Success, TEXT("%s: Failed to create copy of Event."), *Context);

	return Container;
}

FCsResource_DamageModifier* UCsManager_Damage::CreateCopyOfModifier(const FString& Context, const FCsResource_DamageModifier* Modifier)
{
	return CreateCopyOfModifier(Context, Modifier->Get());
}

void UCsManager_Damage::ModifyValue(const FString& Context, const ICsDamageModifier* Modifier, const ICsData_Damage* Data, ICsDamageValue* Value)
{
	checkf(Data, TEXT("%s: Data is NULL."), *Context);

	checkf(Value, TEXT("%s: Value is NULL."), *Context);

	if (!FCsLibrary_DamageModifier::ModifyChecked(Context, Modifier, Data, Value))
	{

	}
}

void UCsManager_Damage::ModifyRange(const FString& Context, const ICsDamageModifier* Modifier, const ICsData_Damage* Data, ICsDamageRange* Range)
{
	checkf(Data, TEXT("%s: Data is NULL."), *Context);

	checkf(Range, TEXT("%s: Range is NULL."), *Context);

	if (!FCsLibrary_DamageModifier::ModifyChecked(Context, Modifier, Data, Range))
	{

	}
}

#pragma endregion Modifier

// Log
#pragma region

void UCsManager_Damage::LogEvent(const ICsDamageEvent* Event)
{
	using namespace NCsManagerDamageCached;

	const FString& Context = Str::LogEvent;

	ICsData_Damage* Data = Event->GetData();

	if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerDamageEvents))
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Damage::ProcessDamageEvent:"));
		// Data
		UE_LOG(LogCs, Warning, TEXT("- Data: Point"));

		// Damage
		{
			const ICsDamageValue* Value = Event->GetDamageValue();

			// Point
			if (const ICsDamageValuePoint* Point = FCsLibrary_DamageValue::GetSafeInterfaceChecked<ICsDamageValuePoint>(Context, Value))
			{
				UE_LOG(LogCs, Warning, TEXT("-- Damage: %f"), Point->GetValue());
			}
			// Range
			if (const ICsDamageValueRange* Range = FCsLibrary_DamageValue::GetSafeInterfaceChecked<ICsDamageValueRange>(Context, Value))
			{
				UE_LOG(LogCs, Warning, TEXT("-- Damage: %f <-> %f"), Range->GetMinValue(), Range->GetMaxValue());
			}
		}
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

#pragma endregion Log
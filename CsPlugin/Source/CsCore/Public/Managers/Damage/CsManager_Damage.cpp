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
#include "Managers/Damage/Modifier/CsLibrary_DamageModifier.h"
#include "Library/CsLibrary_Valid.h"
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
// Library
#include "Managers/Damage/CsLibrary_Manager_Damage.h"
// Singleton
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Managers/Damage/CsGetManagerDamage.h"
#endif // #if WITH_EDITOR

// Cached
#pragma region

namespace NCsManagerDamage
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Damage, GetFromWorldContextObject);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Damage, ProcessDamageEvent);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Damage, ProcessDamageEventContainer);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Damage, LogEvent);
		}
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

#if WITH_EDITOR
/*static*/ UCsManager_Damage* UCsManager_Damage::Get(UObject* InRoot /*=nullptr*/)
{
	return Get_GetManagerDamage(InRoot)->GetManager_Damage();
}
#endif // #if WITH_EDITOR

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
	using namespace NCsManagerDamage::NCached;

	const FString& Context = Str::GetFromWorldContextObject;

	typedef NCsDamage::NManager::FLibrary DamageManagerLibrary;

	if (UObject* ContextRoot = DamageManagerLibrary::GetSafe(Context, WorldContextObject))
	{
		if (UCsManager_Damage* Manager = GetSafe(ContextRoot))
			return Manager;

		UE_LOG(LogCs, Warning, TEXT("%s: Failed to Manager Damage of type UCsManager_Damage from ContextRoot: %s."), *Context, *(ContextRoot->GetName()));
	}
	return nullptr;
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
		
		Manager_Values.Reset(Count);
		Manager_Values.AddDefaulted(Count);
		
			// Create Pool
		const int32& PoolSize = Settings->Manager_Damage.Value.PoolSize;

		for (const FECsDamageValue& Value : EMCsDamageValue::Get())
		{
			typedef NCsDamage::NValue::FManager ValueManagerType;

			ValueManagerType& Manager = Manager_Values[Value.GetValue()];

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
			typedef NCsDamage::NValue::FManager ValueManagerType;

			ValueManagerType& Manager = Manager_Values[Value.GetValue()];

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

#define EventResourceType NCsDamage::NEvent::FResource
#define EventType NCsDamage::NEvent::IEvent

EventType* UCsManager_Damage::ConstructEvent()
{
	typedef NCsDamage::NEvent::FImpl EventImplType;

	return new EventImplType();
}

EventResourceType* UCsManager_Damage::AllocateEvent()
{
	return Manager_Event.Allocate();
}

void UCsManager_Damage::DeallocateEvent(const FString& Context, EventResourceType* Event)
{
	typedef NCsDamage::NEvent::FLibrary DamageEventLibrary;

	// Reset
	if (ICsReset* IReset = DamageEventLibrary::GetSafeInterfaceChecked<ICsReset>(Context, Event->Get()))
		IReset->Reset();

	Manager_Event.Deallocate(Event);
}

bool UCsManager_Damage::CopyEvent(const FString& Context, const EventType* From, EventType* To)
{
	return NCsDamage::NEvent::FLibrary::CopyChecked(Context, From, To);
}

EventResourceType* UCsManager_Damage::CreateCopyOfEvent(const FString& Context, const EventType* Event)
{
	EventResourceType* Container = AllocateEvent();
	EventType* Copy	   = Container->Get();

	bool Success = CopyEvent(Context, Event, Copy);

	checkf(Success, TEXT("%s: Failed to create copy of Event."), *Context);

	return Container;
}

EventResourceType* UCsManager_Damage::CreateCopyOfEvent(const FString& Context, const EventResourceType* Event)
{
	return CreateCopyOfEvent(Context, Event->Get());
}

void UCsManager_Damage::ProcessDamageEvent(const EventType* Event)
{
	using namespace NCsManagerDamage::NCached;

	const FString& Context = Str::ProcessDamageEvent;

	CS_IS_PTR_NULL_CHECKED(Event)

	typedef NCsDamage::NData::IData DataType;

	DataType* Data = Event->GetData();

	checkf(Data, TEXT("%s: Data is NULL. No Damage Data found for Event."), *Context);

	// ICsData_DamageShape
	typedef NCsDamage::NData::FLibrary DamageDataLibrary;
	typedef NCsDamage::NData::NShape::IShape ShapeDataType;

	if (ShapeDataType* Shape = DamageDataLibrary::GetSafeInterfaceChecked<ShapeDataType>(Context, Data))
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
			EventResourceType* EventContainer = CreateCopyOfEvent(Context, Event);
			EventType* Evt					  = EventContainer->Get();

			// Set the Damage
			typedef NCsDamage::NEvent::FLibrary DamageEventLibrary;

			DamageEventLibrary::SetDamageChecked(Context, Evt);

			Local_Events.Add(EventContainer);
		}
	}

	const int32 Count = Local_Receivers.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		FCsReceiveDamage& Receiver		  = Local_Receivers[I];
		EventResourceType* EventContainer = Local_Events[I];

		EventType* Evt = EventContainer->Get();

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

void UCsManager_Damage::ProcessDamageEventContainer(const EventResourceType* Event)
{
	using namespace NCsManagerDamage::NCached;

	const FString& Context = Str::ProcessDamageEventContainer;

	check(Manager_Event.IsValidChecked(Context, Event));

	const EventType* IEvent = Event->Get();

	ProcessDamageEvent(IEvent);
	DeallocateEvent(Context, const_cast<EventResourceType*>(Event));
}

#undef EventResourceType
#undef EventType

#pragma endregion Event

// Value
#pragma region

#define ValueResourceType NCsDamage::NValue::FResource
#define ValueType NCsDamage::NValue::IValue

ValueType* UCsManager_Damage::ConstructValue(const FECsDamageValue& Type)
{
	// Point | NCsDamage::NValue::NPoint::IPoint (NCsDamage::NValue::NPoint::FImpl)
	if (Type == NCsDamageValue::Point)
		return new NCsDamage::NValue::NPoint::FImpl();
	// Point | NCsDamage::NValue::NRange::IRange (NCsDamage::NValue::NRange::FImpl)
	if (Type == NCsDamageValue::Range)
		return new NCsDamage::NValue::NRange::FImpl();
	return nullptr;
}

ValueResourceType* UCsManager_Damage::AllocateValue(const FECsDamageValue& Type)
{
	checkf(EMCsDamageValue::Get().IsValidEnum(Type), TEXT("UCsManager_Damage::AllocateValue: Type: %s is NOT Valid."), Type.ToChar());

	return Manager_Values[Type.GetValue()].Allocate();
}

void UCsManager_Damage::DeallocateValue(const FString& Context, const FECsDamageValue& Type, ValueResourceType* Value)
{
	checkf(EMCsDamageValue::Get().IsValidEnum(Type), TEXT("UCsManager_Damage::DeallocateValue: Type: %s is NOT Valid."), Type.ToChar());

	CS_IS_PTR_NULL_CHECKED(Value)

	typedef NCsDamage::NValue::FLibrary ValueLibrary;

	// Reset
	if (ICsReset* IReset = ValueLibrary::GetSafeInterfaceChecked<ICsReset>(Context, Value->Get()))
		IReset->Reset();

	Manager_Values[Type.GetValue()].Deallocate(Value);
}

void UCsManager_Damage::DeallocateValue(const FString& Context, ValueResourceType* Value)
{
	typedef NCsDamage::NValue::NPoint::IPoint PointType;
	typedef NCsDamage::NValue::NRange::IRange RangeType;

	typedef NCsDamage::NValue::FLibrary ValueLibrary;

	// Point
	if (PointType* Point = ValueLibrary::GetSafeInterfaceChecked<PointType>(Context, Value->Get()))
	{
		DeallocateValue(NCsDamageValue::Point, Value);
	}
	// Range
	else
	if (RangeType* Range = ValueLibrary::GetSafeInterfaceChecked<RangeType>(Context, Value->Get()))
	{
		DeallocateValue(NCsDamageValue::Range, Value);
	}
}

const FECsDamageValue& UCsManager_Damage::GetValueType(const FString& Context, const ValueType* Value)
{
	typedef NCsDamage::NValue::NPoint::IPoint PointType;
	typedef NCsDamage::NValue::NRange::IRange RangeType;

	typedef NCsDamage::NValue::FLibrary ValueLibrary;

	// Point
	if (ValueLibrary::GetSafeInterfaceChecked<PointType>(Context, Value))
		return NCsDamageValue::Point;
	// Range
	if (ValueLibrary::GetSafeInterfaceChecked<RangeType>(Context, Value))
		return NCsDamageValue::Range;

	return EMCsDamageValue::Get().GetMAX();
}


ValueResourceType* UCsManager_Damage::CreateCopyOfValue(const FString& Context, const ValueType* Value)
{
	const FECsDamageValue& Type = GetValueType(Context, Value);

	checkf(EMCsDamageValue::Get().IsValidEnum(Type), TEXT("%s: Type: %s is NOT Valid."), Type.ToChar());

	ValueResourceType* Container = AllocateValue(Type);
	ValueType* Copy				 = Container->Get();

	typedef NCsDamage::NValue::FLibrary ValueLibrary;

	bool Success = ValueLibrary::CopyChecked(Context, Value, Copy);

	checkf(Success, TEXT("%s: Failed to create copy of Event."), *Context);

	return Container;
}

ValueResourceType* UCsManager_Damage::CreateCopyOfValue(const FString& Context, const ValueResourceType* Value)
{
	CS_IS_PTR_NULL_CHECKED(Value)

	return CreateCopyOfValue(Context, Value->Get());
}

#undef ValueResourceType
#undef ValueType

#pragma endregion Value

// Range
#pragma region

#define RangeResourceType NCsDamage::NRange::FResource
#define RangeType NCsDamage::NRange::IRange

RangeType* UCsManager_Damage::ConstructRange()
{
	typedef NCsDamage::NRange::FImpl RangeImplType;
	return new RangeImplType();
}

RangeResourceType* UCsManager_Damage::AllocateRange()
{
	return Manager_Range.Allocate();
}

void UCsManager_Damage::DeallocateRange(const FString& Context, RangeResourceType* Range)
{
	typedef NCsDamage::NRange::FLibrary RangeLibrary;

	// Reset
	if (ICsReset* IReset = RangeLibrary::GetSafeInterfaceChecked<ICsReset>(Context, Range->Get()))
		IReset->Reset();

	Manager_Range.Deallocate(Range);
}

RangeResourceType* UCsManager_Damage::CreateCopyOfRange(const FString& Context, const RangeType* Range)
{
	RangeResourceType* Container = AllocateRange();
	RangeType* Copy				 = Container->Get();

	typedef NCsDamage::NRange::FLibrary RangeLibrary;

	bool Success = RangeLibrary::CopyChecked(Context, Range, Copy);

	checkf(Success, TEXT("%s: Failed to create copy of Event."), *Context);

	return Container;
}

RangeResourceType* UCsManager_Damage::CreateCopyOfRange(const FString& Context, const RangeResourceType* Range)
{
	return CreateCopyOfRange(Context, Range->Get());
}

#define DataType NCsDamage::NData::IData
const RangeType* UCsManager_Damage::GetRange(const FString& Context, const DataType* Data)
{
#undef DataType

	typedef NCsDamage::NData::FLibrary DamageDataLibrary;

	if (const RangeType* Value = DamageDataLibrary::GetRangeChecked(Context, Data))
	{
		return Value;
	}
	return nullptr;
}

#undef RangeResourceType
#undef RangeType


#pragma endregion  Range

// Modifier
#pragma region

#define ModifierResourceType NCsDamage::NModifier::FResource
#define ModifierType NCsDamage::NModifier::IModifier

ModifierType* UCsManager_Damage::ConstructModifier()
{
	return nullptr;
}

ModifierResourceType* UCsManager_Damage::AllocateModifier()
{
	return nullptr;
}

void UCsManager_Damage::DeallocateModifier(const FString& Context, ModifierResourceType* Modifier)
{
}

ModifierResourceType* UCsManager_Damage::CreateCopyOfModifier(const FString& Context, const ModifierType* Modifier)
{
	ModifierResourceType* Container = AllocateModifier();
	ModifierType* Copy				= Container->Get();

	typedef NCsDamage::NModifier::FLibrary ModifierLibrary;

	bool Success = ModifierLibrary::CopyChecked(Context, Modifier, Copy);

	checkf(Success, TEXT("%s: Failed to create copy of Event."), *Context);

	return Container;
}

ModifierResourceType* UCsManager_Damage::CreateCopyOfModifier(const FString& Context, const ModifierResourceType* Modifier)
{
	return CreateCopyOfModifier(Context, Modifier->Get());
}

#define DataType NCsDamage::NData::IData

#define ValueType NCsDamage::NValue::IValue
void UCsManager_Damage::ModifyValue(const FString& Context, const ModifierType* Modifier, const DataType* Data, ValueType* Value)
{
#undef ValueType

	typedef NCsDamage::NModifier::FLibrary ModifierLibrary;

	if (!ModifierLibrary::ModifyChecked(Context, Modifier, Data, Value))
	{

	}
}

#define RangesType NCsDamage::NRange::IRange
void UCsManager_Damage::ModifyRange(const FString& Context, const ModifierType* Modifier, const DataType* Data, RangesType* Range)
{
#undef RangesType

	typedef NCsDamage::NModifier::FLibrary ModifierLibrary;

	if (!ModifierLibrary::ModifyChecked(Context, Modifier, Data, Range))
	{

	}
}

#undef DataType

#undef ModifierResourceType
#undef ModifierType

#pragma endregion Modifier

// Log
#pragma region

#define EventType NCsDamage::NEvent::IEvent
void UCsManager_Damage::LogEvent(const EventType* Event)
{
#undef EventType

	using namespace NCsManagerDamage::NCached;

	const FString& Context = Str::LogEvent;

	typedef NCsDamage::NData::IData DataType;

	DataType* Data = Event->GetData();

	if (CS_CVAR_LOG_IS_SHOWING(LogManagerDamageEvents))
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Damage::ProcessDamageEvent:"));
		// Data
		UE_LOG(LogCs, Warning, TEXT("- Data: Point"));

		// Damage
		{
			typedef NCsDamage::NValue::FLibrary ValueLibrary;
			typedef NCsDamage::NValue::IValue ValueType;

			const ValueType* Value = Event->GetDamageValue();

			// Point
			{
				typedef NCsDamage::NValue::NPoint::IPoint PointType;

				if (const PointType* Point = ValueLibrary::GetSafeInterfaceChecked<PointType>(Context, Value))
				{
					UE_LOG(LogCs, Warning, TEXT("-- Damage: %f"), Point->GetValue());
				}
			}
			// Range
			{
				typedef NCsDamage::NValue::NRange::IRange RangeType;

				if (const RangeType* Range = ValueLibrary::GetSafeInterfaceChecked<RangeType>(Context, Value))
				{
					UE_LOG(LogCs, Warning, TEXT("-- Damage: %f <-> %f"), Range->GetMinValue(), Range->GetMaxValue());
				}
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
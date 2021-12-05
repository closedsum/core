// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
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
#include "Game/CsLibrary_GameInstance.h"
#include "Library/CsLibrary_Valid.h"
// Settings
#include "Settings/CsDeveloperSettings.h"
// Reset
#include "Reset/CsReset.h"
// Damage
#include "Managers/Damage/Handler/CsManager_Damage_DataHandler.h"
#include "Managers/Damage/Event/CsDamageEventImpl.h"
#include "Managers/Damage/Data/CsData_Damage.h"
#include "Managers/Damage/Data/Shape/CsData_DamageShape.h"
#include "Managers/Damage/Value/Point/CsDamageValuePointImpl.h"
#include "Managers/Damage/Value/Range/CsDamageValueRangeImpl.h"
#include "Managers/Damage/Range/CsDamageRangeImpl.h"
// Unique
#include "UniqueObject/CsUniqueObject.h"

#if WITH_EDITOR
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
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Damage, Initialize);
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

UCsManager_Damage::UCsManager_Damage(const FObjectInitializer& ObjectInitializer) : 
	Super(ObjectInitializer)
{
}

// Singleton
#pragma region

#if WITH_EDITOR

/*static*/ UCsManager_Damage* UCsManager_Damage::Get(UObject* InRoot /*=nullptr*/)
{
	return Get_GetManagerDamage(InRoot)->GetManager_Damage();
}

/*static*/ UCsManager_Damage* UCsManager_Damage::GetSafe(const FString& Context, UObject* Object, void(*Log)(const FString&) /*=nullptr*/)
{
	if (ICsGetManagerDamage* GetManagerDamage = GetSafe_GetManagerDamage(Context, Object, Log))
		return GetManagerDamage->GetManager_Damage();
	return nullptr;
}

/*static*/ bool UCsManager_Damage::IsValid(UObject* InRoot /*=nullptr*/)
{
	return Get_GetManagerDamage(InRoot)->GetManager_Damage() != nullptr;
}

#endif // #if WITH_EDITOR


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

/*static*/ ICsGetManagerDamage* UCsManager_Damage::GetSafe_GetManagerDamage(const FString& Context, UObject* InRoot, void(*Log)(const FString&) /*=nullptr*/)
{
	CS_IS_PTR_NULL_RET_NULL(InRoot)

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

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
	return Cast<ICsGetManagerDamage>(Manager_Singleton);
}

#endif // #if WITH_EDITOR

void UCsManager_Damage::Initialize()
{
	using namespace NCsManagerDamage::NCached;

	const FString& Context = Str::Initialize;

	// Populate EnumMaps
	typedef NCsGameInstance::FLibrary GameInstanceLibrary;

	NCsDamageType::PopulateEnumMapFromSettings(Context, GameInstanceLibrary::GetSafeAsObject(MyRoot));
	NCsDamageData::PopulateEnumMapFromSettings(Context, GameInstanceLibrary::GetSafeAsObject(MyRoot));

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
	// Modifier
	/*
	{
		const int32& Count = EMCsDamageModifier::Get().Num();

		Manager_Modifiers.Reset(Count);
		Manager_Modifiers.AddDefaulted(Count);

		// Create Pool
		const int32& PoolSize = Settings->Manager_Damage.Modifier.PoolSize;

		for (const FECsDamageModifier& Modifier : EMCsDamageModifier::Get())
		{
			typedef NCsDamage::NModifier::FManager ModifierManagerType;

			ModifierManagerType& Manager = Manager_Modifiers[Modifier.GetValue()];

			Manager.SetDeconstructResourcesOnShutdown();
			Manager.CreatePool(PoolSize);

			for (int32 I = 0; I < PoolSize; ++I)
			{
				Manager.Add(ConstructModifier(Modifier));
			}
		}
	}
	*/

	// Data Handler
	ConstructDataHandler();

	checkf(DataHandler, TEXT("%s: Failed to construct DataHandler."), *Context);

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
	// Modifier
	/*
	{
		for (const FECsDamageModifier& Modifier : EMCsDamageModifier::Get())
		{
			typedef NCsDamage::NModifier::FManager ModifierManagerType;

			ModifierManagerType& Manager = Manager_Modifiers[Modifier.GetValue()];

			Manager.Shutdown();
		}
	}
	*/
	delete DataHandler;
	DataHandler = nullptr;

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

#define DataType NCsDamage::NData::IData
#define ModifierResourceType NCsDamage::NModifier::FResource
#define ValueType NCsDamage::NValue::IValue

EventResourceType* UCsManager_Damage::CreateEvent(const FString& Context, DataType* Data, UObject* Instigator, UObject* Causer, const FHitResult& HitResult,  const TArray<ModifierResourceType*>& Modifiers)
{
	return CreateEvent(Context, Data->GetValue(), Data, Instigator, Causer, HitResult, Modifiers);
}

EventResourceType* UCsManager_Damage::CreateEvent(const FString& Context, DataType* Data, UObject* Instigator, UObject* Causer, const FHitResult& HitResult)
{
	TArray<ModifierResourceType*> Modifiers;
	return CreateEvent(Context, Data->GetValue(), Data, Instigator, Causer, HitResult, Modifiers);
}

EventResourceType* UCsManager_Damage::CreateEvent(const FString& Context, const ValueType* Value, DataType* Data, UObject* Instigator, UObject* Causer, const FHitResult& HitResult, const TArray<ModifierResourceType*>& Modifiers)
{
	CS_IS_PTR_NULL_CHECKED(Data)
	
	// Get Container from Manager_Damage
	EventResourceType* Container = AllocateEvent();

	// Event
	typedef NCsDamage::NEvent::FLibrary EventLibrary;
	typedef NCsDamage::NEvent::FImpl EventImplType;

	EventType* Event		 = Container->Get();
	EventImplType* EventImpl = EventLibrary::PureStaticCastChecked<EventImplType>(Context, Event);

	// Copy Value from Data, this can change with modifiers
	EventImpl->DamageValue.CopyFrom(Context, MyRoot, Value);
	ValueType* DamageValue = EventImpl->DamageValue.GetValue();

	// Copy Range from Data, this can change with modifiers
	typedef NCsDamage::NRange::IRange RangeType;

	EventImpl->DamageRange.SafeCopyFrom(Context, MyRoot, Data);
	RangeType* Range = EventImpl->DamageRange.GetRange();

	// Apply Modifiers
	typedef NCsDamage::NModifier::FLibrary DamageModifierLibrary;

	if (Range)
	{
		DamageModifierLibrary::ModifyChecked(Context, Modifiers, Data, DamageValue, Range);
	}
	else
	{
		DamageModifierLibrary::ModifyChecked(Context, Modifiers, Data, DamageValue);
	}

	EventImpl->Data		  = Data;
	EventImpl->Instigator = Instigator;
	EventImpl->Causer	  = Causer;
	EventImpl->Origin	  = HitResult;
	EventImpl->HitResult  = HitResult;

	return Container;
}

EventResourceType* UCsManager_Damage::CreateEvent(const FString& Context, const ValueType* Value, DataType* Data, UObject* Instigator, UObject* Causer, const FHitResult& HitResult)
{
	TArray<ModifierResourceType*> Modifiers;
	return CreateEvent(Context, Value, Data, Instigator, Causer, HitResult, Modifiers);
}

#undef DataType
#undef ModifierResourceType
#undef ValueType

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

		CS_NON_SHIPPING_EXPR(LogEvent(Evt));

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

void UCsManager_Damage::DeallocateModifier(const FString& Context, const FECsDamageModifier& Type, ModifierResourceType* Modifier)
{
	checkf(EMCsDamageModifier::Get().IsValidEnum(Type), TEXT("UCsManager_Damage::DeallocateModifier: Type: %s is NOT Valid."), Type.ToChar());

	CS_IS_PTR_NULL_CHECKED(Modifier)

	typedef NCsDamage::NModifier::FLibrary ModifierLibrary;

	// Reset
	if (ICsReset* IReset = ModifierLibrary::GetSafeInterfaceChecked<ICsReset>(Context, Modifier->Get()))
		IReset->Reset();

	Manager_Modifiers[Type.GetValue()].Deallocate(Modifier);
}

const FECsDamageModifier& UCsManager_Damage::GetModifierType(const FString& Context, const ModifierType* Modifier)
{
	/*
	typedef NCsDamage::NModifier::NValue::IValue ValueType;
	typedef NCsDamage::NModifier::NRange::IRange RangeType;

	typedef NCsDamage::NModifier::FLibrary ValueLibrary;

	// Value
	if (ValueLibrary::GetSafeInterfaceChecked<ValueType>(Context, Value))
		return NCsDamageValue::Value;
	// Range
	if (ValueLibrary::GetSafeInterfaceChecked<RangeType>(Context, Value))
		return NCsDamageValue::Range;
	*/
	return EMCsDamageModifier::Get().GetMAX();
}

#undef ModifierResourceType
#undef ModifierType

#pragma endregion Modifier

// Data
#pragma region

void UCsManager_Damage::ConstructDataHandler()
{
	typedef NCsDamage::NManager::NHandler::FData DataHandlerType;

	DataHandler			= new DataHandlerType();
	DataHandler->Outer  = this;
	DataHandler->MyRoot = MyRoot;
}

#define DataType NCsDamage::NData::IData

DataType* UCsManager_Damage::GetDataChecked(const FString& Context, const FName& Name)
{
	return DataHandler->GetDataChecked(Context, Name);
}

DataType* UCsManager_Damage::GetSafeData(const FString& Context, const FName& Name, void(*Log)(const FString&) /*=nullptr*/)
{
	return DataHandler->GetSafeData(Context, Name, Log);
}

#define ModifierResourceType NCsDamage::NModifier::FResource
#define ValueType NCsDamage::NValue::IValue

void UCsManager_Damage::ProcessData(const FString& Context, DataType* Data, UObject* Instigator, UObject* Causer, const FHitResult& HitResult, const TArray<ModifierResourceType*>& Modifiers)
{
	typedef NCsDamage::NEvent::FResource EventResourceType;

	const EventResourceType* Container = CreateEvent(Context, Data, Instigator, Causer, HitResult, Modifiers);

	ProcessDamageEventContainer(Container);
}

void UCsManager_Damage::ProcessData(const FString& Context, DataType* Data, UObject* Instigator, UObject* Causer, const FHitResult& HitResult)
{
	typedef NCsDamage::NEvent::FResource EventResourceType;

	const EventResourceType* Container = CreateEvent(Context, Data, Instigator, Causer, HitResult);

	ProcessDamageEventContainer(Container);
}

void UCsManager_Damage::ProcessData(const FString& Context, const ValueType* Value, DataType* Data, UObject* Instigator, UObject* Causer, const FHitResult& HitResult, const TArray<ModifierResourceType*>& Modifiers)
{
	typedef NCsDamage::NEvent::FResource EventResourceType;

	const EventResourceType* Container = CreateEvent(Context, Value, Data, Instigator, Causer, HitResult, Modifiers);

	ProcessDamageEventContainer(Container);
}

void UCsManager_Damage::ProcessData(const FString& Context, const ValueType* Value, DataType* Data, UObject* Instigator, UObject* Causer, const FHitResult& HitResult)
{
	typedef NCsDamage::NEvent::FResource EventResourceType;

	const EventResourceType* Container = CreateEvent(Context, Value, Data, Instigator, Causer, HitResult);

	ProcessDamageEventContainer(Container);
}

#undef DataType
#undef ModifierResourceType
#undef ValueType

#pragma endregion Data

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
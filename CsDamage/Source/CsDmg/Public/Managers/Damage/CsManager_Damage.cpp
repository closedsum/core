// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/CsManager_Damage.h"
#include "CsDmg.h"

// CVar
#include "Managers/Damage/CsCVars_Manager_Damage.h"
// Library
#include "Managers/Damage/Data/CsLibrary_Data_Damage.h"
#include "Managers/Damage/Value/CsLibrary_DamageValue.h"
#include "Managers/Damage/Range/CsLibrary_DamageRange.h"
#include "Managers/Damage/Event/CsLibrary_DamageEvent.h"
#include "Managers/Damage/Modifier/CsLibrary_DamageModifier.h"
#include "Game/CsLibrary_GameInstance.h"
#include "Library/CsLibrary_Valid.h"
// Settings
#include "Settings/CsDamageSettings.h"
// Data
#include "Managers/Damage/Data/CsData_Damage.h"
#include "Managers/Damage/Data/Shape/CsData_DamageShape.h"
#include "Managers/Damage/Data/Collision/CsData_DamageCollision.h"
// Reset
#include "Reset/CsReset.h"
// Damage
#include "Managers/Damage/Handler/CsManager_Damage_DataHandler.h"
#include "Managers/Damage/Event/CsDamageEventImpl.h"
#include "Managers/Damage/Value/Point/CsDamageValuePointImpl.h"
#include "Managers/Damage/Value/Range/CsDamageValueRangeImpl.h"
#include "Managers/Damage/Range/CsDamageRangeImpl.h"
#include "Managers/Damage/Modifier/Types/CsGetDamageModifierType.h"
#include "Managers/Damage/Modifier/Value/Point/CsDamageModifier_ValuePointImpl.h"
#include "Managers/Damage/Modifier/Value/Range/CsDamageModifier_ValueRangeImpl.h"
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

/*static*/ UCsManager_Damage* UCsManager_Damage::Get(const UObject* InRoot /*=nullptr*/)
{
	return Get_GetManagerDamage(InRoot)->GetManager_Damage();
}

/*static*/ UCsManager_Damage* UCsManager_Damage::GetSafe(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) /*=nullptr*/)
{
	if (ICsGetManagerDamage* GetManagerDamage = GetSafe_GetManagerDamage(Context, InRoot, Log))
		return GetManagerDamage->GetManager_Damage();
	return nullptr;
}

/*static*/ bool UCsManager_Damage::IsValid(const UObject* InRoot /*=nullptr*/)
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
		UE_LOG(LogCsDmg, Warning, TEXT("UCsManager_Damage::Init: Init has already been called."));
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
		UE_LOG(LogCsDmg, Warning, TEXT("UCsManager_Damage::Init: Init has already been called."));
	}
#endif // #if WITH_EDITOR
}

/*static*/ void UCsManager_Damage::Shutdown(const UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerDamage* GetManagerDamage = Get_GetManagerDamage(InRoot);
	UCsManager_Damage* Manager_Damage	  = GetManagerDamage->GetManager_Damage();
	Manager_Damage->CleanUp();

	GetManagerDamage->SetManager_Damage(nullptr);
#else
	if (!s_Instance)
	{
		UE_LOG(LogCsDmg, Warning, TEXT("UCsManager_Damage::Shutdown: Manager has already been shutdown."));
		return;
	}

	s_Instance->CleanUp();
	s_Instance->RemoveFromRoot();
	s_Instance = nullptr;
	s_bShutdown = true;
#endif // #if WITH_EDITOR
}

/*static*/ bool UCsManager_Damage::HasShutdown(const UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerDamage(InRoot)->GetManager_Damage() == nullptr;
#else
	return s_bShutdown;
#endif // #if WITH_EDITOR
}

#if WITH_EDITOR

/*static*/ ICsGetManagerDamage* UCsManager_Damage::Get_GetManagerDamage(const UObject* InRoot)
{
	checkf(InRoot, TEXT("UCsManager_Damage::Get_GetManagerDamage: InRoot is NULL."));

	const ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("UCsManager_Damage::Get_GetManagerDamage: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("UCsManager_Damage::Get_GetManagerDamage: Manager_Singleton is NULL."));

	ICsGetManagerDamage* GetManagerDamage = Cast<ICsGetManagerDamage>(Manager_Singleton);

	checkf(GetManagerDamage, TEXT("UCsManager_Damage::Get_GetManagerDamage: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsGetManagerDamage."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

	return GetManagerDamage;
}

/*static*/ ICsGetManagerDamage* UCsManager_Damage::GetSafe_GetManagerDamage(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) /*=nullptr*/)
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

	UCsDamageSettings* Settings = GetMutableDefault<UCsDamageSettings>();

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

	// Data Handler
	ConstructDataHandler();

	checkf(DataHandler, TEXT("%s: Failed to construct DataHandler."), *Context);

	DataHandler->PopulateDataMapFromSettings(Context);

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
	{
		for (const FECsDamageModifier& Modifier : EMCsDamageModifier::Get())
		{
			typedef NCsDamage::NModifier::FManager ModifierManagerType;

			ModifierManagerType& Manager = Manager_Modifiers[Modifier.GetValue()];

			Manager.Shutdown();
		}
	}

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
	ICsReset* IReset = DamageEventLibrary::GetInterfaceChecked<ICsReset>(Context, Event->Get());
	IReset->Reset();

	Manager_Event.Deallocate(Event);
}

EventResourceType* UCsManager_Damage::CreateCopyOfEvent(const FString& Context, const EventType* Event)
{
	EventResourceType* Container = AllocateEvent();
	EventType* Copy				 = Container->Get();

	typedef NCsDamage::NEvent::FLibrary EventLibrary;
	typedef NCsDamage::NEvent::NCopy::ICopy CopyType;

	CopyType* ICopy = EventLibrary::GetInterfaceChecked<CopyType>(Context, Copy);

	ICopy->Copy(Event);

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
	static TArray<ModifierResourceType*> Modifiers;
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

	EventImpl->Data	= Data;

	EventImpl->SetDamageChecked(Context);

	EventImpl->Instigator = Instigator;
	EventImpl->Causer	  = Causer;
	EventImpl->Origin	  = HitResult;
	EventImpl->HitResult  = HitResult;

	return Container;
}

EventResourceType* UCsManager_Damage::CreateEvent(const FString& Context, const ValueType* Value, DataType* Data, UObject* Instigator, UObject* Causer, const FHitResult& HitResult)
{
	static TArray<ModifierResourceType*> Modifiers;
	return CreateEvent(Context, Value, Data, Instigator, Causer, HitResult, Modifiers);
}

#undef DataType
#undef ModifierResourceType
#undef ValueType

void UCsManager_Damage::ProcessDamageEvent(const EventType* Event)
{
	using namespace NCsManagerDamage::NCached;

	const FString& Context = Str::ProcessDamageEvent;

	EventResourceType* Container = CreateCopyOfEvent(Context, Event);

	ProcessDamageEventContainer(Container);
}

void UCsManager_Damage::ProcessDamageEventContainer(const EventResourceType* EventContainer)
{
	using namespace NCsManagerDamage::NCached;

	const FString& Context = Str::ProcessDamageEventContainer;

	check(Manager_Event.IsValidChecked(Context, EventContainer));

	const EventType* Event = EventContainer->Get();

	CS_NON_SHIPPING_EXPR(LogEvent(Event));

	typedef NCsDamage::NData::IData DataType;

	DataType* Data = Event->GetData();

	checkf(Data, TEXT("%s: Data is NULL. No Damage Data found for Event."), *Context);

	// Shape
	typedef NCsDamage::NData::FLibrary DamageDataLibrary;
	typedef NCsDamage::NData::NShape::IShape ShapeDataType;

	if (ShapeDataType* ShapeData = DamageDataLibrary::GetSafeInterfaceChecked<ShapeDataType>(Context, Data))
	{
		// Collision
		typedef NCsDamage::NData::NCollision::ICollision CollisionDataType;
		typedef NCsDamage::NCollision::EMethod CollisionMethodType;

		if (CollisionDataType* CollisionData = DamageDataLibrary::GetSafeInterfaceChecked<CollisionDataType>(Context, Data))
		{
			// PhysicsOverlap
			if (CollisionData->GetCollisionMethod() == CollisionMethodType::PhysicsOverlap)
			{
				typedef NCsDamage::NEvent::FLibrary EventLibrary;

				static TArray<FHitResult> Hits;

				EventLibrary::OverlapChecked(Context, MyRoot, Event, Hits);

				if (Hits.Num() > CS_EMPTY)
				{
					for (const FHitResult& Hit : Hits)
					{
						if (UObject* O = EventLibrary::Implements_ICsReceiveDamage(Context, Hit, nullptr))
						{
							Local_Receivers.AddDefaulted();
							Local_Receivers.Last().SetObject(O);
						}
					}
				}
			}
		}
	}
	// Point
	else
	{
		typedef NCsDamage::NEvent::FLibrary EventLibrary;

		const FHitResult& HitResult = Event->GetHitResult();
		
		if (UObject* O = EventLibrary::Implements_ICsReceiveDamage(Context, HitResult, nullptr))
		{
			Local_Receivers.AddDefaulted();
			Local_Receivers.Last().SetObject(O);
		}
	}

	const int32 Count = Local_Receivers.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		FCsReceiveDamage& Receiver = Local_Receivers[I];

		Receiver.Damage(Event);
	}

	OnProcessDamageEvent_Event.Broadcast(Event);

	Local_Receivers.Reset(Local_Receivers.Max());

	DeallocateEvent(Context, const_cast<EventResourceType*>(EventContainer));
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
	// Range | NCsDamage::NValue::NRange::IRange (NCsDamage::NValue::NRange::FImpl)
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
	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsDamageValue, Type);

	CS_IS_PTR_NULL_CHECKED(Value)

	typedef NCsDamage::NValue::FLibrary ValueLibrary;

	// Reset
	ICsReset* IReset = ValueLibrary::GetInterfaceChecked<ICsReset>(Context, Value->Get());
	IReset->Reset();

	Manager_Values[Type.GetValue()].Deallocate(Value);
}

void UCsManager_Damage::DeallocateValue(const FString& Context, ValueResourceType* Value)
{
	typedef NCsDamage::NValue::FLibrary ValueLibrary;

	const FECsDamageValue& Type = ValueLibrary::GetTypeChecked(Context, Value->Get());

	DeallocateValue(Type, Value);
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
	ICsReset* IReset = RangeLibrary::GetInterfaceChecked<ICsReset>(Context, Range->Get());
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

ModifierType* UCsManager_Damage::ConstructModifier(const FECsDamageModifier& Type)
{
	// ValuePoint | NCsDamage::NModifier::NValue::NPoint::IPoint (NCsDamage::NModifier::NValue::NPoint::FImpl)
	if (Type == NCsDamageModifier::ValuePoint)
		return new NCsDamage::NModifier::NValue::NPoint::FImpl();
	// ValueRange | NCsDamage::NModifier::NValue::NRange::IRange (NCsDamage::NModifier::NValue::NRange::FImpl)
	if (Type == NCsDamageModifier::ValueRange)
		return new NCsDamage::NModifier::NValue::NRange::FImpl();
	// TODO: Fix
	// Range | NCsDamage::NModifier::NRange::IRange (NCsDamage::NModifier::NRange::FImpl)
	if (Type == NCsDamageModifier::Range)
		return new NCsDamage::NModifier::NValue::NPoint::FImpl();
	return nullptr;
}

ModifierResourceType* UCsManager_Damage::AllocateModifier(const FECsDamageModifier& Type)
{
	checkf(EMCsDamageModifier::Get().IsValidEnum(Type), TEXT("UCsManager_Damage::AllocateModifier: Type: %s is NOT Valid."), Type.ToChar());

	return Manager_Modifiers[Type.GetValue()].Allocate();
}

void UCsManager_Damage::DeallocateModifier(const FString& Context, const FECsDamageModifier& Type, ModifierResourceType* Modifier)
{
	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsDamageModifier, Type);

	CS_IS_PTR_NULL_CHECKED(Modifier)

	typedef NCsDamage::NModifier::FLibrary ModifierLibrary;

	// Reset
	ICsReset* IReset = ModifierLibrary::GetInterfaceChecked<ICsReset>(Context, Modifier->Get());
	IReset->Reset();

	Manager_Modifiers[Type.GetValue()].Deallocate(Modifier);
}

const FECsDamageModifier& UCsManager_Damage::GetModifierType(const FString& Context, const ModifierType* Modifier)
{
	typedef NCsDamage::NModifier::FLibrary ModifierLibrary;

	const ICsGetDamageModifierType* GetDamageModifierType = ModifierLibrary::GetInterfaceChecked<ICsGetDamageModifierType>(Context, Modifier);
	const FECsDamageModifier& Type						  = GetDamageModifierType->GetDamageModifierType();

	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsDamageModifier, Type);

	return Type;
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

	if (CS_CVAR_LOG_IS_SHOWING(LogManagerDamageEvents))
	{
		typedef NCsDamage::NEvent::FLibrary EventLibrary;

		EventLibrary::LogEvent(Context, Event);
	}
}

#pragma endregion Log
// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Damage/CsManager_Damage.h"
#include "CsDmg.h"

// CVar
#include "Managers/Damage/CsCVars_Manager_Damage.h"
// Library
#include "Managers/Damage/Data/CsLibrary_Data_Damage.h"
#include "Value/CsLibrary_DamageValue.h"
#include "Range/CsLibrary_DamageRange.h"
#include "Event/CsLibrary_DamageEvent.h"
#include "Modifier/CsLibrary_DamageModifier.h"
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
#include "Event/CsDamageEventImpl.h"
#include "Value/Point/CsDamageValuePointImpl.h"
#include "Value/Range/CsDamageValueRangeImpl.h"
#include "Range/CsDamageRangeImpl.h"
#include "Modifier/Types/CsGetDamageModifierType.h"
#include "Modifier/CsDamageModifierImpl.h"
// Unique
#include "UniqueObject/CsUniqueObject.h"
// Package
#include "UObject/Package.h"

#if WITH_EDITOR
// Singleton
#include "Singleton/CsGetManagerSingleton.h"
#include "Singleton/CsManager_Singleton.h"
#include "Managers/Damage/CsGetManagerDamage.h"
#endif // #if WITH_EDITOR

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsManager_Damage)

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
	Super(ObjectInitializer),
	// Modifiers
	Manager_Modifiers(),
	ImplTypeByModifier()
{
}

using EventResourceType = NCsDamage::NEvent::FResource;
using EventType = NCsDamage::NEvent::IEvent;
using EventImplType = NCsDamage::NEvent::NImpl::FImpl;
using CopyType = NCsDamage::NEvent::NCopy::ICopy;
using DataType = NCsDamage::NData::IData;
using ShapeDataType = NCsDamage::NData::NShape::IShape;
using ModifierManagerType = NCsDamage::NModifier::NResource::FManager;
using ModifierResourceType = NCsDamage::NModifier::NResource::FResource;
using ModifierType = NCsDamage::NModifier::IModifier;
using ModifierImplType = NCsDamage::NModifier::EImpl;
using ValueLibrary = NCsDamage::NValue::NLibrary::FLibrary;
using ValueManagerType = NCsDamage::NValue::FManager;
using ValueResourceType = NCsDamage::NValue::FResource;
using ValueType = NCsDamage::NValue::IValue;
using RangeResourceType = NCsDamage::NRange::FResource;
using RangeType = NCsDamage::NRange::IRange;
using RangeImplType = NCsDamage::NRange::NImpl::FImpl;
using ProcessPayloadType = NCsDamage::NData::NProcess::FPayload;

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
	NCsDamageType::PopulateEnumMapFromSettings(Context, CsGameInstanceLibrary::GetSafeAsObject(MyRoot));
	NCsDamageData::PopulateEnumMapFromSettings(Context, CsGameInstanceLibrary::GetSafeAsObject(MyRoot));

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
	SetupModifiers();

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
			ValueManagerType& Manager = Manager_Values[Value.GetValue()];

			Manager.Shutdown();
		}
	}
	// Range
	Manager_Range.Shutdown();
	// Modifier
	for (ModifierManagerType& ModifierManager : Manager_Modifiers)
	{
		const TArray<ModifierResourceType*>& Containers = ModifierManager.GetPool();

		for (ModifierResourceType* Container : Containers)
		{
			ModifierType* M = Container->Get();
			delete M;
			Container->Set(nullptr);
		}
	}
	Manager_Modifiers.Reset();

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

EventType* UCsManager_Damage::ConstructEvent()
{
	return new EventImplType();
}

EventResourceType* UCsManager_Damage::AllocateEvent()
{
	return Manager_Event.Allocate();
}

void UCsManager_Damage::DeallocateEvent(const FString& Context, EventResourceType* Event)
{
	// Reset
	ICsReset* IReset = CsDamageEventLibrary::GetInterfaceChecked<ICsReset>(Context, Event->Get());
	IReset->Reset();

	Manager_Event.Deallocate(Event);
}

EventResourceType* UCsManager_Damage::CreateCopyOfEvent(const FString& Context, const EventType* Event)
{
	EventResourceType* Container = AllocateEvent();
	EventType* Copy				 = Container->Get();

	CopyType* ICopy = CsDamageEventLibrary::GetInterfaceChecked<CopyType>(Context, Copy);

	ICopy->Copy(Event);

	return Container;
}

EventResourceType* UCsManager_Damage::CreateCopyOfEvent(const FString& Context, const EventResourceType* Event)
{
	return CreateCopyOfEvent(Context, Event->Get());
}

EventResourceType* UCsManager_Damage::CreateEvent(const FString& Context, DataType* Data, const FECsDamageData& Type, UObject* Instigator, UObject* Causer, const FHitResult& HitResult,  const TArray<ModifierType*>& Modifiers)
{
	CS_IS_PTR_NULL_CHECKED(Data)
	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsDamageData, Type)

	if (ShapeDataType* ShapeData = CsDamageDataLibrary::GetSafeInterfaceChecked<ShapeDataType>(Context, Data))
		return CreateEvent(Context, Data->GetValue(), ShapeData->GetRange(), Data, Type, Instigator, Causer, HitResult, Modifiers);
	return CreateEvent(Context, Data->GetValue(), Data, Type, Instigator, Causer, HitResult, Modifiers);
}

EventResourceType* UCsManager_Damage::CreateEvent(const FString& Context, const ValueType* Value, DataType* Data, const FECsDamageData& Type, UObject* Instigator, UObject* Causer, const FHitResult& HitResult, const TArray<ModifierType*>& Modifiers)
{
	CS_IS_PTR_NULL_CHECKED(Data)
	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsDamageData, Type)
	
	// Get Container from Manager_Damage
	EventResourceType* Container = AllocateEvent();

	// Event
	EventType* Event		 = Container->Get();
	EventImplType* EventImpl = CsDamageEventLibrary::PureStaticCastChecked<EventImplType>(Context, Event);

	// Copy Value this can change with modifiers
	EventImpl->DamageValue.CopyFrom(Context, MyRoot, Value);
	ValueType* DamageValue = EventImpl->DamageValue.GetValue();

	// Copy Range from Data, this can change with modifiers
	EventImpl->DamageRange.SafeCopyFrom(Context, MyRoot, Data, nullptr);
	RangeType* Range = EventImpl->DamageRange.GetRange();

	// Apply Modifiers

	if (Range)
	{
		CsDamageModifierLibrary::ModifyChecked(Context, Modifiers, Data, Type, DamageValue, Range);
	}
	else
	{
		CsDamageModifierLibrary::ModifyChecked(Context, Modifiers, Data, Type, DamageValue);
	}

	EventImpl->Type = Type;
	EventImpl->Data	= Data;

	EventImpl->SetDamageChecked(Context);

	EventImpl->Instigator = Instigator;
	EventImpl->Causer	  = Causer;
	EventImpl->Origin	  = HitResult;
	EventImpl->HitResult  = HitResult;

	return Container;
}

EventResourceType* UCsManager_Damage::CreateEvent(const FString& Context, const ValueType* Value, const RangeType* Range, DataType* Data, const FECsDamageData& Type, UObject* Instigator, UObject* Causer, const FHitResult& HitResult, const TArray<ModifierType*>& Modifiers)
{
	static ProcessPayloadType ProcessPayload;
	ProcessPayload.Reset();

	ProcessPayload.Value = const_cast<ValueType*>(Value);
	ProcessPayload.SetRange(const_cast<RangeType*>(Range));
	ProcessPayload.Type		  = Type;
	ProcessPayload.Data		  = Data;
	ProcessPayload.Instigator = Instigator;
	ProcessPayload.Causer	  = Causer;
	ProcessPayload.HitResult  = HitResult;
	ProcessPayload.Modifiers.Append(Modifiers);

	return CreateEvent(Context, ProcessPayload);
}

EventResourceType* UCsManager_Damage::CreateEvent(const FString& Context, const ProcessPayloadType& ProcessPayload)
{
	CS_IS_PTR_NULL_CHECKED(ProcessPayload.Data)
	
	// Get Container from Manager_Damage
	EventResourceType* Container = AllocateEvent();

	// Event
	EventType* Event		 = Container->Get();
	EventImplType* EventImpl = CsDamageEventLibrary::PureStaticCastChecked<EventImplType>(Context, Event);

	// Copy Value this can changed with modifiers
	EventImpl->DamageValue.CopyFrom(Context, MyRoot, ProcessPayload.Value);
	ValueType* DamageValue = EventImpl->DamageValue.GetValue();

	// Copy Range this can changed with modifiers
	if (ProcessPayload.HasSetRange())
	{
		EventImpl->DamageRange.CopyFrom(Context, MyRoot, ProcessPayload.GetRange());

		RangeType* DamageRange = EventImpl->DamageRange.GetRange();

		CsDamageModifierLibrary::ModifyChecked(Context, ProcessPayload.Modifiers, ProcessPayload.Data, ProcessPayload.Type, DamageValue, DamageRange);
	}
	else
	{
		EventImpl->DamageRange.SafeCopyFrom(Context, MyRoot, ProcessPayload.Data, nullptr);
		CsDamageModifierLibrary::ModifyChecked(Context, ProcessPayload.Modifiers, ProcessPayload.Data, ProcessPayload.Type, DamageValue, EventImpl->ModifierMask);
	}

	EventImpl->Type = ProcessPayload.Type;
	EventImpl->Data	= ProcessPayload.Data;

	EventImpl->SetDamageChecked(Context);

	EventImpl->Instigator = ProcessPayload.Instigator;
	EventImpl->Causer	  = ProcessPayload.Causer;
	EventImpl->DamageDirection = ProcessPayload.Direction;
	EventImpl->Origin	  = ProcessPayload.HitResult;
	EventImpl->HitResult  = ProcessPayload.HitResult;

	return Container;
}

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
	CS_NON_SHIPPING_EXPR(CsDamageEventLibrary::Draw(Context, Event));

	DataType* Data = Event->GetData();

	checkf(Data, TEXT("%s: Data is NULL. No Damage Data found for Event."), *Context);

	// Shape
	if (ShapeDataType* ShapeData = CsDamageDataLibrary::GetSafeInterfaceChecked<ShapeDataType>(Context, Data))
	{
		// Collision
		using CollisionDataType = NCsDamage::NData::NCollision::ICollision;
		using CollisionInfoType = NCsDamage::NCollision::FInfo;
		using CollisionMethodType = NCsDamage::NCollision::EMethod;

		if (CollisionDataType* CollisionData = CsDamageDataLibrary::GetSafeInterfaceChecked<CollisionDataType>(Context, Data))
		{
			const CollisionInfoType& CollisionInfo	   = CollisionData->GetCollisionInfo();
			const CollisionMethodType& CollisionMethod = CollisionInfo.GetMethod();

			// PhysicsSweep
			if (CollisionMethod == CollisionMethodType::PhysicsSweep)
			{
				static TArray<FHitResult> Hits;

				CsDamageEventLibrary::SweepChecked(Context, MyRoot, Event, Hits);

				if (Hits.Num() > CS_EMPTY)
				{
					const int32 Count = Hits.Num();

					for (int32 I = Count - 1; I >= 0; --I)
					{
						const FHitResult& Hit = Hits[I]; 

						if (UObject* O = CsDamageEventLibrary::Implements_ICsReceiveDamage(Context, Hit, nullptr))
						{
							Local_Receivers.AddDefaulted();
							Local_Receivers.Last().SetObject(O);

							// TODO: Update Damage Direction
							//		 Update HitResult

							EventResourceType* EvtContainer = CreateCopyOfEvent(Context, EventContainer);

							Local_Events.Add(EvtContainer);
						}
						Hits.RemoveAt(I, 1, false);
					}
				}
			}
			// Custom
			else
			if (CollisionMethod == CollisionMethodType::Custom)
			{
				ProcessDamageEvent_CustomCollision(Event, CollisionData);
			}
		}
	}
	// Point
	else
	{
		const FHitResult& HitResult = Event->GetHitResult();
		
		if (UObject* O = CsDamageEventLibrary::Implements_ICsReceiveDamage(Context, HitResult, nullptr))
		{
			Local_Receivers.AddDefaulted();
			Local_Receivers.Last().SetObject(O);

			EventResourceType* EvtContainer = CreateCopyOfEvent(Context, EventContainer);

			Local_Events.Add(EvtContainer);
		}
	}

	// NOTE: FUTURE: May need to copy Event and pass the copy with changes
	//				 (in the case of wanting HitResult updated for Damage with a Shape, i.e Circle, Sphere, ... etc).

	const int32 Count = Local_Receivers.Num();

	for (int32 I = Count - 1; I >= 0; --I)
	{
		FCsReceiveDamage& Receiver		= Local_Receivers[I];
		EventResourceType* EvtContainer = Local_Events[I];
		EventType* Evt					= EvtContainer->Get();

		Receiver.Damage(Evt);
		Local_Receivers.RemoveAt(I, 1, false);

		DeallocateEvent(Context, EvtContainer);
		Local_Events.RemoveAt(I, 1, false);
	}

	OnProcessDamageEvent_Event.Broadcast(Event);

	DeallocateEvent(Context, const_cast<EventResourceType*>(EventContainer));
}

#pragma endregion Event

// Value
#pragma region

ValueType* UCsManager_Damage::ConstructValue(const FECsDamageValue& Type)
{
	// Point | NCsDamage::NValue::NPoint::IPoint (NCsDamage::NValue::NPoint::NImpl::FImpl)
	if (Type == NCsDamageValue::Point)
		return new NCsDamage::NValue::NPoint::NImpl::FImpl();
	// Range | NCsDamage::NValue::NRange::IRange (NCsDamage::NValue::NRange::NImpl::FImpl)
	if (Type == NCsDamageValue::Range)
		return new NCsDamage::NValue::NRange::NImpl::FImpl();
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

	// Reset
	ICsReset* IReset = ValueLibrary::GetInterfaceChecked<ICsReset>(Context, Value->Get());
	IReset->Reset();

	Manager_Values[Type.GetValue()].Deallocate(Value);
}

void UCsManager_Damage::DeallocateValue(const FString& Context, ValueResourceType* Value)
{
	const FECsDamageValue& Type = ValueLibrary::GetTypeChecked(Context, Value->Get());

	DeallocateValue(Context, Type, Value);
}

#pragma endregion Value

// Range
#pragma region

RangeType* UCsManager_Damage::ConstructRange()
{
	return new RangeImplType();
}

RangeResourceType* UCsManager_Damage::AllocateRange()
{
	return Manager_Range.Allocate();
}

void UCsManager_Damage::DeallocateRange(const FString& Context, RangeResourceType* Range)
{
	// Reset
	ICsReset* IReset = CsDamageRangeLibrary::GetInterfaceChecked<ICsReset>(Context, Range->Get());
	IReset->Reset();

	Manager_Range.Deallocate(Range);
}

#pragma endregion  Range

// Modifier
#pragma region

void UCsManager_Damage::SetupModifiers()
{
	Manager_Modifiers.Reset((uint8)ModifierImplType::EImpl_MAX);
	Manager_Modifiers.AddDefaulted((uint8)ModifierImplType::EImpl_MAX);

	const FCsSettings_Manager_Damage_Modifier& ModifierSettings = FCsSettings_Manager_Damage_Modifier::Get();

	const int32& PoolSize = ModifierSettings.PoolSize;

	// Int
	{
		ModifierManagerType& ModifierManager = Manager_Modifiers[(uint8)ModifierImplType::Int];

		ModifierManager.CreatePool(PoolSize);

		for (int32 I = 0; I < PoolSize; ++I)
		{
			ModifierManager.Add(ConstructModifier(ModifierImplType::Int));
		}
	}
	// Float
	{
		ModifierManagerType& ModifierManager = Manager_Modifiers[(uint8)ModifierImplType::Float];

		ModifierManager.CreatePool(PoolSize);

		for (int32 I = 0; I < PoolSize; ++I)
		{
			ModifierManager.Add(ConstructModifier(ModifierImplType::Float));
		}
	}
	// Toggle
	{
		ModifierManagerType& ModifierManager = Manager_Modifiers[(uint8)ModifierImplType::Toggle];

		ModifierManager.CreatePool(PoolSize);

		for (int32 I = 0; I < PoolSize; ++I)
		{
			ModifierManager.Add(ConstructModifier(ModifierImplType::Toggle));
		}
	}

	ImplTypeByModifier.Reset(EMCsDamageModifier::Get().Num());
	ImplTypeByModifier.AddDefaulted(EMCsDamageModifier::Get().Num());

	ImplTypeByModifier[NCsDamageModifier::ValuePoint.GetValue()]			= ModifierImplType::Float;
	ImplTypeByModifier[NCsDamageModifier::ValueRange_Uniform.GetValue()]	= ModifierImplType::Float;
	//ImplTypeByModifier[NCsDamageModifier::ValueRange_Range.GetValue()]	= ModifierImplType::Float;
	ImplTypeByModifier[NCsDamageModifier::Range_Uniform.GetValue()]			= ModifierImplType::Float;
	//ImplTypeByModifier[NCsDamageModifier::Range_Range.GetValue()]			= ModifierImplType::Float;
	// Critical
	ImplTypeByModifier[NCsDamageModifier::CriticalChance.GetValue()] = ModifierImplType::Float;
	ImplTypeByModifier[NCsDamageModifier::CriticalStrike.GetValue()] = ModifierImplType::Float;
}

ModifierType* UCsManager_Damage::ConstructModifier(const ModifierImplType& ImplType)
{
	// Int
	if (ImplType == ModifierImplType::Int)
		return new NCsDamage::NModifier::NInt::FInt();
	// Float
	if (ImplType == ModifierImplType::Float)
		return new NCsDamage::NModifier::NFloat::FFloat();
	// Toggle
	if (ImplType == ModifierImplType::Toggle)
		return new NCsDamage::NModifier::NToggle::FToggle();
	// TODO: Float Range
	check(0);
	return nullptr;
}

ModifierResourceType* UCsManager_Damage::AllocateModifier(const FECsDamageModifier& Type)
{
	checkf(EMCsDamageModifier::Get().IsValidEnum(Type), TEXT("UCsManager_Damage::AllocateModifier: Type: %s is NOT Valid."), Type.ToChar());

	return GetManagerModifier(Type).Allocate();
}

void UCsManager_Damage::DeallocateModifier(const FString& Context, const FECsDamageModifier& Type, ModifierResourceType* Modifier)
{
	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsDamageModifier, Type);
	CS_IS_PTR_NULL_CHECKED(Modifier)

	// Reset
	ICsReset* IReset = CsDamageModifierLibrary::GetInterfaceChecked<ICsReset>(Context, Modifier->Get());
	IReset->Reset();

	GetManagerModifier(Type).Deallocate(Modifier);
}

const FECsDamageModifier& UCsManager_Damage::GetModifierType(const FString& Context, const ModifierType* Modifier)
{
	const ICsGetDamageModifierType* GetDamageModifierType = CsDamageModifierLibrary::GetInterfaceChecked<ICsGetDamageModifierType>(Context, Modifier);
	const FECsDamageModifier& Type						  = GetDamageModifierType->GetDamageModifierType();

	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsDamageModifier, Type);

	return Type;
}

#pragma endregion Modifier

// Data
#pragma region

void UCsManager_Damage::ConstructDataHandler()
{
	using DataHandlerImplType = NCsDamage::NManager::NHandler::NData::FData;

	DataHandler			= new DataHandlerImplType();
	DataHandler->Outer  = this;
	DataHandler->MyRoot = MyRoot;
}

const FECsDamageData& UCsManager_Damage::GetDataTypeChecked(const FString& Context, const DataType* Data) const
{
	CS_IS_PTR_NULL_CHECKED(Data)

	return DataHandler->GetTypeChecked<EMCsDamageData, FECsDamageData>(Context, Data);
}

DataType* UCsManager_Damage::GetDataChecked(const FString& Context, const FName& Name)
{
#if UE_BUILD_SHIPPING
	return DataHandler->GetDataChecked(Context, Name);
#else
	DataType* Data = DataHandler->GetDataChecked(Context, Name);

	check(IsValidChecked(Context, Data));
	return Data;
#endif // #if UE_BUILD_SHIPPING
}

DataType* UCsManager_Damage::GetSafeData(const FString& Context, const FName& Name, void(*Log)(const FString&) /*=nullptr*/)
{
#if UE_BUILD_SHIPPING
	return DataHandler->GetSafeData(Context, Name, Log);
#else
	DataType* Data = DataHandler->GetSafeData(Context, Name, Log);

	if (!IsValid(Context, Data, Log))
		return nullptr;
	return Data;
#endif // #if UE_BUILD_SHIPPING
}

DataType* UCsManager_Damage::GetSafeData(const FString& Context, const FECsDamageData& Type, void(*Log)(const FString&) /*=nullptr*/)
{
	using EnumMapType = EMCsDamageData;
	using EnumType = FECsDamageData;

#if UE_BUILD_SHIPPING
	return DataHandler->GetSafeData<EnumMapType, EnumType>(Context, Type, Log);
#else
	DataType* Data = DataHandler->GetSafeData<EnumMapType, EnumType>(Context, Type, Log);

	if (!IsValid(Context, Data, Log))
		return nullptr;
	return Data;
#endif // #if UE_BUILD_SHIPPING
}

#pragma endregion Data

// Valid
#pragma region

bool UCsManager_Damage::IsValidChecked(const FString& Context, const DataType* Data) const
{
	check(CsDamageDataLibrary::IsValidChecked(Context, Data));
	return true;
}

bool UCsManager_Damage::IsValid(const FString& Context, const DataType* Data, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/)
{
	if (!CsDamageDataLibrary::IsValid(Context, Data, Log))
		return false;
	return true;
}

#pragma endregion Valid

// Log
#pragma region

void UCsManager_Damage::LogEvent(const EventType* Event)
{
	using namespace NCsManagerDamage::NCached;

	const FString& Context = Str::LogEvent;

	if (CS_CVAR_LOG_IS_SHOWING(LogManagerDamageEvents))
	{
		CsDamageEventLibrary::LogEvent(Context, Event);
	}
}

#pragma endregion Log
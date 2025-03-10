// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Resource
#include "Managers/Resource/CsManager_ResourceValueType_Abstract_Fixed.h"
#include "Managers/Resource/CsManager_ResourcePointerType_Fixed.h"
// Types
#include "Managers/Damage/Data/Types/CsTypes_Data_Damage.h"
#include "Value/Types/CsTypes_DamageValue.h"
#include "Modifier/Types/CsTypes_DamageModifier.h"
#include "UniqueObject/CsTypes_UniqueObject.h"
// Damage
#include "Event/CsDamageEvent.h"
#include "Value/CsResource_DamageValue.h"
#include "Range/CsDamageRange.h"
#include "Modifier/CsResource_DamageModifier.h"
#include "Managers/Damage/CsReceiveDamage.h"
#include "Process/Payload/CsProcessDamageDataPayload.h"

#include "CsManager_Damage.generated.h"

// Structs
#pragma region

namespace NCsDamage
{
	namespace NEvent
	{
		// NCsDamage::NEvent::IEvent

		/**
		* Container for holding a reference to an object that implements the interface: NCsDamage::NEvent::IEvent.
		* This serves as an easy way for a Manager Resource to keep track of the resource.
		*/
		struct CSDMG_API FResource : public TCsResourceContainer<IEvent> {};

		/**
		* A manager handling allocating and deallocating objects that implement the interface: NCsDamage::NEvent::IEvent and
		* are wrapped in the container: NCsDamage::NEvent::FResource.
		*/
		struct CSDMG_API FManager : public NCsResource::NManager::NValue::NAbstract::TFixed<IEvent, FResource, 0> {};
	}

	namespace NRange
	{
		// NCsDamage::NRange::IRange

		/**
		* Container for holding a reference to an object that implements the interface: NCsDamage::NRange::IRange.
		* This serves as an easy way for a Manager Resource to keep track of the resource.
		*/
		struct CSDMG_API FResource : public TCsResourceContainer<IRange> {};

		/**
		* A manager handling allocating and deallocating objects that implement the interface: NCsDamage::NRange::IRange and
		* are wrapped in the container: NCsDamage::NRange::FResource.
		*/
		struct CSDMG_API FManager : public NCsResource::NManager::NValue::NAbstract::TFixed<IRange, FResource, 0> {};
	}
}

#pragma endregion Structs

class ICsGetManagerDamage;

// NCsDamage::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NData, IData)

// NCsData::NManager::NHandler::TData
namespace NCsData {
	namespace NManager {
		namespace NHandler {
			template<typename InterfaceDataType, typename DataContainerType, typename DataInterfaceMapType>
			class TData;
		}
	}
}

// NCsDamage::NData::FInterfaceMap
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NData, FInterfaceMap)

// NCsDamage::NData::NCollision::ICollision
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsDamage, NData, NCollision, ICollision)

UCLASS()
class CSDMG_API UCsManager_Damage : public UObject
{
	GENERATED_UCLASS_BODY()

private:

	using EventResourceType = NCsDamage::NEvent::FResource;
	using EventManagerType = NCsDamage::NEvent::FManager;
	using EventType = NCsDamage::NEvent::IEvent;

	using ValueResourceType = NCsDamage::NValue::FResource;
	using ValueManagerType = NCsDamage::NValue::FManager;
	using ValueType = NCsDamage::NValue::IValue;

	using RangeResourceType = NCsDamage::NRange::FResource;
	using RangeManagerType = NCsDamage::NRange::FManager;
	using RangeType = NCsDamage::NRange::IRange;

	using ModifierResourceType = NCsDamage::NModifier::NResource::FResource;
	using ModifierManagerType = NCsDamage::NModifier::NResource::FManager;
	using ModifierType = NCsDamage::NModifier::IModifier;
	using ModifierImplType = NCsDamage::NModifier::EImpl;

	using DataType = NCsDamage::NData::IData;
	using DataInterfaceMapType = NCsDamage::NData::FInterfaceMap;
	using DataHandlerType = NCsData::NManager::NHandler::TData<DataType, FCsData_DamagePtr, DataInterfaceMapType>;

	using CollisionDataType = NCsDamage::NData::NCollision::ICollision;

	using ProcessPayloadType = NCsDamage::NData::NProcess::FPayload;

// Singleton
#pragma region
public:

#if WITH_EDITOR
	static UCsManager_Damage* Get(const UObject* InRoot = nullptr);
#else
FORCEINLINE static UCsManager_Damage* Get(const UObject* InRoot = nullptr)
{
	return s_bShutdown ? nullptr : s_Instance;
}
#endif // #if WITH_EDITOR

	template<typename T>
	FORCEINLINE static T* Get(const UObject* InRoot = nullptr)
	{
		return Cast<T>(Get(InRoot));
	}

#if WITH_EDITOR
	static UCsManager_Damage* GetSafe(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) = nullptr);
#else
	FORCEINLINE static UCsManager_Damage* GetSafe(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) = nullptr)
	{
		return s_bShutdown ? nullptr : s_Instance;
	}
#endif // #if WITH_EDITOR

#if WITH_EDITOR
	static bool IsValid(const UObject* InRoot = nullptr);
#else
	FORCEINLINE static bool IsValid(const UObject* InRoot = nullptr)
	{
		return s_bShutdown ? false : s_Instance != nullptr;
	}
#endif // #if WITH_EDITOR

	static void Init(UObject* InRoot, TSubclassOf<UCsManager_Damage> ManagerDamageClass, UObject* InOuter = nullptr);
	
	static void Shutdown(const UObject* InRoot = nullptr);
	static bool HasShutdown(const UObject* InRoot = nullptr);

#if WITH_EDITOR
protected:

	static ICsGetManagerDamage* Get_GetManagerDamage(const UObject* InRoot);
	static ICsGetManagerDamage* GetSafe_GetManagerDamage(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) = nullptr);

#endif // #if WITH_EDITOR

protected:

	bool bInitialized;

	virtual void Initialize();

public:

	static bool HasInitialized(UObject* InRoot);

protected:

	virtual void CleanUp();

private:
	// Singleton data
	static UCsManager_Damage* s_Instance;
	static bool s_bShutdown;

	// Root
#pragma region
protected:

	UObject* MyRoot;

	void SetMyRoot(UObject* InRoot);

public:

	FORCEINLINE UObject* GetMyRoot()
	{
		return MyRoot;
	}

#pragma endregion Root

#pragma endregion Singleton

// Receive Damage
#pragma region
protected:

	TMap<FCsUniqueObjectId, ICsReceiveDamage*> ReceiveDamageMap;

public:

	void Add(ICsReceiveDamage* Object);

	void Remove(ICsReceiveDamage* Object);

#pragma endregion Receive Damage

// Event
#pragma region
protected:

	EventManagerType Manager_Event;

	/**
	*
	*
	* return	Event that implements the interface: NCsDamage::NEvent::IEvent
	*/
	virtual EventType* ConstructEvent();

public:

	/**
	*
	*
	* return
	*/
	EventResourceType* AllocateEvent();

	virtual void DeallocateEvent(const FString& Context, EventResourceType* Event);

	EventResourceType* CreateCopyOfEvent(const FString& Context, const EventType* Event);

	EventResourceType* CreateCopyOfEvent(const FString& Context, const EventResourceType* Event);

	EventResourceType* CreateEvent(const FString& Context, DataType* Data, const FECsDamageData& Type, UObject* Instigator, UObject* Causer, const FHitResult& HitResult, const TArray<ModifierType*>& Modifiers);
	FORCEINLINE EventResourceType* CreateEvent(const FString& Context, DataType* Data, const FECsDamageData& Type, UObject* Instigator, UObject* Causer, const FHitResult& HitResult)
	{
		static TArray<ModifierType*> Modifiers;
		return CreateEvent(Context, Data, Type, Instigator, Causer, HitResult, Modifiers);
	}

	EventResourceType* CreateEvent(const FString& Context, const ValueType* Value, DataType* Data, const FECsDamageData& Type, UObject* Instigator, UObject* Causer, const FHitResult& HitResult, const TArray<ModifierType*>& Modifiers);
	FORCEINLINE EventResourceType* CreateEvent(const FString& Context, const ValueType* Value, DataType* Data, const FECsDamageData& Type, UObject* Instigator, UObject* Causer, const FHitResult& HitResult)
	{
		static TArray<ModifierType*> Modifiers;
		return CreateEvent(Context, Value, Data, Type, Instigator, Causer, HitResult, Modifiers);
	}

	EventResourceType* CreateEvent(const FString& Context, const ValueType* Value, const RangeType* Range, DataType* Data, const FECsDamageData& Type, UObject* Instigator, UObject* Causer, const FHitResult& HitResult, const TArray<ModifierType*>& Modifiers);
	FORCEINLINE EventResourceType* CreateEvent(const FString& Context, const ValueType* Value, const RangeType* Range, DataType* Data, const FECsDamageData& Type, UObject* Instigator, UObject* Causer, const FHitResult& HitResult)
	{
		static TArray<ModifierType*> Modifiers;
		return CreateEvent(Context, Value, Range, Data, Type, Instigator, Causer, HitResult, Modifiers);
	}

	EventResourceType* CreateEvent(const FString& Context, const ProcessPayloadType& ProcessPayload);

protected:

	TArray<FCsReceiveDamage> Local_Receivers;

	TArray<EventResourceType*> Local_Events;

public:

	/**
	*
	*
	* @param Event	Event that implements the interface: (EventType) NCsDamage::NEvent::IEvent
	*/
	void ProcessDamageEvent(const EventType* Event);

	/**
	*
	*
	* @param Event
	*/
	void ProcessDamageEventContainer(const EventResourceType* Event);

	/**
	*
	*
	* @param Event	Event that implements the interface: (EventType) NCsDamage::NEvent::IEvent
	*/
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnProcessDamageEvent, const EventType* /*Event*/);

	/** */
	FOnProcessDamageEvent OnProcessDamageEvent_Event;

protected:

	virtual void ProcessDamageEvent_CustomCollision(const EventType* Event, const CollisionDataType* CollisionData)
	{
		checkf(0, TEXT("UCsManager_Damage::ProcessDamageEvent_CustomCollision: NOT IMPLEMENTED."));
	}

#pragma endregion Event

// Value
#pragma region
protected:

	TArray<ValueManagerType> Manager_Values;

	/**
	* Constructs an object that implements the interface: NCsDamage::NValue::IValue for the 
	* appropriate Type.
	*
	* @param Type
	* return
	*/
	virtual ValueType* ConstructValue(const FECsDamageValue& Type);

public:

	/**
	*
	*
	* @param Type
	* return
	*/
	ValueResourceType* AllocateValue(const FECsDamageValue& Type);

	/**
	*
	*
	* @param Type
	* @param Value
	*/
	virtual void DeallocateValue(const FString& Context, const FECsDamageValue& Type, ValueResourceType* Value);

protected:

	/**
	*
	*
	* @param Context
	* @param Value
	*/
	virtual void DeallocateValue(const FString& Context, ValueResourceType* Value);

#pragma endregion Value

// Range
#pragma region
protected:

	RangeManagerType Manager_Range;

	virtual NCsDamage::NRange::IRange* ConstructRange();

public:

	RangeResourceType* AllocateRange();

	void DeallocateRange(const FString& Context, RangeResourceType* Range);

#pragma endregion Range

// Modifier
#pragma region
protected:

	TArray<ModifierManagerType> Manager_Modifiers;

	TArray<ModifierImplType> ImplTypeByModifier;

	FORCEINLINE const ModifierImplType& GetModifierImplType(const FECsDamageModifier& Type) const
	{
		return ImplTypeByModifier[Type.GetValue()];
	}

	FORCEINLINE ModifierManagerType& GetManagerModifier(const FECsDamageModifier& Type)
	{
		return Manager_Modifiers[(uint8)GetModifierImplType(Type)];
	}

	void SetupModifiers();

	virtual ModifierType* ConstructModifier(const ModifierImplType& ImplType);

public:

	ModifierResourceType* AllocateModifier(const FECsDamageModifier& Type);

	void DeallocateModifier(const FString& Context, const FECsDamageModifier& Type, ModifierResourceType* Modifier);

	/**
	*
	*
	* @param Context	The calling context.
	* @param Value
	* return
	*/
	virtual const FECsDamageModifier& GetModifierType(const FString& Context, const ModifierType* Modifier);

#pragma endregion Modifier

// Data
#pragma region
protected:

	DataHandlerType* DataHandler;

	virtual void ConstructDataHandler();

public:

	FORCEINLINE DataHandlerType* GetDataHandler() const { return DataHandler; }

public:

	const FECsDamageData& GetDataTypeChecked(const FString& Context, const DataType* Data) const;

	/**
	* Get the Data (implements interface: DataType (NCsData::NData::IData)) associated with Name of the projectile type.
	* "Checked" in regards to returning a valid pointer.
	*
	* @param Context	The calling context.
	* @param Name		Name of the Projectile.
	* return			Data that implements the interface: DataType (NCsData::NData::IData).
	*/
	DataType* GetDataChecked(const FString& Context, const FName& Name);

	/**
	* Safely get the Data (implements interface: DataType (NCsData::NData::IData)) associated with Name of the weapon type.
	*
	* @param Context	The calling context.
	* @param Name		Name of the Damage.
	* @param Log		(optional)
	* return			Data that implements the interface: DataType (NCsData::NData::IData).
	*/
	DataType* GetSafeData(const FString& Context, const FName& Name, void(*Log)(const FString&) = nullptr);

	/**
	* Safely get the Data (implements interface: DataType (NCsData::NData::IData)) associated with Name of the weapon type.
	*
	* @param Context	The calling context.
	* @param Type		Damage Type.
	* @param Log		(optional)
	* return			Data that implements the interface: DataType (NCsData::NData::IData).
	*/
	DataType* GetSafeData(const FString& Context, const FECsDamageData& Type, void(*Log)(const FString&) = nullptr);

	FORCEINLINE void ProcessData(const FString& Context, DataType* Data, const FECsDamageData& Type, UObject* Instigator, UObject* Causer, const FHitResult& HitResult, const TArray<ModifierType*>& Modifiers)
	{
		const EventResourceType* Container = CreateEvent(Context, Data, Type, Instigator, Causer, HitResult, Modifiers);

		ProcessDamageEventContainer(Container);
	}
	FORCEINLINE void ProcessData(const FString& Context, DataType* Data, const FECsDamageData& Type, UObject* Instigator, UObject* Causer, const FHitResult& HitResult)
	{
		const EventResourceType* Container = CreateEvent(Context, Data, Type, Instigator, Causer, HitResult);

		ProcessDamageEventContainer(Container);
	}

	FORCEINLINE void ProcessData(const FString& Context, const ValueType* Value, DataType* Data, const FECsDamageData& Type, UObject* Instigator, UObject* Causer, const FHitResult& HitResult, const TArray<ModifierType*>& Modifiers)
	{
		const EventResourceType* Container = CreateEvent(Context, Value, Data, Type, Instigator, Causer, HitResult, Modifiers);

		ProcessDamageEventContainer(Container);
	}
	FORCEINLINE void ProcessData(const FString& Context, const ValueType* Value, DataType* Data, const FECsDamageData& Type, UObject* Instigator, UObject* Causer, const FHitResult& HitResult)
	{
		static TArray<ModifierType*> Modifiers;
		ProcessData(Context, Value, Data, Type, Instigator, Causer, HitResult, Modifiers);
	}

	FORCEINLINE void ProcessData(const FString& Context, const ValueType* Value, const RangeType* Range, DataType* Data, const FECsDamageData& Type, UObject* Instigator, UObject* Causer, const FHitResult& HitResult, const TArray<ModifierType*>& Modifiers)
	{
		const EventResourceType* Container = CreateEvent(Context, Value, Range, Data, Type, Instigator, Causer, HitResult, Modifiers);

		ProcessDamageEventContainer(Container);
	}
	FORCEINLINE void ProcessData(const FString& Context, const ValueType* Value, const RangeType* Range, DataType* Data, const FECsDamageData& Type, UObject* Instigator, UObject* Causer, const FHitResult& HitResult)
	{
		static TArray<ModifierType*> Modifiers;
		ProcessData(Context, Value, Range, Data, Type, Instigator, Causer, HitResult, Modifiers);
	}

	FORCEINLINE void ProcessData(const FString& Context, const ProcessPayloadType& ProcessPayload)
	{
		const EventResourceType* Container = CreateEvent(Context, ProcessPayload);

		ProcessDamageEventContainer(Container);
	}

#pragma endregion Data

// Valid
#pragma region
protected:

	virtual bool IsValidChecked(const FString& Context, const DataType* Data) const;
	virtual bool IsValid(const FString& Context, const DataType* Data, void(*Log)(const FString&) = &NCsDamage::FLog::Warning);

#pragma endregion Valid

// Log
#pragma region
public:

	void LogEvent(const EventType* Event);

#pragma endregion Log
};
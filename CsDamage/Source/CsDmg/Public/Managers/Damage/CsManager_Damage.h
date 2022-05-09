// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
// Resource
#include "Managers/Resource/CsManager_ResourceValueType_Abstract_Fixed.h"
#include "Managers/Resource/CsManager_ResourcePointerType_Fixed.h"
// Damage
#include "Event/CsDamageEvent.h"
#include "Value/CsResource_DamageValue.h"
#include "Range/CsDamageRange.h"
#include "Modifier/CsResource_DamageModifier.h"
#include "Managers/Damage/CsReceiveDamage.h"
#include "Process/Payload/CsProcessDamageDataPayload.h"
// Types
#include "Managers/Damage/Data/Types/CsTypes_Data_Damage.h"
#include "Value/Types/CsTypes_DamageValue.h"
#include "Modifier/Types/CsTypes_DamageModifier.h"
#include "UniqueObject/CsTypes_UniqueObject.h"

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

UCLASS()
class CSDMG_API UCsManager_Damage : public UObject
{
	GENERATED_UCLASS_BODY()

#define EventResourceType NCsDamage::NEvent::FResource
#define EventManagerType NCsDamage::NEvent::FManager
#define EventType NCsDamage::NEvent::IEvent

#define ValueResourceType NCsDamage::NValue::FResource
#define ValueManagerType NCsDamage::NValue::FManager
#define ValueType NCsDamage::NValue::IValue

#define RangeResourceType NCsDamage::NRange::FResource
#define RangeManagerType NCsDamage::NRange::FManager
#define RangeType NCsDamage::NRange::IRange

#define ModifierResourceType NCsDamage::NModifier::FResource
#define ModifierManagerType NCsDamage::NModifier::FManager
#define ModifierType NCsDamage::NModifier::IModifier

#define DataType NCsDamage::NData::IData

#define ProcessPayloadType NCsDamage::NData::NProcess::FPayload

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

	EventResourceType* CreateEvent(const FString& Context, DataType* Data, UObject* Instigator, UObject* Causer, const FHitResult& HitResult, const TArray<ModifierResourceType*>& Modifiers);
	EventResourceType* CreateEvent(const FString& Context, DataType* Data, UObject* Instigator, UObject* Causer, const FHitResult& HitResult);

	EventResourceType* CreateEvent(const FString& Context, const ValueType* Value, DataType* Data, UObject* Instigator, UObject* Causer, const FHitResult& HitResult, const TArray<ModifierResourceType*>& Modifiers);
	EventResourceType* CreateEvent(const FString& Context, const ValueType* Value, DataType* Data, UObject* Instigator, UObject* Causer, const FHitResult& HitResult);

	EventResourceType* CreateEvent(const FString& Context, const ValueType* Value, const RangeType* Range, DataType* Data, UObject* Instigator, UObject* Causer, const FHitResult& HitResult, const TArray<ModifierResourceType*>& Modifiers);
	EventResourceType* CreateEvent(const FString& Context, const ValueType* Value, const RangeType* Range, DataType* Data, UObject* Instigator, UObject* Causer, const FHitResult& HitResult);

	EventResourceType* CreateEvent(const FString& Context, const ProcessPayloadType& ProcessPayload);

private:

	TArray<FCsReceiveDamage> Local_Receivers;

public:

	/**
	*
	*
	* @param Event	Event that implements the interface: NCsDamage::NEvent::IEvent
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
	* @param Event	Event that implements the interface: NCsDamage::NEvent::IEvent
	*/
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnProcessDamageEvent, const EventType* /*Event*/);

	/** */
	FOnProcessDamageEvent OnProcessDamageEvent_Event;

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

	virtual ModifierType* ConstructModifier(const FECsDamageModifier& Type);

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

#define DataHandlerType NCsData::NManager::NHandler::TData
#define DataInterfaceMapType NCsDamage::NData::FInterfaceMap

	DataHandlerType<DataType, FCsData_DamagePtr, DataInterfaceMapType>* DataHandler;

	virtual void ConstructDataHandler();

public:

	FORCEINLINE DataHandlerType<DataType, FCsData_DamagePtr, DataInterfaceMapType>* GetDataHandler() const { return DataHandler; }

#undef DataHandlerType
#undef DataInterfaceMapType

public:

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
	* @param Name		Name of the Weapon.
	* @param Log		(optional)
	* return			Data that implements the interface: DataType (NCsData::NData::IData).
	*/
	DataType* GetSafeData(const FString& Context, const FName& Name, void(*Log)(const FString&) = nullptr);

	void ProcessData(const FString& Context, DataType* Data, UObject* Instigator, UObject* Causer, const FHitResult& HitResult, const TArray<ModifierResourceType*>& Modifiers);
	void ProcessData(const FString& Context, DataType* Data, UObject* Instigator, UObject* Causer, const FHitResult& HitResult);

	void ProcessData(const FString& Context, const ValueType* Value, DataType* Data, UObject* Instigator, UObject* Causer, const FHitResult& HitResult, const TArray<ModifierResourceType*>& Modifiers);
	void ProcessData(const FString& Context, const ValueType* Value, DataType* Data, UObject* Instigator, UObject* Causer, const FHitResult& HitResult);

	void ProcessData(const FString& Context, const ValueType* Value, const RangeType* Range, DataType* Data, UObject* Instigator, UObject* Causer, const FHitResult& HitResult, const TArray<ModifierResourceType*>& Modifiers);
	void ProcessData(const FString& Context, const ValueType* Value, const RangeType* Range, DataType* Data, UObject* Instigator, UObject* Causer, const FHitResult& HitResult);

	void ProcessData(const FString& Context, const ProcessPayloadType& ProcessPayload);

#pragma endregion Data

// Log
#pragma region
public:

	void LogEvent(const EventType* Event);

#pragma endregion Log

#undef EventResourceType
#undef EventManagerType
#undef EventType

#undef ValueResourceType
#undef ValueManagerType
#undef ValueType

#undef RangeResourceType
#undef RangeManagerType
#undef RangeType

#undef ModifierResourceType
#undef ModifierManagerType
#undef ModifierType

#undef DataType

#undef ProcessPayloadType
};
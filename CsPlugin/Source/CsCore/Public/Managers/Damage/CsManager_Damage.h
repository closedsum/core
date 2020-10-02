// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
// Resource
#include "Managers/Resource/CsManager_ResourceValueType_Abstract_Fixed.h"
#include "Managers/Resource/CsManager_ResourcePointerType_Fixed.h"
// Damage
#include "Managers/Damage/Event/CsDamageEvent.h"
#include "Managers/Damage/Value/CsDamageValue.h"
#include "Managers/Damage/Range/CsDamageRange.h"
#include "Managers/Damage/Modifier/CsDamageModifier.h"
#include "Managers/Damage/CsReceiveDamage.h"
// Types
#include "Managers/Damage/Value/CsTypes_DamageValue.h"

#include "UniqueObject/CsTypes_UniqueObject.h"

#include "CsManager_Damage.generated.h"

// Structs
#pragma region

	// NCsDamage::NEvent::IEvent

/**
* Container for holding a reference to an object that implements the interface: NCsDamage::NEvent::IEvent.
* This serves as an easy way for a Manager Resource to keep track of the resource.
*/
struct CSCORE_API FCsResource_DamageEvent : public TCsResourceContainer<NCsDamage::NEvent::IEvent>
{
};

/**
* A manager handling allocating and deallocating objects that implement the interface: NCsDamage::NEvent::IEvent and
* are wrapped in the container: FCsResource_DamageEvent.
*/
struct CSCORE_API FCsManager_DamageEvent : public TCsManager_ResourceValueType_Abstract_Fixed<NCsDamage::NEvent::IEvent, FCsResource_DamageEvent, 0>
{
};
	
	// NCsDamage::NValue::IValue

/**
* Container for holding a reference to an object that implements the interface: NCsDamage::NValue::IValue.
* This serves as an easy way for a Manager Resource to keep track of the resource.
*/
struct CSCORE_API FCsResource_DamageValue : public TCsResourceContainer<NCsDamage::NValue::IValue>
{
};

/**
* A manager handling allocating and deallocating objects that implement the interface: NCsDamage::NValue::IValue and
* are wrapped in the container: FCsResource_DamageValue.
*/
struct CSCORE_API FCsManager_DamageValue : public TCsManager_ResourcePointerType_Fixed<NCsDamage::NValue::IValue, FCsResource_DamageValue, 0>
{
};

	// NCsDamage::NRange::IRange

/**
* Container for holding a reference to an object that implements the interface: NCsDamage::NRange::IRange.
* This serves as an easy way for a Manager Resource to keep track of the resource.
*/
struct CSCORE_API FCsResource_DamageRange : public TCsResourceContainer<NCsDamage::NRange::IRange>
{
};

/**
* A manager handling allocating and deallocating objects that implement the interface: NCsDamage::NRange::IRange and
* are wrapped in the container: FCsResource_DamageRange.
*/
struct CSCORE_API FCsManager_DamageRange : public TCsManager_ResourceValueType_Abstract_Fixed<NCsDamage::NRange::IRange, FCsResource_DamageRange, 0>
{
};

	// NCsDamage::NModifier::IModifier

/**
* Container for holding a reference to an object that implements the interface: NCsDamage::NModifier::IModifier.
* This serves as an easy way for a Manager Resource to keep track of the resource.
*/
struct CSCORE_API FCsResource_DamageModifier : public TCsResourceContainer<NCsDamage::NModifier::IModifier>
{

};

/**
* A manager handling allocating and deallocating objects that implement the interface: NCsDamage::NModifier::IModifier and
* are wrapped in the container: FCsResource_DamageModifier.
*/
struct CSCORE_API FCsManager_DamageModifier : public TCsManager_ResourceValueType_Abstract_Fixed<NCsDamage::NModifier::IModifier, FCsResource_DamageModifier, 0>
{
};

#pragma endregion Structs

class ICsGetManagerDamage;
class ICsData_Damage;

UCLASS()
class CSCORE_API UCsManager_Damage : public UObject
{
	GENERATED_UCLASS_BODY()

#define EventType NCsDamage::NEvent::IEvent

// Singleton
#pragma region
public:

	static UCsManager_Damage* Get(UObject* InRoot = nullptr);
	
	template<typename T>
	static T* Get(UObject* InRoot = nullptr)
	{
		return Cast<T>(Get(InRoot));
	}

	static bool IsValid(UObject* InRoot = nullptr);

	static void Init(UObject* InRoot, TSubclassOf<UCsManager_Damage> ManagerDamageClass, UObject* InOuter = nullptr);
	
	static void Shutdown(UObject* InRoot = nullptr);
	static bool HasShutdown(UObject* InRoot = nullptr);

#if WITH_EDITOR
protected:

	static ICsGetManagerDamage* Get_GetManagerDamage(UObject* InRoot);
	static ICsGetManagerDamage* GetSafe_GetManagerDamage(UObject* Object);

	static UCsManager_Damage* GetSafe(UObject* Object);

public:

	static UCsManager_Damage* GetFromWorldContextObject(const UObject* WorldContextObject);

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

	FCsManager_DamageEvent Manager_Event;

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
	FCsResource_DamageEvent* AllocateEvent();

	virtual void DeallocateEvent(const FString& Context, FCsResource_DamageEvent* Event);

	virtual bool CopyEvent(const FString& Context, const EventType* From, EventType* To);

	FCsResource_DamageEvent* CreateCopyOfEvent(const FString& Context, const EventType* Event);

	FCsResource_DamageEvent* CreateCopyOfEvent(const FString& Context, const FCsResource_DamageEvent* Event);

private:

	TArray<FCsReceiveDamage> Local_Receivers;
	TArray<FCsResource_DamageEvent*> Local_Events;

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
	void ProcessDamageEventContainer(const FCsResource_DamageEvent* Event);

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

	TArray<FCsManager_DamageValue> Manager_Values;

	/**
	* Constructs an object that implements the interface: NCsDamage::NValue::IValue for the 
	* appropriate Type.
	*
	* @param Type
	* return
	*/
	virtual NCsDamage::NValue::IValue* ConstructValue(const FECsDamageValue& Type);

public:

	/**
	*
	*
	* @param Type
	* return
	*/
	FCsResource_DamageValue* AllocateValue(const FECsDamageValue& Type);

	/**
	*
	*
	* @param Type
	* @param Value
	*/
	virtual void DeallocateValue(const FString& Context, const FECsDamageValue& Type, FCsResource_DamageValue* Value);

protected:

	/**
	*
	*
	* @param Context
	* @param Value
	*/
	virtual void DeallocateValue(const FString& Context, FCsResource_DamageValue* Value);

public:

	/**
	*
	*
	* @param Context	The calling context.
	* @param Value
	* return
	*/
	virtual const FECsDamageValue& GetValueType(const FString& Context, const NCsDamage::NValue::IValue* Value);

	/**
	*
	*
	* @param Context	The calling context.
	* @param Value
	* return
	*/
	virtual FCsResource_DamageValue* CreateCopyOfValue(const FString& Context, const NCsDamage::NValue::IValue* Value);

	/**
	*
	*
	* @param Context	The calling context.
	* @param Value
	* return
	*/
	virtual FCsResource_DamageValue* CreateCopyOfValue(const FString& Context, const FCsResource_DamageValue* Value);

protected:

	//void LogValue(const NCsDamage::NValue::IValue* Value);

#pragma endregion Value

// Range
#pragma region
protected:

	FCsManager_DamageRange Manager_Range;

	virtual NCsDamage::NRange::IRange* ConstructRange();

public:

	FCsResource_DamageRange* AllocateRange();

	void DeallocateRange(const FString& Context, FCsResource_DamageRange* Range);

	FCsResource_DamageRange* CreateCopyOfRange(const FString& Context, const NCsDamage::NRange::IRange* Range);

	FCsResource_DamageRange* CreateCopyOfRange(const FString& Context, const FCsResource_DamageRange* Range);

	/**
	*
	*
	* @param Context	The calling context.
	* @param Data
	* return
	*/
	virtual const NCsDamage::NRange::IRange* GetRange(const FString& Context, const ICsData_Damage* Data);

#pragma endregion Range

// Modifier
#pragma region
protected:

	virtual NCsDamage::NModifier::IModifier* ConstructModifier();

public:

	FCsResource_DamageModifier* AllocateModifier();

	void DeallocateModifier(const FString& Context, FCsResource_DamageModifier* Modifier);

	FCsResource_DamageModifier* CreateCopyOfModifier(const FString& Context, const NCsDamage::NModifier::IModifier* Modifier);

	FCsResource_DamageModifier* CreateCopyOfModifier(const FString& Context, const FCsResource_DamageModifier* Modifier);

	virtual void ModifyValue(const FString& Context, const NCsDamage::NModifier::IModifier* Modifier, const ICsData_Damage* Data, NCsDamage::NValue::IValue* Value);

	virtual void ModifyRange(const FString& Context, const NCsDamage::NModifier::IModifier* Modifier, const ICsData_Damage* Data, NCsDamage::NRange::IRange* Range);

#pragma endregion Modifier

// Log
#pragma region
public:

	void LogEvent(const EventType* Event);

#pragma endregion Log

#undef EventType
};
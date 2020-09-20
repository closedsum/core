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

	// DamageEvent

/**
* Container for holding a reference to an object that implements the interface: ICsDamageEvent.
* This serves as an easy way for a Manager Resource to keep track of the resource.
*/
struct CSCORE_API FCsResource_DamageEvent : public TCsResourceContainer<ICsDamageEvent>
{
};

/**
* A manager handling allocating and deallocating objects that implement the interface: ICsDamageEvent and
* are wrapped in the container: FCsResource_DamageEvent.
*/
struct CSCORE_API FCsManager_DamageEvent : public TCsManager_ResourceValueType_Abstract_Fixed<ICsDamageEvent, FCsResource_DamageEvent, 0>
{
};
	
	// DamageValue

/**
* Container for holding a reference to an object that implements the interface: ICsDamageValue.
* This serves as an easy way for a Manager Resource to keep track of the resource.
*/
struct CSCORE_API FCsResource_DamageValue : public TCsResourceContainer<ICsDamageValue>
{
};

/**
* A manager handling allocating and deallocating objects that implement the interface: ICsDamageValue and
* are wrapped in the container: FCsResource_DamageValue.
*/
struct CSCORE_API FCsManager_DamageValue : public TCsManager_ResourcePointerType_Fixed<ICsDamageValue, FCsResource_DamageValue, 0>
{
};

	// DamageRange

/**
* Container for holding a reference to an object that implements the interface: ICsDamageRange.
* This serves as an easy way for a Manager Resource to keep track of the resource.
*/
struct CSCORE_API FCsResource_DamageRange : public TCsResourceContainer<ICsDamageRange>
{
};

/**
* A manager handling allocating and deallocating objects that implement the interface: ICsDamageRange and
* are wrapped in the container: FCsResource_DamageRange.
*/
struct CSCORE_API FCsManager_DamageRange : public TCsManager_ResourceValueType_Abstract_Fixed<ICsDamageRange, FCsResource_DamageRange, 0>
{
};

	// DamageModifier

/**
* Container for holding a reference to an object that implements the interface: ICsDamageModifier.
* This serves as an easy way for a Manager Resource to keep track of the resource.
*/
struct CSCORE_API FCsResource_DamageModifier : public TCsResourceContainer<ICsDamageModifier>
{

};

/**
* A manager handling allocating and deallocating objects that implement the interface: ICsDamageModifier and
* are wrapped in the container: FCsResource_DamageModifier.
*/
struct CSCORE_API FCsManager_DamageModifier : public TCsManager_ResourceValueType_Abstract_Fixed<ICsDamageModifier, FCsResource_DamageModifier, 0>
{
};

#pragma endregion Structs

class ICsGetManagerDamage;
class ICsData_Damage;

UCLASS()
class CSCORE_API UCsManager_Damage : public UObject
{
	GENERATED_UCLASS_BODY()

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

	virtual ICsDamageEvent* ConstructEvent();

public:

	/**
	*
	*
	* return
	*/
	FCsResource_DamageEvent* AllocateEvent();

	virtual void DeallocateEvent(const FString& Context, FCsResource_DamageEvent* Event);

	virtual bool CopyEvent(const FString& Context, const ICsDamageEvent* From, ICsDamageEvent* To);

	FCsResource_DamageEvent* CreateCopyOfEvent(const FString& Context, const ICsDamageEvent* Event);

	FCsResource_DamageEvent* CreateCopyOfEvent(const FString& Context, const FCsResource_DamageEvent* Event);

private:

	TArray<FCsReceiveDamage> Local_Receivers;
	TArray<FCsResource_DamageEvent*> Local_Events;

public:

	/**
	*
	*
	* @param Event
	*/
	void ProcessDamageEvent(const ICsDamageEvent* Event);

	/**
	*
	*
	* @param Event
	*/
	void ProcessDamageEventContainer(const FCsResource_DamageEvent* Event);

	/**
	*
	*
	* @param Event
	*/
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnProcessDamageEvent, const ICsDamageEvent* /*Event*/);

	/** */
	FOnProcessDamageEvent OnProcessDamageEvent_Event;

#pragma endregion Event

// Value
#pragma region
protected:

	TArray<FCsManager_DamageValue> Manager_Values;

	/**
	* Constructs an object that implements the interface: ICsDamageValue for the 
	* appropriate Type.
	*
	* @param Type
	* return
	*/
	virtual ICsDamageValue* ConstructValue(const FECsDamageValue& Type);

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
	virtual const FECsDamageValue& GetValueType(const FString& Context, const ICsDamageValue* Value);

	/**
	*
	*
	* @param Context	The calling context.
	* @param Value
	* return
	*/
	virtual FCsResource_DamageValue* CreateCopyOfValue(const FString& Context, const ICsDamageValue* Value);

	/**
	*
	*
	* @param Context	The calling context.
	* @param Value
	* return
	*/
	virtual FCsResource_DamageValue* CreateCopyOfValue(const FString& Context, const FCsResource_DamageValue* Value);

protected:

	//void LogValue(const ICsDamageValue* Value);

#pragma endregion Value

// Range
#pragma region
protected:

	FCsManager_DamageRange Manager_Range;

	virtual ICsDamageRange* ConstructRange();

public:

	FCsResource_DamageRange* AllocateRange();

	void DeallocateRange(const FString& Context, FCsResource_DamageRange* Range);

	FCsResource_DamageRange* CreateCopyOfRange(const FString& Context, const ICsDamageRange* Range);

	FCsResource_DamageRange* CreateCopyOfRange(const FString& Context, const FCsResource_DamageRange* Range);

	/**
	*
	*
	* @param Context	The calling context.
	* @param Data
	* return
	*/
	virtual const ICsDamageRange* GetRange(const FString& Context, const ICsData_Damage* Data);

#pragma endregion Range

// Modifier
#pragma region
protected:

	virtual ICsDamageModifier* ConstructModifier();

public:

	FCsResource_DamageModifier* AllocateModifier();

	void DeallocateModifier(const FString& Context, FCsResource_DamageModifier* Modifier);

	FCsResource_DamageModifier* CreateCopyOfModifier(const FString& Context, const ICsDamageModifier* Modifier);

	FCsResource_DamageModifier* CreateCopyOfModifier(const FString& Context, const FCsResource_DamageModifier* Modifier);

	virtual void ModifyValue(const FString& Context, const ICsDamageModifier* Modifier, const ICsData_Damage* Data, ICsDamageValue* Value);

	virtual void ModifyRange(const FString& Context, const ICsDamageModifier* Modifier, const ICsData_Damage* Data, ICsDamageRange* Range);

#pragma endregion Modifier

// Log
#pragma region
public:

	void LogEvent(const ICsDamageEvent* Event);

#pragma endregion Log
};
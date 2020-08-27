// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Event/CsStatusEffectEvent.h"
#include "Event/Damage/CsStatusEffectEvent_Damage.h"
#include "Reset/CsReset.h"
#include "Containers/CsInterfaceMap.h"
// Types
#include "Managers/Damage/Event/CsAllocated_DamageEvent.h"
#pragma once

class UObject;
struct FCsInterfaceMap;
class ICsData_StatusEffect;
struct ICsDamageEvent;

struct CSSE_API FCsStatusEffectEvent_DamageImpl final : public ICsStatusEffectEvent,
													    public ICsStatusEffectEvent_Damage,
														public ICsReset
{
public:

	static const FName Name;

private:

	// ICsGetInterfaceMap

	FCsInterfaceMap InterfaceMap;

public:

	// ICsStatusEffectEvent

	ICsData_StatusEffect* Data;

	TWeakObjectPtr<UObject> Instigator;

	TWeakObjectPtr<UObject> Causer;

	TWeakObjectPtr<UObject> Receiver;

	TArray<TWeakObjectPtr<UObject>> IgnoreObjects;

	// ICsStatusEffectEvent_Damage

	FCsAllocated_DamageEvent DamageEvent;

public:

	FCsStatusEffectEvent_DamageImpl();

// ICsGetInterfaceMap
#pragma region
public:

	FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
	{
		return const_cast<FCsInterfaceMap*>(&InterfaceMap);
	}

#pragma endregion ICsGetInterfaceMap

// ICsStatusEffectEvent
#pragma region
public:

	FORCEINLINE ICsData_StatusEffect* GetData() const
	{
		return Data;
	}

	FORCEINLINE UObject* GetInstigator() const
	{
		return Instigator.IsValid() ? Instigator.Get() : nullptr;
	}

	FORCEINLINE UObject* GetCauser() const
	{
		return Causer.IsValid() ? Causer.Get() : nullptr;
	}

	FORCEINLINE UObject* GetReceiver() const
	{
		return Receiver.IsValid() ? Receiver.Get() : nullptr;
	}

	FORCEINLINE const TArray<TWeakObjectPtr<UObject>>& GetIgnoreObjects() const
	{
		return IgnoreObjects;
	}

#pragma endregion ICsStatusEffectEvent

// ICsStatusEffectEvent_Damage
#pragma region
public:

	FORCEINLINE ICsDamageEvent* GetDamageEvent() const
	{
		return DamageEvent.Event;
	}

#pragma endregion ICsStatusEffectEvent_Damage

public:

	template<typename T>
	FORCEINLINE T* GetInstigator() const
	{
		return Cast<T>(GetInstigator());
	}

	template<typename T>
	FORCEINLINE T* GetCauser() const
	{
		return Cast<T>(GetCauser());
	}

	/**
	* Copy all elements from another Event 
	*  EXCEPT:
	*   InterfaceMap: This needs to be unique per instance.
	*
	* @param From	Event to copy from.
	*/
	void CopyFrom(const FCsStatusEffectEvent_DamageImpl* From);

// ICsReset
#pragma region
public:

	void Reset();

#pragma endregion ICsReset
};
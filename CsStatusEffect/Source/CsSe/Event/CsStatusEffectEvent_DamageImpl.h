// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Event/CsStatusEffectEvent.h"
#include "Event/CsStatusEffectEvent_Damage.h"
#include "Containers/CsInterfaceMap.h"
#pragma once

class UObject;
struct FCsInterfaceMap;
class ICsStatusEffect;
struct ICsDamageEvent;
struct FCsResource_DamageEvent;

struct CSSE_API FCsStatusEffectEvent_DamageImpl final : public ICsStatusEffectEvent,
													    public ICsStatusEffectEvent_Damage
{
public:

	static const FName Name;

private:

	// ICsGetInterfaceMap

	FCsInterfaceMap InterfaceMap;

public:

	// ICsStatusEffectEvent

	ICsStatusEffect* StatusEffect;

	TWeakObjectPtr<UObject> Instigator;

	TWeakObjectPtr<UObject> Causer;

	TWeakObjectPtr<UObject> Receiver;

	TArray<TWeakObjectPtr<UObject>> IgnoreObjects;

	// ICsStatusEffectEvent_Damage

	ICsDamageEvent* DamageEvent;

	FCsResource_DamageEvent* DamageEventContainer;

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

	FORCEINLINE ICsStatusEffect* GetStatusEffect() const
	{
		return StatusEffect;
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
		return DamageEvent;
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

	void Reset();
};
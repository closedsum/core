// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Event/CsStatusEffectEvent.h"
#include "Containers/CsInterfaceMap.h"
#pragma once

class UObject;
struct FCsInterfaceMap;
class ICsStatusEffect;

struct CSSE_API FCsStatusEffectEventImpl final : public ICsStatusEffectEvent
{
public:

	static const FName Name;

private:

	FCsInterfaceMap InterfaceMap;

public:

	// ICsDamageEvent

	ICsStatusEffect* StatusEffect;

	UObject* Instigator;

	UObject* Causer;

public:

	FCsStatusEffectEventImpl();

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
		return Instigator;
	}

	FORCEINLINE UObject* GetCauser() const
	{
		return Causer;
	}

#pragma endregion ICsStatusEffectEvent

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
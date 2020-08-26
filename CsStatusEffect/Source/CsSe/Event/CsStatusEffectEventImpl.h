// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Event/CsStatusEffectEvent.h"
#include "Containers/CsInterfaceMap.h"
#pragma once

class UObject;
struct FCsInterfaceMap;
class ICsData_StatusEffect;

struct CSSE_API FCsStatusEffectEventImpl final : public ICsStatusEffectEvent
{
public:

	static const FName Name;

private:

	FCsInterfaceMap InterfaceMap;

public:

	// ICsStatusEffectEvent

	ICsData_StatusEffect* Data;

	TWeakObjectPtr<UObject> Instigator;

	TWeakObjectPtr<UObject> Causer;

	TWeakObjectPtr<UObject> Receiver;

	TArray<TWeakObjectPtr<UObject>> IgnoreObjects;

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
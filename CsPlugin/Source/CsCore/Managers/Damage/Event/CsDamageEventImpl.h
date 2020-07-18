// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Event/CsDamageEvent.h"
#include "Containers/CsInterfaceMap.h"
#pragma once

class UObject;
struct FCsInterfaceMap;
class ICsDamageExpression;

struct CSCORE_API FCsDamageEventImpl final : public ICsDamageEvent
{
public:

	static const FName Name;

private:

	FCsInterfaceMap InterfaceMap;

public:

	// ICsDamageEvent

	ICsDamageExpression* Expression;

	UObject* Instigator;

	UObject* Causer;

	FECsHitType HitType;

	FHitResult HitResult;

	TArray<UObject*> IgnoreObjects;

public:

	FCsDamageEventImpl();

// ICsGetInterfaceMap
#pragma region
public:

	FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
	{
		return const_cast<FCsInterfaceMap*>(&InterfaceMap);
	}

#pragma endregion ICsGetInterfaceMap

// ICsDamageEvent
#pragma region
public:

	FORCEINLINE ICsDamageExpression* GetExpression() const
	{
		return Expression;
	}

	FORCEINLINE UObject* GetInstigator() const
	{
		return Instigator;
	}

	FORCEINLINE UObject* GetCauser() const
	{
		return Causer;
	}

	FORCEINLINE const FECsHitType& GetHitType() const
	{
		return HitType;
	}

	FORCEINLINE const FHitResult& GetHitResult() const
	{
		return HitResult;
	}

	FORCEINLINE const TArray<UObject*>& GetIgnoreObjects() const
	{
		return IgnoreObjects;
	}

#pragma endregion ICsDamageEvent

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
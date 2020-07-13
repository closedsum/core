// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Event/CsDamageEvent.h"

#pragma once

class UObject;
struct FCsInterfaceMap;
struct ICsDamageExpression;

struct CSCORE_API FCsDamageEventImpl final : public ICsDamageEvent
{
public:

	static const FName Name;

private:

	FCsInterfaceMap* InterfaceMap;

public:

	// ICsDamageEvent

	ICsDamageExpression* Expression;

	UObject* Instigator;

	UObject* Causer;

	FECsHitType HitType;

	FHitResult HitResult;

public:

	FCsDamageEventImpl();
	~FCsDamageEventImpl();

// ICsGetInterfaceMap
#pragma region
public:

	FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
	{
		return InterfaceMap;
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
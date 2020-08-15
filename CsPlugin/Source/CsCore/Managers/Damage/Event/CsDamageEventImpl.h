// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

// Interfaces
#include "Managers/Damage/Event/CsDamageEvent.h"
// Container
#include "Containers/CsInterfaceMap.h"
// Types
#include "Managers/Damage/Value/CsTypes_DamageValue.h"
#pragma once

class UObject;
struct FCsInterfaceMap;
struct FCsResource_DamageValue;
struct ICsDamageValue;
class ICsDamageExpression;

/**
* Basic implementation of the interface: ICsDmaageEvent
*/
struct CSCORE_API FCsDamageEventImpl final : public ICsDamageEvent
{
public:

	static const FName Name;

private:

	FCsInterfaceMap InterfaceMap;

public:

	// ICsDamageEvent

	float Damage;

	FCsResource_DamageValue* DamageValueContainer;

	FECsDamageValue DamageValueType;

	ICsDamageValue* DamageValue;

	ICsDamageExpression* Expression;

	UObject* Instigator;

	UObject* Causer;

	FECsHitType HitType;

	FHitResult Origin;

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

	FORCEINLINE const float& GetDamage() const
	{
		return Damage;
	}

	FORCEINLINE const ICsDamageValue* GetDamageValue() const
	{
		return DamageValue;
	}

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

	FORCEINLINE const FHitResult& GetOrigin() const
	{
		return Origin;
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

	void CopyFrom(const FCsDamageEventImpl* From);

	void SetDamageChecked(const FString& Context);

	void Reset();
};
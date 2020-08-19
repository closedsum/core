// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

// Interfaces
#include "Managers/Damage/Event/CsDamageEvent.h"
#include "Reset/CsReset.h"
// Container
#include "Containers/CsInterfaceMap.h"
// Types
#include "Managers/Damage/Value/CsTypes_DamageValue.h"
#pragma once

class UObject;
struct FCsInterfaceMap;
struct FCsResource_DamageValue;
struct ICsDamageValue;
struct FCsResource_DamageRange;
struct ICsDamageRange;
class ICsDamageExpression;

/**
* Basic implementation of the interface: ICsDmaageEvent
*/
struct CSCORE_API FCsDamageEventImpl final : public ICsDamageEvent,
											 public ICsReset
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

	FCsResource_DamageRange* DamageRangeContainer;

	ICsDamageRange* DamageRange;

	ICsDamageExpression* Expression;

	UObject* Instigator;

	UObject* Causer;

	FECsHitType HitType;

	FHitResult Origin;

	FHitResult HitResult;

	TArray<UObject*> IgnoreObjects;

public:

	FCsDamageEventImpl();

	FORCEINLINE UObject* _getUObject() const { return nullptr; }

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

	FORCEINLINE const ICsDamageRange* GetDamageRange() const
	{
		return DamageRange;
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

	/**
	* Copy all elements from another Event 
	*  EXCEPT:
	*   InterfaceMap: This needs to be unique per instance.
	*   DamageValueContainer: This pointer should be unique per instance.
	*   DamageValue: This pointer should be unique per instance.
	*   DamageRangeContainer: This pointer should be unique per instance.
	*   DamageRange: This pointer should be unique per instance.
	*
	* @param From	Event to copy from.
	*/
	void CopyFrom(const FCsDamageEventImpl* From);

	/**
	*
	*
	* @param Context	The calling context.
	* return			Whether the damage was successfully set.
	*/
	bool SetDamageChecked(const FString& Context);

// ICsReset
#pragma region

	void Reset();

#pragma endregion ICsReset
};
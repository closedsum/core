// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Result/CsDamageResult.h"

#pragma once

class UObject;
struct FCsInterfaceMap;

struct CSCORE_API FCsDamageResultImpl final : public ICsDamageResult
{
public:

	static const FName Name;

private:

	FCsInterfaceMap* InterfaceMap;

public:

	// ICsDamageEvent

	float Damage;

	UObject* Instigator;

	UObject* Causer;

	UObject* Victim;
	
	FECsDamageType DamageType;

	FECsHitType HitType;

	bool bImpulse;

	FHitResult HitResult;

public:

	FCsDamageResultImpl();
	~FCsDamageResultImpl();

// ICsGetInterfaceMap
#pragma region
public:

	FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
	{
		return InterfaceMap;
	}

#pragma endregion ICsGetInterfaceMap

// ICsDamageResult
#pragma region
public:

	FORCEINLINE const float& GetDamage() const
	{
		return Damage;
	}

	FORCEINLINE UObject* GetInstigator() const
	{
		return Instigator;
	}

	FORCEINLINE UObject* GetCauser() const
	{
		return Causer;
	}

	FORCEINLINE UObject* GetVictim() const
	{
		return Victim;
	}

	FORCEINLINE const FECsDamageType& GetDamageType() const
	{
		return DamageType;
	}

	FORCEINLINE const FECsHitType& GetHitType() const
	{
		return HitType;
	}

	FORCEINLINE const bool& HasImpulse() const
	{
		return bImpulse;
	}

	FORCEINLINE const FHitResult& GetHitResult() const
	{
		return HitResult;
	}

#pragma endregion ICsDamageResult

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

	template<typename T>
	FORCEINLINE T* GetVictim() const
	{
		return Cast<T>(GetVictim());
	}

	void Reset();
};
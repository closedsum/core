// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"
#include "Payload/CsPayload_Projectile.h"

#pragma once

class UObject;
struct FCsInterfaceMap;

/**
* Basic implementation of the interface: ICsPayload_PooledObject and ICsPayload_Projectile.
*/
struct CSPRJ_API FCsPayload_ProjectilePooledImpl : public ICsPayload_PooledObject,
												   public ICsPayload_Projectile
{
public:

	static const FName Name;

private:

	// ICsGetInterfaceMap

	FCsInterfaceMap* InterfaceMap;

	// ICsPayload_PooledObject

	bool bAllocated;

public:

	UObject* Instigator;

	UObject* Owner;

	UObject* Parent;
	
	FCsTime Time;

	// ICsPayload_Projectile

	FVector Direction;

	FVector Location;

public:

	FCsPayload_ProjectilePooledImpl();
	~FCsPayload_ProjectilePooledImpl();

// ICsGetInterfaceMap
#pragma region
public:

	FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
	{
		return InterfaceMap;
	}

#pragma endregion ICsGetInterfaceMap

// ICsPayload_PooledObject
#pragma region
public:

	FORCEINLINE const bool& IsAllocated() const
	{
		return bAllocated;
	}

	FORCEINLINE UObject* GetInstigator() const
	{
		return Instigator;
	}

	FORCEINLINE UObject* GetOwner() const
	{
		return Owner;
	}

	FORCEINLINE UObject* GetParent() const
	{
		return Parent;
	}

	FORCEINLINE const FCsTime& GetTime() const
	{
		return Time;
	}

	FORCEINLINE void Allocate()
	{
		bAllocated = true;
	}

	void Reset();

#pragma endregion ICsPayload_PooledObject

public:

	template<typename T>
	FORCEINLINE T* GetInstigator() const
	{
		return Cast<T>(GetInstigator());
	}

	template<typename T>
	FORCEINLINE T* GetOwner() const
	{
		return Cast<T>(GetOwner());
	}

	template<typename T>
	FORCEINLINE T* GetParent() const
	{
		return Cast<T>(GetParent());
	}

// ICsPayload_Projectile
#pragma region
public:

	FORCEINLINE const FVector& GetDirection() const
	{
		return Direction;
	}

	FORCEINLINE const FVector& GetLocation() const
	{
		return Location;
	}

#pragma endregion ICsPayload_Projectile
};
// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Payload/CsPayload_Projectile.h"
#include "Reset/CsReset.h"

#pragma once

class UObject;
struct FCsInterfaceMap;

/**
* Basic implementation of the interface: ICsPayload_PooledObject and ICsPayload_Projectile.
*/
struct CSPRJ_API FCsPayload_ProjectileImplSlice : public ICsPayload_Projectile,
												  public ICsReset
{
public:

	static const FName Name;

private:

	// ICsGetInterfaceMap

	FCsInterfaceMap* InterfaceMap;

public:

	// ICsPayload_Projectile

	FVector Direction;

	FVector Location;

public:

	FCsPayload_ProjectileImplSlice();

// ICsGetInterfaceMap
#pragma region
public:

	FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
	{
		return InterfaceMap;
	}

#pragma endregion ICsGetInterfaceMap

public:

	void SetInterfaceMap(FCsInterfaceMap* InInterfaceMap);

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

// ICsReset
#pragma region
public:

	void Reset();

#pragma endregion ICsReset

public:

	bool CopyFrom(const FCsPayload_ProjectileImplSlice* From);
};
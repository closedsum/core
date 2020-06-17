// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Data/CsData_Projectile.h"

struct FCsInterfaceMap;

struct CSPRJ_API FCsData_ProjectileImpl : public ICsData_Projectile
{
private:

	FCsInterfaceMap* InterfaceMap;

	float* InitialSpeed;

	float* MaxSpeed;

	float* GravityScale;

public:

	FCsData_ProjectileImpl();
	~FCsData_ProjectileImpl();

	FORCEINLINE void SetInitialSpeed(float* Value)
	{
		InitialSpeed = Value;
	}

	FORCEINLINE void SetMaxSpeed(float* Value)
	{
		MaxSpeed = Value;
	}

	FORCEINLINE void SetGravityScale(float* Value)
	{
		GravityScale = Value;
	}

	FORCEINLINE UObject* _getUObject() const { return nullptr; }

// ICsGetInterfaceMap
#pragma region
public:

	FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
	{
		return InterfaceMap;
	}

#pragma endregion ICsGetInterfaceMap

// ICsData_Projectile
#pragma region
public:

	FORCEINLINE const float& GetInitialSpeed() const
	{
		return *InitialSpeed;
	}

	FORCEINLINE const float& GetMaxSpeed() const
	{
		return *MaxSpeed;
	}

	FORCEINLINE const float& GetGravityScale() const
	{
		return *GravityScale;
	}

#pragma endregion ICsData_Projectile
};
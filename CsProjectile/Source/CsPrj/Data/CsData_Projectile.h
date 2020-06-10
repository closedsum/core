// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "Containers/CsInterfaceMap.h"
#include "Types/Property/Ref/CsProperty_Ref_float.h"
#include "CsData_Projectile.generated.h"

UINTERFACE(BlueprintType)
class CSPRJ_API UCsData_Projectile : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

class CSPRJ_API ICsData_Projectile : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	/**
	*
	*
	* return
	*/
	virtual const float& GetInitialSpeed() const = 0;

	/**
	*
	*
	* return
	*/
	virtual const float& GetMaxSpeed() const = 0;

	/**
	* 
	*
	* return
	*/
	virtual const float& GetGravityScale() const = 0;
};

struct CSPRJ_API FCsData_ProjectileImpl : public ICsData_Projectile
{
private:

	FCsInterfaceMap* InterfaceMap;

	float* InitialSpeed;

	float* MaxSpeed;

	float* GravityScale;

public:

	FCsData_ProjectileImpl() :
		InterfaceMap(nullptr),
		InitialSpeed(nullptr),
		MaxSpeed(nullptr),
		GravityScale(nullptr)
	{
	}

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
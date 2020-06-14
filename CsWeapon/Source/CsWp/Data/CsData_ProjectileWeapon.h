// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "Containers/CsGetInterfaceMap.h"
#include "CsData_ProjectileWeapon.generated.h"

UINTERFACE(BlueprintType)
class CSWP_API UCsData_ProjectileWeapon : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

class CSWP_API ICsData_ProjectileWeapon : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

	/**
	*
	*
	* return
	*/
	virtual const bool& DoFireOnRelease() const = 0;

	/**
	*
	*
	* return
	*/
	virtual const bool& IsFullAuto() const = 0;

	/**
	*
	*
	* return
	*/
	virtual const int32& GetMaxAmmo() const = 0;

	/**
	*
	*
	* return
	*/
	virtual const float& GetProjectilesPerShot() const = 0;

	/**
	*
	*
	* return
	*/
	virtual const float& GetTimeBetweenShots() const = 0;

	/**
	*
	*
	* return
	*/
	virtual const float& GetTimeBetweenAutoShots() const = 0;
};
// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "CsProjectile.generated.h"

UINTERFACE(Blueprintable)
class UCsProjectile : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

//class ICsData_Projectile;

class ICsProjectile
{
	GENERATED_IINTERFACE_BODY()

public:
	
	/**
	*
	*
	* return Data that implements the interface: ICsData_Projectile.
	*/
	//virtual ICsData_Projectile* GetData()  = 0;

	/**
	*
	*
	* return Owner of the projectile.
	*/
	virtual UObject* GetOwner() = 0;

	/**
	*
	*
	* return Instigator of the projectile.
	*/
	virtual UObject* GetInstigator() = 0;
};
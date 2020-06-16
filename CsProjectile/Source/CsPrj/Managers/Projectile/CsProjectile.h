// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "CsProjectile.generated.h"

UINTERFACE(Blueprintable)
class CSPRJ_API UCsProjectile : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class ICsData_Projectile;

class CSPRJ_API ICsProjectile
{
	GENERATED_IINTERFACE_BODY()

public:
	
	/**
	* The Data the projectile is currently using.
	*
	* return Data that implements the interface: ICsData_Projectile.
	*/
	virtual ICsData_Projectile* GetData() const = 0;

	/**
	* The object that "owns" the projectile.
	*
	* return Owner of the projectile.
	*/
	virtual UObject* GetOwner() const = 0;

	/**
	* The object that started the process of launching / activating the projectile.
	*
	* return Instigator of the projectile.
	*/
	virtual UObject* GetInstigator() const = 0;
};
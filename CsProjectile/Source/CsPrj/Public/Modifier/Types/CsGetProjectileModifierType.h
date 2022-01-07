// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Modifier/Types/CsTypes_ProjectileModifier.h"

/**
* Interface to get the Projectile Modifier "type".
* This is used to provide an easier way to access what the "type" is
* for a Projectile Modifier.
*  Projectile Modifier implements the interface: NCsProjectile::NModifier::IModifier.
*/
struct CSPRJ_API ICsGetProjectileModifierType : public ICsGetInterfaceMap
{
public:

	static const FName Name;

public:

	virtual ~ICsGetProjectileModifierType() {}

	/**
	* Get the type of the Projectile Modifier.
	* 
	* return Type.
	*/
	virtual const FECsProjectileModifier& GetProjectileModifierType() const = 0;
};
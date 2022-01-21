// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Modifier/Types/CsTypes_WeaponModifier.h"

/**
* Interface to get the Weapon Modifier "type".
* This is used to provide an easier way to access what the "type" is
* for a Weapon Modifier.
*  Weapon Modifier implements the interface: NCsWeapon::NModifier::IModifier.
*/
struct CSWP_API ICsGetWeaponModifierType : public ICsGetInterfaceMap
{
public:

	static const FName Name;

public:

	virtual ~ICsGetWeaponModifierType() {}

	/**
	* Get the type of the Weapon Modifier.
	*
	* return Type.
	*/
	virtual const FECsWeaponModifier& GetWeaponModifierType() const = 0;
};
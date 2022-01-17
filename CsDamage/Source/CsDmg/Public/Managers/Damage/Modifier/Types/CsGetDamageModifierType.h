// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Managers/Damage/Modifier/Types/CsTypes_DamageModifier.h"

/**
* Interface to get the Damage Modifier "type".
* This is used to provide an easier way to access what the "type" is
* for a Damage Modifier.
*  Damage Modifier implements the interface: NCsDamage::NModifier::IModifier.
*/
struct CSDMG_API ICsGetDamageModifierType : public ICsGetInterfaceMap
{
public:

	static const FName Name;

public:

	virtual ~ICsGetDamageModifierType() {}

	/**
	* Get the type of the Damage Modifier.
	* 
	* return Type.
	*/
	virtual const FECsDamageModifier& GetDamageModifierType() const = 0;
};
// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Modifier/Types/CsTypes_DamageModifier.h"

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
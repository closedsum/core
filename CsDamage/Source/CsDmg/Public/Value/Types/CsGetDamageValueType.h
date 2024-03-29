// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Value/Types/CsTypes_DamageValue.h"

/**
* Interface to describe which Damage Value implementation type.
* This is used to provide an easier way to access what the "type" is
* for a Damage Value implementation.
*/
class CSDMG_API ICsGetDamageValueType : public ICsGetInterfaceMap
{
public:

	static const FName Name;

public:

	virtual ~ICsGetDamageValueType(){}

	/**
	* Get the type of Damage Value.
	*
	* return Type.
	*/
	virtual const FECsDamageValue& GetDamageValueType() const = 0;
};
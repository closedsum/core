// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"
#include "Managers/Damage/CsTypes_Damage.h"
#include "Engine/EngineTypes.h"
#pragma once

/**
* Interface to describe Damage. Other interfaces can be "added" on top of this to 
* expose more functionality (i.e. ICsDamageShape, ... etc)
*/
struct CSCORE_API ICsDamageExpression : virtual public ICsGetInterfaceMap
{
public:

	static const FName Name;

public:

	virtual ~ICsDamageExpression() {}

	/**
	* Get the amount of damage.
	* 
	* return Damage.
	*/
	virtual float GetDamage() const = 0;

	/**
	* Get the type of damage.
	*
	* return Damage Type.
	*/
	virtual const FECsDamageType& GetType() const = 0;
};
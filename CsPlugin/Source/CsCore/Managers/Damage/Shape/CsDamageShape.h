// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"
#include "Engine/EngineTypes.h"
#pragma once

/**
* Interface to describe he shape of Damage. This should be used with 
* the interface "base" ICsDamageExpression.
*/
struct CSCORE_API ICsDamageShape : virtual public ICsGetInterfaceMap
{
public:

	static const FName Name;

public:

	virtual ~ICsDamageShape() {}

	/**
	* Get the minimum damage.
	*
	* return Minimum Damage.
	*/
	virtual const float& GetMinDamage() const = 0;

	/**
	* Get the maximum damage.
	*
	* return Maximum Damage.
	*/
	virtual const float& GetMaxDamage() const = 0;

	/**
	* Calculate damage given an origin and point.
	*
	* @param Origin		The center of the damage event.
	* @param Point		The location to evaluate for how much damage
	*
	*/
	virtual float CalculateDamage(const FVector& Origin, const FVector& Point) const = 0;
};
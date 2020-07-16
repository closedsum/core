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
	* Calculate damage given an origin and point.
	*
	* @param Origin		The center of the damage event.
	* @param Point		The location to evaluate for how much damage
	* return			Damage
	*
	*/
	virtual float CalculateDamage(const FVector& Origin, const FVector& Point) const = 0;

	/**
	* Check if a given Point is within the bounds of an Origin.
	*
	* @param Origin		The center of the bounds.
	* @param Point		The location to evaluate if in bounds.
	* return			Whether the point is in bounds of the origin.
	*/
	virtual bool IsInBounds(const FVector& Origin, const FVector& Point) const = 0;
};
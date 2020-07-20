// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"
#include "Engine/EngineTypes.h"
#include "CsDamageShape.generated.h"
#pragma once

UINTERFACE(BlueprintType)
class CSCORE_API UCsDamageShape : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
* Interface to describe the shape of Damage. This should be used with 
* the interface "base" ICsDamageExpression.
*/
class CSCORE_API ICsDamageShape : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:

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
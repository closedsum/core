// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"
#include "Engine/EngineTypes.h"
#include "CsData_DamageShape.generated.h"
#pragma once

UINTERFACE(BlueprintType)
class CSCORE_API UCsData_DamageShape : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

struct ICsDamageValue;
struct ICsDamageRange;

/**
* Interface to describe the shape of Damage. This should be used with 
* the interface "base" ICsData_Damage.
*/
class CSCORE_API ICsData_DamageShape : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:

	/**
	*
	*
	* return
	*/
	virtual const ICsDamageRange* GetRange() const = 0;

	/**
	* Calculate damage given an origin and point.
	*
	* @param Value		
	* @param Range
	* @param Origin		The center of the damage event.
	* @param Point		The location to evaluate for how much damage
	* return			Damage
	*
	*/
	virtual float CalculateDamage(const ICsDamageValue* Value, const ICsDamageRange* Range, const FVector& Origin, const FVector& Point) const = 0;

	/**
	* Check if a given Point is within the bounds of an Origin.
	*
	* @param Origin		The center of the bounds.
	* @param Point		The location to evaluate if in bounds.
	* return			Whether the point is in bounds of the origin.
	*/
	virtual bool IsInBounds(const FVector& Origin, const FVector& Point) const = 0;
};
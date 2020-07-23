// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"
#include "Engine/EngineTypes.h"
#include "CsStatusEffect_Shape.generated.h"
#pragma once

UINTERFACE(BlueprintType)
class CSSE_API UCsStatusEffect_Shape : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
* Interface to describe the shape of a Status Effect. This should be used with 
* the interface "base" ICsStatusEffect.
*/
class CSSE_API ICsStatusEffect_Shape : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:

	/**
	* Check if a given Point is within the bounds of an Origin.
	*
	* @param Origin		The center of the bounds.
	* @param Point		The location to evaluate if in bounds.
	* return			Whether the point is in bounds of the origin.
	*/
	virtual bool IsInBounds(const FVector& Origin, const FVector& Point) const = 0;
};
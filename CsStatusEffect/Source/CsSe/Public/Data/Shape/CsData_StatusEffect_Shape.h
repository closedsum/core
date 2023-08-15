// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"

#include "CsData_StatusEffect_Shape.generated.h"

namespace NCsStatusEffect
{
	namespace NData
	{
		namespace NShape
		{
			/**
			* Interface to describe the shape of a Status Effect. This should be used with
			* the interface "base" IData.
			*/
			struct IShape : public ICsGetInterfaceMap
			{
			public:

				static const FName Name;

			public:

				virtual ~IShape(){}

				/**
				* Check if a given Point is within the bounds of an Origin.
				*
				* @param Origin		The center of the bounds.
				* @param Point		The location to evaluate if in bounds.
				* return			Whether the point is in bounds of the origin.
				*/
				virtual bool IsInBounds(const FVector3f& Origin, const FVector3f& Point) const = 0;
			};
		}
	}
}

UINTERFACE(BlueprintType)
class CSSE_API UCsData_StatusEffect_Shape : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
* Interface to describe the shape of a Status Effect. This should be used with 
* the interface "base" ICsData_StatusEffect.
*/
class CSSE_API ICsData_StatusEffect_Shape : public ICsGetInterfaceMap
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
	virtual bool IsInBounds(const FVector3f& Origin, const FVector3f& Point) const = 0;
};
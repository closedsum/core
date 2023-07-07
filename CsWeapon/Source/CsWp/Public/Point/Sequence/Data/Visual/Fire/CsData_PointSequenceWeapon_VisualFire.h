// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Point/Sequence/Data/Visual/Fire/CsParams_PointSequenceWeapon_VisualFire.h"

#include "CsData_PointSequenceWeapon_VisualFire.generated.h"

namespace NCsWeapon
{
	namespace NPoint
	{
		namespace NSequence
		{
			namespace NData
			{
				namespace NVisual
				{
					namespace NFire
					{
						/**
						* Interface that describes any visual information associated to the Fire() call 
						* from a Point Sequence Weapon.
						*  Weapon is an object that implements the interface: ICsWeapon.
						*  Point Sequence Weapon is an object that implements the interface: ICsPointSequenceWeapon.
						*/
						struct CSWP_API IFire : public ICsGetInterfaceMap
						{
						public:

							static const FName Name;

						public:

							virtual ~IFire(){}

						#define FireVisualParamsType NCsWeapon::NPoint::NSequence::NFire::NVisual::FParams

							/**
							* Get whether to use the Fire Visual Params or not.
							* 
							* return
							*/
							virtual const bool& UseFireVisualParams() const = 0;

							/**
							* Get any Visual information related to the Fire action.
							*
							* return Fire Visual Params
							*/
							virtual const FireVisualParamsType& GetFireVisualParams() const = 0;

						#undef FireVisualParamsType
						};
					}
				}
			}
		}
	}
}

UINTERFACE(BlueprintType)
class CSWP_API UCsData_PointSequenceWeapon_VisualFire : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
* Interface that describes any visual information associated to the Fire() call
* from a Point Sequence Weapon.
*  Weapon is an object that implements the interface: ICsWeapon.
*  Point Sequence Weapon is an object that implements the interface: ICsPointSequenceWeapon.
*/
class CSWP_API ICsData_PointSequenceWeapon_VisualFire : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:

#define FireVisualParamsType NCsWeapon::NPoint::NSequence::NFire::NVisual::FParams

	/**
	* Get whether to use the Fire Visual Params or not.
	* 
	* return
	*/
	virtual const bool& UseFireVisualParams() const = 0;

	/**
	* Get any Visual information related to the Fire action.
	*
	* return Fire Visual Params
	*/
	virtual const FireVisualParamsType& GetFireVisualParams() const = 0;

#undef FireVisualParamsType
};
// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
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

						private:

							// Allow clearer names without name collisions
							struct _
							{
								using FireVisualParamsType = NCsWeapon::NPoint::NSequence::NFire::NVisual::FParams;
							};

						public:

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
							virtual const _::FireVisualParamsType& GetFireVisualParams() const = 0;
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

private:

	// Allow clearer names without name collisions
	struct _
	{
		using FireVisualParamsType = NCsWeapon::NPoint::NSequence::NFire::NVisual::FParams;
	};

public:

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
	virtual const _::FireVisualParamsType& GetFireVisualParams() const = 0;
};
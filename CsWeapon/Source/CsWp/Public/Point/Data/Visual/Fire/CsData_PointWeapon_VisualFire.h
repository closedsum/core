// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Interface.h"
// Interfaces
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Point/Data/Visual/Fire/CsParams_PointWeapon_VisualFire.h"

#include "CsData_PointWeapon_VisualFire.generated.h"

namespace NCsWeapon
{
	namespace NPoint
	{
		namespace NData
		{
			namespace NVisual
			{
				namespace NFire
				{
					/**
					* Interface that describes any visual information associated to the Fire() call 
					* from a Point Weapon.
					*  Weapon is an object that implements the interface: ICsWeapon.
					*  Point Weapon is an object that implements the interface: ICsPointWeapon.
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
							using FireVisualParamsType = NCsWeapon::NPoint::NFire::NVisual::FParams;
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

UINTERFACE(BlueprintType)
class CSWP_API UCsData_PointWeapon_VisualFire : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
* Interface that describes any visual information associated to the Fire() call
* from a Point Weapon.
*  Weapon is an object that implements the interface: ICsWeapon.
*  Point Weapon is an object that implements the interface: ICsPointWeapon.
*/
class CSWP_API ICsData_PointWeapon_VisualFire : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

private:

	// Allow clearer names without name collisions
	struct _
	{
		using FireVisualParamsType = NCsWeapon::NPoint::NFire::NVisual::FParams;
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
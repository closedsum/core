// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
// Interfaces
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Point/Data/Visual/CsParams_PointWeapon_VisualFire.h"

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
					*
					*/
					struct CSWP_API IFire : public ICsGetInterfaceMap
					{
					public:

						static const FName Name;

					public:

						virtual ~IFire(){}

					#define VisualFireParamsType NCsWeapon::NProjectile::NData::NVisual::NFire::FParams

						/**
						*
						*
						* return
						*/
						virtual const VisualFireParamsType& GetVisualFireParams() const = 0;

					#undef VisualFireParamsType
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
*
*/
class CSWP_API ICsData_PointWeapon_VisualFire : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:

#define VisualFireParamsType NCsWeapon::NProjectile::NData::NVisual::NFire::FParams

	/**
	*
	*
	* return
	*/
	virtual const VisualFireParamsType& GetVisualFireParams() const = 0;

#undef VisualFireParamsType
};
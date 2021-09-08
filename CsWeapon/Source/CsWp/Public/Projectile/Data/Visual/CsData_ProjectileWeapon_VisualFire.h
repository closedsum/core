// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
// Interfaces
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Projectile/Data/Visual/CsParams_ProjectileWeapon_VisualFire.h"

#include "CsData_ProjectileWeapon_VisualFire.generated.h"

namespace NCsWeapon
{
	namespace NProjectile
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

						/**
						*
						*
						* return
						*/
						virtual const FParams& GetFireFXParams() const = 0;
					};
				}
			}
		}
	}
}

UINTERFACE(BlueprintType)
class CSWP_API UCsData_ProjectileWeapon_VisualFire : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
*
*/
class CSWP_API ICsData_ProjectileWeapon_VisualFire : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

private:

	typedef NCsWeapon::NProjectile::NData::NVisual::NFire::FParams ParamsType;

public:

	/**
	*
	*
	* return
	*/
	virtual const ParamsType& GetFireFXParams() const = 0;
};
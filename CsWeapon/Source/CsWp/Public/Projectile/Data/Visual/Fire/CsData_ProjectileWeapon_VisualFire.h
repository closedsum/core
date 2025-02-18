// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Interface.h"
// Interfaces
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Projectile/Data/Visual/Fire/CsParams_ProjectileWeapon_VisualFire.h"

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

					private:

						// Allow clearer names without name collisions
						struct _
						{
							using FireVisualParamsType = NCsWeapon::NProjectile::NFire::NVisual::FParams;
						};

					public:

						/**
						*
						*
						* return
						*/
						virtual const _::FireVisualParamsType& GetFireVisualParams() const = 0;
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

	// Allow clearer names without name collisions
	struct _
	{
		using FireVisualParamsType = NCsWeapon::NProjectile::NFire::NVisual::FParams;
	};

public:

	/**
	*
	*
	* return
	*/
	virtual const _::FireVisualParamsType& GetFireVisualParams() const = 0;
};
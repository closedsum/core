// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Projectile/Params/Spread/CsParams_ProjectileWeapon_Spread.h"

#include "CsData_ProjectileWeapon.generated.h"

// NCsWeapon::NProjectile::NParams::NLaunch::ILaunch
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NProjectile, NParams, NLaunch, ILaunch)

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NData
		{
			/**
			*
			*/
			struct CSWP_API IData : public ICsGetInterfaceMap
			{
			public:

				static const FName Name;

			public:

				virtual ~IData(){}

			#define LaunchParamsType NCsWeapon::NProjectile::NParams::NLaunch::ILaunch
			#define SpreadParamsType NCsWeapon::NProjectile::NSpread::FParams

				/**
				*
				*
				* return
				*/
				virtual const bool& DoFireOnRelease() const = 0;

				/**
				*
				*
				* return
				*/
				virtual const bool& IsFullAuto() const = 0;

				/**
				*
				*
				* return
				*/
				virtual const bool& HasInfiniteAmmo() const = 0;

				/**
				*
				*
				* return
				*/
				virtual const int32& GetMaxAmmo() const = 0;

				/**
				*
				*
				* return
				*/
				virtual const int32& GetProjectilesPerShot() const = 0;

				/**
				*
				*
				* return
				*/
				virtual const float& GetTimeBetweenShots() const = 0;

				/**
				*
				*
				* return
				*/
				virtual const float& GetTimeBetweenAutoShots() const = 0;

				/**
				*
				*
				* return
				*/
				virtual const float& GetTimeBetweenProjectilesPerShot() const = 0;

				/**
				*
				*
				* return
				*/
				virtual const LaunchParamsType* GetLaunchParams() const = 0;

				virtual const bool& UseSpreadParams() const = 0;

				virtual const SpreadParamsType& GetSpreadParams() const = 0;

			#undef LaunchParamsType
			#undef SpreadParamsType
			};
		}
	}
}

UINTERFACE(BlueprintType)
class CSWP_API UCsData_ProjectileWeapon : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

// NCsWeapon::NProjectile::NParams::NLaunch::ILaunch
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NProjectile, NParams, NLaunch, ILaunch)

/**
*
*/
class CSWP_API ICsData_ProjectileWeapon : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:

#define LaunchParamsType NCsWeapon::NProjectile::NParams::NLaunch::ILaunch
#define SpreadParamsType NCsWeapon::NProjectile::NSpread::FParams

	/**
	*
	*
	* return
	*/
	virtual const bool& DoFireOnRelease() const = 0;

	/**
	*
	*
	* return
	*/
	virtual const bool& IsFullAuto() const = 0;

	/**
	*
	*
	* return
	*/
	virtual const bool& HasInfiniteAmmo() const = 0;

	/**
	*
	*
	* return
	*/
	virtual const int32& GetMaxAmmo() const = 0;

	/**
	*
	*
	* return
	*/
	virtual const int32& GetProjectilesPerShot() const = 0;

	/**
	*
	*
	* return
	*/
	virtual const float& GetTimeBetweenShots() const = 0;

	/**
	*
	*
	* return
	*/
	virtual const float& GetTimeBetweenAutoShots() const = 0;

	/**
	*
	*
	* return
	*/
	virtual const float& GetTimeBetweenProjectilesPerShot() const = 0;

	/**
	*
	*
	* return
	*/
	virtual const LaunchParamsType* GetLaunchParams() const = 0;

	virtual const bool& UseSpreadParams() const = 0;

	virtual const SpreadParamsType& GetSpreadParams() const = 0;

#undef LaunchParamsType
#undef SpreadParamsType
};
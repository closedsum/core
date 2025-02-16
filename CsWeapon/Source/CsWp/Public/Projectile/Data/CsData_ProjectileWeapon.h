// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Projectile/Params/Shot/Projectile/CsParams_ProjectileWeapon_Shot_Projectile.h"
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

			private:

				// Allow clearer names without name collisions
				struct _
				{
					using ProjectilesPerShotParamsType = NCsWeapon::NProjectile::NShot::NProjectile::FParams;
					using LaunchParamsType = NCsWeapon::NProjectile::NParams::NLaunch::ILaunch;
					using SpreadParamsType = NCsWeapon::NProjectile::NSpread::FParams;
				};

			public:

				/**
				* Get whether to perform a Fire action on input pressed or released.
				*
				* return
				*/
				virtual const bool& DoFireOnRelease() const = 0;

				/**
				* Get whether the Fire action continues to execute when the Fire action is
				* active.
				*
				* return
				*/
				virtual const bool& IsFullAuto() const = 0;

				/**
				* Get whether the weapon uses infinite ammo.
				*  Max Ammo is ignored if TRUE.
				*
				* return
				*/
				virtual const bool& HasInfiniteAmmo() const = 0;

				/**
				* Get the maximum amount ammo that can be consumed before the Fire action
				* can NO longer be called.
				*
				* return
				*/
				virtual const int32& GetMaxAmmo() const = 0;

				/**
				* Get the minimum interval of time in seconds between executing the Fire action.
				*
				* return
				*/
				virtual const float& GetTimeBetweenShots() const = 0;

				/**
				* Get the minimum interval of time in seconds between automatically executing the Fire action.
				* This is only valid if IsFullAuto() is TRUE.
				*
				* return
				*/
				virtual const float& GetTimeBetweenAutoShots() const = 0;

				/**
				* Get any information related to Projectiles per Shot.
				*
				* return
				*/
				virtual const _::ProjectilesPerShotParamsType& GetProjectilesPerShotParams() const = 0;

				/**
				* Get any information related to Launching a Projectile using a Trace.
				* The trace may determine the Location and/or Direction with which to Launch the Projectile.
				*
				* return
				*/
				virtual const _::LaunchParamsType* GetLaunchParams() const = 0;

				/**
				* Get whether to use Spread Params or not.
				*
				* return
				*/
				virtual const bool& UseSpreadParams() const = 0;

				/**
				* Get any information related to Spread Shape.
				*  NOTE: UseSpreadParams() must be TRUE for this to be used.
				*
				* return
				*/
				virtual const _::SpreadParamsType& GetSpreadParams() const = 0;
			};
		}
	}
}

using CsProjectileWeaponDataType = NCsWeapon::NProjectile::NData::IData;

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

private:

	// Allow clearer names without name collisions
	struct _
	{
		using ProjectilesPerShotParamsType = NCsWeapon::NProjectile::NShot::NProjectile::FParams;
		using LaunchParamsType = NCsWeapon::NProjectile::NParams::NLaunch::ILaunch;
		using SpreadParamsType = NCsWeapon::NProjectile::NSpread::FParams;
	};

public:

	/**
	* Get whether to perform a Fire action on input pressed or released.
	*
	* return
	*/
	virtual const bool& DoFireOnRelease() const = 0;

	/**
	* Get whether the Fire action continues to execute when the Fire action is
	* active.
	*
	* return
	*/
	virtual const bool& IsFullAuto() const = 0;

	/**
	* Get whether the weapon uses infinite ammo.
	*  Max Ammo is ignored if TRUE.
	*
	* return
	*/
	virtual const bool& HasInfiniteAmmo() const = 0;

	/**
	* Get the maximum amount ammo that can be consumed before the Fire action
	* can NO longer be called.
	*
	* return
	*/
	virtual const int32& GetMaxAmmo() const = 0;

	/**
	* Get the minimum interval of time in seconds between executing the Fire action.
	*
	* return
	*/
	virtual const float& GetTimeBetweenShots() const = 0;

	/**
	* Get the minimum interval of time in seconds between automatically executing the Fire action.
	* This is only valid if IsFullAuto() is TRUE.
	*
	* return
	*/
	virtual const float& GetTimeBetweenAutoShots() const = 0;

	/** 
	* Get any information related to Projectiles per Shot.
	* 
	* return
	*/
	virtual const _::ProjectilesPerShotParamsType& GetProjectilesPerShotParams() const = 0;

	/**
	* Get any information related to Launching a Projectile using a Trace.
	* The trace may determine the Location and/or Direction with which to Launch the Projectile.
	*
	* return
	*/
	virtual const _::LaunchParamsType* GetLaunchParams() const = 0;

	/**
	* Get whether to use Spread Params or not.
	* 
	* return
	*/
	virtual const bool& UseSpreadParams() const = 0;

	/**
	* Get any information related to Spread Shape.
	*  NOTE: UseSpreadParams() must be TRUE for this to be used.
	* 
	* return
	*/
	virtual const _::SpreadParamsType& GetSpreadParams() const = 0;
};
// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Projectile/Params/Launch/CsTypes_Params_ProjectileWeapon_Launch.h"
// Containers
#include "Containers/CsGetInterfaceMap.h"

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NParams
		{
			namespace NLaunch
			{
				/**
				* Interface describing the Launch Parameters for a weapon of type: ICsProjectileWeapon. The
				* parameters are usually used to location and direction of a projectile being fired from the weapon.
				*/
				struct CSWP_API ILaunch : public ICsGetInterfaceMap
				{
				public:

					static const FName Name;

				public:

					virtual ~ILaunch() {}

				#define LaunchLocationType NCsWeapon::NProjectile::NParams::NLaunch::ELocation
				#define LaunchLocationOffsetSpace NCsWeapon::NProjectile::NParams::NLaunch::NLocation::EOffsetSpace
				#define LaunchDirectionType NCsWeapon::NProjectile::NParams::NLaunch::EDirection

					/**
					* Get the different methods to get the Location from which a Projectile is launched from a Projectile Weapon.
					* 
					* return
					*/
					virtual const LaunchLocationType& GetLocationType() const = 0;

					/**
					* Get the "Space" the location offset is applied to the Location a Projectile is Launched from a Projectile Weapon.
					* 
					* return 
					*/
					virtual const LaunchLocationOffsetSpace& GetLocationOffsetSpace() const = 0;

					/**
					*  Get which components (Pitch, Yaw, and/or Roll) or Rotation / Direction from GetLocationOffsetSpace() will
					*  affect the GetLocationOffset(). Components NOT affected will result the LocationOffset applied "directly" 
					*  in World Space..
					*  i.e. If GetLocationOffsetSpace() == LaunchLocationOffsetSpace::Owner,
					*		   Owner's Rotation is used. 
					*		   Rotation is filtered by which component (aka Rule) should affect the GetLocationOffset().
					*		   If GetLocationOffsetSpaceRules() == ECsRotationRules::Yaw then only affect the X and Y components of GetLocationOffset(), ... etc.
					* 
					* return Rules
					*/
					virtual const int32& GetLocationOffsetSpaceRules() const = 0;

					/**
					* Get the offset to apply to the Rotation determined from GetLocationOffsetSpace().
					*
					* return
					*/
					virtual const FRotator3f& GetLocationOffsetSpaceOffset() const = 0;

					/**
					* Get the offset to apply to the Location determined from GetLocationType().
					* 
					* return
					*/
					virtual const FVector3f& GetLocationOffset() const = 0;

					/**
					* Get the different methods to get the Direction from which a Projectile is launched from a Projectile Weapon.
					* 
					* return
					*/
					virtual const LaunchDirectionType& GetDirectionType() const = 0;

					/**
					* Get the offset to apply to the Rotation determined from GetDirectionType().
					*
					* return
					*/
					virtual const FRotator3f& GetDirectionOffset() const = 0;

					/**
					* Get whether the Direction from which the Projectile will be launched from a Weapon should be inverted (multiplied by -1.0f).
					* 
					* return
					*/
					virtual const bool& InvertDirection() const = 0;

					/**
					*/
					virtual const int32& GetDirectionRules() const = 0;

				#undef LaunchLocationType
				#undef LaunchLocationOffsetSpace
				#undef LaunchDirectionType
				};
			}
		}
	}
}
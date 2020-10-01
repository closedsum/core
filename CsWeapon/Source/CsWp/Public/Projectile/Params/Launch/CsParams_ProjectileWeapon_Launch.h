// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Projectile/Params/Launch/CsTypes_Params_ProjectileWeapon_Launch.h"

#include "Containers/CsGetInterfaceMap.h"

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NParams
		{
			namespace NLaunch
			{
			// Location
			#pragma region

				/**
				* Describes the different methods to get the Location from which a projectile of type:
				* ICsProjectile will be launched from a weapon of type: ICsProjectileWeapon.
				*/
				enum class ELocation : uint8
				{
					/** Owner's Location. If the Owner is of type: AActor, then it will
						be GetActorLocation(). */
					Owner,
					/** If there is a SkeletalMesh that acts as the root object for the 
						Weapon, use the Bone / Socket location. */ 
					Bone,
					Custom
				};

			#pragma endregion Location

			// Direction
			#pragma region

				/**
				* Describes the different methods to get the Direction from which a projectile of type:
				* ICsProjectile will be launched from a weapon of type: ICsProjectileWeapon.
				*/
				enum class EDirection : uint8
				{
					Owner,
					/** Owner's Rotation. If the Owner is of type: AActor, then it will
						be GetActorRotation(). */
					Camera,
					/** If there is a SkeletalMesh that acts as the root object for the Weapon, 
						use the Bone / Socket's rotation. */
					Bone,
					/** A trace is used to determine the direction. The start and end points of the 
						trace are determined by other parameters. */
					Trace,
					Custom
				};
				
			#pragma endregion Direction

				/**
				*/
				struct CSWP_API ILaunch : public ICsGetInterfaceMap
				{
				public:

					static const FName Name;

				public:

					virtual ~ILaunch() {}

					/**
					*/
					virtual const ELocation& GetLocationType() const = 0;

					/**
					*/
					virtual const EDirection& GetDirectionType() const = 0;
				};
			}
		}
	}
}
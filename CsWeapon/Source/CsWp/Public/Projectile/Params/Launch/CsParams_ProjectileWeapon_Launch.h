// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
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
					/** SceneComponent's Location. The Component is marked as the Launch Component Transform. */
					Component,
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
					/** Owner's Rotation. If the Owner is of type: AActor, then it will
						be GetActorRotation(). */
					Owner,
					/** If there is a SkeletalMesh that acts as the root object for the Weapon, 
						use the Bone / Socket's rotation. */
					Bone,
					/** SceneComponent's Rotation. The Component is marked as the Launch Component Transform. */
					Component,
					/** Owner's Camera's Rotation. */
					Camera,
					/** A trace is used to determine the direction. The start and end points of the 
						trace are determined by other parameters. */
					Trace,
					Custom
				};
				
			#pragma endregion Direction

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

					/**
					*/
					virtual const ELocation& GetLocationType() const = 0;

					/**
					*/
					virtual const EDirection& GetDirectionType() const = 0;

					/**
					*/
					virtual const int32& GetDirectionRules() const = 0;
				};
			}
		}
	}
}
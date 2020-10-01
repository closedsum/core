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

				enum class ELocation
				{
					/** Owner's Location. If the Owner is of type: AActor, then it will
						GetActorLocation(). */
					Owner,
					/** If there is a SkeletalMesh that acts as the root object for the 
						Weapon, use the Bone / Socket location. */
					Bone,
					Custom
				};

			#pragma endregion Location

			// Direction
			#pragma region

				enum class EDirection
				{
					Owner,
					Camera,
					/** */
					Bone,
					/** A trace from the camera (center of the screen) is used to determine
						the direction */
					CameraTrace,
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

					virtual const ELocation& GetLocationType() const = 0;

					virtual const EDirection& GetDirectionType() const = 0;
				};
			}
		}
	}
}
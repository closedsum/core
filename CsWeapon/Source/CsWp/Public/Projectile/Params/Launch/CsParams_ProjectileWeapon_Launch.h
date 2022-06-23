// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Types/Enum/CsEnumMap.h"
// Containers
#include "Containers/CsGetInterfaceMap.h"

// Location (NCsWeapon::NProjectile::NParams::NLaunch::ELocation)
#pragma region

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NParams
		{
			namespace NLaunch
			{
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

				struct CSWP_API EMLocation : public TCsEnumMap<ELocation>
				{
					CS_ENUM_MAP_BODY(EMLocation, ELocation)
				};

				namespace NLocation
				{
					typedef ELocation Type;

					namespace Ref
					{
						extern CSWP_API const Type Owner;
						extern CSWP_API const Type Bone;
						extern CSWP_API const Type Component;
						extern CSWP_API const Type Custom;
					}
				}
			}
		}
	}
}

#pragma endregion Location (NCsWeapon::NProjectile::NParams::NLaunch::ELocation)

// Direction (NCsWeapon::NProjectile::NParams::NLaunch::EDirection)
#pragma region

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NParams
		{
			namespace NLaunch
			{
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

				struct CSWP_API EMDirection : public TCsEnumMap<EDirection>
				{
					CS_ENUM_MAP_BODY(EMDirection, EDirection)
				};

				namespace NDirection
				{
					typedef EDirection Type;

					namespace Ref
					{
						extern CSWP_API const Type Owner;
						extern CSWP_API const Type Bone;
						extern CSWP_API const Type Component;
						extern CSWP_API const Type Camera;
						extern CSWP_API const Type Trace;
						extern CSWP_API const Type Custom;
					}
				}
			}
		}
	}
}

#pragma endregion Direction (NCsWeapon::NProjectile::NParams::NLaunch::EDirection)

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

					/**
					* Get the different methods to get the Location from which a Projectile will be launched from a Weapon.
					* 
					* return
					*/
					virtual const ELocation& GetLocationType() const = 0;

					/**
					* Get the offset to apply to the Location determined from GetLocationType().
					* 
					* return
					*/
					virtual const FVector& GetLocationOffset() const = 0;

					/**
					* Get the different methods to get the Direction from which a Projectile will be launched from a Weapon.
					* 
					* return
					*/
					virtual const EDirection& GetDirectionType() const = 0;

					/**
					* Get the offset to apply to the Rotation determined from GetDirectionType().
					*
					* return
					*/
					virtual const FRotator& GetDirectionOffset() const = 0;

					/**
					* Get whether the Direction from which the Projectile will be launched from a Weapon should be inverted (multiplied by -1.0f).
					* 
					* return
					*/
					virtual const bool& InvertDirection() const = 0;

					/**
					*/
					virtual const int32& GetDirectionRules() const = 0;
				};
			}
		}
	}
}
// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsEnumMap.h"

#include "CsTypes_Params_ProjectileWeapon_Launch.generated.h"
#pragma once

// ProjectileWeaponLaunchLocation
#pragma region

/**
* Describes the different methods to get the Location from which a projectile of type:
* ICsProjectile will be launched from a weapon of type: ICsProjectileWeapon.
*/
UENUM(BlueprintType)
enum class ECsProjectileWeaponLaunchLocation : uint8
{
	/** Owner's Location. If the Owner is of type: AActor, then it will
		GetActorLocation(). */
	Owner									UMETA(DisplayName = "Owner"),
	/** If there is a SkeletalMesh that acts as the root object for the 
		Weapon, use the Bone / Socket location. */
	Bone									UMETA(DisplayName = "Bone"),
	Component								UMETA(DisplayName = "Component"),
	Custom									UMETA(DisplayName = "Custom"),
	ECsProjectileWeaponLaunchLocation_MAX	UMETA(Hidden),
};


struct CSWP_API EMCsProjectileWeaponLaunchLocation : public TCsEnumMap<ECsProjectileWeaponLaunchLocation>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsProjectileWeaponLaunchLocation, ECsProjectileWeaponLaunchLocation)
};

namespace NCsProjectileWeaponLaunchLocation
{
	typedef ECsProjectileWeaponLaunchLocation Type;

	namespace Ref
	{
		extern CSWP_API const Type Owner;
		extern CSWP_API const Type Bone;
		extern CSWP_API const Type Component;
		extern CSWP_API const Type Custom;
		extern CSWP_API const Type ECsProjectileWeaponLaunchLocation_MAX;
	}

	extern CSWP_API const uint8 MAX;
}

#pragma endregion ProjectileWeaponLaunchLocation

// ProjectileWeaponLaunchDirection
#pragma region

/**
* Describes the different methods to get the Direction from which a projectile of type:
* ICsProjectile will be launched from a weapon of type: ICsProjectileWeapon.
*/
UENUM(BlueprintType)
enum class ECsProjectileWeaponLaunchDirection : uint8
{
	/** Owner's Location. If the Owner is of type: AActor, then it will
		GetActorLocation(). */
	Owner									UMETA(DisplayName = "Owner"),
	/** If there is a SkeletalMesh that acts as the root object for the Weapon,
		use the Bone / Socket's rotation. */
	Bone									UMETA(DisplayName = "Bone"),
	Component								UMETA(DisplayName = "Component"),
	/** Owner's Camera's Rotation. */
	Camera									UMETA(DisplayName = "Camera"),
	/** A trace is used to determine the direction. The start and end points of the
		trace are determined by other parameters. */
	Trace									UMETA(DisplayName = "Trace"),
	Custom									UMETA(DisplayName = "Custom"),
	ECsProjectileWeaponLaunchDirection_MAX	UMETA(Hidden),
};


struct CSWP_API EMCsProjectileWeaponLaunchDirection : public TCsEnumMap<ECsProjectileWeaponLaunchDirection>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsProjectileWeaponLaunchDirection, ECsProjectileWeaponLaunchDirection)
};

namespace NCsProjectileWeaponLaunchDirection
{
	typedef ECsProjectileWeaponLaunchDirection Type;

	namespace Ref
	{
		extern CSWP_API const Type Owner;
		extern CSWP_API const Type Bone;
		extern CSWP_API const Type Component;
		extern CSWP_API const Type Trace;
		extern CSWP_API const Type Custom;
		extern CSWP_API const Type ECsProjectileWeaponLaunchDirection_MAX;
	}

	extern CSWP_API const uint8 MAX;
}

#pragma endregion ProjectileWeaponLaunchDirection
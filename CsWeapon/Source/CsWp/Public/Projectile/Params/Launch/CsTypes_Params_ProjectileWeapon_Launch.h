// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
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
		extern CSWP_API const Type Custom;
		extern CSWP_API const Type ECsProjectileWeaponLaunchLocation_MAX;
	}

	extern CSWP_API const uint8 MAX;
}

#pragma endregion ProjectileWeaponLaunchLocation
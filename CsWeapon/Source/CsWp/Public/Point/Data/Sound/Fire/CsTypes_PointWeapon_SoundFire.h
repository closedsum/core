// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/Sound/CsTypes_Sound.h"
// Log
#include "Utility/CsWpLog.h"

#include "CsTypes_PointWeapon_SoundFire.generated.h"

// PointWeaponSoundFireAttach
#pragma region

/**
* Describes where the Fire Sound should be played from a Point Weapon.
*  Weapon is an object that implements the interface: ICsWeapon.
*  Projectile Weapon is an object that implements the interface: ICsProjectileWeapon.
*/
UENUM(BlueprintType)
enum class ECsPointWeaponSoundFireAttach : uint8
{
	None								UMETA(DisplayName = "None"),
	Owner								UMETA(DisplayName = "Owner"),
	Component							UMETA(DisplayName = "Component"),
	Custom								UMETA(DisplayName = "Custom"),
	ECsPointWeaponSoundFireAttach_MAX	UMETA(Hidden),
};


struct CSWP_API EMCsPointWeaponSoundFireAttach : public TCsEnumMap<ECsPointWeaponSoundFireAttach>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsPointWeaponSoundFireAttach, ECsPointWeaponSoundFireAttach)
};

namespace NCsPointWeaponSoundFireAttach
{
	typedef ECsPointWeaponSoundFireAttach Type;

	namespace Ref
	{
		extern CSWP_API const Type None;
		extern CSWP_API const Type Owner;
		extern CSWP_API const Type Component;
		extern CSWP_API const Type ECsPointWeaponSoundFireAttach_MAX;
	}

	extern CSWP_API const uint8 MAX;
}

namespace NCsWeapon
{
	namespace NPoint
	{
		namespace NFire
		{
			namespace NSound
			{
				enum class EAttach : uint8
				{
					None,
					Owner,
					Component,
					Custom,
					EAttach_MAX
				};

				struct CSWP_API EMAttach : public TCsEnumMap<EAttach>
				{
					CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMAttach, EAttach)
				};

				namespace NAttach
				{
					typedef EAttach Type;

					namespace Ref
					{
						extern CSWP_API const Type None;
						extern CSWP_API const Type Owner;
						extern CSWP_API const Type Component;
						extern CSWP_API const Type EAttach_MAX;
					}
				}
			}
		}
	}
}

#pragma endregion PointWeaponSoundFireAttach
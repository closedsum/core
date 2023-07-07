// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/Sound/CsTypes_Sound.h"
// Log
#include "Utility/CsWpLog.h"

#include "CsTypes_PointSequenceWeapon_SoundFire.generated.h"

// PointSequenceWeaponSoundFireAttach
#pragma region

/**
* Describes where the Fire Sound should be played from a Point Sequence Weapon.
*  Weapon is an object that implements the interface: ICsWeapon.
*  Projectile Sequence Weapon is an object that implements the interface: ICsPointSequenceWeapon.
*/
UENUM(BlueprintType)
enum class ECsPointSequenceWeaponSoundFireAttach : uint8
{
	None										UMETA(DisplayName = "None"),
	Owner										UMETA(DisplayName = "Owner"),
	Component									UMETA(DisplayName = "Component"),
	Custom										UMETA(DisplayName = "Custom"),
	ECsPointSequenceWeaponSoundFireAttach_MAX	UMETA(Hidden),
};


struct CSWP_API EMCsPointSequenceWeaponSoundFireAttach : public TCsEnumMap<ECsPointSequenceWeaponSoundFireAttach>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsPointSequenceWeaponSoundFireAttach, ECsPointSequenceWeaponSoundFireAttach)
};

namespace NCsPointSequenceWeaponSoundFireAttach
{
	typedef ECsPointSequenceWeaponSoundFireAttach Type;

	namespace Ref
	{
		extern CSWP_API const Type None;
		extern CSWP_API const Type Owner;
		extern CSWP_API const Type Component;
		extern CSWP_API const Type Custom;
		extern CSWP_API const Type ECsPointSequenceWeaponSoundFireAttach_MAX;
	}

	extern CSWP_API const uint8 MAX;
}

namespace NCsWeapon
{
	namespace NPoint
	{
		namespace NSequence
		{
			namespace NFire
			{
				namespace NSound
				{
					/**
					* Describes where the Fire Sound should be played from a Point Sequence Weapon.
					*  Weapon is an object that implements the interface: ICsWeapon.
					*  Projectile Sequence Weapon is an object that implements the interface: ICsPointSequenceWeapon.
					*/
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
							extern CSWP_API const Type Custom;
							extern CSWP_API const Type EAttach_MAX;
						}
					}
				}
			}
		}
	}
}

#pragma endregion PointSequenceWeaponSoundFireAttach
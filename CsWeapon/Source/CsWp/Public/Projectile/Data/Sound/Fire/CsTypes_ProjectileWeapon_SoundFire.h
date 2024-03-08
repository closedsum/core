// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/Sound/CsTypes_Sound.h"
// Log
#include "Utility/CsWpLog.h"

#include "CsTypes_ProjectileWeapon_SoundFire.generated.h"

// ProjectileWeaponFireSoundAttach
#pragma region

/**
* Describes where the Fire Sound should be played from on the weapon.
*/
UENUM(BlueprintType)
enum class ECsProjectileWeaponFireSoundAttach : uint8
{
	None									UMETA(DisplayName = "None"),
	Owner									UMETA(DisplayName = "Owner"),
	Component								UMETA(DisplayName = "Component"),
	Custom									UMETA(DisplayName = "Custom"),
	ECsProjectileWeaponFireSoundAttach_MAX	UMETA(Hidden),
};

struct CSWP_API EMCsProjectileWeaponFireSoundAttach : public TCsEnumMap<ECsProjectileWeaponFireSoundAttach>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsProjectileWeaponFireSoundAttach, ECsProjectileWeaponFireSoundAttach)
};

namespace NCsProjectileWeaponFireSoundAttach
{
	typedef ECsProjectileWeaponFireSoundAttach Type;

	namespace Ref
	{
		extern CSWP_API const Type None;
		extern CSWP_API const Type Owner;
		extern CSWP_API const Type Component;
		extern CSWP_API const Type ECsProjectileWeaponFireSoundAttach_MAX;
	}

	extern CSWP_API const uint8 MAX;
}

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NFire
		{
			namespace NSound
			{
				/**
				* Describes where the Fire Sound should be played from on the weapon.
				*/
				enum class EAttach
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

#pragma endregion ProjectileWeaponFireSoundAttach
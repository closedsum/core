// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Sound/CsTypes_Sound.h"

#include "CsTypes_Params_ProjectileWeapon_SoundFire.generated.h"
#pragma once

// ProjectileWeaponSoundFireAttach
#pragma region

/**
* Describes where the Fire Sound should be played from on the weapon.
*/
UENUM(BlueprintType)
enum class ECsProjectileWeaponSoundFireAttach : uint8
{
	None									UMETA(DisplayName = "None"),
	Owner									UMETA(DisplayName = "Owner"),
	Component								UMETA(DisplayName = "Component"),
	Custom									UMETA(DisplayName = "Custom"),
	ECsProjectileWeaponSoundFireAttach_MAX	UMETA(Hidden),
};


struct CSWP_API EMCsProjectileWeaponSoundFireAttach : public TCsEnumMap<ECsProjectileWeaponSoundFireAttach>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsProjectileWeaponSoundFireAttach, ECsProjectileWeaponSoundFireAttach)
};

namespace NCsProjectileWeaponSoundFireAttach
{
	typedef ECsProjectileWeaponSoundFireAttach Type;

	namespace Ref
	{
		extern CSWP_API const Type None;
		extern CSWP_API const Type Owner;
		extern CSWP_API const Type Component;
		extern CSWP_API const Type ECsProjectileWeaponSoundFireAttach_MAX;
	}

	extern CSWP_API const uint8 MAX;
}

#pragma endregion ProjectileWeaponSoundFireAttach

// FCsProjectileWeaponSoundFireParams
#pragma region

CS_FWD_DECLARE_STRUCT_NAMESPACE_6(NCsWeapon, NProjectile, NData, NSound, NFire, NParams, FEmu)

USTRUCT(BlueprintType)
struct CSWP_API FCsProjectileWeaponSoundFireParams
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCsSound Sound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECsProjectileWeaponSoundFireAttach Attach;

	FCsProjectileWeaponSoundFireParams() :
		Sound(),
		Attach(ECsProjectileWeaponSoundFireAttach::Component)
	{
	}

#define ParamsType NCsWeapon::NProjectile::NData::NSound::NFire::NParams::FEmu

	void CopyParams(ParamsType* Params);

#undef ParamsType
	
	// NOTE: Added to get around compiler error when using #undef
private:
	FORCEINLINE void _Nothing(){}
};

#pragma endregion FCsProjectileWeaponSoundFireParams
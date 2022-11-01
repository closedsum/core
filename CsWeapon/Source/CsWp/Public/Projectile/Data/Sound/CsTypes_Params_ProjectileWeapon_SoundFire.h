// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/Sound/CsTypes_Sound.h"
// Log
#include "Utility/CsWpLog.h"

#include "CsTypes_Params_ProjectileWeapon_SoundFire.generated.h"

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

// FCsProjectileWeapon_SoundFire_Params
#pragma region

// NCsWeapon::NProjectile::NData::NSound::NFire::NParams::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_6(NCsWeapon, NProjectile, NData, NSound, NFire, NParams, FImpl)

/**
* Describes any Sound information related to the Fire action for a Projectile Weapon.
*  Projectile Weapon is an object that implements the interface: ICsProjectileWeapon.
*/
USTRUCT(BlueprintType)
struct CSWP_API FCsProjectileWeapon_SoundFire_Params
{
	GENERATED_USTRUCT_BODY()

public:

	/** Which Sound to play when the Fire action is executed. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Projectile")
	FCsSound Sound;

	/** How the Sound should be attached. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Projectile")
	ECsProjectileWeaponSoundFireAttach Attach;

	FCsProjectileWeapon_SoundFire_Params() :
		Sound(),
		Attach(ECsProjectileWeaponSoundFireAttach::Component)
	{
	}

#define ParamsType NCsWeapon::NProjectile::NData::NSound::NFire::NParams::FImpl

	void CopyToParams(ParamsType* Params);
	void CopyToParamsAsValue(ParamsType* Params) const;

#undef ParamsType
	
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const 
	{
		if (!Sound.IsValid(Context, Log))
			return false;
		return true;
	}
};

#pragma endregion FCsProjectileWeapon_SoundFire_Params
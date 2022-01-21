// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Projectile/Data/Sound/CsTypes_Params_ProjectileWeapon_SoundFire.h"

#include "Projectile/Data/Sound/CsParams_ProjectileWeapon_SoundFire.h"

// ProjectileWeaponSoundFireAttach
#pragma region

namespace NCsProjectileWeaponSoundFireAttach
{
	namespace Ref
	{
		typedef EMCsProjectileWeaponSoundFireAttach EnumMapType;

		CSWP_API CS_ADD_TO_ENUM_MAP(None);
		CSWP_API CS_ADD_TO_ENUM_MAP(Owner);
		CSWP_API CS_ADD_TO_ENUM_MAP(Component);
		CSWP_API CS_ADD_TO_ENUM_MAP(Custom);
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsProjectileWeaponSoundFireAttach_MAX, "MAX");
	}

	CSWP_API const uint8 MAX = (uint8)Type::ECsProjectileWeaponSoundFireAttach_MAX;
}

#pragma endregion ProjectileWeaponSoundFireAttach

// FCsProjectileWeapon_SoundFire_Params
#pragma region

#define ParamsType NCsWeapon::NProjectile::NData::NSound::NFire::NParams::FImpl

void FCsProjectileWeapon_SoundFire_Params::CopyToParams(ParamsType* Params)
{
	Params->SetSound(&Sound);

	typedef NCsWeapon::NProjectile::NData::NSound::NFire::NParams::EAttach AttachType;

	Params->SetAttachType((AttachType*)(&Attach));
}

void FCsProjectileWeapon_SoundFire_Params::CopyToParamsAsValue(ParamsType* Params) const
{
	Params->SetSound(Sound);

	typedef NCsWeapon::NProjectile::NData::NSound::NFire::NParams::EAttach AttachType;

	Params->SetAttachType((AttachType)(Attach));
}

#undef ParamsType

#pragma endregion FCsProjectileWeapon_SoundFire_Params
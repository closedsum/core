// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Beam/Data/Sound/CsTypes_Params_BeamWeapon_SoundFire.h"

#include "Beam/Data/Sound/CsParams_BeamWeapon_SoundFire.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_Params_BeamWeapon_SoundFire)

// BeamWeaponSoundFireAttach
#pragma region

namespace NCsBeamWeaponSoundFireAttach
{
	namespace Ref
	{
		typedef EMCsBeamWeaponSoundFireAttach EnumMapType;

		CSWP_API CS_ADD_TO_ENUM_MAP(None);
		CSWP_API CS_ADD_TO_ENUM_MAP(Owner);
		CSWP_API CS_ADD_TO_ENUM_MAP(Component);
		CSWP_API CS_ADD_TO_ENUM_MAP(Custom);
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsBeamWeaponSoundFireAttach_MAX, "MAX");
	}

	CSWP_API const uint8 MAX = (uint8)Type::ECsBeamWeaponSoundFireAttach_MAX;
}

#pragma endregion BeamWeaponSoundFireAttach

// FCsBeamWeaponSoundFireParams
#pragma region

#define ParamsType NCsWeapon::NBeam::NData::NSound::NFire::NParams::FProxy
void FCsBeamWeaponSoundFireParams::CopyToParams(ParamsType* Params)
{
#undef ParamsType

	Params->SetSound(&Sound);

	typedef NCsWeapon::NBeam::NData::NSound::NFire::NParams::EAttach AttachType;

	Params->SetAttachType((AttachType*)(&Attach));
}

bool FCsBeamWeaponSoundFireParams::IsValidChecked(const FString& Context) const
{
	check(Sound.IsValidChecked(Context));

	check(EMCsBeamWeaponSoundFireAttach::Get().IsValidEnumChecked(Context, Attach));
	return true;
}

#pragma endregion FCsBeamWeaponSoundFireParams
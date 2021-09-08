// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Trace/Data/Sound/CsTypes_Params_TraceWeapon_SoundFire.h"

#include "Trace/Data/Sound/CsParams_TraceWeapon_SoundFire.h"

// TraceWeaponSoundFireAttach
#pragma region

namespace NCsTraceWeaponSoundFireAttach
{
	namespace Ref
	{
		typedef EMCsTraceWeaponSoundFireAttach EnumMapType;

		CSWP_API CS_ADD_TO_ENUM_MAP(None);
		CSWP_API CS_ADD_TO_ENUM_MAP(Owner);
		CSWP_API CS_ADD_TO_ENUM_MAP(Component);
		CSWP_API CS_ADD_TO_ENUM_MAP(Custom);
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsTraceWeaponSoundFireAttach_MAX, "MAX");
	}

	CSWP_API const uint8 MAX = (uint8)Type::ECsTraceWeaponSoundFireAttach_MAX;
}

#pragma endregion TraceWeaponSoundFireAttach

// FCsTraceWeaponSoundFireParams
#pragma region

#define ParamsType NCsWeapon::NTrace::NData::NSound::NFire::NParams::FProxy
void FCsTraceWeaponSoundFireParams::CopyParams(ParamsType* Params)
{
#undef ParamsType

	Params->SetSound(&Sound);

	typedef NCsWeapon::NTrace::NData::NSound::NFire::NParams::EAttach AttachType;

	Params->SetAttachType((AttachType*)(&Attach));
}

#pragma endregion FCsTraceWeaponSoundFireParams
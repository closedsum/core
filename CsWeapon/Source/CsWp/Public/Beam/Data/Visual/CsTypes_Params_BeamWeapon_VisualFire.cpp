// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Beam/Data/Visual/CsTypes_Params_BeamWeapon_VisualFire.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Data
#include "Beam/Data/Visual/CsParams_BeamWeapon_VisualFire.h"

// BeamWeaponVisualFireAttach
#pragma region

namespace NCsBeamWeaponVisualFireAttach
{
	namespace Ref
	{
		typedef EMCsBeamWeaponVisualFireAttach EnumMapType;

		CSWP_API CS_ADD_TO_ENUM_MAP(None);
		CSWP_API CS_ADD_TO_ENUM_MAP(Owner);
		CSWP_API CS_ADD_TO_ENUM_MAP(Component);
		CSWP_API CS_ADD_TO_ENUM_MAP(Custom);
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsBeamWeaponVisualFireAttach_MAX, "MAX");
	}

	CSWP_API const uint8 MAX = (uint8)Type::ECsBeamWeaponVisualFireAttach_MAX;
}

#pragma endregion BeamWeaponVisualFireAttach

// FCsBeamWeaponVisualFireParams
#pragma region

#define ParamsType NCsWeapon::NBeam::NData::NVisual::NFire::NParams::FProxy
void FCsBeamWeaponVisualFireParams::CopyToParams(ParamsType* Params)
{
#undef ParamsType

	Params->SetFX(&FX);

	typedef NCsWeapon::NBeam::NData::NVisual::NFire::NParams::EAttach AttachType;

	Params->SetAttachType((AttachType*)&Attach);
}

bool FCsBeamWeaponVisualFireParams::IsValidChecked(const FString& Context) const
{
	CS_IS_VALID_CHECKED(FX);

	check(EMCsBeamWeaponVisualFireAttach::Get().IsValidEnumChecked(Context, Attach));
	return true;
}

#pragma endregion FCsBeamWeaponVisualFireParams
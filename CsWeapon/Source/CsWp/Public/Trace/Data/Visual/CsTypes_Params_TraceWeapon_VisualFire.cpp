// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Trace/Data/Visual/CsTypes_Params_TraceWeapon_VisualFire.h"

#include "Trace/Data/Visual/CsParams_TraceWeapon_VisualFire.h"

// TraceWeaponVisualFireAttach
#pragma region

namespace NCsTraceWeaponVisualFireAttach
{
	namespace Ref
	{
		typedef EMCsTraceWeaponVisualFireAttach EnumMapType;

		CSWP_API CS_ADD_TO_ENUM_MAP(None);
		CSWP_API CS_ADD_TO_ENUM_MAP(Owner);
		CSWP_API CS_ADD_TO_ENUM_MAP(Component);
		CSWP_API CS_ADD_TO_ENUM_MAP(Custom);
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsTraceWeaponVisualFireAttach_MAX, "MAX");
	}

	CSWP_API const uint8 MAX = (uint8)Type::ECsTraceWeaponVisualFireAttach_MAX;
}

#pragma endregion TraceWeaponVisualFireAttach

// FCsTraceWeaponVisualFireParams
#pragma region

#define ParamsType NCsWeapon::NTrace::NData::NVisual::NFire::NParams::FProxy
void FCsTraceWeaponVisualFireParams::CopyParams(ParamsType* Params)
{
#undef ParamsType

	Params->SetFX(&FX);

	typedef NCsWeapon::NTrace::NData::NVisual::NFire::NParams::EAttach AttachType;

	Params->SetAttachType((AttachType*)&Attach);
}

#pragma endregion FCsTraceWeaponVisualFireParams
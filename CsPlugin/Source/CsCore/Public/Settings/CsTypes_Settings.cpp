// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Settings/CsTypes_Settings.h"

// PopulateEnumMapMethod
#pragma region

namespace NCsPopulateEnumMapMethod
{
	CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsPopulateEnumMapMethod, Native);
	CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsPopulateEnumMapMethod, EnumSettings, "Enum Settings");
	CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsPopulateEnumMapMethod, DataTable);
	CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsPopulateEnumMapMethod, ECsPopulateEnumMapMethod_MAX, "MAX");

	CSCORE_API const uint8 MAX = (uint8)ECsPopulateEnumMapMethod::ECsPopulateEnumMapMethod_MAX;
}

#pragma endregion PopulateEnumMapMethod
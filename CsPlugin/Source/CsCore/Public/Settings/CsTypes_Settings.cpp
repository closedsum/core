// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Settings/CsTypes_Settings.h"

// PopulateEnumMapMethod
#pragma region

namespace NCsPopulateEnumMapMethod
{
	namespace Ref
	{
		typedef EMCsPopulateEnumMapMethod EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(Native);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EnumSettings, "Enum Settings");
		CSCORE_API CS_ADD_TO_ENUM_MAP(DataTable);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsPopulateEnumMapMethod_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)ECsPopulateEnumMapMethod::ECsPopulateEnumMapMethod_MAX;
}

#pragma endregion PopulateEnumMapMethod
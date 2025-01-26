// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Camera/CsTypes_Camera.h"

// ViewTargetBlendFunction
#pragma region

namespace NViewTargetBlendFunction
{
	namespace Ref
	{
		typedef EMCsViewTargetBlendFunction EnumMapType;

		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(VTBlend_Linear, "Linear");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(VTBlend_Cubic, "Cubic");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(VTBlend_EaseIn, "Ease In");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(VTBlend_EaseOut, "Ease Out");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(VTBlend_EaseInOut, "Ease In Out");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(VTBlend_PreBlended, "PreBlended");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(VTBlend_MAX, "MAX");
	}
}

#pragma endregion ViewTargetBlendFunction
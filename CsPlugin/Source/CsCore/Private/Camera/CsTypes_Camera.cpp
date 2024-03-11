// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Camera/CsTypes_Camera.h"
#include "CsCore.h"

// ViewTargetBlendFunction
#pragma region

namespace NViewTargetBlendFunction
{
	namespace Ref
	{
		typedef EMCsViewTargetBlendFunction EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(VTBlend_Linear, "Linear");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(VTBlend_Cubic, "Cubic");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(VTBlend_EaseIn, "Ease In");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(VTBlend_EaseOut, "Ease Out");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(VTBlend_EaseInOut, "Ease In Out");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(VTBlend_PreBlended, "PreBlended");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(VTBlend_MAX, "MAX");
	}
}

#pragma endregion ViewTargetBlendFunction
// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Types/Enum/CsEnumMap.h"
#include "Camera/PlayerCameraManager.h"

// ViewTargetBlendFunction
#pragma region

struct CSCORE_API EMCsViewTargetBlendFunction : public TCsEnumMap<EViewTargetBlendFunction>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsViewTargetBlendFunction, EViewTargetBlendFunction)
};

namespace NViewTargetBlendFunction
{
	typedef EViewTargetBlendFunction Type;

	namespace Ref
	{
		extern CSCORE_API const Type VTBlend_Linear;
		extern CSCORE_API const Type VTBlend_Cubic;
		extern CSCORE_API const Type VTBlend_EaseIn;
		extern CSCORE_API const Type VTBlend_EaseOut;
		extern CSCORE_API const Type VTBlend_EaseInOut;
		extern CSCORE_API const Type VTBlend_PreBlended;
		extern CSCORE_API const Type VTBlend_MAX;
	}
}

#pragma endregion ViewTargetBlendFunction
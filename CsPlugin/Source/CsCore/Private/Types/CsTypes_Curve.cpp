// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Types/CsTypes_Curve.h"
#include "CsCore.h"

// RichCurveInterpMode
#pragma region

namespace NCsRichCurveInterpMode
{
	namespace Ref
	{
		typedef EMCsRichCurveInterpMode EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(RCIM_Linear, "Linear");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(RCIM_Constant, "Constant");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(RCIM_Cubic, "Cubic");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(RCIM_None, "None");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsRichCurveInterpMode_MAX, "MAX");
	}
}

#pragma endregion RichCurveInterpMode

// RichCurveTangentMode
#pragma region

namespace NCsRichCurveTangentMode
{
	namespace Ref
	{
		typedef EMCsRichCurveTangentMode EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(RCTM_Auto, "Auto");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(RCTM_User, "User");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(RCTM_Break, "Break");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(RCTM_None, "None");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsRichCurveTangentMode_MAX, "MAX");
	}
}

#pragma endregion RichCurveTangentMode
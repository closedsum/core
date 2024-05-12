// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Types/CsTypes_Curve.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_Curve)

// RichCurveInterpMode
#pragma region

namespace NCsRichCurveInterpMode
{
	namespace Ref
	{
		typedef EMCsRichCurveInterpMode EnumMapType;

		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(RCIM_Linear, "Linear");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(RCIM_Constant, "Constant");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(RCIM_Cubic, "Cubic");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(RCIM_None, "None");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsRichCurveInterpMode_MAX, "MAX");
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

		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(RCTM_Auto, "Auto");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(RCTM_User, "User");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(RCTM_Break, "Break");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(RCTM_None, "None");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsRichCurveTangentMode_MAX, "MAX");
	}
}

#pragma endregion RichCurveTangentMode
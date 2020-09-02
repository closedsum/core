// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Curve.h"
#include "CsCore.h"

// RichCurveInterpMode
#pragma region

namespace NCsRichCurveInterpMode
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsRichCurveInterpMode, RCIM_Linear, "Linear");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsRichCurveInterpMode, RCIM_Constant, "Constant");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsRichCurveInterpMode, RCIM_Cubic, "Cubic");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsRichCurveInterpMode, RCIM_None, "None");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsRichCurveInterpMode, ECsRichCurveInterpMode_MAX, "MAX");
	}
}

#pragma endregion RichCurveInterpMode

// RichCurveTangentMode
#pragma region

namespace NCsRichCurveTangentMode
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsRichCurveTangentMode, RCTM_Auto, "Auto");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsRichCurveTangentMode, RCTM_User, "User");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsRichCurveTangentMode, RCTM_Break, "Break");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsRichCurveTangentMode, RCTM_None, "None");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsRichCurveTangentMode, ECsRichCurveTangentMode_MAX, "MAX");
	}
}

#pragma endregion RichCurveTangentMode
// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Curve.h"
#include "CsCore.h"

// RichCurveInterpMode
EMCsRichCurveInterpMode* EMCsRichCurveInterpMode::Instance;

EMCsRichCurveInterpMode& EMCsRichCurveInterpMode::Get()
{
	if (!Instance)
		Instance = new EMCsRichCurveInterpMode();
	return *Instance;
}

namespace ECsRichCurveInterpMode
{
	namespace Ref
	{
		CSCORE_API const Type RCIM_Linear = EMCsRichCurveInterpMode::Get().Add(Type::RCIM_Linear, TEXT("RCIM_Linear"), TEXT("Linear"));
		CSCORE_API const Type RCIM_Constant = EMCsRichCurveInterpMode::Get().Add(Type::RCIM_Constant, TEXT("RCIM_Constant"), TEXT("Constant"));
		CSCORE_API const Type RCIM_Cubic = EMCsRichCurveInterpMode::Get().Add(Type::RCIM_Cubic, TEXT("RCIM_Cubic"), TEXT("Cubic"));
		CSCORE_API const Type RCIM_None = EMCsRichCurveInterpMode::Get().Add(Type::RCIM_None, TEXT("RCIM_None"), TEXT("None"));
		CSCORE_API const Type ECsRichCurveInterpMode_MAX = EMCsRichCurveInterpMode::Get().Add(Type::ECsRichCurveInterpMode_MAX, TEXT("ECsRichCurveInterpMode_MAX"), TEXT("MAX"));
	}
}

// RichCurveTangentMode
EMCsRichCurveTangentMode* EMCsRichCurveTangentMode::Instance;

EMCsRichCurveTangentMode& EMCsRichCurveTangentMode::Get()
{
	if (!Instance)
		Instance = new EMCsRichCurveTangentMode();
	return *Instance;
}

namespace ECsRichCurveTangentMode
{
	namespace Ref
	{
		CSCORE_API const Type RCTM_Auto = EMCsRichCurveTangentMode::Get().Add(Type::RCTM_Auto, TEXT("RCTM_Auto"), TEXT("Auto"));
		CSCORE_API const Type RCTM_User = EMCsRichCurveTangentMode::Get().Add(Type::RCTM_User, TEXT("RCTM_User"), TEXT("User"));
		CSCORE_API const Type RCTM_Break = EMCsRichCurveTangentMode::Get().Add(Type::RCTM_Break, TEXT("RCTM_Break"), TEXT("Break"));
		CSCORE_API const Type RCTM_None = EMCsRichCurveTangentMode::Get().Add(Type::RCTM_None, TEXT("RCTM_None"), TEXT("None"));
		CSCORE_API const Type ECsRichCurveTangentMode_MAX = EMCsRichCurveTangentMode::Get().Add(Type::ECsRichCurveTangentMode_MAX, TEXT("ECsRichCurveTangentMode_MAX"), TEXT("MAX"));
	}
}
// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Interpolation.h"

// BlendDirection
#pragma region

namespace NCsBlendDirection
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsBlendDirection, In);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsBlendDirection, Out);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsBlendDirection, ECsBlendDirection_MAX, "MAX");
	}
}

#pragma endregion BlendDirection

// EasingType
#pragma region

namespace NCsEasingType
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsEasingType, Linear);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsEasingType, BounceIn);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsEasingType, BounceOut);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsEasingType, BounceInOut);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsEasingType, CubicIn);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsEasingType, CubicOut);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsEasingType, CubicInOut);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsEasingType, ExpoIn);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsEasingType, ExpoOut);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsEasingType, ExpoInOut);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsEasingType, ECsEasingType_MAX, "MAX");
	}
}

#pragma endregion EasingType

// InterpolatingMethod
#pragma region

namespace NCsInterpolatingMethod
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsInterpolatingMethod, Easing);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsInterpolatingMethod, Curve);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsInterpolatingMethod, Custom);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsInterpolatingMethod, ECsInterpolatingMethod_MAX, "MAX");
	}
}

#pragma endregion InterpolatingMethod
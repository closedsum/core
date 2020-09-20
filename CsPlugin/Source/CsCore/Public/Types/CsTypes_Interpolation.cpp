// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Interpolation.h"

// BlendDirection
#pragma region

namespace NCsBlendDirection
{
	namespace Ref
	{
		typedef EMCsBlendDirection EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(In);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Out);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsBlendDirection_MAX, "MAX");
	}
}

#pragma endregion BlendDirection

// EasingType
#pragma region

namespace NCsEasingType
{
	namespace Ref
	{
		typedef EMCsEasingType EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(Linear);
		CSCORE_API CS_ADD_TO_ENUM_MAP(BounceIn);
		CSCORE_API CS_ADD_TO_ENUM_MAP(BounceOut);
		CSCORE_API CS_ADD_TO_ENUM_MAP(BounceInOut);
		CSCORE_API CS_ADD_TO_ENUM_MAP(CubicIn);
		CSCORE_API CS_ADD_TO_ENUM_MAP(CubicOut);
		CSCORE_API CS_ADD_TO_ENUM_MAP(CubicInOut);
		CSCORE_API CS_ADD_TO_ENUM_MAP(ExpoIn);
		CSCORE_API CS_ADD_TO_ENUM_MAP(ExpoOut);
		CSCORE_API CS_ADD_TO_ENUM_MAP(ExpoInOut);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsEasingType_MAX, "MAX");
	}
}

#pragma endregion EasingType

// InterpolatingMethod
#pragma region

namespace NCsInterpolatingMethod
{
	namespace Ref
	{
		typedef EMCsInterpolatingMethod EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(Easing);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Curve);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Custom);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsInterpolatingMethod_MAX, "MAX");
	}
}

#pragma endregion InterpolatingMethod
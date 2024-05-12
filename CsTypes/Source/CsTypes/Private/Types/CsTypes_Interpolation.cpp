// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Types/CsTypes_Interpolation.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_Interpolation)

// BlendDirection
#pragma region

namespace NCsBlendDirection
{
	namespace Ref
	{
		typedef EMCsBlendDirection EnumMapType;

		CSTYPES_API CS_ADD_TO_ENUM_MAP(In);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(Out);
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsBlendDirection_MAX, "MAX");
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

		CSTYPES_API CS_ADD_TO_ENUM_MAP(Linear);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(BounceIn);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(BounceOut);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(BounceInOut);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(QuadIn);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(QuadOut);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(QuadInOut);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(CubicIn);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(CubicOut);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(CubicInOut);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(ExpoIn);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(ExpoOut);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(ExpoInOut);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(BackIn);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(BackOut);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(BackInOut);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(ElasticIn);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(ElasticOut);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(ElasticInOut);
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsEasingType_MAX, "MAX");
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

		CSTYPES_API CS_ADD_TO_ENUM_MAP(Easing);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(Curve);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(Custom);
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsInterpolatingMethod_MAX, "MAX");
	}
}

#pragma endregion InterpolatingMethod
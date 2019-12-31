// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Interpolation.h"

// BlendDirection
#pragma region

namespace NCsBlendDirection
{
	namespace Ref
	{
		CSCORE_API const Type In = EMCsBlendDirection::Get().Add(Type::In, TEXT("In"));
		CSCORE_API const Type Out = EMCsBlendDirection::Get().Add(Type::Out, TEXT("Out"));
		CSCORE_API const Type ECsBlendDirection_MAX = EMCsBlendDirection::Get().Add(Type::ECsBlendDirection_MAX, TEXT("ECsBlendDirection_MAX"), TEXT("MAX"));
	}
}

#pragma endregion BlendDirection

// EasingType
#pragma region

namespace NCsEasingType
{
	namespace Ref
	{
		CSCORE_API const Type Linear = EMCsEasingType::Get().Add(Type::Linear, TEXT("Linear"));
		CSCORE_API const Type BounceIn = EMCsEasingType::Get().Add(Type::BounceIn, TEXT("BounceIn"));
		CSCORE_API const Type BounceOut = EMCsEasingType::Get().Add(Type::BounceOut, TEXT("BounceOut"));
		CSCORE_API const Type BounceInOut = EMCsEasingType::Get().Add(Type::BounceInOut, TEXT("BounceInOut"));
		CSCORE_API const Type CubicIn = EMCsEasingType::Get().Add(Type::CubicIn, TEXT("CubicIn"));
		CSCORE_API const Type CubicOut = EMCsEasingType::Get().Add(Type::CubicOut, TEXT("CubicOut"));
		CSCORE_API const Type CubicInOut = EMCsEasingType::Get().Add(Type::CubicInOut, TEXT("CubicInOut"));
		CSCORE_API const Type ExpoIn = EMCsEasingType::Get().Add(Type::ExpoIn, TEXT("ExpoIn"));
		CSCORE_API const Type ExpoOut = EMCsEasingType::Get().Add(Type::ExpoOut, TEXT("ExpoOut"));
		CSCORE_API const Type ExpoInOut = EMCsEasingType::Get().Add(Type::ExpoInOut, TEXT("ExpoInOut"));
		CSCORE_API const Type ECsEasingType_MAX = EMCsEasingType::Get().Add(Type::ECsEasingType_MAX, TEXT("ECsEasingType_MAX"), TEXT("MAX"));
	}
}

#pragma endregion EasingType
// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsEnumMap.h"

//#include "CsTypes_Interpolation.generated.h"
#pragma once

// BlendDirection
#pragma region

/**
*/
UENUM(BlueprintType)
enum class ECsBlendDirection : uint8
{
	In						UMETA(DisplayName = "In"),
	Out						UMETA(DisplayName = "Out"),
	ECsBlendDirection_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsBlendDirection : public TCsEnumMap<ECsBlendDirection>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsBlendDirection, ECsBlendDirection)
};

namespace NCsBlendDirection
{
	namespace Ref
	{
		typedef ECsBlendDirection Type;

		extern CSCORE_API const Type In;
		extern CSCORE_API const Type Out;
		extern CSCORE_API const Type ECsBlendDirection_MAX;
	}
}

#pragma endregion BlendDirection

// EasingType
#pragma region

/**
*/
UENUM(BlueprintType)
enum class ECsEasingType : uint8
{
	Linear				UMETA(DisplayName = "Linear"),
	BounceIn			UMETA(DisplayName = "Bounce In"),
	BounceOut			UMETA(DisplayName = "Bounce Out"),
	BounceInOut			UMETA(DisplayName = "Bounce In Out"),
	CubicIn				UMETA(DisplayName = "Cubic In"),
	CubicOut			UMETA(DisplayName = "Cubic Out"),
	CubicInOut			UMETA(DisplayName = "Cubic In Out"),
	ExpoIn				UMETA(DisplayName = "Cubic In"),
	ExpoOut				UMETA(DisplayName = "Expo Out"),
	ExpoInOut			UMETA(DisplayName = "Expo In Out"),
	ECsEasingType_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsEasingType : public TCsEnumMap<ECsEasingType>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsEasingType, ECsEasingType)
};

namespace NCsEasingType
{
	typedef ECsEasingType Type;

	namespace Ref
	{
		extern CSCORE_API const Type Linear;
		extern CSCORE_API const Type BounceIn;
		extern CSCORE_API const Type BounceOut;
		extern CSCORE_API const Type BounceInOut;
		extern CSCORE_API const Type CubicIn;
		extern CSCORE_API const Type CubicOut;
		extern CSCORE_API const Type CubicInOut;
		extern CSCORE_API const Type ExpoIn;
		extern CSCORE_API const Type ExpoOut;
		extern CSCORE_API const Type ExpoInOut;
		extern CSCORE_API const Type ECsEasingType_MAX;
	}
}

#pragma endregion EasingType

// Easing Function (Time, Start, Final, Duration)
typedef float(*TCsEasingFunction)(const float&, const float&, const float&, const float&);

// InterpolatingMethod
#pragma region

/**
*/
UENUM(BlueprintType)
enum class ECsInterpolatingMethod : uint8
{
	Easing						UMETA(DisplayName = "Easing"),
	Curve						UMETA(DisplayName = "Curve"),
	Custom						UMETA(DisplayName = "Custom"),
	ECsInterpolatingMethod_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsInterpolatingMethod : public TCsEnumMap<ECsInterpolatingMethod>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsInterpolatingMethod, ECsInterpolatingMethod)
};

namespace NCsInterpolatingMethod
{
	typedef ECsInterpolatingMethod Type;

	namespace Ref
	{
		extern CSCORE_API const Type Easing;
		extern CSCORE_API const Type Curve;
		extern CSCORE_API const Type Custom;
		extern CSCORE_API const Type ECsInterpolatingMethod_MAX;
	}
}

#pragma endregion InterpolatingMethod
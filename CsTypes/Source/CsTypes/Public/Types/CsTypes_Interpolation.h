// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CsMacro_Proxy.h"
#include "Types/Enum/CsEnumMap.h"

#include "CsTypes_Interpolation.generated.h"

USTRUCT()
struct CSTYPES_API FCsTypes_Interpolation_STUB
{
	GENERATED_USTRUCT_BODY()

	FCsTypes_Interpolation_STUB()
	{
	}
};

// BlendDirection
#pragma region

/**
* Describes the direction a value should be interpolated / blended.
*/
UENUM(BlueprintType)
enum class ECsBlendDirection : uint8
{
	In						UMETA(DisplayName = "In"),
	Out						UMETA(DisplayName = "Out"),
	ECsBlendDirection_MAX	UMETA(Hidden),
};

struct CSTYPES_API EMCsBlendDirection : public TCsEnumMap<ECsBlendDirection>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsBlendDirection, ECsBlendDirection)
};

namespace NCsBlendDirection
{
	namespace Ref
	{
		typedef ECsBlendDirection Type;

		extern CSTYPES_API const Type In;
		extern CSTYPES_API const Type Out;
		extern CSTYPES_API const Type ECsBlendDirection_MAX;
	}
}

#pragma endregion BlendDirection

// EasingType
#pragma region

/**
* Describes which easing method / function should be used for interpolating a value.
*/
UENUM(BlueprintType)
enum class ECsEasingType : uint8
{
	Linear				UMETA(DisplayName = "Linear"),
	BounceIn			UMETA(DisplayName = "Bounce In"),
	BounceOut			UMETA(DisplayName = "Bounce Out"),
	BounceInOut			UMETA(DisplayName = "Bounce In Out"),
	QuadIn				UMETA(DisplayName = "Quad In"),
	QuadOut				UMETA(DisplayName = "Quad Out"),
	QuadInOut			UMETA(DisplayName = "Quad In Out"),
	CubicIn				UMETA(DisplayName = "Cubic In"),
	CubicOut			UMETA(DisplayName = "Cubic Out"),
	CubicInOut			UMETA(DisplayName = "Cubic In Out"),
	ExpoIn				UMETA(DisplayName = "Expo In"),
	ExpoOut				UMETA(DisplayName = "Expo Out"),
	ExpoInOut			UMETA(DisplayName = "Expo In Out"),
	BackIn				UMETA(DisplayName = "Back In"),
	BackOut				UMETA(DisplayName = "Back Out"),
	BackInOut			UMETA(DisplayName = "Back In Out"),
	ElasticIn			UMETA(DisplayName = "Elastic In"),
	ElasticOut			UMETA(DisplayName = "Elastic Out"),
	ElasticInOut		UMETA(DisplayName = "Elastic In Out"),
	ECsEasingType_MAX	UMETA(Hidden),
};

struct CSTYPES_API EMCsEasingType : public TCsEnumMap<ECsEasingType>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsEasingType, ECsEasingType)
};

namespace NCsEasingType
{
	typedef ECsEasingType Type;

	namespace Ref
	{
		extern CSTYPES_API const Type Linear;
		extern CSTYPES_API const Type BounceIn;
		extern CSTYPES_API const Type BounceOut;
		extern CSTYPES_API const Type BounceInOut;
		extern CSTYPES_API const Type QuadIn;
		extern CSTYPES_API const Type QuadOut;
		extern CSTYPES_API const Type QuadInOut;
		extern CSTYPES_API const Type CubicIn;
		extern CSTYPES_API const Type CubicOut;
		extern CSTYPES_API const Type CubicInOut;
		extern CSTYPES_API const Type ExpoIn;
		extern CSTYPES_API const Type ExpoOut;
		extern CSTYPES_API const Type ExpoInOut;
		extern CSTYPES_API const Type BackIn;
		extern CSTYPES_API const Type BackOut;
		extern CSTYPES_API const Type BackInOut;
		extern CSTYPES_API const Type ElasticIn;
		extern CSTYPES_API const Type ElasticOut;
		extern CSTYPES_API const Type ElasticInOut;
		extern CSTYPES_API const Type ECsEasingType_MAX;
	}
}

#pragma endregion EasingType

// Easing Function (Time, Start, Final, Duration)
typedef float(*TCsEasingFunction)(const float&, const float&, const float&, const float&);

// InterpolatingMethod
#pragma region

/**
* Describes with method to use for interpolating a set of values.
*/
UENUM(BlueprintType)
enum class ECsInterpolatingMethod : uint8
{
	Easing						UMETA(DisplayName = "Easing"),
	Curve						UMETA(DisplayName = "Curve"),
	Custom						UMETA(DisplayName = "Custom"),
	ECsInterpolatingMethod_MAX	UMETA(Hidden),
};

struct CSTYPES_API EMCsInterpolatingMethod : public TCsEnumMap<ECsInterpolatingMethod>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsInterpolatingMethod, ECsInterpolatingMethod)
};

namespace NCsInterpolatingMethod
{
	typedef ECsInterpolatingMethod Type;

	namespace Ref
	{
		extern CSTYPES_API const Type Easing;
		extern CSTYPES_API const Type Curve;
		extern CSTYPES_API const Type Custom;
		extern CSTYPES_API const Type ECsInterpolatingMethod_MAX;
	}
}

#pragma endregion InterpolatingMethod
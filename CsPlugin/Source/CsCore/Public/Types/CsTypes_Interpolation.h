// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Types/Enum/CsEnumMap.h"
// Log
#include "Utility/CsLog.h"

//#include "CsTypes_Interpolation.generated.h"

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
		extern CSCORE_API const Type QuadIn;
		extern CSCORE_API const Type QuadOut;
		extern CSCORE_API const Type QuadInOut;
		extern CSCORE_API const Type CubicIn;
		extern CSCORE_API const Type CubicOut;
		extern CSCORE_API const Type CubicInOut;
		extern CSCORE_API const Type ExpoIn;
		extern CSCORE_API const Type ExpoOut;
		extern CSCORE_API const Type ExpoInOut;
		extern CSCORE_API const Type BackIn;
		extern CSCORE_API const Type BackOut;
		extern CSCORE_API const Type BackInOut;
		extern CSCORE_API const Type ElasticIn;
		extern CSCORE_API const Type ElasticOut;
		extern CSCORE_API const Type ElasticInOut;
		extern CSCORE_API const Type ECsEasingType_MAX;
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

namespace NCsEasing
{
	struct CSCORE_API FFloat
	{
	private:

		CS_DECLARE_MEMBER_WITH_PROXY(Type, ECsEasingType)
		CS_DECLARE_MEMBER_WITH_PROXY(Min, float)
		CS_DECLARE_MEMBER_WITH_PROXY(Max, float)

	public:

		FFloat() :
			CS_CTOR_INIT_MEMBER_WITH_PROXY(Type, ECsEasingType::Linear),
			CS_CTOR_INIT_MEMBER_WITH_PROXY(Min, 0.0f),
			CS_CTOR_INIT_MEMBER_WITH_PROXY(Max, 0.0f)
		{
			CS_CTOR_SET_MEMBER_PROXY(Type);
			CS_CTOR_SET_MEMBER_PROXY(Min);
			CS_CTOR_SET_MEMBER_PROXY(Max);
		}

		CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Type, ECsEasingType)
		CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Min, float)
		CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Max, float)

		bool IsValidChecked(const FString& Context) const;
		bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

		float Ease(const float& Alpha) const;
	};
}
// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Primitive.h"

//#include "CsTypes_Interpolation.generated.h"
#pragma once

// BlendDirection
#pragma region

UENUM(BlueprintType)
enum class ECsBlendDirection : uint8
{
	In						UMETA(DisplayName = "In"),
	Out						UMETA(DisplayName = "Out"),
	ECsBlendDirection_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsBlendDirection : public TCsEnumMap<ECsBlendDirection>
{
protected:
	EMCsBlendDirection() {}
	EMCsBlendDirection(const EMCsBlendDirection &) = delete;
	EMCsBlendDirection(EMCsBlendDirection &&) = delete;
public:
	~EMCsBlendDirection() {}
private:
	static EMCsBlendDirection* Instance;

public:
	static EMCsBlendDirection& Get();
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
protected:
	EMCsEasingType() {}
	EMCsEasingType(const EMCsEasingType &) = delete;
	EMCsEasingType(EMCsEasingType &&) = delete;
public:
	~EMCsEasingType() {}
private:
	static EMCsEasingType* Instance;

public:
	static EMCsEasingType& Get();
};

namespace NCsEasingType
{
	namespace Ref
	{
		typedef ECsEasingType Type;

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
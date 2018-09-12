// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
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

UENUM(BlueprintType)
namespace ECsEasingType
{
	enum Type
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
}

namespace ECsEasingType
{
	typedef TCsProperty_Multi_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString Linear = TCsString(TEXT("Linear"), TEXT("linear"), TEXT("linear"));
		const TCsString BounceIn = TCsString(TEXT("BounceIn"), TEXT("bouncein"), TEXT("bounce in"));
		const TCsString BounceOut = TCsString(TEXT("BounceOut"), TEXT("bounceout"), TEXT("bounce out"));
		const TCsString BounceInOut = TCsString(TEXT("BounceInOut"), TEXT("bounceinout"), TEXT("bounce in out"));
		const TCsString CubicIn = TCsString(TEXT("CubicIn"), TEXT("cubicin"), TEXT("cubic in"));
		const TCsString CubicOut = TCsString(TEXT("CubicOut"), TEXT("cubicout"), TEXT("cubic out"));
		const TCsString CubicInOut = TCsString(TEXT("CubicInOut"), TEXT("cubicinout"), TEXT("cubic in out"));
		const TCsString ExpoIn = TCsString(TEXT("ExpoIn"), TEXT("expoin"), TEXT("expo in"));
		const TCsString ExpoOut = TCsString(TEXT("ExpoOut"), TEXT("expoout"), TEXT("expo out"));
		const TCsString ExpoInOut = TCsString(TEXT("ExpoInOut"), TEXT("expoinout"), TEXT("expo in out"));
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		if (EType == Type::Linear) { return Str::Linear.Value; }
		if (EType == Type::BounceIn) { return Str::BounceIn.Value; }
		if (EType == Type::BounceOut) { return Str::BounceOut.Value; }
		if (EType == Type::BounceInOut) { return Str::BounceInOut.Value; }
		if (EType == Type::CubicIn) { return Str::CubicIn.Value; }
		if (EType == Type::CubicOut) { return Str::CubicOut.Value; }
		if (EType == Type::CubicInOut) { return Str::CubicInOut.Value; }
		if (EType == Type::ExpoIn) { return Str::ExpoIn.Value; }
		if (EType == Type::ExpoOut) { return Str::ExpoOut.Value; }
		if (EType == Type::ExpoInOut) { return Str::ExpoInOut.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::Linear) { return Type::Linear; }
		if (String == Str::BounceIn) { return Type::BounceIn; }
		if (String == Str::BounceOut) { return Type::BounceOut; }
		if (String == Str::BounceInOut) { return Type::BounceInOut; }
		if (String == Str::CubicIn) { return Type::CubicIn; }
		if (String == Str::CubicOut) { return Type::CubicOut; }
		if (String == Str::CubicInOut) { return Type::CubicInOut; }
		if (String == Str::ExpoIn) { return Type::ExpoIn; }
		if (String == Str::ExpoOut) { return Type::ExpoOut; }
		if (String == Str::ExpoInOut) { return Type::ExpoInOut; }
		return Type::ECsEasingType_MAX;
	}
}

#define ECS_EASING_TYPE_MAX (uint8)ECsEasingType::ECsEasingType_MAX
typedef ECsEasingType::Type TCsEasingType;

// Easing Function (Time, Start, Final, Duration)
typedef float(*TCsEasingFunction)(const float&, const float&, const float&, const float&);
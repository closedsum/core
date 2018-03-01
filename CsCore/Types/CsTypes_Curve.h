// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Load.h"

#include "Curves/CurveFloat.h"
#include "Curves/CurveVector.h"

#include "CsTypes_Curve.generated.h"
#pragma once

// Curves
#pragma region

// UCurveFloat
USTRUCT(BlueprintType)
struct FCsCurveFloat
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Curves")
	TAssetPtr<UCurveFloat> Curve;

	UPROPERTY(EditAnywhere, Category = "Curves", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Curve_LoadFlags;

private:
	UPROPERTY(Transient)
	class UCurveFloat* Curve_Internal;

public:
	FCsCurveFloat()
	{
		CS_SET_BLUEPRINT_BITFLAG(Curve_LoadFlags, ECsLoadFlags::Game);
	}

	FCsCurveFloat& operator=(const FCsCurveFloat& B)
	{
		Curve = B.Curve;
		Curve_LoadFlags = B.Curve_LoadFlags;
		Curve_Internal = B.Curve_Internal;
		return *this;
	}

	bool operator==(const FCsCurveFloat& B) const
	{
		return Curve == B.Curve && Curve_LoadFlags == B.Curve_LoadFlags && Curve_Internal == B.Curve_Internal;
	}

	bool operator!=(const FCsCurveFloat& B) const
	{
		return !(*this == B);
	}

	UCurveFloat* Get() const
	{
		return Curve_Internal;
	}
};

// UCurveVector
USTRUCT()
struct FCsCurveVector
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Curves")
	TAssetPtr<UCurveVector> Curve;

	UPROPERTY(EditAnywhere, Category = "Curves", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Curve_LoadFlags;

private:
	UPROPERTY(Transient)
	class UCurveVector* Curve_Internal;

public:
	FCsCurveVector()
	{
		CS_SET_BLUEPRINT_BITFLAG(Curve_LoadFlags, ECsLoadFlags::Game);
	}

	FCsCurveVector& operator=(const FCsCurveVector& B)
	{
		Curve = B.Curve;
		Curve_LoadFlags = B.Curve_LoadFlags;
		Curve_Internal = B.Curve_Internal;
		return *this;
	}

	bool operator==(const FCsCurveVector& B) const
	{
		return Curve == B.Curve && Curve_LoadFlags == B.Curve_LoadFlags && Curve_Internal == B.Curve_Internal;
	}

	bool operator!=(const FCsCurveVector& B) const
	{
		return !(*this == B);
	}

	UCurveVector* Get() const
	{
		return Curve_Internal;
	}
};

UENUM(BlueprintType)
namespace ECsRichCurveInterpMode
{
	enum Type
	{
		RCIM_Linear					UMETA(DisplayName = "Linear"),
		RCIM_Constant				UMETA(DisplayName = "Constant"),
		RCIM_Cubic					UMETA(DisplayName = "Cubic"),
		RCIM_None					UMETA(DisplayName = "None"),
		ECsRichCurveInterpMode_MAX	UMETA(Hidden),
	};
}

namespace ECsRichCurveInterpMode
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString RCIM_Linear = TCsString(TEXT("RCIM_Linear"), TEXT("rcim_linear"), TEXT("linear"));
		const TCsString RCIM_Constant = TCsString(TEXT("RCIM_Constant"), TEXT("rcim_constant"), TEXT("constant"));
		const TCsString RCIM_Cubic = TCsString(TEXT("RCIM_Cubic"), TEXT("rcim_cubic"), TEXT("cubic"));
		const TCsString RCIM_None = TCsString(TEXT("RCIM_None"), TEXT("rcim_none"), TEXT("none"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::RCIM_Linear) { return Str::RCIM_Linear.Value; }
		if (EType == Type::RCIM_Constant) { return Str::RCIM_Constant.Value; }
		if (EType == Type::RCIM_Cubic) { return Str::RCIM_Cubic.Value; }
		if (EType == Type::RCIM_None) { return Str::RCIM_None.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE FString ToString(const ERichCurveInterpMode &EType)
	{
		if (EType == ERichCurveInterpMode::RCIM_Linear) { return Str::RCIM_Linear.Value; }
		if (EType == ERichCurveInterpMode::RCIM_Constant) { return Str::RCIM_Constant.Value; }
		if (EType == ERichCurveInterpMode::RCIM_Cubic) { return Str::RCIM_Cubic.Value; }
		if (EType == ERichCurveInterpMode::RCIM_None) { return Str::RCIM_None.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::RCIM_Linear) { return Type::RCIM_Linear; }
		if (String == Str::RCIM_Constant) { return Type::RCIM_Constant; }
		if (String == Str::RCIM_Cubic) { return Type::RCIM_Cubic; }
		if (String == Str::RCIM_None) { return Type::RCIM_None; }
		return Type::ECsRichCurveInterpMode_MAX;
	}

	FORCEINLINE ERichCurveInterpMode ToBaseType(const FString &String)
	{
		if (String == Str::RCIM_Linear) { return ERichCurveInterpMode::RCIM_Linear; }
		if (String == Str::RCIM_Constant) { return ERichCurveInterpMode::RCIM_Constant; }
		if (String == Str::RCIM_Cubic) { return ERichCurveInterpMode::RCIM_Cubic; }
		if (String == Str::RCIM_None) { return ERichCurveInterpMode::RCIM_None; }
		return ERichCurveInterpMode::RCIM_None;
	}
}

#define ECS_RICH_CURVE_INTERP_MODE_MAX (uint8)ECsRichCurveInterpMode::ABPT_MAX
typedef ECsRichCurveInterpMode::Type TCsRichCurveInterpMode;

UENUM(BlueprintType)
namespace ECsRichCurveTangentMode
{
	enum Type
	{
		RCTM_Auto					UMETA(DisplayName = "Auto"),
		RCTM_User					UMETA(DisplayName = "User"),
		RCTM_Break					UMETA(DisplayName = "Break"),
		RCTM_None					UMETA(DisplayName = "None"),
		ECsRichCurveTangentMode_MAX	UMETA(Hidden),
	};
}

namespace ECsRichCurveTangentMode
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString RCTM_Auto = TCsString(TEXT("RCTM_Auto"), TEXT("rctm_auto"), TEXT("auto"));
		const TCsString RCTM_User = TCsString(TEXT("RCTM_User"), TEXT("rctm_user"), TEXT("user"));
		const TCsString RCTM_Break = TCsString(TEXT("RCTM_Break"), TEXT("rctm_break"), TEXT("break"));
		const TCsString RCTM_None = TCsString(TEXT("RCTM_None"), TEXT("rctm_none"), TEXT("none"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::RCTM_Auto) { return Str::RCTM_Auto.Value; }
		if (EType == Type::RCTM_User) { return Str::RCTM_User.Value; }
		if (EType == Type::RCTM_Break) { return Str::RCTM_Break.Value; }
		if (EType == Type::RCTM_None) { return Str::RCTM_None.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE FString ToString(const ERichCurveTangentMode &EType)
	{
		if (EType == ERichCurveTangentMode::RCTM_Auto) { return Str::RCTM_Auto.Value; }
		if (EType == ERichCurveTangentMode::RCTM_User) { return Str::RCTM_User.Value; }
		if (EType == ERichCurveTangentMode::RCTM_Break) { return Str::RCTM_Break.Value; }
		if (EType == ERichCurveTangentMode::RCTM_None) { return Str::RCTM_None.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::RCTM_Auto) { return Type::RCTM_Auto; }
		if (String == Str::RCTM_User) { return Type::RCTM_User; }
		if (String == Str::RCTM_Break) { return Type::RCTM_Break; }
		if (String == Str::RCTM_None) { return Type::RCTM_None; }
		return Type::ECsRichCurveTangentMode_MAX;
	}

	FORCEINLINE ERichCurveTangentMode ToBaseType(const FString &String)
	{
		if (String == Str::RCTM_Auto) { return ERichCurveTangentMode::RCTM_Auto; }
		if (String == Str::RCTM_User) { return ERichCurveTangentMode::RCTM_User; }
		if (String == Str::RCTM_Break) { return ERichCurveTangentMode::RCTM_Break; }
		if (String == Str::RCTM_None) { return ERichCurveTangentMode::RCTM_None; }
		return ERichCurveTangentMode::RCTM_None;
	}
}

#define ECS_RICH_CURVE_TANGENT_MODE_MAX (uint8)ECsRichCurveTangentMode::ABPT_MAX
typedef ECsRichCurveTangentMode::Type TCsRichCurveTangentMode;

#pragma endregion Curves
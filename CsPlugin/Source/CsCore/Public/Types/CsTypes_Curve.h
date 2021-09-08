// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsEnumMap.h"
#include "Curves/RealCurve.h"

#include "CsTypes_Curve.generated.h"
#pragma once

// UCurveFloat
#pragma region

class UCurveFloat;

USTRUCT(BlueprintType)
struct CSCORE_API FCsCurveFloat
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UCurveFloat> Curve;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Curve_LoadFlags;

	UPROPERTY(Transient, BlueprintReadOnly)
	UCurveFloat* Curve_Internal;

public:
	FCsCurveFloat() :
		Curve(nullptr),
		Curve_LoadFlags(0),
		Curve_Internal(nullptr)
	{
	}

	FORCEINLINE bool operator==(const FCsCurveFloat& B) const
	{
		return Curve == B.Curve && Curve_LoadFlags == B.Curve_LoadFlags && Curve_Internal == B.Curve_Internal;
	}

	FORCEINLINE bool operator!=(const FCsCurveFloat& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE UCurveFloat* Get() const
	{
		return Curve_Internal;
	}
};

#pragma endregion UCurveFloat

// FCsCurveVector
#pragma region

class UCurveVector;

USTRUCT(BlueprintType)
struct CSCORE_API FCsCurveVector
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UCurveVector> Curve;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Curve_LoadFlags;

	UPROPERTY(Transient, BlueprintReadOnly)
	UCurveVector* Curve_Internal;

public:

	FCsCurveVector() :
		Curve(nullptr),
		Curve_LoadFlags(0),
		Curve_Internal(nullptr)
	{
	}

	FORCEINLINE bool operator==(const FCsCurveVector& B) const
	{
		return Curve == B.Curve && Curve_LoadFlags == B.Curve_LoadFlags && Curve_Internal == B.Curve_Internal;
	}

	FORCEINLINE bool operator!=(const FCsCurveVector& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE UCurveVector* Get() const
	{
		return Curve_Internal;
	}
};

#pragma endregion FCsCurveVector

// RichCurveInterpMode
#pragma region

UENUM(BlueprintType)
enum class ECsRichCurveInterpMode : uint8
{
	RCIM_Linear					UMETA(DisplayName = "Linear"),
	RCIM_Constant				UMETA(DisplayName = "Constant"),
	RCIM_Cubic					UMETA(DisplayName = "Cubic"),
	RCIM_None					UMETA(DisplayName = "None"),
	ECsRichCurveInterpMode_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsRichCurveInterpMode : public TCsEnumMap<ECsRichCurveInterpMode>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsRichCurveInterpMode, ECsRichCurveInterpMode)
};

namespace NCsRichCurveInterpMode
{
	typedef ECsRichCurveInterpMode Type;

	namespace Ref
	{
		extern CSCORE_API const Type RCIM_Linear;
		extern CSCORE_API const Type RCIM_Constant;
		extern CSCORE_API const Type RCIM_Cubic;
		extern CSCORE_API const Type RCIM_None;
		extern CSCORE_API const Type ECsRichCurveInterpMode_MAX;
	}

	FORCEINLINE const FString& ToString(const ERichCurveInterpMode &EType)
	{
		if (EType == ERichCurveInterpMode::RCIM_Linear) { return EMCsRichCurveInterpMode::Get().ToString(Ref::RCIM_Linear); }
		if (EType == ERichCurveInterpMode::RCIM_Constant) { return EMCsRichCurveInterpMode::Get().ToString(Ref::RCIM_Constant); }
		if (EType == ERichCurveInterpMode::RCIM_Cubic) { return EMCsRichCurveInterpMode::Get().ToString(Ref::RCIM_Cubic); }
		if (EType == ERichCurveInterpMode::RCIM_None) { return EMCsRichCurveInterpMode::Get().ToString(Ref::RCIM_None); }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE ERichCurveInterpMode ToBaseType(const FString &String)
	{
		const Type& Enum = EMCsRichCurveInterpMode::Get().ToType(String);

		if (Enum == Ref::RCIM_Linear) { return ERichCurveInterpMode::RCIM_Linear; }
		if (Enum == Ref::RCIM_Constant) { return ERichCurveInterpMode::RCIM_Constant; }
		if (Enum == Ref::RCIM_Cubic) { return ERichCurveInterpMode::RCIM_Cubic; }
		if (Enum == Ref::RCIM_None) { return ERichCurveInterpMode::RCIM_None; }
		return ERichCurveInterpMode::RCIM_None;
	}
}

#pragma endregion RichCurveInterpMode

// RichCurveTangentMode
#pragma region

UENUM(BlueprintType)
enum class ECsRichCurveTangentMode : uint8
{
	RCTM_Auto					UMETA(DisplayName = "Auto"),
	RCTM_User					UMETA(DisplayName = "User"),
	RCTM_Break					UMETA(DisplayName = "Break"),
	RCTM_None					UMETA(DisplayName = "None"),
	ECsRichCurveTangentMode_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsRichCurveTangentMode : public TCsEnumMap<ECsRichCurveTangentMode>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsRichCurveTangentMode, ECsRichCurveTangentMode)
};

namespace NCsRichCurveTangentMode
{
	typedef ECsRichCurveTangentMode Type;

	namespace Ref
	{
		extern CSCORE_API const Type RCTM_Auto;
		extern CSCORE_API const Type RCTM_User;
		extern CSCORE_API const Type RCTM_Break;
		extern CSCORE_API const Type RCTM_None;
		extern CSCORE_API const Type ECsRichCurveTangentMode_MAX;
	}

	FORCEINLINE const FString& ToString(const ERichCurveTangentMode &EType)
	{
		if (EType == ERichCurveTangentMode::RCTM_Auto) { return EMCsRichCurveTangentMode::Get().ToString(Ref::RCTM_Auto); }
		if (EType == ERichCurveTangentMode::RCTM_User) { return EMCsRichCurveTangentMode::Get().ToString(Ref::RCTM_User); }
		if (EType == ERichCurveTangentMode::RCTM_Break) { return EMCsRichCurveTangentMode::Get().ToString(Ref::RCTM_Break); }
		if (EType == ERichCurveTangentMode::RCTM_None) { return EMCsRichCurveTangentMode::Get().ToString(Ref::RCTM_None); }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE ERichCurveTangentMode ToBaseType(const FString &String)
	{
		const Type& Enum = EMCsRichCurveTangentMode::Get().ToType(String);

		if (Enum == Ref::RCTM_Auto) { return ERichCurveTangentMode::RCTM_Auto; }
		if (Enum == Ref::RCTM_User) { return ERichCurveTangentMode::RCTM_User; }
		if (Enum == Ref::RCTM_Break) { return ERichCurveTangentMode::RCTM_Break; }
		if (Enum == Ref::RCTM_None) { return ERichCurveTangentMode::RCTM_None; }
		return ERichCurveTangentMode::RCTM_None;
	}
}

#pragma endregion RichCurveTangentMode
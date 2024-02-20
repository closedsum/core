// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Struct/CsTypes_StructOps.h"
#include "Types/Enum/CsEnumMap.h"
#include "Curves/RealCurve.h"
// Log
#include "Utility/CsLog.h"

#include "CsTypes_Curve.generated.h"

// FCsCurve
#pragma region

class UCurveBase;

USTRUCT(BlueprintType)
struct CSCORE_API FCsCurve
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Curve")
	TSoftObjectPtr<UCurveBase> Curve;

	UPROPERTY(BlueprintReadOnly, Category = "CsCore|Curve", meta = (Bitmask, BitmaskEnum = "/Script/CsCore.ECsLoadFlags"))
	int32 Curve_LoadFlags;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsCore|Curve")
	UCurveBase* Curve_Internal;

public:

	FCsCurve() :
		Curve(nullptr),
		Curve_LoadFlags(0),
		Curve_Internal(nullptr)
	{
	}

	/**
	* Get the Hard reference to the UCurveBase asset.
	*
	* return Curve
	*/
	FORCEINLINE UCurveBase* Get() const { return Curve_Internal; }

	/**
	* Get the pointer to the Hard reference to the UCurveBase asset.
	*
	* return Curve
	*/
	FORCEINLINE UCurveBase** GetPtr() { return &Curve_Internal; }

	/**
	* Get the Hard reference to the UCurveBase asset.
	*
	* @param Context	The calling context.
	* return			Curve
	*/
	FORCEINLINE UCurveBase* GetChecked(const FString& Context) const
	{
		checkf(Curve.ToSoftObjectPath().IsValid(), TEXT("%s: Curve's Path is NOT Valid."), *Context);
		checkf(Curve_Internal, TEXT("%s: Curve has NOT been loaded from Path @ %s."), *Context, *(Curve.ToSoftObjectPath().ToString()));

		return Curve_Internal;
	}

	/**
	* Get the Hard reference to the UCurveBase asset.
	*
	* return Curve
	*/
	FORCEINLINE UCurveBase* GetChecked() const
	{
		checkf(Curve.ToSoftObjectPath().IsValid(), TEXT("FCsCurve::GetChecked: Curve's Path is NOT Valid."));
		checkf(Curve_Internal, TEXT("FCsCurve::GetChecked: Curve has NOT been loaded from Path @ %s."), *(Curve.ToSoftObjectPath().ToString()));

		return Curve_Internal;
	}

	/**
	* Safely get the Hard reference to the UCurveBase asset.
	*
	* @param Context	The calling context.
	* @param Log		(optional)
	* return			Curve
	*/
	UCurveBase* GetSafe(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
	{
		if (!Curve.ToSoftObjectPath().IsValid())
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Curve's Path is NOT Valid."), *Context));
			return nullptr;
		}

		if (!Curve_Internal)
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Curve has NOT been loaded from Path @ %s."), *Context, *(Curve.ToSoftObjectPath().ToString())));
		}
		return Curve_Internal;
	}

	/**
	* Safely get the Hard reference to the UCurveBase asset.
	*
	* return Curve
	*/
	UCurveBase* GetSafe()
	{
		if (!Curve.ToSoftObjectPath().IsValid())
			return nullptr;
		return Curve_Internal;
	}

	CS_STRUCT_OPS_IS_VALID_CHECKED(FCsCurve)
	CS_STRUCT_OPS_IS_VALID(FCsCurve)
	CS_STRUCT_OPS_IS_TOP_VALID_CHECKED(FCsCurve)
	CS_STRUCT_OPS_IS_TOP_VALID(FCsCurve)

	FORCEINLINE bool IsValidChecked(const FString& Context) const
	{
		check(GetChecked(Context));
		return true;
	}

	FORCEINLINE bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
	{
		if (!GetSafe(Context, Log))
			return false;
		return true;
	}

	FORCEINLINE bool IsTopValidChecked(const FString& Context) const
	{
		checkf(Curve.ToSoftObjectPath().IsValid(), TEXT("%s: Curve's Path is NOT Valid."), *Context);
		return true;
	}

	FORCEINLINE bool IsTopValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
	{
		if (!Curve.ToSoftObjectPath().IsValid())
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Curve's Path is NOT Valid."), *Context));
			return false;
		}
		return true;
	}

	CS_STRUCT_OPS_DATA_UNLOAD(FCsCurve)

	FORCEINLINE void Unload()
	{
		Curve.ResetWeakPtr();
		Curve_Internal = nullptr;
	}
};

#pragma endregion FCsCurve

// FCsCurveFloat
#pragma region

class UCurveFloat;

USTRUCT(BlueprintType)
struct CSCORE_API FCsCurveFloat
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Curve")
	TSoftObjectPtr<UCurveFloat> Curve;

	UPROPERTY(BlueprintReadOnly, Category = "CsCore|Curve", meta = (Bitmask, BitmaskEnum = "/Script/CsCore.ECsLoadFlags"))
	int32 Curve_LoadFlags;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsCore|Curve")
	UCurveFloat* Curve_Internal;

public:

	FCsCurveFloat() :
		Curve(nullptr),
		Curve_LoadFlags(0),
		Curve_Internal(nullptr)
	{
	}

	/**
	* Get the Hard reference to the UCurveFloat asset.
	*
	* return Curve Float
	*/
	FORCEINLINE UCurveFloat* Get() const { return Curve_Internal; }

	/**
	* Get the pointer to the Hard reference to the UCurveFloat asset.
	*
	* return Curve Float
	*/
	FORCEINLINE UCurveFloat** GetPtr() { return &Curve_Internal; }

	/**
	* Get the Hard reference to the UCurveFloat asset.
	*
	* @param Context	The calling context.
	* return			Curve Float
	*/
	FORCEINLINE UCurveFloat* GetChecked(const FString& Context) const
	{
		checkf(Curve.ToSoftObjectPath().IsValid(), TEXT("%s: Curve's Path is NOT Valid."), *Context);
		checkf(Curve_Internal, TEXT("%s: Curve has NOT been loaded from Path @ %s."), *Context, *(Curve.ToSoftObjectPath().ToString()));

		return Curve_Internal;
	}

	/**
	* Get the Hard reference to the UCurveFloat asset.
	*
	* return Curve Float
	*/
	FORCEINLINE UCurveFloat* GetChecked() const
	{
		checkf(Curve.ToSoftObjectPath().IsValid(), TEXT("FCsMaterialInterface::GetChecked: Curve's Path is NOT Valid."));
		checkf(Curve_Internal, TEXT("FCsMaterialInterface::GetChecked: Curve has NOT been loaded from Path @ %s."), *(Curve.ToSoftObjectPath().ToString()));

		return Curve_Internal;
	}

	/**
	* Safely get the Hard reference to the UCurveFloat asset.
	*
	* @param Context	The calling context.
	* @param Log		(optional)
	* return			Curve Float
	*/
	UCurveFloat* GetSafe(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
	{
		if (!Curve.ToSoftObjectPath().IsValid())
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Curve's Path is NOT Valid."), *Context));
			return nullptr;
		}

		if (!Curve_Internal)
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Curve has NOT been loaded from Path @ %s."), *Context, *(Curve.ToSoftObjectPath().ToString())));
		}
		return Curve_Internal;
	}

	/**
	* Safely get the Hard reference to the UCurveFloat asset.
	*
	* return Curve Float
	*/
	UCurveFloat* GetSafe()
	{
		if (!Curve.ToSoftObjectPath().IsValid())
			return nullptr;
		return Curve_Internal;
	}

	CS_STRUCT_OPS_IS_VALID_CHECKED(FCsCurveFloat)
	CS_STRUCT_OPS_IS_VALID(FCsCurveFloat)
	CS_STRUCT_OPS_IS_TOP_VALID_CHECKED(FCsCurveFloat)
	CS_STRUCT_OPS_IS_TOP_VALID(FCsCurveFloat)

	FORCEINLINE bool IsValidChecked(const FString& Context) const
	{
		check(GetChecked(Context));
		return true;
	}

	FORCEINLINE bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
	{
		if (!GetSafe(Context, Log))
			return false;
		return true;
	}

	FORCEINLINE bool IsTopValidChecked(const FString& Context) const
	{
		checkf(Curve.ToSoftObjectPath().IsValid(), TEXT("%s: Curve's Path is NOT Valid."), *Context);
		return true;
	}

	FORCEINLINE bool IsTopValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
	{
		if (!Curve.ToSoftObjectPath().IsValid())
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Curve's Path is NOT Valid."), *Context));
			return false;
		}
		return true;
	}

	CS_STRUCT_OPS_DATA_UNLOAD(FCsCurveFloat)

	FORCEINLINE void Unload()
	{
		Curve.ResetWeakPtr();
		Curve_Internal = nullptr;
	}
};

#pragma endregion FCsCurveFloat

// FCsCurveVector
#pragma region

class UCurveVector;

USTRUCT(BlueprintType)
struct CSCORE_API FCsCurveVector
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Curve")
	TSoftObjectPtr<UCurveVector> Curve;

	UPROPERTY(BlueprintReadOnly, Category = "CsCore|Curve", meta = (Bitmask, BitmaskEnum = "/Script/CsCore.ECsLoadFlags"))
	int32 Curve_LoadFlags;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsCore|Curve")
	UCurveVector* Curve_Internal;

public:

	FCsCurveVector() :
		Curve(nullptr),
		Curve_LoadFlags(0),
		Curve_Internal(nullptr)
	{
	}

	/**
	* Get the Hard reference to the UCurveVector asset.
	*
	* return Curve Vector
	*/
	FORCEINLINE UCurveVector* Get() const { return Curve_Internal; }

	/**
	* Get the pointer to the Hard reference to the UCurveVector asset.
	*
	* return Curve Vector
	*/
	FORCEINLINE UCurveVector** GetPtr() { return &Curve_Internal; }

	/**
	* Get the Hard reference to the UCurveVector asset.
	*
	* @param Context	The calling context.
	* return			Curve Vector
	*/
	FORCEINLINE UCurveVector* GetChecked(const FString& Context) const
	{
		checkf(Curve.ToSoftObjectPath().IsValid(), TEXT("%s: Curve's Path is NOT Valid."), *Context);
		checkf(Curve_Internal, TEXT("%s: Curve has NOT been loaded from Path @ %s."), *Context, *(Curve.ToSoftObjectPath().ToString()));

		return Curve_Internal;
	}

	/**
	* Get the Hard reference to the UCurveVector asset.
	*
	* return Curve Float
	*/
	FORCEINLINE UCurveVector* GetChecked() const
	{
		checkf(Curve.ToSoftObjectPath().IsValid(), TEXT("FCsCurveVector::GetChecked: Curve's Path is NOT Valid."));
		checkf(Curve_Internal, TEXT("FCsCurveVector::GetChecked: Curve has NOT been loaded from Path @ %s."), *(Curve.ToSoftObjectPath().ToString()));

		return Curve_Internal;
	}

	/**
	* Safely get the Hard reference to the UCurveVector asset.
	*
	* @param Context	The calling context.
	* @param Log		(optional)
	* return			Curve Vector
	*/
	UCurveVector* GetSafe(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
	{
		if (!Curve.ToSoftObjectPath().IsValid())
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Curve's Path is NOT Valid."), *Context));
			return nullptr;
		}

		if (!Curve_Internal)
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Curve has NOT been loaded from Path @ %s."), *Context, *(Curve.ToSoftObjectPath().ToString())));
		}
		return Curve_Internal;
	}

	/**
	* Safely get the Hard reference to the UCurveVector asset.
	*
	* return Curve Vector
	*/
	UCurveVector* GetSafe()
	{
		if (!Curve.ToSoftObjectPath().IsValid())
			return nullptr;
		return Curve_Internal;
	}

	CS_STRUCT_OPS_IS_VALID_CHECKED(FCsCurveVector)
	CS_STRUCT_OPS_IS_VALID(FCsCurveVector)
	CS_STRUCT_OPS_IS_TOP_VALID_CHECKED(FCsCurveVector)
	CS_STRUCT_OPS_IS_TOP_VALID(FCsCurveVector)

	FORCEINLINE bool IsValidChecked(const FString& Context) const
	{
		check(GetChecked(Context));
		return true;
	}

	FORCEINLINE bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
	{
		if (!GetSafe(Context, Log))
			return false;
		return true;
	}

	FORCEINLINE bool IsTopValidChecked(const FString& Context) const
	{
		checkf(Curve.ToSoftObjectPath().IsValid(), TEXT("%s: Curve's Path is NOT Valid."), *Context);
		return true;
	}

	FORCEINLINE bool IsTopValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
	{
		if (!Curve.ToSoftObjectPath().IsValid())
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Curve's Path is NOT Valid."), *Context));
			return false;
		}
		return true;
	}

	CS_STRUCT_OPS_DATA_UNLOAD(FCsCurveVector)

	FORCEINLINE void Unload()
	{
		Curve.ResetWeakPtr();
		Curve_Internal = nullptr;
	}
};

#pragma endregion FCsCurveVector

// FCsCurveLinearColor
#pragma region

class UCurveLinearColor;

USTRUCT(BlueprintType)
struct CSCORE_API FCsCurveLinearColor
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Curve")
	TSoftObjectPtr<UCurveLinearColor> Curve;

	UPROPERTY(BlueprintReadOnly, Category = "CsCore|Curve", meta = (Bitmask, BitmaskEnum = "/Script/CsCore.ECsLoadFlags"))
	int32 Curve_LoadFlags;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsCore|Curve")
	UCurveLinearColor* Curve_Internal;

public:

	FCsCurveLinearColor() :
		Curve(nullptr),
		Curve_LoadFlags(0),
		Curve_Internal(nullptr)
	{
	}

	/**
	* Get the Hard reference to the UCurveLinearColor asset.
	*
	* return Curve Linear Color
	*/
	FORCEINLINE UCurveLinearColor* Get() const { return Curve_Internal; }

	/**
	* Get the pointer to the Hard reference to the UCurveLinearColor asset.
	*
	* return Curve Linear Color
	*/
	FORCEINLINE UCurveLinearColor** GetPtr() { return &Curve_Internal; }

	/**
	* Get the Hard reference to the UCurveLinearColor asset.
	*
	* @param Context	The calling context.
	* return			Curve Vector
	*/
	FORCEINLINE UCurveLinearColor* GetChecked(const FString& Context) const
	{
		checkf(Curve.ToSoftObjectPath().IsValid(), TEXT("%s: Curve's Path is NOT Valid."), *Context);
		checkf(Curve_Internal, TEXT("%s: Curve has NOT been loaded from Path @ %s."), *Context, *(Curve.ToSoftObjectPath().ToString()));

		return Curve_Internal;
	}

	/**
	* Get the Hard reference to the UCurveLinearColor asset.
	*
	* return Curve Linear Color
	*/
	FORCEINLINE UCurveLinearColor* GetChecked() const
	{
		checkf(Curve.ToSoftObjectPath().IsValid(), TEXT("FCsCurveLinearColor::GetChecked: Curve's Path is NOT Valid."));
		checkf(Curve_Internal, TEXT("FCsCurveLinearColor::GetChecked: Curve has NOT been loaded from Path @ %s."), *(Curve.ToSoftObjectPath().ToString()));

		return Curve_Internal;
	}

	/**
	* Safely get the Hard reference to the UCurveLinearColor asset.
	*
	* @param Context	The calling context.
	* @param Log		(optional)
	* return			Curve Linear Color
	*/
	UCurveLinearColor* GetSafe(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
	{
		if (!Curve.ToSoftObjectPath().IsValid())
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Curve's Path is NOT Valid."), *Context));
			return nullptr;
		}

		if (!Curve_Internal)
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Curve has NOT been loaded from Path @ %s."), *Context, *(Curve.ToSoftObjectPath().ToString())));
		}
		return Curve_Internal;
	}

	/**
	* Safely get the Hard reference to the UCurveVector asset.
	*
	* return Curve Vector
	*/
	UCurveLinearColor* GetSafe()
	{
		if (!Curve.ToSoftObjectPath().IsValid())
			return nullptr;
		return Curve_Internal;
	}

	CS_STRUCT_OPS_IS_VALID_CHECKED(FCsCurveLinearColor)
	CS_STRUCT_OPS_IS_VALID(FCsCurveLinearColor)
	CS_STRUCT_OPS_IS_TOP_VALID_CHECKED(FCsCurveLinearColor)
	CS_STRUCT_OPS_IS_TOP_VALID(FCsCurveLinearColor)

	FORCEINLINE bool IsValidChecked(const FString& Context) const
	{
		check(GetChecked(Context));
		return true;
	}

	FORCEINLINE bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
	{
		if (!GetSafe(Context, Log))
			return false;
		return true;
	}

	FORCEINLINE bool IsTopValidChecked(const FString& Context) const
	{
		checkf(Curve.ToSoftObjectPath().IsValid(), TEXT("%s: Curve's Path is NOT Valid."), *Context);
		return true;
	}

	FORCEINLINE bool IsTopValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
	{
		if (!Curve.ToSoftObjectPath().IsValid())
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Curve's Path is NOT Valid."), *Context));
			return false;
		}
		return true;
	}

	CS_STRUCT_OPS_DATA_UNLOAD(FCsCurveLinearColor)

	FORCEINLINE void Unload()
	{
		Curve.ResetWeakPtr();
		Curve_Internal = nullptr;
	}
};

#pragma endregion FCsCurveLinearColor

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
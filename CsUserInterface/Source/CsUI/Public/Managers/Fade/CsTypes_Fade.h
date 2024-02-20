// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Struct/CsTypes_StructOps.h"
#include "Types/CsTypes_Interpolation.h"
#include "Types/CsTypes_Curve.h"
// Log
#include "Utility/CsUILog.h"

#include "CsTypes_Fade.generated.h"

// FCsFade_ClearToBlackParams
#pragma region

// NCsFade::NClearToBlack::FParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsFade, NClearToBlack, FParams)

/**
* Describes any parameters related to Fading the Screen from Clear to Black.
*/
USTRUCT(BlueprintType)
struct CSUI_API FCsFade_ClearToBlackParams
{
	GENERATED_USTRUCT_BODY()

	/* Describes with method to use for interpolating the Fade Color. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsUI|Fade")
	ECsInterpolatingMethod InterpolationMethod;

	/** Describes which easing method / function should be used for interpolating the Fade Color. 
		NOTE: InterpolationMethod == ECsInterpolationMethod::Easing for this to be used. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsUI|Fade", meta = (EditCondition = "InterpolationMethod==ECsInterpolatingMethod::Easing", EditConditionHides))
	ECsEasingType Easing;

	/** The Curve used for interpolating the Fade Color. 
		NOTE: InterpolationMethod == ECsInterpolationMethod::Curve for this to be used. 
		NOTE: Time Range MUST be [0.0, 1.0] and Value Range MUST be [0.0, 1.0]. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsUI|Fade", meta = (EditCondition = "InterpolationMethod==ECsInterpolatingMethod::Curve", EditConditionHides, UIMin = "0.0", ClampMin = "0.0", UIMax = "1.0", ClampMax = "1.0"))
	FCsCurve Curve;

	/** The amount of time to take to Fade Transparent to Black. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsUI|Fade", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Time;

	FCsFade_ClearToBlackParams() :
		InterpolationMethod(ECsInterpolatingMethod::Easing),
		Easing(ECsEasingType::Linear),
		Curve(),
		Time(0.0f)
	{
	}

#define ParamsType NCsFade::NClearToBlack::FParams
	void CopyToParams(ParamsType* Params);
	void CopyToParamsAsValue(ParamsType* Params) const;
#undef ParamsType

	CS_STRUCT_OPS_IS_VALID_CHECKED(FCsFade_ClearToBlackParams)
	CS_STRUCT_OPS_IS_VALID(FCsFade_ClearToBlackParams)
	CS_STRUCT_OPS_IS_TOP_VALID_CHECKED(FCsFade_ClearToBlackParams)
	CS_STRUCT_OPS_IS_TOP_VALID(FCsFade_ClearToBlackParams)

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsUI::FLog::Warning) const;
	bool IsTopValidChecked(const FString& Context) const;
	bool IsTopValid(const FString& Context, void(*Log)(const FString&) = &NCsUI::FLog::Warning) const;

	CS_STRUCT_OPS_DATA_UNLOAD(FCsFade_ClearToBlackParams)

	FORCEINLINE void Unload()
	{
		Curve.Unload();
	}
};

class UCurveBase;

namespace NCsFade
{
	namespace NClearToBlack
	{
		/**
		* Describes any parameters related to Fading the Screen from Clear to Black.
		*/
		struct CSUI_API FParams
		{
		private:

			/* Describes with method to use for interpolating the Fade Color. */
			CS_DECLARE_MEMBER_WITH_PROXY(InterpolationMethod, ECsInterpolatingMethod)
			/** Describes which easing method / function should be used for interpolating the Fade Color. 
				NOTE: GetInterpolationMethod() == ECsInterpolationMethod::Easing for this to be used. */
			CS_DECLARE_MEMBER_WITH_PROXY(Easing, ECsEasingType)
			/** The Curve used for interpolating the Fade Color. 
				NOTE: InterpolationMethod == ECsInterpolationMethod::Curve for this to be used. 
				NOTE: Time Range MUST be [0.0, 1.0] and Value Range MUST be [0.0, 1.0]. */
			CS_DECLARE_MEMBER_WITH_PROXY(Curve, UCurveBase*)
			/** The amount of time to take to Fade Transparent to Black. */
			CS_DECLARE_MEMBER_WITH_PROXY(Time, float)

		public:

			FParams() :
				CS_CTOR_INIT_MEMBER_WITH_PROXY(InterpolationMethod, ECsInterpolatingMethod::Easing),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Easing, ECsEasingType::Linear),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Curve, nullptr),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Time, 0.0f)
			{
				CS_CTOR_SET_MEMBER_PROXY(InterpolationMethod);
				CS_CTOR_SET_MEMBER_PROXY(Easing);
				CS_CTOR_SET_MEMBER_PROXY(Curve);
				CS_CTOR_SET_MEMBER_PROXY(Time);
			}

			FParams(FParams& B)
			{
				SetInterpolationMethod(B.GetInterpolationMethod());
				SetEasing(B.GetEasing());
				SetCurve(B.GetCurve());
				SetTime(B.GetTime());
			}

			FParams(const FParams& B)
			{
				Copy(B);
			}

			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(InterpolationMethod, ECsInterpolatingMethod)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Easing, ECsEasingType)
			CS_DEFINE_SET_GET_MEMBER_PTR_WITH_PROXY(Curve, UCurveBase)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Time, float)

			FORCEINLINE void Copy(const FParams& B)
			{
				SetInterpolationMethod(B.GetInterpolationMethod());
				SetEasing(B.GetEasing());
				SetCurve(B.GetCurve());
				SetTime(B.GetTime());
			}

			FORCEINLINE static FParams Make(const FCsFade_ClearToBlackParams& Params)
			{
				FParams P;
				Params.CopyToParamsAsValue(&P);
				return P;
			}

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsUI::FLog::Warning) const;
			bool IsTopValidChecked(const FString& Context) const;
			bool IsTopValid(const FString& Context, void(*Log)(const FString&) = &NCsUI::FLog::Warning) const;
		};
	}
}

#pragma endregion FCsFade_ClearToBlackParams

// FCsFade_BlackToClearParams
#pragma region

// NCsFade::NBlackToClear::FParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsFade, NBlackToClear, FParams)

/**
* Describes any parameters related to Fading the Screen from Black to Clear.
*/
USTRUCT(BlueprintType)
struct CSUI_API FCsFade_BlackToClearParams
{
	GENERATED_USTRUCT_BODY()

	/* Describes with method to use for interpolating the Fade Color. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsUI|Fade")
	ECsInterpolatingMethod InterpolationMethod;

	/** Describes which easing method / function should be used for interpolating the Fade Color. 
		NOTE: InterpolationMethod == ECsInterpolationMethod::Easing for this to be used. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsUI|Fade", meta = (EditCondition = "InterpolationMethod==ECsInterpolatingMethod::Easing", EditConditionHides))
	ECsEasingType Easing;

	/** The Curve used for interpolating the Fade Color. 
		NOTE: InterpolationMethod == ECsInterpolationMethod::Curve for this to be used. 
		NOTE: Time Range MUST be [0.0, 1.0] and Value Range MUST be [0.0, 1.0]. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsUI|Fade", meta = (EditCondition = "InterpolationMethod==ECsInterpolatingMethod::Curve", EditConditionHides, UIMin = "0.0", ClampMin = "0.0", UIMax = "1.0", ClampMax = "1.0"))
	FCsCurve Curve;

	/** The amount of time to take to Fade Black to Transparent. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsUI|Fade", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Time;

	FCsFade_BlackToClearParams() :
		InterpolationMethod(ECsInterpolatingMethod::Easing),
		Easing(ECsEasingType::Linear),
		Curve(),
		Time(0.0f)
	{
	}

#define ParamsType NCsFade::NBlackToClear::FParams
	void CopyToParams(ParamsType* Params);
	void CopyToParamsAsValue(ParamsType* Params) const;
#undef ParamsType

	CS_STRUCT_OPS_IS_VALID_CHECKED(FCsFade_BlackToClearParams)
	CS_STRUCT_OPS_IS_VALID(FCsFade_BlackToClearParams)
	CS_STRUCT_OPS_IS_TOP_VALID_CHECKED(FCsFade_BlackToClearParams)
	CS_STRUCT_OPS_IS_TOP_VALID(FCsFade_BlackToClearParams)

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsUI::FLog::Warning) const;
	bool IsTopValidChecked(const FString& Context) const;
	bool IsTopValid(const FString& Context, void(*Log)(const FString&) = &NCsUI::FLog::Warning) const;

	CS_STRUCT_OPS_DATA_UNLOAD(FCsFade_BlackToClearParams)

	FORCEINLINE void Unload()
	{
		Curve.Unload();
	}
};

class UCurveBase;

namespace NCsFade
{
	namespace NBlackToClear
	{
		/**
		* Describes any parameters related to Fading the Screen from Black to Clear.
		*/
		struct CSUI_API FParams
		{
		private:

			/* Describes with method to use for interpolating the Fade Color. */
			CS_DECLARE_MEMBER_WITH_PROXY(InterpolationMethod, ECsInterpolatingMethod)
			/** Describes which easing method / function should be used for interpolating the Fade Color. 
				NOTE: GetInterpolationMethod() == ECsInterpolationMethod::Easing for this to be used. */
			CS_DECLARE_MEMBER_WITH_PROXY(Easing, ECsEasingType)
			/** The Curve used for interpolating the Fade Color. 
				NOTE: InterpolationMethod == ECsInterpolationMethod::Curve for this to be used. 
				NOTE: Time Range MUST be [0.0, 1.0] and Value Range MUST be [0.0, 1.0]. */
			CS_DECLARE_MEMBER_WITH_PROXY(Curve, UCurveBase*)
			/** The amount of time to take to Fade Black to Transparent. */
			CS_DECLARE_MEMBER_WITH_PROXY(Time, float)

		public:

			FParams() :
				CS_CTOR_INIT_MEMBER_WITH_PROXY(InterpolationMethod, ECsInterpolatingMethod::Easing),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Easing, ECsEasingType::Linear),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Curve, nullptr),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Time, 0.0f)
			{
				CS_CTOR_SET_MEMBER_PROXY(InterpolationMethod);
				CS_CTOR_SET_MEMBER_PROXY(Easing);
				CS_CTOR_SET_MEMBER_PROXY(Curve);
				CS_CTOR_SET_MEMBER_PROXY(Time);
			}

			FParams(FParams& B)
			{
				SetInterpolationMethod(B.GetInterpolationMethod());
				SetEasing(B.GetEasing());
				SetCurve(B.GetCurve());
				SetTime(B.GetTime());
			}

			FParams(const FParams& B)
			{
				Copy(B);
			}

			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(InterpolationMethod, ECsInterpolatingMethod)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Easing, ECsEasingType)
			CS_DEFINE_SET_GET_MEMBER_PTR_WITH_PROXY(Curve, UCurveBase)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Time, float)

			FORCEINLINE void Copy(const FParams& B)
			{
				SetInterpolationMethod(B.GetInterpolationMethod());
				SetEasing(B.GetEasing());
				SetCurve(B.GetCurve());
				SetTime(B.GetTime());
			}

			FORCEINLINE static FParams Make(const FCsFade_BlackToClearParams& Params)
			{
				FParams P;
				Params.CopyToParamsAsValue(&P);
				return P;
			}

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsUI::FLog::Warning) const;
			bool IsTopValidChecked(const FString& Context) const;
			bool IsTopValid(const FString& Context, void(*Log)(const FString&) = &NCsUI::FLog::Warning) const;
		};
	}
}

#pragma endregion FCsFade_BlackToClearParams

// FCsFadeParams
#pragma region

// NCsFade::FParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_1(NCsFade, FParams)

/**
* Describes any parameters for Fading the Screen.
*/
USTRUCT(BlueprintType)
struct CSUI_API FCsFadeParams
{
	GENERATED_USTRUCT_BODY()

	/** The Color to Start Fading From. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsUI|Fade")
	FLinearColor From;

	/** The Destination Color to End Fading To. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsUI|Fade")
	FLinearColor To;

	/* Describes with method to use for interpolating the Fade Color. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsUI|Fade")
	ECsInterpolatingMethod InterpolationMethod;

	/** Describes which easing method / function should be used for interpolating the Fade Color. 
		NOTE: InterpolationMethod == ECsInterpolationMethod::Easing for this to be used. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsUI|Fade", meta = (EditCondition = "InterpolationMethod==ECsInterpolatingMethod::Easing", EditConditionHides))
	ECsEasingType Easing;

	/** The Curve used for interpolating the Fade Color. 
		NOTE: InterpolationMethod == ECsInterpolationMethod::Curve for this to be used. 
		NOTE: Time Range MUST be [0.0, 1.0] and Value Range MUST be [0.0, 1.0]. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsUI|Fade", meta = (EditCondition = "InterpolationMethod==ECsInterpolatingMethod::Curve", EditConditionHides, UIMin = "0.0", ClampMin = "0.0", UIMax = "1.0", ClampMax = "1.0"))
	FCsCurve Curve;

	/** The amount of time to take to Fade From -> To. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsUI|Fade", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Time;

	FCsFadeParams() :
		From(FLinearColor::Black),
		To(FLinearColor::Black),
		InterpolationMethod(ECsInterpolatingMethod::Easing),
		Easing(ECsEasingType::Linear),
		Curve(),
		Time(0.0f)
	{
	}

#define ParamsType NCsFade::FParams
	void CopyToParams(ParamsType* Params);
	void CopyToParamsAsValue(ParamsType* Params) const;
#undef ParamsType

	CS_STRUCT_OPS_IS_VALID_CHECKED(FCsFadeParams)
	CS_STRUCT_OPS_IS_VALID(FCsFadeParams)
	CS_STRUCT_OPS_IS_TOP_VALID_CHECKED(FCsFadeParams)
	CS_STRUCT_OPS_IS_TOP_VALID(FCsFadeParams)

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsUI::FLog::Warning) const;
	bool IsTopValidChecked(const FString& Context) const;
	bool IsTopValid(const FString& Context, void(*Log)(const FString&) = &NCsUI::FLog::Warning) const;

	CS_STRUCT_OPS_DATA_UNLOAD(FCsFadeParams)

	FORCEINLINE void Unload()
	{
		Curve.Unload();
	}
};

namespace NCsFade
{
	struct CSUI_API FParams
	{
	private:

		/** The Color to Start Fading From. */
		CS_DECLARE_MEMBER_WITH_PROXY(From, FLinearColor)
		/** The Destination Color to End Fading To. */
		CS_DECLARE_MEMBER_WITH_PROXY(To, FLinearColor)
		/* Describes with method to use for interpolating the Fade Color. */
		CS_DECLARE_MEMBER_WITH_PROXY(InterpolationMethod, ECsInterpolatingMethod)
		/** Describes which easing method / function should be used for interpolating the Fade Color. 
			NOTE: GetInterpolationMethod() == ECsInterpolationMethod::Easing for this to be used. */
		CS_DECLARE_MEMBER_WITH_PROXY(Easing, ECsEasingType)
		/** The Curve used for interpolating the Fade Color. 
			NOTE: InterpolationMethod == ECsInterpolationMethod::Curve for this to be used. 
			NOTE: Time Range MUST be [0.0, 1.0] and Value Range MUST be [0.0, 1.0]. */
		CS_DECLARE_MEMBER_WITH_PROXY(Curve, UCurveBase*)
		/** The amount of time to take to Fade From -> To. */
		CS_DECLARE_MEMBER_WITH_PROXY(Time, float)

		// TODO: Add Easing / Curve

		CS_DECLARE_MEMBER_WITH_PROXY(bCollapseOnEnd, bool)

	public:

		FParams() :
			CS_CTOR_INIT_MEMBER_WITH_PROXY(From, FLinearColor::Black),
			CS_CTOR_INIT_MEMBER_WITH_PROXY(To, FLinearColor::Black),
			CS_CTOR_INIT_MEMBER_WITH_PROXY(InterpolationMethod, ECsInterpolatingMethod::Easing),
			CS_CTOR_INIT_MEMBER_WITH_PROXY(Easing, ECsEasingType::Linear),
			CS_CTOR_INIT_MEMBER_WITH_PROXY(Curve, nullptr),
			CS_CTOR_INIT_MEMBER_WITH_PROXY(Time, 0.0f),
			CS_CTOR_INIT_MEMBER_WITH_PROXY(bCollapseOnEnd, false)
		{
			CS_CTOR_SET_MEMBER_PROXY(From);
			CS_CTOR_SET_MEMBER_PROXY(To);
			CS_CTOR_SET_MEMBER_PROXY(InterpolationMethod);
			CS_CTOR_SET_MEMBER_PROXY(Easing);
			CS_CTOR_SET_MEMBER_PROXY(Curve);
			CS_CTOR_SET_MEMBER_PROXY(Time);
			CS_CTOR_SET_MEMBER_PROXY(bCollapseOnEnd);
		}

		FParams(FParams& B)
		{
			SetFrom(B.GetFrom());
			SetTo(B.GetTo());
			SetInterpolationMethod(B.GetInterpolationMethod());
			SetEasing(B.GetEasing());
			SetCurve(B.GetCurve());
			SetTime(B.GetTime());
			SetbCollapseOnEnd(B.GetbCollapseOnEnd());
		}

		FParams(const FParams& B)
		{
			Copy(B);
		}

		CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(From, FLinearColor)
		CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(To, FLinearColor)
		CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(InterpolationMethod, ECsInterpolatingMethod)
		CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Easing, ECsEasingType)
		CS_DEFINE_SET_GET_MEMBER_PTR_WITH_PROXY(Curve, UCurveBase)
		CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Time, float)
		CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bCollapseOnEnd, bool)
		FORCEINLINE const bool& ShouldCollapseOnEnd() const { return GetbCollapseOnEnd(); }

		FORCEINLINE void Copy(const FParams& B)
		{
			SetFrom(B.GetFrom());
			SetTo(B.GetTo());
			SetInterpolationMethod(B.GetInterpolationMethod());
			SetEasing(B.GetEasing());
			SetCurve(B.GetCurve());
			SetTime(B.GetTime());
			SetbCollapseOnEnd(B.GetbCollapseOnEnd());
		}

		FORCEINLINE static FParams Make(const FCsFadeParams& Params)
		{
			FParams P;
			Params.CopyToParamsAsValue(&P);
			return P;
		}

		FORCEINLINE static FParams Make(const FCsFade_ClearToBlackParams& Params)
		{
			FParams P;		
			P.SetFrom(FLinearColor::Transparent);
			P.SetTo(FLinearColor::Black);
			P.SetInterpolationMethod(Params.InterpolationMethod);
			P.SetEasing(Params.Easing);
			P.SetCurve(Params.Curve.Get());
			P.SetTime(Params.Time);
			return P;
		}

		FORCEINLINE static FParams Make(const NCsFade::NClearToBlack::FParams& Params)
		{
			FParams P;
			P.SetFrom(FLinearColor::Transparent);
			P.SetTo(FLinearColor::Black);
			P.SetInterpolationMethod(Params.GetInterpolationMethod());
			P.SetEasing(Params.GetEasing());
			P.SetCurve(Params.GetCurve());
			P.SetTime(Params.GetTime());
			return P;
		}

		FORCEINLINE static FParams Make(const FCsFade_BlackToClearParams& Params)
		{
			FParams P;
			P.SetFrom(FLinearColor::Black);
			P.SetTo(FLinearColor::Transparent);
			P.SetInterpolationMethod(Params.InterpolationMethod);
			P.SetEasing(Params.Easing);
			P.SetCurve(Params.Curve.Get());
			P.SetTime(Params.Time);
			return P;
		}

		FORCEINLINE static FParams Make(const NCsFade::NBlackToClear::FParams& Params)
		{
			FParams P;
			P.SetFrom(FLinearColor::Black);
			P.SetTo(FLinearColor::Transparent);
			P.SetInterpolationMethod(Params.GetInterpolationMethod());
			P.SetEasing(Params.GetEasing());
			P.SetCurve(Params.GetCurve());
			P.SetTime(Params.GetTime());
			return P;
		}

		bool IsValidChecked(const FString& Context) const;
		bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsUI::FLog::Warning) const;
		bool IsTopValidChecked(const FString& Context) const;
		bool IsTopValid(const FString& Context, void(*Log)(const FString&) = &NCsUI::FLog::Warning) const;
	};
}

#pragma endregion FCsFadeParams
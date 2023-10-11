// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Log
#include "Utility/CsUILog.h"

#include "CsTypes_Fade.generated.h"

USTRUCT(BlueprintType)
struct FCsFadeParams
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsUI|Fade")
	FLinearColor From;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsUI|Fade")
	FLinearColor To;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsUI|Fade", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Time;

	FCsFadeParams() :
		From(FLinearColor::Black),
		To(FLinearColor::Black),
		Time(0.0f)
	{
	}

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsUI::FLog::Warning) const;
};

namespace NCsFade
{
	struct CSUI_API FParams
	{
	public:

		FLinearColor From;

		FLinearColor To;

		float Time;

		// TODO: Add Easing / Curve

		bool bCollapseOnEnd;

		FParams() :
			From(FLinearColor::Black),
			To(FLinearColor::Black),
			Time(0.0f),
			bCollapseOnEnd(false)
		{
		}

		static FParams Make(const FCsFadeParams& Params)
		{
			FParams P;
			P.From	= Params.From;
			P.To	= Params.To;
			P.Time	= Params.Time;
			return P;
		}

		bool IsValidChecked(const FString& Context) const;
		bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsUI::FLog::Warning) const;
	};
}
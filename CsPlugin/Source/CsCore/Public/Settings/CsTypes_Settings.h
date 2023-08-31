// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "CsTypes_Settings.generated.h"

// FCsSettings_PIE
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsSettings_PIE
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Settings")
	bool bSwapViewportDimensions;

	/** The width of the new view port window in pixels (0 = use the desktop's screen resolution). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Settings", meta = (ClampMin = 0))
	int32 NewWindowWidth;

	/** The height of the new view port window in pixels (0 = use the desktop's screen resolution). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Settings", meta = (ClampMin = 0))
	int32 NewWindowHeight;

	FCsSettings_PIE() :
		bSwapViewportDimensions(false),
		NewWindowWidth(1280),
		NewWindowHeight(720)
	{
	}

	void SwapViewportDimensions()
	{
		int32 Temp	    = NewWindowWidth;
		NewWindowWidth  = NewWindowHeight;
		NewWindowHeight = Temp;

		bSwapViewportDimensions = false;
	}
};

#pragma endregion FCsSettings_PIE

// FCsSettings_Entry
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsSettings_Entry
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Settings", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float CompanyLogoDisplayTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Settings", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float GameSplashDisplayTime;

	FCsSettings_Entry() :
		CompanyLogoDisplayTime(0.0f),
		GameSplashDisplayTime(0.0f)
	{
	}
};

#pragma endregion FCsSettings_Entry
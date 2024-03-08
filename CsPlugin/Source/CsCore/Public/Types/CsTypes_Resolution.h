// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CsTypes_Resolution.generated.h"

// FCsScreenResolution
#pragma region

USTRUCT(BlueprintType)
struct FCsScreenResolution
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Resolution", meta = (UIMin = "0", ClampMin = "0"))
	int32 Width;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Resolution", meta = (UIMin = "0", ClampMin = "0"))
	int32 Height;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Resolution", meta = (UIMin = "0", ClampMin = "0"))
	int32 RefreshRate;

	FCsScreenResolution() :
		Width(1920),
		Height(1080),
		RefreshRate(60)
	{
	}

	bool operator==(const FCsScreenResolution& B) const
	{
		return Width == B.Width && Height == B.Height && RefreshRate == B.RefreshRate;
	}

	bool operator!=(const FCsScreenResolution& B) const
	{
		return !(*this == B);
	}

	void Reset()
	{
		Width = 1920;
		Height = 1080;
		RefreshRate = 60;
	}

	FORCEINLINE FString ToOptionsString() const 
	{
		return FString::Printf(TEXT("%dx%d @ %d Hz"), Width, Height, RefreshRate);
	}

	FORCEINLINE FString ToConsoleString() const
	{
		return FString::Printf(TEXT("%dx%d"), Width, Height);
	}
};

#pragma endregion FCsScreenResolution
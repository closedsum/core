// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "CsTypes_RenderTarget.generated.h"

// FCsTextureRenderTarget2D_Array
#pragma region

class UTextureRenderTarget2D;

USTRUCT(BlueprintType)
struct CSCORE_API FCsTextureRenderTarget2D_Array
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Render")
	TArray<UTextureRenderTarget2D*> Textures;

	FCsTextureRenderTarget2D_Array() :
		Textures()
	{
	}
};

#pragma endregion FCsTextureRenderTarget2D_Array
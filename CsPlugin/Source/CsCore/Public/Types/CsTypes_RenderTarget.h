// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#include "CsTypes_RenderTarget.generated.h"
#pragma once


// FCsTextureRenderTarget2D_Array
#pragma region

class UTextureRenderTarget2D;

USTRUCT(BlueprintType)
struct CSCORE_API FCsTextureRenderTarget2D_Array
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UTextureRenderTarget2D*> Textures;

	FCsTextureRenderTarget2D_Array() :
		Textures()
	{
	}
};

#pragma endregion FCsTextureRenderTarget2D_Array
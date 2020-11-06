// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#include "CsTypes_Texture.generated.h"
#pragma once


// FCsTexture
#pragma region

class UTexture;

USTRUCT(BlueprintType)
struct CSCORE_API FCsTexture
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSoftObjectPtr<UTexture> Texture;

	UPROPERTY()
	int32 Load_Flags;

	UPROPERTY(Transient, BlueprintReadOnly)
	UTexture* Texture_Internal;

	FCsTexture() :
		Texture(nullptr),
		Load_Flags(0),
		Texture_Internal(nullptr)
	{
	}

	FORCEINLINE UTexture* Get() const { return Texture_Internal; }
};

#pragma endregion FCsTexture
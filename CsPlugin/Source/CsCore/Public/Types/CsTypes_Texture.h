// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
// Log
#include "Utility/CsLog.h"

#include "CsTypes_Texture.generated.h"
#pragma once


// FCsTexture
#pragma region

class UTexture;

USTRUCT(BlueprintType)
struct CSCORE_API FCsTexture
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UTexture> Texture;

	UPROPERTY()
	int32 Texture_LoadFlags;

	UPROPERTY(Transient, BlueprintReadWrite)
	UTexture* Texture_Internal;

	FCsTexture() :
		Texture(nullptr),
		Texture_LoadFlags(0),
		Texture_Internal(nullptr)
	{
	}

	/**
	* Get the Hard reference to the UTexture asset.
	*
	* return Texture
	*/
	FORCEINLINE UTexture* Get() const { return Texture_Internal; }

	/**
	* Get the pointer to the Hard reference to the UTexture asset.
	*
	* return Texture
	*/
	FORCEINLINE UTexture** GetPtr() { return &Texture_Internal; }

	/**
	* Get the Hard reference to the UTexture asset.
	*
	* @param Context	The calling context.
	* return			Texture
	*/
	FORCEINLINE UTexture* GetChecked(const FString& Context) const
	{
		checkf(Texture.ToSoftObjectPath().IsValid(), TEXT("%s: Texture is NULL."), *Context);

		checkf(Texture_Internal, TEXT("%s: Texture has NOT been loaded from Path @ %s."), *Context, *(Texture.ToSoftObjectPath().ToString()));

		return Texture_Internal;
	}

	/**
	* Get the Hard reference to the UTexture asset.
	*
	* return Static Mesh
	*/
	FORCEINLINE UTexture* GetChecked() const
	{
		checkf(Texture.ToSoftObjectPath().IsValid(), TEXT("FCsTexture::GetChecked: Mesh is NULL."));

		checkf(Texture_Internal, TEXT("FCsTexture::GetChecked: Texture has NOT been loaded from Path @ %s."), *(Texture.ToSoftObjectPath().ToString()));

		return Texture_Internal;
	}

	/**
	* Safely get the Hard reference to the UTexture asset.
	*
	* @param Context	The calling context.
	* @param Log		(optional)
	* return			Static Mesh
	*/
	UTexture* GetSafe(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
	{
		if (!Texture.ToSoftObjectPath().IsValid())
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Texture is NULL."), *Context));
			return nullptr;
		}

		if (!Texture_Internal)
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Texture has NOT been loaded from Path @ %s."), *Context, *(Texture.ToSoftObjectPath().ToString())));
		}
		return Texture_Internal;
	}

	/**
	* Safely get the Hard reference to the UTexture asset.
	*
	* return Static Mesh
	*/
	UTexture* GetSafe()
	{
		if (!Texture.ToSoftObjectPath().IsValid())
			return nullptr;
		return Texture_Internal;
	}

	bool IsValidChecked(const FString& Context) const
	{
		check(GetChecked(Context));
		return true;
	}

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
	{
		if (!GetSafe(Context, Log))
			return false;
		return true;
	}
};

#pragma endregion FCsTexture
// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Log
#include "Utility/CsLog.h"
// Engine
#include "Engine/DataTable.h"

#include "CsTypes_Texture.generated.h"

// FCsTexture
#pragma region

class UTexture;

USTRUCT(BlueprintType)
struct CSCORE_API FCsTexture : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DataTable)
	TSoftObjectPtr<UTexture> Texture;

	UPROPERTY()
	int32 Texture_LoadFlags;

	UPROPERTY(Transient, BlueprintReadOnly, Category = DataTable)
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

// FCsTexture2D
#pragma region

class UTexture2D;

USTRUCT(BlueprintType)
struct CSCORE_API FCsTexture2D : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DataTable)
	TSoftObjectPtr<UTexture2D> Texture;

	UPROPERTY()
	int32 Texture_LoadFlags;

	UPROPERTY(Transient, BlueprintReadOnly, Category = DataTable)
	UTexture2D* Texture_Internal;

	FCsTexture2D() :
		Texture(nullptr),
		Texture_LoadFlags(0),
		Texture_Internal(nullptr)
	{
	}

	/**
	* Get the Hard reference to the UTexture2D asset.
	*
	* return Texture
	*/
	FORCEINLINE UTexture2D* Get() const { return Texture_Internal; }

	/**
	* Get the pointer to the Hard reference to the UTexture2D asset.
	*
	* return Texture
	*/
	FORCEINLINE UTexture2D** GetPtr() { return &Texture_Internal; }

	/**
	* Get the Hard reference to the UTexture2D asset.
	*
	* @param Context	The calling context.
	* return			Texture
	*/
	FORCEINLINE UTexture2D* GetChecked(const FString& Context) const
	{
		checkf(Texture.ToSoftObjectPath().IsValid(), TEXT("%s: Texture is NULL."), *Context);

		checkf(Texture_Internal, TEXT("%s: Texture has NOT been loaded from Path @ %s."), *Context, *(Texture.ToSoftObjectPath().ToString()));

		return Texture_Internal;
	}

	/**
	* Get the Hard reference to the UTexture2D asset.
	*
	* return Static Mesh
	*/
	FORCEINLINE UTexture2D* GetChecked() const
	{
		checkf(Texture.ToSoftObjectPath().IsValid(), TEXT("FCsTexture::GetChecked: Mesh is NULL."));

		checkf(Texture_Internal, TEXT("FCsTexture::GetChecked: Texture has NOT been loaded from Path @ %s."), *(Texture.ToSoftObjectPath().ToString()));

		return Texture_Internal;
	}

	/**
	* Safely get the Hard reference to the UTexture2D asset.
	*
	* @param Context	The calling context.
	* @param Log		(optional)
	* return			Static Mesh
	*/
	UTexture2D* GetSafe(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
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
	* Safely get the Hard reference to the UTexture2D asset.
	*
	* return Static Mesh
	*/
	UTexture2D* GetSafe()
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

#pragma endregion FCsTexture2D
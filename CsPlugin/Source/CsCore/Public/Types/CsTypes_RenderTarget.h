// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Types/CsTypes_Macro.h"
// Log
#include "Utility/CsLog.h"

#include "CsTypes_RenderTarget.generated.h"

// FCsTexture
#pragma region

class UTextureRenderTarget2D;

USTRUCT(BlueprintType)
struct CSCORE_API FCsTextureRenderTarget2D
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Render")
	TSoftObjectPtr<UTextureRenderTarget2D> Texture;

	UPROPERTY()
	int32 Texture_LoadFlags;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsCore|Render")
	UTextureRenderTarget2D* Texture_Internal;

	FCsTextureRenderTarget2D() :
		Texture(nullptr),
		Texture_LoadFlags(0),
		Texture_Internal(nullptr)
	{
	}

	/**
	* Get the Hard reference to the UTextureRenderTarget2D asset.
	*
	* return Texture
	*/
	FORCEINLINE UTextureRenderTarget2D* Get() const { return Texture_Internal; }

	/**
	* Get the pointer to the Hard reference to the UTextureRenderTarget2D asset.
	*
	* return Texture
	*/
	FORCEINLINE UTextureRenderTarget2D** GetPtr() { return &Texture_Internal; }

	/**
	* Get the Hard reference to the UTextureRenderTarget2D asset.
	*
	* @param Context	The calling context.
	* return			Texture
	*/
	FORCEINLINE UTextureRenderTarget2D* GetChecked(const FString& Context) const
	{
		checkf(Texture.ToSoftObjectPath().IsValid(), TEXT("%s: Texture is NULL."), *Context);

		checkf(Texture_Internal, TEXT("%s: Texture has NOT been loaded from Path @ %s."), *Context, *(Texture.ToSoftObjectPath().ToString()));

		return Texture_Internal;
	}

	/**
	* Get the Hard reference to the UTextureRenderTarget2D asset.
	*
	* return Static Mesh
	*/
	FORCEINLINE UTextureRenderTarget2D* GetChecked() const
	{
		checkf(Texture.ToSoftObjectPath().IsValid(), TEXT("FCsTextureRenderTarget2D::GetChecked: Mesh is NULL."));

		checkf(Texture_Internal, TEXT("FCsTextureRenderTarget2D::GetChecked: Texture has NOT been loaded from Path @ %s."), *(Texture.ToSoftObjectPath().ToString()));

		return Texture_Internal;
	}

	/**
	* Safely get the Hard reference to the UTextureRenderTarget2D asset.
	*
	* @param Context	The calling context.
	* @param Log		(optional)
	* return			Static Mesh
	*/
	UTextureRenderTarget2D* GetSafe(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
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
	* Safely get the Hard reference to the UTextureRenderTarget2D asset.
	*
	* return Static Mesh
	*/
	UTextureRenderTarget2D* GetSafe()
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

	FORCEINLINE TArray<UTextureRenderTarget2D*>* GetPtr() { return &Textures; }
};

#pragma endregion FCsTextureRenderTarget2D_Array

// FCsTArrayTextureRenderTarget2D
#pragma region

class UTextureRenderTarget2D;

/**
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsTArrayTextureRenderTarget2D
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Texture")
	TArray<TSoftObjectPtr<UTextureRenderTarget2D>> Textures;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Texture", meta = (Bitmask, BitmaskEnum = "/Script/CsCore.ECsLoadFlags"))
	int32 Textures_LoadFlags;

	UPROPERTY(Transient, BlueprintReadWrite, Category = "CsCore|Texture")
	TArray<UTextureRenderTarget2D*> Textures_Internal;

public:

	FCsTArrayTextureRenderTarget2D() :
		Textures(),
		Textures_LoadFlags(0),
		Textures_Internal()
	{
	}

	FORCEINLINE const TArray<UTextureRenderTarget2D*>& Get() const { return Textures_Internal; }

	FORCEINLINE TArray<UTextureRenderTarget2D*>* GetPtr() { return &Textures_Internal; }
	FORCEINLINE const TArray<UTextureRenderTarget2D*>* GetPtr() const { return &Textures_Internal; }

	/**
	* Get the Hard references to the array of Textures of type: UTextureRenderTarget2D.
	*
	* @param Context	The calling context.
	* return			Textures
	*/
	FORCEINLINE const TArray<UTextureRenderTarget2D*>& GetChecked(const FString& Context) const
	{ 
		checkf(Textures.Num() > CS_EMPTY, TEXT("%s: No Textures set."), *Context);

		checkf(Textures.Num() == Textures_Internal.Num(), TEXT("%s: Mismatch between Soft and Hard references to textures, %d != %d."), *Context, Textures.Num(), Textures_Internal.Num());

		const int32 Count = Textures.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const TSoftObjectPtr<UTextureRenderTarget2D>& SoftObject = Textures[I];

			checkf(SoftObject.ToSoftObjectPath().IsValid(), TEXT("%s: Textures[%d] is NULL."), *Context, I);

			UTextureRenderTarget2D* Texture = Textures_Internal[I];
	
			checkf(Texture, TEXT("%s: Textures[%d] has NOT been loaded from Path @ %s."), *Context, I, *(SoftObject.ToSoftObjectPath().ToString()));
		}
		return Textures_Internal;
	}

	/**
	* Get the Hard references to the array of Textures of type: UTextureRenderTarget2D.
	*
	* @param Context	The calling context.
	* return			Textures
	*/
	FORCEINLINE const TArray<UTextureRenderTarget2D*>& GetChecked() const
	{
		checkf(Textures.Num() > CS_EMPTY, TEXT("FCsTArrayTextureRenderTarget2D::GetChecked: No Textures set."));

		checkf(Textures.Num() == Textures_Internal.Num(), TEXT("FCsTArrayTextureRenderTarget2D::GetChecked: Mismatch between Soft and Hard references to textures, %d != %d."), Textures.Num(), Textures_Internal.Num());

		const int32 Count = Textures.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const TSoftObjectPtr<UTextureRenderTarget2D>& SoftObject = Textures[I];

			checkf(SoftObject.ToSoftObjectPath().IsValid(), TEXT("FCsTArrayTextureRenderTarget2D::GetChecked: Textures[%d] is NULL."), I);

			UTextureRenderTarget2D* Texture = Textures_Internal[I];

			checkf(Texture, TEXT("FCsTArrayTextureRenderTarget2D::GetChecked: Textures[%d] has NOT been loaded from Path @ %s."), I, *(SoftObject.ToSoftObjectPath().ToString()));
		}
		return Textures_Internal;
	}

	/**
	* Get the Hard reference to the Texture at Index of type: UTextureRenderTarget2D.
	*
	* @param Context	The calling context.
	* @param Index
	* return			Texture
	*/
	FORCEINLINE UTextureRenderTarget2D* GetChecked(const FString& Context, const int32& Index) const
	{
		checkf(Index >= 0 && Index < Textures_Internal.Num(), TEXT("%s: Index: %d is NOT in the range [0, %d)."), *Context, Index, Textures_Internal.Num());

		return GetChecked(Context)[Index];
	}

	/**
	* Safely get the Hard reference to the array of Textures of type: UTextureRenderTarget2D.
	*
	* @param Context	The calling context.
	* @param Log		(optional)
	* return			Textures
	*/
	const TArray<UTextureRenderTarget2D*>* GetSafe(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
	{
		if (Textures.Num() == CS_EMPTY)
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: No Textures set."), *Context));
			return nullptr;
		}

		if (Textures.Num() != Textures_Internal.Num())
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Mismatch between Soft and Hard references to textures, %d != %d."), *Context, Textures.Num(), Textures_Internal.Num()));
			return nullptr;
		}

		const int32 Count = Textures.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const TSoftObjectPtr<UTextureRenderTarget2D>& SoftObject = Textures[I];

			if (!SoftObject.ToSoftObjectPath().IsValid())
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: Textures[%d] is NULL."), *Context, I));
				return nullptr;
			}

			UTextureRenderTarget2D* Texture = Textures_Internal[I];

			if (!Texture)
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: Textures[%d] has NOT been loaded from Path @ %s."), *Context, I, *(SoftObject.ToSoftObjectPath().ToString())));
				return nullptr;
			}
		}
		return &Textures_Internal;
	}

	bool IsValidChecked(const FString& Context) const
	{
		checkf(Textures.Num() > CS_EMPTY, TEXT("%s: No Textures set."), *Context);

		checkf(Textures.Num() == Textures_Internal.Num(), TEXT("%s: Mismatch between Soft and Hard references to textures, %d != %d."), *Context, Textures.Num(), Textures_Internal.Num());

		const int32 Count = Textures.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const TSoftObjectPtr<UTextureRenderTarget2D>& SoftObject = Textures[I];

			checkf(SoftObject.ToSoftObjectPath().IsValid(), TEXT("%s: Textures[%d] is NULL."), *Context, I);

			UTextureRenderTarget2D* Material = Textures_Internal[I];

			checkf(Material, TEXT("%s: Textures[%d] has NOT been loaded from Path @ %s."), *Context, I, *(SoftObject.ToSoftObjectPath().ToString()));
		}
		return true;
	}

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
	{
		if (Textures.Num() == CS_EMPTY)
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: No Textures set."), *Context));
			return false;
		}

		if (Textures.Num() != Textures_Internal.Num())
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Mismatch between Soft and Hard references to textures, %d != %d."), *Context, Textures.Num(), Textures_Internal.Num()));
			return false;
		}

		const int32 Count = Textures.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const TSoftObjectPtr<UTextureRenderTarget2D>& SoftObject = Textures[I];

			if (!SoftObject.ToSoftObjectPath().IsValid())
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: Textures[%d] is NULL."), *Context, I));
				return false;
			}

			UTextureRenderTarget2D* Texture = Textures_Internal[I];

			if (!Texture)
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: Textures[%d] has NOT been loaded from Path @ %s."), *Context, I, *(SoftObject.ToSoftObjectPath().ToString())));
				return false;
			}
		}
		return true;
	}
};

#pragma endregion FCsTArrayTextureRenderTarget2D
// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "Types/CsTypes_Texture.h"

#include "CsScriptLibrary_Texture.generated.h"

class UTexture;

UCLASS()
class CSCORELIBRARY_API UCsScriptLibrary_Texture : public UObject
{ 
	GENERATED_UCLASS_BODY() 

// Load
#pragma region
public:

	/**
	* Load a Texture at the given Path.
	* 
	* @param Context	The calling context.
	* @param Path		SoftObjectPath to the Texture to load.
	* return			Texture
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCoreLibrary|Library|Texture", meta = (AutoCreateRefTerm = "Context,Path"))
	static UTexture* LoadBySoftObjectPath(const FString& Context, const FSoftObjectPath& Path);

	/**
	* Load a Texture at the given Path.
	* 
	* @param Context	The calling context.
	* @param Path		FString path to the Texture to load.
	* return			Texture
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCoreLibrary|Library|Texture", meta = (AutoCreateRefTerm = "Context,Path"))
	static UTexture* LoadByStringPath(const FString& Context, const FString& Path);

#pragma endregion Load

// Unload
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "CsCoreLibrary|Library|Texture", meta = (DisplayName = "Unload (FCsTexture)", CompactNodeTitle = "Unload"))
	static void FCsTexture_Unload(UPARAM(ref) FCsTexture& Texture)
	{
		Texture.Unload();
	}

	UFUNCTION(BlueprintCallable, Category = "CsCoreLibrary|Library|Texture", meta = (DisplayName = "Unload (TArray<FCsTexture>)", CompactNodeTitle = "Unload"))
	static void TArray_FCsTexture_Unload(UPARAM(ref) TArray<FCsTexture>& Textures)
	{
		for (FCsTexture& Texture : Textures)
		{
			Texture.Unload();
		}
	}

	UFUNCTION(BlueprintCallable, Category = "CsCoreLibrary|Library|Texture", meta = (DisplayName = "Unload (FCsTexture2D)", CompactNodeTitle = "Unload"))
	static void FCsTexture2D_Unload(UPARAM(ref) FCsTexture2D& Texture)
	{
		Texture.Unload();
	}

	UFUNCTION(BlueprintCallable, Category = "CsTypes|Library|Texture", meta = (DisplayName = "Unload (TArray<FCsTexture2D>)", CompactNodeTitle = "Unload"))
	static void TArray_FCsTexture2D_Unload(UPARAM(ref) TArray<FCsTexture2D>& Textures)
	{
		for (FCsTexture2D& Texture : Textures)
		{
			Texture.Unload();
		}
	}

#pragma endregion Unload
};
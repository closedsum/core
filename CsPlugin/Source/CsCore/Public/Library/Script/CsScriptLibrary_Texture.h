// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"

#include "CsScriptLibrary_Texture.generated.h"

class UTexture;

UCLASS()
class CSCORE_API UCsScriptLibrary_Texture : public UObject
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
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Texture", meta = (AutoCreateRefTerm = "Context,Path"))
	static UTexture* LoadBySoftObjectPath(const FString& Context, const FSoftObjectPath& Path);

	/**
	* Load a Texture at the given Path.
	* 
	* @param Context	The calling context.
	* @param Path		FString path to the Texture to load.
	* return			Texture
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Texture", meta = (AutoCreateRefTerm = "Context,Path"))
	static UTexture* LoadByStringPath(const FString& Context, const FString& Path);

#pragma endregion Load
};
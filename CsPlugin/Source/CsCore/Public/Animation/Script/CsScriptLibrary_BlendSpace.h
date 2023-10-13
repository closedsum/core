// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"

#include "CsScriptLibrary_BlendSpace.generated.h"

class UBlendSpace;
class UBlendSpace1D;

UCLASS()
class CSCORE_API UCsScriptLibrary_BlendSpace : public UObject
{ 
	GENERATED_UCLASS_BODY() 

// Load
#pragma region
public:

	/**
	* Load a BlendSpace at the given Path.
	* 
	* @param Context	The calling context.
	* @param Path		SoftObjectPath to the BlendSpace to load.
	* return			BlendSpace
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Anim|Blend Space", meta = (AutoCreateRefTerm = "Context,Path"))
	static UBlendSpace* LoadBySoftObjectPath(const FString& Context, const FSoftObjectPath& Path);

	/**
	* Load a BlendSpace at the given Path.
	* 
	* @param Context	The calling context.
	* @param Path		FString path to the BlendSpace to load.
	* return			BlendSpace
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Anim|Blend Space", meta = (AutoCreateRefTerm = "Context,Path"))
	static UBlendSpace* LoadByStringPath(const FString& Context, const FString& Path);

	/**
	* Load a BlendSpace1D at the given Path.
	* 
	* @param Context	The calling context.
	* @param Path		SoftObjectPath to the BlendSpace1D to load.
	* return			BlendSpace1D
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Anim|Blend Space", meta = (AutoCreateRefTerm = "Context,Path"))
	static UBlendSpace1D* Load1DBySoftObjectPath(const FString& Context, const FSoftObjectPath& Path);

	/**
	* Load a BlendSpace1D at the given Path.
	* 
	* @param Context	The calling context.
	* @param Path		FString path to the BlendSpace1D to load.
	* return			BlendSpace1D
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Anim|Blend Space", meta = (AutoCreateRefTerm = "Context,Path"))
	static UBlendSpace1D* Load1DByStringPath(const FString& Context, const FString& Path);

#pragma endregion Load

// Get
#pragma region

	/**
	* Get BlendSpace value associated with member at Path for Object.
	* 
	* @param Context	The calling context.
	* @param Object
	* @param Path
	* @param OutSuccess	(out)
	* @param Log		(optional)
	* return			BlendSpace.
	*/
	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Anim|Blend Space", meta = (AutoCreateRefTerm = "Context,Path"))
	static UBlendSpace* GetByPath(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess);

	/**
	* Get BlendSpace1D value associated with member at Path for Object.
	* 
	* @param Context	The calling context.
	* @param Object
	* @param Path
	* @param OutSuccess	(out)
	* @param Log		(optional)
	* return			BlendSpace1D.
	*/
	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Anim|Blend Space", meta = (AutoCreateRefTerm = "Context,Path"))
	static UBlendSpace1D* Get1DByPath(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess);

#pragma endregion Get
};
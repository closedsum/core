// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"

#include "CsScriptLibrary_SkeletalMesh.generated.h"

class USkeletalMesh;

UCLASS()
class CSCORE_API UCsScriptLibrary_SkeletalMesh : public UObject
{ 
	GENERATED_UCLASS_BODY() 

// Load
#pragma region
public:

	/**
	* Load a SkeletalMesh at the given Path.
	* 
	* @param Context	The calling context.
	* @param Path		SoftObjectPath to the SkeletalMesh to load.
	* return			SkeletalMesh
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|SkeletalMesh", meta = (AutoCreateRefTerm = "Context,Path"))
	static USkeletalMesh* LoadBySoftObjectPath(const FString& Context, const FSoftObjectPath& Path);

	/**
	* Load a SkeletalMesh at the given Path.
	* 
	* @param Context	The calling context.
	* @param Path		FString path to the SkeletalMesh to load.
	* return			SkeletalMesh
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|SkeletalMesh", meta = (AutoCreateRefTerm = "Context,Path"))
	static USkeletalMesh* LoadByStringPath(const FString& Context, const FString& Path);

#pragma endregion Load

// Get
#pragma region
public:

	/**
	* Get the SkeletalMesh value at the give Path for Object.
	* 
	* @param Context	The calling context.
	* @param Object
	* @param Path		Full variable path to the SkeletalMesh value on Object.
	* @param OutSuccess	(out)
	* return			SkeletalMesh
	*/
	UFUNCTION(BlueprintPure, Category = "CsCore|Library|SkeletalMesh", meta = (AutoCreateRefTerm = "Context,Path"))
	static USkeletalMesh* GetByPath(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess);

#pragma endregion Get
};
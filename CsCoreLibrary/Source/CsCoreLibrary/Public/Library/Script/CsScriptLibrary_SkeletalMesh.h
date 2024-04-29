// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "Types/CsTypes_SkeletalMesh.h"

#include "CsScriptLibrary_SkeletalMesh.generated.h"

class USkeletalMesh;

UCLASS()
class CSCORELIBRARY_API UCsScriptLibrary_SkeletalMesh : public UObject
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
	UFUNCTION(BlueprintCallable, Category = "CsCoreLibrary|Library|SkeletalMesh", meta = (AutoCreateRefTerm = "Context,Path"))
	static USkeletalMesh* LoadBySoftObjectPath(const FString& Context, const FSoftObjectPath& Path);

	/**
	* Load a SkeletalMesh at the given Path.
	* 
	* @param Context	The calling context.
	* @param Path		FString path to the SkeletalMesh to load.
	* return			SkeletalMesh
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCoreLibrary|Library|SkeletalMesh", meta = (AutoCreateRefTerm = "Context,Path"))
	static USkeletalMesh* LoadByStringPath(const FString& Context, const FString& Path);

#pragma endregion Load

// Unload
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "CsCoreLibrary|Library|SkeletalMesh", meta = (DisplayName = "Unload (FCsSkeletalMesh)", CompactNodeTitle = "Unload"))
	static void FCsSkeletalMesh_Unload(UPARAM(ref) FCsSkeletalMesh& Mesh)
	{
		Mesh.Unload();
	}

	UFUNCTION(BlueprintCallable, Category = "CsCoreLibrary|Library|SkeletalMesh", meta = (DisplayName = "Unload (TArray<FCsSkeletalMesh>)", CompactNodeTitle = "Unload"))
	static void TArray_FCsSkeletalMesh_Unload(UPARAM(ref) TArray<FCsSkeletalMesh>& Meshes)
	{
		for (FCsSkeletalMesh& Mesh : Meshes)
		{
			Mesh.Unload();
		}
	}

#pragma endregion Unload

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
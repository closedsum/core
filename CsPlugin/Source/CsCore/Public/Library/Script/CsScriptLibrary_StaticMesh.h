// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"

#include "CsScriptLibrary_StaticMesh.generated.h"

class UStaticMesh;

UCLASS()
class CSCORE_API UCsScriptLibrary_StaticMesh : public UObject
{ 
	GENERATED_UCLASS_BODY() 

// Load
#pragma region
public:

	/**
	* Load a StaticMesh at the given Path.
	* 
	* @param Context	The calling context.
	* @param Path		SoftObjectPath to the StaticMesh to load.
	* return			StaticMesh
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|StaticMesh", meta = (AutoCreateRefTerm = "Context,Path"))
	static UStaticMesh* LoadBySoftObjectPath(const FString& Context, const FSoftObjectPath& Path);

	/**
	* Load a StaticMesh at the given Path.
	* 
	* @param Context	The calling context.
	* @param Path		FString path to the StaticMesh to load.
	* return			StaticMesh
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|StaticMesh", meta = (AutoCreateRefTerm = "Context,Path"))
	static UStaticMesh* LoadByStringPath(const FString& Context, const FString& Path);

#pragma endregion Load
};
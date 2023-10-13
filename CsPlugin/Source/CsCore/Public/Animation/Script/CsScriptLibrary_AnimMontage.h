// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"

#include "CsScriptLibrary_AnimMontage.generated.h"

class UAnimMontage;

UCLASS()
class CSCORE_API UCsScriptLibrary_AnimMontage : public UObject
{ 
	GENERATED_UCLASS_BODY() 

// Load
#pragma region
public:

	/**
	* Load a AnimMontage at the given Path.
	* 
	* @param Context	The calling context.
	* @param Path		SoftObjectPath to the AnimMontage to load.
	* return			AnimMontage
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|AnimMontage", meta = (AutoCreateRefTerm = "Context,Path"))
	static UAnimMontage* LoadBySoftObjectPath(const FString& Context, const FSoftObjectPath& Path);

	/**
	* Load a AnimMontage at the given Path.
	* 
	* @param Context	The calling context.
	* @param Path		FString path to the AnimMontage to load.
	* return			AnimMontage
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|AnimMontage", meta = (AutoCreateRefTerm = "Context,Path"))
	static UAnimMontage* LoadByStringPath(const FString& Context, const FString& Path);

#pragma endregion Load

// Get
#pragma region
public:

	/**
	* Get AnimMontage value associated with member at Path for Object.
	* 
	* @param Context	The calling context.
	* @param Object
	* @param Path
	* @param OutSuccess	(out)
	* @param Log		(optional)
	* return			AnimMontage.
	*/
	UFUNCTION(BlueprintPure, Category = "CsCore|Library|AnimMontage", meta = (AutoCreateRefTerm = "Context,Path"))
	static UAnimMontage* GetByPath(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess);

#pragma endregion Get
};
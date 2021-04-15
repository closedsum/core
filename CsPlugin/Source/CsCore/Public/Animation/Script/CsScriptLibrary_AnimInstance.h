// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"

#include "CsScriptLibrary_AnimInstance.generated.h"

class UAnimBlueprint;
class UAnimBlueprintGeneratedClass;

UCLASS()
class CSCORE_API UCsScriptLibrary_AnimInstance : public UObject
{ 
	GENERATED_UCLASS_BODY() 

// Load
#pragma region
public:

	/**
	* Load a AnimBlueprint at the given Path.
	* 
	* @param Context	The calling context.
	* @param Path		SoftObjectPath to the AnimBlueprint to load.
	* return			AnimBlueprintGeneratedClass
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|AnimInstance", meta = (AutoCreateRefTerm = "Context,Path"))
	static UAnimBlueprint* LoadBySoftObjectPath(const FString& Context, const FSoftObjectPath& Path);

	/**
	* Load a AnimBlueprint at the given Path.
	* 
	* @param Context	The calling context.
	* @parma Path		FString path to the AnimBlueprint to load.
	* return			AnimBlueprintGeneratedClass
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|AnimInstance", meta = (AutoCreateRefTerm = "Context,Path"))
	static UAnimBlueprint* LoadByStringPath(const FString& Context, const FString& Path);

#pragma endregion Load

// Get
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|AnimInstance", meta = (AutoCreateRefTerm = "Context,Path"))
	static UAnimBlueprintGeneratedClass* GetGeneratedClass(const FString& Context, UAnimBlueprint* Blueprint);

#pragma endregion Get
};
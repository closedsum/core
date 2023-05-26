// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
// Blueprint
#include "Animation/AnimBlueprintGeneratedClass.h"

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
	* return			AnimBlueprint
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|AnimInstance", meta = (AutoCreateRefTerm = "Context,Path"))
	static UAnimBlueprint* LoadBySoftObjectPath(const FString& Context, const FSoftObjectPath& Path);

	/**
	* Load a AnimBlueprint at the given Path.
	* 
	* @param Context	The calling context.
	* @param Path		FString path to the AnimBlueprint to load.
	* return			AnimBlueprint
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|AnimInstance", meta = (AutoCreateRefTerm = "Context,Path"))
	static UAnimBlueprint* LoadByStringPath(const FString& Context, const FString& Path);

	/**
	* Load a AnimBlueprint at the given Path and get the UClass (Generated Class) associated with the AnimBlueprint.
	* 
	* @param Context	The calling context.
	* @param Path		FString path to the AnimBlueprint to load.
	* return			AnimBlueprint
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|AnimInstance", meta = (AutoCreateRefTerm = "Context,Path"))
	static UAnimBlueprintGeneratedClass* LoadAndGetGeneratedClassByStringPath(const FString& Context, const FString& Path);

#pragma endregion Load

// Get
#pragma region
public:

	/**
	* Get the UClass (Generated Class) associated with the anim blueprint, Blueprint.
	* 
	* @param Context	The calling context.
	* @param Blueprint	
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|AnimInstance", meta = (AutoCreateRefTerm = "Context"))
	static UAnimBlueprintGeneratedClass* GetGeneratedClass(const FString& Context, UAnimBlueprint* Blueprint);

#pragma endregion Get
};
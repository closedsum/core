// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "Animation/CsTypes_Anim.h"
// Blueprint
#include "Animation/AnimBlueprintGeneratedClass.h"

#include "CsScriptLibrary_AnimInstance.generated.h"

class UAnimBlueprint;
class UAnimBlueprintGeneratedClass;

UCLASS()
class CSCORELIBRARY_API UCsScriptLibrary_AnimInstance : public UObject
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
	UFUNCTION(BlueprintCallable, Category = "CsCoreLibrary|Library|AnimInstance", meta = (AutoCreateRefTerm = "Context,Path"))
	static UAnimBlueprint* LoadBySoftObjectPath(const FString& Context, const FSoftObjectPath& Path);

	/**
	* Load a AnimBlueprint at the given Path.
	* 
	* @param Context	The calling context.
	* @param Path		FString path to the AnimBlueprint to load.
	* return			AnimBlueprint
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCoreLibrary|Library|AnimInstance", meta = (AutoCreateRefTerm = "Context,Path"))
	static UAnimBlueprint* LoadByStringPath(const FString& Context, const FString& Path);

	/**
	* Load a AnimBlueprint at the given Path and get the UClass (Generated Class) associated with the AnimBlueprint.
	* 
	* @param Context	The calling context.
	* @param Path		FString path to the AnimBlueprint to load.
	* return			AnimBlueprint
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCoreLibrary|Library|AnimInstance", meta = (AutoCreateRefTerm = "Context,Path"))
	static UAnimBlueprintGeneratedClass* LoadAndGetGeneratedClassByStringPath(const FString& Context, const FString& Path);

#pragma endregion Load

// Unload
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "CsCoreLibrary|Library|AnimInstance", meta = (DisplayName = "Unload (FCsAnimBlueprint)", CompactNodeTitle = "Unload"))
	static void FCsAnimBlueprint_Unload(UPARAM(ref) FCsAnimBlueprint& AnimBlueprint)
	{
		AnimBlueprint.Unload();
	}

#pragma endregion Unload

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
	UFUNCTION(BlueprintPure, Category = "CsCoreLibrary|Library|AnimInstance", meta = (AutoCreateRefTerm = "Context"))
	static UAnimBlueprintGeneratedClass* GetGeneratedClass(const FString& Context, UAnimBlueprint* Blueprint);

	/**
	* Get AnimBlueprintGeneratedClass value associated with member at Path for Object.
	* 
	* @param Context	The calling context.
	* @param Object
	* @param Path
	* @param OutSuccess	(out)
	* @param Log		(optional)
	* return			AnimBlueprintGeneratedClass.
	*/
	UFUNCTION(BlueprintPure, Category = "CsCoreLibrary|Library|AnimInstance", meta = (AutoCreateRefTerm = "Context,Path"))
	static UAnimBlueprintGeneratedClass* GetClassByPath(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess);

#pragma endregion Get
};
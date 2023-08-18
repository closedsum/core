// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "UObject/Object.h"

#include "CsScriptLibrary_Character.generated.h"

class ACharacter;

UCLASS()
class CSCORE_API UCsScriptLibrary_Character : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	/**
	* Spawn a Character
	*
	* @param Context			The calling context
	* @param WorldContextObject
	* return					Character
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Character", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static ACharacter* Spawn(const FString& Context, const UObject* WorldContextObject);

// Get
#pragma region
public:

	/**
	* Get an Character with the given Tag (checks AActor->Tags)
	* NOTE: Find the FIRST Character the given Tag.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Tag
	* return				Actor
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Character", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Tag"))
	static ACharacter* GetByTag(const FString& Context, UObject* WorldContextObject, const FName& Tag);

	/**
	* Get an Character with the given Tags (checks AActor->Tags)
	* NOTE: Find the FIRST Character the given Tag.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Tag
	* return				Actor
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Character", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static ACharacter* GetByTags(const FString& Context, UObject* WorldContextObject, const TArray<FName>& Tags);

	/**
	* Get a list of Actors with the given Tag (checks AActor->Tags).
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Tags
	* @param OutActors		(out)
	* return				Whether any actors were found with Tags.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Character", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static bool GetAnyByTags(const FString& Context, UObject* WorldContextObject, const TArray<FName>& Tags, TArray<ACharacter*>& OutCharacters);

	/**
	* Get an Character with the given Name.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Name
	* return				Character
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Character", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Name"))
	static ACharacter* GetByName(const FString& Context, UObject* WorldContextObject, const FName& Name);

	/**
	* Get an Character with the given Label.
	* NOTE: - More than 1 Character can have the SAME Label in Editor. In this case, the FIRST
	*		  Character found in the search will be returned.
	*		- Only valid in Editor.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Name
	* return				Character
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Character", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Label"))
	static ACharacter* GetByLabel(const FString& Context, UObject* WorldContextObject, const FString& Label);

#pragma endregion Get
};
// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "UObject/Object.h"

#include "CsScriptLibrary_ScriptableCharacter.generated.h"

class ACharacter;

UCLASS()
class CSJS_API UCsScriptLibrary_ScriptableCharacter : public UObject
{
	GENERATED_UCLASS_BODY()

// Get
#pragma region
public:

	/**
	* Get all Scriptable Characters.
	*  Characters MUST implement the interface: ICsScriptableActor.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param OutCharacters	(out)
	* return				Whether GetAll was executed successfully or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsJs|Library|Character|Scriptable", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static bool GetAll(const FString& Context, const UObject* WorldContextObject, TArray<ACharacter*>& OutCharacters);

	/**
	* Get an Scriptable Character with the given Tag (checks AActor->Tags)
	*  Character MUST implement the interface: ICsScriptableActor.
	* NOTE: Find the FIRST Actor the given Tag.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Tag
	* return				Actor
	*/
	UFUNCTION(BlueprintCallable, Category = "CsJs|Library|Character|Scriptable", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Tag"))
	static ACharacter* GetByTag(const FString& Context, UObject* WorldContextObject, const FName& Tag);

	/**
	* Get a list of Scriptable Characters with the given Tag (checks AActor->Tags).
	*  Characters MUST implement the interface: ICsScriptableActor.
	* 
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Tags
	* @param OutCharacters	(out)
	* return				Whether any actors were found with Tags.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsJs|Library|Character|Scriptable", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static bool GetAnyByTags(const FString& Context, UObject* WorldContextObject, const TArray<FName>& Tags, TArray<ACharacter*>& OutCharacters);

	/**
	* Get an Scriptable Character with the given Name.
	*  Character MUST implement the interface: ICsScriptableActor.
	* 
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Name
	* return				Character
	*/
	UFUNCTION(BlueprintCallable, Category = "CsJs|Library|Character|Scriptable", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Name"))
	static ACharacter* GetByName(const FString& Context, UObject* WorldContextObject, const FName& Name);

	/**
	* Get an Scriptable Character with the given Label.
	*  Character MUST implement the interface: ICsScriptableActor.
	* NOTE: - More than 1 Character can have the SAME Label in Editor. In this case, the FIRST
	*		  Character found in the search will be returned.
	*		- Only valid in Editor.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Name
	* return				Character
	*/
	UFUNCTION(BlueprintCallable, Category = "CsJs|Library|Character|Scriptable", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Label"))
	static ACharacter* GetByLabel(const FString& Context, UObject* WorldContextObject, const FString& Label);

#pragma endregion Get
};
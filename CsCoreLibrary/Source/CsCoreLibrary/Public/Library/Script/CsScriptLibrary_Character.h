// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "Animation/CsTypes_AnimMontage.h"

#include "CsScriptLibrary_Character.generated.h"

class ACharacter;
class UAnimMontage;

UCLASS()
class CSCORELIBRARY_API UCsScriptLibrary_Character : public UObject
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
	UFUNCTION(BlueprintCallable, Category = "CsCoreLibrary|Library|Character", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context"))
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
	UFUNCTION(BlueprintCallable, Category = "CsCoreLibrary|Library|Character", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context,Tag"))
	static ACharacter* GetByTag(const FString& Context, const UObject* WorldContextObject, const FName& Tag);

	/**
	* Get an Character with the given Tags (checks AActor->Tags)
	*  NOTE: Find the FIRST Character the given Tag.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Tag
	* return				Actor
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCoreLibrary|Library|Character", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context"))
	static ACharacter* GetByTags(const FString& Context, const UObject* WorldContextObject, const TArray<FName>& Tags);

	/**
	* Get an Character with the given Tags (checks AActor->Tags)
	*  NOTE: Find the FIRST Character the given Tags.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Tag
	* return				Actor
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCoreLibrary|Library|Character", meta = (DisplayName = "Get by Tags (Checked)", WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context"))
	static ACharacter* GetByTagsChecked(const FString& Context, const UObject* WorldContextObject, const TArray<FName>& Tags, bool& OutSuccess);

	/**
	* Get a list of Actors with the given Tag (checks AActor->Tags).
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Tags
	* @param OutActors		(out)
	* return				Whether any actors were found with Tags.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCoreLibrary|Library|Character", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context"))
	static bool GetAnyByTags(const FString& Context, const UObject* WorldContextObject, const TArray<FName>& Tags, TArray<ACharacter*>& OutCharacters);

	/**
	* Get a list of Actors with the given Tag (checks AActor->Tags).
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Tags
	* @param OutActors		(out)
	* return				Whether any actors were found with Tags.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCoreLibrary|Library|Character", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context"))
	static bool GetAllByTags(const FString& Context, const UObject* WorldContextObject, const TArray<FName>& Tags, TArray<ACharacter*>& OutCharacters);

	/**
	* Get a list of Actors with the given Tag (checks AActor->Tags).
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Tags
	* @param OutActors		(out)
	* return				Whether any actors were found with Tags.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCoreLibrary|Library|Character", meta = (DisplayName = "Get All by Tags (Checked)", WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context"))
	static void GetAllByTagsChecked(const FString& Context, const UObject* WorldContextObject, const TArray<FName>& Tags, TArray<ACharacter*>& OutCharacters, bool& OutSuccess);

	/**
	* Get an Character with the given Name.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Name
	* return				Character
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCoreLibrary|Library|Character", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context,Name"))
	static ACharacter* GetByName(const FString& Context, const UObject* WorldContextObject, const FName& Name);

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
	UFUNCTION(BlueprintCallable, Category = "CsCoreLibrary|Library|Character", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context,Label"))
	static ACharacter* GetByLabel(const FString& Context, const UObject* WorldContextObject, const FString& Label);

#pragma endregion Get

// Anim
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "CsCoreLibrary|Library|Character", meta = (AutoCreateRefTerm = "Context,Params"))
	static float Montage_Play(const FString& Context, ACharacter* Character, const FCsAnimMontage_PlayParams& Params);

#pragma endregion Anim
};
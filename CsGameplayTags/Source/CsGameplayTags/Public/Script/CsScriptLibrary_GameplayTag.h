// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "GameplayTagContainer.h"

#include "CsScriptLibrary_GameplayTag.generated.h"

UCLASS()
class CSGAMEPLAYTAGS_API UCsScriptLibrary_GameplayTag : public UObject
{ 
	GENERATED_UCLASS_BODY() 

// Tag
#pragma region
public:

	/**
	* Get the GameplayTag associated with Name: TagName.
	* 
	* @param Context	The calling context
	* @param TagName	The Name of the GameplayTag
	* return			GameplayTag associated with TagName.
	*/
	UFUNCTION(BlueprintPure, Category = "CsGameplayTags|Library", meta = (CallableWithoutWorldContext, AutoCreateRefTerm = "TagName"))
	static FGameplayTag Get(const FString& Context, const FName& TagName);

	/**
	* Get the GameplayTag associated with Name: TagName.
	* 
	* @param Context	The calling context
	* @param TagName	The Name of the GameplayTag
	* @param OutSuccess	(out)
	* return			GameplayTag associated with TagName.
	*/
	UFUNCTION(BlueprintPure, Category = "CsGameplayTags|Library", meta = (DisplayName = "Get (Checked)", CallableWithoutWorldContext, AutoCreateRefTerm = "TagName"))
	static FGameplayTag GetChecked(const FString& Context, const FName& TagName, bool& OutSuccess);

	/**
	* Get the GameplayTag associated with String: TagName.
	* 
	* @param Context	The calling context
	* @param TagName	The Name of the GameplayTag
	* return			GameplayTag associated with TagName.
	*/
	UFUNCTION(BlueprintPure, Category = "CsGameplayTags|Library", meta = (CallableWithoutWorldContext, AutoCreateRefTerm = "TagName"))
	static FGameplayTag GetByString(const FString& Context, const FString& TagName);

	/**
	* Get the GameplayTag associated with String: TagName.
	* 
	* @param Context	The calling context
	* @param TagName	The Name of the GameplayTag
	* @param OutSuccess	(out)
	* return			GameplayTag associated with TagName.
	*/
	UFUNCTION(BlueprintPure, Category = "CsGameplayTags|Library", meta = (DisplayName = "Get by String (Checked)", CallableWithoutWorldContext, AutoCreateRefTerm = "TagName"))
	static FGameplayTag GetByStringChecked(const FString& Context, const FString& TagName, bool& OutSuccess);

	/** 
	* Returns true if the values are equal (A == B) 
	*/
	UFUNCTION(BlueprintPure, Category = "CsGameplayTags|Library",meta = (DisplayName = "Equal (GameplayTag)", CompactNodeTitle="==", BlueprintThreadSafe))
	static bool EqualEqual_GameplayTagName(const FGameplayTag& A, const FName& B)
	{
		return A.GetTagName() == B;
	}

	/** 
	* Returns true if the values are equal (A == B) 
	*/
	UFUNCTION(BlueprintPure, Category = "CsGameplayTags|Library",meta = (DisplayName = "Equal (GameplayTag)", CompactNodeTitle="==", BlueprintThreadSafe))
	static bool EqualEqual_GameplayTagString(const FGameplayTag& A, const FString& B)
	{
		return A.GetTagName() == FName(*B);
	}

	/** 
	* Returns true if the values are equal (A == B) 
	*/
	UFUNCTION(BlueprintPure, Category = "CsGameplayTags|Library",meta = (DisplayName = "Not Equal (GameplayTag)", CompactNodeTitle="!=", BlueprintThreadSafe))
	static bool NotEqual_GameplayTagName(const FGameplayTag& A, const FName& B)
	{
		return A.GetTagName() != B;
	}

	/** 
	* Returns true if the values are equal (A == B) 
	*/
	UFUNCTION(BlueprintPure, Category = "CsGameplayTags|Library",meta = (DisplayName = "Not Equal (GameplayTag)", CompactNodeTitle="!=", BlueprintThreadSafe))
	static bool NotEqual_GameplayTagString(const FGameplayTag& A, const FString& B)
	{
		return A.GetTagName() != FName(*B);
	}

#pragma endregion Tag

// Container
#pragma region
public:

	UFUNCTION(BlueprintPure, Category = "CsGameplayTags|Library", meta = (CallableWithoutWorldContext, AutoCreateRefTerm = "GameplayTag"))
	static FGameplayTagContainer MakeContainer(const FGameplayTag& GameplayTag)
	{
		return FGameplayTagContainer(GameplayTag);
	}

#pragma endregion Settings
};
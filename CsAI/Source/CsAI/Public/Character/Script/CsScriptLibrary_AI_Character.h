// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "UObject/Object.h"

#include "CsScriptLibrary_AI_Character.generated.h"

class ACharacter;

UCLASS()
class CSAI_API UCsScriptLibrary_AI_Character : public UObject
{
	GENERATED_UCLASS_BODY()

public:

// Blackboard
#pragma region
public:

	/**
	* Set the Character's Blackboard Object Key value associated with KeyName.
	*
	* @param Context		The calling context.
	* @param Character
	* @param KeyName
	* @parma ObjectValue
	* return				Whether the value was set or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Library|Character", meta = (AutoCreateRefTerm = "Context,KeyName"))
	static bool Blackboard_SetValueAsObject(const FString& Context, const ACharacter* Character, const FName& KeyName, UObject* ObjectValue);

	/**
	* Set the Character's Blackboard Class Key value associated with KeyName.
	*
	* @param Context		The calling context.
	* @param Character
	* @param KeyName
	* @parma ClassValue
	* return				Whether the value was set or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Library|Character", meta = (AutoCreateRefTerm = "Context,KeyName"))
	static bool Blackboard_SetValueAsClass(const FString& Context, const ACharacter* Character, const FName& KeyName, UClass* ClassValue);

	/**
	* Set the Character's Blackboard Vector (Vector3d) Key value associated with KeyName.
	*
	* @param Context		The calling context.
	* @param Character
	* @param KeyName
	* @parma VectorValue
	* return				Whether the value was set or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Library|Character", meta = (AutoCreateRefTerm = "Context,KeyName,VectorValue"))
	static bool Blackboard_SetValueAsVector(const FString& Context, const ACharacter* Character, const FName& KeyName, const FVector& VectorValue);

#pragma endregion Blackboard
};
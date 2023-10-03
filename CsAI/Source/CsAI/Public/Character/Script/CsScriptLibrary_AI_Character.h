// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "BehaviorTree/BehaviorTreeTypes.h"

#include "CsScriptLibrary_AI_Character.generated.h"

class ACharacter;
class AAIController;

UCLASS()
class CSAI_API UCsScriptLibrary_AI_Character : public UObject
{
	GENERATED_UCLASS_BODY()

public:

// Controller
#pragma region
public:

	/**
	* Get the AI Controller associated with Character.
	* 
	* @param Context	The calling context.
	* @param Character
	* return			AI Controller.
	*/
	UFUNCTION(BlueprintPure, Category = "CsAI|Library|Character", meta = (AutoCreateRefTerm = "Context"))
	static AAIController* GetController(const FString& Context, const ACharacter* Character);

#pragma endregion Controller

// Blackboard
#pragma region
public:

	// Object
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
	UFUNCTION(BlueprintCallable, Category = "CsAI|Library|Character", meta = (DisplayName = "Blackboard: Set Value as Object", AutoCreateRefTerm = "Context,KeyName"))
	static bool Blackboard_SetValueAsObject(const FString& Context, const ACharacter* Character, const FName& KeyName, UObject* ObjectValue);

	/**
	* Set the Character's Blackboard Object Key value associated with KeySelector.
	*
	* @param Context		The calling context.
	* @param Character
	* @param KeySelector
	* @parma ObjectValue
	* return				Whether the value was set or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Library|Character", meta = (DisplayName = "Blackboard: Set Value as Object (Selector)", AutoCreateRefTerm = "Context,KeySelector"))
	static bool Blackboard_SetValueBySelectorAsObject(const FString& Context, const ACharacter* Character, const FBlackboardKeySelector& KeySelector, UObject* ObjectValue);

	/**
	* Get the Character's Blackboard Object Key value associated with KeyName.
	*
	* @param Context		The calling context.
	* @param Character
	* @param KeyName
	* return				Object.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Library|Character", meta = (DisplayName = "Blackboard: Get Value as Object", AutoCreateRefTerm = "Context,KeyName"))
	static UObject* Blackboard_GetValueAsObject(const FString& Context, const ACharacter* Character, const FName& KeyName);

	/**
	* Get the Character's Blackboard Object Key value associated with KeySelector.
	*
	* @param Context		The calling context.
	* @param Character
	* @param KeySelector
	* return				Object.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Library|Character", meta = (DisplayName = "Blackboard: Get Value as Object (Selector)", AutoCreateRefTerm = "Context,KeySelector"))
	static UObject* Blackboard_GetValueBySelectorAsObject(const FString& Context, const ACharacter* Character, const FBlackboardKeySelector& KeySelector);

#pragma endregion Object

public:

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
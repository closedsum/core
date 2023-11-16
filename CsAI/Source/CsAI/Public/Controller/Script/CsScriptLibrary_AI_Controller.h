// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "Types/CsTypes_AI.h"
#include "BehaviorTree/BehaviorTreeTypes.h"

#include "CsScriptLibrary_AI_Controller.generated.h"

class AAIController;
class UBlackboardComponent;
class APawn;

UCLASS()
class CSAI_API UCsScriptLibrary_AI_Controller : public UObject
{
	GENERATED_UCLASS_BODY()

// Blackboard
#pragma region
public:

	/**
	* Get the Blackboard associated with Controller.
	*
	* @param Context	The calling context.
	* @param Controller
	* return			Blackboard
	*/
	UFUNCTION(BlueprintPure, Category = "CsAI|Library|Controller", meta = (AutoCreateRefTerm = "Context"))
	static UBlackboardComponent* GetBlackboard(const FString& Context, const AAIController* Controller);

	// Object
#pragma region
public:

	/**
	* Set the Controller's Blackboard Object Key value associated with KeyName.
	*
	* @param Context		The calling context.
	* @param Controller
	* @param KeyName
	* @parma ObjectValue
	* return				Whether the value was set or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Library|Controller", meta = (DisplayName = "Blackboard: Set Object", AutoCreateRefTerm = "Context,KeyName"))
	static bool Blackboard_SetObject(const FString& Context, const AAIController* Controller, const FName& KeyName, UObject* ObjectValue);

	/**
	* Set the Controller's Blackboard Object Key value associated with KeySelector.
	*
	* @param Context		The calling context.
	* @param Controller
	* @param KeySelector
	* @parma ObjectValue
	* return				Whether the value was set or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Library|Controller", meta = (DisplayName = "Blackboard: Set Object (Selector)", AutoCreateRefTerm = "Context,KeySelector"))
	static bool Blackboard_SetObjectBySelector(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, UObject* ObjectValue);

	/**
	* Set the Controller's Blackboard Object Key value associated with KeyName.
	*
	* @param Context		The calling context.
	* @param Controller
	* @param KeyName
	* @parma ObjectValue
	* return				Whether the value was set or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Library|Controller", meta = (DisplayName = "Blackboard: Set Object (Checked)", AutoCreateRefTerm = "Context,KeyName"))
	static bool Blackboard_SetObjectChecked(const FString& Context, const AAIController* Controller, const FName& KeyName, UObject* ObjectValue);

	/**
	* Set the Controller's Blackboard Object Key value associated with KeySelector.
	*
	* @param Context		The calling context.
	* @param Controller
	* @param KeySelector
	* @parma ObjectValue
	* return				Whether the value was set or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Library|Controller", meta = (DisplayName = "Blackboard: Set Object (Selector | Checked)", AutoCreateRefTerm = "Context,KeySelector"))
	static bool Blackboard_SetObjectBySelectorChecked(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, UObject* ObjectValue);

	/**
	* Set the Controller's Blackboard Object Key value associated with KeyName.
	*  ObjectValue MUST be Valid (NOT NULL and NOT Marked as Garbage).
	* 
	* @param Context		The calling context.
	* @param Controller
	* @param KeyName
	* @parma ObjectValue
	* return				Whether the value was set or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Library|Controller", meta = (DisplayName = "Blackboard: Set Object (Not Null)", AutoCreateRefTerm = "Context,KeyName"))
	static bool Blackboard_SetObject2(const FString& Context, const AAIController* Controller, const FName& KeyName, UObject* ObjectValue);

	/**
	* Set the Controller's Blackboard Object Key value associated with KeySelector.
	*  ObjectValue MUST be Valid (NOT NULL and NOT Marked as Garbage).
	* 
	* @param Context		The calling context.
	* @param Controller
	* @param KeySelector
	* @parma ObjectValue
	* return				Whether the value was set or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Library|Controller", meta = (DisplayName = "Blackboard: Set Object (Not Null | Selector)", AutoCreateRefTerm = "Context,KeySelector"))
	static bool Blackboard_SetObjectBySelector2(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, UObject* ObjectValue);

	/**
	* Set the Controller's Blackboard Object Key value associated with KeyName.
	*  ObjectValue MUST be Valid (NOT NULL and NOT Marked as Garbage).
	* 
	* @param Context		The calling context.
	* @param Controller
	* @param KeyName
	* @parma ObjectValue
	* return				Whether the value was set or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Library|Controller", meta = (DisplayName = "Blackboard: Set Object (Not Null | Checked)", AutoCreateRefTerm = "Context,KeyName"))
	static bool Blackboard_SetObjectChecked2(const FString& Context, const AAIController* Controller, const FName& KeyName, UObject* ObjectValue);

	/**
	* Set the Controller's Blackboard Object Key value associated with KeySelector.
	*  ObjectValue MUST be Valid (NOT NULL and NOT Marked as Garbage).
	* 
	* @param Context		The calling context.
	* @param Controller
	* @param KeySelector
	* @parma ObjectValue
	* return				Whether the value was set or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Library|Controller", meta = (DisplayName = "Blackboard: Set Object (Not Null | Selector | Checked)", AutoCreateRefTerm = "Context,KeySelector"))
	static bool Blackboard_SetObjectBySelectorChecked2(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, UObject* ObjectValue);

	/**
	* Get the Controller's Blackboard Object Key value associated with KeyName.
	*
	* @param Context		The calling context.
	* @param Controller
	* @param KeyName
	* @param OutSuccess		(out)
	* return				Object.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Library|Controller", meta = (DisplayName = "Blackboard: Get Object", AutoCreateRefTerm = "Context,KeyName"))
	static UObject* Blackboard_GetObject(const FString& Context, const AAIController* Controller, const FName& KeyName, bool& OutSuccess);

	/**
	* Get the Controller's Blackboard Object Key value associated with KeySelector.
	*
	* @param Context		The calling context.
	* @param Controller
	* @param KeySelector
	* return				Object.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Library|Controller", meta = (DisplayName = "Blackboard: Get Object (Selector)", AutoCreateRefTerm = "Context,KeySelector"))
	static UObject* Blackboard_GetObjectBySelector(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, bool& OutSuccess);

	/**
	* Get the Controller's Blackboard Object Key value associated with KeyName.
	*
	* @param Context		The calling context.
	* @param Controller
	* @param KeyName
	* return				Object.
	*/
	UFUNCTION(BlueprintPure, Category = "CsAI|Library|Controller", meta = (DisplayName = "Blackboard: Get Object (Checked)", AutoCreateRefTerm = "Context,KeyName"))
	static UObject* Blackboard_GetObjectChecked(const FString& Context, const AAIController* Controller, const FName& KeyName, bool& OutSuccess);

	/**
	* Get the Controller's Blackboard Object Key value associated with KeySelector.
	*
	* @param Context		The calling context.
	* @param Controller
	* @param KeySelector
	* return				Object.
	*/
	UFUNCTION(BlueprintPure, Category = "CsAI|Library|Controller", meta = (DisplayName = "Blackboard: Get Object (Selector | Checked)", AutoCreateRefTerm = "Context,KeySelector"))
	static UObject* Blackboard_GetObjectBySelectorChecked(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, bool& OutSuccess);

#pragma endregion Object

	// Pawn
#pragma region
public:

	/**
	* Set the Controller's Blackboard Object Key value as Pawn associated with KeyName.
	*
	* @param Context		The calling context.
	* @param Controller
	* @param KeyName
	* @parma PawnValue
	* return				Whether the value was set or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Library|Controller", meta = (DisplayName = "Blackboard: Set Pawn", AutoCreateRefTerm = "Context,KeyName"))
	static bool Blackboard_SetPawn(const FString& Context, const AAIController* Controller, const FName& KeyName, APawn* PawnValue);

	/**
	* Set the Controller's Blackboard Object Key value as Pawn associated with KeySelector.
	*
	* @param Context		The calling context.
	* @param Controller
	* @param KeySelector
	* @parma PawnValue
	* return				Whether the value was set or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Library|Controller", meta = (DisplayName = "Blackboard: Set Pawn (Selector)", AutoCreateRefTerm = "Context,KeySelector"))
	static bool Blackboard_SetPawnBySelector(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, APawn* PawnValue);

	/**
	* Set the Controller's Blackboard Object Key value as Pawn associated with KeyName.
	*
	* @param Context		The calling context.
	* @param Controller
	* @param KeyName
	* @parma PawnValue
	* return				Whether the value was set or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Library|Controller", meta = (DisplayName = "Blackboard: Set Pawn (Checked)", AutoCreateRefTerm = "Context,KeyName"))
	static bool Blackboard_SetPawnChecked(const FString& Context, const AAIController* Controller, const FName& KeyName, APawn* PawnValue);

	/**
	* Set the Controller's Blackboard Object Key value as Pawn associated with KeySelector.
	*
	* @param Context		The calling context.
	* @param Controller
	* @param KeySelector
	* @parma PawnValue
	* return				Whether the value was set or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Library|Controller", meta = (DisplayName = "Blackboard: Set Pawn (Selector | Checked)", AutoCreateRefTerm = "Context,KeySelector"))
	static bool Blackboard_SetPawnBySelectorChecked(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, APawn* PawnValue);

	/**
	* Set the Controller's Blackboard Object Key value as Pawn associated with KeyName.
	*  PawnValue MUST be Valid (NOT NULL and NOT Marked as Garbage).
	* 
	* @param Context		The calling context.
	* @param Controller
	* @param KeyName
	* @parma PawnValue
	* return				Whether the value was set or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Library|Controller", meta = (DisplayName = "Blackboard: Set Pawn (Not Null)", AutoCreateRefTerm = "Context,KeyName"))
	static bool Blackboard_SetPawn2(const FString& Context, const AAIController* Controller, const FName& KeyName, APawn* PawnValue);

	/**
	* Set the Controller's Blackboard Object Key value as Pawn associated with KeySelector.
	*  PawnValue MUST be Valid (NOT NULL and NOT Marked as Garbage).
	* 
	* @param Context		The calling context.
	* @param Controller
	* @param KeySelector
	* @parma PawnValue
	* return				Whether the value was set or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Library|Controller", meta = (DisplayName = "Blackboard: Set Pawn (Not Null | Selector)", AutoCreateRefTerm = "Context,KeySelector"))
	static bool Blackboard_SetPawnBySelector2(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, APawn* PawnValue);

	/**
	* Set the Controller's Blackboard Object Key value as Pawn associated with KeyName.
	*  PawnValue MUST be Valid (NOT NULL and NOT Marked as Garbage).
	* 
	* @param Context		The calling context.
	* @param Controller
	* @param KeyName
	* @parma PawnValue
	* return				Whether the value was set or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Library|Controller", meta = (DisplayName = "Blackboard: Set Pawn (Not Null | Checked)", AutoCreateRefTerm = "Context,KeyName"))
	static bool Blackboard_SetPawnChecked2(const FString& Context, const AAIController* Controller, const FName& KeyName, APawn* PawnValue);

	/**
	* Set the Controller's Blackboard Object Key value as Pawn associated with KeySelector.
	*  PawnValue MUST be Valid (NOT NULL and NOT Marked as Garbage).
	* 
	* @param Context		The calling context.
	* @param Controller
	* @param KeySelector
	* @parma PawnValue
	* return				Whether the value was set or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Library|Controller", meta = (DisplayName = "Blackboard: Set Pawn (Not Null | Selector | Checked)", AutoCreateRefTerm = "Context,KeySelector"))
	static bool Blackboard_SetPawnBySelectorChecked2(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, APawn* PawnValue);

	/**
	* Get the Controller's Blackboard Object Key value as Pawn associated with KeyName.
	*
	* @param Context		The calling context.
	* @param Controller
	* @param KeyName
	* @param OutSuccess		(out)
	* return				Pawn.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Library|Controller", meta = (DisplayName = "Blackboard: Get Pawn", AutoCreateRefTerm = "Context,KeyName"))
	static APawn* Blackboard_GetPawn(const FString& Context, const AAIController* Controller, const FName& KeyName, bool& OutSuccess);

	/**
	* Get the Controller's Blackboard Object Key value as Pawn associated with KeySelector.
	*
	* @param Context		The calling context.
	* @param Controller
	* @param KeySelector
	* @param OutSuccess		(out)
	* return				Pawn.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Library|Controller", meta = (DisplayName = "Blackboard: Get Pawn (Selector)", AutoCreateRefTerm = "Context,KeySelector"))
	static APawn* Blackboard_GetPawnBySelector(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, bool& OutSuccess);

	/**
	* Get the Controller's Blackboard Object Key value as Pawn associated with KeyName.
	*
	* @param Context		The calling context.
	* @param Controller
	* @param KeyName
	* @param OutSuccess		(out)
	* return				Pawn.
	*/
	UFUNCTION(BlueprintPure, Category = "CsAI|Library|Controller", meta = (DisplayName = "Blackboard: Get Pawn (Checked)", AutoCreateRefTerm = "Context,KeyName"))
	static APawn* Blackboard_GetPawnChecked(const FString& Context, const AAIController* Controller, const FName& KeyName, bool& OutSuccess);

	/**
	* Get the Controller's Blackboard Object Key value as Pawn associated with KeySelector.
	*
	* @param Context		The calling context.
	* @param Controller
	* @param KeySelector
	* return				Pawn.
	*/
	UFUNCTION(BlueprintPure, Category = "CsAI|Library|Controller", meta = (DisplayName = "Blackboard: Get Pawn (Selector | Checked)", AutoCreateRefTerm = "Context,KeySelector"))
	static APawn* Blackboard_GetPawnBySelectorChecked(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, bool& OutSuccess);

#pragma endregion Pawn

	// Enum
#pragma region
public:

	/**
	* Set the Controller's Blackboard Enum Key value associated with KeyName.
	*
	* @param Context		The calling context.
	* @param Controller
	* @param KeyName
	* @parma EnumValue
	* return				Whether the value was set or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Library|Controller", meta = (DisplayName = "Blackboard: Set Enum", AutoCreateRefTerm = "Context,KeyName,EnumValue"))
	static bool Blackboard_SetEnum(const FString& Context, const AAIController* Controller, const FName& KeyName, const uint8& EnumValue);

	/**
	* Set the Controller's Blackboard Enum Key value associated with KeySelector.
	*
	* @param Context		The calling context.
	* @param Controller
	* @param KeySelector
	* @parma EnumValue
	* return				Whether the value was set or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Library|Controller", meta = (DisplayName = "Blackboard: Set Enum (Selector)", AutoCreateRefTerm = "Context,KeySelector,EnumValue"))
	static bool Blackboard_SetEnumBySelector(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, const uint8& EnumValue);

	/**
	* Set the Controller's Blackboard Enum Key value associated with KeyName.
	*
	* @param Context		The calling context.
	* @param Controller
	* @param KeyName
	* @parma EnumValue
	* return				Whether the value was set or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Library|Controller", meta = (DisplayName = "Blackboard: Set Enum (Checked)", AutoCreateRefTerm = "Context,KeyName,EnumValue"))
	static bool Blackboard_SetEnumChecked(const FString& Context, const AAIController* Controller, const FName& KeyName, const uint8& EnumValue);

	/**
	* Set the Controller's Blackboard Enum Key value associated with KeySelector.
	*
	* @param Context		The calling context.
	* @param Controller
	* @param KeySelector
	* @parma EnumValue
	* return				Whether the value was set or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Library|Controller", meta = (DisplayName = "Blackboard: Set Enum (Selector | Checked)", AutoCreateRefTerm = "Context,KeySelector,EnumValue"))
	static bool Blackboard_SetEnumBySelectorChecked(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, const uint8& EnumValue);

	/**
	* Get the Controller's Blackboard Enum Key value associated with KeyName.
	*
	* @param Context		The calling context.
	* @param Controller
	* @param KeyName
	* @param OutSuccess		(out)
	* return				Enum (as Byte).
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Library|Controller", meta = (DisplayName = "Blackboard: Get Enum", AutoCreateRefTerm = "Context,KeyName"))
	static uint8 Blackboard_GetEnum(const FString& Context, const AAIController* Controller, const FName& KeyName, bool& OutSuccess);

	/**
	* Get the Controller's Blackboard Enum Key value associated with KeySelector.
	*
	* @param Context		The calling context.
	* @param Controller
	* @param KeySelector
	* @param OutSuccess		(out)
	* return				Enum (as Byte).
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Library|Controller", meta = (DisplayName = "Blackboard: Get Enum (Selector)", AutoCreateRefTerm = "Context,KeySelector"))
	static uint8 Blackboard_GetEnumBySelector(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, bool& OutSuccess);

	/**
	* Get the Controller's Blackboard Enum Key value associated with KeyName.
	*
	* @param Context		The calling context.
	* @param Controller
	* @param KeyName
	* @param OutSuccess		(out)
	* return				Enum (as Byte).
	*/
	UFUNCTION(BlueprintPure, Category = "CsAI|Library|Controller", meta = (DisplayName = "Blackboard: Get Enum (Checked)", AutoCreateRefTerm = "Context,KeyName"))
	static uint8 Blackboard_GetEnumChecked(const FString& Context, const AAIController* Controller, const FName& KeyName, bool& OutSuccess);

	/**
	* Get the Controller's Blackboard Enum Key value associated with KeySelector.
	*
	* @param Context		The calling context.
	* @param Controller
	* @param KeySelector
	* @param OutSuccess		(out)
	* return				Enum (as Byte).
	*/
	UFUNCTION(BlueprintPure, Category = "CsAI|Library|Controller", meta = (DisplayName = "Blackboard: Get Enum (Selector | Checked)", AutoCreateRefTerm = "Context,KeySelector"))
	static uint8 Blackboard_GetEnumBySelectorChecked(const FString& Context, const AAIController* Controller, const FBlackboardKeySelector& KeySelector, bool& OutSuccess);

#pragma endregion Enum

#pragma endregion Blackboard

public:

	/** 
	* Makes AI go toward specified destination
	* 
	* @param MoveRequest	details about move
	* @return				struct holding MoveId and enum code
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Library|Controller", meta = (AutoCreateRefTerm = "Context,MoveRequest"))
	static FCsPathFollowingRequestResult MoveTo(const FString& Context, AAIController* Controller, const FCsAIMoveRequest& MoveRequest);

	/** 
	* Makes AI go toward specified destination
	* 
	* @param MoveRequest	details about move
	* @param OutSuccess
	* @return				struct holding MoveId and enum code
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Library|Controller", meta = (DisplayName = "Move To (Checked)", AutoCreateRefTerm = "Context,MoveRequest"))
	static FCsPathFollowingRequestResult MoveToChecked(const FString& Context, AAIController* Controller, const FCsAIMoveRequest& MoveRequest, bool& OutSuccess);

	/**
	* Call Controller->GetDefaultNavigationFilterClass()
	*
	* @param Context	The calling context.
	* @param Controller
	* return			Default Navigation Filter Class
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Library|Controller")
	static TSubclassOf<UNavigationQueryFilter> GetDefaultNavigationFilterClass(const FString& Context, AAIController* Controller);
};
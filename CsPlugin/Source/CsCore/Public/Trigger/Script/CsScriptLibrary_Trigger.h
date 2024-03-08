// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"

#include "CsScriptLibrary_Trigger.generated.h"

class ATriggerBase;

UCLASS()
class CSCORE_API UCsScriptLibrary_Trigger : public UObject
{
	GENERATED_UCLASS_BODY()

// Get
#pragma region
public:

	/**
	* Get all Triggers of type: ATriggerBase.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param OutTriggers	(out)
	* return				
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Trigger", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context"))
	static bool GetAll(const FString& Context, const UObject* WorldContextObject, TArray<ATriggerBase*>& OutTriggers);

	/**
	* Get a Trigger with the given Tag (checks ATriggerBase->Tags)
	* NOTE: Find the FIRST Trigger the given Tag.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Tag
	* return				Trigger
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Trigger", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context,Tag"))
	static ATriggerBase* GetByTag(const FString& Context, const UObject* WorldContextObject, const FName& Tag);

	/**
	* Get an Trigger with the given Tags (checks ATriggerBase->Tags)
	* NOTE: Find the FIRST Trigger the given Tags.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Tags
	* return				Trigger
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Trigger", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context,Tags"))
	static ATriggerBase* GetByTags(const FString& Context, const UObject* WorldContextObject, const TArray<FName>& Tags);

	/**
	* Get a list of Triggers with the given Tag (checks ATriggerBase->Tags).
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Tags
	* @param OutTriggers	(out)
	* return				Whether any Triggers were found with Tags.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Trigger", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context"))
	static bool GetAnyByTags(const FString& Context, const UObject* WorldContextObject, const TArray<FName>& Tags, TArray<ATriggerBase*>& OutTriggers);

	/**
	* Get a Trigger with the given Name.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Name
	* return				Trigger
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Trigger", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context,Name"))
	static ATriggerBase* GetByName(const FString& Context, const UObject* WorldContextObject, const FName& Name);

	/**
	* Get an Trigger with the given Label.
	* NOTE: - More than 1 Trigger can have the SAME Label in Editor. In this case, the FIRST
	*		  Trigger found in the search will be returned.
	*		- Only valid in Editor.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Name
	* return				Trigger
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Trigger", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context,Label"))
	static ATriggerBase* GetByLabel(const FString& Context, const UObject* WorldContextObject, const FString& Label);

#pragma endregion Get
};
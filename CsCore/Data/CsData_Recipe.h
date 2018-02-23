// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Data/CsData.h"
#include "Types/CsTypes_Recipe.h"
#include "CsData_Recipe.generated.h"

UCLASS(Abstract, hidecategories = (Object, Actor, Replication, Rendering, Input, "Actor Tick"))
class CSCORE_API ACsData_Recipe : public ACsData
{
	GENERATED_UCLASS_BODY()

	TCsRecipeType BaseRecipeType;

	TCsRecipeType GetBaseRecipeType();

// Stats
#pragma region
public:

	/** ShortCode for the Item created from the Recipe */
	virtual FName GetCreatedItem();

#pragma endregion Stats

// Ingredients
#pragma region
public:

	/** List of all Ingredients (Item, Count, ... etc) used in the Recipe */
	virtual TArray<FCsRecipeIngredient>* GetIngredients();

	/** Time to process single Recipe */
	UFUNCTION(BlueprintCallable, Category = "Ingredients")
	virtual float GetTime();
	/** Whether to use BulkTime */
	UFUNCTION(BlueprintCallable, Category = "Ingredients")
	virtual bool GetUseBulkTime();
	/** Time to process many Recipes at once (i.e. Bulk)*/
	UFUNCTION(BlueprintCallable, Category = "Ingredients")
	virtual float GetBulkTime();

#pragma endregion Ingredients

// UI
#pragma region
public:

	/** Name to show in the Crafting Menu */
	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual FString GetDisplayName();

#pragma endregion UI
};
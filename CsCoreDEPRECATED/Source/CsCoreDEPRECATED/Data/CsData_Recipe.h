// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Data/CsData_Impl.h"
#include "Types/CsTypes_Recipe.h"
#include "CsData_Recipe.generated.h"

UCLASS(Abstract)
class CSCOREDEPRECATED_API UCsData_Recipe : public UCsData_Impl
{
	GENERATED_UCLASS_BODY()

	virtual const FECsRecipeType& GetRecipeType();

// Stats
#pragma region
public:

	/** ShortCode for the Item created from the Recipe */
	UFUNCTION(BlueprintCallable, Category = "Stats")
	virtual const FName& GetCreatedItem();

#pragma endregion Stats

// Ingredients
#pragma region
public:

	/** List of all Ingredients (Item, Count, ... etc) used in the Recipe */
	virtual TArray<FCsRecipeIngredient>* GetIngredients();

	/** Time to process single Recipe */
	UFUNCTION(BlueprintCallable, Category = "Ingredients")
	virtual const float& GetTime();
	/** Whether to use BulkTime */
	UFUNCTION(BlueprintCallable, Category = "Ingredients")
	virtual const bool& GetUseBulkTime();
	/** Time to process many Recipes at once (i.e. Bulk)*/
	UFUNCTION(BlueprintCallable, Category = "Ingredients")
	virtual const float& GetBulkTime();

#pragma endregion Ingredients

// UI
#pragma region
public:

	/** Name to show in the Crafting Menu */
	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual const FString& GetDisplayName();

#pragma endregion UI
};
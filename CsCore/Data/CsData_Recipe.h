// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Data/CsData.h"
#include "Types/CsTypes_Recipe.h"
#include "CsData_Recipe.generated.h"

UCLASS(hidecategories = (Object, Actor, Replication, Rendering, Input, "Actor Tick"))
class CSCORE_API ACsData_Recipe : public ACsData
{
	GENERATED_UCLASS_BODY()

	TCsRecipeType BaseRecipeType;

	TCsRecipeType GetBaseRecipeType();

// Ingredients
#pragma region
public:

	virtual TArray<FCsRecipeIngredient>* GetIngredients();

	UFUNCTION(BlueprintCallable, Category = "Ingredients")
	virtual float GetTime();

#pragma endregion Ingredients

// UI
#pragma region
public:

	/** Name to show in the Crafting Menu */
	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual FString GetDisplayName();

#pragma endregion UI
};
// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_Recipe.h"
#include "CsCore.h"

ACsData_Recipe::ACsData_Recipe(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

TCsRecipeType ACsData_Recipe::GetBaseRecipeType() { return BaseRecipeType; }

// Ingredients
#pragma region

TArray<FCsRecipeIngredient>* ACsData_Recipe::GetIngredients() { return nullptr; }
float ACsData_Recipe::GetTime() { return 0.0f; }

#pragma endregion Ingredients

// UI
#pragma region

FString ACsData_Recipe::GetDisplayName() { return ECsCachedString::Str::INVALID; }

#pragma endregion UI
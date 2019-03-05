// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_Recipe.h"
#include "CsCore.h"

ACsData_Recipe::ACsData_Recipe(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

const FECsRecipeType& ACsData_Recipe::GetRecipeType() { return EMCsRecipeType::Get().GetMAX(); }

// Stats
#pragma region

const FName& ACsData_Recipe::GetCreatedItem() { return ECsCached::Name::None; }

#pragma endregion Stats

// Ingredients
#pragma region

TArray<FCsRecipeIngredient>* ACsData_Recipe::GetIngredients() { return nullptr; }
const float& ACsData_Recipe::GetTime() { return ECsCached::Ref::Float; }
const bool& ACsData_Recipe::GetUseBulkTime() { return ECsCached::Ref::False; }
const float& ACsData_Recipe::GetBulkTime() { return ECsCached::Ref::Float; }

#pragma endregion Ingredients

// UI
#pragma region

const FString& ACsData_Recipe::GetDisplayName() { return ECsCached::Str::INVALID; }

#pragma endregion UI
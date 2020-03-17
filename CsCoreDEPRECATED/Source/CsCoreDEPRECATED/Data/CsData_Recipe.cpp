// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_Recipe.h"
#include "CsCore.h"

UCsData_Recipe::UCsData_Recipe(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

const FECsRecipeType& UCsData_Recipe::GetRecipeType() { return EMCsRecipeType::Get().GetMAX(); }

// Stats
#pragma region

const FName& UCsData_Recipe::GetCreatedItem() { return NCsCached::Name::None; }

#pragma endregion Stats

// Ingredients
#pragma region

TArray<FCsRecipeIngredient>* UCsData_Recipe::GetIngredients() { return nullptr; }
const float& UCsData_Recipe::GetTime() { return NCsCached::Ref::Float; }
const bool& UCsData_Recipe::GetUseBulkTime() { return NCsCached::Ref::False; }
const float& UCsData_Recipe::GetBulkTime() { return NCsCached::Ref::Float; }

#pragma endregion Ingredients

// UI
#pragma region

const FString& UCsData_Recipe::GetDisplayName() { return NCsCached::Str::INVALID; }

#pragma endregion UI
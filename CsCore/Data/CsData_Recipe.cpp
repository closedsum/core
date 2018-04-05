// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_Recipe.h"
#include "CsCore.h"

ACsData_Recipe::ACsData_Recipe(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

TCsRecipeType ACsData_Recipe::GetBaseRecipeType() { return BaseRecipeType; }

// Stats
#pragma region

const FName& ACsData_Recipe::GetCreatedItem() { return ECsCachedName::Name::None; }

#pragma endregion Stats

// Ingredients
#pragma region

TArray<FCsRecipeIngredient>* ACsData_Recipe::GetIngredients() { return nullptr; }
const float& ACsData_Recipe::GetTime() { return ECsCachedReferences::Ref::Float; }
const bool& ACsData_Recipe::GetUseBulkTime() { return ECsCachedReferences::Ref::False; }
const float& ACsData_Recipe::GetBulkTime() { return ECsCachedReferences::Ref::Float; }

#pragma endregion Ingredients

// UI
#pragma region

const FString& ACsData_Recipe::GetDisplayName() { return ECsCachedString::Str::INVALID; }

#pragma endregion UI
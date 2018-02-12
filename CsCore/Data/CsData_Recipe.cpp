// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_Recipe.h"
#include "CsCore.h"

ACsData_Recipe::ACsData_Recipe(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

TCsRecipe ACsData_Recipe::GetBaseRecipe() { return BaseRecipe; }

// UI
#pragma region

FString ACsData_Recipe::GetDisplayName() { return ECsCachedString::Str::INVALID; }

#pragma endregion UI
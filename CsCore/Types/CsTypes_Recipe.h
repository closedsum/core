// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Primitive.h"

//#include "CsTypes_Item.generated.h"
#pragma once

// Recipe
#pragma region

namespace ECsRecipe
{
	enum Type : uint8;
}

typedef ECsRecipe::Type TCsRecipe;

// RecipeToString
typedef FString(*TCsRecipeToString)(const TCsRecipe&);
// StringToRecipe
typedef TCsRecipe(*TCsStringToRecipe)(const FString&);

#define CS_DECLARE_RECIPE	TCsRecipe Recipe_MAX;\
							uint8 RECIPE_MAX; \
							TCsRecipeToString RecipeToString; \
							TCsStringToRecipe StringToRecipe;

#define CS_DEFINE_RECIPE	Recipe_MAX = ECsRecipe::ECsRecipe_MAX; \
							RECIPE_MAX = (uint8)Recipe_MAX; \
							RecipeToString = &ECsRecipe::ToString; \
							StringToRecipe = &ECsRecipe::ToType;

#pragma endregion Recipe
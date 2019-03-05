// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Recipe.h"

// RecipeType
EMCsRecipeType* EMCsRecipeType::Instance;

EMCsRecipeType& EMCsRecipeType::Get()
{
	if (!Instance)
		Instance = new EMCsRecipeType();
	return *Instance;
}
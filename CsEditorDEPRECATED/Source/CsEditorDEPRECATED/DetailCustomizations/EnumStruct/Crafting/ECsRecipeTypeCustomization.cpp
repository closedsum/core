// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/Crafting/ECsRecipeTypeCustomization.h"

#include "Types/CsTypes_Recipe.h"

#define LOCTEXT_NAMESPACE "ECsRecipeTypeCustomization"


FECsRecipeTypeCustomization::FECsRecipeTypeCustomization()
{
	Init<EMCsRecipeType, FECsRecipeType>();
}

TSharedRef<IPropertyTypeCustomization> FECsRecipeTypeCustomization::MakeInstance()
{
	return MakeShareable(new FECsRecipeTypeCustomization);
}

void FECsRecipeTypeCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsRecipeType>(StructPropertyHandle);
}

void FECsRecipeTypeCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EMCsRecipeType, FECsRecipeType>(DisplayName);
}

#undef LOCTEXT_NAMESPACE

// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/Item/ECsItemInteractionCustomization.h"

#include "Types/CsTypes_Item.h"

#define LOCTEXT_NAMESPACE "ECsItemInteractionCustomization"


FECsItemInteractionCustomization::FECsItemInteractionCustomization()
{
	Init<EMCsItemInteraction, FECsItemInteraction>();
}

TSharedRef<IPropertyTypeCustomization> FECsItemInteractionCustomization::MakeInstance()
{
	return MakeShareable(new FECsItemInteractionCustomization);
}

void FECsItemInteractionCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsItemInteraction>(StructPropertyHandle);
}

void FECsItemInteractionCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EMCsItemInteraction, FECsItemInteraction>(DisplayName);
}

#undef LOCTEXT_NAMESPACE

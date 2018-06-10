// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/Item/ECsItemInteractionCustomization.h"

#include "Types/CsTypes_Item.h"

#define LOCTEXT_NAMESPACE "ECsItemInteractionCustomization"


FECsItemInteractionCustomization::FECsItemInteractionCustomization()
{
	Init<FECsItemInteraction, EMCsItemInteraction>();
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
	SetEnumWithDisplayName_Internal<FECsItemInteraction, EMCsItemInteraction>(DisplayName);
}

#undef LOCTEXT_NAMESPACE

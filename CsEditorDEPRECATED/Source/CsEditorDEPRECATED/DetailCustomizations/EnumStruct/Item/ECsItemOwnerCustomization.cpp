// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/Item/ECsItemOwnerCustomization.h"

#include "Types/CsTypes_Item.h"

#define LOCTEXT_NAMESPACE "ECsItemOwnerCustomization"


FECsItemOwnerCustomization::FECsItemOwnerCustomization()
{
	Init<EMCsItemOwner, FECsItemOwner>();
}

TSharedRef<IPropertyTypeCustomization> FECsItemOwnerCustomization::MakeInstance()
{
	return MakeShareable(new FECsItemOwnerCustomization);
}

void FECsItemOwnerCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsItemOwner>(StructPropertyHandle);
}

void FECsItemOwnerCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EMCsItemOwner, FECsItemOwner>(DisplayName);
}

#undef LOCTEXT_NAMESPACE

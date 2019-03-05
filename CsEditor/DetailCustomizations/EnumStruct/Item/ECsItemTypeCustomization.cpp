// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/Item/ECsItemTypeCustomization.h"

#include "Types/CsTypes_Item.h"

#define LOCTEXT_NAMESPACE "ECsItemTypeCustomization"


FECsItemTypeCustomization::FECsItemTypeCustomization()
{
	Init<FECsItemType, EMCsItemType>();
}

TSharedRef<IPropertyTypeCustomization> FECsItemTypeCustomization::MakeInstance()
{
	return MakeShareable(new FECsItemTypeCustomization);
}

void FECsItemTypeCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsItemType>(StructPropertyHandle);
}

void FECsItemTypeCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<FECsItemType, EMCsItemType>(DisplayName);
}

#undef LOCTEXT_NAMESPACE

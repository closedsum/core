// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsAssetTypeCustomization.h"

#include "Types/CsTypes_Load.h"

#define LOCTEXT_NAMESPACE "ECsAssetTypeCustomization"


FECsAssetTypeCustomization::FECsAssetTypeCustomization() :
	Super()
{
	Init<EMCsAssetType, FECsAssetType>();
}

TSharedRef<IPropertyTypeCustomization> FECsAssetTypeCustomization::MakeInstance()
{
	return MakeShareable(new FECsAssetTypeCustomization);
}

void FECsAssetTypeCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsAssetType>(StructPropertyHandle);
}

void FECsAssetTypeCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EMCsAssetType, FECsAssetType>(DisplayName);
}

void FECsAssetTypeCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EMCsAssetType, FECsAssetType>(OutDisplayName);
}

#undef LOCTEXT_NAMESPACE

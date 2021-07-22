// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsAssetTypeCustomization.h"

#include "Types/CsTypes_Load.h"

#define LOCTEXT_NAMESPACE "ECsAssetTypeCustomization"

#define EnumMapType EMCsAssetType
#define EnumType FECsAssetType

FECsAssetTypeCustomization::FECsAssetTypeCustomization() :
	Super()
{
	Init<EnumMapType, EnumType>();
}

TSharedRef<IPropertyTypeCustomization> FECsAssetTypeCustomization::MakeInstance()
{
	return MakeShareable(new FECsAssetTypeCustomization);
}

void FECsAssetTypeCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<EnumType>(StructPropertyHandle);
}

void FECsAssetTypeCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EnumMapType, EnumType>(DisplayName);
}

void FECsAssetTypeCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EnumMapType, EnumType>(OutDisplayName);
}

#undef EnumMapType
#undef EnumType

#undef LOCTEXT_NAMESPACE

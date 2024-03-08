// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsLoadAssetsTypeCustomization.h"
#include "IDetailChildrenBuilder.h"
#include "DetailWidgetRow.h"
#include "IDetailGroup.h"
#include "DetailLayoutBuilder.h"

#include "Types/CsTypes_Load.h"

#define LOCTEXT_NAMESPACE "ECsLoadAssetsTypeCustomization"

#define EnumMapType EMCsLoadAssetsType
#define EnumType FECsLoadAssetsType

FECsLoadAssetsTypeCustomization::FECsLoadAssetsTypeCustomization() : 
	Super()
{
	Init<EnumMapType, EnumType>();

	bPerformDropDownCheck = false;
}

TSharedRef<IPropertyTypeCustomization> FECsLoadAssetsTypeCustomization::MakeInstance()
{
	return MakeShareable(new FECsLoadAssetsTypeCustomization);
}

void FECsLoadAssetsTypeCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<EnumType>(StructPropertyHandle);
}

void FECsLoadAssetsTypeCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EnumMapType, EnumType>(DisplayName);
}

void FECsLoadAssetsTypeCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EnumMapType, EnumType>(OutDisplayName);
}

#undef EnumMapType
#undef EnumType

#undef LOCTEXT_NAMESPACE

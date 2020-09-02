// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsLoadAssetsTypeCustomization.h"
#include "IDetailChildrenBuilder.h"
#include "DetailWidgetRow.h"
#include "IDetailGroup.h"
#include "DetailLayoutBuilder.h"

#include "Types/CsTypes_Load.h"

#define LOCTEXT_NAMESPACE "ECsLoadAssetsTypeCustomization"


FECsLoadAssetsTypeCustomization::FECsLoadAssetsTypeCustomization() : 
	Super()
{
	Init<EMCsLoadAssetsType, FECsLoadAssetsType>();

	bPerformDropDownCheck = false;
}

TSharedRef<IPropertyTypeCustomization> FECsLoadAssetsTypeCustomization::MakeInstance()
{
	return MakeShareable(new FECsLoadAssetsTypeCustomization);
}

void FECsLoadAssetsTypeCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsLoadAssetsType>(StructPropertyHandle);
}

void FECsLoadAssetsTypeCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EMCsLoadAssetsType, FECsLoadAssetsType>(DisplayName);
}

void FECsLoadAssetsTypeCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EMCsLoadAssetsType, FECsLoadAssetsType>(OutDisplayName);
}

#undef LOCTEXT_NAMESPACE

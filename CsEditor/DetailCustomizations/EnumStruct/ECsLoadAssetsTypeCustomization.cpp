// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsLoadAssetsTypeCustomization.h"
#include "IDetailChildrenBuilder.h"
#include "DetailWidgetRow.h"
#include "IDetailGroup.h"
#include "DetailLayoutBuilder.h"

#include "Types/CsTypes_Load.h"

#define LOCTEXT_NAMESPACE "ECsLoadAssetsTypeCustomization"


FECsLoadAssetsTypeCustomization::FECsLoadAssetsTypeCustomization()
{
	Init<FECsLoadAssetsType, EMCsLoadAssetsType>();

	PerformDropDownCheck = false;
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
	SetEnumWithDisplayName_Internal<FECsLoadAssetsType, EMCsLoadAssetsType>(DisplayName);
}

#undef LOCTEXT_NAMESPACE

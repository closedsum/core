// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/Menu/ECsMenuCustomization.h"

// Managers
#include "Managers/Menu/CsTypes_Menu.h"

#define LOCTEXT_NAMESPACE "ECsMenuCustomization"

FECsMenuCustomization::FECsMenuCustomization() :
	Super()
{
	Init<EMCsMenu, FECsMenu>();
}

TSharedRef<IPropertyTypeCustomization> FECsMenuCustomization::MakeInstance()
{
	return MakeShareable(new FECsMenuCustomization);
}

void FECsMenuCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsMenu>(StructPropertyHandle);
}

void FECsMenuCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EMCsMenu, FECsMenu>(DisplayName);
}

void FECsMenuCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EMCsMenu, FECsMenu>(OutDisplayName);
}

#undef LOCTEXT_NAMESPACE

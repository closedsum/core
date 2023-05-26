// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/Menu/ECsMenuCustomization.h"

// Managers
#include "Managers/Menu/CsTypes_Menu.h"

#define LOCTEXT_NAMESPACE "ECsMenuCustomization"

#define CLASS_TYPE FECsMenuCustomization
#define EnumMapType EMCsMenu
#define EnumType FECsMenu

CLASS_TYPE::CLASS_TYPE() :
	Super()
{
	Init<EnumMapType, EnumType>();
}

TSharedRef<IPropertyTypeCustomization> CLASS_TYPE::MakeInstance()
{
	return MakeShareable(new CLASS_TYPE);
}

void CLASS_TYPE::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<EnumType>(StructPropertyHandle);
}

void CLASS_TYPE::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EnumMapType, EnumType>(DisplayName);
}

void CLASS_TYPE::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EnumMapType, EnumType>(OutDisplayName);
}

#undef CLASS_TYPE
#undef EnumMapType
#undef EnumType

#undef LOCTEXT_NAMESPACE

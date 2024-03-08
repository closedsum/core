// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/CVar/ECsCVarToggleCustomization.h"

#include "CsCVars.h"

#define LOCTEXT_NAMESPACE "ECsCVarToggleCustomization"

#define EnumMapType EMCsCVarToggle
#define EnumType FECsCVarToggle

FECsCVarToggleCustomization::FECsCVarToggleCustomization() :
	Super()
{
	Init<EnumMapType, EnumType>();
}

TSharedRef<IPropertyTypeCustomization> FECsCVarToggleCustomization::MakeInstance()
{
	return MakeShareable(new FECsCVarToggleCustomization);
}

void FECsCVarToggleCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<EnumType>(StructPropertyHandle);
}

void FECsCVarToggleCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EnumMapType, EnumType>(DisplayName);
}

void FECsCVarToggleCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EnumMapType, EnumType>(OutDisplayName);
}

#undef EnumMapType
#undef EnumType

#undef LOCTEXT_NAMESPACE

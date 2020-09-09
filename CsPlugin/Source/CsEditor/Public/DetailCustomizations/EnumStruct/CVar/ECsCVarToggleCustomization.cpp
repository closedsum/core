// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/CVar/ECsCVarToggleCustomization.h"

#include "CsCVars.h"

#define LOCTEXT_NAMESPACE "ECsCVarToggleCustomization"


FECsCVarToggleCustomization::FECsCVarToggleCustomization() :
	Super()
{
	Init<EMCsCVarToggle, FECsCVarToggle>();
}

TSharedRef<IPropertyTypeCustomization> FECsCVarToggleCustomization::MakeInstance()
{
	return MakeShareable(new FECsCVarToggleCustomization);
}

void FECsCVarToggleCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsCVarToggle>(StructPropertyHandle);
}

void FECsCVarToggleCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EMCsCVarToggle, FECsCVarToggle>(DisplayName);
}

void FECsCVarToggleCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EMCsCVarToggle, FECsCVarToggle>(OutDisplayName);
}

#undef LOCTEXT_NAMESPACE

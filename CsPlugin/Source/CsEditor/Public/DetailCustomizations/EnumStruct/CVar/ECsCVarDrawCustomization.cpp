// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/CVar/ECsCVarDrawCustomization.h"

#include "CsCVars.h"

#define LOCTEXT_NAMESPACE "ECsCVarDrawCustomization"


FECsCVarDrawCustomization::FECsCVarDrawCustomization() :
	Super()
{
	Init<EMCsCVarDraw, FECsCVarDraw>();
}

TSharedRef<IPropertyTypeCustomization> FECsCVarDrawCustomization::MakeInstance()
{
	return MakeShareable(new FECsCVarDrawCustomization);
}

void FECsCVarDrawCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsCVarDraw>(StructPropertyHandle);
}

void FECsCVarDrawCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EMCsCVarDraw, FECsCVarDraw>(DisplayName);
}

void FECsCVarDrawCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EMCsCVarDraw, FECsCVarDraw>(OutDisplayName);
}

#undef LOCTEXT_NAMESPACE

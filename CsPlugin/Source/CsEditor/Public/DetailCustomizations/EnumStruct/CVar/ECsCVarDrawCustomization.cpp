// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/CVar/ECsCVarDrawCustomization.h"

#include "CsCVars.h"

#define LOCTEXT_NAMESPACE "ECsCVarDrawCustomization"

#define EnumMapType EMCsCVarDraw
#define EnumType FECsCVarDraw

FECsCVarDrawCustomization::FECsCVarDrawCustomization() :
	Super()
{
	Init<EnumMapType, EnumType>();
}

TSharedRef<IPropertyTypeCustomization> FECsCVarDrawCustomization::MakeInstance()
{
	return MakeShareable(new FECsCVarDrawCustomization);
}

void FECsCVarDrawCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<EnumType>(StructPropertyHandle);
}

void FECsCVarDrawCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EnumMapType, EnumType>(DisplayName);
}

void FECsCVarDrawCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EnumMapType, EnumType>(OutDisplayName);
}

#undef EnumMapType
#undef EnumType

#undef LOCTEXT_NAMESPACE

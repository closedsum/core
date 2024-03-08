// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/CVar/ECsCVarLogCustomization.h"

#include "CsCVars.h"

#define LOCTEXT_NAMESPACE "ECsCVarLogCustomization"

#define EnumMapType EMCsCVarLog
#define EnumType FECsCVarLog

FECsCVarLogCustomization::FECsCVarLogCustomization() :
	Super()
{
	Init<EnumMapType, EnumType>();
}

TSharedRef<IPropertyTypeCustomization> FECsCVarLogCustomization::MakeInstance()
{
	return MakeShareable(new FECsCVarLogCustomization);
}

void FECsCVarLogCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<EnumType>(StructPropertyHandle);
}

void FECsCVarLogCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EnumMapType, EnumType>(DisplayName);
}

void FECsCVarLogCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EnumMapType, EnumType>(OutDisplayName);
}

#undef EnumMapType
#undef EnumType

#undef LOCTEXT_NAMESPACE

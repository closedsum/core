// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/CVar/ECsCVarLogCustomization.h"

#include "CsCVars.h"

#define LOCTEXT_NAMESPACE "ECsCVarLogCustomization"


FECsCVarLogCustomization::FECsCVarLogCustomization() :
	Super()
{
	Init<EMCsCVarLog, FECsCVarLog>();
}

TSharedRef<IPropertyTypeCustomization> FECsCVarLogCustomization::MakeInstance()
{
	return MakeShareable(new FECsCVarLogCustomization);
}

void FECsCVarLogCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsCVarLog>(StructPropertyHandle);
}

void FECsCVarLogCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EMCsCVarLog, FECsCVarLog>(DisplayName);
}

void FECsCVarLogCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EMCsCVarLog, FECsCVarLog>(OutDisplayName);
}

#undef LOCTEXT_NAMESPACE

// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "DetailCustomizations/EnumStruct/ECsDamageTypeCustomization.h"

#include "Types/CsTypes_Damage.h"

#define LOCTEXT_NAMESPACE "ECsDamageTypeCustomization"

#define EnumMapType EMCsDamageType
#define EnumType FECsDamageType

FECsDamageTypeCustomization::FECsDamageTypeCustomization() :
	Super()
{
	Init<EnumMapType, EnumType>();
}

TSharedRef<IPropertyTypeCustomization> FECsDamageTypeCustomization::MakeInstance()
{
	return MakeShareable(new FECsDamageTypeCustomization);
}

void FECsDamageTypeCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<EnumType>(StructPropertyHandle);
}

void FECsDamageTypeCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EnumMapType, EnumType>(DisplayName);
}

void FECsDamageTypeCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EnumMapType, EnumType>(OutDisplayName);
}

#undef EnumMapType
#undef EnumType

#undef LOCTEXT_NAMESPACE

// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "DetailCustomizations/EnumStruct/ECsDamageModifierCustomization.h"

// Managers
#include "Modifier/Types/CsTypes_DamageModifier.h"

#define LOCTEXT_NAMESPACE "ECsDamageModifierCustomization"

#define EnumMapType EMCsDamageModifier
#define EnumType FECsDamageModifier

FECsDamageModifierCustomization::FECsDamageModifierCustomization() :
	Super()
{
	Init<EnumMapType, EnumType>();
}

TSharedRef<IPropertyTypeCustomization> FECsDamageModifierCustomization::MakeInstance()
{
	return MakeShareable(new FECsDamageModifierCustomization);
}

void FECsDamageModifierCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<EnumType>(StructPropertyHandle);
}

void FECsDamageModifierCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EnumMapType, EnumType>(DisplayName);
}

void FECsDamageModifierCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EnumMapType, EnumType>(OutDisplayName);
}

#undef EnumMapType
#undef EnumType

#undef LOCTEXT_NAMESPACE
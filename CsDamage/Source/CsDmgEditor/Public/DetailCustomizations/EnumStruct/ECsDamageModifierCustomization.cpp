// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
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
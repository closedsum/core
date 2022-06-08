// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsWeaponModifierCustomization.h"

#include "Modifier/Types/CsTypes_WeaponModifier.h"

#define LOCTEXT_NAMESPACE "ECsWeaponModifierCustomization"

#define EnumMapType EMCsWeaponModifier
#define EnumType FECsWeaponModifier

FECsWeaponModifierCustomization::FECsWeaponModifierCustomization()
{
	Init<EnumMapType, EnumType>();
}

TSharedRef<IPropertyTypeCustomization> FECsWeaponModifierCustomization::MakeInstance()
{
	return MakeShareable(new FECsWeaponModifierCustomization);
}

void FECsWeaponModifierCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<EnumType>(StructPropertyHandle);
}

void FECsWeaponModifierCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EnumMapType, EnumType>(DisplayName);
}

void FECsWeaponModifierCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EnumMapType, EnumType>(OutDisplayName);
}

#undef EnumMapType
#undef EnumType

#undef LOCTEXT_NAMESPACE
// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsProjectileModifierCustomization.h"

// Managers
#include "Modifier/Types/CsTypes_ProjectileModifier.h"

#define LOCTEXT_NAMESPACE "ECsProjectileModifierCustomization"

#define EnumMapType EMCsProjectileModifier
#define EnumType FECsProjectileModifier

FECsProjectileModifierCustomization::FECsProjectileModifierCustomization() :
	Super()
{
	Init<EnumMapType, EnumType>();
}

TSharedRef<IPropertyTypeCustomization> FECsProjectileModifierCustomization::MakeInstance()
{
	return MakeShareable(new FECsProjectileModifierCustomization);
}

void FECsProjectileModifierCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<EnumType>(StructPropertyHandle);
}

void FECsProjectileModifierCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EnumMapType, EnumType>(DisplayName);
}

void FECsProjectileModifierCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EnumMapType, EnumType>(OutDisplayName);
}

#undef EnumMapType
#undef EnumType

#undef LOCTEXT_NAMESPACE
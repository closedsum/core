// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsProjectileDataCustomization.h"

// Managers
#include "Types/CsTypes_Projectile.h"

#define LOCTEXT_NAMESPACE "ECsProjectileDataCustomization"

#define EnumMapType EMCsProjectileData
#define EnumType FECsProjectileData

FECsProjectileDataCustomization::FECsProjectileDataCustomization() :
	Super()
{
	Init<EnumMapType, EnumType>();
}

TSharedRef<IPropertyTypeCustomization> FECsProjectileDataCustomization::MakeInstance()
{
	return MakeShareable(new FECsProjectileDataCustomization);
}

void FECsProjectileDataCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<EnumType>(StructPropertyHandle);
}

void FECsProjectileDataCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EnumMapType, EnumType>(DisplayName);
}

void FECsProjectileDataCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EnumMapType, EnumType>(OutDisplayName);
}

#undef EnumMapType
#undef EnumType

#undef LOCTEXT_NAMESPACE
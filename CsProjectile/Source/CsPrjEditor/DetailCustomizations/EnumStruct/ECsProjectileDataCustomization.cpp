// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsProjectileDataCustomization.h"

// Managers
#include "Managers/Projectile/CsTypes_Projectile.h"

#define LOCTEXT_NAMESPACE "ECsProjectileDataCustomization"

FECsProjectileDataCustomization::FECsProjectileDataCustomization() :
	Super()
{
	Init<EMCsProjectileData, FECsProjectileData>();
}

TSharedRef<IPropertyTypeCustomization> FECsProjectileDataCustomization::MakeInstance()
{
	return MakeShareable(new FECsProjectileDataCustomization);
}

void FECsProjectileDataCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsProjectileData>(StructPropertyHandle);
}

void FECsProjectileDataCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EMCsProjectileData, FECsProjectileData>(DisplayName);
}

void FECsProjectileDataCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EMCsProjectileData, FECsProjectileData>(OutDisplayName);
}

#undef LOCTEXT_NAMESPACE
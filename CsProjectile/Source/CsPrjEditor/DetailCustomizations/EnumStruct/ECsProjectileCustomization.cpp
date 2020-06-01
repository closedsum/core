// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsProjectileCustomization.h"

// Managers
#include "Managers/Projectile/CsTypes_Projectile.h"
// Settings
#include "Settings/CsProjectileSettings.h"

#define LOCTEXT_NAMESPACE "ECsProjectileCustomization"


FECsProjectileCustomization::FECsProjectileCustomization() :
	Super()
{
	Init<EMCsProjectile, FECsProjectile>();
}

void FECsProjectileCustomization::PopulateEnumMapFromSettings()
{
	PopulateEnumMapFromSettings_Internal<UCsProjectileSettings, EMCsProjectile, FECsProjectile>(TEXT("FECsProjectileCustomization::PopulateEnumMapFromSettings"));
}

TSharedRef<IPropertyTypeCustomization> FECsProjectileCustomization::MakeInstance()
{
	return MakeShareable(new FECsProjectileCustomization);
}

void FECsProjectileCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsProjectile>(StructPropertyHandle);
}

void FECsProjectileCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EMCsProjectile, FECsProjectile>(DisplayName);
}

#undef LOCTEXT_NAMESPACE

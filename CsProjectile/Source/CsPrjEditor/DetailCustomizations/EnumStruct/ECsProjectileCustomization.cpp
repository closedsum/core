// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsProjectileCustomization.h"

#include "Managers/Projectile/CsTypes_Projectile.h"

#define LOCTEXT_NAMESPACE "ECsProjectileCustomization"


FECsProjectileCustomization::FECsProjectileCustomization()
{
	Init<FECsProjectile, EMCsProjectile>();
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
	SetEnumWithDisplayName_Internal<FECsProjectile, EMCsProjectile>(DisplayName);
}

#undef LOCTEXT_NAMESPACE

// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/Projectile/ECsProjectileTypeCustomization.h"

#include "Managers/Projectile/CsTypes_Projectile.h"

#define LOCTEXT_NAMESPACE "ECsAssetTypeCustomization"


FECsProjectileTypeCustomization::FECsProjectileTypeCustomization()
{
	Init<FECsProjectileType, EMCsProjectileType>();
}

TSharedRef<IPropertyTypeCustomization> FECsProjectileTypeCustomization::MakeInstance()
{
	return MakeShareable(new FECsProjectileTypeCustomization);
}

void FECsProjectileTypeCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsProjectileType>(StructPropertyHandle);
}

void FECsProjectileTypeCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<FECsProjectileType, EMCsProjectileType>(DisplayName);
}

#undef LOCTEXT_NAMESPACE

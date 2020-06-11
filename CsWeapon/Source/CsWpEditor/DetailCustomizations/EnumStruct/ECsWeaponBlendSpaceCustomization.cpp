// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsWeaponBlendSpaceCustomization.h"

#include "CsTypes_Weapon.h"

#define LOCTEXT_NAMESPACE "ECsWeaponBlendSpaceCustomization"


FECsWeaponBlendSpaceCustomization::FECsWeaponBlendSpaceCustomization()
{
	Init<EMCsWeaponBlendSpace, FECsWeaponBlendSpace>();
}

TSharedRef<IPropertyTypeCustomization> FECsWeaponBlendSpaceCustomization::MakeInstance()
{
	return MakeShareable(new FECsWeaponBlendSpaceCustomization);
}

void FECsWeaponBlendSpaceCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsWeaponBlendSpace>(StructPropertyHandle);
}

void FECsWeaponBlendSpaceCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EMCsWeaponBlendSpace, FECsWeaponBlendSpace>(DisplayName);
}

#undef LOCTEXT_NAMESPACE
// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/Weapon/ECsWeaponBlendSpaceCustomization.h"

#include "Types/CsTypes_Weapon.h"

#define LOCTEXT_NAMESPACE "ECsWeaponBlendSpaceCustomization"


FECsWeaponBlendSpaceCustomization::FECsWeaponBlendSpaceCustomization()
{
	Init<FECsWeaponBlendSpace, EMCsWeaponBlendSpace>();
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
	SetEnumWithDisplayName_Internal<FECsWeaponBlendSpace, EMCsWeaponBlendSpace>(DisplayName);
}

#undef LOCTEXT_NAMESPACE

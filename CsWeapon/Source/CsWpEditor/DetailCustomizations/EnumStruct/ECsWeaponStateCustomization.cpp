// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsWeaponStateCustomization.h"

#include "CsTypes_Weapon.h"

#define LOCTEXT_NAMESPACE "ECsWeaponStateCustomization"


FECsWeaponStateCustomization::FECsWeaponStateCustomization()
{
	Init<EMCsWeaponState, FECsWeaponState>();
}

TSharedRef<IPropertyTypeCustomization> FECsWeaponStateCustomization::MakeInstance()
{
	return MakeShareable(new FECsWeaponStateCustomization);
}

void FECsWeaponStateCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsWeaponState>(StructPropertyHandle);
}

void FECsWeaponStateCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EMCsWeaponState, FECsWeaponState>(DisplayName);
}

void FECsWeaponStateCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EMCsWeaponState, FECsWeaponState>(OutDisplayName);
}

#undef LOCTEXT_NAMESPACE
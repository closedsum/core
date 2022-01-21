// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsWeaponDataCustomization.h"

#include "Types/CsTypes_Weapon.h"

#define LOCTEXT_NAMESPACE "ECsWeaponDataCustomization"


FECsWeaponDataCustomization::FECsWeaponDataCustomization()
{
	Init<EMCsWeaponData, FECsWeaponData>();
}

TSharedRef<IPropertyTypeCustomization> FECsWeaponDataCustomization::MakeInstance()
{
	return MakeShareable(new FECsWeaponDataCustomization);
}

void FECsWeaponDataCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsWeaponData>(StructPropertyHandle);
}

void FECsWeaponDataCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EMCsWeaponData, FECsWeaponData>(DisplayName);
}

void FECsWeaponDataCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EMCsWeaponData, FECsWeaponData>(OutDisplayName);
}

#undef LOCTEXT_NAMESPACE
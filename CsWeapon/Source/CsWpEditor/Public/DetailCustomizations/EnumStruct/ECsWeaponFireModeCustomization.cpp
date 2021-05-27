// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsWeaponFireModeCustomization.h"

#include "Types/CsTypes_Weapon.h"

#define LOCTEXT_NAMESPACE "ECsWeaponFireModeCustomization"


FECsWeaponFireModeCustomization::FECsWeaponFireModeCustomization()
{
	Init<EMCsWeaponFireMode, FECsWeaponFireMode>();
}

TSharedRef<IPropertyTypeCustomization> FECsWeaponFireModeCustomization::MakeInstance()
{
	return MakeShareable(new FECsWeaponFireModeCustomization);
}

void FECsWeaponFireModeCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsWeaponFireMode>(StructPropertyHandle);
}

void FECsWeaponFireModeCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EMCsWeaponFireMode, FECsWeaponFireMode>(DisplayName);
}

void FECsWeaponFireModeCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EMCsWeaponFireMode, FECsWeaponFireMode>(OutDisplayName);
}

#undef LOCTEXT_NAMESPACE
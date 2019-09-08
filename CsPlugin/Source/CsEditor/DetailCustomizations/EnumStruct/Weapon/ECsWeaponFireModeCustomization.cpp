// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/Weapon/ECsWeaponFireModeCustomization.h"

#include "Types/CsTypes_Weapon.h"

#define LOCTEXT_NAMESPACE "ECsWeaponFireModeCustomization"


FECsWeaponFireModeCustomization::FECsWeaponFireModeCustomization()
{
	Init<FECsWeaponFireMode, EMCsWeaponFireMode>();
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
	SetEnumWithDisplayName_Internal<FECsWeaponFireMode, EMCsWeaponFireMode>(DisplayName);
}

#undef LOCTEXT_NAMESPACE

// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsWeaponSoundCustomization.h"

#include "CsTypes_Weapon.h"

#define LOCTEXT_NAMESPACE "ECsWeaponSoundCustomization"


FECsWeaponSoundCustomization::FECsWeaponSoundCustomization()
{
	Init<EMCsWeaponSound, FECsWeaponSound>();
}

TSharedRef<IPropertyTypeCustomization> FECsWeaponSoundCustomization::MakeInstance()
{
	return MakeShareable(new FECsWeaponSoundCustomization);
}

void FECsWeaponSoundCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsWeaponSound>(StructPropertyHandle);
}

void FECsWeaponSoundCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EMCsWeaponSound, FECsWeaponSound>(DisplayName);
}

#undef LOCTEXT_NAMESPACE
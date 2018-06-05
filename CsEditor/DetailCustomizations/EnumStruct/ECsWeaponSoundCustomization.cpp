// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsWeaponSoundCustomization.h"

#include "Types/CsTypes_Weapon.h"

#define LOCTEXT_NAMESPACE "ECsWeaponSoundCustomization"


FECsWeaponSoundCustomization::FECsWeaponSoundCustomization()
{
	Init<FECsWeaponSound, EMCsWeaponSound>();
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
	SetEnumWithDisplayName_Internal<FECsWeaponSound, EMCsWeaponSound>(DisplayName);
}

#undef LOCTEXT_NAMESPACE

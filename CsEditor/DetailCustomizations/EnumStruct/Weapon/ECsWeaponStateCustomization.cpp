// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/Weapon/ECsWeaponStateCustomization.h"

#include "Types/CsTypes_Weapon.h"

#define LOCTEXT_NAMESPACE "ECsWeaponStateCustomization"


FECsWeaponStateCustomization::FECsWeaponStateCustomization()
{
	Init<FECsWeaponState, EMCsWeaponState>();
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
	SetEnumWithDisplayName_Internal<FECsWeaponState, EMCsWeaponState>(DisplayName);
}

#undef LOCTEXT_NAMESPACE

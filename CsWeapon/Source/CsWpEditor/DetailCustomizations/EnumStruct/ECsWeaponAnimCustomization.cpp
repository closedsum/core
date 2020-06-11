// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsWeaponAnimCustomization.h"

#include "CsTypes_Weapon.h"

#define LOCTEXT_NAMESPACE "ECsWeaponAnimCustomization"


FECsWeaponAnimCustomization::FECsWeaponAnimCustomization()
{
	Init<EMCsWeaponAnim, FECsWeaponAnim>();
}

TSharedRef<IPropertyTypeCustomization> FECsWeaponAnimCustomization::MakeInstance()
{
	return MakeShareable(new FECsWeaponAnimCustomization);
}

void FECsWeaponAnimCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsWeaponAnim>(StructPropertyHandle);
}

void FECsWeaponAnimCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EMCsWeaponAnim, FECsWeaponAnim>(DisplayName);
}

#undef LOCTEXT_NAMESPACE
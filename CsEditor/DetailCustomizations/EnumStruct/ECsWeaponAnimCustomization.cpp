// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsWeaponAnimCustomization.h"

#include "Types/CsTypes_Weapon.h"

#define LOCTEXT_NAMESPACE "ECsWeaponAnimCustomization"


FECsWeaponAnimCustomization::FECsWeaponAnimCustomization()
{
	Init<FECsWeaponAnim, EMCsWeaponAnim>();
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
	SetEnumWithDisplayName_Internal<FECsWeaponAnim, EMCsWeaponAnim>(DisplayName);
}

#undef LOCTEXT_NAMESPACE

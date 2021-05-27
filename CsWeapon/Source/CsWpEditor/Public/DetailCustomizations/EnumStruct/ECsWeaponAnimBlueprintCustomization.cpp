// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsWeaponAnimBlueprintCustomization.h"

#include "Types/CsTypes_Weapon.h"

#define LOCTEXT_NAMESPACE "ECsWeaponAnimBlueprintCustomization"


FECsWeaponAnimBlueprintCustomization::FECsWeaponAnimBlueprintCustomization()
{
	Init<EMCsWeaponAnimBlueprint, FECsWeaponAnimBlueprint>();
}

TSharedRef<IPropertyTypeCustomization> FECsWeaponAnimBlueprintCustomization::MakeInstance()
{
	return MakeShareable(new FECsWeaponAnimBlueprintCustomization);
}

void FECsWeaponAnimBlueprintCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsWeaponAnimBlueprint>(StructPropertyHandle);
}

void FECsWeaponAnimBlueprintCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EMCsWeaponAnimBlueprint, FECsWeaponAnimBlueprint>(DisplayName);
}

void FECsWeaponAnimBlueprintCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EMCsWeaponAnimBlueprint, FECsWeaponAnimBlueprint>(OutDisplayName);
}

#undef LOCTEXT_NAMESPACE
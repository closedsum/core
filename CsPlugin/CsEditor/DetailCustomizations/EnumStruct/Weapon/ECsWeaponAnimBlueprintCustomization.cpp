// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/Weapon/ECsWeaponAnimBlueprintCustomization.h"

#include "Types/CsTypes_Weapon.h"

#define LOCTEXT_NAMESPACE "ECsWeaponAnimBlueprintCustomization"


FECsWeaponAnimBlueprintCustomization::FECsWeaponAnimBlueprintCustomization()
{
	Init<FECsWeaponAnimBlueprint, EMCsWeaponAnimBlueprint>();
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
	SetEnumWithDisplayName_Internal<FECsWeaponAnimBlueprint, EMCsWeaponAnimBlueprint>(DisplayName);
}

#undef LOCTEXT_NAMESPACE

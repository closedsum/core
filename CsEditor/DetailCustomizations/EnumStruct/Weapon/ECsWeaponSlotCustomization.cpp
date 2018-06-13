// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/Weapon/ECsWeaponSlotCustomization.h"

#include "Types/CsTypes_Weapon.h"

#define LOCTEXT_NAMESPACE "ECsWeaponSlotCustomization"


FECsWeaponSlotCustomization::FECsWeaponSlotCustomization()
{
	Init<FECsWeaponSlot, EMCsWeaponSlot>();
}

TSharedRef<IPropertyTypeCustomization> FECsWeaponSlotCustomization::MakeInstance()
{
	return MakeShareable(new FECsWeaponSlotCustomization);
}

void FECsWeaponSlotCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsWeaponSlot>(StructPropertyHandle);
}

void FECsWeaponSlotCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<FECsWeaponSlot, EMCsWeaponSlot>(DisplayName);
}

#undef LOCTEXT_NAMESPACE

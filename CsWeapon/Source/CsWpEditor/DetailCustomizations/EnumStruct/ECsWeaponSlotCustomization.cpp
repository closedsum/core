// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsWeaponSlotCustomization.h"

#include "CsTypes_Weapon.h"

#define LOCTEXT_NAMESPACE "ECsWeaponSlotCustomization"


FECsWeaponSlotCustomization::FECsWeaponSlotCustomization()
{
	Init<EMCsWeaponSlot, FECsWeaponSlot>();
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
	SetEnumWithDisplayName_Internal<EMCsWeaponSlot, FECsWeaponSlot>(DisplayName);
}

void FECsWeaponSlotCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EMCsWeaponSlot, FECsWeaponSlot>(OutDisplayName);
}

#undef LOCTEXT_NAMESPACE
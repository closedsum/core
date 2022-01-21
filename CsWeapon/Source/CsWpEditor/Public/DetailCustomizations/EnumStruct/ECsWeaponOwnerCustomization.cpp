// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsWeaponOwnerCustomization.h"

#include "Types/CsTypes_Weapon.h"

#define LOCTEXT_NAMESPACE "ECsWeaponOwnerCustomization"


FECsWeaponOwnerCustomization::FECsWeaponOwnerCustomization()
{
	Init<EMCsWeaponOwner, FECsWeaponOwner>();
}

TSharedRef<IPropertyTypeCustomization> FECsWeaponOwnerCustomization::MakeInstance()
{
	return MakeShareable(new FECsWeaponOwnerCustomization);
}

void FECsWeaponOwnerCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsWeaponOwner>(StructPropertyHandle);
}

void FECsWeaponOwnerCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EMCsWeaponOwner, FECsWeaponOwner>(DisplayName);
}

void FECsWeaponOwnerCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EMCsWeaponOwner, FECsWeaponOwner>(OutDisplayName);
}

#undef LOCTEXT_NAMESPACE
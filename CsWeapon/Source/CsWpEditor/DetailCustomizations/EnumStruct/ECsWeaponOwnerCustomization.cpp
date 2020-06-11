// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsWeaponOwnerCustomization.h"

#include "CsTypes_Weapon.h"

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

#undef LOCTEXT_NAMESPACE
// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/Weapon/ECsWeaponOwnerCustomization.h"

#include "Types/CsTypes_Weapon.h"

#define LOCTEXT_NAMESPACE "ECsWeaponOwnerCustomization"


FECsWeaponOwnerCustomization::FECsWeaponOwnerCustomization()
{
	Init<FECsWeaponOwner, EMCsWeaponOwner>();
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
	SetEnumWithDisplayName_Internal<FECsWeaponOwner, EMCsWeaponOwner>(DisplayName);
}

#undef LOCTEXT_NAMESPACE

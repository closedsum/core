// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsWeaponGripCustomization.h"

#include "Types/CsTypes_Weapon.h"

#define LOCTEXT_NAMESPACE "ECsWeaponGripCustomization"


FECsWeaponGripCustomization::FECsWeaponGripCustomization()
{
	Init<EMCsWeaponGrip, FECsWeaponGrip>();
}

TSharedRef<IPropertyTypeCustomization> FECsWeaponGripCustomization::MakeInstance()
{
	return MakeShareable(new FECsWeaponGripCustomization);
}

void FECsWeaponGripCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsWeaponGrip>(StructPropertyHandle);
}

void FECsWeaponGripCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EMCsWeaponGrip, FECsWeaponGrip>(DisplayName);
}

void FECsWeaponGripCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EMCsWeaponGrip, FECsWeaponGrip>(OutDisplayName);
}

#undef LOCTEXT_NAMESPACE
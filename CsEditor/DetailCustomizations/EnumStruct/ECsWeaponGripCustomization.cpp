// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsWeaponGripCustomization.h"

#include "Types/CsTypes_Weapon.h"

#define LOCTEXT_NAMESPACE "ECsWeaponGripCustomization"


FECsWeaponGripCustomization::FECsWeaponGripCustomization()
{
	Init<FECsWeaponGrip, EMCsWeaponGrip>();
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
	SetEnumWithDisplayName_Internal<FECsWeaponGrip, EMCsWeaponGrip>(DisplayName);
}

#undef LOCTEXT_NAMESPACE

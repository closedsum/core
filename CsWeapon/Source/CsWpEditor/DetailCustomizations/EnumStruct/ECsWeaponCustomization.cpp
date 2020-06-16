// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsWeaponCustomization.h"

#include "CsTypes_Weapon.h"

#define LOCTEXT_NAMESPACE "ECsWeaponCustomization"

// Cached
#pragma region

namespace NCsWeaponCustomizationCached
{
	namespace Str
	{
		const FString CustomPopulateEnumMap = TEXT("FECsWeaponCustomization::CustomPopulateEnumMap");
	}
}

#pragma endregion Cached

FECsWeaponCustomization::FECsWeaponCustomization()
{
	Init<EMCsWeapon, FECsWeapon>();
}

void FECsWeaponCustomization::CustomPopulateEnumMap()
{
	using namespace NCsWeaponCustomizationCached;

	NCsWeapon::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

TSharedRef<IPropertyTypeCustomization> FECsWeaponCustomization::MakeInstance()
{
	return MakeShareable(new FECsWeaponCustomization);
}

void FECsWeaponCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsWeapon>(StructPropertyHandle);
}

void FECsWeaponCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EMCsWeapon, FECsWeapon>(DisplayName);
}

#undef LOCTEXT_NAMESPACE
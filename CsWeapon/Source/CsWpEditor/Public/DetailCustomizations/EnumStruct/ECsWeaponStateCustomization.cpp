// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsWeaponStateCustomization.h"

#include "Types/CsTypes_Weapon.h"

#define LOCTEXT_NAMESPACE "ECsWeaponStateCustomization"

// Cached
#pragma region

namespace NCsWeaponStateCustomizationCached
{
	namespace Str
	{
		const FString CustomPopulateEnumMap = TEXT("FECsWeaponStateCustomization::CustomPopulateEnumMap");
	}
}

#pragma endregion Cached

FECsWeaponStateCustomization::FECsWeaponStateCustomization()
{
	Init<EMCsWeaponState, FECsWeaponState>();
}

void FECsWeaponStateCustomization::CustomPopulateEnumMap()
{
	using namespace NCsWeaponStateCustomizationCached;

	NCsWeaponState::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

TSharedRef<IPropertyTypeCustomization> FECsWeaponStateCustomization::MakeInstance()
{
	return MakeShareable(new FECsWeaponStateCustomization);
}

void FECsWeaponStateCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsWeaponState>(StructPropertyHandle);
}

void FECsWeaponStateCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EMCsWeaponState, FECsWeaponState>(DisplayName);
}

void FECsWeaponStateCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EMCsWeaponState, FECsWeaponState>(OutDisplayName);
}

#undef LOCTEXT_NAMESPACE
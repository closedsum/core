// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsWeaponClassCustomization.h"

#include "Types/CsTypes_Weapon.h"

#define LOCTEXT_NAMESPACE "ECsWeaponClassCustomization"

// Cached
#pragma region

namespace NCsWeaponClassCustomizationCached
{
	namespace Str
	{
		const FString CustomPopulateEnumMap = TEXT("FECsWeaponClassCustomization::CustomPopulateEnumMap");
	}
}

#pragma endregion Cached

FECsWeaponClassCustomization::FECsWeaponClassCustomization()
{
	Init<EMCsWeaponClass, FECsWeaponClass>();
}

void FECsWeaponClassCustomization::CustomPopulateEnumMap()
{
	using namespace NCsWeaponClassCustomizationCached;

	NCsWeaponClass::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

TSharedRef<IPropertyTypeCustomization> FECsWeaponClassCustomization::MakeInstance()
{
	return MakeShareable(new FECsWeaponClassCustomization);
}

void FECsWeaponClassCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsWeaponClass>(StructPropertyHandle);
}

void FECsWeaponClassCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EMCsWeaponClass, FECsWeaponClass>(DisplayName);
}

void FECsWeaponClassCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EMCsWeaponClass, FECsWeaponClass>(OutDisplayName);
}

#undef LOCTEXT_NAMESPACE
// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsWeaponCustomization.h"

#include "Types/CsTypes_Weapon.h"

#define LOCTEXT_NAMESPACE "ECsWeaponCustomization"

// Cached
#pragma region

namespace NCsWeaponCustomization
{
	namespace NCached
	{
		namespace Str
		{
			const FString CustomPopulateEnumMap = TEXT("FECsWeaponCustomization::CustomPopulateEnumMap");
		}
	}
}

#pragma endregion Cached

#define EnumMapType EMCsWeapon
#define EnumType FECsWeapon

FECsWeaponCustomization::FECsWeaponCustomization()
{
	Init<EnumMapType, EnumType>();
}

void FECsWeaponCustomization::CustomPopulateEnumMap()
{
	using namespace NCsWeaponCustomization::NCached;

	NCsWeapon::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

TSharedRef<IPropertyTypeCustomization> FECsWeaponCustomization::MakeInstance()
{
	return MakeShareable(new FECsWeaponCustomization);
}

void FECsWeaponCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<EnumType>(StructPropertyHandle);
}

void FECsWeaponCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EnumMapType, EnumType>(DisplayName);
}

void FECsWeaponCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EnumMapType, EnumType>(OutDisplayName);
}

#undef EnumMapType
#undef EnumType


#undef LOCTEXT_NAMESPACE
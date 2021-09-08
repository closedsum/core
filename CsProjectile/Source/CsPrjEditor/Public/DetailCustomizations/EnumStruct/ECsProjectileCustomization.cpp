// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsProjectileCustomization.h"

// Managers
#include "Types/CsTypes_Projectile.h"
// Settings
#include "Settings/CsProjectileSettings.h"

#define LOCTEXT_NAMESPACE "ECsProjectileCustomization"

// Cached
#pragma region

namespace NCsProjectileCustomizationCached
{
	namespace Str
	{
		const FString CustomPopulateEnumMap = TEXT("FECsProjectileCustomization::CustomPopulateEnumMap");
	}
}

#pragma endregion Cached

#define EnumMapType EMCsProjectile
#define EnumType FECsProjectile

FECsProjectileCustomization::FECsProjectileCustomization() :
	Super()
{
	Init<EnumMapType, EnumType>();
}

void FECsProjectileCustomization::CustomPopulateEnumMap()
{
	using namespace NCsProjectileCustomizationCached;

	NCsProjectile::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

TSharedRef<IPropertyTypeCustomization> FECsProjectileCustomization::MakeInstance()
{
	return MakeShareable(new FECsProjectileCustomization);
}

void FECsProjectileCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<EnumType>(StructPropertyHandle);
}

void FECsProjectileCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EnumMapType, EnumType>(DisplayName);
}

void FECsProjectileCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EnumMapType, EnumType>(OutDisplayName);
}

#undef EnumMapType
#undef EnumType

#undef LOCTEXT_NAMESPACE

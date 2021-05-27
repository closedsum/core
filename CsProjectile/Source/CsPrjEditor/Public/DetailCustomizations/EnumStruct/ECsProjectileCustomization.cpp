// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
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

FECsProjectileCustomization::FECsProjectileCustomization() :
	Super()
{
	Init<EMCsProjectile, FECsProjectile>();
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
	SetPropertyHandles_Internal<FECsProjectile>(StructPropertyHandle);
}

void FECsProjectileCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EMCsProjectile, FECsProjectile>(DisplayName);
}

void FECsProjectileCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EMCsProjectile, FECsProjectile>(OutDisplayName);
}

#undef LOCTEXT_NAMESPACE

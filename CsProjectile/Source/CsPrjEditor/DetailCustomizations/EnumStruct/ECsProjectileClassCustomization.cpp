// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsProjectileClassCustomization.h"

// Types
#include "Managers/Projectile/CsTypes_Projectile.h"

#define LOCTEXT_NAMESPACE "ECsProjectileClassCustomization"

// Cached
#pragma region

namespace NCsProjectileClassCustomizationCached
{
	namespace Str
	{
		const FString CustomPopulateEnumMap = TEXT("FECsProjectileClassCustomization::CustomPopulateEnumMap");
	}
}

#pragma endregion Cached

FECsProjectileClassCustomization::FECsProjectileClassCustomization() :
	Super()
{
	Init<EMCsProjectileClass, FECsProjectileClass>();
}

void FECsProjectileClassCustomization::CustomPopulateEnumMap()
{
	using namespace NCsProjectileClassCustomizationCached;

	NCsProjectileClass::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

TSharedRef<IPropertyTypeCustomization> FECsProjectileClassCustomization::MakeInstance()
{
	return MakeShareable(new FECsProjectileClassCustomization);
}

void FECsProjectileClassCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsProjectileClass>(StructPropertyHandle);
}

void FECsProjectileClassCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EMCsProjectileClass, FECsProjectileClass>(DisplayName);
}

void FECsProjectileClassCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EMCsProjectileClass, FECsProjectileClass>(OutDisplayName);
}

#undef LOCTEXT_NAMESPACE

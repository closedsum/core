// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/FX/ECsFXCustomization.h"

// Managers
#include "Managers/FX/CsTypes_FX.h"
// Settings
#include "Settings/CsDeveloperSettings.h"

#define LOCTEXT_NAMESPACE "ECsFXCustomization"

// Cached
#pragma region

namespace NCsFXCustomizationCached
{
	namespace Str
	{
		const FString CustomPopulateEnumMap = TEXT("FECsFXCustomization::CustomPopulateEnumMap");
	}
}

#pragma endregion Cached

FECsFXCustomization::FECsFXCustomization() :
	Super()
{
	Init<EMCsFX, FECsFX>();
}

void FECsFXCustomization::CustomPopulateEnumMap()
{
	using namespace NCsFXCustomizationCached;

	NCsFX::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

TSharedRef<IPropertyTypeCustomization> FECsFXCustomization::MakeInstance()
{
	return MakeShareable(new FECsFXCustomization);
}

void FECsFXCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsFX>(StructPropertyHandle);
}

void FECsFXCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EMCsFX, FECsFX>(DisplayName);
}

void FECsFXCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EMCsFX, FECsFX>(OutDisplayName);
}

#undef LOCTEXT_NAMESPACE

// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/Sound/ECsSoundCustomization.h"

#include "Managers/Sound/CsTypes_Sound.h"

#define LOCTEXT_NAMESPACE "ECsSurfaceCustomization"

// Cached
#pragma region

namespace NCsSoundCustomizationCached
{
	namespace Str
	{
		const FString CustomPopulateEnumMap = TEXT("FECsSoundCustomization::CustomPopulateEnumMap");
	}
}

#pragma endregion Cached

FECsSoundCustomization::FECsSoundCustomization() :
	Super()
{
	Init<EMCsSound, FECsSound>();
}

void FECsSoundCustomization::CustomPopulateEnumMap()
{
	using namespace NCsSoundCustomizationCached;

	NCsSound::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

TSharedRef<IPropertyTypeCustomization> FECsSoundCustomization::MakeInstance()
{
	return MakeShareable(new FECsSoundCustomization);
}

void FECsSoundCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsSound>(StructPropertyHandle);
}

void FECsSoundCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EMCsSound, FECsSound>(DisplayName);
}

void FECsSoundCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EMCsSound, FECsSound>(OutDisplayName);
}

#undef LOCTEXT_NAMESPACE

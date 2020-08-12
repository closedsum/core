// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/Input/ECsGameEventCustomization.h"

#include "Managers/Input/CsTypes_Input.h"

#define LOCTEXT_NAMESPACE "ECsGameEventCustomization"

// Cached
#pragma region

namespace NCsGameEventCustomizationCached
{
	namespace Str
	{
		const FString CustomPopulateEnumMap = TEXT("FECsGameEventCustomization::CustomPopulateEnumMap");
	}
}

#pragma endregion Cached

FECsGameEventCustomization::FECsGameEventCustomization() :
	Super()
{
	Init<EMCsGameEvent, FECsGameEvent>();
}

TSharedRef<IPropertyTypeCustomization> FECsGameEventCustomization::MakeInstance()
{
	return MakeShareable(new FECsGameEventCustomization);
}

void FECsGameEventCustomization::CustomPopulateEnumMap()
{
	using namespace NCsGameEventCustomizationCached;

	NCsGameEvent::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

void FECsGameEventCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsGameEvent>(StructPropertyHandle);
}

void FECsGameEventCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EMCsGameEvent, FECsGameEvent>(DisplayName);
}

void FECsGameEventCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EMCsGameEvent, FECsGameEvent>(OutDisplayName);
}

#undef LOCTEXT_NAMESPACE

// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/FX/ECsFXCustomization.h"

// Managers
#include "Managers/FX/CsTypes_FX.h"
// Settings
#include "Settings/CsDeveloperSettings.h"

#define LOCTEXT_NAMESPACE "ECsFXCustomization"

// Cached
#pragma region

namespace NCsFXCustomization
{
	namespace NCached
	{
		namespace Str
		{
			const FString CustomPopulateEnumMap = TEXT("FECsFXCustomization::CustomPopulateEnumMap");
		}
	}
}

#pragma endregion Cached

#define EnumMapType EMCsFX
#define EnumType FECsFX

FECsFXCustomization::FECsFXCustomization() :
	Super()
{
	Init<EnumMapType, EnumType>();
}

void FECsFXCustomization::CustomPopulateEnumMap()
{
	using namespace NCsFXCustomization::NCached;

	NCsFX::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

TSharedRef<IPropertyTypeCustomization> FECsFXCustomization::MakeInstance()
{
	return MakeShareable(new FECsFXCustomization);
}

void FECsFXCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<EnumType>(StructPropertyHandle);
}

void FECsFXCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EnumMapType, EnumType>(DisplayName);
}

void FECsFXCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EnumMapType, EnumType>(OutDisplayName);
}

#undef EnumMapType
#undef EnumType

#undef LOCTEXT_NAMESPACE

// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "DetailCustomizations/EnumStruct/ECsBeamCustomization.h"

// Types
#include "Types/CsTypes_Beam.h"

#define LOCTEXT_NAMESPACE "ECsBeamCustomization"

// Cached
#pragma region

namespace NCsBeamCustomizationCached
{
	namespace Str
	{
		const FString CustomPopulateEnumMap = TEXT("FECsBeamCustomization::CustomPopulateEnumMap");
	}
}

#pragma endregion Cached

#define EnumMapType EMCsBeam
#define EnumType FECsBeam

FECsBeamCustomization::FECsBeamCustomization() :
	Super()
{
	Init<EnumMapType, EnumType>();
}

void FECsBeamCustomization::CustomPopulateEnumMap()
{
	using namespace NCsBeamCustomizationCached;

	NCsBeam::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

TSharedRef<IPropertyTypeCustomization> FECsBeamCustomization::MakeInstance()
{
	return MakeShareable(new FECsBeamCustomization);
}

void FECsBeamCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<EnumType>(StructPropertyHandle);
}

void FECsBeamCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EnumMapType, EnumType>(DisplayName);
}

void FECsBeamCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EnumMapType, EnumType>(OutDisplayName);
}

#undef EnumMapType
#undef EnumType

#undef LOCTEXT_NAMESPACE

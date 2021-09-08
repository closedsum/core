// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/Sound/ECsSoundCustomization.h"

#include "Managers/Sound/CsTypes_Sound.h"

#define LOCTEXT_NAMESPACE "ECsSurfaceCustomization"

// Cached
#pragma region

namespace NCsSoundCustomization
{
	namespace NCached
	{
		namespace Str
		{
			const FString CustomPopulateEnumMap = TEXT("FECsSoundCustomization::CustomPopulateEnumMap");
		}
	}
}

#pragma endregion Cached

#define EnumMapType EMCsSound
#define EnumType FECsSound

FECsSoundCustomization::FECsSoundCustomization() :
	Super()
{
	Init<EnumMapType, EnumType>();
}

void FECsSoundCustomization::CustomPopulateEnumMap()
{
	using namespace NCsSoundCustomization::NCached;

	NCsSound::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

TSharedRef<IPropertyTypeCustomization> FECsSoundCustomization::MakeInstance()
{
	return MakeShareable(new FECsSoundCustomization);
}

void FECsSoundCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<EnumType>(StructPropertyHandle);
}

void FECsSoundCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EnumMapType, EnumType>(DisplayName);
}

void FECsSoundCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EnumMapType, EnumType>(OutDisplayName);
}

#undef EnumMapType
#undef EnumType

#undef LOCTEXT_NAMESPACE

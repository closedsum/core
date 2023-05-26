// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/Input/ECsGameEventCustomization.h"

#include "Managers/Input/GameEvent/CsGameEvent.h"

#define LOCTEXT_NAMESPACE "ECsGameEventCustomization"

// Cached
#pragma region

namespace NCsGameEventCustomization
{
	namespace NCached
	{
		namespace Str
		{
			const FString CustomPopulateEnumMap = TEXT("FECsGameEventCustomization::CustomPopulateEnumMap");
		}
	}
}

#pragma endregion Cached

#define EnumMapType EMCsGameEvent
#define EnumType FECsGameEvent

FECsGameEventCustomization::FECsGameEventCustomization() :
	Super()
{
	Init<EnumMapType, EnumType>();
}

TSharedRef<IPropertyTypeCustomization> FECsGameEventCustomization::MakeInstance()
{
	return MakeShareable(new FECsGameEventCustomization);
}

void FECsGameEventCustomization::CustomPopulateEnumMap()
{
	using namespace NCsGameEventCustomization::NCached;

	NCsGameEvent::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

void FECsGameEventCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<EnumType>(StructPropertyHandle);
}

void FECsGameEventCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EnumMapType, EnumType>(DisplayName);
}

void FECsGameEventCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EnumMapType, EnumType>(OutDisplayName);
}

#undef EnumMapType
#undef EnumType

#undef LOCTEXT_NAMESPACE

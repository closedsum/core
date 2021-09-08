// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/WidgetActor/ECsWidgetActorClassCustomization.h"

// Types
#include "Managers/WidgetActor/CsTypes_WidgetActor.h"

#define LOCTEXT_NAMESPACE "ECsWidgetActorClassCustomization"

// Cached
#pragma region

namespace NCsWidgetActorClassCustomizationCached
{
	namespace Str
	{
		const FString CustomPopulateEnumMap = TEXT("FECsWidgetActorClassCustomization::CustomPopulateEnumMap");
	}
}

#pragma endregion Cached

FECsWidgetActorClassCustomization::FECsWidgetActorClassCustomization() :
	Super()
{
	Init<EMCsWidgetActorClass, FECsWidgetActorClass>();
}

void FECsWidgetActorClassCustomization::CustomPopulateEnumMap()
{
	using namespace NCsWidgetActorClassCustomizationCached;

	NCsWidgetActorClass::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

TSharedRef<IPropertyTypeCustomization> FECsWidgetActorClassCustomization::MakeInstance()
{
	return MakeShareable(new FECsWidgetActorClassCustomization);
}

void FECsWidgetActorClassCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsWidgetActorClass>(StructPropertyHandle);
}

void FECsWidgetActorClassCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EMCsWidgetActorClass, FECsWidgetActorClass>(DisplayName);
}

void FECsWidgetActorClassCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EMCsWidgetActorClass, FECsWidgetActorClass>(OutDisplayName);
}

#undef LOCTEXT_NAMESPACE

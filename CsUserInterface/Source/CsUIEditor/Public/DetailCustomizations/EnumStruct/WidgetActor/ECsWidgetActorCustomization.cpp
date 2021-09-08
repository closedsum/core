// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/WidgetActor/ECsWidgetActorCustomization.h"

// Managers
#include "Managers/WidgetActor/CsTypes_WidgetActor.h"

#define LOCTEXT_NAMESPACE "ECsWidgetActorCustomization"

// Cached
#pragma region

namespace NCsWidgetActorCustomizationCached
{
	namespace Str
	{
		const FString CustomPopulateEnumMap = TEXT("FECsWidgetActorCustomization::CustomPopulateEnumMap");
	}
}

#pragma endregion Cached

FECsWidgetActorCustomization::FECsWidgetActorCustomization() :
	Super()
{
	Init<EMCsWidgetActor, FECsWidgetActor>();
}

void FECsWidgetActorCustomization::CustomPopulateEnumMap()
{
	using namespace NCsWidgetActorCustomizationCached;

	NCsWidgetActor::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

TSharedRef<IPropertyTypeCustomization> FECsWidgetActorCustomization::MakeInstance()
{
	return MakeShareable(new FECsWidgetActorCustomization);
}

void FECsWidgetActorCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsWidgetActor>(StructPropertyHandle);
}

void FECsWidgetActorCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EMCsWidgetActor, FECsWidgetActor>(DisplayName);
}

void FECsWidgetActorCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EMCsWidgetActor, FECsWidgetActor>(OutDisplayName);
}

#undef LOCTEXT_NAMESPACE

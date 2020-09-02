// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/UserWidget/ECsUserWidgetPooledCustomization.h"

// Managers
#include "Managers/UserWidget/CsTypes_UserWidget.h"

#define LOCTEXT_NAMESPACE "ECsUserWidgetPooledCustomization"

// Cached
#pragma region

namespace NCsUserWidgetPooledCustomizationCached
{
	namespace Str
	{
		const FString CustomPopulateEnumMap = TEXT("FECsUserWidgetPooledCustomization::CustomPopulateEnumMap");
	}
}

#pragma endregion Cached

FECsUserWidgetPooledCustomization::FECsUserWidgetPooledCustomization() :
	Super()
{
	Init<EMCsUserWidgetPooled, FECsUserWidgetPooled>();
}

void FECsUserWidgetPooledCustomization::CustomPopulateEnumMap()
{
	using namespace NCsUserWidgetPooledCustomizationCached;

	NCsUserWidgetPooled::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

TSharedRef<IPropertyTypeCustomization> FECsUserWidgetPooledCustomization::MakeInstance()
{
	return MakeShareable(new FECsUserWidgetPooledCustomization);
}

void FECsUserWidgetPooledCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsUserWidgetPooled>(StructPropertyHandle);
}

void FECsUserWidgetPooledCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EMCsUserWidgetPooled, FECsUserWidgetPooled>(DisplayName);
}

void FECsUserWidgetPooledCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EMCsUserWidgetPooled, FECsUserWidgetPooled>(OutDisplayName);
}

#undef LOCTEXT_NAMESPACE

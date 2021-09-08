// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/UserWidget/ECsUserWidgetCustomization.h"

// Managers
#include "Managers/UserWidget/CsTypes_UserWidget.h"

#define LOCTEXT_NAMESPACE "ECsUserWidgetCustomization"

// Cached
#pragma region

namespace NCsUserWidgetCustomizationCached
{
	namespace Str
	{
		const FString CustomPopulateEnumMap = TEXT("FECsUserWidgetCustomization::CustomPopulateEnumMap");
	}
}

#pragma endregion Cached

FECsUserWidgetCustomization::FECsUserWidgetCustomization() :
	Super()
{
	Init<EMCsUserWidget, FECsUserWidget>();
}

void FECsUserWidgetCustomization::CustomPopulateEnumMap()
{
	using namespace NCsUserWidgetCustomizationCached;

	NCsUserWidget::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

TSharedRef<IPropertyTypeCustomization> FECsUserWidgetCustomization::MakeInstance()
{
	return MakeShareable(new FECsUserWidgetCustomization);
}

void FECsUserWidgetCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsUserWidget>(StructPropertyHandle);
}

void FECsUserWidgetCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EMCsUserWidget, FECsUserWidget>(DisplayName);
}

void FECsUserWidgetCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EMCsUserWidget, FECsUserWidget>(OutDisplayName);
}

#undef LOCTEXT_NAMESPACE

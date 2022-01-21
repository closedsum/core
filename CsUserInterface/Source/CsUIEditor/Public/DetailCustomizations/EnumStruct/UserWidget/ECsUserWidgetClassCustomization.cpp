// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/UserWidget/ECsUserWidgetClassCustomization.h"

// Types
#include "Managers/UserWidget/CsTypes_UserWidget.h"

#define LOCTEXT_NAMESPACE "ECsUserWidgetClassCustomization"

// Cached
#pragma region

namespace NCsUserWidgetClassCustomizationCached
{
	namespace Str
	{
		const FString CustomPopulateEnumMap = TEXT("FECsUserWidgetClassCustomization::CustomPopulateEnumMap");
	}
}

#pragma endregion Cached

FECsUserWidgetClassCustomization::FECsUserWidgetClassCustomization() :
	Super()
{
	Init<EMCsUserWidgetClass, FECsUserWidgetClass>();
}

void FECsUserWidgetClassCustomization::CustomPopulateEnumMap()
{
	using namespace NCsUserWidgetClassCustomizationCached;

	NCsUserWidgetClass::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

TSharedRef<IPropertyTypeCustomization> FECsUserWidgetClassCustomization::MakeInstance()
{
	return MakeShareable(new FECsUserWidgetClassCustomization);
}

void FECsUserWidgetClassCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsUserWidgetClass>(StructPropertyHandle);
}

void FECsUserWidgetClassCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EMCsUserWidgetClass, FECsUserWidgetClass>(DisplayName);
}

void FECsUserWidgetClassCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EMCsUserWidgetClass, FECsUserWidgetClass>(OutDisplayName);
}

#undef LOCTEXT_NAMESPACE

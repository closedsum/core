// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/UserWidget/ECsUserWidgetCustomization.h"

// Managers
#include "Managers/UserWidget/CsTypes_UserWidget.h"

#define LOCTEXT_NAMESPACE "ECsUserWidgetCustomization"

// Cached
#pragma region

namespace NCsUserWidgetCustomization
{
	namespace NCached
	{
		namespace Str
		{
			const FString CustomPopulateEnumMap = TEXT("FECsUserWidgetCustomization::CustomPopulateEnumMap");
		}
	}
}

#pragma endregion Cached

#define EnumMapType EMCsUserWidget
#define EnumType FECsUserWidget

FECsUserWidgetCustomization::FECsUserWidgetCustomization() :
	Super()
{
	Init<EnumMapType, EnumType>();
}

void FECsUserWidgetCustomization::CustomPopulateEnumMap()
{
	using namespace NCsUserWidgetCustomization::NCached;

	NCsUserWidget::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

TSharedRef<IPropertyTypeCustomization> FECsUserWidgetCustomization::MakeInstance()
{
	return MakeShareable(new FECsUserWidgetCustomization);
}

void FECsUserWidgetCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<EnumType>(StructPropertyHandle);
}

void FECsUserWidgetCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EnumMapType, EnumType>(DisplayName);
}

void FECsUserWidgetCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EnumMapType, EnumType>(OutDisplayName);
}

#undef EnumMapType
#undef EnumType

#undef LOCTEXT_NAMESPACE

// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
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

#define CLASS_TYPE FECsUserWidgetCustomization
#define EnumMapType EMCsUserWidget
#define EnumType FECsUserWidget

CLASS_TYPE::CLASS_TYPE() :
	Super()
{
	Init<EnumMapType, EnumType>();
}

void CLASS_TYPE::CustomPopulateEnumMap()
{
	using namespace NCsUserWidgetCustomization::NCached;

	NCsUserWidget::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

TSharedRef<IPropertyTypeCustomization> CLASS_TYPE::MakeInstance()
{
	return MakeShareable(new CLASS_TYPE);
}

void CLASS_TYPE::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<EnumType>(StructPropertyHandle);
}

void CLASS_TYPE::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EnumMapType, EnumType>(DisplayName);
}

void CLASS_TYPE::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EnumMapType, EnumType>(OutDisplayName);
}

#undef CLASS_TYPE
#undef EnumMapType
#undef EnumType

#undef LOCTEXT_NAMESPACE

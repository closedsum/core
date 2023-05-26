// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/UserWidget/ECsUserWidgetPooledCustomization.h"

// Managers
#include "Managers/UserWidget/CsTypes_UserWidget.h"

#define LOCTEXT_NAMESPACE "ECsUserWidgetPooledCustomization"

// Cached
#pragma region

namespace NCsUserWidgetPooledCustomization
{
	namespace NCached
	{
		namespace Str
		{
			const FString CustomPopulateEnumMap = TEXT("FECsUserWidgetPooledCustomization::CustomPopulateEnumMap");
		}
	}
}

#pragma endregion Cached

#define CLASS_TYPE FECsUserWidgetPooledCustomization
#define EnumMapType EMCsUserWidgetPooled
#define EnumType FECsUserWidgetPooled

CLASS_TYPE::CLASS_TYPE() :
	Super()
{
	Init<EnumMapType, EnumType>();
}

void CLASS_TYPE::CustomPopulateEnumMap()
{
	using namespace NCsUserWidgetPooledCustomization::NCached;

	NCsUserWidgetPooled::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
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
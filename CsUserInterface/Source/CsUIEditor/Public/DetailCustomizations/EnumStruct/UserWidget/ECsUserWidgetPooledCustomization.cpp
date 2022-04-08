// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
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

#define EnumMapType EMCsUserWidgetPooled
#define EnumType FECsUserWidgetPooled

FECsUserWidgetPooledCustomization::FECsUserWidgetPooledCustomization() :
	Super()
{
	Init<EnumMapType, EnumType>();
}

void FECsUserWidgetPooledCustomization::CustomPopulateEnumMap()
{
	using namespace NCsUserWidgetPooledCustomization::NCached;

	NCsUserWidgetPooled::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

TSharedRef<IPropertyTypeCustomization> FECsUserWidgetPooledCustomization::MakeInstance()
{
	return MakeShareable(new FECsUserWidgetPooledCustomization);
}

void FECsUserWidgetPooledCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<EnumType>(StructPropertyHandle);
}

void FECsUserWidgetPooledCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EnumMapType, EnumType>(DisplayName);
}

void FECsUserWidgetPooledCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EnumMapType, EnumType>(OutDisplayName);
}

#undef EnumMapType
#undef EnumType

#undef LOCTEXT_NAMESPACE
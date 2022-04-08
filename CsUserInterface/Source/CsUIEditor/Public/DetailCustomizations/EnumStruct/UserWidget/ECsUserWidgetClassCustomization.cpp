// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/UserWidget/ECsUserWidgetClassCustomization.h"

// Types
#include "Managers/UserWidget/CsTypes_UserWidget.h"

#define LOCTEXT_NAMESPACE "ECsUserWidgetClassCustomization"

// Cached
#pragma region

namespace NCsUserWidgetClassCustomization
{
	namespace NCached
	{
		namespace Str
		{
			const FString CustomPopulateEnumMap = TEXT("FECsUserWidgetClassCustomization::CustomPopulateEnumMap");
		}
	}
}

#pragma endregion Cached

#define EnumMapType EMCsUserWidgetClass
#define EnumType FECsUserWidgetClass

FECsUserWidgetClassCustomization::FECsUserWidgetClassCustomization() :
	Super()
{
	Init<EnumMapType, EnumType>();
}

void FECsUserWidgetClassCustomization::CustomPopulateEnumMap()
{
	using namespace NCsUserWidgetClassCustomization::NCached;

	NCsUserWidgetClass::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

TSharedRef<IPropertyTypeCustomization> FECsUserWidgetClassCustomization::MakeInstance()
{
	return MakeShareable(new FECsUserWidgetClassCustomization);
}

void FECsUserWidgetClassCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<EnumType>(StructPropertyHandle);
}

void FECsUserWidgetClassCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EnumMapType, EnumType>(DisplayName);
}

void FECsUserWidgetClassCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EnumMapType, EnumType>(OutDisplayName);
}

#undef EnumMapType
#undef EnumType

#undef LOCTEXT_NAMESPACE

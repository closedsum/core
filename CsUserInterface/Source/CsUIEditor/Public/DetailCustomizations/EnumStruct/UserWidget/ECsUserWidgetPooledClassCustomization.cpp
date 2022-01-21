// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/UserWidget/ECsUserWidgetPooledClassCustomization.h"

// Types
#include "Managers/UserWidget/CsTypes_UserWidget.h"

#define LOCTEXT_NAMESPACE "ECsUserWidgetPooledClassCustomization"

// Cached
#pragma region

namespace NCsUserWidgetPooledClassCustomizationCached
{
	namespace Str
	{
		const FString CustomPopulateEnumMap = TEXT("FECsUserWidgetPooledClassCustomization::CustomPopulateEnumMap");
	}
}

#pragma endregion Cached

FECsUserWidgetPooledClassCustomization::FECsUserWidgetPooledClassCustomization() :
	Super()
{
	Init<EMCsUserWidgetPooledClass, FECsUserWidgetPooledClass>();
}

void FECsUserWidgetPooledClassCustomization::CustomPopulateEnumMap()
{
	using namespace NCsUserWidgetPooledClassCustomizationCached;

	NCsUserWidgetPooledClass::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

TSharedRef<IPropertyTypeCustomization> FECsUserWidgetPooledClassCustomization::MakeInstance()
{
	return MakeShareable(new FECsUserWidgetPooledClassCustomization);
}

void FECsUserWidgetPooledClassCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsUserWidgetPooledClass>(StructPropertyHandle);
}

void FECsUserWidgetPooledClassCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EMCsUserWidgetPooledClass, FECsUserWidgetPooledClass>(DisplayName);
}

void FECsUserWidgetPooledClassCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EMCsUserWidgetPooledClass, FECsUserWidgetPooledClass>(OutDisplayName);
}

#undef LOCTEXT_NAMESPACE

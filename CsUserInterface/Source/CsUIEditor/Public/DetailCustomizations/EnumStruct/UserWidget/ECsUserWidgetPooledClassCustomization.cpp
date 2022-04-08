// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/UserWidget/ECsUserWidgetPooledClassCustomization.h"

// Types
#include "Managers/UserWidget/CsTypes_UserWidget.h"

#define LOCTEXT_NAMESPACE "ECsUserWidgetPooledClassCustomization"

// Cached
#pragma region

namespace NCsUserWidgetPooledClassCustomization
{
	namespace NCached
	{
		namespace Str
		{
			const FString CustomPopulateEnumMap = TEXT("FECsUserWidgetPooledClassCustomization::CustomPopulateEnumMap");
		}
	}
}

#pragma endregion Cached

#define EnumMapType EMCsUserWidgetPooledClass
#define EnumType FECsUserWidgetPooledClass

FECsUserWidgetPooledClassCustomization::FECsUserWidgetPooledClassCustomization() :
	Super()
{
	Init<EnumMapType, EnumType>();
}

void FECsUserWidgetPooledClassCustomization::CustomPopulateEnumMap()
{
	using namespace NCsUserWidgetPooledClassCustomization::NCached;

	NCsUserWidgetPooledClass::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

TSharedRef<IPropertyTypeCustomization> FECsUserWidgetPooledClassCustomization::MakeInstance()
{
	return MakeShareable(new FECsUserWidgetPooledClassCustomization);
}

void FECsUserWidgetPooledClassCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<EnumType>(StructPropertyHandle);
}

void FECsUserWidgetPooledClassCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EnumMapType, EnumType>(DisplayName);
}

void FECsUserWidgetPooledClassCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EnumMapType, EnumType>(OutDisplayName);
}

#undef EnumMapType
#undef EnumType

#undef LOCTEXT_NAMESPACE

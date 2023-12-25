// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/Data/ECsDataEntryDataCustomization.h"

// Types
#include "Data/CsTypes_DataEntry.h"

#define LOCTEXT_NAMESPACE "ECsDataEntryDataCustomization"

// Cached
#pragma region

namespace NCsDataEntryDataCustomization
{
	namespace NCached
	{
		namespace Str
		{
			const FString CustomPopulateEnumMap = TEXT("FECsDataEntryDataCustomization::CustomPopulateEnumMap");
		}
	}
}

#pragma endregion Cached

#define CLASS_TYPE FECsDataEntryDataCustomization
#define EnumMapType EMCsDataEntryData
#define EnumType FECsDataEntryData

CLASS_TYPE::CLASS_TYPE() :
	Super()
{
	Init<EnumMapType, EnumType>();
}

void CLASS_TYPE::CustomPopulateEnumMap()
{
	using namespace NCsDataEntryDataCustomization::NCached;

	NCsDataEntryData::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

void CLASS_TYPE::AddPropertyChange()
{
	NCsDataEntryData::AddPropertyChange();
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

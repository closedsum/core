// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/Input/ECsInputActionMapCustomization.h"

#include "Managers/Input/Action/CsInputActionMap.h"

#define LOCTEXT_NAMESPACE "ECsInputActionMapCustomization"

// Cached
#pragma region

namespace NCsInputActionMapCustomization
{
	namespace NCached
	{
		namespace Str
		{
			const FString CustomPopulateEnumMap = TEXT("FECsInputActionMapCustomization::CustomPopulateEnumMap");
		}
	}
}

#pragma endregion Cached

#define CLASS_TYPE FECsInputActionMapCustomization
#define EnumMapType EMCsInputActionMap
#define EnumType FECsInputActionMap

CLASS_TYPE::CLASS_TYPE() :
	Super()
{
	Init<EnumMapType, EnumType>();
}

void CLASS_TYPE::CustomPopulateEnumMap()
{
	using namespace NCsInputActionMapCustomization::NCached;

	NCsInputActionMap::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

void CLASS_TYPE::AddPropertyChange()
{
	NCsInputActionMap::AddPropertyChange();
}

TSharedRef<IPropertyTypeCustomization> CLASS_TYPE::MakeInstance()
{
	return MakeShareable(new CLASS_TYPE);
}

void CLASS_TYPE::AddEnumToMap(const FString& Name)
{
	EnumMapType::Get().CreateSafe(Name, true);
}

const FString& CLASS_TYPE::GetEnumStructName()
{
	return EnumMapType::Get().GetEnumName();
}

const FName& CLASS_TYPE::GetEnumStructFName()
{
	return EnumMapType::Get().GetEnumFName();
}

void CLASS_TYPE::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<EnumType>(StructPropertyHandle);
}

void CLASS_TYPE::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EnumMapType, EnumType, int32>(DisplayName);
}

void CLASS_TYPE::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EnumMapType, EnumType>(OutDisplayName);
}

#undef CLASS_TYPE
#undef EnumMapType
#undef EnumType

#undef LOCTEXT_NAMESPACE

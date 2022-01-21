// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
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

#define EnumMapType EMCsInputActionMap
#define EnumType FECsInputActionMap

FECsInputActionMapCustomization::FECsInputActionMapCustomization() :
	Super()
{
	Init<EnumMapType, EnumType>();
}

void FECsInputActionMapCustomization::CustomPopulateEnumMap()
{
	using namespace NCsInputActionMapCustomization::NCached;

	NCsInputActionMap::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

TSharedRef<IPropertyTypeCustomization> FECsInputActionMapCustomization::MakeInstance()
{
	return MakeShareable(new FECsInputActionMapCustomization);
}

void FECsInputActionMapCustomization::AddEnumToMap(const FString& Name)
{
	EnumMapType::Get().CreateSafe(Name, true);
}

const FString& FECsInputActionMapCustomization::GetEnumStructName()
{
	return EnumMapType::Get().GetEnumName();
}

const FName& FECsInputActionMapCustomization::GetEnumStructFName()
{
	return EnumMapType::Get().GetEnumFName();
}

void FECsInputActionMapCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<EnumType>(StructPropertyHandle);
}

void FECsInputActionMapCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EnumMapType, EnumType, int32>(DisplayName);
}

void FECsInputActionMapCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EnumMapType, EnumType>(OutDisplayName);
}

#undef EnumMapType
#undef EnumType

#undef LOCTEXT_NAMESPACE

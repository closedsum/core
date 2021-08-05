// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/Input/ECsInputActionCustomization.h"

#include "Managers/Input/Action/CsInputAction.h"

#define LOCTEXT_NAMESPACE "ECsInputActionCustomization"

// Cached
#pragma region

namespace NCsInputActionCustomization
{
	namespace NCached
	{
		namespace Str
		{
			const FString CustomPopulateEnumMap = TEXT("FECsInputActionCustomization::CustomPopulateEnumMap");
		}
	}
}

#pragma endregion Cached

#define EnumMapType EMCsInputAction
#define EnumType FECsInputAction

FECsInputActionCustomization::FECsInputActionCustomization() :
	Super()
{
	Init<EnumMapType, EnumType>();
}

void FECsInputActionCustomization::CustomPopulateEnumMap()
{
	using namespace NCsInputActionCustomization::NCached;

	NCsInputAction::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

TSharedRef<IPropertyTypeCustomization> FECsInputActionCustomization::MakeInstance()
{
	return MakeShareable(new FECsInputActionCustomization);
}

void FECsInputActionCustomization::AddEnumToMap(const FString& Name)
{
	EnumMapType::Get().CreateSafe(Name, true);
}

const FString& FECsInputActionCustomization::GetEnumStructName()
{
	return EnumMapType::Get().GetEnumName();
}

const FName& FECsInputActionCustomization::GetEnumStructFName()
{
	return EnumMapType::Get().GetEnumFName();
}

void FECsInputActionCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<EnumType>(StructPropertyHandle);
}

void FECsInputActionCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EnumMapType, EnumType>(DisplayName);
}

void FECsInputActionCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EnumMapType, EnumType>(OutDisplayName);
}

#undef EnumMapType
#undef EnumType

#undef LOCTEXT_NAMESPACE

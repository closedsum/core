// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/Update/ECsUpdateGroupCustomization.h"

#include "Managers/Time/CsTypes_Update.h"

#define LOCTEXT_NAMESPACE "ECsUpdateGroupCustomization"

// Cached
#pragma region

namespace NCsUpdateGroupCustomization
{
	namespace NCached
	{
		namespace Str
		{
			const FString CustomPopulateEnumMap = TEXT("FECsUpdateGroupCustomization::CustomPopulateEnumMap");
		}
	}
}

#pragma endregion Cached

#define EnumMapType EMCsUpdateGroup
#define EnumType FECsUpdateGroup

FECsUpdateGroupCustomization::FECsUpdateGroupCustomization() :
	Super()
{
	Init<EnumMapType, EnumType>();
}

void FECsUpdateGroupCustomization::CustomPopulateEnumMap()
{
	using namespace NCsUpdateGroupCustomization::NCached;

	//NCsUpdateGroup::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

TSharedRef<IPropertyTypeCustomization> FECsUpdateGroupCustomization::MakeInstance()
{
	return MakeShareable(new FECsUpdateGroupCustomization);
}

void FECsUpdateGroupCustomization::AddEnumToMap(const FString& Name)
{
	EnumMapType::Get().CreateSafe(Name, true);
}

const FString& FECsUpdateGroupCustomization::GetEnumStructName()
{
	return EnumMapType::Get().GetEnumName();
}

const FName& FECsUpdateGroupCustomization::GetEnumStructFName()
{
	return EnumMapType::Get().GetEnumFName();
}

void FECsUpdateGroupCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<EnumType>(StructPropertyHandle);
}

void FECsUpdateGroupCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EnumMapType, EnumType>(DisplayName);
}

void FECsUpdateGroupCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EnumMapType, EnumType>(OutDisplayName);
}

#undef EnumMapType
#undef EnumType

#undef LOCTEXT_NAMESPACE

// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsDamageDataCustomization.h"

#include "Managers/Damage/Data/Types/CsTypes_Data_Damage.h"

#define LOCTEXT_NAMESPACE "ECsDamageDataCustomization"

// Cached
#pragma region

namespace NCDamageDataCustomization
{
	namespace NCached
	{
		namespace Str
		{
			const FString CustomPopulateEnumMap = TEXT("FECsDamageDataCustomization::CustomPopulateEnumMap");
		}
	}
}

#pragma endregion Cached

#define EnumMapType EMCsDamageData
#define EnumType FECsDamageData

FECsDamageDataCustomization::FECsDamageDataCustomization() :
	Super()
{
	Init<EnumMapType, EnumType>();
}

void FECsDamageDataCustomization::CustomPopulateEnumMap()
{
	using namespace NCDamageDataCustomization::NCached;

	NCsDamageData::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

TSharedRef<IPropertyTypeCustomization> FECsDamageDataCustomization::MakeInstance()
{
	return MakeShareable(new FECsDamageDataCustomization);
}

void FECsDamageDataCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<EnumType>(StructPropertyHandle);
}

void FECsDamageDataCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EnumMapType, EnumType>(DisplayName);
}

void FECsDamageDataCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EnumMapType, EnumType>(OutDisplayName);
}

#undef EnumMapType
#undef EnumType

#undef LOCTEXT_NAMESPACE

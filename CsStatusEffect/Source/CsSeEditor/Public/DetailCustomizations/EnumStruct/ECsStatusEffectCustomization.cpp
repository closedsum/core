// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsStatusEffectCustomization.h"

// Managers
#include "Types/CsTypes_StatusEffect.h"

#define LOCTEXT_NAMESPACE "ECsStatusEffectCustomization"

// Cached
#pragma region

namespace NCsStatusEffectCustomization
{
	namespace NCached
	{
		namespace Str
		{
			const FString CustomPopulateEnumMap = TEXT("FECsStatusEffectCustomization::CustomPopulateEnumMap");
		}
	}
}

#pragma endregion Cached

#define EnumMapType EMCsStatusEffect
#define EnumType FECsStatusEffect

FECsStatusEffectCustomization::FECsStatusEffectCustomization() :
	Super()
{
	Init<EnumMapType, EnumType>();
}

void FECsStatusEffectCustomization::CustomPopulateEnumMap()
{
	using namespace NCsStatusEffectCustomization::NCached;

	NCsStatusEffect::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

TSharedRef<IPropertyTypeCustomization> FECsStatusEffectCustomization::MakeInstance()
{
	return MakeShareable(new FECsStatusEffectCustomization);
}

void FECsStatusEffectCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<EnumType>(StructPropertyHandle);
}

void FECsStatusEffectCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EnumMapType, EnumType>(DisplayName);
}

void FECsStatusEffectCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EnumMapType, EnumType>(OutDisplayName);
}

#undef EnumMapType
#undef EnumType

#undef LOCTEXT_NAMESPACE

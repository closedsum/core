// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsStatusEffectEventCustomization.h"

// Managers
#include "CsTypes_StatusEffect.h"

#define LOCTEXT_NAMESPACE "ECsStatusEffectEventCustomization"

// Cached
#pragma region

namespace NCsStatusEffectEventCustomizationCached
{
	namespace Str
	{
		const FString CustomPopulateEnumMap = TEXT("FECsStatusEffectEventCustomization::CustomPopulateEnumMap");
	}
}

#pragma endregion Cached

FECsStatusEffectEventCustomization::FECsStatusEffectEventCustomization() :
	Super()
{
	Init<EMCsStatusEffectEvent, FECsStatusEffectEvent>();
}

TSharedRef<IPropertyTypeCustomization> FECsStatusEffectEventCustomization::MakeInstance()
{
	return MakeShareable(new FECsStatusEffectEventCustomization);
}

void FECsStatusEffectEventCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsStatusEffectEvent>(StructPropertyHandle);
}

void FECsStatusEffectEventCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EMCsStatusEffectEvent, FECsStatusEffectEvent>(DisplayName);
}

#undef LOCTEXT_NAMESPACE

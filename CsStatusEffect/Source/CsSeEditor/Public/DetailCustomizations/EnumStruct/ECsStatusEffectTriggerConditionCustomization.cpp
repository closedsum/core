// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsStatusEffectTriggerConditionCustomization.h"

// Managers
#include "CsTypes_StatusEffect.h"

#define LOCTEXT_NAMESPACE "ECsStatusEffectTriggerConditionCustomization"

// Cached
#pragma region

namespace NCsStatusEffectTriggerConditionCustomizationCached
{
	namespace Str
	{
		const FString CustomPopulateEnumMap = TEXT("FECsStatusEffectTriggerConditionCustomization::CustomPopulateEnumMap");
	}
}

#pragma endregion Cached

FECsStatusEffectTriggerConditionCustomization::FECsStatusEffectTriggerConditionCustomization() :
	Super()
{
	Init<EMCsStatusEffectTriggerCondition, FECsStatusEffectTriggerCondition>();
}

TSharedRef<IPropertyTypeCustomization> FECsStatusEffectTriggerConditionCustomization::MakeInstance()
{
	return MakeShareable(new FECsStatusEffectTriggerConditionCustomization);
}

void FECsStatusEffectTriggerConditionCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsStatusEffectTriggerCondition>(StructPropertyHandle);
}

void FECsStatusEffectTriggerConditionCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EMCsStatusEffectTriggerCondition, FECsStatusEffectTriggerCondition>(DisplayName);
}

void FECsStatusEffectTriggerConditionCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EMCsStatusEffectTriggerCondition, FECsStatusEffectTriggerCondition>(OutDisplayName);
}

#undef LOCTEXT_NAMESPACE

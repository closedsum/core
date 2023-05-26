// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsStatusEffectTriggerConditionCustomization.h"

// Managers
#include "Trigger/CsTypes_StatusEffect_Trigger.h"

#define LOCTEXT_NAMESPACE "ECsStatusEffectTriggerConditionCustomization"

#define EnumMapType EMCsStatusEffectTriggerCondition
#define EnumType FECsStatusEffectTriggerCondition

FECsStatusEffectTriggerConditionCustomization::FECsStatusEffectTriggerConditionCustomization() :
	Super()
{
	Init<EnumMapType, EnumType>();
}

TSharedRef<IPropertyTypeCustomization> FECsStatusEffectTriggerConditionCustomization::MakeInstance()
{
	return MakeShareable(new FECsStatusEffectTriggerConditionCustomization);
}

void FECsStatusEffectTriggerConditionCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<EnumType>(StructPropertyHandle);
}

void FECsStatusEffectTriggerConditionCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EnumMapType, EnumType>(DisplayName);
}

void FECsStatusEffectTriggerConditionCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EnumMapType, EnumType>(OutDisplayName);
}

#undef EnumMapType
#undef EnumType

#undef LOCTEXT_NAMESPACE

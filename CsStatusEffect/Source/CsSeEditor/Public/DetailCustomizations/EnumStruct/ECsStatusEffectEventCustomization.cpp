// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsStatusEffectEventCustomization.h"

// Managers
#include "Types/CsTypes_StatusEffect.h"

#define LOCTEXT_NAMESPACE "ECsStatusEffectEventCustomization"

#define EnumMapType EMCsStatusEffectEvent
#define EnumType FECsStatusEffectEvent

FECsStatusEffectEventCustomization::FECsStatusEffectEventCustomization() :
	Super()
{
	Init<EnumMapType, EnumType>();
}

TSharedRef<IPropertyTypeCustomization> FECsStatusEffectEventCustomization::MakeInstance()
{
	return MakeShareable(new FECsStatusEffectEventCustomization);
}

void FECsStatusEffectEventCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<EnumType>(StructPropertyHandle);
}

void FECsStatusEffectEventCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EnumMapType, EnumType>(DisplayName);
}

void FECsStatusEffectEventCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EnumMapType, EnumType>(OutDisplayName);
}

#undef EnumMapType
#undef EnumType

#undef LOCTEXT_NAMESPACE

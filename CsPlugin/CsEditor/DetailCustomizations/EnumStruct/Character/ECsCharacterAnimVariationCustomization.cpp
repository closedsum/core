// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/Character/ECsCharacterAnimVariationCustomization.h"

#include "Types/CsTypes_Character.h"

#define LOCTEXT_NAMESPACE "ECsCharacterAnimVariationCustomization"


FECsCharacterAnimVariationCustomization::FECsCharacterAnimVariationCustomization()
{
	Init<FECsCharacterAnimVariation, EMCsCharacterAnimVariation>();
}

TSharedRef<IPropertyTypeCustomization> FECsCharacterAnimVariationCustomization::MakeInstance()
{
	return MakeShareable(new FECsCharacterAnimVariationCustomization);
}

void FECsCharacterAnimVariationCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsCharacterAnimVariation>(StructPropertyHandle);
}

void FECsCharacterAnimVariationCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<FECsCharacterAnimVariation, EMCsCharacterAnimVariation>(DisplayName);
}

#undef LOCTEXT_NAMESPACE

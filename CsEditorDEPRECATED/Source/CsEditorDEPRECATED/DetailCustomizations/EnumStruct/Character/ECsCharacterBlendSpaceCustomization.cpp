// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/Character/ECsCharacterBlendSpaceCustomization.h"

#include "Types/CsTypes_Character.h"

#define LOCTEXT_NAMESPACE "ECsCharacterBlendSpaceCustomization"


FECsCharacterBlendSpaceCustomization::FECsCharacterBlendSpaceCustomization()
{
	Init<EMCsCharacterBlendSpace, FECsCharacterBlendSpace>();
}

TSharedRef<IPropertyTypeCustomization> FECsCharacterBlendSpaceCustomization::MakeInstance()
{
	return MakeShareable(new FECsCharacterBlendSpaceCustomization);
}

void FECsCharacterBlendSpaceCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsCharacterBlendSpace>(StructPropertyHandle);
}

void FECsCharacterBlendSpaceCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EMCsCharacterBlendSpace, FECsCharacterBlendSpace>(DisplayName);
}

#undef LOCTEXT_NAMESPACE

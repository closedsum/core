// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/Character/ECsCharacterAnimCustomization.h"

#include "Types/CsTypes_Character.h"

#define LOCTEXT_NAMESPACE "ECsCharacterAnimCustomization"


FECsCharacterAnimCustomization::FECsCharacterAnimCustomization()
{
	Init<EMCsCharacterAnim, FECsCharacterAnim>();
}

TSharedRef<IPropertyTypeCustomization> FECsCharacterAnimCustomization::MakeInstance()
{
	return MakeShareable(new FECsCharacterAnimCustomization);
}

void FECsCharacterAnimCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsCharacterAnim>(StructPropertyHandle);
}

void FECsCharacterAnimCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EMCsCharacterAnim, FECsCharacterAnim>(DisplayName);
}

#undef LOCTEXT_NAMESPACE

// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/Character/ECsCharacterAnimBlueprintCustomization.h"

#include "Types/CsTypes_Character.h"

#define LOCTEXT_NAMESPACE "ECsCharacterAnimBlueprintCustomization"


FECsCharacterAnimBlueprintCustomization::FECsCharacterAnimBlueprintCustomization()
{
	Init<EMCsCharacterAnimBlueprint, FECsCharacterAnimBlueprint>();
}

TSharedRef<IPropertyTypeCustomization> FECsCharacterAnimBlueprintCustomization::MakeInstance()
{
	return MakeShareable(new FECsCharacterAnimBlueprintCustomization);
}

void FECsCharacterAnimBlueprintCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsCharacterAnimBlueprint>(StructPropertyHandle);
}

void FECsCharacterAnimBlueprintCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EMCsCharacterAnimBlueprint, FECsCharacterAnimBlueprint>(DisplayName);
}

#undef LOCTEXT_NAMESPACE

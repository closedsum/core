// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/Interaction/ECsInteractionCustomization.h"

// Types
#include "CsTypes_Interaction.h"

#define LOCTEXT_NAMESPACE "ECsInteractionCustomization"

#define EnumMapType EMCsInteraction
#define EnumType FECsInteraction

FECsInteractionCustomization::FECsInteractionCustomization() :
	Super()
{
	Init<EnumMapType, EnumType>();
}

TSharedRef<IPropertyTypeCustomization> FECsInteractionCustomization::MakeInstance()
{
	return MakeShareable(new FECsInteractionCustomization);
}

void FECsInteractionCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<EnumType>(StructPropertyHandle);
}

void FECsInteractionCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EnumMapType, EnumType>(DisplayName);
}

void FECsInteractionCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EnumMapType, EnumType>(OutDisplayName);
}

#undef EnumMapType
#undef EnumType

#undef LOCTEXT_NAMESPACE

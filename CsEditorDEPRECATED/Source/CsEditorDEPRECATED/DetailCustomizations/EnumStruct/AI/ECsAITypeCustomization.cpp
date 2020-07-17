// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/AI/ECsAITypeCustomization.h"

#include "AI/CsTypes_AI.h"

#define LOCTEXT_NAMESPACE "ECsAITypeCustomization"


FECsAITypeCustomization::FECsAITypeCustomization()
{
	Init<EMCsAIType, FECsAIType>();
}

TSharedRef<IPropertyTypeCustomization> FECsAITypeCustomization::MakeInstance()
{
	return MakeShareable(new FECsAITypeCustomization);
}

void FECsAITypeCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsAIType>(StructPropertyHandle);
}

void FECsAITypeCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EMCsAIType, FECsAIType>(DisplayName);
}

#undef LOCTEXT_NAMESPACE

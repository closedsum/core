// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/AI/ECsAITypeCustomization.h"

#include "Types/CsTypes_AI.h"

#define LOCTEXT_NAMESPACE "ECsAITypeCustomization"


FECsAITypeCustomization::FECsAITypeCustomization()
{
	Init<FECsAIType, EMCsAIType>();
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
	SetEnumWithDisplayName_Internal<FECsAIType, EMCsAIType>(DisplayName);
}

#undef LOCTEXT_NAMESPACE

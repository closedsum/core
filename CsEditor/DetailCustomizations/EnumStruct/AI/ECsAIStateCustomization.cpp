// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/AI/ECsAIStateCustomization.h"

#include "Types/CsTypes_AI.h"

#define LOCTEXT_NAMESPACE "ECsAIStateCustomization"


FECsAIStateCustomization::FECsAIStateCustomization()
{
	Init<FECsAIState, EMCsAIState>();
}

TSharedRef<IPropertyTypeCustomization> FECsAIStateCustomization::MakeInstance()
{
	return MakeShareable(new FECsAIStateCustomization);
}

void FECsAIStateCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsAIState>(StructPropertyHandle);
}

void FECsAIStateCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<FECsAIState, EMCsAIState>(DisplayName);
}

#undef LOCTEXT_NAMESPACE

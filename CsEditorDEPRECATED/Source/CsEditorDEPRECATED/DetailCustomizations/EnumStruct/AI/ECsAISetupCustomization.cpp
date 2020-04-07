// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/AI/ECsAISetupCustomization.h"

#include "AI/CsTypes_AI.h"

#define LOCTEXT_NAMESPACE "ECsAIStateCustomization"


FECsAISetupCustomization::FECsAISetupCustomization()
{
	Init<FECsAISetup, EMCsAISetup>();
}

TSharedRef<IPropertyTypeCustomization> FECsAISetupCustomization::MakeInstance()
{
	return MakeShareable(new FECsAISetupCustomization);
}

void FECsAISetupCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsAISetup>(StructPropertyHandle);
}

void FECsAISetupCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<FECsAISetup, EMCsAISetup>(DisplayName);
}

#undef LOCTEXT_NAMESPACE

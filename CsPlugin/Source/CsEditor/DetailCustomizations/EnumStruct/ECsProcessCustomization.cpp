// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsProcessCustomization.h"

#include "Managers/Process/CsProcess.h"

#define LOCTEXT_NAMESPACE "ECsProcessCustomization"


FECsProcessCustomization::FECsProcessCustomization()
{
	Init<FECsProcess, EMCsProcess>();
}

TSharedRef<IPropertyTypeCustomization> FECsProcessCustomization::MakeInstance()
{
	return MakeShareable(new FECsProcessCustomization);
}

void FECsProcessCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsProcess>(StructPropertyHandle);
}

void FECsProcessCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<FECsProcess, EMCsProcess>(DisplayName);
}

#undef LOCTEXT_NAMESPACE

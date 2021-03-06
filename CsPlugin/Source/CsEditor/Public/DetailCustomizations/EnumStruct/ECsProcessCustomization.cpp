// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsProcessCustomization.h"

#include "Managers/Process/CsProcess.h"

#define LOCTEXT_NAMESPACE "ECsProcessCustomization"


FECsProcessCustomization::FECsProcessCustomization() :
	Super()
{
	Init<EMCsProcess, FECsProcess>();
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
	SetEnumWithDisplayName_Internal<EMCsProcess, FECsProcess>(DisplayName);
}

void FECsProcessCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EMCsProcess, FECsProcess>(OutDisplayName);
}

#undef LOCTEXT_NAMESPACE

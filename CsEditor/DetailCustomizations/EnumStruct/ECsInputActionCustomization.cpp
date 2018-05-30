// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsInputActionCustomization.h"

#include "Types/CsTypes_Input.h"

#define LOCTEXT_NAMESPACE "ECsInputActionCustomization"


FECsInputActionCustomization::FECsInputActionCustomization()
{
	Init<FECsInputAction, EMCsInputAction>();
}

TSharedRef<IPropertyTypeCustomization> FECsInputActionCustomization::MakeInstance()
{
	return MakeShareable(new FECsInputActionCustomization);
}

void FECsInputActionCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsInputAction>(StructPropertyHandle);
}

void FECsInputActionCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<FECsInputAction, EMCsInputAction>(DisplayName);
}

#undef LOCTEXT_NAMESPACE

// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsGameEventCustomization.h"

#include "Managers/Input/CsTypes_Input.h"

#define LOCTEXT_NAMESPACE "ECsGameEventCustomization"


FECsGameEventCustomization::FECsGameEventCustomization()
{
	Init<FECsGameEvent, EMCsGameEvent>();
}

TSharedRef<IPropertyTypeCustomization> FECsGameEventCustomization::MakeInstance()
{
	return MakeShareable(new FECsGameEventCustomization);
}

void FECsGameEventCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsGameEvent>(StructPropertyHandle);
}

void FECsGameEventCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<FECsGameEvent, EMCsGameEvent>(DisplayName);
}

#undef LOCTEXT_NAMESPACE

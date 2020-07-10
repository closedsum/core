// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/Sound/ECsSoundCustomization.h"

#include "Managers/Sound/CsTypes_Sound.h"

#define LOCTEXT_NAMESPACE "ECsSurfaceCustomization"


FECsSoundCustomization::FECsSoundCustomization() :
	Super()
{
	Init<EMCsSound, FECsSound>();
}

TSharedRef<IPropertyTypeCustomization> FECsSoundCustomization::MakeInstance()
{
	return MakeShareable(new FECsSoundCustomization);
}

void FECsSoundCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsSound>(StructPropertyHandle);
}

void FECsSoundCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EMCsSound, FECsSound>(DisplayName);
}

#undef LOCTEXT_NAMESPACE

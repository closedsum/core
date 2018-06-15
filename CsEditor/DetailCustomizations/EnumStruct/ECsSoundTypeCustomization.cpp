// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsSoundTypeCustomization.h"

#include "Types/CsTypes_Sound.h"

#define LOCTEXT_NAMESPACE "ECsSurfaceTypeCustomization"


FECsSoundTypeCustomization::FECsSoundTypeCustomization()
{
	Init<FECsSoundType, EMCsSoundType>();
}

TSharedRef<IPropertyTypeCustomization> FECsSoundTypeCustomization::MakeInstance()
{
	return MakeShareable(new FECsSoundTypeCustomization);
}

void FECsSoundTypeCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsSoundType>(StructPropertyHandle);
}

void FECsSoundTypeCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<FECsSoundType, EMCsSoundType>(DisplayName);
}

#undef LOCTEXT_NAMESPACE

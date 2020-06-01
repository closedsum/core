// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsSoundTypeCustomization.h"

#include "Types/CsTypes_Sound.h"

#define LOCTEXT_NAMESPACE "ECsSurfaceTypeCustomization"


FECsSoundTypeCustomization::FECsSoundTypeCustomization() :
	Super()
{
	Init<EMCsSoundType, FECsSoundType>();
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
	SetEnumWithDisplayName_Internal<EMCsSoundType, FECsSoundType>(DisplayName);
}

#undef LOCTEXT_NAMESPACE

// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsSurfaceTypeCustomization.h"

#include "Types/CsTypes.h"

#define LOCTEXT_NAMESPACE "ECsSurfaceTypeCustomization"


FECsSurfaceTypeCustomization::FECsSurfaceTypeCustomization()
{
	Init<FECsSurfaceType, EMCsSurfaceType>();
}

TSharedRef<IPropertyTypeCustomization> FECsSurfaceTypeCustomization::MakeInstance()
{
	return MakeShareable(new FECsSurfaceTypeCustomization);
}

void FECsSurfaceTypeCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsSurfaceType>(StructPropertyHandle);
}

void FECsSurfaceTypeCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<FECsSurfaceType, EMCsSurfaceType>(DisplayName);
}

#undef LOCTEXT_NAMESPACE

// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsSurfaceTypeCustomization.h"

#include "Types/CsTypes.h"

#define LOCTEXT_NAMESPACE "ECsSurfaceTypeCustomization"


FECsSurfaceTypeCustomization::FECsSurfaceTypeCustomization() :
	Super()
{
	Init<EMCsSurfaceType, FECsSurfaceType>();
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
	SetEnumWithDisplayName_Internal<EMCsSurfaceType, FECsSurfaceType>(DisplayName);
}

void FECsSurfaceTypeCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EMCsSurfaceType, FECsSurfaceType>(OutDisplayName);
}

#undef LOCTEXT_NAMESPACE

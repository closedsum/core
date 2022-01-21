// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsSurfaceTypeCustomization.h"

#include "Types/CsTypes.h"

#define LOCTEXT_NAMESPACE "ECsSurfaceTypeCustomization"

#define EnumMapType EMCsSurfaceType
#define EnumType FECsSurfaceType

FECsSurfaceTypeCustomization::FECsSurfaceTypeCustomization() :
	Super()
{
	Init<EnumMapType, EnumType>();
}

TSharedRef<IPropertyTypeCustomization> FECsSurfaceTypeCustomization::MakeInstance()
{
	return MakeShareable(new FECsSurfaceTypeCustomization);
}

void FECsSurfaceTypeCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<EnumType>(StructPropertyHandle);
}

void FECsSurfaceTypeCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EnumMapType, EnumType>(DisplayName);
}

void FECsSurfaceTypeCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EnumMapType, EnumType>(OutDisplayName);
}

#undef EnumMapType
#undef EnumType

#undef LOCTEXT_NAMESPACE

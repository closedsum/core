// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/Input/ECsGestureTypeCustomization.h"

#include "Types/CsTypes.h"

#define LOCTEXT_NAMESPACE "ECsGestureTypeCustomization"


FECsGestureTypeCustomization::FECsGestureTypeCustomization() :
	Super()
{
	Init<EMCsGestureType, FECsGestureType>();
}

TSharedRef<IPropertyTypeCustomization> FECsGestureTypeCustomization::MakeInstance()
{
	return MakeShareable(new FECsGestureTypeCustomization);
}

void FECsGestureTypeCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsGestureType>(StructPropertyHandle);
}

void FECsGestureTypeCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EMCsGestureType, FECsGestureType>(DisplayName);
}

void FECsGestureTypeCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EMCsGestureType, FECsGestureType>(OutDisplayName);
}

#undef LOCTEXT_NAMESPACE

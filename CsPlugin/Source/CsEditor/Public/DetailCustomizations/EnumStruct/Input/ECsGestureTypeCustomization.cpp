// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/Input/ECsGestureTypeCustomization.h"

#include "Managers/Gesture/CsTypes_Gesture.h"

#define LOCTEXT_NAMESPACE "ECsGestureTypeCustomization"

#define EnumMapType EMCsGestureType
#define EnumType FECsGestureType

FECsGestureTypeCustomization::FECsGestureTypeCustomization() :
	Super()
{
	Init<EnumMapType, EnumType>();
}

TSharedRef<IPropertyTypeCustomization> FECsGestureTypeCustomization::MakeInstance()
{
	return MakeShareable(new FECsGestureTypeCustomization);
}

void FECsGestureTypeCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<EnumType>(StructPropertyHandle);
}

void FECsGestureTypeCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EnumMapType, EnumType>(DisplayName);
}

void FECsGestureTypeCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EnumMapType, EnumType>(OutDisplayName);
}

#undef EnumMapType
#undef EnumType

#undef LOCTEXT_NAMESPACE

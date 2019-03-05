// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsGestureTypeCustomization.h"

#include "Types/CsTypes.h"

#define LOCTEXT_NAMESPACE "ECsGestureTypeCustomization"


FECsGestureTypeCustomization::FECsGestureTypeCustomization()
{
	Init<FECsGestureType, EMCsGestureType>();
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
	SetEnumWithDisplayName_Internal<FECsGestureType, EMCsGestureType>(DisplayName);
}

#undef LOCTEXT_NAMESPACE

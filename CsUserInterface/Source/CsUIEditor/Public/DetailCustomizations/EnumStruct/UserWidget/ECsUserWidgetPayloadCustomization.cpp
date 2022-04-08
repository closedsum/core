// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/UserWidget/ECsUserWidgetPayloadCustomization.h"

// Managers
#include "Managers/UserWidget/Payload/CsTypes_Payload_UserWidget.h"

#define LOCTEXT_NAMESPACE "ECsUserWidgetPayloadCustomization"

#define EnumMapType EMCsUserWidgetPayload
#define EnumType FECsUserWidgetPayload

FECsUserWidgetPayloadCustomization::FECsUserWidgetPayloadCustomization() :
	Super()
{
	Init<EnumMapType, EnumType>();
}

TSharedRef<IPropertyTypeCustomization> FECsUserWidgetPayloadCustomization::MakeInstance()
{
	return MakeShareable(new FECsUserWidgetPayloadCustomization);
}

void FECsUserWidgetPayloadCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<EnumType>(StructPropertyHandle);
}

void FECsUserWidgetPayloadCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EnumMapType, EnumType>(DisplayName);
}

void FECsUserWidgetPayloadCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EnumMapType, EnumType>(OutDisplayName);
}

#undef EnumMapType
#undef EnumType

#undef LOCTEXT_NAMESPACE
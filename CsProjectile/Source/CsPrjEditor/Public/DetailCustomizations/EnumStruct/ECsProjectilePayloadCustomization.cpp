// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsProjectilePayloadCustomization.h"

// Managers
#include "Payload/CsTypes_Payload_Projectile.h"

#define LOCTEXT_NAMESPACE "ECsProjectilePayloadCustomization"

#define EnumMapType EMCsProjectilePayload
#define EnumType FECsProjectilePayload

FECsProjectilePayloadCustomization::FECsProjectilePayloadCustomization() :
	Super()
{
	Init<EnumMapType, EnumType>();
}

TSharedRef<IPropertyTypeCustomization> FECsProjectilePayloadCustomization::MakeInstance()
{
	return MakeShareable(new FECsProjectilePayloadCustomization);
}

void FECsProjectilePayloadCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<EnumType>(StructPropertyHandle);
}

void FECsProjectilePayloadCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EnumMapType, EnumType>(DisplayName);
}

void FECsProjectilePayloadCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EnumMapType, EnumType>(OutDisplayName);
}

#undef EnumMapType
#undef EnumType

#undef LOCTEXT_NAMESPACE
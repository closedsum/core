// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsProjectilePayloadCustomization.h"

// Managers
#include "Payload/CsTypes_Payload_Projectile.h"

#define LOCTEXT_NAMESPACE "ECsProjectilePayloadCustomization"

FECsProjectilePayloadCustomization::FECsProjectilePayloadCustomization() :
	Super()
{
	Init<EMCsProjectilePayload, FECsProjectilePayload>();
}

TSharedRef<IPropertyTypeCustomization> FECsProjectilePayloadCustomization::MakeInstance()
{
	return MakeShareable(new FECsProjectilePayloadCustomization);
}

void FECsProjectilePayloadCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsProjectilePayload>(StructPropertyHandle);
}

void FECsProjectilePayloadCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EMCsProjectilePayload, FECsProjectilePayload>(DisplayName);
}

void FECsProjectilePayloadCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EMCsProjectilePayload, FECsProjectilePayload>(OutDisplayName);
}

#undef LOCTEXT_NAMESPACE
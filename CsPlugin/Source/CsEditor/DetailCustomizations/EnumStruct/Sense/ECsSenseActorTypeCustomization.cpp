// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/Sense/ECsSenseActorTypeCustomization.h"

#include "Managers/Sense/CsTypes_Sense.h"

#define LOCTEXT_NAMESPACE "ECsAssetTypeCustomization"


FECsSenseActorTypeCustomization::FECsSenseActorTypeCustomization() :
	Super()
{
	Init<EMCsSenseActorType, FECsSenseActorType>();
}

TSharedRef<IPropertyTypeCustomization> FECsSenseActorTypeCustomization::MakeInstance()
{
	return MakeShareable(new FECsSenseActorTypeCustomization);
}

void FECsSenseActorTypeCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsSenseActorType>(StructPropertyHandle);
}

void FECsSenseActorTypeCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EMCsSenseActorType, FECsSenseActorType>(DisplayName);
}

void FECsSenseActorTypeCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EMCsSenseActorType, FECsSenseActorType>(OutDisplayName);
}

#undef LOCTEXT_NAMESPACE

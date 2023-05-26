// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/Sense/ECsSenseActorTypeCustomization.h"

#include "Managers/Sense/CsTypes_Sense.h"

#define LOCTEXT_NAMESPACE "ECsAssetTypeCustomization"

#define EnumMapType EMCsSenseActorType
#define EnumType FECsSenseActorType

FECsSenseActorTypeCustomization::FECsSenseActorTypeCustomization() :
	Super()
{
	Init<EnumMapType, EnumType>();
}

TSharedRef<IPropertyTypeCustomization> FECsSenseActorTypeCustomization::MakeInstance()
{
	return MakeShareable(new FECsSenseActorTypeCustomization);
}

void FECsSenseActorTypeCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<EnumType>(StructPropertyHandle);
}

void FECsSenseActorTypeCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EnumMapType, EnumType>(DisplayName);
}

void FECsSenseActorTypeCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EnumMapType, EnumType>(OutDisplayName);
}

#undef EnumMapType
#undef EnumType

#undef LOCTEXT_NAMESPACE

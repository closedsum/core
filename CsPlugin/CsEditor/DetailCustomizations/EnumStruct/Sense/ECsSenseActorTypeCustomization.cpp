// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/Sense/ECsSenseActorTypeCustomization.h"

#include "Types/CsTypes_Sense.h"

#define LOCTEXT_NAMESPACE "ECsAssetTypeCustomization"


FECsSenseActorTypeCustomization::FECsSenseActorTypeCustomization()
{
	Init<FECsSenseActorType, EMCsSenseActorType>();
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
	SetEnumWithDisplayName_Internal<FECsSenseActorType, EMCsSenseActorType>(DisplayName);
}

#undef LOCTEXT_NAMESPACE

// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/Damage/ECsDamageTypeCustomization.h"

#include "Managers/Damage/CsTypes_Damage.h"

#define LOCTEXT_NAMESPACE "ECsDamageTypeCustomization"


FECsDamageTypeCustomization::FECsDamageTypeCustomization() :
	Super()
{
	Init<EMCsDamageType, FECsDamageType>();
}

TSharedRef<IPropertyTypeCustomization> FECsDamageTypeCustomization::MakeInstance()
{
	return MakeShareable(new FECsDamageTypeCustomization);
}

void FECsDamageTypeCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsDamageType>(StructPropertyHandle);
}

void FECsDamageTypeCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EMCsDamageType, FECsDamageType>(DisplayName);
}

#undef LOCTEXT_NAMESPACE

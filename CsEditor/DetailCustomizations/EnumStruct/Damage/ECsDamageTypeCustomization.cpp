// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/Damage/ECsDamageTypeCustomization.h"

#include "Types/CsTypes_Damage.h"

#define LOCTEXT_NAMESPACE "ECsDamageTypeCustomization"


FECsDamageTypeCustomization::FECsDamageTypeCustomization()
{
	Init<FECsDamageType, EMCsDamageType>();
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
	SetEnumWithDisplayName_Internal<FECsDamageType, EMCsDamageType>(DisplayName);
}

#undef LOCTEXT_NAMESPACE

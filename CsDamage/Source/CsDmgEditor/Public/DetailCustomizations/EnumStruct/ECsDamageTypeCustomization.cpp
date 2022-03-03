// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsDamageTypeCustomization.h"

#include "Types/CsTypes_Damage.h"

#define LOCTEXT_NAMESPACE "ECsDamageTypeCustomization"

#define EnumMapType EMCsDamageType
#define EnumType FECsDamageType

FECsDamageTypeCustomization::FECsDamageTypeCustomization() :
	Super()
{
	Init<EnumMapType, EnumType>();
}

TSharedRef<IPropertyTypeCustomization> FECsDamageTypeCustomization::MakeInstance()
{
	return MakeShareable(new FECsDamageTypeCustomization);
}

void FECsDamageTypeCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<EnumType>(StructPropertyHandle);
}

void FECsDamageTypeCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EnumMapType, EnumType>(DisplayName);
}

void FECsDamageTypeCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EnumMapType, EnumType>(OutDisplayName);
}

#undef EnumMapType
#undef EnumType

#undef LOCTEXT_NAMESPACE

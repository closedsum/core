// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/Interactive/ECsInteractiveTypeCustomization.h"

#include "Types/CsTypes_Interactive.h"

#define LOCTEXT_NAMESPACE "ECsDamageTypeCustomization"


FECsInteractiveTypeCustomization::FECsInteractiveTypeCustomization()
{
	Init<EMCsInteractiveType, FECsInteractiveType>();
}

TSharedRef<IPropertyTypeCustomization> FECsInteractiveTypeCustomization::MakeInstance()
{
	return MakeShareable(new FECsInteractiveTypeCustomization);
}

void FECsInteractiveTypeCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsInteractiveType>(StructPropertyHandle);
}

void FECsInteractiveTypeCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EMCsInteractiveType, FECsInteractiveType>(DisplayName);
}

#undef LOCTEXT_NAMESPACE

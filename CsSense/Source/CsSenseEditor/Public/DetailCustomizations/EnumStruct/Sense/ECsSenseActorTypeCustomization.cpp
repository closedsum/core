// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "DetailCustomizations/EnumStruct/Sense/ECsSenseActorTypeCustomization.h"

#include "Types/CsTypes_Sense.h"

#define LOCTEXT_NAMESPACE "ECsSenseActorTypeCustomization"

#define CLASSTYPE FECsSenseActorTypeCustomization
#define EnumMapType EMCsSenseActorType
#define EnumType FECsSenseActorType

CLASSTYPE::CLASSTYPE() :
	Super()
{
	Init<EnumMapType, EnumType>();
}

TSharedRef<IPropertyTypeCustomization> CLASSTYPE::MakeInstance()
{
	return MakeShareable(new CLASSTYPE);
}

void CLASSTYPE::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<EnumType>(StructPropertyHandle);
}

void CLASSTYPE::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EnumMapType, EnumType>(DisplayName);
}

void CLASSTYPE::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EnumMapType, EnumType>(OutDisplayName);
}

#undef CLASSTYPE
#undef EnumMapType
#undef EnumType

#undef LOCTEXT_NAMESPACE

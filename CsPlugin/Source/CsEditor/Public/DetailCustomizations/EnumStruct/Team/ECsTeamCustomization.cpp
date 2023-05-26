// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/Team/ECsTeamCustomization.h"

// Types
#include "Team/CsTypes_Team.h"

#define LOCTEXT_NAMESPACE "ECsTeamCustomization"

#define EnumMapType EMCsTeam
#define EnumType FECsTeam

FECsTeamCustomization::FECsTeamCustomization() :
	Super()
{
	Init<EnumMapType, EnumType>();
}

TSharedRef<IPropertyTypeCustomization> FECsTeamCustomization::MakeInstance()
{
	return MakeShareable(new FECsTeamCustomization);
}

void FECsTeamCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<EnumType>(StructPropertyHandle);
}

void FECsTeamCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EnumMapType, EnumType>(DisplayName);
}

void FECsTeamCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EnumMapType, EnumType>(OutDisplayName);
}

#undef EnumMapType
#undef EnumType

#undef LOCTEXT_NAMESPACE

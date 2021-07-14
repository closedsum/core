// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/Team/ECsTeamCustomization.h"

// Types
#include "Team/CsTypes_Team.h"

#define LOCTEXT_NAMESPACE "ECsTeamCustomization"


FECsTeamCustomization::FECsTeamCustomization() :
	Super()
{
	Init<EMCsTeam, FECsTeam>();
}

TSharedRef<IPropertyTypeCustomization> FECsTeamCustomization::MakeInstance()
{
	return MakeShareable(new FECsTeamCustomization);
}

void FECsTeamCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsTeam>(StructPropertyHandle);
}

void FECsTeamCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EMCsTeam, FECsTeam>(DisplayName);
}

void FECsTeamCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EMCsTeam, FECsTeam>(OutDisplayName);
}

#undef LOCTEXT_NAMESPACE

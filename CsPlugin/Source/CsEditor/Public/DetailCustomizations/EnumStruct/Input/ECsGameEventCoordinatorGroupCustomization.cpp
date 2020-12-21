// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/Input/ECsGameEventCoordinatorGroupCustomization.h"

#include "Coordinators/GameEvent/CsTypes_Coordinator_GameEvent.h"

#define LOCTEXT_NAMESPACE "ECsGameEventCoordinatorGroupCustomization"

FECsGameEventCoordinatorGroupCustomization::FECsGameEventCoordinatorGroupCustomization() :
	Super()
{
	Init<EMCsGameEventCoordinatorGroup, FECsGameEventCoordinatorGroup>();
}

TSharedRef<IPropertyTypeCustomization> FECsGameEventCoordinatorGroupCustomization::MakeInstance()
{
	return MakeShareable(new FECsGameEventCoordinatorGroupCustomization);
}

void FECsGameEventCoordinatorGroupCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsGameEventCoordinatorGroup>(StructPropertyHandle);
}

void FECsGameEventCoordinatorGroupCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EMCsGameEventCoordinatorGroup, FECsGameEventCoordinatorGroup>(DisplayName);
}

void FECsGameEventCoordinatorGroupCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EMCsGameEventCoordinatorGroup, FECsGameEventCoordinatorGroup>(OutDisplayName);
}

#undef LOCTEXT_NAMESPACE

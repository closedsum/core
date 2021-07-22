// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/Input/ECsGameEventCoordinatorGroupCustomization.h"

#include "Coordinators/GameEvent/CsTypes_Coordinator_GameEvent.h"

#define LOCTEXT_NAMESPACE "ECsGameEventCoordinatorGroupCustomization"

#define EnumMapType EMCsGameEventCoordinatorGroup
#define EnumType FECsGameEventCoordinatorGroup

FECsGameEventCoordinatorGroupCustomization::FECsGameEventCoordinatorGroupCustomization() :
	Super()
{
	Init<EnumMapType, EnumType>();
}

TSharedRef<IPropertyTypeCustomization> FECsGameEventCoordinatorGroupCustomization::MakeInstance()
{
	return MakeShareable(new FECsGameEventCoordinatorGroupCustomization);
}

void FECsGameEventCoordinatorGroupCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<EnumType>(StructPropertyHandle);
}

void FECsGameEventCoordinatorGroupCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EnumMapType, EnumType>(DisplayName);
}

void FECsGameEventCoordinatorGroupCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EnumMapType, EnumType>(OutDisplayName);
}

#undef EnumMapType
#undef EnumType

#undef LOCTEXT_NAMESPACE

// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsTdCreepCustomization.h"

// Types
#include "Managers/Creep/CsTdTypes_Creep.h"

#define LOCTEXT_NAMESPACE "ECsTdCreepCustomization"


FECsTdCreepCustomization::FECsTdCreepCustomization()
{
	Init<FECsTdCreep, EMCsTdCreep>();
}

TSharedRef<IPropertyTypeCustomization> FECsTdCreepCustomization::MakeInstance()
{
	return MakeShareable(new FECsTdCreepCustomization);
}

void FECsTdCreepCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsTdCreep>(StructPropertyHandle);
}

void FECsTdCreepCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<FECsTdCreep, EMCsTdCreep>(DisplayName);
}

#undef LOCTEXT_NAMESPACE

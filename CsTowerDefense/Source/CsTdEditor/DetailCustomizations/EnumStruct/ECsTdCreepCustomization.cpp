// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsTdCreepCustomization.h"
#include "CsTdEditor.h"

// Types
#include "Managers/Creep/CsTdTypes_Creep.h"
// Settings
#include "Settings/CsTdSettings.h"

#define LOCTEXT_NAMESPACE "ECsTdCreepCustomization"

FECsTdCreepCustomization::FECsTdCreepCustomization() :
	Super()
{
	Init<EMCsTdCreep, FECsTdCreep>();
}

void FECsTdCreepCustomization::PopulateEnumMapFromSettings()
{
	PopulateEnumMapFromSettings_Internal<UCsTdSettings, EMCsTdCreep, FECsTdCreep>(TEXT("FECsTdCreepCustomization::PopulateEnumMapFromSettings"));
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
	SetEnumWithDisplayName_Internal<EMCsTdCreep, FECsTdCreep>(DisplayName);
}

#undef LOCTEXT_NAMESPACE

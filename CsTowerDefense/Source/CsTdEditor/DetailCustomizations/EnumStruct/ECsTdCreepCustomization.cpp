// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsTdCreepCustomization.h"
#include "CsTdEditor.h"

// Types
#include "Managers/Creep/CsTdTypes_Creep.h"
// Settings
#include "Settings/CsTdSettings.h"

#define LOCTEXT_NAMESPACE "ECsTdCreepCustomization"

FECsTdCreepCustomization::FECsTdCreepCustomization()
{
	Init<FECsTdCreep, EMCsTdCreep>();
}

void FECsTdCreepCustomization::PopulateEnumMapFromSettings()
{
	PopulateEnumMapFromSettings_Internal<UCsTdSettings, EMCsTdCreep, FECsTdCreep>(TEXT("FECsTdCreepCustomization::PopulateEnumMapFromSettings"));

	/*
	if (UCsTdSettings* Settings = GetMutableDefault<UCsTdSettings>())
	{
		const TArray<FCsSettings_Enum>& Enums = Settings->ECsTdCreep;

		if (Enums.Num() > CS_EMPTY)
		{
			EMCsTdCreep::Get().ClearUserDefinedEnums();

			for (const FCsSettings_Enum& Enum : Enums)
			{
				if (Enum.Name.IsEmpty())
				{
					UE_LOG(LogCsTdEditor, Warning, TEXT("FECsTdCreepCustomization::PopulateEnumMapFromSettings: Empty Enum listed in UCsTdSettings::ECsTdCreep."));
					continue;
				}
				
				if (Enum.DisplayName.IsEmpty())
				{
					if (!EMCsTdCreep::Get().CreateSafe(Enum.Name, true))
					{
						UE_LOG(LogCsTdEditor, Warning, TEXT("FECsTdCreepCustomization::PopulateEnumMapFromSettings: Enum: %s listed in UCsTdSettings::ECsTdCreep already exists."), *(Enum.Name));
					}
				}
				else
				{
					if (!EMCsTdCreep::Get().CreateSafe(Enum.Name, Enum.DisplayName, true))
					{
						UE_LOG(LogCsTdEditor, Warning, TEXT("FECsTdCreepCustomization::PopulateEnumMapFromSettings: Enum: %s listed in UCsTdSettings::ECsTdCreep already exists."), *(Enum.Name));
					}
				}
			}
		}
	}
	else
	{
		UE_LOG(LogCsTdEditor, Warning, TEXT("FECsTdCreepCustomization::PopulateEnumMapFromSettings: Failed to find settings of Type: UCsTdSettings."));
	}
	*/
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

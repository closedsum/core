// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Beam.h"
#include "CsBeam.h"

// Library
	// Settings
#include "Settings/CsLibrary_BeamSettings.h"
// Data
#include "Data/CsBeamGetDataRootSet.h"
// Utility
#include "Utility/CsPopulateEnumMapFromSettings.h"
#include "Utility/CsBeamPopulateEnumMapFromSettings.h"
#include "Utility/CsBeamLog.h"

// Beam
#pragma region

namespace NCsBeam
{
	namespace NCached
	{
		namespace Str
		{
			const FString Beam = TEXT("Beam");
		}
	}

	void FromEnumSettings(const FString& Context)
	{
		using namespace NCsBeam::NCached;

		typedef NCsBeam::NSettings::FLibrary SettingsLibrary;
		typedef NCsEnum::NSettings::FLibrary EnumSettingsLibrary;
		typedef NCsEnum::NSettings::FLibrary::FPopulate::FPayload PayloadType;

		PayloadType Payload;
		Payload.Enums					 = SettingsLibrary::GetSettingsEnum_Beam();
		Payload.EnumSettingsPath		 = SettingsLibrary::GetSettingsEnumPath_Beam();
		Payload.EnumName				 = Str::Beam;
		Payload.Create					 = &Create;
		Payload.CreateCustom			 = &CreateCustom;
		Payload.IsValidEnum				 = &IsValidEnum;
		Payload.IsValidEnumByDisplayName = &IsValidEnumByDisplayName;
		Payload.Log						 = &NCsBeam::FLog::Warning;

		EnumSettingsLibrary::Populate(Context, Payload);
	}

	void FromDataTable(const FString& Context, UObject* ContextRoot)
	{
		const FCsBeamDataRootSet* DataRootSet = FCsBeamPopulateEnumMapFromSettings::GetDataRootSet(Context, ContextRoot);

		if (!DataRootSet)
			return;
		/*
		for (const FCsBeamSettings_DataTable_Beams& Beams : DataRootSet->Beams)
		{
			FCsPopulateEnumMapFromSettings::FromDataTable<EMCsBeam>(Context, ContextRoot, Beams.Beams, Str::Beam, &NCsBeam::FLog::Warning);
		}
		*/
	}

	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		typedef NCsBeam::NSettings::FLibrary SettingsLibrary;

		EMCsBeam::Get().ClearUserDefinedEnums();

		// Enum Settings
		if (SettingsLibrary::Get_ECsBeam_PopulateEnumMapMethod() == ECsPopulateEnumMapMethod::EnumSettings)
		{
			FromEnumSettings(Context);
		}

		// DataTable
		if (SettingsLibrary::Get_ECsBeam_PopulateEnumMapMethod() == ECsPopulateEnumMapMethod::DataTable)
		{
			FromDataTable(Context, ContextRoot);
		}
	}
}

#pragma endregion Beam

// BeamClass
#pragma region

namespace NCsBeamClass
{
	namespace NCached
	{
		namespace Str
		{
			const FString BeamClass = TEXT("BeamClass");
		}
	}

	void FromEnumSettings(const FString& Context)
	{
		using namespace NCsBeamClass::NCached;

		typedef NCsBeam::NSettings::FLibrary SettingsLibrary;
		typedef NCsEnum::NSettings::FLibrary EnumSettingsLibrary;
		typedef NCsEnum::NSettings::FLibrary::FPopulate::FPayload PayloadType;

		PayloadType Payload;
		Payload.Enums					 = SettingsLibrary::GetSettingsEnum_BeamClass();
		Payload.EnumSettingsPath		 = SettingsLibrary::GetSettingsEnumPath_BeamClass();
		Payload.EnumName				 = Str::BeamClass;
		Payload.Create					 = &Create;
		Payload.CreateCustom			 = &CreateCustom;
		Payload.IsValidEnum				 = &IsValidEnum;
		Payload.IsValidEnumByDisplayName = &IsValidEnumByDisplayName;
		Payload.Log						 = &NCsBeam::FLog::Warning;

		EnumSettingsLibrary::Populate(Context, Payload);
	}

	void FromDataTable(const FString& Context, UObject* ContextRoot)
	{
		const FCsBeamDataRootSet* DataRootSet = FCsBeamPopulateEnumMapFromSettings::GetDataRootSet(Context, ContextRoot);

		if (!DataRootSet)
			return;

		FCsPopulateEnumMapFromSettings::FromDataTable<EMCsBeamClass>(Context, ContextRoot, DataRootSet->BeamClasses, NCached::Str::BeamClass, &NCsBeam::FLog::Warning);
	}

	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		typedef NCsBeam::NSettings::FLibrary SettingsLibrary;

		EMCsBeamClass::Get().ClearUserDefinedEnums();

		// Enum Settings
		if (SettingsLibrary::Get_ECsBeamClass_PopulateEnumMapMethod() == ECsPopulateEnumMapMethod::EnumSettings)
		{
			FromEnumSettings(Context);
		}

		// DataTable
		if (SettingsLibrary::Get_ECsBeamClass_PopulateEnumMapMethod() == ECsPopulateEnumMapMethod::DataTable)
		{
			FromDataTable(Context, ContextRoot);
		}
	}
}

#pragma endregion BeamClass
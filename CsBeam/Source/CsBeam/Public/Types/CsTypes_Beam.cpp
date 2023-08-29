// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Beam.h"
#include "CsBeam.h"

// Data
#include "Data/CsBeamGetDataRootSet.h"
// Settings
#include "Settings/CsBeamSettings.h"
// Utility
#include "Utility/CsBeamLog.h"
#include "Utility/CsPopulateEnumMapFromSettings.h"
#include "Utility/CsBeamPopulateEnumMapFromSettings.h"

// Beam
#pragma region

namespace NCsBeam
{
	namespace Str
	{
		const FString Beam = TEXT("Beam");
	}

	void FromEnumSettings(const FString& Context)
	{
		FCsPopulateEnumMapFromSettings::FromEnumSettings<UCsBeamSettings, EMCsBeam, FECsBeam>(Context, Str::Beam, &NCsBeam::FLog::Warning);
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
		UCsBeamSettings* ModuleSettings = GetMutableDefault<UCsBeamSettings>();

		checkf(ModuleSettings, TEXT("%s: Failed to find settings of type: UCsBeamSettings."), *Context);

		EMCsBeam::Get().ClearUserDefinedEnums();

		// Enum Settings
		if (ModuleSettings->ECsBeam_PopulateEnumMapMethod == ECsPopulateEnumMapMethod::EnumSettings)
		{
			FromEnumSettings(Context);
		}

		// DataTable
		if (ModuleSettings->ECsBeam_PopulateEnumMapMethod == ECsPopulateEnumMapMethod::DataTable)
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
	namespace Str
	{
		const FString BeamClass = TEXT("BeamClass");
	}

	void FromEnumSettings(const FString& Context)
	{
		FCsPopulateEnumMapFromSettings::FromEnumSettings<UCsBeamSettings, EMCsBeamClass, FECsBeamClass>(Context, Str::BeamClass, &NCsBeam::FLog::Warning);
	}

	void FromDataTable(const FString& Context, UObject* ContextRoot)
	{
		const FCsBeamDataRootSet* DataRootSet = FCsBeamPopulateEnumMapFromSettings::GetDataRootSet(Context, ContextRoot);

		if (!DataRootSet)
			return;

		FCsPopulateEnumMapFromSettings::FromDataTable<EMCsBeamClass>(Context, ContextRoot, DataRootSet->BeamClasses, Str::BeamClass, &NCsBeam::FLog::Warning);
	}

	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		UCsBeamSettings* ModuleSettings = GetMutableDefault<UCsBeamSettings>();

		checkf(ModuleSettings, TEXT("%s: Failed to find settings of type: UCsBeamSettings."), *Context);

		EMCsBeamClass::Get().ClearUserDefinedEnums();

		// Enum Settings
		if (ModuleSettings->ECsBeamClass_PopulateEnumMapMethod == ECsPopulateEnumMapMethod::EnumSettings)
		{
			FromEnumSettings(Context);
		}

		// DataTable
		if (ModuleSettings->ECsBeamClass_PopulateEnumMapMethod == ECsPopulateEnumMapMethod::DataTable)
		{
			FromDataTable(Context, ContextRoot);
		}
	}
}

#pragma endregion BeamClass
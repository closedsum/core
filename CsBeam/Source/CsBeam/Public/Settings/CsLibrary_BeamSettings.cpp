// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Settings/CsLibrary_BeamSettings.h"
#include "CsBeam.h"

// Settings
#include "Settings/CsBeamSettings.h"

namespace NCsBeam
{
	namespace NSettings
	{
		UCsBeamSettings* FLibrary::Get() { return GetMutableDefault<UCsBeamSettings>(); }

		// Enum
		#pragma region

		const ECsPopulateEnumMapMethod& FLibrary::Get_ECsBeam_PopulateEnumMapMethod() { return Get()->ECsBeam_PopulateEnumMapMethod; }
		const TArray<FCsSettings_Enum>& FLibrary::GetSettingsEnum_Beam()			{ return Get()->GetSettingsEnum<FECsBeam>(); }
		const FString& FLibrary::GetSettingsEnumPath_Beam()							{ return NCsBeamSettings::NCached::Str::Beam; }
		const ECsPopulateEnumMapMethod& FLibrary::Get_ECsBeamClass_PopulateEnumMapMethod() { return Get()->ECsBeamClass_PopulateEnumMapMethod; }
		const TArray<FCsSettings_Enum>& FLibrary::GetSettingsEnum_BeamClass()		{ return Get()->GetSettingsEnum<FECsBeamClass>(); }
		const FString& FLibrary::GetSettingsEnumPath_BeamClass()					{ return NCsBeamSettings::NCached::Str::BeamClass; }

		#pragma endregion Enum
	}
}
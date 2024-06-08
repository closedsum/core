
// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Settings/CsLibrary_InputSettings.h"

// Settings
#include "Settings/CsInputSettings.h"

namespace NCsInput
{
	namespace NSettings
	{
		UCsInputSettings* FLibrary::Get() { return GetMutableDefault<UCsInputSettings>(); }

		// Input
		#pragma region

		const TArray<FCsSettings_Enum>& FLibrary::GetSettingsEnum_InputActionMap()	{ return Get()->GetSettingsEnum<FECsInputActionMap>(); }
		const FString& FLibrary::GetSettingsEnumPath_InputActionMap()				{ return NCsInputSettings::NCached::Str::InputActionMap; }
		const TArray<FCsSettings_Enum>& FLibrary::GetSettingsEnum_GameEvent()		{ return Get()->GetSettingsEnum<FECsGameEvent>(); }
		const FString& FLibrary::GetSettingsEnumPath_GameEvent()					{ return NCsInputSettings::NCached::Str::GameEvent; }

		#pragma endregion Input
	}
}
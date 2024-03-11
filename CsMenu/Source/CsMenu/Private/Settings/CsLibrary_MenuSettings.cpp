// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Settings/CsLibrary_MenuSettings.h"
#include "CsMenu.h"

// Settings
#include "Settings/CsMenuSettings.h"

namespace NCsMenu
{
	namespace NSettings
	{
		UCsMenuSettings* FLibrary::Get() { return GetMutableDefault<UCsMenuSettings>(); }
		
		// MenuEvent
        #pragma region

        const ECsPopulateEnumMapMethod& FLibrary::Get_ECsMenuEvent_PopulateEnumMapMethod() { return Get()->ECsMenuEvent_PopulateEnumMapMethod; }
        const TArray<FCsSettings_Enum>& FLibrary::GetSettingsEnum_MenuEvent()                { return Get()->GetSettingsEnum<FECsMenuEvent>(); }
        const FString& FLibrary::GetSettingsEnumPath_MenuEvent()                            { return NCsMenuSettings::NCached::Str::MenuEvent; }

        #pragma endregion MenuEvent
	}
}
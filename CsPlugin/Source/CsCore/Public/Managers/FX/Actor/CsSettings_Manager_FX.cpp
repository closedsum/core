// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/FX/Actor/CsSettings_Manager_FX.h"

// Settings
#include "Settings/CsDeveloperSettings.h"

// FCsSettings_Manager_FX
#pragma region

const FCsSettings_Manager_FX& FCsSettings_Manager_FX::GetChecked(const FString& Context)
{
	UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>();

	checkf(Settings, TEXT("%s: Failed to get settings of type: UCsDeveloperSettings."), *Context);

	return Settings->Manager_FX;
}

#pragma endregion FCsSettings_Manager_FX
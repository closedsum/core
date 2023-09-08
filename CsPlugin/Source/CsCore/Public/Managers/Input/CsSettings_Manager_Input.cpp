// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Input/CsSettings_Manager_Input.h"

// Settings
#include "Settings/CsDeveloperSettings.h"

// FCsSettings_Manager_Input
#pragma region

const FCsSettings_Manager_Input& FCsSettings_Manager_Input::Get()
{
	return GetMutableDefault<UCsDeveloperSettings>()->Manager_Input;
}

#pragma endregion FCsSettings_Manager_Input
// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Runnable/CsSettings_Manager_Runnable.h"

// Settings
#include "Settings/CsDeveloperSettings.h"

// FCsSettings_Manager_Runnable
#pragma region

const FCsSettings_Manager_Runnable& FCsSettings_Manager_Runnable::Get()
{
	return GetMutableDefault<UCsDeveloperSettings>()->Manager_Runnable;
}

#pragma endregion FCsSettings_Manager_Runnable
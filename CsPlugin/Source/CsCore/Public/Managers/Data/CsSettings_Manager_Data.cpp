// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Data/CsSettings_Manager_Data.h"

// Settings
#include "Settings/CsDeveloperSettings.h"

// FCsSettings_Manager_Data
#pragma region

/*static*/ const FCsSettings_Manager_Data& FCsSettings_Manager_Data::Get()
{
	return GetMutableDefault<UCsDeveloperSettings>()->Manager_Data;
}
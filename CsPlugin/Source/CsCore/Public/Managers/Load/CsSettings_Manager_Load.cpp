// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Load/CsSettings_Manager_Load.h"

// Settings
#include "Settings/CsDeveloperSettings.h"

// FCsSettings_Manager_Load
#pragma region

const FCsSettings_Manager_Load& FCsSettings_Manager_Load::Get()
{
	return GetMutableDefault<UCsDeveloperSettings>()->Manager_Load;
}

#pragma endregion FCsSettings_Manager_Load
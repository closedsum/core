// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Load/CsSettings_Manager_Load.h"

// Settings
#include "Settings/CsDeveloperSettings.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsSettings_Manager_Load)

// FCsSettings_Manager_Load
#pragma region

const FCsSettings_Manager_Load& FCsSettings_Manager_Load::Get()
{
	return GetMutableDefault<UCsDeveloperSettings>()->Manager_Load;
}

#pragma endregion FCsSettings_Manager_Load
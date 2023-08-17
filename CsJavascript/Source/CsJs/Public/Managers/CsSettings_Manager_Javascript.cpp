// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/CsSettings_Manager_Javascript.h"

// Settings
#include "Settings/CsJsSettings.h"

// FCsSettings_Manager_Javascript
#pragma region

/*static*/ const FCsSettings_Manager_Javascript& FCsSettings_Manager_Javascript::Get()
{
	return GetMutableDefault<UCsJsSettings>()->Manager_Javascript;
}

#pragma endregion FCsSettings_Manager_Javascript
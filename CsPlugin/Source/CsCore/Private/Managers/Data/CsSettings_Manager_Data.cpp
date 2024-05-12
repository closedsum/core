// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Data/CsSettings_Manager_Data.h"

// Settings
#include "Settings/CsDeveloperSettings.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsSettings_Manager_Data)

// FCsSettings_Manager_Data
#pragma region

/*static*/ const FCsSettings_Manager_Data& FCsSettings_Manager_Data::Get()
{
	return GetMutableDefault<UCsDeveloperSettings>()->Manager_Data;
}

#pragma endregion FCsSettings_Manager_Data
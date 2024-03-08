// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
// Types
#include "Settings/CsSettings_Damage.h"

// Settings
#include "Settings/CsDamageSettings.h"

// FCsSettings_Damage_Debug
#pragma region

const FCsSettings_Damage_Debug& FCsSettings_Damage_Debug::Get()
{
	return FCsSettings_Damage::Get().Debug;
}

#pragma endregion FCsSettings_Damage_Debug

// FCsSettings_Damage
#pragma region

const FCsSettings_Damage& FCsSettings_Damage::Get()
{
	return GetMutableDefault<UCsDamageSettings>()->Damage;
}

#pragma endregion FCsSettings_Damage
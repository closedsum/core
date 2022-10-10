// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/CsSettings_Manager_Damage.h"

// Settings
#include "Settings/CsDamageSettings.h"

// FCsSettings_Manager_Damage_Modifier
#pragma region

const FCsSettings_Manager_Damage_Modifier& FCsSettings_Manager_Damage_Modifier::Get()
{
	return FCsSettings_Manager_Damage::Get().Modifier;
}

#pragma endregion FCsSettings_Manager_Damage_Modifier

// FCsSettings_Manager_Damage
#pragma region

const FCsSettings_Manager_Damage& FCsSettings_Manager_Damage::Get()
{
	return GetMutableDefault<UCsDamageSettings>()->Manager_Damage;
}

#pragma endregion FCsSettings_Manager_Damage
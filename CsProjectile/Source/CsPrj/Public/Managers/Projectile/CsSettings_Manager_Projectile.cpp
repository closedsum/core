// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Projectile/CsSettings_Manager_Projectile.h"

// Settings
#include "Settings/CsProjectileSettings.h"

// FCsSettings_Manager_Projectile
#pragma region

const FCsSettings_Manager_Projectile& FCsSettings_Manager_Projectile::Get()
{
	return GetMutableDefault<UCsProjectileSettings>()->Manager_Projectile;
}

#pragma endregion FCsSettings_Manager_Projectile
// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Settings/CsTypes_ProjectileSettings.h"

// Settings
#include "Settings/CsProjectileSettings.h"

// FCsSettings_Projectile_Debug
#pragma region

const FCsSettings_Projectile_Debug& FCsSettings_Projectile_Debug::Get()
{
	return FCsSettings_Projectile::Get().Debug;
}

#pragma endregion FCsSettings_Projectile_Debug

// FCsSettings_Projectile
#pragma region

const FCsSettings_Projectile& FCsSettings_Projectile::Get()
{
	return GetMutableDefault<UCsProjectileSettings>()->Projectile;
}

#pragma endregion FCsSettings_Projectile
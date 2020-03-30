// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Weapon/CsCVars_Weapon.h"

TAutoConsoleVariable<int32> CsCVarDrawWeaponFireProjectile(
	TEXT("draw.weapon.fireprojectile"),
	0,
	TEXT("Draw Projectile destinations from Weapon."),
	ECVF_SetByConsole
);

// CVarLog
#pragma region

namespace NCsCVarLog
{
	// Weapon
	namespace Map
	{
	}
}

#pragma endregion CVarLog
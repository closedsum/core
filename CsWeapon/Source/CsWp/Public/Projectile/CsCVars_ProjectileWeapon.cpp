// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Projectile/CsCVars_ProjectileWeapon.h"

TAutoConsoleVariable<int32> CsCVarLogWeaponProjectileState(
	TEXT("log.weapon.projecitle.state"),
	0,
	TEXT("Log ProjectileWeapon Current State"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogWeaponProjectileStateTransition(
	TEXT("log.weapon.projecitle.state.transition"),
	0,
	TEXT("Log ProjectileWeapon State Transition"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogWeaponProjectileCanFire(
	TEXT("log.weapon.projecitle.canfire"),
	0,
	TEXT("Log ProjectileWeapon CanFire()."),
	ECVF_SetByConsole
);

// CVarLog
#pragma region

namespace NCsCVarLog
{
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogWeaponProjectileState, "Log ProjectileWeapon Current State");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogWeaponProjectileStateTransition, "Log ProjectileWeapon State Transition");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogWeaponProjectileCanFire, "Log ProjectileWeapon CanFire()");

	namespace Map
	{
		CSWP_API CS_ADD_TO_CVAR_MAP(LogWeaponProjectileState, CsCVarLogWeaponProjectileState);
		CSWP_API CS_ADD_TO_CVAR_MAP(LogWeaponProjectileStateTransition, CsCVarLogWeaponProjectileStateTransition);
		CSWP_API CS_ADD_TO_CVAR_MAP(LogWeaponProjectileCanFire, CsCVarLogWeaponProjectileCanFire);
	}
}

#pragma endregion CVarLog
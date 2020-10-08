// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Projectile/CsCVars_ProjectileWeapon.h"

TAutoConsoleVariable<int32> CsCVarLogWeaponProjectileState(
	TEXT("log.weapon.projectile.state"),
	0,
	TEXT("Log ProjectileWeapon Current State"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogWeaponProjectileStateTransition(
	TEXT("log.weapon.projectile.state.transition"),
	0,
	TEXT("Log ProjectileWeapon State Transition"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogWeaponProjectileCanFire(
	TEXT("log.weapon.projectile.canfire"),
	0,
	TEXT("Log ProjectileWeapon CanFire()."),
	ECVF_SetByConsole
);

// Scoped Timer

TAutoConsoleVariable<int32> CsCVarLogWeaponProjectileScopedTimer(
	TEXT("log.weapon.projectile.scopedtimer"),
	0,
	TEXT("Log Weapon Projectile Scoped Timer."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogWeaponProjectileFireScopedTimer(
	TEXT("log.weapon.projectile.fire.scopedtimer"),
	0,
	TEXT("Log Weapon Projectile Fire() Scoped Timer."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogWeaponProjectileGetLaunchLocationScopedTimer(
	TEXT("log.weapon.projectile.getlaunchlocation.scopedtimer"),
	0,
	TEXT("Log Weapon Projectile GetLaunchLocation() Scoped Timer."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogWeaponProjectileGetLaunchDirectionScopedTimer(
	TEXT("log.weapon.projectile.getlaunchdirection.scopedtimer"),
	0,
	TEXT("Log Weapon Projectile GetLaunchDirection() Scoped Timer."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogWeaponProjectileProjectileStartLaunchScopedTimer(
	TEXT("log.weapon.projectile.projectile.startlaunch.scopedtimer"),
	0,
	TEXT("Log Weapon Projectile ProjectileImpl.StartLaunch() Scoped Timer."),
	ECVF_SetByConsole
);

// CVarLog
#pragma region

namespace NCsCVarLog
{
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogWeaponProjectileState, "Log ProjectileWeapon Current State");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogWeaponProjectileStateTransition, "Log ProjectileWeapon State Transition");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogWeaponProjectileCanFire, "Log ProjectileWeapon CanFire()");
	// Scoped Timers
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogWeaponProjectileScopedTimer, "Log Weapon Projectile Scoped Timer");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogWeaponProjectileFireScopedTimer, "Log Weapon Projectile Fire() Scoped Timer");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogWeaponProjectileGetLaunchLocationScopedTimer, "Log Weapon Projectile GetLaunchLocation() Scoped Timer");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogWeaponProjectileGetLaunchDirectionScopedTimer, "Log Weapon Projectile GetLaunchDirection() Scoped Timer");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogWeaponProjectileProjectileStartLaunchScopedTimer, "Log Weapon Projectile ProjectileImpl.StartLaunch() Scoped Timer");

	namespace Map
	{
		CSWP_API CS_ADD_TO_CVAR_MAP(LogWeaponProjectileState, CsCVarLogWeaponProjectileState);
		CSWP_API CS_ADD_TO_CVAR_MAP(LogWeaponProjectileStateTransition, CsCVarLogWeaponProjectileStateTransition);
		CSWP_API CS_ADD_TO_CVAR_MAP(LogWeaponProjectileCanFire, CsCVarLogWeaponProjectileCanFire);
		// Scoped Timers
		CSWP_API CS_ADD_TO_CVAR_MAP(LogWeaponProjectileScopedTimer, CsCVarLogWeaponProjectileScopedTimer);
		CSWP_API CS_ADD_TO_CVAR_MAP(LogWeaponProjectileFireScopedTimer, CsCVarLogWeaponProjectileFireScopedTimer);
		CSWP_API CS_ADD_TO_CVAR_MAP(LogWeaponProjectileGetLaunchLocationScopedTimer, CsCVarLogWeaponProjectileGetLaunchLocationScopedTimer);
		CSWP_API CS_ADD_TO_CVAR_MAP(LogWeaponProjectileGetLaunchDirectionScopedTimer, CsCVarLogWeaponProjectileGetLaunchDirectionScopedTimer);
		CSWP_API CS_ADD_TO_CVAR_MAP(LogWeaponProjectileProjectileStartLaunchScopedTimer, CsCVarLogWeaponProjectileProjectileStartLaunchScopedTimer);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(WeaponProjectile, "Weapon Projectile");

	namespace Map
	{
		extern CSWP_API CS_ADD_TO_CVAR_MAP(WeaponProjectile, CsCVarLogWeaponProjectileScopedTimer);
	}
}

#pragma endregion ScopedGroup
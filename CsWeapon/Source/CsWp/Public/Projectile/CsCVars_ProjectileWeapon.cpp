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

TAutoConsoleVariable<int32> CsCVarLogWeaponProjectileScopedTimerFire(
	TEXT("log.weapon.projectile.scopedtimer.fire"),
	0,
	TEXT("Log Weapon Projectile Scoped Timer Fire()."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogWeaponProjectileScopedTimerGetLaunchLocation(
	TEXT("log.weapon.projectile.scopedtimer.getlaunchlocation"),
	0,
	TEXT("Log Weapon Projectile Scoped Timer GetLaunchLocation()."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogWeaponProjectileScopedTimerGetLaunchDirection(
	TEXT("log.weapon.projectile.scopedtimer.getlaunchdirection"),
	0,
	TEXT("Log Weapon Projectile Scoped Timer GetLaunchDirection()."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogWeaponProjectileProjectileScopedTimerStartLaunch(
	TEXT("log.weapon.projectile.projectile.scopedtimer.startlaunch"),
	0,
	TEXT("Log Weapon Projectile Scoped Timer ProjectileImpl.StartLaunch()."),
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
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogWeaponProjectileScopedTimerFire, "Log Weapon Projectile Scoped Timer Fire()");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogWeaponProjectileScopedTimerGetLaunchLocation, "Log Weapon Projectile Scoped Timer GetLaunchLocation()");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogWeaponProjectileScopedTimerGetLaunchDirection, "Log Weapon Projectile Scoped Timer GetLaunchDirection()");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogWeaponProjectileProjectileScopedTimerStartLaunch, "Log Weapon Projectile Scoped Timer ProjectileImpl.StartLaunch()");

	namespace Map
	{
		CSWP_API CS_ADD_TO_CVAR_MAP(LogWeaponProjectileState, CsCVarLogWeaponProjectileState);
		CSWP_API CS_ADD_TO_CVAR_MAP(LogWeaponProjectileStateTransition, CsCVarLogWeaponProjectileStateTransition);
		CSWP_API CS_ADD_TO_CVAR_MAP(LogWeaponProjectileCanFire, CsCVarLogWeaponProjectileCanFire);
		// Scoped Timers
		CSWP_API CS_ADD_TO_CVAR_MAP(LogWeaponProjectileScopedTimer, CsCVarLogWeaponProjectileScopedTimer);
		CSWP_API CS_ADD_TO_CVAR_MAP(LogWeaponProjectileScopedTimerFire, CsCVarLogWeaponProjectileScopedTimerFire);
		CSWP_API CS_ADD_TO_CVAR_MAP(LogWeaponProjectileScopedTimerGetLaunchLocation, CsCVarLogWeaponProjectileScopedTimerGetLaunchLocation);
		CSWP_API CS_ADD_TO_CVAR_MAP(LogWeaponProjectileScopedTimerGetLaunchDirection, CsCVarLogWeaponProjectileScopedTimerGetLaunchDirection);
		CSWP_API CS_ADD_TO_CVAR_MAP(LogWeaponProjectileProjectileScopedTimerStartLaunch, CsCVarLogWeaponProjectileProjectileScopedTimerStartLaunch);
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
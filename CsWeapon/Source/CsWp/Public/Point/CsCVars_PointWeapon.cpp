// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Point/CsCVars_PointWeapon.h"

TAutoConsoleVariable<int32> CsCVarLogWeaponPointState(
	TEXT("log.weapon.point.state"),
	0,
	TEXT("Log PointWeapon Current State\n")
	TEXT("\n")
	TEXT("[Editor]\n")
	TEXT("0 - (default) DON'T	show log.\n")
	TEXT("1 -			SHOW	log."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogWeaponPointStateTransition(
	TEXT("log.weapon.point.state.transition"),
	0,
	TEXT("Log PointWeapon State Transition\n")
	TEXT("\n")
	TEXT("[Editor]\n")
	TEXT("0 - (default) DON'T	show log.\n")
	TEXT("1 -			SHOW	log."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogWeaponPointCanFire(
	TEXT("log.weapon.point.canfire"),
	0,
	TEXT("Log PointWeapon CanFire().\n")
	TEXT("\n")
	TEXT("[Editor]\n")
	TEXT("0 - (default) DON'T	show log.\n")
	TEXT("1 -			SHOW	log."),
	ECVF_SetByConsole
);

// Scoped Timer

TAutoConsoleVariable<int32> CsCVarLogWeaponPointScopedTimer(
	TEXT("log.weapon.point.scopedtimer"),
	0,
	TEXT("Log Weapon Point Scoped Timer.\n")
	TEXT("\n")
	TEXT("[Editor]\n")
	TEXT("0 - (default) DON'T	show log.\n")
	TEXT("1 -			SHOW	log."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogWeaponPointScopedTimerFire(
	TEXT("log.weapon.point.scopedtimer.fire"),
	0,
	TEXT("Log Weapon Point Scoped Timer Fire().\n")
	TEXT("\n")
	TEXT("[Editor]\n")
	TEXT("0 - (default) DON'T	show log.\n")
	TEXT("1 -			SHOW	log."),
	ECVF_SetByConsole
);

// CVarLog
#pragma region

namespace NCsCVarLog
{
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogWeaponPointState, "Log PointWeapon Current State");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogWeaponPointStateTransition, "Log PointWeapon State Transition");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogWeaponPointCanFire, "Log PointWeapon CanFire()");
	// Scoped Timers
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogWeaponPointScopedTimer, "Log Weapon Point Scoped Timer");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogWeaponPointScopedTimerFire, "Log Weapon Point Scoped Timer Fire()");

	namespace Map
	{
		CSWP_API CS_ADD_TO_CVAR_MAP(LogWeaponPointState, CsCVarLogWeaponPointState);
		CSWP_API CS_ADD_TO_CVAR_MAP(LogWeaponPointStateTransition, CsCVarLogWeaponPointStateTransition);
		CSWP_API CS_ADD_TO_CVAR_MAP(LogWeaponPointCanFire, CsCVarLogWeaponPointCanFire);
		// Scoped Timers
		CSWP_API CS_ADD_TO_CVAR_MAP(LogWeaponPointScopedTimer, CsCVarLogWeaponPointScopedTimer);
		CSWP_API CS_ADD_TO_CVAR_MAP(LogWeaponPointScopedTimerFire, CsCVarLogWeaponPointScopedTimerFire);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(WeaponPoint, "Weapon Point");

	namespace Map
	{
		extern CSWP_API CS_ADD_TO_CVAR_MAP(WeaponPoint, CsCVarLogWeaponPointScopedTimer);
	}
}

#pragma endregion ScopedGroup
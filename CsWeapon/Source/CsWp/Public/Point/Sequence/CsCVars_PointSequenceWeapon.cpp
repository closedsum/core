// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Point/CsCVars_PointWeapon.h"

TAutoConsoleVariable<int32> CsCVarLogWeaponPointSequenceState(
	TEXT("log.weapon.point.sequence.state"),
	0,
	TEXT("Log PointWeapon Current State\n")
	TEXT("\n")
	TEXT("[Editor]\n")
	TEXT("0 - (default) DON'T	show log.\n")
	TEXT("1 -			SHOW	log."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogWeaponPointSequenceStateTransition(
	TEXT("log.weapon.point.sequence.state.transition"),
	0,
	TEXT("Log PointWeapon State Transition\n")
	TEXT("\n")
	TEXT("[Editor]\n")
	TEXT("0 - (default) DON'T	show log.\n")
	TEXT("1 -			SHOW	log."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogWeaponPointSequenceCanFire(
	TEXT("log.weapon.point.sequence.canfire"),
	0,
	TEXT("Log PointWeapon CanFire().\n")
	TEXT("\n")
	TEXT("[Editor]\n")
	TEXT("0 - (default) DON'T	show log.\n")
	TEXT("1 -			SHOW	log."),
	ECVF_SetByConsole
);

// Scoped Timer

TAutoConsoleVariable<int32> CsCVarLogWeaponPointSequenceScopedTimer(
	TEXT("log.weapon.point.sequence.scopedtimer"),
	0,
	TEXT("Log Weapon Point Scoped Timer.\n")
	TEXT("\n")
	TEXT("[Editor]\n")
	TEXT("0 - (default) DON'T	show log.\n")
	TEXT("1 -			SHOW	log."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogWeaponPointSequenceScopedTimerFire(
	TEXT("log.weapon.point.sequence.scopedtimer.fire"),
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
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogWeaponPointSequenceState, "Log PointWeapon Current State");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogWeaponPointSequenceStateTransition, "Log PointWeapon State Transition");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogWeaponPointSequenceCanFire, "Log PointWeapon CanFire()");
	// Scoped Timers
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogWeaponPointSequenceScopedTimer, "Log Weapon Point Scoped Timer");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogWeaponPointSequenceScopedTimerFire, "Log Weapon Point Scoped Timer Fire()");

	namespace Map
	{
		CSWP_API CS_ADD_TO_CVAR_MAP(LogWeaponPointSequenceState, CsCVarLogWeaponPointSequenceState);
		CSWP_API CS_ADD_TO_CVAR_MAP(LogWeaponPointSequenceStateTransition, CsCVarLogWeaponPointSequenceStateTransition);
		CSWP_API CS_ADD_TO_CVAR_MAP(LogWeaponPointSequenceCanFire, CsCVarLogWeaponPointSequenceCanFire);
		// Scoped Timers
		CSWP_API CS_ADD_TO_CVAR_MAP(LogWeaponPointSequenceScopedTimer, CsCVarLogWeaponPointSequenceScopedTimer);
		CSWP_API CS_ADD_TO_CVAR_MAP(LogWeaponPointSequenceScopedTimerFire, CsCVarLogWeaponPointSequenceScopedTimerFire);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(WeaponPointSequence, "Weapon Point");

	namespace Map
	{
		extern CSWP_API CS_ADD_TO_CVAR_MAP(WeaponPointSequence, CsCVarLogWeaponPointSequenceScopedTimer);
	}
}

#pragma endregion ScopedGroup
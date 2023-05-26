// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Beam/CsCVars_BeamWeapon.h"

TAutoConsoleVariable<int32> CsCVarLogWeaponBeamState(
	TEXT("log.weapon.beam.state"),
	0,
	TEXT("Log BeamWeapon Current State"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogWeaponBeamStateTransition(
	TEXT("log.weapon.beam.state.transition"),
	0,
	TEXT("Log BeamWeapon State Transition"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogWeaponBeamCanFire(
	TEXT("log.weapon.beam.canfire"),
	0,
	TEXT("Log BeamWeapon CanFire()."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogWeaponBeamBeamCollision(
	TEXT("log.weapon.beam.beam.collision"),
	0,
	TEXT("Log BeamWeapon Beam() Collision."),
	ECVF_SetByConsole
);

// Scoped Timer

TAutoConsoleVariable<int32> CsCVarLogWeaponBeamScopedTimer(
	TEXT("log.weapon.beam.scopedtimer"),
	0,
	TEXT("Log Weapon Beam Scoped Timer."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogWeaponBeamScopedTimerFire(
	TEXT("log.weapon.beam.scopedtimer.fire"),
	0,
	TEXT("Log Weapon Beam Scoped Timer Fire()."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogWeaponBeamScopedTimerBeamGetLocation(
	TEXT("log.weapon.beam.scopedtimer.beam.getlocation"),
	0,
	TEXT("Log Weapon Beam Scoped Timer BeamImpl.GetLocation()."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogWeaponBeamScopedTimerBeamGetDirection(
	TEXT("log.weapon.beam.scopedtimer.beam.getdirection"),
	0,
	TEXT("Log Weapon Beam Scoped Timer BeamImpl.GetDirection()."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogWeaponBeamScopedTimerBeam(
	TEXT("log.weapon.beam.scopedtimer.beam"),
	0,
	TEXT("Log Weapon Beam Scoped Timer Beam()."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogWeaponBeamScopedTimerLineBeam(
	TEXT("log.weapon.beam.scopedtimer.linebeam"),
	0,
	TEXT("Log Weapon Beam Scoped Timer LineBeam()."),
	ECVF_SetByConsole
);

// CVarLog
#pragma region

namespace NCsCVarLog
{
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogWeaponBeamState, "Log BeamWeapon Current State");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogWeaponBeamStateTransition, "Log BeamWeapon State Transition");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogWeaponBeamCanFire, "Log BeamWeapon CanFire()");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogWeaponBeamBeamCollision, "Log BeamWeapon Beam() Collision");
	// Scoped Timers
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogWeaponBeamScopedTimer, "Log Weapon Beam Scoped Timer");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogWeaponBeamScopedTimerFire, "Log Weapon Beam Scoped Timer Fire()");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogWeaponBeamScopedTimerBeamGetLocation, "Log Weapon Beam Scoped Timer BeamImpl.GetLocation()");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogWeaponBeamScopedTimerBeamGetDirection, "Log Weapon Beam Scoped Timer BeamImpl.GetDirection()");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogWeaponBeamScopedTimerBeam, "Log Weapon Beam Scoped Timer Beam()");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogWeaponBeamScopedTimerLineBeam, "Log Weapon Beam Scoped Timer LineBeam()");

	namespace Map
	{
		CSWP_API CS_ADD_TO_CVAR_MAP(LogWeaponBeamState, CsCVarLogWeaponBeamState);
		CSWP_API CS_ADD_TO_CVAR_MAP(LogWeaponBeamStateTransition, CsCVarLogWeaponBeamStateTransition);
		CSWP_API CS_ADD_TO_CVAR_MAP(LogWeaponBeamCanFire, CsCVarLogWeaponBeamCanFire);
		CSWP_API CS_ADD_TO_CVAR_MAP(LogWeaponBeamBeamCollision, CsCVarLogWeaponBeamBeamCollision);
		// Scoped Timers
		CSWP_API CS_ADD_TO_CVAR_MAP(LogWeaponBeamScopedTimer, CsCVarLogWeaponBeamScopedTimer);
		CSWP_API CS_ADD_TO_CVAR_MAP(LogWeaponBeamScopedTimerFire, CsCVarLogWeaponBeamScopedTimerFire);
		CSWP_API CS_ADD_TO_CVAR_MAP(LogWeaponBeamScopedTimerBeamGetLocation, CsCVarLogWeaponBeamScopedTimerBeamGetLocation);
		CSWP_API CS_ADD_TO_CVAR_MAP(LogWeaponBeamScopedTimerBeamGetDirection, CsCVarLogWeaponBeamScopedTimerBeamGetDirection);
		CSWP_API CS_ADD_TO_CVAR_MAP(LogWeaponBeamScopedTimerBeam, CsCVarLogWeaponBeamScopedTimerBeam);
		CSWP_API CS_ADD_TO_CVAR_MAP(LogWeaponBeamScopedTimerLineBeam, CsCVarLogWeaponBeamScopedTimerLineBeam);
	}
}

#pragma endregion CVarLog

TAutoConsoleVariable<int32> CsCVarDrawWeaponBeamBeam(
	TEXT("draw.weapon.beam.beam"),
	0,
	TEXT("Draw BeamWeapon Beam()"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarDrawWeaponBeamLineBeam(
	TEXT("draw.weapon.beam.linebeam"),
	0,
	TEXT("Draw BeamWeapon LineBeam()"),
	ECVF_SetByConsole
);

// CVarDraw
#pragma region

namespace NCsCVarDraw
{
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(DrawWeaponBeamBeam, "Draw BeamWeapon Beam()");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(DrawWeaponBeamLineBeam, "Draw BeamWeapon LineBeam()");

	namespace Map
	{
		CSWP_API CS_ADD_TO_CVAR_MAP(DrawWeaponBeamBeam, CsCVarDrawWeaponBeamBeam);
		CSWP_API CS_ADD_TO_CVAR_MAP(DrawWeaponBeamLineBeam, CsCVarDrawWeaponBeamLineBeam);
	}
}

#pragma endregion CVarDraw

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(WeaponBeam, "Weapon Beam");

	namespace Map
	{
		extern CSWP_API CS_ADD_TO_CVAR_MAP(WeaponBeam, CsCVarLogWeaponBeamScopedTimer);
	}
}

#pragma endregion ScopedGroup
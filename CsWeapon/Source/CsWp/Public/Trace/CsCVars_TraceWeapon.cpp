// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Trace/CsCVars_TraceWeapon.h"

TAutoConsoleVariable<int32> CsCVarLogWeaponTraceState(
	TEXT("log.weapon.trace.state"),
	0,
	TEXT("Log TraceWeapon Current State"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogWeaponTraceStateTransition(
	TEXT("log.weapon.trace.state.transition"),
	0,
	TEXT("Log TraceWeapon State Transition"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogWeaponTraceCanFire(
	TEXT("log.weapon.trace.canfire"),
	0,
	TEXT("Log TraceWeapon CanFire()."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogWeaponTraceTraceCollision(
	TEXT("log.weapon.trace.trace.collision"),
	0,
	TEXT("Log TraceWeapon Trace() Collision."),
	ECVF_SetByConsole
);

// Scoped Timer

TAutoConsoleVariable<int32> CsCVarLogWeaponTraceScopedTimer(
	TEXT("log.weapon.trace.scopedtimer"),
	0,
	TEXT("Log Weapon Trace Scoped Timer."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogWeaponTraceScopedTimerFire(
	TEXT("log.weapon.trace.scopedtimer.fire"),
	0,
	TEXT("Log Weapon Trace Scoped Timer Fire()."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogWeaponTraceScopedTimerTraceGetLocation(
	TEXT("log.weapon.trace.scopedtimer.trace.getlocation"),
	0,
	TEXT("Log Weapon Trace Scoped Timer TraceImpl.GetLocation()."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogWeaponTraceScopedTimerTraceGetDirection(
	TEXT("log.weapon.trace.scopedtimer.trace.getdirection"),
	0,
	TEXT("Log Weapon Trace Scoped Timer TraceImpl.GetDirection()."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogWeaponTraceScopedTimerTrace(
	TEXT("log.weapon.trace.scopedtimer.trace"),
	0,
	TEXT("Log Weapon Trace Scoped Timer Trace()."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogWeaponTraceScopedTimerLineTrace(
	TEXT("log.weapon.trace.scopedtimer.linetrace"),
	0,
	TEXT("Log Weapon Trace Scoped Timer LineTrace()."),
	ECVF_SetByConsole
);

// CVarLog
#pragma region

namespace NCsCVarLog
{
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogWeaponTraceState, "Log TraceWeapon Current State");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogWeaponTraceStateTransition, "Log TraceWeapon State Transition");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogWeaponTraceCanFire, "Log TraceWeapon CanFire()");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogWeaponTraceTraceCollision, "Log TraceWeapon Trace() Collision");
	// Scoped Timers
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogWeaponTraceScopedTimer, "Log Weapon Trace Scoped Timer");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogWeaponTraceScopedTimerFire, "Log Weapon Trace Scoped Timer Fire()");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogWeaponTraceScopedTimerTraceGetLocation, "Log Weapon Trace Scoped Timer TraceImpl.GetLocation()");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogWeaponTraceScopedTimerTraceGetDirection, "Log Weapon Trace Scoped Timer TraceImpl.GetDirection()");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogWeaponTraceScopedTimerTrace, "Log Weapon Trace Scoped Timer Trace()");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogWeaponTraceScopedTimerLineTrace, "Log Weapon Trace Scoped Timer LineTrace()");

	namespace Map
	{
		CSWP_API CS_ADD_TO_CVAR_MAP(LogWeaponTraceState, CsCVarLogWeaponTraceState);
		CSWP_API CS_ADD_TO_CVAR_MAP(LogWeaponTraceStateTransition, CsCVarLogWeaponTraceStateTransition);
		CSWP_API CS_ADD_TO_CVAR_MAP(LogWeaponTraceCanFire, CsCVarLogWeaponTraceCanFire);
		CSWP_API CS_ADD_TO_CVAR_MAP(LogWeaponTraceTraceCollision, CsCVarLogWeaponTraceTraceCollision);
		// Scoped Timers
		CSWP_API CS_ADD_TO_CVAR_MAP(LogWeaponTraceScopedTimer, CsCVarLogWeaponTraceScopedTimer);
		CSWP_API CS_ADD_TO_CVAR_MAP(LogWeaponTraceScopedTimerFire, CsCVarLogWeaponTraceScopedTimerFire);
		CSWP_API CS_ADD_TO_CVAR_MAP(LogWeaponTraceScopedTimerTraceGetLocation, CsCVarLogWeaponTraceScopedTimerTraceGetLocation);
		CSWP_API CS_ADD_TO_CVAR_MAP(LogWeaponTraceScopedTimerTraceGetDirection, CsCVarLogWeaponTraceScopedTimerTraceGetDirection);
		CSWP_API CS_ADD_TO_CVAR_MAP(LogWeaponTraceScopedTimerTrace, CsCVarLogWeaponTraceScopedTimerTrace);
		CSWP_API CS_ADD_TO_CVAR_MAP(LogWeaponTraceScopedTimerLineTrace, CsCVarLogWeaponTraceScopedTimerLineTrace);
	}
}

#pragma endregion CVarLog

TAutoConsoleVariable<int32> CsCVarDrawWeaponTraceTrace(
	TEXT("draw.weapon.trace.trace"),
	0,
	TEXT("Draw TraceWeapon Trace()"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarDrawWeaponTraceLineTrace(
	TEXT("draw.weapon.trace.linetrace"),
	0,
	TEXT("Draw TraceWeapon LineTrace()"),
	ECVF_SetByConsole
);

// CVarDraw
#pragma region

namespace NCsCVarDraw
{
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(DrawWeaponTraceTrace, "Draw TraceWeapon Trace()");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(DrawWeaponTraceLineTrace, "Draw TraceWeapon LineTrace()");

	namespace Map
	{
		CSWP_API CS_ADD_TO_CVAR_MAP(DrawWeaponTraceTrace, CsCVarDrawWeaponTraceTrace);
		CSWP_API CS_ADD_TO_CVAR_MAP(DrawWeaponTraceLineTrace, CsCVarDrawWeaponTraceLineTrace);
	}
}

#pragma endregion CVarDraw

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(WeaponTrace, "Weapon Trace");

	namespace Map
	{
		extern CSWP_API CS_ADD_TO_CVAR_MAP(WeaponTrace, CsCVarLogWeaponTraceScopedTimer);
	}
}

#pragma endregion ScopedGroup
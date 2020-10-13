// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
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

TAutoConsoleVariable<int32> CsCVarLogWeaponTraceScopedTimerGetDirection(
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

// CVarLog
#pragma region

namespace NCsCVarLog
{
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogWeaponTraceState, "Log TraceWeapon Current State");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogWeaponTraceStateTransition, "Log TraceWeapon State Transition");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogWeaponTraceCanFire, "Log TraceWeapon CanFire()");
	// Scoped Timers
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogWeaponTraceScopedTimer, "Log Weapon Trace Scoped Timer");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogWeaponTraceScopedTimerFire, "Log Weapon Trace Scoped Timer Fire()");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogWeaponTraceScopedTimerTraceGetLocation, "Log Weapon Trace Scoped Timer TraceImpl.GetLocation()");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogWeaponTraceScopedTimerTraceGetDirection, "Log Weapon Trace Scoped Timer TraceImpl.GetDirection()");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogWeaponTraceScopedTimerTrace, "Log Weapon Trace Scoped Timer Trace()");

	namespace Map
	{
		CSWP_API CS_ADD_TO_CVAR_MAP(LogWeaponTraceState, CsCVarLogWeaponTraceState);
		CSWP_API CS_ADD_TO_CVAR_MAP(LogWeaponTraceStateTransition, CsCVarLogWeaponTraceStateTransition);
		CSWP_API CS_ADD_TO_CVAR_MAP(LogWeaponTraceCanFire, CsCVarLogWeaponTraceCanFire);
		// Scoped Timers
		CSWP_API CS_ADD_TO_CVAR_MAP(LogWeaponTraceScopedTimer, CsCVarLogWeaponTraceScopedTimer);
		CSWP_API CS_ADD_TO_CVAR_MAP(LogWeaponTraceScopedTimerFire, CsCVarLogWeaponTraceScopedTimerFire);
		CSWP_API CS_ADD_TO_CVAR_MAP(LogWeaponTraceScopedTimerTraceGetLocation, CsCVarLogWeaponTraceScopedTimerTraceGetLocation);
		CSWP_API CS_ADD_TO_CVAR_MAP(LogWeaponTraceScopedTimerTraceGetDirection, CsCVarLogWeaponTraceScopedTimerTraceGetDirection);
		CSWP_API CS_ADD_TO_CVAR_MAP(LogWeaponTraceScopedTimerTrace, CsCVarLogWeaponTraceScopedTimerTrace);
	}
}

#pragma endregion CVarLog

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
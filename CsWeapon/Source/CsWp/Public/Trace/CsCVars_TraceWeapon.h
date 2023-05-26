// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "CsCVars.h"

#pragma once

extern CSWP_API TAutoConsoleVariable<int32> CsCVarLogWeaponTraceState;
extern CSWP_API TAutoConsoleVariable<int32> CsCVarLogWeaponTraceStateTransition;
extern CSWP_API TAutoConsoleVariable<int32> CsCVarLogWeaponTraceCanFire;
extern CSWP_API TAutoConsoleVariable<int32> CsCVarLogWeaponTraceTraceCollision;
// Scoped Timers
extern CSWP_API TAutoConsoleVariable<int32> CsCVarLogWeaponTraceScopedTimer;
extern CSWP_API TAutoConsoleVariable<int32> CsCVarLogWeaponTraceScopedTimerFire;
extern CSWP_API TAutoConsoleVariable<int32> CsCVarLogWeaponTraceScopedTimerTraceGetLocation;
extern CSWP_API TAutoConsoleVariable<int32> CsCVarLogWeaponTraceScopedTimerTraceGetDirection;
extern CSWP_API TAutoConsoleVariable<int32> CsCVarLogWeaponTraceScopedTimerTrace;
extern CSWP_API TAutoConsoleVariable<int32> CsCVarLogWeaponTraceScopedTimerLineTrace;

// CVarLog
#pragma region

namespace NCsCVarLog
{
	extern CSWP_API const Type LogWeaponTraceState;
	extern CSWP_API const Type LogWeaponTraceStateTransition;
	extern CSWP_API const Type LogWeaponTraceCanFire;
	extern CSWP_API const Type LogWeaponTraceTraceCollision;
	// Scoped Timers
	extern CSWP_API const Type LogWeaponTraceScopedTimer;
	extern CSWP_API const Type LogWeaponTraceScopedTimerFire;
	extern CSWP_API const Type LogWeaponTraceScopedTimerTraceGetLocation;
	extern CSWP_API const Type LogWeaponTraceScopedTimerTraceGetDirection;
	extern CSWP_API const Type LogWeaponTraceScopedTimerTrace;
	extern CSWP_API const Type LogWeaponTraceScopedTimerLineTrace;

	namespace Map
	{
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(LogWeaponTraceState);
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(LogWeaponTraceStateTransition);
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(LogWeaponTraceCanFire);
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(LogWeaponTraceTraceCollision);
		// Scoped Timers
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(LogWeaponTraceScopedTimer);
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(LogWeaponTraceScopedTimerFire);
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(LogWeaponTraceScopedTimerTraceGetLocation);
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(LogWeaponTraceScopedTimerTraceGetDirection);
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(LogWeaponTraceScopedTimerTrace);
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(LogWeaponTraceScopedTimerLineTrace);
	}
}

#pragma endregion CVarLog

extern CSWP_API TAutoConsoleVariable<int32> CsCVarDrawWeaponTraceTrace;

// CVarDraw
#pragma region

namespace NCsCVarDraw
{
	extern CSWP_API const Type DrawWeaponTraceTrace;
	extern CSWP_API const Type DrawWeaponTraceLineTrace;

	namespace Map
	{
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(DrawWeaponTraceTrace);
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(DrawWeaponTraceLineTrace);
	}
}

#pragma endregion CVarDraw

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	extern CSWP_API const Type WeaponTrace;

	namespace Map
	{
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(WeaponTrace);
	}
}

#pragma endregion ScopedGroup
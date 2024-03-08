// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "CsCVars.h"

extern CSWP_API TAutoConsoleVariable<int32> CsCVarLogWeaponPointState;
extern CSWP_API TAutoConsoleVariable<int32> CsCVarLogWeaponPointStateTransition;
extern CSWP_API TAutoConsoleVariable<int32> CsCVarLogWeaponPointCanFire;
// Scoped Timers
extern CSWP_API TAutoConsoleVariable<int32> CsCVarLogWeaponPointScopedTimer;
extern CSWP_API TAutoConsoleVariable<int32> CsCVarLogWeaponPointScopedTimerFire;

// CVarLog
#pragma region

namespace NCsCVarLog
{
	extern CSWP_API const Type LogWeaponPointState;
	extern CSWP_API const Type LogWeaponPointStateTransition;
	extern CSWP_API const Type LogWeaponPointCanFire;
	// Scoped Timers
	extern CSWP_API const Type LogWeaponPointScopedTimer;
	extern CSWP_API const Type LogWeaponPointScopedTimerFire;

	namespace Map
	{
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(LogWeaponPointState);
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(LogWeaponPointStateTransition);
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(LogWeaponPointCanFire);
		// Scoped Timers
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(LogWeaponPointScopedTimer);
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(LogWeaponPointScopedTimerFire);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	extern CSWP_API const Type WeaponPoint;

	namespace Map
	{
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(WeaponPoint);
	}
}

#pragma endregion ScopedGroup
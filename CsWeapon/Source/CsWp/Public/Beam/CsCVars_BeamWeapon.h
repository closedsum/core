// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "CsCVars.h"

#pragma once

extern CSWP_API TAutoConsoleVariable<int32> CsCVarLogWeaponBeamState;
extern CSWP_API TAutoConsoleVariable<int32> CsCVarLogWeaponBeamStateTransition;
extern CSWP_API TAutoConsoleVariable<int32> CsCVarLogWeaponBeamCanFire;
extern CSWP_API TAutoConsoleVariable<int32> CsCVarLogWeaponBeamBeamCollision;
// Scoped Timers
extern CSWP_API TAutoConsoleVariable<int32> CsCVarLogWeaponBeamScopedTimer;
extern CSWP_API TAutoConsoleVariable<int32> CsCVarLogWeaponBeamScopedTimerFire;
extern CSWP_API TAutoConsoleVariable<int32> CsCVarLogWeaponBeamScopedTimerBeamGetLocation;
extern CSWP_API TAutoConsoleVariable<int32> CsCVarLogWeaponBeamScopedTimerBeamGetDirection;
extern CSWP_API TAutoConsoleVariable<int32> CsCVarLogWeaponBeamScopedTimerBeam;
extern CSWP_API TAutoConsoleVariable<int32> CsCVarLogWeaponBeamScopedTimerLineBeam;

// CVarLog
#pragma region

namespace NCsCVarLog
{
	extern CSWP_API const Type LogWeaponBeamState;
	extern CSWP_API const Type LogWeaponBeamStateTransition;
	extern CSWP_API const Type LogWeaponBeamCanFire;
	extern CSWP_API const Type LogWeaponBeamBeamCollision;
	// Scoped Timers
	extern CSWP_API const Type LogWeaponBeamScopedTimer;
	extern CSWP_API const Type LogWeaponBeamScopedTimerFire;
	extern CSWP_API const Type LogWeaponBeamScopedTimerBeamGetLocation;
	extern CSWP_API const Type LogWeaponBeamScopedTimerBeamGetDirection;
	extern CSWP_API const Type LogWeaponBeamScopedTimerBeam;
	extern CSWP_API const Type LogWeaponBeamScopedTimerLineBeam;

	namespace Map
	{
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(LogWeaponBeamState);
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(LogWeaponBeamStateTransition);
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(LogWeaponBeamCanFire);
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(LogWeaponBeamBeamCollision);
		// Scoped Timers
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(LogWeaponBeamScopedTimer);
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(LogWeaponBeamScopedTimerFire);
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(LogWeaponBeamScopedTimerBeamGetLocation);
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(LogWeaponBeamScopedTimerBeamGetDirection);
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(LogWeaponBeamScopedTimerBeam);
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(LogWeaponBeamScopedTimerLineBeam);
	}
}

#pragma endregion CVarLog

extern CSWP_API TAutoConsoleVariable<int32> CsCVarDrawWeaponBeamBeam;

// CVarDraw
#pragma region

namespace NCsCVarDraw
{
	extern CSWP_API const Type DrawWeaponBeamBeam;
	extern CSWP_API const Type DrawWeaponBeamLineBeam;

	namespace Map
	{
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(DrawWeaponBeamBeam);
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(DrawWeaponBeamLineBeam);
	}
}

#pragma endregion CVarDraw

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	extern CSWP_API const Type WeaponBeam;

	namespace Map
	{
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(WeaponBeam);
	}
}

#pragma endregion ScopedGroup
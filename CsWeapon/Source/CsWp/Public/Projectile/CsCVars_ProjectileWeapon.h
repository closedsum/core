// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "CsCVars.h"

#pragma once

extern CSWP_API TAutoConsoleVariable<int32> CsCVarLogWeaponProjectileState;
extern CSWP_API TAutoConsoleVariable<int32> CsCVarLogWeaponProjectileStateTransition;
extern CSWP_API TAutoConsoleVariable<int32> CsCVarLogWeaponProjectileCanFire;
extern CSWP_API TAutoConsoleVariable<int32> CsCVarLogWeaponProjectileLaunchDirection;
// Scoped Timers
extern CSWP_API TAutoConsoleVariable<int32> CsCVarLogWeaponProjectileScopedTimer;
extern CSWP_API TAutoConsoleVariable<int32> CsCVarLogWeaponProjectileScopedTimerFire;
extern CSWP_API TAutoConsoleVariable<int32> CsCVarLogWeaponProjectileScopedTimerGetLaunchLocation;
extern CSWP_API TAutoConsoleVariable<int32> CsCVarLogWeaponProjectileScopedTimerGetLaunchDirection;
extern CSWP_API TAutoConsoleVariable<int32> CsCVarLogWeaponProjectileProjectileScopedTimerLaunch;

// CVarLog
#pragma region

namespace NCsCVarLog
{
	extern CSWP_API const Type LogWeaponProjectileState;
	extern CSWP_API const Type LogWeaponProjectileStateTransition;
	extern CSWP_API const Type LogWeaponProjectileCanFire;
	extern CSWP_API const Type LogWeaponProjectileLaunchDirection;
	// Scoped Timers
	extern CSWP_API const Type LogWeaponProjectileScopedTimer;
	extern CSWP_API const Type LogWeaponProjectileScopedTimerFire;
	extern CSWP_API const Type LogWeaponProjectileScopedTimerGetLaunchLocation;
	extern CSWP_API const Type LogWeaponProjectileScopedTimerGetLaunchDirection;
	extern CSWP_API const Type LogWeaponProjectileProjectileScopedTimerLaunch;

	namespace Map
	{
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(LogWeaponProjectileState);
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(LogWeaponProjectileStateTransition);
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(LogWeaponProjectileCanFire);
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(LogWeaponProjectileLaunchDirection);
		// Scoped Timers
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(LogWeaponProjectileScopedTimer);
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(LogWeaponProjectileScopedTimerFire);
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(LogWeaponProjectileScopedTimerGetLaunchLocation);
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(LogWeaponProjectileScopedTimerGetLaunchDirection);
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(LogWeaponProjectileProjectileScopedTimerLaunch);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	extern CSWP_API const Type WeaponProjectile;

	namespace Map
	{
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(WeaponProjectile);
	}
}

#pragma endregion ScopedGroup
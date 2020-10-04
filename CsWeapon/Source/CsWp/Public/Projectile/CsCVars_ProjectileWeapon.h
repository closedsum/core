// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "CsCVars.h"

#pragma once

extern CSWP_API TAutoConsoleVariable<int32> CsCVarLogWeaponProjectileState;
extern CSWP_API TAutoConsoleVariable<int32> CsCVarLogWeaponProjectileStateTransition;
extern CSWP_API TAutoConsoleVariable<int32> CsCVarLogWeaponProjectileCanFire;
// Scoped Timers
extern CSWP_API TAutoConsoleVariable<int32> CsCVarLogWeaponProjectileScopedTimer;

// CVarLog
#pragma region

namespace NCsCVarLog
{
	extern CSWP_API const Type LogWeaponProjectileState;
	extern CSWP_API const Type LogWeaponProjectileStateTransition;
	extern CSWP_API const Type LogWeaponProjectileCanFire;
	// Scoped Timers
	extern CSWP_API const Type LogWeaponProjectileScopedTimer;

	namespace Map
	{
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(LogWeaponProjectileState);
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(LogWeaponProjectileStateTransition);
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(LogWeaponProjectileCanFire);
		// Scoped Timers
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(LogWeaponProjectileScopedTimer);
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
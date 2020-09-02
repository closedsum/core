// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "CsCVars.h"

#pragma once

extern CSWP_API TAutoConsoleVariable<int32> CsCVarLogWeaponProjectileState;
extern CSWP_API TAutoConsoleVariable<int32> CsCVarLogWeaponProjectileStateTransition;
extern CSWP_API TAutoConsoleVariable<int32> CsCVarLogWeaponProjectileCanFire;

// CVarLog
#pragma region

namespace NCsCVarLog
{
	extern CSWP_API const Type LogWeaponProjectileState;
	extern CSWP_API const Type LogWeaponProjectileStateTransition;
	extern CSWP_API const Type LogWeaponProjectileCanFire;

	namespace Map
	{
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(LogWeaponProjectileState);
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(LogWeaponProjectileStateTransition);
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(LogWeaponProjectileCanFire);
	}
}

#pragma endregion CVarLog
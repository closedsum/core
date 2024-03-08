// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CsCVars.h"

extern CSDMG_API TAutoConsoleVariable<int32> CsCVarDrawDamageEventSphere;

// CVarDraw
#pragma region

namespace NCsCVarDraw
{
	extern CSDMG_API const Type DrawDamageEventSphere;

	namespace Map
	{
		extern CSDMG_API CS_DECLARE_ADD_TO_CVAR_MAP(DrawDamageEventSphere);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	extern CSDMG_API const Type Damage;

	namespace Map
	{
		//extern CSDMG_API CS_DECLARE_ADD_TO_CVAR_MAP(Damage);
	}
}

#pragma endregion ScopedGroup
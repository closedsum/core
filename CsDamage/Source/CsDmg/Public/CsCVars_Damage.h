// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
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
// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "CsCVars.h"

#pragma once

extern CSSE_API TAutoConsoleVariable<int32> CsCVarLogCoordinatorStatusEffectEvents;

// CVarLog
#pragma region

namespace NCsCVarLog
{
	extern CSSE_API const Type LogCoordinatorStatusEffectEvents;

	namespace Map
	{
		extern CSSE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogCoordinatorStatusEffectEvents);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	extern CSSE_API const Type CoordinatorStatusEffect;

	namespace Map
	{
		//extern CSSE_API CS_DECLARE_ADD_TO_CVAR_MAP(ManagerDamage);
	}
}

#pragma endregion ScopedGroup
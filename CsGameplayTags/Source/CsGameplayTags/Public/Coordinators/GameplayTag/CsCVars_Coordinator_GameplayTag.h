// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CsCVars.h"

extern CSGAMEPLAYTAGS_API TAutoConsoleVariable<int32> CsCVarLogCoordinatorGameplayTagEvents;

// CVarLog
#pragma region

namespace NCsCVarLog
{
	extern CSGAMEPLAYTAGS_API const Type LogCoordinatorGameplayTagEvents;

	namespace Map
	{
		extern CSGAMEPLAYTAGS_API CS_DECLARE_ADD_TO_CVAR_MAP(LogCoordinatorGameplayTagEvents);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	//extern CSCORE_API const Type CoordinatorStatusEffect;

	namespace Map
	{
		//extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(ManagerDamage);
	}
}

#pragma endregion ScopedGroup
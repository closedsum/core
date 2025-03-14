// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CsCVars.h"

extern CSINPUT_API TAutoConsoleVariable<int32> CsCVarLogCoordinatorGameEventEvents;

// CVarLog
#pragma region

namespace NCsCVarLog
{
	extern CSINPUT_API const Type LogCoordinatorGameEventEvents;

	namespace Map
	{
		extern CSINPUT_API CS_DECLARE_ADD_TO_CVAR_MAP(LogCoordinatorGameEventEvents);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	//extern CSINPUT_API const Type CoordinatorStatusEffect;

	namespace Map
	{
		//extern CSINPUT_API CS_DECLARE_ADD_TO_CVAR_MAP(ManagerDamage);
	}
}

#pragma endregion ScopedGroup
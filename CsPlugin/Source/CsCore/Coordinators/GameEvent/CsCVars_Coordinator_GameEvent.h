// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "CsCVars.h"

#pragma once

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogCoordinatorGameEventEvents;

// CVarLog
#pragma region

namespace NCsCVarLog
{
	extern CSCORE_API const Type LogCoordinatorGameEventEvents;

	namespace Map
	{
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogCoordinatorGameEventEvents);
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
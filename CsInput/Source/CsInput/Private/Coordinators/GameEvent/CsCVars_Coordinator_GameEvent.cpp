// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Coordinators/GameEvent/CsCVars_Coordinator_GameEvent.h"

TAutoConsoleVariable<int32> CsCVarLogCoordinatorGameEventEvents(
	TEXT("log.coordinator.gameevent.events"),
	0,
	TEXT("Log Coordinator Game Event Events."),
	ECVF_SetByConsole
);

// CVarLog
#pragma region

namespace NCsCVarLog
{
	CSINPUT_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogCoordinatorGameEventEvents, "Log Coordinator Game Event Events");

	namespace Map
	{
		CSINPUT_API CS_ADD_TO_CVAR_MAP(LogCoordinatorGameEventEvents, CsCVarLogCoordinatorGameEventEvents);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	//CSINPUT_API CS_CREATE_ENUM_STRUCT_CUSTOM(CoordinatorStatusEffect, "Coordinator Status Effect");

	namespace Map
	{
		//extern CSINPUT_API CS_ADD_TO_CVAR_MAP(ManagerDamage, CsCVarLogManagerDamageScopedTimer);
	}
}

#pragma endregion ScopedGroup
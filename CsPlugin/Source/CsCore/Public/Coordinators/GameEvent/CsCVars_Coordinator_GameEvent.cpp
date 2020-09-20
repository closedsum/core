// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
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
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogCoordinatorGameEventEvents, "Log Coordinator Game Event Events");

	namespace Map
	{
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogCoordinatorGameEventEvents, CsCVarLogCoordinatorGameEventEvents);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	//CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(CoordinatorStatusEffect, "Coordinator Status Effect");

	namespace Map
	{
		//extern CSCORE_API CS_ADD_TO_CVAR_MAP(ManagerDamage, CsCVarLogManagerDamageScopedTimer);
	}
}

#pragma endregion ScopedGroup
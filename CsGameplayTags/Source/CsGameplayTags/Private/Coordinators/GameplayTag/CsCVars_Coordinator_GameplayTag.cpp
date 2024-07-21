// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Coordinators/GameplayTag/CsCVars_Coordinator_GameplayTag.h"

TAutoConsoleVariable<int32> CsCVarLogCoordinatorGameplayTagEvents(
	TEXT("log.coordinator.gameplaytag.events"),
	0,
	TEXT("Log Coordinator GameplayTag Events."),
	ECVF_SetByConsole
);

// CVarLog
#pragma region

namespace NCsCVarLog
{
	CSGAMEPLAYTAGS_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogCoordinatorGameplayTagEvents, "Log Coordinator GameplayTag Events");

	namespace Map
	{
		CSGAMEPLAYTAGS_API CS_ADD_TO_CVAR_MAP(LogCoordinatorGameplayTagEvents, CsCVarLogCoordinatorGameplayTagEvents);
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
// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Coordinators/StatusEffect/CsCVars_Coordinator_StatusEffect.h"

TAutoConsoleVariable<int32> CsCVarLogCoordinatorStatusEffectEvents(
	TEXT("log.coordinator.statuseffect.events"),
	0,
	TEXT("Log Coordinator Status Effect Events."),
	ECVF_SetByConsole
);

// CVarLog
#pragma region

namespace NCsCVarLog
{
	CSSE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogCoordinatorStatusEffectEvents, "Log Coordinator Status Effect Events");

	namespace Map
	{
		CSSE_API CS_ADD_TO_CVAR_MAP(FCsCVarLogMap, LogCoordinatorStatusEffectEvents, CsCVarLogCoordinatorStatusEffectEvents);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	CSSE_API CS_CREATE_ENUM_STRUCT_CUSTOM(CoordinatorStatusEffect, "Coordinator Status Effect");

	namespace Map
	{
		//extern CSCORE_API CS_ADD_TO_CVAR_MAP(FCsScopedGroupMap, ManagerDamage, CsCVarLogManagerDamageScopedTimer);
	}
}

#pragma endregion ScopedGroup
// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "CsCVars_Manager_Achievement.h"

TAutoConsoleVariable<int32> CsCVarLogManagerAchievementTransactions(
	TEXT("log.manager.achievement.transactions"),
	0,
	TEXT("Log Manager Achievement Transactions."),
	ECVF_SetByConsole | ECVF_SetByCode
);

// CVarLog
#pragma region

namespace NCsCVarLog
{
	CSPLATFORMSERVICES_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerAchievementTransactions, "Log Manager Achievement Transactions");

	namespace Map
	{
		CSPLATFORMSERVICES_API CS_ADD_TO_CVAR_MAP(LogManagerAchievementTransactions, CsCVarLogManagerAchievementTransactions);
	}
}

#pragma endregion CVarLog

TAutoConsoleVariable<int32> CsCVarEnableManagerAchievement(
	TEXT("enable.manager.achievement"),
	0,
	TEXT("[Non-Shipping][.ini - SystemSettings] Enable Manager Achievement."),
	ECVF_SetBySystemSettingsIni
);

namespace NCsCVarToggle
{
	CSPLATFORMSERVICES_API CS_CREATE_ENUM_STRUCT_CUSTOM(EnableManagerAchievement, "Enable Manager Achievement");

	namespace Map
	{
		CSPLATFORMSERVICES_API CS_ADD_TO_CVAR_MAP(EnableManagerAchievement, CsCVarEnableManagerAchievement);
	}
}
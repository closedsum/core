// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "CsCVars_Manager_Achievement.h"

// Managers
#pragma region

	// Achievement
#pragma region

TAutoConsoleVariable<int32> CsCVarLogManagerAchievementTransactions(
	TEXT("log.manager.achievement.transactions"),
	0,
	TEXT("Log Manager Achievement Transactions."),
	ECVF_SetByConsole | ECVF_SetByCode
);

#pragma endregion Achievement

#pragma endregion Managers

// CVarLog
#pragma region

namespace NCsCVarLog
{
	// Managers

		// Achievement
	CSPLATFORMSERVICES_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogManagerAchievementTransactions);

	namespace Map
	{
		// Managers

			// Achievement
		CSPLATFORMSERVICES_API CS_ADD_TO_CVAR_MAP(FCsCVarLogMap, LogManagerAchievementTransactions, CsCVarLogManagerAchievementTransactions);
	}
}

#pragma endregion CVarLog
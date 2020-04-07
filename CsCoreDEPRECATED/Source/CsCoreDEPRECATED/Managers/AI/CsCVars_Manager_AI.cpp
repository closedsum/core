// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/AI/CsCVars_Manager_AI.h"

// Managers
#pragma region

	// AI
#pragma region

TAutoConsoleVariable<int32> CsCVarLogManagerAITransactions(
	TEXT("log.manager.ai.transactions"),
	0,
	TEXT("Log Manager A.I. Allocation and DeAllocation."),
	ECVF_SetByConsole
);

#pragma endregion AI

#pragma endregion Managers

// CVarLog
#pragma region

namespace NCsCVarLog
{
	// Managers

		// AI
	CSCOREDEPRECATED_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogManagerAITransactions);

	namespace Map
	{
	}
}

#pragma endregion CVarLog
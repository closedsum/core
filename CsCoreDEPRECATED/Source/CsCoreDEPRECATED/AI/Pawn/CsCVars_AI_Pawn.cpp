// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "AI/Pawn/CsCVars_AI_Pawn.h"

// AI
#pragma region

TAutoConsoleVariable<int32> CsCVarLogManagerAITransactions(
	TEXT("log.manager.ai.transactions"),
	0,
	TEXT("Log Manager A.I. Allocation and DeAllocation."),
	ECVF_SetByConsole
);

#pragma endregion AI

// CVarLog
#pragma region

namespace NCsCVarLog
{
	// AI

		// Interactive AI Pawn
	CSCOREDEPRECATED_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogInteractiveAIPawnPhysicsStateChange);

	namespace Map
	{
	}
}

#pragma endregion CVarLog
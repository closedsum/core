// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "CsCVars_AI_BT_Task.h"

// AI
#pragma region

	// Behavior Tree
#pragma region

TAutoConsoleVariable<int32> CsCVarLogAIBTTasks(
	TEXT("log.ai.bt.tasks"),
	0,
	TEXT("Log A.I. Behavior Tree Tasks (Execute, Succeeded, and Abort)."),
	ECVF_SetByConsole
);

#pragma endregion Behavior Tree

#pragma endregion AI

// CVarLog
#pragma region

namespace NCsCVarLog
{
	// AI

		// Behavior Tree
	CSCOREDEPRECATED_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogAIBTTasks);

	namespace Map
	{
	}
}

#pragma endregion CVarLog
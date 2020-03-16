// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "AI/BehaviorTree/CsCVars_AI_BT.h"

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

TAutoConsoleVariable<int32> CsCVarDrawAIBTMoveTo(
	TEXT("draw.ai.bt.moveto"),
	0,
	TEXT("Draw A.I. Behavior Tree MoveTo Task."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarDrawAIBTRotateToFaceBBEntry(
	TEXT("draw.ai.bt.rotatetofacebbentry"),
	0,
	TEXT("Draw A.I. Behavior Tree RotateToFaceBBEntry Task."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarDrawAIBTLookAtRotateToFace(
	TEXT("draw.ai.bt.lookatandrotatetoface"),
	0,
	TEXT("Draw A.I. Behavior Tree LookAtAndRotateToFace Task."),
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
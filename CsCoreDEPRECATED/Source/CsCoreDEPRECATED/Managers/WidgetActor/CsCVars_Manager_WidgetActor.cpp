// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/WidgetActor/CsCVars_Manager_WidgetActor.h"

// Widget Actor
#pragma region

TAutoConsoleVariable<int32> CsCVarLogManagerWidgetActorTransactions(
	TEXT("log.manager.widget.actor.transactions"),
	0,
	TEXT("Log Manager Widget Actor Allocation and DeAllocation."),
	ECVF_SetByConsole
);

#pragma endregion Widget Actor

// CVarLog
#pragma region

namespace NCsCVarLog
{
	// Managers

		// Widget Actor
	CSCOREDEPRECATED_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogManagerWidgetActorTransactions);

	namespace Map
	{
		// Managers

			// Widget
	}
}

#pragma endregion CVarLog
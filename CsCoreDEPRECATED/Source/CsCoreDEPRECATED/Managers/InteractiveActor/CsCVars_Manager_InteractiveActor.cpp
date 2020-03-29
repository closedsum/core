// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/InteractiveActor/CsCVars_Manager_InteractiveActor.h"

// Interactive Actor
#pragma region

TAutoConsoleVariable<int32> CsCVarLogInteractiveActorPhysicsStateChange(
	TEXT("log.interactive.actor.physicsstatechange"),
	0,
	TEXT("Log Interactive Actor Physics State changes (Set and Clear)."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerInteractiveActorTransactions(
	TEXT("log.manager.interactive.actor.transactions"),
	0,
	TEXT("Log Manager Interactive Actor Allocation and DeAllocation."),
	ECVF_SetByConsole
);

#pragma endregion Interactive Actor

// CVarLog
#pragma region

namespace NCsCVarLog
{
	// Managers

		// Interactive Actor
	CSCOREDEPRECATED_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogInteractiveActorPhysicsStateChange);
	CSCOREDEPRECATED_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogManagerInteractiveActorTransactions);

	namespace Map
	{
		// Managers

			// Interactive Actor
	}
}

#pragma endregion CVarLog
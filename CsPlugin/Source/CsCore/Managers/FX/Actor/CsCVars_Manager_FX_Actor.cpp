// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/FX/Actor/CsCVars_Manager_FX_Actor.h"

TAutoConsoleVariable<int32> CsCVarLogManagerFXActorTransactions(
	TEXT("log.manager.fx.actor.transactions"),
	0,
	TEXT("Log Manager FX Actor Allocation and DeAllocation."),
	ECVF_SetByConsole
);

// CVarLog
#pragma region

namespace NCsCVarLog
{
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsCVarLog, LogManagerFXActorTransactions, "Log Manager FX Actor Transactions");

	namespace Map
	{
		CSCORE_API CS_ADD_TO_CVAR_MAP(FCsCVarLogMap, LogManagerFXActorTransactions, CsCVarLogManagerFXActorTransactions);
	}
}

#pragma endregion CVarLog
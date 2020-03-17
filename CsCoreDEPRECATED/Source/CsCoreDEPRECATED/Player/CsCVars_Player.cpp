// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Player/CsCVars_Player.h"

// OnBoard
#pragma region

TAutoConsoleVariable<int32> CsCVarLogPlayerStateOnBoard(
	TEXT("log.playerstate.onboard"),
	0,
	TEXT("Log PlayerState OnBoard"),
	ECVF_SetByConsole
);

#pragma endregion OnBoard

// CVarLog
#pragma region

namespace NCsCVarLog
{
	// AI

		// OnBoard
	CSCOREDEPRECATED_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogPlayerStateOnBoard);

	namespace Map
	{
	}
}

#pragma endregion CVarLog
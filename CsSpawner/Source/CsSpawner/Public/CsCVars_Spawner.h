// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CsCVars.h"

extern CSSPAWNER_API TAutoConsoleVariable<int32> CsCVarLogSpawnerTransactions;

// CVarLog
#pragma region

namespace NCsCVarLog
{
	extern CSSPAWNER_API const Type LogSpawnerTransactions;

	namespace Map
	{
		extern CSSPAWNER_API CS_DECLARE_ADD_TO_CVAR_MAP(LogSpawnerTransactions);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	namespace Map
	{
	}
}

#pragma endregion ScopedGroup
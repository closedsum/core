// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "CsCVars.h"

#pragma once

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerFXActorTransactions;

// CVarLog
#pragma region

namespace NCsCVarLog
{
	extern CSCORE_API const Type LogManagerFXActorTransactions;

	namespace Map
	{
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerFXActorTransactions);
	}
}

#pragma endregion CVarLog
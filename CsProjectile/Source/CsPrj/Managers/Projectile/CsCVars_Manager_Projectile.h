// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "CsCVars.h"

#pragma once

extern CSPRJ_API TAutoConsoleVariable<int32> CsCVarLogManagerProjectileTransactions;

// CVarLog
#pragma region

namespace NCsCVarLog
{
	extern CSPRJ_API const Type LogManagerProjectileTransactions;

	namespace Map
	{
		extern CSPRJ_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerProjectileTransactions);
	}
}

#pragma endregion CVarLog
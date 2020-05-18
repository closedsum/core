// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "CsCVars.h"

extern CSTD_API TAutoConsoleVariable<int32> CsTdCVarLogManagerCreepTransactions;
extern CSTD_API TAutoConsoleVariable<int32> CsTdCVarEnableManagerCreepUnitTest;

// CVarLog
#pragma region

namespace NCsCVarLog
{
	extern CSTD_API const Type LogManagerCreepTransactions;

	namespace Map
	{
		extern CSTD_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerCreepTransactions);
	}
}

#pragma endregion CVarLog

// CVarToggle
#pragma region

namespace NCsCVarToggle
{
	extern CSTD_API const Type EnableManagerCreepUnitTest;

	namespace Map
	{
		extern CSTD_API CS_DECLARE_ADD_TO_CVAR_MAP(EnableManagerCreepUnitTest);
	}
}

#pragma endregion CVarToggle
// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CsCVars.h"

extern CSLOAD_API TAutoConsoleVariable<int32> CsCVarLogManagerLoad;
extern CSLOAD_API TAutoConsoleVariable<int32> CsCVarManagerLoadAsyncOrder;
extern CSLOAD_API TAutoConsoleVariable<int32> CsCVarDisplayLoading;

// CVarLog
#pragma region

namespace NCsCVarLog
{
	typedef FECsCVarLog Type;

	extern CSLOAD_API const Type LogManagerLoad;

	namespace Map
	{
		extern CSLOAD_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerLoad);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
}

#pragma endregion ScopedGroup
// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "CsCVars.h"

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerLoad;

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarManagerLoadAsyncOrder;

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarDisplayLoading;

// CVarLog
#pragma region

namespace NCsCVarLog
{
	typedef FECsCVarLog Type;

	extern CSCORE_API const Type LogManagerLoad;

	namespace Map
	{
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerLoad);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
}

#pragma endregion ScopedGroup
// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "CsCVars.h"

#pragma once

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogRoutineScopedTimer;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogCoroutineScopedTimer;

// CVarLog
#pragma region

namespace NCsCVarLog
{
	extern CSCORE_API const Type LogRoutineScopedTimer;
	extern CSCORE_API const Type LogCoroutineScopedTimer;

	namespace Map
	{
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogRoutineScopedTimer);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogCoroutineScopedTimer);
	}
}

#pragma endregion CVarLog
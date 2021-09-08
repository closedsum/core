// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "CsCVars.h"

#pragma once

extern CSUI_API TAutoConsoleVariable<int32> CsCVarLogManagerFade;

// CVarLog
#pragma region

namespace NCsCVarLog
{
	extern CSUI_API const Type LogManagerFade;

	namespace Map
	{
		extern CSUI_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerFade);
	}
}

#pragma endregion CVarLog
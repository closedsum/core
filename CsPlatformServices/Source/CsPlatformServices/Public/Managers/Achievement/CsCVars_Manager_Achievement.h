// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CsCVars.h"

extern CSPLATFORMSERVICES_API TAutoConsoleVariable<int32> CsCVarLogManagerAchievementTransactions;

namespace NCsCVarLog
{
	extern CSPLATFORMSERVICES_API const Type LogManagerAchievementTransactions;

	namespace Map
	{
		extern CSPLATFORMSERVICES_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerAchievementTransactions);
	}
}

extern CSPLATFORMSERVICES_API TAutoConsoleVariable<bool> CsCVarEnableManagerAchievement;

namespace NCsCVarToggle
{
	extern CSPLATFORMSERVICES_API const Type EnableManagerAchievement;

	namespace Map
	{
		extern CSPLATFORMSERVICES_API CS_DECLARE_ADD_TO_CVAR_MAP(EnableManagerAchievement);
	}
}
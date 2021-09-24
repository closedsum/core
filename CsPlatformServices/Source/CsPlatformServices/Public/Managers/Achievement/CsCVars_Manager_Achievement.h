// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
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

extern CSPLATFORMSERVICES_API TAutoConsoleVariable<int32> CsCVarEnableManagerAchievement;

namespace NCsCVarToggle
{
	extern CSPLATFORMSERVICES_API const Type EnableManagerAchievement;

	namespace Map
	{
		extern CSPLATFORMSERVICES_API CS_DECLARE_ADD_TO_CVAR_MAP(EnableManagerAchievement);
	}
}
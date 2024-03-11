// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "CsCVars_Performance.h"

TAutoConsoleVariable<bool> CsCVarShowPerformanceFPS(
	TEXT("show.performance.fps"),
	0,
	TEXT("Show Performance FPS.\n")
	TEXT("\n")
	TEXT("Toggles showing any performance related FPS.\n")
	TEXT("0 - (default) DON'T SHOW.\n")
	TEXT("1 -			SHOW."),
	ECVF_SetByConsole
);

// CVarToggle
#pragma region

namespace NCsCVarToggle
{
	CSPERFORMANCE_API CS_CREATE_ENUM_STRUCT_CUSTOM(ShowPerformanceFPS, "Show Performance FPS");

	namespace Map
	{
		CSPERFORMANCE_API CS_ADD_TO_CVAR_MAP(ShowPerformanceFPS, CsCVarShowPerformanceFPS);
	}
}

#pragma endregion CVarToggle
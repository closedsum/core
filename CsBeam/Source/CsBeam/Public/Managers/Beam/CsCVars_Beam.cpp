// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Beam/CsCVars_Beam.h"

TAutoConsoleVariable<int32> CsCVarLogBeamCollision(
	TEXT("log.beam.collision"),
	0,
	TEXT("Log Beam Collision."),
	ECVF_SetByConsole
);

// Scoped Timer

TAutoConsoleVariable<int32> CsCVarLogBeamScopedTimer(
	TEXT("log.beam.scopedtimer"),
	0,
	TEXT("Log Beam Scoped Timer."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogBeamScopedTimerPrepareOnSetCollision(
	TEXT("log.beam.scopedtimer.prepareon.setcollision"),
	0,
	TEXT("Log Beam Scoped Timer Prepare On Set Collision."),
	ECVF_SetByConsole
);

// CVarLog
#pragma region

namespace NCsCVarLog
{
	CSBEAM_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogBeamCollision, "Log Beam Collision");
	// Scoped Timers
	CSBEAM_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogBeamScopedTimer, "Log Beam Scoped Timer");
	CSBEAM_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogBeamScopedTimerPrepareOnSetCollision, "Log Beam Scoped Timer Prepare On Set Collision");

	namespace Map
	{
		CSBEAM_API CS_ADD_TO_CVAR_MAP(LogBeamCollision, CsCVarLogBeamCollision);
		// Scoped Timers
		CSBEAM_API CS_ADD_TO_CVAR_MAP(LogBeamScopedTimer, CsCVarLogBeamScopedTimer);
		CSBEAM_API CS_ADD_TO_CVAR_MAP(LogBeamScopedTimerPrepareOnSetCollision, CsCVarLogBeamScopedTimerPrepareOnSetCollision);
	}
}

#pragma endregion CVarLog

// CVarDraw
#pragma region

namespace NCsCVarDraw
{
	namespace Map
	{
	}
}

#pragma endregion CVarDraw

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	CSBEAM_API CS_CREATE_ENUM_STRUCT_CUSTOM(Beam, "Beam");

	namespace Map
	{
		extern CSBEAM_API CS_ADD_TO_CVAR_MAP(Beam, CsCVarLogBeamScopedTimer);
	}
}

#pragma endregion ScopedGroup
// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CsCVars.h"

extern CSBEAM_API TAutoConsoleVariable<int32> CsCVarLogBeamCollision;
extern CSBEAM_API TAutoConsoleVariable<int32> CsCVarLogBeamCollision;
// Scoped Timers
extern CSBEAM_API TAutoConsoleVariable<int32> CsCVarLogBeamScopedTimer;
extern CSBEAM_API TAutoConsoleVariable<int32> CsCVarLogBeamScopedTimerPrepareOnSetCollision;

// CVarLog
#pragma region

namespace NCsCVarLog
{
	extern CSBEAM_API const Type LogBeamCollision;
	// Scoped Timers
	extern CSBEAM_API const Type LogBeamScopedTimer;
	extern CSBEAM_API const Type LogBeamScopedTimerPrepareOnSetCollision;

	namespace Map
	{
		extern CSBEAM_API CS_DECLARE_ADD_TO_CVAR_MAP(LogBeamCollision);
		// Scoped Timers
		extern CSBEAM_API CS_DECLARE_ADD_TO_CVAR_MAP(LogBeamScopedTimer);
		extern CSBEAM_API CS_DECLARE_ADD_TO_CVAR_MAP(LogBeamScopedTimerPrepareOnSetCollision);
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

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	extern CSBEAM_API const Type Beam;

	namespace Map
	{
		extern CSBEAM_API CS_DECLARE_ADD_TO_CVAR_MAP(Beam);
	}
}

#pragma endregion ScopedGroup
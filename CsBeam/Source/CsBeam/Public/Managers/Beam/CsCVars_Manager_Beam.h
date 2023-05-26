// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "CsCVars.h"

#pragma once

extern CSBEAM_API TAutoConsoleVariable<int32> CsCVarLogManagerBeamTransactions;
// Scoped Timers
extern CSBEAM_API TAutoConsoleVariable<int32> CsCVarLogManagerBeamScopedTimer;
extern CSBEAM_API TAutoConsoleVariable<int32> CsCVarLogManagerBeamScopedTimerCreatePool;
extern CSBEAM_API TAutoConsoleVariable<int32> CsCVarLogManagerBeamScopedTimerUpdate;
extern CSBEAM_API TAutoConsoleVariable<int32> CsCVarLogManagerBeamScopedTimerUpdateObject;
extern CSBEAM_API TAutoConsoleVariable<int32> CsCVarLogManagerBeamScopedTimerAllocate;
extern CSBEAM_API TAutoConsoleVariable<int32> CsCVarLogManagerBeamScopedTimerAllocateObject;
extern CSBEAM_API TAutoConsoleVariable<int32> CsCVarLogManagerBeamScopedTimerDeallocate;
extern CSBEAM_API TAutoConsoleVariable<int32> CsCVarLogManagerBeamScopedTimerDeallocateObject;
extern CSBEAM_API TAutoConsoleVariable<int32> CsCVarLogManagerBeamScopedTimerSpawn;
extern CSBEAM_API TAutoConsoleVariable<int32> CsCVarLogManagerBeamScopedTimerDestroy;

// CVarLog
#pragma region

namespace NCsCVarLog
{
	extern CSBEAM_API const Type LogManagerBeamTransactions;
	// Scoped Timer
	extern CSBEAM_API const Type LogManagerBeamScopedTimer;
	extern CSBEAM_API const Type LogManagerBeamScopedTimerCreatePool;
	extern CSBEAM_API const Type LogManagerBeamScopedTimerUpdate;
	extern CSBEAM_API const Type LogManagerBeamScopedTimerUpdateObject;
	extern CSBEAM_API const Type LogManagerBeamScopedTimerAllocate;
	extern CSBEAM_API const Type LogManagerBeamScopedTimerAllocateObject;
	extern CSBEAM_API const Type LogManagerBeamScopedTimerDeallocate;
	extern CSBEAM_API const Type LogManagerBeamScopedTimerDeallocateObject;
	extern CSBEAM_API const Type LogManagerBeamScopedTimerSpawn;
	extern CSBEAM_API const Type LogManagerBeamScopedTimerDestroy;

	namespace Map
	{
		extern CSBEAM_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerBeamTransactions);
		// Scoped Timer
		extern CSBEAM_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerBeamScopedTimer);
		extern CSBEAM_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerBeamScopedTimerCreatePool);
		extern CSBEAM_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerBeamScopedTimerUpdate);
		extern CSBEAM_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerBeamScopedTimerUpdateObject);
		extern CSBEAM_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerBeamScopedTimerAllocate);
		extern CSBEAM_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerBeamScopedTimerAllocateObject);
		extern CSBEAM_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerBeamScopedTimerDeallocate);
		extern CSBEAM_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerBeamScopedTimerDeallocateObject);
		extern CSBEAM_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerBeamScopedTimerSpawn);
		extern CSBEAM_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerBeamScopedTimerDestroy);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	extern CSBEAM_API const Type ManagerBeam;

	namespace Map
	{
		extern CSBEAM_API CS_DECLARE_ADD_TO_CVAR_MAP(ManagerBeam);
	}
}

#pragma endregion ScopedGroup
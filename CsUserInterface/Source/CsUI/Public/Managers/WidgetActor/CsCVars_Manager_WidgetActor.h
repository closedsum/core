// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CsCVars.h"

extern CSUI_API TAutoConsoleVariable<int32> CsCVarLogManagerWidgetActorTransactions;
// Scoped Timers
extern CSUI_API TAutoConsoleVariable<int32> CsCVarLogManagerWidgetActorScopedTimer;
extern CSUI_API TAutoConsoleVariable<int32> CsCVarLogManagerWidgetActorScopedTimerCreatePool;
extern CSUI_API TAutoConsoleVariable<int32> CsCVarLogManagerWidgetActorScopedTimerUpdate;
extern CSUI_API TAutoConsoleVariable<int32> CsCVarLogManagerWidgetActorScopedTimerUpdateObject;
extern CSUI_API TAutoConsoleVariable<int32> CsCVarLogManagerWidgetActorScopedTimerAllocate;
extern CSUI_API TAutoConsoleVariable<int32> CsCVarLogManagerWidgetActorScopedTimerAllocateObject;
extern CSUI_API TAutoConsoleVariable<int32> CsCVarLogManagerWidgetActorScopedTimerDeallocate;
extern CSUI_API TAutoConsoleVariable<int32> CsCVarLogManagerWidgetActorScopedTimerDeallocateObject;
extern CSUI_API TAutoConsoleVariable<int32> CsCVarLogManagerWidgetActorScopedTimerSpawn;
extern CSUI_API TAutoConsoleVariable<int32> CsCVarLogManagerWidgetActorScopedTimerDestroy;

// CVarLog
#pragma region

namespace NCsCVarLog
{
	extern CSUI_API const Type LogManagerWidgetActorTransactions;
	// Scoped Timer
	extern CSUI_API const Type LogManagerWidgetActorScopedTimer;
	extern CSUI_API const Type LogManagerWidgetActorScopedTimerCreatePool;
	extern CSUI_API const Type LogManagerWidgetActorScopedTimerUpdate;
	extern CSUI_API const Type LogManagerWidgetActorScopedTimerUpdateObject;
	extern CSUI_API const Type LogManagerWidgetActorScopedTimerAllocate;
	extern CSUI_API const Type LogManagerWidgetActorScopedTimerAllocateObject;
	extern CSUI_API const Type LogManagerWidgetActorScopedTimerDeallocate;
	extern CSUI_API const Type LogManagerWidgetActorScopedTimerDeallocateObject;
	extern CSUI_API const Type LogManagerWidgetActorScopedTimerSpawn;
	extern CSUI_API const Type LogManagerWidgetActorScopedTimerDestroy;

	namespace Map
	{
		extern CSUI_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerWidgetActorTransactions);
		// Scoped Timer
		extern CSUI_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerWidgetActorScopedTimer);
		extern CSUI_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerWidgetActorScopedTimerCreatePool);
		extern CSUI_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerWidgetActorScopedTimerUpdate);
		extern CSUI_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerWidgetActorScopedTimerUpdateObject);
		extern CSUI_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerWidgetActorScopedTimerAllocate);
		extern CSUI_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerWidgetActorScopedTimerAllocateObject);
		extern CSUI_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerWidgetActorScopedTimerDeallocate);
		extern CSUI_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerWidgetActorScopedTimerDeallocateObject);
		extern CSUI_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerWidgetActorScopedTimerSpawn);
		extern CSUI_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerWidgetActorScopedTimerDestroy);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	extern CSUI_API const Type ManagerWidgetActor;

	namespace Map
	{
		extern CSUI_API CS_DECLARE_ADD_TO_CVAR_MAP(ManagerWidgetActor);
	}
}

#pragma endregion ScopedGroup
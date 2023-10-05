// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CsCVars.h"

extern CSUI_API TAutoConsoleVariable<int32> CsCVarLogManagerUserWidgetTransactions;
// Scoped Timers
extern CSUI_API TAutoConsoleVariable<int32> CsCVarLogManagerUserWidgetScopedTimer;
extern CSUI_API TAutoConsoleVariable<int32> CsCVarLogManagerUserWidgetScopedTimerCreatePool;
extern CSUI_API TAutoConsoleVariable<int32> CsCVarLogManagerUserWidgetScopedTimerUpdate;
extern CSUI_API TAutoConsoleVariable<int32> CsCVarLogManagerUserWidgetScopedTimerUpdateObject;
extern CSUI_API TAutoConsoleVariable<int32> CsCVarLogManagerUserWidgetScopedTimerAllocate;
extern CSUI_API TAutoConsoleVariable<int32> CsCVarLogManagerUserWidgetScopedTimerAllocateObject;
extern CSUI_API TAutoConsoleVariable<int32> CsCVarLogManagerUserWidgetScopedTimerDeallocate;
extern CSUI_API TAutoConsoleVariable<int32> CsCVarLogManagerUserWidgetScopedTimerDeallocateObject;
extern CSUI_API TAutoConsoleVariable<int32> CsCVarLogManagerUserWidgetScopedTimerSpawn;
extern CSUI_API TAutoConsoleVariable<int32> CsCVarLogManagerUserWidgetScopedTimerDestroy;

// CVarLog
#pragma region

namespace NCsCVarLog
{
	extern CSUI_API const Type LogManagerUserWidgetTransactions;
	// Scoped Timer
	extern CSUI_API const Type LogManagerUserWidgetScopedTimer;
	extern CSUI_API const Type LogManagerUserWidgetScopedTimerCreatePool;
	extern CSUI_API const Type LogManagerUserWidgetScopedTimerUpdate;
	extern CSUI_API const Type LogManagerUserWidgetScopedTimerUpdateObject;
	extern CSUI_API const Type LogManagerUserWidgetScopedTimerAllocate;
	extern CSUI_API const Type LogManagerUserWidgetScopedTimerAllocateObject;
	extern CSUI_API const Type LogManagerUserWidgetScopedTimerDeallocate;
	extern CSUI_API const Type LogManagerUserWidgetScopedTimerDeallocateObject;
	extern CSUI_API const Type LogManagerUserWidgetScopedTimerSpawn;
	extern CSUI_API const Type LogManagerUserWidgetScopedTimerDestroy;

	namespace Map
	{
		extern CSUI_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerUserWidgetTransactions);
		// Scoped Timer
		extern CSUI_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerUserWidgetScopedTimer);
		extern CSUI_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerUserWidgetScopedTimerCreatePool);
		extern CSUI_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerUserWidgetScopedTimerUpdate);
		extern CSUI_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerUserWidgetScopedTimerUpdateObject);
		extern CSUI_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerUserWidgetScopedTimerAllocate);
		extern CSUI_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerUserWidgetScopedTimerAllocateObject);
		extern CSUI_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerUserWidgetScopedTimerDeallocate);
		extern CSUI_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerUserWidgetScopedTimerDeallocateObject);
		extern CSUI_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerUserWidgetScopedTimerSpawn);
		extern CSUI_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerUserWidgetScopedTimerDestroy);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	extern CSUI_API const Type ManagerUserWidget;

	namespace Map
	{
		extern CSUI_API CS_DECLARE_ADD_TO_CVAR_MAP(ManagerUserWidget);
	}
}

#pragma endregion ScopedGroup
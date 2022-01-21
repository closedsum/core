// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/UserWidget/CsCVars_Manager_UserWidget.h"

TAutoConsoleVariable<int32> CsCVarLogManagerUserWidgetTransactions(
	TEXT("log.manager.userwidget.transactions"),
	0,
	TEXT("Log Manager UserWidget Allocation and DeAllocation."),
	ECVF_SetByConsole
);

// Scoped Timer

TAutoConsoleVariable<int32> CsCVarLogManagerUserWidgetScopedTimer(
	TEXT("log.manager.userwidget.scopedtimer"),
	0,
	TEXT("Log Manager UserWidget Scoped Timer."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerUserWidgetScopedTimerCreatePool(
	TEXT("log.manager.userwidget.scopedtimer.createpool"),
	0,
	TEXT("Log Manager UserWidget Scoped Timer Create Pool."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerUserWidgetScopedTimerUpdate(
	TEXT("log.manager.userwidget.scopedtimer.update"),
	0,
	TEXT("Log Manager UserWidget Scoped Timer Update."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerUserWidgetScopedTimerUpdateObject(
	TEXT("log.manager.userwidget.scopedtimer.updateobject"),
	0,
	TEXT("Log Manager UserWidget Scoped Timer Update Object."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerUserWidgetScopedTimerAllocate(
	TEXT("log.manager.userwidget.scopedtimer.allocate"),
	0,
	TEXT("Log Manager UserWidget Scoped Timer Allocate."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerUserWidgetScopedTimerAllocateObject(
	TEXT("log.manager.userwidget.scopedtimer.allocateobject"),
	0,
	TEXT("Log Manager UserWidget Scoped Timer Allocate Object."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerUserWidgetScopedTimerDeallocate(
	TEXT("log.manager.userwidget.scopedtimer.deallocate"),
	0,
	TEXT("Log Manager UserWidget Scoped Timer Deallocate."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerUserWidgetScopedTimerDeallocateObject(
	TEXT("log.manager.userwidget.scopedtimer.deallocateobject"),
	0,
	TEXT("Log Manager UserWidget Scoped Timer Deallocate Object."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerUserWidgetScopedTimerSpawn(
	TEXT("log.manager.userwidget.scopedtimer.spawn"),
	0,
	TEXT("Log Manager UserWidget Scoped Timer Spawn."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerUserWidgetScopedTimerDestroy(
	TEXT("log.manager.userwidget.scopedtimer.destroy"),
	0, 
	TEXT("Log Manager UserWidget Scoped Timer Destroy."),
	ECVF_SetByConsole
);

// CVarLog
#pragma region

namespace NCsCVarLog
{
	CSUI_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerUserWidgetTransactions, "Log Manager UserWidget Transactions");
	// Scoped Timer
	CSUI_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerUserWidgetScopedTimer, "Log Manager UserWidget Scoped Timer");
	CSUI_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerUserWidgetScopedTimerCreatePool, "Log Manager UserWidget Scoped Timer Create Pool");
	CSUI_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerUserWidgetScopedTimerUpdate, "Log Manager UserWidget Scoped Timer Update");
	CSUI_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerUserWidgetScopedTimerUpdateObject, "Log Manager UserWidget Scoped Timer Update Object");
	CSUI_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerUserWidgetScopedTimerAllocate, "Log Manager UserWidget Scoped Allocate");
	CSUI_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerUserWidgetScopedTimerAllocateObject, "Log Manager UserWidget Scoped Allocate Object");
	CSUI_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerUserWidgetScopedTimerDeallocate, "Log Manager UserWidget Scoped Timer Deallocate");
	CSUI_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerUserWidgetScopedTimerDeallocateObject, "Log Manager UserWidget Scoped Timer Deallocate Object");
	CSUI_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerUserWidgetScopedTimerSpawn, "Log Manager UserWidget Scoped Timer Spawn");
	CSUI_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerUserWidgetScopedTimerDestroy, "Log Manager UserWidget Scoped Timer Destroy");


	namespace Map
	{
		CSUI_API CS_ADD_TO_CVAR_MAP(LogManagerUserWidgetTransactions, CsCVarLogManagerUserWidgetTransactions);
		// Scoped Timer
		CSUI_API CS_ADD_TO_CVAR_MAP(LogManagerUserWidgetScopedTimer, CsCVarLogManagerUserWidgetScopedTimer);
		CSUI_API CS_ADD_TO_CVAR_MAP(LogManagerUserWidgetScopedTimerCreatePool, CsCVarLogManagerUserWidgetScopedTimerCreatePool);
		CSUI_API CS_ADD_TO_CVAR_MAP(LogManagerUserWidgetScopedTimerUpdate, CsCVarLogManagerUserWidgetScopedTimerUpdate);
		CSUI_API CS_ADD_TO_CVAR_MAP(LogManagerUserWidgetScopedTimerUpdateObject, CsCVarLogManagerUserWidgetScopedTimerUpdateObject);
		CSUI_API CS_ADD_TO_CVAR_MAP(LogManagerUserWidgetScopedTimerAllocate, CsCVarLogManagerUserWidgetScopedTimerAllocate);
		CSUI_API CS_ADD_TO_CVAR_MAP(LogManagerUserWidgetScopedTimerAllocateObject, CsCVarLogManagerUserWidgetScopedTimerAllocateObject);
		CSUI_API CS_ADD_TO_CVAR_MAP(LogManagerUserWidgetScopedTimerDeallocate, CsCVarLogManagerUserWidgetScopedTimerDeallocate);
		CSUI_API CS_ADD_TO_CVAR_MAP(LogManagerUserWidgetScopedTimerDeallocateObject, CsCVarLogManagerUserWidgetScopedTimerDeallocateObject);
		CSUI_API CS_ADD_TO_CVAR_MAP(LogManagerUserWidgetScopedTimerSpawn, CsCVarLogManagerUserWidgetScopedTimerSpawn);
		CSUI_API CS_ADD_TO_CVAR_MAP(LogManagerUserWidgetScopedTimerDestroy, CsCVarLogManagerUserWidgetScopedTimerDestroy);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	CSUI_API CS_CREATE_ENUM_STRUCT_CUSTOM(ManagerUserWidget, "Manager UserWidget");

	namespace Map
	{
		extern CSUI_API CS_ADD_TO_CVAR_MAP(ManagerUserWidget, CsCVarLogManagerUserWidgetScopedTimer);
	}
}

#pragma endregion ScopedGroup
// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Data/CsCVars_Manager_Data.h"

// Managers
#pragma region

TAutoConsoleVariable<int32> CsCVarManagerDataLoadAsyncOrder(
	TEXT("manager.data.loadasyncorder"),
	2,
	TEXT("Manager Data Load Async Order. None = 0, FirstToLast = 1, Bulk = 2. Default is Bulk. See ECsLoadAsyncOrder."),
	ECVF_SetByConsole
);

#pragma endregion Managers
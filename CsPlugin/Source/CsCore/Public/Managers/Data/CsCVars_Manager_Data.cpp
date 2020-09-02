// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "CsCVars_Manager_Data.h"

// Managers
#pragma region

TAutoConsoleVariable<int32> CsCVarManagerDataLoadAsyncOrder(
	TEXT("manager.data.loadasyncorder"),
	2,
	TEXT("Manager Data Load Async Order. None = 0, FirstToLast = 1, Bulk = 2. Default is Bulk. See ECsLoadAsyncOrder."),
	ECVF_SetByConsole
);

#pragma endregion Managers
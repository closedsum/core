// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Widget/CsCVars_Manager_Widget.h"

	// Widget
#pragma region

TAutoConsoleVariable<int32> CsCVarLogManagerWidgetTransactions(
	TEXT("log.manager.widget.transactions"),
	0,
	TEXT("Log Manager Widget Allocation and DeAllocation."),
	ECVF_SetByConsole
);

#pragma endregion Widget

// CVarLog
#pragma region

namespace NCsCVarLog
{
	// Managers

	CSCOREDEPRECATED_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogManagerWidgetTransactions);

	namespace Map
	{
		// Managers

			// Widget
	}
}

#pragma endregion CVarLog
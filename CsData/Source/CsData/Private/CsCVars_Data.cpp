// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "CsCVars_Data.h"

// Payload
#pragma region

TAutoConsoleVariable<int32> CsCVarLogPayloadPopulate(
	TEXT("log.payload.populate"),
	1,
	TEXT("Log Payload Populate."),
	ECVF_SetByConsole
);

#pragma endregion Payload

// Data
#pragma region

TAutoConsoleVariable<int32> CsCVarLogDataEntryPopulate(
	TEXT("log.data.entry.populate"),
	1,
	TEXT("Log Data Entry Populate."),
	ECVF_SetByConsole
);

#pragma endregion Data

// CVarLog
#pragma region

namespace NCsCVarLog
{
	// Payload
	CSDATA_API CS_CREATE_ENUM_STRUCT(LogPayloadPopulate);
	// Data
	CSDATA_API CS_CREATE_ENUM_STRUCT(LogDataEntryPopulate);

	namespace Map
	{
		// Payload
		CSDATA_API CS_ADD_TO_CVAR_MAP(LogPayloadPopulate, CsCVarLogPayloadPopulate);
		// Data
		CSDATA_API CS_ADD_TO_CVAR_MAP(LogDataEntryPopulate, CsCVarLogDataEntryPopulate);
	}
}

#pragma endregion CVarLog
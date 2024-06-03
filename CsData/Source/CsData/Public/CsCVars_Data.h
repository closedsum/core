// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CsCVars.h"


// Payload
#pragma region

extern CSDATA_API TAutoConsoleVariable<int32> CsCVarLogPayloadPopulate;

#pragma endregion Payload

// Data
#pragma region

extern CSDATA_API TAutoConsoleVariable<int32> CsCVarLogDataEntryPopulate;

#pragma endregion Data

namespace NCsCVarLog
{
	// Payload
	extern CSDATA_API const Type LogPayloadPopulate;
	// Data
	extern CSDATA_API const Type LogDataEntryPopulate;

	namespace Map
	{
		// Payload
		extern CSDATA_API CS_DECLARE_ADD_TO_CVAR_MAP(LogPayloadPopulate);
		// Data
		extern CSDATA_API CS_DECLARE_ADD_TO_CVAR_MAP(LogDataEntryPopulate);
	}
}
// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CsCVars.h"

extern CSPLATFORMPROCESS_API TAutoConsoleVariable<int32> CsCVarLogManagerProcessTransactions;
extern CSPLATFORMPROCESS_API TAutoConsoleVariable<int32> CsCVarLogProcessIO;

namespace NCsCVarLog
{
	// Process
	extern CSPLATFORMPROCESS_API const Type LogManagerProcessTransactions;
	extern CSPLATFORMPROCESS_API const Type LogProcessIO;

	namespace Map
	{
	}
}
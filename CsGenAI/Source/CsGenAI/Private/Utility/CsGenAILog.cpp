// Copyright 2017-2025 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Utility/CsGenAILog.h"
#include "CsGenAI.h"

namespace NCsGenAI
{
	void FLog::Warning(const FString& Str)
	{
		UE_LOG(LogCsGenAI, Warning, TEXT("%s"), *Str);
	}

	void FLog::Error(const FString& Str)
	{
		UE_LOG(LogCsGenAI, Error, TEXT("%s"), *Str);
	}
}

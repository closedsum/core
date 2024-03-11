// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Utility/CsPerformanceLog.h"
#include "CsPerformance.h"

namespace NCsPerformance
{
	void FLog::Warning(const FString& Str)
	{
		UE_LOG(LogCsPerformance, Warning, TEXT("%s"), *Str);
	}

	void FLog::Error(const FString& Str)
	{
		UE_LOG(LogCsPerformance, Error, TEXT("%s"), *Str);
	}
}

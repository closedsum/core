// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Utility/CsTimeLog.h"

namespace NCsTime
{
	void FLog::Warning(const FString& Str)
	{
		UE_LOG(LogCsTime, Warning, TEXT("%s"), *Str);
	}

	void FLog::Error(const FString& Str)
	{
		UE_LOG(LogCsTime, Error, TEXT("%s"), *Str);
	}
}
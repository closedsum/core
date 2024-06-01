// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Utility/CsLoadLog.h"
#include "CsLoad.h"

namespace NCsLoad
{
	void FLog::Warning(const FString& Str)
	{
		UE_LOG(LogCsLoad, Warning, TEXT("%s"), *Str);
	}

	void FLog::Error(const FString& Str)
	{
		UE_LOG(LogCsLoad, Error, TEXT("%s"), *Str);
	}
}
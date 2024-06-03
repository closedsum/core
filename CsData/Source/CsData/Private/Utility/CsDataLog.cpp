// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Utility/CsDataLog.h"
#include "CsData.h"

namespace NCsData
{
	void FLog::Warning(const FString& Str)
	{
		UE_LOG(LogCsData, Warning, TEXT("%s"), *Str);
	}

	void FLog::Error(const FString& Str)
	{
		UE_LOG(LogCsData, Error, TEXT("%s"), *Str);
	}
}
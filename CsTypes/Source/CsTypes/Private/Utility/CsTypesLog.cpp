// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Utility/CsTypesLog.h"
#include "CsTypes.h"

namespace NCsTypes
{
	void FLog::Warning(const FString& Str)
	{
		UE_LOG(LogCsTypes, Warning, TEXT("%s"), *Str);
	}

	void FLog::Error(const FString& Str)
	{
		UE_LOG(LogCsTypes, Error, TEXT("%s"), *Str);
	}
}
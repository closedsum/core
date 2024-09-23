// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Utility/CsPIELog.h"
#include "CsPIE.h"

namespace NCsPIE
{
	void FLog::Warning(const FString& Str)
	{
		UE_LOG(LogCsPIE, Warning, TEXT("%s"), *Str);
	}

	void FLog::Error(const FString& Str)
	{
		UE_LOG(LogCsPIE, Error, TEXT("%s"), *Str);
	}
}
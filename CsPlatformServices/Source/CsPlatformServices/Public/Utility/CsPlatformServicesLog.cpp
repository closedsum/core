// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Utility/CsPlatformServicesLog.h"
#include "CsPlatformServices.h"

void FCsPlatformServicesLog::Warning(const FString& Str)
{
	UE_LOG(LogCsPlatformServices, Warning, TEXT("%s"), *Str);
}

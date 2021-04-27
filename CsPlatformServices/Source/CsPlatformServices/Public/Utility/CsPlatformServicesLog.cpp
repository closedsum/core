// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Utility/CsPlatformServicesLog.h"
#include "CsPlatformServices.h"

void FCsPlatformServicesLog::Warning(const FString& Str)
{
	UE_LOG(LogCsPlatformServices, Warning, TEXT("%s"), *Str);
}

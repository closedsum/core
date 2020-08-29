// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Utility/CsWpLog.h"
#include "CsWp.h"

void FCsWpLog::Warning(const FString& Str)
{
	UE_LOG(LogCsWp, Warning, TEXT("%s"), *Str);
}

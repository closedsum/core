// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Utility/CsLog.h"
#include "CsCore.h"

void FCsLog::Warning(const FString& Str)
{
	UE_LOG(LogCs, Warning, TEXT("%s"), *Str);
}

// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Utility/CsPrjLog.h"
#include "CsPrj.h"

void FCsPrjLog::Warning(const FString& Str)
{
	UE_LOG(LogCsPrj, Warning, TEXT("%s"), *Str);
}

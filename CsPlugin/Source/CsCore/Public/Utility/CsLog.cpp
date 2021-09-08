// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Utility/CsLog.h"
#include "CsCore.h"

void FCsLog::Warning(const FString& Str)
{
	UE_LOG(LogCs, Warning, TEXT("%s"), *Str);
}

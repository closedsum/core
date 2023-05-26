// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Utility/CsSeLog.h"
#include "CsSe.h"

namespace NCsStatusEffect
{
	void FLog::Warning(const FString& Str)
	{
		UE_LOG(LogCsSe, Warning, TEXT("%s"), *Str);
	}
}

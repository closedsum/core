// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Utility/CsAILog.h"
#include "CsAI.h"

namespace NCsAI
{
	void FLog::Warning(const FString& Str)
	{
		UE_LOG(LogCsAI, Warning, TEXT("%s"), *Str);
	}
}

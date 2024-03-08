// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Utility/CsPlaybackLog.h"
#include "CsPlayback.h"

namespace NCsPlayback
{
	void FLog::Warning(const FString& Str)
	{
		UE_LOG(LogCsPlayback, Warning, TEXT("%s"), *Str);
	}
}

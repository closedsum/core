// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Utility/CsPlaybackLog.h"
#include "CsPlayback.h"

namespace NCsPlayback
{
	void FLog::Warning(const FString& Str)
	{
		UE_LOG(LogCsPlayback, Warning, TEXT("%s"), *Str);
	}
}

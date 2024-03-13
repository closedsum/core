// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Utility/CsSoundLog.h"
#include "CsSound.h"

namespace NCsSound
{
	void FLog::Warning(const FString& Str)
	{
		UE_LOG(LogCsSound, Warning, TEXT("%s"), *Str);
	}

	void FLog::Error(const FString& Str)
	{
		UE_LOG(LogCsSound, Error, TEXT("%s"), *Str);
	}
}
// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Utility/CsBeamLog.h"
#include "CsBeam.h"

namespace NCsBeam
{
	void FLog::Warning(const FString& Str)
	{
		UE_LOG(LogCsBeam, Warning, TEXT("%s"), *Str);
	}
}

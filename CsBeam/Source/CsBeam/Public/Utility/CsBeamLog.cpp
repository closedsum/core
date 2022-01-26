// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Utility/CsBeamLog.h"
#include "CsBeam.h"

namespace NCsBeam
{
	void FLog::Warning(const FString& Str)
	{
		UE_LOG(LogCsBeam, Warning, TEXT("%s"), *Str);
	}
}

// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Utility/CsInteractiveLog.h"
#include "CsInteractive.h"

namespace NCsInteractive
{
	void FLog::Warning(const FString& Str)
	{
		UE_LOG(LogCsInteractive, Warning, TEXT("%s"), *Str);
	}
}

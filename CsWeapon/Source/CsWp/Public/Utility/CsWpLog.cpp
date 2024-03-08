// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Utility/CsWpLog.h"
#include "CsWp.h"

namespace NCsWeapon
{
	void FLog::Warning(const FString& Str)
	{
		UE_LOG(LogCsWp, Warning, TEXT("%s"), *Str);
	}
}

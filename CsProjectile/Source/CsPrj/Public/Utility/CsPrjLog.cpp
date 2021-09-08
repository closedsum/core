// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Utility/CsPrjLog.h"
#include "CsPrj.h"

namespace NCsProjectile
{
	void FLog::Warning(const FString& Str)
	{
		UE_LOG(LogCsPrj, Warning, TEXT("%s"), *Str);
	}
}

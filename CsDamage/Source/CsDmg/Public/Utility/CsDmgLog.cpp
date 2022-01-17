// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Utility/CsDmgLog.h"
#include "CsDmg.h"

namespace NCsDamage
{
	void FLog::Warning(const FString& Str)
	{
		UE_LOG(LogCsDmg, Warning, TEXT("%s"), *Str);
	}
}

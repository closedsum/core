// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Utility/CsUILog.h"
#include "CsUI.h"

namespace NCsUI
{
	void FLog::Warning(const FString& Str)
	{
		UE_LOG(LogCsUI, Warning, TEXT("%s"), *Str);
	}
}

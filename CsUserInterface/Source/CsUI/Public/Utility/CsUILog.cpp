// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Utility/CsUILog.h"
#include "CsUI.h"

namespace NCsUI
{
	void FLog::Warning(const FString& Str)
	{
		UE_LOG(LogCsUI, Warning, TEXT("%s"), *Str);
	}

	void FLog::Error(const FString& Str)
	{
		UE_LOG(LogCsUI, Error, TEXT("%s"), *Str);
	}
}

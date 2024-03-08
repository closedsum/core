// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Utility/CsPlatformProcessLog.h"
#include "CsPlatformProcess.h"

namespace NCsUI
{
	namespace NCore
	{
		void FLog::Warning(const FString& Str)
		{
			UE_LOG(LogCsPlatformProcess, Warning, TEXT("%s"), *Str);
		}

		void FLog::Error(const FString& Str)
		{
			UE_LOG(LogCsPlatformProcess, Error, TEXT("%s"), *Str);
		}
	}
}

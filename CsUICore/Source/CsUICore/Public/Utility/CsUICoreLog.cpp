// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Utility/CsUICoreLog.h"
#include "CsUICore.h"

namespace NCsUI
{
	namespace NCore
	{
		void FLog::Warning(const FString& Str)
		{
			UE_LOG(LogCsUICore, Warning, TEXT("%s"), *Str);
		}

		void FLog::Error(const FString& Str)
		{
			UE_LOG(LogCsUICore, Error, TEXT("%s"), *Str);
		}
	}
}

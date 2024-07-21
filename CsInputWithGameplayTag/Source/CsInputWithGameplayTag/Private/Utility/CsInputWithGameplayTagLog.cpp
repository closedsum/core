// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Utility/CsInputWithGameplayTagLog.h"
#include "CsInputWithGameplayTag.h"

namespace NCsInput
{
	namespace NWithGameplayTag
	{
		void FLog::Warning(const FString& Str)
		{
			UE_LOG(LogCsInputWithGameplayTag, Warning, TEXT("%s"), *Str);
		}

		void FLog::Error(const FString& Str)
		{
			UE_LOG(LogCsInputWithGameplayTag, Error, TEXT("%s"), *Str);
		}
	}
}
// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Utility/CsCoreLibraryLog.h"
#include "CsCoreLibrary.h"

namespace NCsCore
{
	namespace NLibrary
	{
		void FLog::Warning(const FString& Str)
		{
			UE_LOG(LogCsCoreLibrary, Warning, TEXT("%s"), *Str);
		}

		void FLog::Error(const FString& Str)
		{
			UE_LOG(LogCsCoreLibrary, Error, TEXT("%s"), *Str);
		}
	}
}
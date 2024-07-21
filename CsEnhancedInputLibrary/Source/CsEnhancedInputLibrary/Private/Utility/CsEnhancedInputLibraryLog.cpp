// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Utility/CsEnhancedInputLibraryLog.h"
#include "CsEnhancedInputLibrary.h"

namespace NCsInput
{
	namespace NEnhanced
	{
		namespace NLibrary
		{
			void FLog::Warning(const FString& Str)
			{
				UE_LOG(LogCsEnhancedInputLibrary, Warning, TEXT("%s"), *Str);
			}

			void FLog::Error(const FString& Str)
			{
				UE_LOG(LogCsEnhancedInputLibrary, Error, TEXT("%s"), *Str);
			}
		}
	}
}
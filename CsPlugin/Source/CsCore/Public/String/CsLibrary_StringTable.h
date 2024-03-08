// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Internationalization/TextKey.h"
// Log
#include "Utility/CsLog.h"

class UStringTable;

namespace NCsString
{
	namespace NTable
	{
		/**
		* Library for interacting with a UStringTable
		*/
		struct CSCORE_API FLibrary
		{
		#define LogWarning void(*Log)(const FString&) = &FCsLog::Warning

		public:

			static bool SetSafeSourceString(const FString& Context, UStringTable* StringTable, const FTextKey& InKey, const FString& InSourceString, LogWarning);

		#undef LogWarning
		};
	}
}
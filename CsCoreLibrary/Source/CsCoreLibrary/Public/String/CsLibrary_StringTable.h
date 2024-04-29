// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Internationalization/TextKey.h"
// Log
#include "Utility/CsCoreLibraryLog.h"

class UStringTable;

namespace NCsString
{
	namespace NTable
	{
		/**
		* Library for interacting with a UStringTable
		*/
		struct CSCORELIBRARY_API FLibrary
		{
		#define LogLevel void(*Log)(const FString&) = &NCsCore::NLibrary::FLog::Warning

		public:

			static bool SetSafeSourceString(const FString& Context, UStringTable* StringTable, const FTextKey& InKey, const FString& InSourceString, LogLevel);

		#undef LogLevel
		};
	}
}
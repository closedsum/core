// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Log
#include "Utility/CsStartPlayLog.h"

class UObject;

namespace NCsStartPlay
{
	struct CSSTARTPLAY_API FLibrary
	{
	#define LogLevel void(*Log)(const FString&) = &NCsStartPlay::FLog::Warning

	public:

		static bool ImplementsChecked(const FString& Context, const UObject* Object);
		static bool ImplementsChecked(const FString& Context, const UObject* Object, bool& OutIsScript);

		static bool SafeImplements(const FString& Context, const UObject* Object, LogLevel);
		static bool SafeImplements(const FString& Context, const UObject* Object, bool& OutIsScript, LogLevel);

		static bool HasStartedPlayChecked(const FString& Context, const UObject* Object);
		static bool SafeHasStartedPlay(const FString& Context, const UObject* Object, LogLevel);

		static void StartPlayChecked(const FString& Context, UObject* Object);
		static void SafeStartPlay(const FString& Context, UObject* Object, LogLevel);

	#undef LogLevel
	};
}

using CsStartPlayLibrary = NCsStartPlay::FLibrary;
// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Log
#include "Utility/CsLog.h"

class UObject;

namespace NCsStartPlay
{
	struct CSCORE_API FLibrary
	{
	public:

		static bool ImplementsChecked(const FString& Context, const UObject* Object);
		static bool ImplementsChecked(const FString& Context, const UObject* Object, bool& OutIsScript);

		static bool SafeImplements(const FString& Context, const UObject* Object, void(*Log)(const FString&) = &FCsLog::Warning);
		static bool SafeImplements(const FString& Context, const UObject* Object, bool& OutIsScript, void(*Log)(const FString&) = &FCsLog::Warning);

		static bool HasStartedPlayChecked(const FString& Context, const UObject* Object);
		static bool SafeHasStartedPlay(const FString& Context, const UObject* Object, void(*Log)(const FString&) = &FCsLog::Warning);

		static void StartPlayChecked(const FString& Context, UObject* Object);
		static void SafeStartPlay(const FString& Context, UObject* Object, void(*Log)(const FString&) = &FCsLog::Warning);
	};
}
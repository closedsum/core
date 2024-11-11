// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CsMacro_Log.h"
// Log
#include "Utility/CsStartPlayLog.h"

class UObject;

namespace NCsStartPlay
{
	struct CSSTARTPLAY_API FLibrary
	{
	private:

		CS_DECLARE_STATIC_LOG_LEVEL

	public:

		static bool ImplementsChecked(const FString& Context, const UObject* Object);
		static bool ImplementsChecked(const FString& Context, const UObject* Object, bool& OutIsScript);

		static bool SafeImplements(const FString& Context, const UObject* Object, CS_FN_PARAM_DEFAULT_LOG_LEVEL);
		static bool SafeImplements(const FString& Context, const UObject* Object, bool& OutIsScript, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

		static bool HasStartedPlayChecked(const FString& Context, const UObject* Object);
		static bool SafeHasStartedPlay(const FString& Context, const UObject* Object, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

		static void StartPlayChecked(const FString& Context, UObject* Object);
		static void SafeStartPlay(const FString& Context, UObject* Object, CS_FN_PARAM_DEFAULT_LOG_LEVEL);
	};
}

using CsStartPlayLibrary = NCsStartPlay::FLibrary;
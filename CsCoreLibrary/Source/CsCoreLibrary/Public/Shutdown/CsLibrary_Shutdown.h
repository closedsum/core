// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Log
#include "Utility/CsCoreLibraryLog.h"

namespace NCsShutdown
{
	/**
	*/
	struct CSCORELIBRARY_API FLibrary
	{
	#define LogLevel void(*Log)(const FString&) = &NCsCore::NLibrary::FLog::Warning

	// Implement
	#pragma region
	public:

		static bool ImplementsChecked(const FString& Context, const UObject* Object);

		static bool SafeImplements(const FString& Context, const UObject* Object, LogLevel);

		static bool SafeImplements(const UObject* Object);

	#pragma endregion Implement

	// Shutdown
	#pragma region
	public:

		static bool SafeHasShutdown(const FString& Context, const UObject* Object, LogLevel);

		static bool SafeHasShutdown(const UObject* Object);

	#pragma endregion Shutdown

	#undef LogLevel
	};
}

using CsShutdownLibrary = NCsShutdown::FLibrary;
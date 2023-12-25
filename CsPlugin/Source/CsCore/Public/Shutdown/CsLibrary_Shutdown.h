// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Log
#include "Utility/CsLog.h"

namespace NCsShutdown
{
	/**
	*/
	struct CSCORE_API FLibrary
	{
	// Implement
	#pragma region
	public:

		static bool ImplementsChecked(const FString& Context, const UObject* Object);

		static bool SafeImplements(const FString& Context, const UObject* Object, void(*Log)(const FString&) = &FCsLog::Warning);

		static bool SafeImplements(const UObject* Object);

	#pragma endregion Implement

	// Shutdown
	#pragma region
	public:

		static bool SafeHasShutdown(const FString& Context, const UObject* Object, void(*Log)(const FString&) = &FCsLog::Warning);

		static bool SafeHasShutdown(const UObject* Object);

	#pragma endregion Shutdown
	};
}
// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Log
#include "Utility/CsPIELog.h"

class UObject;

namespace NCsPIE
{
	namespace NEvent
	{
		struct CSPIE_API FLibrary
		{
		#define LogLevel void(*Log)(const FString&) = &NCsPIE::FLog::Warning

		// Implements
		#pragma region
		public:

			static bool ImplementsChecked(const FString& Context, const UObject* Object);

			static bool SafeImplements(const FString& Context, const UObject* Object, LogLevel);

		#pragma endregion Implements

		#undef LogLevel
		};
	}
}

using CsPIEEventLibrary = NCsPIE::NEvent::FLibrary;
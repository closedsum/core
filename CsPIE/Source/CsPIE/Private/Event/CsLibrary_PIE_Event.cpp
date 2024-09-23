// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Event/CsLibrary_PIE_Event.h"

// Library
#include "Library/CsLibrary_Valid.h"
// PIE
#include "Event/CsPIE_Event.h"

namespace NCsPIE
{
	namespace NEvent
	{
		#define LogLevel void(*Log)(const FString&) /*=&NCsPIE::FLog::Warning*/

		// Implements
		#pragma region

		bool FLibrary::ImplementsChecked(const FString& Context, const UObject* Object)
		{
			CS_IMPLEMENTS_INTERFACE_CHECKED(Object, UObject, ICsPIE_Event);
			return true;
		}

		bool FLibrary::SafeImplements(const FString& Context, const UObject* Object, LogLevel)
		{
			CS_IMPLEMENTS_INTERFACE(Object, UObject, ICsPIE_Event)
			return true;
		}

		#pragma endregion Implements

		#undef LogLevel
	}
}
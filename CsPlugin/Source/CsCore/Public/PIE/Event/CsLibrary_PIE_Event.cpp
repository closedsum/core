// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "PIE/Event/CsLibrary_PIE_Event.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Valid.h"
// PIE
#include "PIE/Event/CsPIE_Event.h"

namespace NCsPIE
{
	namespace NEvent
	{
		// Implements
		#pragma region

		bool FLibrary::ImplementsChecked(const FString& Context, const UObject* Object)
		{
			CS_IMPLEMENTS_INTERFACE_CHECKED(Object, UObject, ICsPIE_Event);
			return true;
		}

		bool FLibrary::SafeImplements(const FString& Context, const UObject* Object, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			CS_IMPLEMENTS_INTERFACE(Object, UObject, ICsPIE_Event)
			return true;
		}

		#pragma endregion Implements
	}
}
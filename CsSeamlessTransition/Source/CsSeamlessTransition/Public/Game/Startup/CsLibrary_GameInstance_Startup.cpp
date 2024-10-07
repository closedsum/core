// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Game/Startup/CsLibrary_GameInstance_Startup.h"

// Library
#include "Game/CsLibrary_GameInstance.h"
#include "Library/CsLibrary_Valid.h"
// Game
#include "Game/Startup/CsGameInstance_Startup.h"

namespace NCsGameInstance
{
	namespace NStartup
	{
		#define LogLevel void(*Log)(const FString&) /*=&NCsSeamlessTransition::FLog::Warning*/

		// Interface
		#pragma region

		ICsGameInstance_Startup* FLibrary::GetInterfaceChecked(const FString& Context, const UObject* ContextObject)
		{
			UObject* GameInstance = CsGameInstanceLibrary::GetAsObjectChecked(Context, ContextObject);
			
			return CS_INTERFACE_CAST_CHECKED(GameInstance, UObject, ICsGameInstance_Startup);
		}

		ICsGameInstance_Startup* FLibrary::GetSafeInterface(const FString& Context, const UObject* ContextObject, LogLevel)
		{
			if (UObject* GameInstance = CsGameInstanceLibrary::GetSafeAsObject(Context, ContextObject, Log))
				return CS_INTERFACE_CAST(GameInstance, UObject, ICsGameInstance_Startup);
			return nullptr;
		}

		#pragma endregion Interface

		bool FLibrary::HasStartedFromEntryChecked(const FString& Context, const UObject* ContextObject)
		{
			return GetInterfaceChecked(Context, ContextObject)->HasStartedFromEntry();
		}

		bool FLibrary::SafeHasStartedFromEntry(const FString& Context, const UObject* ContextObject, LogLevel)
		{
			if (ICsGameInstance_Startup* Interface = GetSafeInterface(Context, ContextObject, Log))
				return Interface->HasStartedFromEntry();
			return false;
		}

		#undef LogLevel
	}
}
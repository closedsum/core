// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Game/Startup/CsLibrary_GameState_Startup.h"

// Library
#include "Game/CsLibrary_GameState.h"
#include "Library/CsLibrary_Valid.h"
// Game
#include "Game/Startup/CsGameState_Startup.h"

namespace NCsGameState
{
	namespace NStartup
	{
		#define LogLevel void(*Log)(const FString&) /*=&NCsSeamlessTransition::FLog::Warning*/

		// Interface
		#pragma region

		ICsGameState_Startup* FLibrary::GetInterfaceChecked(const FString& Context, const UObject* WorldContext)
		{
			UObject* GameState = CsGameStateLibrary::GetAsObjectChecked(Context, WorldContext);
			
			return CS_INTERFACE_CAST_CHECKED(GameState, UObject, ICsGameState_Startup);
		}

		ICsGameState_Startup* FLibrary::GetSafeInterface(const FString& Context, const UObject* WorldContext, LogLevel)
		{
			if (UObject* GameState = CsGameStateLibrary::GetSafeAsObject(Context, WorldContext, Log))
				return CS_INTERFACE_CAST(GameState, UObject, ICsGameState_Startup);
			return nullptr;
		}

		#pragma endregion Interface

		bool FLibrary::IsStartupCompleteChecked(const FString& Context, const UObject* WorldContext)
		{
			return GetInterfaceChecked(Context, WorldContext)->IsStartupComplete();
		}

		bool FLibrary::SafeIsStartupComplete(const FString& Context, const UObject* WorldContext, LogLevel)
		{
			if (ICsGameState_Startup* Interface = GetSafeInterface(Context, WorldContext, Log))
				return Interface->IsStartupComplete();
			return false;
		}

		#undef LogLevel
	}
}
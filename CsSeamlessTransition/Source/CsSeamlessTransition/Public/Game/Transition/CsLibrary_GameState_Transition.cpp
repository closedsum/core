// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Game/Transition/CsLibrary_GameState_Transition.h"

// Library
#include "Game/CsLibrary_GameState.h"
#include "Library/CsLibrary_Valid.h"
// Game
#include "Game/Transition/CsGameState_Transition.h"

namespace NCsGameState
{
	namespace NTransition
	{
		#define LogLevel void(*Log)(const FString&) /*=&NCsSeamlessTransition::FLog::Warning*/

		// Interface
		#pragma region

		ICsGameState_Transition* FLibrary::GetInterfaceChecked(const FString& Context, const UObject* WorldContext)
		{
			UObject* GameState = CsGameStateLibrary::GetAsObjectChecked(Context, WorldContext);
			
			return CS_INTERFACE_CAST_CHECKED(GameState, UObject, ICsGameState_Transition);
		}

		ICsGameState_Transition* FLibrary::GetSafeInterface(const FString& Context, const UObject* WorldContext, LogLevel)
		{
			if (UObject* GameState = CsGameStateLibrary::GetSafeAsObject(Context, WorldContext, Log))
				return CS_INTERFACE_CAST(GameState, UObject, ICsGameState_Transition);
			return nullptr;
		}

		#pragma endregion Interface

		bool FLibrary::HasFinishedTransitionOutChecked(const FString& Context, const UObject* WorldContext)
		{
			return GetInterfaceChecked(Context, WorldContext)->HasFinishedTransitionOut();
		}

		bool FLibrary::SafeHasFinishedTransitionOut(const FString& Context, const UObject* WorldContext, bool& OutSuccess, LogLevel)
		{
			OutSuccess = false;

			if (ICsGameState_Transition* Interface = GetSafeInterface(Context, WorldContext, Log))
			{
				OutSuccess = true;
				return Interface->HasFinishedTransitionOut();
			}
			return false;
		}

		void FLibrary::TransitionOutChecked(const FString& Context, const UObject* WorldContext)
		{
			GetInterfaceChecked(Context, WorldContext)->TransitionOut();
		}

		bool FLibrary::SafeTransitionOut(const FString& Context, const UObject* WorldContext, LogLevel)
		{
			if (ICsGameState_Transition* Interface = GetSafeInterface(Context, WorldContext, Log))
			{
				Interface->TransitionOut();
				return true;
			}
			return false;
		}

		#undef LogLevel
	}
}
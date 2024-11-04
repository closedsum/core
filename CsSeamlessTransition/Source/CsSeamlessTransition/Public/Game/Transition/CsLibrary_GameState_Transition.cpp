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
		using LogClassType = NCsSeamlessTransition::FLog;

		CS_DEFINE_STATIC_LOG_LEVEL(FLibrary, LogClassType::Warning);

		// Interface
		#pragma region

		ICsGameState_Transition* FLibrary::GetInterfaceChecked(const FString& Context, const UObject* WorldContext)
		{
			UObject* GameState = CsGameStateLibrary::GetAsObjectChecked(Context, WorldContext);
			
			return CS_INTERFACE_CAST_CHECKED(GameState, UObject, ICsGameState_Transition);
		}

		ICsGameState_Transition* FLibrary::GetSafeInterface(const FString& Context, const UObject* WorldContext, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
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

		bool FLibrary::SafeHasFinishedTransitionOut(const FString& Context, const UObject* WorldContext, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
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

		bool FLibrary::SafeTransitionOut(const FString& Context, const UObject* WorldContext, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			if (ICsGameState_Transition* Interface = GetSafeInterface(Context, WorldContext, Log))
			{
				Interface->TransitionOut();
				return true;
			}
			return false;
		}
	}
}
// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Game/CsLibrary_GameState_SeamlessTransition.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Game/CsLibrary_GameState.h"
#include "Library/CsLibrary_Valid.h"
// Game
#include "Game/CsGameState_SeamlessTransition.h"

namespace NCsGameState
{
	namespace NSeamlessTransition
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCGameState::NSeamlessTransition::FLibrary, GetSafeInterface);
				}
			}
		}

		#define LogLevel void(*Log)(const FString&) /*=&NCsSeamlessTransition::FLog::Warning*/

		// Interface
		#pragma region

		ICsGameState_SeamlessTransition* FLibrary::GetInterfaceChecked(const FString& Context, const UObject* WorldContext)
		{
			UObject* GameState = CsGameStateLibrary::GetAsObjectChecked(Context, WorldContext);

			return CS_INTERFACE_CAST_CHECKED(GameState, UObject, ICsGameState_SeamlessTransition);
		}

		ICsGameState_SeamlessTransition* FLibrary::GetSafeInterface(const FString& Context, const UObject* WorldContext, LogLevel)
		{
			if (UObject* GameState = CsGameStateLibrary::GetAsObjectChecked(Context, WorldContext))
				return CS_INTERFACE_CAST(GameState, UObject, ICsGameState_SeamlessTransition);
			return nullptr;
		}

		ICsGameState_SeamlessTransition* FLibrary::GetSafeInterface(const UObject* WorldContext)
		{
			using namespace NCsGameState::NSeamlessTransition::NLibrary::NCached;

			const FString& Context = Str::GetSafeInterface;

			return GetSafeInterface(Context, WorldContext, nullptr);
		}

		bool FLibrary::CanGetInterfaceChecked(const FString& Context, const UObject* WorldContext)
		{
			return GetInterfaceChecked(Context, WorldContext) != nullptr;
		}

		bool FLibrary::CanGetSafeInterface(const FString& Context, const UObject* WorldContext, LogLevel)
		{
			return GetSafeInterface(Context, WorldContext, Log) != nullptr;
		}

		#pragma endregion Interface

		void FLibrary::SeamlessTransition_TransitionOutChecked(const FString& Context, const UObject* WorldContext)
		{
			GetInterfaceChecked(Context, WorldContext)->SeamlessTransition_TransitionOut();
		}

		bool FLibrary::SeamlessTransition_Transition_IsTransitionOutCompleteChecked(const FString& Context, const UObject* WorldContext)
		{
			return GetInterfaceChecked(Context, WorldContext)->SeamlessTransition_Transition_IsTransitionOutComplete();
		}

		bool FLibrary::SeamlessTransition_Transition_IsStartupCompleteChecked(const FString& Context, const UObject* WorldContext)
		{
			return GetInterfaceChecked(Context, WorldContext)->SeamlessTransition_Transition_IsStartupComplete();
		}

		#undef LogLevel
	}
}
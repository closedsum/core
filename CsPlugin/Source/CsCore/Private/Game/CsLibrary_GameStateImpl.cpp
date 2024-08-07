// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Game/CsLibrary_GameStateImpl.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Game/CsLibrary_GameState.h"
#include "Library/CsLibrary_Valid.h"
// Game
#include "Game/Startup/CsGameState_Startup.h"
#include "Game/Transition/CsGameState_Transition.h"
#include "Game/ExitGame/CsGameState_ExitGame.h"
// World
#include "GameFramework/GameStateBase.h"

namespace NCsGameState
{
	namespace NImpl
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsGameState::NImpl::FLibrary, GetSafe);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsGameState::NImpl::FLibrary, GetSafeAsObject);
					// ICsGameState_ExitGame
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsGameState::NImpl::FLibrary, SafeHasFinishedExitGame);
				}
			}
		}

		#define USING_NS_CACHED using namespace NCsGameState::NImpl::NLibrary::NCached;
		#define SET_CONTEXT(__FunctionName) using namespace NCsGameState::NImpl::NLibrary::NCached; \
			const FString& Context = Str::__FunctionName
		#define LogLevel void(*Log)(const FString&) /*=&FCsLog::Warning*/

		FString FLibrary::PrintGameStateAndClass(AGameStateBase* GameState)
		{
			return FString::Printf(TEXT("GameState: %s with Class: %s"), *(GameState->GetName()), *(GameState->GetClass()->GetName()));
		}

		// ICsGameState_Startup
		#pragma region

		bool FLibrary::IsStartupCompleteChecked(const FString& Context, const UObject* WorldContext)
		{
			AGameStateBase* GameState		= CsGameStateLibrary::GetChecked(Context, WorldContext);
			ICsGameState_Startup* Interface = CS_INTERFACE_CAST_CHECKED(GameState, AGameStateBase, ICsGameState_Startup);

			return Interface->IsStartupComplete();
		}

		bool FLibrary::SafeIsStartupComplete(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			if (AGameStateBase* GameState = CsGameStateLibrary::GetSafe(Context, WorldContext, Log))
			{
				ICsGameState_Startup* Interface = CS_INTERFACE_CAST(GameState, AGameStateBase, ICsGameState_Startup);

				if (Interface)
					return Interface->IsStartupComplete();
				return false;
			}
			return false;
		}

		#pragma endregion ICsGameState_Startup

		// ICsGameState_Transition
		#pragma region

		bool FLibrary::HasFinishedTransitionOutChecked(const FString& Context, const UObject* WorldContext)
		{
			AGameStateBase* GameState		   = CsGameStateLibrary::GetChecked(Context, WorldContext);
			ICsGameState_Transition* Interface = CS_INTERFACE_CAST_CHECKED(GameState, AGameStateBase, ICsGameState_Transition);

			return Interface->HasFinishedTransitionOut();
		}

		void FLibrary::TransitionOutChecked(const FString& Context, const UObject* WorldContext)
		{
			AGameStateBase* GameState		   = CsGameStateLibrary::GetChecked(Context, WorldContext);
			ICsGameState_Transition* Interface = CS_INTERFACE_CAST_CHECKED(GameState, AGameStateBase, ICsGameState_Transition);

			Interface->TransitionOut();
		}

		#pragma endregion ICsGameState_Transition

		// ICsGameState_ExitGame
		#pragma region
		
		bool FLibrary::HasFinishedExitGameChecked(const FString& Context, const UObject* WorldContext)
		{
			AGameStateBase* GameState		 = CsGameStateLibrary::GetChecked(Context, WorldContext);
			ICsGameState_ExitGame* Interface = CS_INTERFACE_CAST_CHECKED(GameState, AGameStateBase, ICsGameState_ExitGame);

			return Interface->HasFinishedExitGame();
		}

		bool FLibrary::SafeHasFinishedExitGame(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			AGameStateBase* GameState = CsGameStateLibrary::GetSafe(Context, WorldContext, Log);

			if (!GameState)
				return true;

			ICsGameState_ExitGame* Interface = CS_INTERFACE_CAST(GameState, AGameStateBase, ICsGameState_ExitGame);

			if (!Interface)
				return true;
			return Interface->HasFinishedExitGame();
		}

		bool FLibrary::SafeHasFinishedExitGame(const UObject* WorldContext)
		{
			SET_CONTEXT(SafeHasFinishedExitGame);

			return SafeHasFinishedExitGame(Context, WorldContext, nullptr);
		}

		#pragma endregion ICsGameState_ExitGame

		#undef USING_NS_CACHED
		#undef SET_CONTEXT
		#undef LogLevel
	}
}
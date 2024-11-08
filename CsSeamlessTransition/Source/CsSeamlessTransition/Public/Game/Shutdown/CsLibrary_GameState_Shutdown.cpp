// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Game/Shutdown/CsLibrary_GameState_Shutdown.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Game/CsLibrary_GameState.h"
#include "Library/CsLibrary_Valid.h"
// Game
#include "Game/Shutdown/CsGameState_Shutdown.h"

namespace NCsGameState
{
	namespace NShutdown
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsGameState::NShutdown::FLibrary, SafeHasFinishedExitGame);
				}
			}
		}

		using LogClassType = NCsSeamlessTransition::FLog;

		CS_DEFINE_STATIC_LOG_LEVEL(FLibrary, LogClassType::Warning);

		#define USING_NS_CACHED using namespace NCsGameState::NShutdown::NLibrary::NCached;
		#define SET_CONTEXT(__FunctionName) using namespace NCsGameState::NShutdown::NLibrary::NCached; \
			const FString& Context = Str::__FunctionName

		// Interface
		#pragma region

		ICsGameState_Shutdown* FLibrary::GetInterfaceChecked(const FString& Context, const UObject* ContextObject)
		{
			UObject* GameState = CsGameStateLibrary::GetAsObjectChecked(Context, ContextObject);
			
			return CS_INTERFACE_CAST_CHECKED(GameState, UObject, ICsGameState_Shutdown);
		}

		ICsGameState_Shutdown* FLibrary::GetSafeInterface(const FString& Context, const UObject* ContextObject, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			if (UObject* GameState = CsGameStateLibrary::GetSafeAsObject(Context, ContextObject, Log))
				return CS_INTERFACE_CAST(GameState, UObject, ICsGameState_Shutdown);
			return nullptr;
		}

		#pragma endregion Interface


		bool FLibrary::HasFinishedExitGameChecked(const FString& Context, const UObject* WorldContext)
		{
			return GetInterfaceChecked(Context, WorldContext)->HasFinishedExitGame();
		}

		bool FLibrary::SafeHasFinishedExitGame(const FString& Context, const UObject* WorldContext, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			if (ICsGameState_Shutdown* Interface = GetSafeInterface(Context, WorldContext, Log))
				return Interface->HasFinishedExitGame();
			return false;
		}

		bool FLibrary::SafeHasFinishedExitGame(const UObject* WorldContext)
		{
			SET_CONTEXT(SafeHasFinishedExitGame);

			return SafeHasFinishedExitGame(Context, WorldContext, nullptr);
		}

		#undef USING_NS_CACHED
		#undef SET_CONTEXT
	}
}
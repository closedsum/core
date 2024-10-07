// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Game/CsLibrary_GameStateImpl.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Game/CsLibrary_GameState.h"
#include "Library/CsLibrary_Valid.h"
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

		#undef USING_NS_CACHED
		#undef SET_CONTEXT
		#undef LogLevel
	}
}
// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Game/Script/CsScriptLibrary_GameState.h"
#include "CsCore.h"

// CVar
#include "Script/CsCVars_Script.h"
// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Game/CsLibrary_GameState.h"

// Cached
#pragma region

namespace NCsScriptLibraryGameState
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_GameState, IsStartupComplete);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_GameState, IsStartupCompleteChecked);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_GameState::UCsScriptLibrary_GameState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define CLASS_TYPE UCsScriptLibrary_GameState
#define USING_NS_CACHED using namespace NCsScriptLibraryGameState::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryGameState::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::##__FunctionName : Context
#define LogError &FCsLog::Error
#define GameStateLibrary NCsGameState::FLibrary

// ICsGameState_Startup
#pragma region

bool CLASS_TYPE::IsStartupComplete(const FString& Context, const UObject* WorldContextObject)
{
	CONDITIONAL_SET_CTXT(IsStartupComplete);

	return GameStateLibrary::SafeIsStartupComplete(Ctxt, WorldContextObject);
}

bool CLASS_TYPE::IsStartupCompleteChecked(const FString& Context, const UObject* WorldContextObject, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(IsStartupCompleteChecked);

	OutSuccess = true;
	return CS_SCRIPT_GET_CHECKED(GameStateLibrary::IsStartupCompleteChecked(Ctxt, WorldContextObject), GameStateLibrary::SafeIsStartupComplete(Ctxt, WorldContextObject, OutSuccess, LogError));
}

#pragma endregion ICsGameState_Startup

#undef CLASS_TYPE
#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT
#undef LogError
#undef GameStateLibrary
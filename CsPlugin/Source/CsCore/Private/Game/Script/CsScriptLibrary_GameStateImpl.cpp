// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Game/Script/CsScriptLibrary_GameStateImpl.h"

// CVar
#include "Script/CsCVars_Script.h"
// Types
#include "CsMacro_Misc.h"
// Library
#include "Game/Startup/CsLibrary_GameState_Startup.h"
#include "Game/Transition/CsLibrary_GameState_Transition.h"
// Utility
#include "Utility/CsLog.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_GameStateImpl)

// Cached
#pragma region

namespace NCsScriptLibraryGameStateImpl
{
	namespace NCached
	{
		namespace Str
		{
			// ICsGameState_Startup
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_GameStateImpl, IsStartupComplete);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_GameStateImpl, IsStartupCompleteChecked);
			// ICsGameState_Transition
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_GameStateImpl, HasFinishedTransitionOut);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_GameStateImpl, TransitionOut);
		}
	}
}

#pragma endregion Cached

void(*UCsScriptLibrary_GameStateImpl::LogError)(const FString&) = &FCsLog::Error;

UCsScriptLibrary_GameStateImpl::UCsScriptLibrary_GameStateImpl(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define CLASS_TYPE UCsScriptLibrary_GameStateImpl
#define USING_NS_CACHED using namespace NCsScriptLibraryGameStateImpl::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryGameStateImpl::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context

// ICsGameState_Startup
#pragma region

bool CLASS_TYPE::IsStartupComplete(const FString& Context, const UObject* WorldContextObject)
{
	CONDITIONAL_SET_CTXT(IsStartupComplete);

	return CsGameStateStartupLibrary::SafeIsStartupComplete(Ctxt, WorldContextObject);
}

bool CLASS_TYPE::IsStartupCompleteChecked(const FString& Context, const UObject* WorldContextObject, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(IsStartupCompleteChecked);

	OutSuccess = true;
	return CS_SCRIPT_GET_CHECKED(CsGameStateStartupLibrary::IsStartupCompleteChecked(Ctxt, WorldContextObject), CsGameStateStartupLibrary::SafeIsStartupComplete(Ctxt, WorldContextObject, OutSuccess, LogError));
}

#pragma endregion ICsGameState_Startup

// ICsGameState_Transition
#pragma region

bool CLASS_TYPE::HasFinishedTransitionOut(const FString& Context, const UObject* WorldContextObject)
{
	CONDITIONAL_SET_CTXT(HasFinishedTransitionOut);

	return CsGameStateTransitionLibrary::SafeHasFinishedTransitionOut(Context, WorldContextObject);
}

bool CLASS_TYPE::TransitionOut(const FString& Context, const UObject* WorldContextObject)
{
	CONDITIONAL_SET_CTXT(TransitionOut);

	return CsGameStateTransitionLibrary::SafeTransitionOut(Context, WorldContextObject);
}

#pragma endregion ICsGameState_Transition

#undef CLASS_TYPE
#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT
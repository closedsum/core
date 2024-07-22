// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Game/Script/CsScriptLibrary_GameState.h"

// CVar
#include "Script/CsCVars_Script.h"
// Types
#include "CsMacro_Misc.h"
// Library
#include "Game/CsLibrary_GameState.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_GameState)

// Cached
#pragma region

namespace NCsScriptLibraryGameState
{
	namespace NCached
	{
		namespace Str
		{
			// Get
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_GameState, Get);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_GameState, GetChecked);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_GameState::UCsScriptLibrary_GameState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


#define USING_NS_CACHED using namespace NCsScriptLibraryGameState::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryGameState::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context
#define LogError &NCsCore::NLibrary::FLog::Error

AGameStateBase* UCsScriptLibrary_GameState::Get(const FString& Context, const UObject* WorldContextObject)
{
	CONDITIONAL_SET_CTXT(Get);

	return CsGameStateLibrary::GetSafe(Ctxt, WorldContextObject);
}

AGameStateBase* UCsScriptLibrary_GameState::GetChecked(const FString& Context, const UObject* WorldContextObject, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(GetChecked);

	OutSuccess = true;
	return CS_SCRIPT_GET_CHECKED(CsGameStateLibrary::GetChecked(Ctxt, WorldContextObject), CsGameStateLibrary::GetSafe(Ctxt, WorldContextObject, OutSuccess, LogError));
}

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT
#undef LogError
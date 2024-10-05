// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Player/Script/CsScriptLibrary_PlayerTransitionCache.h"

// CVar
#include "Script/CsCVars_Script.h"
// Types
#include "CsMacro_Misc.h"
// Library
#include "Player/CsLibrary_PlayerTransitionCache.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_PlayerTransitionCache)

// Cached
#pragma region

namespace NCsScriptLibraryPlayerTransitionCache
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_PlayerTransitionCache, Input_AddEvent);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_PlayerTransitionCache, Input_AddEventChecked);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_PlayerTransitionCache::UCsScriptLibrary_PlayerTransitionCache(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define USING_NS_CACHED using namespace NCsScriptLibraryPlayerTransitionCache::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryPlayerTransitionCache::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context
#define LogError &NCsSeamlessTransition::FLog::Error

bool UCsScriptLibrary_PlayerTransitionCache::Input_AddEvent(const FString& Context, const UObject* WorldContextObject, const FCsGameEventInfo& Info)
{
	CONDITIONAL_SET_CTXT(Input_AddEvent);

	return CsPlayerTransitionCacheLibray::Input_SafeAddEvent(Ctxt, WorldContextObject, Info);
}

void UCsScriptLibrary_PlayerTransitionCache::Input_AddEventChecked(const FString& Context, const UObject* WorldContextObject, const FCsGameEventInfo& Info, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(Input_AddEventChecked);

	OutSuccess = true;
	CS_SCRIPT_CHECKED(CsPlayerTransitionCacheLibray::Input_AddEventChecked(Ctxt, WorldContextObject, Info), CsPlayerTransitionCacheLibray::Input_SafeAddEvent(Ctxt, WorldContextObject, Info, OutSuccess, LogError));
}

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT
#undef LogError
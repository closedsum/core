// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Fade/Script/CsScriptLibrary_Manager_Fade.h"

// CVar
#include "Script/CsCVars_Script.h"
// Types
#include "CsMacro_Misc.h"
// Library
#include "Managers/Fade/CsLibrary_Manager_Fade.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_Manager_Fade)

// Cached
#pragma region

namespace NCsScriptLibraryManagerFade
{
	namespace NCached
	{
		namespace Str
		{
			// Get
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Fade, Get);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Fade, GetChecked);
			// Fade
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Fade, ClearFade);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Fade, ClearFadeChecked);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Fade, FadeClearToBlack);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Fade, FadeClearToBlackChecked);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Fade, FadeBlackToClear);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Fade, FadeBlackToClearChecked);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Fade, IsFadeActive);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Fade, IsFadeActiveChecked);
		}
	}
}

#pragma endregion Cached

void(*UCsScriptLibrary_Manager_Fade::LogError)(const FString&) = &NCsFade::FLog::Error;

UCsScriptLibrary_Manager_Fade::UCsScriptLibrary_Manager_Fade(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define USING_NS_CACHED using namespace NCsScriptLibraryManagerFade::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryManagerFade::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context

// Get
#pragma region

UCsManager_Fade* UCsScriptLibrary_Manager_Fade::Get(const FString& Context, const UObject* WorldContextObject)
{
	CONDITIONAL_SET_CTXT(Get);

	return CsFadeManagerLibrary::GetSafe(Ctxt, WorldContextObject);
}

UCsManager_Fade* UCsScriptLibrary_Manager_Fade::GetChecked(const FString& Context, const UObject* WorldContextObject, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(GetChecked);

	return CS_SCRIPT_LIBRARY_GET_CUSTOM_CHECKED_4(GetChecked, GetSafe, WorldContextObject);
}

#pragma endregion Get

bool UCsScriptLibrary_Manager_Fade::ClearFade(const FString& Context, const UObject* WorldContextObject)
{
	CONDITIONAL_SET_CTXT(ClearFade);

	return CsFadeManagerLibrary::SafeClearFade(Ctxt, WorldContextObject);
}

void UCsScriptLibrary_Manager_Fade::ClearFadeChecked(const FString& Context, const UObject* WorldContextObject, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(ClearFadeChecked);

	CS_SCRIPT_LIBRARY_CHECKED_4(ClearFade, WorldContextObject)
}

bool UCsScriptLibrary_Manager_Fade::FadeClearToBlack(const FString& Context, const UObject* WorldContextObject, const float& Time)
{
	CONDITIONAL_SET_CTXT(FadeClearToBlack);

	return CsFadeManagerLibrary::SafeFadeClearToBlack(Ctxt, WorldContextObject, Time);
}

void UCsScriptLibrary_Manager_Fade::FadeClearToBlackChecked(const FString& Context, const UObject* WorldContextObject, const float& Time, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(FadeClearToBlackChecked);

	CS_SCRIPT_LIBRARY_CHECKED_5(FadeClearToBlack, WorldContextObject, Time)
}

bool UCsScriptLibrary_Manager_Fade::FadeBlackToClear(const FString& Context, const UObject* WorldContextObject, const float& Time)
{
	CONDITIONAL_SET_CTXT(FadeBlackToClear);

	return CsFadeManagerLibrary::SafeFadeBlackToClear(Ctxt, WorldContextObject, Time);
}

void UCsScriptLibrary_Manager_Fade::FadeBlackToClearChecked(const FString& Context, const UObject* WorldContextObject, const float& Time, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(FadeBlackToClearChecked);

	CS_SCRIPT_LIBRARY_CHECKED_5(FadeBlackToClear, WorldContextObject, Time)
}

bool UCsScriptLibrary_Manager_Fade::IsFadeActive(const FString& Context, const UObject* WorldContextObject)
{
	CONDITIONAL_SET_CTXT(IsFadeActive);

	return CsFadeManagerLibrary::SafeIsFadeActive(Ctxt, WorldContextObject);
}

bool UCsScriptLibrary_Manager_Fade::IsFadeActiveChecked(const FString& Context, const UObject* WorldContextObject, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(IsFadeActiveChecked);

	OutSuccess = true;
	return CS_SCRIPT_LIBRARY_GET_CHECKED_4(IsFadeActive, WorldContextObject);
}

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT
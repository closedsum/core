// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Fade/Script/CsScriptLibrary_Manager_Fade.h"
#include "CsFade.h"

// CVar
#include "Script/CsCVars_Script.h"
// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Managers/Fade/CsLibrary_Manager_Fade.h"

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

UCsScriptLibrary_Manager_Fade::UCsScriptLibrary_Manager_Fade(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define USING_NS_CACHED using namespace NCsScriptLibraryManagerFade::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryManagerFade::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context
#define LogError &NCsFade::FLog::Error
#define FadeManagerLibrary NCsFade::NManager::FLibrary

// Get
#pragma region

UCsManager_Fade* UCsScriptLibrary_Manager_Fade::Get(const FString& Context, const UObject* WorldContextObject)
{
	CONDITIONAL_SET_CTXT(Get);

	return FadeManagerLibrary::GetSafe(Ctxt, WorldContextObject);
}

UCsManager_Fade* UCsScriptLibrary_Manager_Fade::GetChecked(const FString& Context, const UObject* WorldContextObject, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(GetChecked);

	return CS_SCRIPT_GET_CHECKED(FadeManagerLibrary::GetChecked(Ctxt, WorldContextObject), FadeManagerLibrary::GetSafe(Ctxt, WorldContextObject, OutSuccess, LogError));
}

#pragma endregion Get

bool UCsScriptLibrary_Manager_Fade::ClearFade(const FString& Context, const UObject* WorldContextObject)
{
	CONDITIONAL_SET_CTXT(ClearFade);

	return FadeManagerLibrary::SafeClearFade(Ctxt, WorldContextObject);
}

void UCsScriptLibrary_Manager_Fade::ClearFadeChecked(const FString& Context, const UObject* WorldContextObject, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(ClearFadeChecked);

	OutSuccess = true;
	CS_SCRIPT_CHECKED(FadeManagerLibrary::ClearFadeChecked(Ctxt, WorldContextObject), FadeManagerLibrary::SafeClearFade(Ctxt, WorldContextObject, OutSuccess, LogError))
}

bool UCsScriptLibrary_Manager_Fade::FadeClearToBlack(const FString& Context, const UObject* WorldContextObject, const float& Time)
{
	CONDITIONAL_SET_CTXT(FadeClearToBlack);

	return FadeManagerLibrary::SafeFadeClearToBlack(Ctxt, WorldContextObject, Time);
}

void UCsScriptLibrary_Manager_Fade::FadeClearToBlackChecked(const FString& Context, const UObject* WorldContextObject, const float& Time, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(FadeClearToBlackChecked);

	OutSuccess = true;
	CS_SCRIPT_CHECKED(FadeManagerLibrary::FadeClearToBlackChecked(Ctxt, WorldContextObject, Time), FadeManagerLibrary::SafeFadeClearToBlack(Ctxt, WorldContextObject, Time, OutSuccess, LogError))
}

bool UCsScriptLibrary_Manager_Fade::FadeBlackToClear(const FString& Context, const UObject* WorldContextObject, const float& Time)
{
	CONDITIONAL_SET_CTXT(FadeBlackToClear);

	return FadeManagerLibrary::SafeFadeBlackToClear(Ctxt, WorldContextObject, Time);
}

void UCsScriptLibrary_Manager_Fade::FadeBlackToClearChecked(const FString& Context, const UObject* WorldContextObject, const float& Time, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(FadeBlackToClearChecked);

	OutSuccess = true;
	CS_SCRIPT_CHECKED(FadeManagerLibrary::FadeBlackToClearChecked(Ctxt, WorldContextObject, Time), FadeManagerLibrary::SafeFadeBlackToClear(Ctxt, WorldContextObject, Time, OutSuccess, LogError))
}

bool UCsScriptLibrary_Manager_Fade::IsFadeActive(const FString& Context, const UObject* WorldContextObject)
{
	CONDITIONAL_SET_CTXT(IsFadeActive);

	return FadeManagerLibrary::SafeIsFadeActive(Ctxt, WorldContextObject);
}

bool UCsScriptLibrary_Manager_Fade::IsFadeActiveChecked(const FString& Context, const UObject* WorldContextObject, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(IsFadeActiveChecked);

	OutSuccess = true;
	return CS_SCRIPT_GET_CHECKED(FadeManagerLibrary::IsFadeActiveChecked(Ctxt, WorldContextObject), FadeManagerLibrary::SafeIsFadeActive(Ctxt, WorldContextObject, OutSuccess, LogError));
}

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT
#undef LogError
#undef FadeManagerLibrary
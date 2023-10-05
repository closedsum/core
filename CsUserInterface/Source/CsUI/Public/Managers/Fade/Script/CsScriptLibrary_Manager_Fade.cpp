// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Fade/Script/CsScriptLibrary_Manager_Fade.h"
#include "CsUI.h"

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
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Fade, FadeClearToBlack);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Fade, FadeBlackToClear);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Manager_Fade::UCsScriptLibrary_Manager_Fade(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define LogError &FCsLog::Error
#define FadeManagerLibrary NCsFade::NManager::FLibrary

// Get
#pragma region

UCsManager_Fade* UCsScriptLibrary_Manager_Fade::Get(const FString& Context, const UObject* WorldContextObject)
{
	using namespace NCsScriptLibraryManagerFade::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Get : Context;

	return FadeManagerLibrary::GetSafe(Ctxt, WorldContextObject);
}

UCsManager_Fade* UCsScriptLibrary_Manager_Fade::GetChecked(const FString& Context, const UObject* WorldContextObject, bool& OutSuccess)
{
	using namespace NCsScriptLibraryManagerFade::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Get : Context;

	return CS_SCRIPT_GET_CHECKED(FadeManagerLibrary::GetChecked(Ctxt, WorldContextObject), FadeManagerLibrary::GetSafe(Ctxt, WorldContextObject, OutSuccess, LogError));
}

#pragma endregion Get

bool UCsScriptLibrary_Manager_Fade::FadeClearToBlack(const FString& Context, const UObject* WorldContextObject, const float& Time)
{
	using namespace NCsScriptLibraryManagerFade::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::FadeClearToBlack : Context;

	return FadeManagerLibrary::SafeFadeClearToBlack(Ctxt, WorldContextObject, Time);
}

bool UCsScriptLibrary_Manager_Fade::FadeBlackToClear(const FString& Context, const UObject* WorldContextObject, const float& Time)
{
	using namespace NCsScriptLibraryManagerFade::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::FadeBlackToClear : Context;

	return FadeManagerLibrary::SafeFadeBlackToClear(Ctxt, WorldContextObject, Time);
}

#undef LogError
#undef FadeManagerLibrary
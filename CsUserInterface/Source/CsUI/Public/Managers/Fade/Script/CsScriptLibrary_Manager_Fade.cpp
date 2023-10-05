// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Fade/Script/CsScriptLibrary_Manager_Fade.h"
#include "CsUI.h"

// Library
#include "Managers/Fade/CsLibrary_Manager_Fade.h"
// Types
#include "Types/CsTypes_Macro.h"

// Cached
#pragma region

namespace NCsScriptLibraryManagerFade
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Fade, Get);
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

// Get
#pragma region

UCsManager_Fade* UCsScriptLibrary_Manager_Fade::Get(const FString& Context, const UObject* WorldContextObject)
{
	using namespace NCsScriptLibraryManagerFade::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Get : Context;

	typedef NCsFade::NManager::FLibrary FadeManagerLibrary;

	return FadeManagerLibrary::GetSafe(Ctxt, WorldContextObject);
}

#pragma endregion Get

bool UCsScriptLibrary_Manager_Fade::FadeClearToBlack(const FString& Context, const UObject* WorldContextObject, const float& Time)
{
	using namespace NCsScriptLibraryManagerFade::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::FadeClearToBlack : Context;

	typedef NCsFade::NManager::FLibrary FadeManagerLibrary;

	return FadeManagerLibrary::SafeFadeClearToBlack(Ctxt, WorldContextObject, Time);
}

bool UCsScriptLibrary_Manager_Fade::FadeBlackToClear(const FString& Context, const UObject* WorldContextObject, const float& Time)
{
	using namespace NCsScriptLibraryManagerFade::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::FadeBlackToClear : Context;

	typedef NCsFade::NManager::FLibrary FadeManagerLibrary;

	return FadeManagerLibrary::SafeFadeBlackToClear(Ctxt, WorldContextObject, Time);
}
// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Player/Script/CsScriptLibrary_PlayerController.h"

// CVar
#include "Script/CsCVars_Script.h"
// Types
#include "CsMacro_Misc.h"
// Library
#include "Player/CsLibrary_Player.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_PlayerController)

// Cached
#pragma region

namespace NCsScriptLibraryPlayerController
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_PlayerController, GetFirstLocal);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_PlayerController, GetFirstLocalChecked);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_PlayerController::UCsScriptLibrary_PlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define USING_NS_CACHED using namespace NCsScriptLibraryPlayerController::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryPlayerController::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context
#define LogError &NCsCore::NLibrary::FLog::Error

APlayerController* UCsScriptLibrary_PlayerController::GetFirstLocal(const FString& Context, const UObject* WorldContextObject)
{
	CONDITIONAL_SET_CTXT(GetFirstLocal);

	return CsPCFirstLocalLibrary::GetSafe(Ctxt, WorldContextObject);
}

APlayerController* UCsScriptLibrary_PlayerController::GetFirstLocalChecked(const FString& Context, const UObject* WorldContextObject, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(GetFirstLocalChecked);

	return CS_SCRIPT_GET_CHECKED(CsPCFirstLocalLibrary::GetChecked(Ctxt, WorldContextObject), CsPCFirstLocalLibrary::GetSafe(Ctxt, WorldContextObject, OutSuccess, LogError));
}

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT
#undef LogError
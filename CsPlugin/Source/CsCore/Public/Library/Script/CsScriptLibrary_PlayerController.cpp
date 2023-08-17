// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/Script/CsScriptLibrary_PlayerController.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Library/CsLibrary_Player.h"

// Cached
#pragma region

namespace NCsScriptLibraryPlayerController
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_PlayerController, GetFirstLocal);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_PlayerController::UCsScriptLibrary_PlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

APlayerController* UCsScriptLibrary_PlayerController::GetFirstLocal(const FString& Context, const UObject* WorldContextObject)
{
	using namespace NCsScriptLibraryPlayerController::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetFirstLocal : Context;

	typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

	return PlayerControllerLibrary::GetSafeFirstLocal(Ctxt, WorldContextObject);
}
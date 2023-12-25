// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Player/Script/CsScriptLibrary_PlayerCamera.h"
#include "CsCore.h"

// CVars
#include "Script/CsCVars_Script.h"
// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Player/CsLibrary_PlayerCamera.h"

// Cached
#pragma region

namespace NCsScriptLibraryPlayerCamera
{
	namespace NCached
	{
		namespace Str
		{
			// Get
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_PlayerCamera, Get);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_PlayerCamera, GetChecked);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_PlayerCamera, GetByPawn);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_PlayerCamera, GetByPawnChecked);
			// Orientation
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_PlayerCamera::UCsScriptLibrary_PlayerCamera(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define USING_NS_CACHED using namespace NCsScriptLibraryPlayerCamera::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryPlayerCamera::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::##__FunctionName : Context
#define LogError &FCsLog::Error
#define PlayerCameraLibrary NCsPlayer::NCamera::FLibrary

// Get
#pragma region

APlayerCameraManager* UCsScriptLibrary_PlayerCamera::Get(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId)
{
	CONDITIONAL_SET_CTXT(Get);

	return PlayerCameraLibrary::GetSafe(Ctxt, WorldContextObject, ControllerId);
}

APlayerCameraManager* UCsScriptLibrary_PlayerCamera::GetChecked(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(Get);

	OutSuccess = true;
	return CS_SCRIPT_GET_CHECKED(PlayerCameraLibrary::GetChecked(Ctxt, WorldContextObject, ControllerId), PlayerCameraLibrary::GetSafe(Ctxt, WorldContextObject, ControllerId, OutSuccess, LogError));
}

APlayerCameraManager* UCsScriptLibrary_PlayerCamera::GetByPawn(const FString& Context, const APawn* Pawn)
{
	CONDITIONAL_SET_CTXT(GetByPawn);

	return PlayerCameraLibrary::GetSafe(Ctxt, Pawn);
}

APlayerCameraManager* UCsScriptLibrary_PlayerCamera::GetByPawnChecked(const FString& Context, const APawn* Pawn, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(GetByPawnChecked);

	OutSuccess = true;
	return CS_SCRIPT_GET_CHECKED(PlayerCameraLibrary::GetChecked(Ctxt, Pawn), PlayerCameraLibrary::GetSafe(Ctxt, Pawn, OutSuccess, LogError));
}

#pragma endregion Get

// Orientation
#pragma region

#pragma endregion Orientation

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT
#undef LogError
#undef PlayerCameraLibrary
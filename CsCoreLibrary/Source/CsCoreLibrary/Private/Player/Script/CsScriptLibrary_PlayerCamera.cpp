// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Player/Script/CsScriptLibrary_PlayerCamera.h"

// CVars
#include "Script/CsCVars_Script.h"
// Types
#include "CsMacro_Misc.h"
// Library
#include "Player/CsLibrary_PlayerCamera.h"
// Log
#include "Utility/CsCoreLibraryLog.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_PlayerCamera)

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
			// View Target
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_PlayerCamera, SetViewTarget);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_PlayerCamera, SetViewTargetChecked);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_PlayerCamera, SetViewTargetByPawn);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_PlayerCamera, SetViewTargetByPawnChecked);
			// FOV
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_PlayerCamera, SetFOV);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_PlayerCamera, SetFOVChecked);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_PlayerCamera, SetFOVByPawn);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_PlayerCamera, SetFOVByPawnChecked);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_PlayerCamera, GetFOV);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_PlayerCamera, GetFOVChecked);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_PlayerCamera, GetFOVByPawn);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_PlayerCamera, GetFOVByPawnChecked);
			// View
				// Pitch
					// Min
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_PlayerCamera, SetViewPitchMin);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_PlayerCamera, SetViewPitchMinChecked);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_PlayerCamera, SetViewPitchMinByPawn);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_PlayerCamera, SetViewPitchMinByPawnChecked);
					// Max
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_PlayerCamera, SetViewPitchMax);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_PlayerCamera, SetViewPitchMaxChecked);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_PlayerCamera, SetViewPitchMaxByPawn);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_PlayerCamera, SetViewPitchMaxByPawnChecked);
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
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context
#define LogError &NCsCore::NLibrary::FLog::Error

// Get
#pragma region

APlayerCameraManager* UCsScriptLibrary_PlayerCamera::Get(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId)
{
	CONDITIONAL_SET_CTXT(Get);

	return CsPlayerCameraLibrary::GetSafe(Ctxt, WorldContextObject, ControllerId);
}

APlayerCameraManager* UCsScriptLibrary_PlayerCamera::GetChecked(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(Get);

	OutSuccess = true;
	return CS_SCRIPT_GET_CHECKED(CsPlayerCameraLibrary::GetChecked(Ctxt, WorldContextObject, ControllerId), CsPlayerCameraLibrary::GetSafe(Ctxt, WorldContextObject, ControllerId, OutSuccess, LogError));
}

APlayerCameraManager* UCsScriptLibrary_PlayerCamera::GetByPawn(const FString& Context, const APawn* Pawn)
{
	CONDITIONAL_SET_CTXT(GetByPawn);

	return CsPlayerCameraLibrary::GetSafe(Ctxt, Pawn);
}

APlayerCameraManager* UCsScriptLibrary_PlayerCamera::GetByPawnChecked(const FString& Context, const APawn* Pawn, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(GetByPawnChecked);

	OutSuccess = true;
	return CS_SCRIPT_GET_CHECKED(CsPlayerCameraLibrary::GetChecked(Ctxt, Pawn), CsPlayerCameraLibrary::GetSafe(Ctxt, Pawn, OutSuccess, LogError));
}

#pragma endregion Get

// Orientation
#pragma region

#pragma endregion Orientation

// View Target
#pragma region

bool UCsScriptLibrary_PlayerCamera::SetViewTarget(const FString& Context, APlayerController* PlayerController, AActor* NewViewTarget, const FViewTargetTransitionParams& TransitionParams)
{
	CONDITIONAL_SET_CTXT(SetViewTarget);

	return CsPlayerCameraLibrary::SetSafeViewTarget(Ctxt, PlayerController, NewViewTarget, TransitionParams);
}

void UCsScriptLibrary_PlayerCamera::SetViewTargetChecked(const FString& Context, APlayerController* PlayerController, AActor* NewViewTarget, const FViewTargetTransitionParams& TransitionParams, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(SetViewTargetChecked);

	OutSuccess = true;
	CS_SCRIPT_CHECKED(CsPlayerCameraLibrary::SetViewTargetChecked(Ctxt, PlayerController, NewViewTarget, TransitionParams), CsPlayerCameraLibrary::SetSafeViewTarget(Ctxt, PlayerController, NewViewTarget, TransitionParams, OutSuccess))
}

bool UCsScriptLibrary_PlayerCamera::SetViewTargetByPawn(const FString& Context, const APawn* Pawn, AActor* NewViewTarget, const FViewTargetTransitionParams& TransitionParams)
{
	CONDITIONAL_SET_CTXT(SetViewTargetByPawn);

	return CsPlayerCameraLibrary::SetSafeViewTarget(Ctxt, Pawn, NewViewTarget, TransitionParams);
}

void UCsScriptLibrary_PlayerCamera::SetViewTargetByPawnChecked(const FString& Context, const APawn* Pawn, AActor* NewViewTarget, const FViewTargetTransitionParams& TransitionParams, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(SetViewTargetByPawnChecked);

	OutSuccess = true;
	CS_SCRIPT_CHECKED(CsPlayerCameraLibrary::SetViewTargetChecked(Ctxt, Pawn, NewViewTarget, TransitionParams), CsPlayerCameraLibrary::SetSafeViewTarget(Ctxt, Pawn, NewViewTarget, TransitionParams, OutSuccess, LogError))
}

#pragma endregion View Target

// FOV
#pragma region

bool UCsScriptLibrary_PlayerCamera::SetFOV(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, const float& FOV)
{
	CONDITIONAL_SET_CTXT(SetFOV);

	return CsPlayerCameraLibrary::SetSafeFOV(Ctxt, WorldContextObject, ControllerId, FOV);
}

void UCsScriptLibrary_PlayerCamera::SetFOVChecked(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, const float& FOV, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(SetFOVChecked);

	OutSuccess = true;
	CS_SCRIPT_CHECKED(CsPlayerCameraLibrary::SetFOVChecked(Ctxt, WorldContextObject, ControllerId, FOV), CsPlayerCameraLibrary::SetSafeFOV(Ctxt, WorldContextObject, ControllerId, FOV, OutSuccess, LogError))
}

bool UCsScriptLibrary_PlayerCamera::SetFOVByPawn(const FString& Context, const APawn* Pawn, const float& FOV)
{
	CONDITIONAL_SET_CTXT(SetFOV);

	return CsPlayerCameraLibrary::SetSafeFOV(Ctxt, Pawn, FOV);
}

void UCsScriptLibrary_PlayerCamera::SetFOVByPawnChecked(const FString& Context, const APawn* Pawn, const float& FOV, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(SetFOVChecked);

	OutSuccess = true;
	CS_SCRIPT_CHECKED(CsPlayerCameraLibrary::SetFOVChecked(Ctxt, Pawn, FOV), CsPlayerCameraLibrary::SetSafeFOV(Ctxt, Pawn, FOV, OutSuccess, LogError))
}

float UCsScriptLibrary_PlayerCamera::GetFOV(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(GetFOV);

	return CsPlayerCameraLibrary::GetSafeFOV(Ctxt, WorldContextObject, ControllerId, OutSuccess);
}

float UCsScriptLibrary_PlayerCamera::GetFOVChecked(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(GetFOVChecked);

	OutSuccess = true;
	return CS_SCRIPT_GET_CHECKED(CsPlayerCameraLibrary::GetFOVChecked(Ctxt, WorldContextObject, ControllerId), CsPlayerCameraLibrary::GetSafeFOV(Ctxt, WorldContextObject, ControllerId, OutSuccess, LogError));
}

float UCsScriptLibrary_PlayerCamera::GetFOVByPawn(const FString& Context, const APawn* Pawn, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(GetFOVByPawn);

	return CsPlayerCameraLibrary::GetSafeFOV(Ctxt, Pawn, OutSuccess);
}

float UCsScriptLibrary_PlayerCamera::GetFOVByPawnChecked(const FString& Context, const APawn* Pawn, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(GetFOVByPawnChecked);

	OutSuccess = true;
	return CS_SCRIPT_GET_CHECKED(CsPlayerCameraLibrary::GetFOVChecked(Ctxt, Pawn), CsPlayerCameraLibrary::GetSafeFOV(Ctxt, Pawn, OutSuccess, LogError));
}

#pragma endregion FOV

// View
#pragma region

	// Pitch

		// Min

bool UCsScriptLibrary_PlayerCamera::SetViewPitchMin(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, const float& MinPitch)
{
	CONDITIONAL_SET_CTXT(SetViewPitchMin);

	return CsPlayerCameraLibrary::SetSafeViewPitchMin(Ctxt, WorldContextObject, ControllerId, MinPitch);
}

void UCsScriptLibrary_PlayerCamera::SetViewPitchMinChecked(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, const float& MinPitch, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(SetViewPitchMinChecked);

	OutSuccess = true;
	CS_SCRIPT_CHECKED(CsPlayerCameraLibrary::SetViewPitchMinChecked(Ctxt, WorldContextObject, ControllerId, MinPitch), CsPlayerCameraLibrary::SetSafeViewPitchMin(Ctxt, WorldContextObject, ControllerId, MinPitch, OutSuccess, LogError))
}

bool UCsScriptLibrary_PlayerCamera::SetViewPitchMinByPawn(const FString& Context, const APawn* Pawn, const float& MinPitch)
{
	CONDITIONAL_SET_CTXT(SetViewPitchMinByPawn);

	return CsPlayerCameraLibrary::SetSafeViewPitchMin(Ctxt, Pawn, MinPitch);
}

void UCsScriptLibrary_PlayerCamera::SetViewPitchMinByPawnChecked(const FString& Context, const APawn* Pawn, const float& MinPitch, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(SetViewPitchMinByPawnChecked);

	OutSuccess = true;
	CS_SCRIPT_CHECKED(CsPlayerCameraLibrary::SetViewPitchMinChecked(Ctxt, Pawn, MinPitch), CsPlayerCameraLibrary::SetSafeViewPitchMin(Ctxt, Pawn, MinPitch, OutSuccess, LogError))
}

		// Max

bool UCsScriptLibrary_PlayerCamera::SetViewPitchMax(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, const float& MaxPitch)
{
	CONDITIONAL_SET_CTXT(SetViewPitchMax);

	return CsPlayerCameraLibrary::SetSafeViewPitchMax(Ctxt, WorldContextObject, ControllerId, MaxPitch);
}

void UCsScriptLibrary_PlayerCamera::SetViewPitchMaxChecked(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, const float& MaxPitch, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(SetViewPitchMaxChecked);

	OutSuccess = true;
	CS_SCRIPT_CHECKED(CsPlayerCameraLibrary::SetViewPitchMaxChecked(Ctxt, WorldContextObject, ControllerId, MaxPitch), CsPlayerCameraLibrary::SetSafeViewPitchMax(Ctxt, WorldContextObject, ControllerId, MaxPitch, OutSuccess, LogError))
}

bool UCsScriptLibrary_PlayerCamera::SetViewPitchMaxByPawn(const FString& Context, const APawn* Pawn, const float& MaxPitch)
{
	CONDITIONAL_SET_CTXT(SetViewPitchMaxByPawn);

	return CsPlayerCameraLibrary::SetSafeViewPitchMax(Ctxt, Pawn, MaxPitch);
}

void UCsScriptLibrary_PlayerCamera::SetViewPitchMaxByPawnChecked(const FString& Context, const APawn* Pawn, const float& MaxPitch, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(SetViewPitchMaxByPawnChecked);

	OutSuccess = true;
	CS_SCRIPT_CHECKED(CsPlayerCameraLibrary::SetViewPitchMaxChecked(Ctxt, Pawn, MaxPitch), CsPlayerCameraLibrary::SetSafeViewPitchMax(Ctxt, Pawn, MaxPitch, OutSuccess, LogError))
}

#pragma endregion View

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT
#undef LogError
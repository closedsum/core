// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Achievement/Script/CsScriptLibrary_Manager_Achievement.h"
#include "CsPlatformServices.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Managers/Achievement/CsLibrary_Manager_Achievement.h"
// Managers
#include "Managers/PlayerProfile/CsManager_PlayerProfile.h"
#include "Managers/Achievement/CsManager_Achievement.h"

#include "Managers/PlayerProfile/CsPlayerProfile.h"

namespace NCsScriptLibraryManagerAchievement
{
	namespace NCached
	{
		namespace Str
		{
			// Complete
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Achievement, Complete);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Achievement, BindToEvent_OnComplete);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Achievement, IsCompleted);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Achievement, GetNumCompleted);
			// Reset
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Achievement, Reset);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Achievement, ResetAll);
			// Progress
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Achievement, GetProgress);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Achievement, GetTotalProgress);
		}
	}
}

UCsScriptLibrary_Manager_Achievement::UCsScriptLibrary_Manager_Achievement(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define USING_NS_CACHED using namespace NCsScriptLibraryManagerAchievement::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryManagerAchievement::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context
#define AchievementManagerLibrary NCsAchievement::NManager::FLibrary

// Complete
#pragma region

void UCsScriptLibrary_Manager_Achievement::Complete(const FString& Context, UObject* WorldContextObject, const FECsAchievement& Achievement)
{
	CONDITIONAL_SET_CTXT(Complete);

	AchievementManagerLibrary::SafeComplete(Ctxt, WorldContextObject, Achievement);
}

void UCsScriptLibrary_Manager_Achievement::BindToEvent_OnComplete(const FString& Context, UObject* WorldContextObject, const FECsAchievement& Achievement, FCsScriptLibraryManagerAchievement_OnComplete Delegate)
{
	CONDITIONAL_SET_CTXT(BindToEvent_OnComplete);

	if (UCsManager_Achievement* Manager = AchievementManagerLibrary::GetSafe(Ctxt, WorldContextObject))
	{
		CS_ADD_TO_DYNAMIC_MULITCAST_DELEGATE(Ctxt, Manager, OnComplete_ScriptEvent, Delegate, LogCsPlatformServices)
	}
}

bool UCsScriptLibrary_Manager_Achievement::IsCompleted(const FString& Context, UObject* WorldContextObject, const FECsAchievement& Achievement)
{
	CONDITIONAL_SET_CTXT(IsCompleted);

	return AchievementManagerLibrary::IsSafeCompleted(Ctxt, WorldContextObject, Achievement);
}

int32 UCsScriptLibrary_Manager_Achievement::GetNumCompleted(const FString& Context, UObject* WorldContextObject)
{
	CONDITIONAL_SET_CTXT(GetNumCompleted);

	return AchievementManagerLibrary::GetSafeNumCompleted(Ctxt, WorldContextObject);
}

#pragma endregion Complete

// Reset
#pragma region

void UCsScriptLibrary_Manager_Achievement::Reset(const FString& Context, UObject* WorldContextObject, const FECsAchievement& Achievement, const float& Percent /*= 0*/)
{
	CONDITIONAL_SET_CTXT(Reset);

	AchievementManagerLibrary::SafeReset(Ctxt, WorldContextObject, Achievement, Percent);
}

void UCsScriptLibrary_Manager_Achievement::ResetAll(const FString& Context, UObject* WorldContextObject)
{
	CONDITIONAL_SET_CTXT(ResetAll);

	AchievementManagerLibrary::SafeResetAll(Ctxt, WorldContextObject);
}

#pragma endregion Reset

// Progress
#pragma region

float UCsScriptLibrary_Manager_Achievement::GetProgress(const FString& Context, UObject* WorldContextObject, const FECsAchievement& Achievement)
{
	CONDITIONAL_SET_CTXT(GetProgress);

	return AchievementManagerLibrary::GetSafeProgress(Ctxt, WorldContextObject, Achievement);
}

float UCsScriptLibrary_Manager_Achievement::GetTotalProgress(const FString& Context, UObject* WorldContextObject)
{
	CONDITIONAL_SET_CTXT(GetTotalProgress);

	return AchievementManagerLibrary::GetSafeTotalProgress(Ctxt, WorldContextObject);
}

#pragma endregion Progress

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT
#undef AchievementManagerLibrary
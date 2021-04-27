// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Achievement/Script/CsScriptLibrary_Manager_Achievement.h"
#include "CsPlatformServices.h"

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
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Achievement, Complete);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Achievement, BindToEvent_OnComplete);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Achievement, IsCompleted);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Achievement, GetNumCompleted);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Achievement, Reset);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Achievement, ResetAll);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Achievement, GetProgress);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Achievement, GetTotalProgress);
		}
	}
}

UCsScriptLibrary_Manager_Achievement::UCsScriptLibrary_Manager_Achievement(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Complete
#pragma region

void UCsScriptLibrary_Manager_Achievement::Complete(const FString& Context, UObject* WorldContextObject, const FECsAchievement& Achievement)
{
	using namespace NCsScriptLibraryManagerAchievement::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Complete : Context;

	typedef NCsAchievement::NManager::FLibrary AchievementManagerLibrary;

	AchievementManagerLibrary::SafeComplete(Ctxt, WorldContextObject, Achievement);
}

void UCsScriptLibrary_Manager_Achievement::BindToEvent_OnComplete(const FString& Context, UObject* WorldContextObject, const FECsAchievement& Achievement, FCsScriptLibraryManagerAchievement_OnComplete Delegate)
{
	using namespace NCsScriptLibraryManagerAchievement::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::BindToEvent_OnComplete : Context;

	typedef NCsAchievement::NManager::FLibrary AchievementManagerLibrary;

	if (UCsManager_Achievement* Manager = AchievementManagerLibrary::GetSafe(Ctxt, WorldContextObject))
	{
		CS_ADD_TO_DYNAMIC_MULITCAST_DELEGATE(Ctxt, Manager, OnComplete_ScriptEvent, Delegate, LogCsPlatformServices)
	}
}

bool UCsScriptLibrary_Manager_Achievement::IsCompleted(const FString& Context, UObject* WorldContextObject, const FECsAchievement& Achievement)
{
	using namespace NCsScriptLibraryManagerAchievement::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::IsCompleted : Context;

	typedef NCsAchievement::NManager::FLibrary AchievementManagerLibrary;

	return AchievementManagerLibrary::IsSafeCompleted(Ctxt, WorldContextObject, Achievement);
}

int32 UCsScriptLibrary_Manager_Achievement::GetNumCompleted(const FString& Context, UObject* WorldContextObject)
{
	using namespace NCsScriptLibraryManagerAchievement::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetNumCompleted : Context;

	typedef NCsAchievement::NManager::FLibrary AchievementManagerLibrary;

	return AchievementManagerLibrary::GetSafeNumCompleted(Ctxt, WorldContextObject);
}

#pragma endregion Complete

// Reset
#pragma region

void UCsScriptLibrary_Manager_Achievement::Reset(const FString& Context, UObject* WorldContextObject, const FECsAchievement& Achievement, const float& Percent /*= 0*/)
{
	using namespace NCsScriptLibraryManagerAchievement::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Reset : Context;

	typedef NCsAchievement::NManager::FLibrary AchievementManagerLibrary;

	AchievementManagerLibrary::SafeReset(Ctxt, WorldContextObject, Achievement, Percent);
}

void UCsScriptLibrary_Manager_Achievement::ResetAll(const FString& Context, UObject* WorldContextObject)
{
	using namespace NCsScriptLibraryManagerAchievement::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::ResetAll : Context;

	typedef NCsAchievement::NManager::FLibrary AchievementManagerLibrary;

	AchievementManagerLibrary::SafeResetAll(Ctxt, WorldContextObject);
}

#pragma endregion Reset

// Progress
#pragma region

float UCsScriptLibrary_Manager_Achievement::GetProgress(const FString& Context, UObject* WorldContextObject, const FECsAchievement& Achievement)
{
	using namespace NCsScriptLibraryManagerAchievement::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetProgress : Context;

	typedef NCsAchievement::NManager::FLibrary AchievementManagerLibrary;

	return AchievementManagerLibrary::GetSafeProgress(Ctxt, WorldContextObject, Achievement);
}

float UCsScriptLibrary_Manager_Achievement::GetTotalProgress(const FString& Context, UObject* WorldContextObject)
{
	using namespace NCsScriptLibraryManagerAchievement::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetTotalProgress : Context;

	typedef NCsAchievement::NManager::FLibrary AchievementManagerLibrary;

	return AchievementManagerLibrary::GetSafeTotalProgress(Ctxt, WorldContextObject);
}

#pragma endregion Progress
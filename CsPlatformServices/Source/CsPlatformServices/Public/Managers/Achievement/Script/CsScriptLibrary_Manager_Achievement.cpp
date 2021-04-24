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

#if WITH_EDITOR
	typedef NCsAchievement::NManager::FLibrary AchievementManagerLibrary;

	UObject* ContextRoot = AchievementManagerLibrary::GetSafeContextRoot(Ctxt, WorldContextObject);

	if (ContextRoot)
#else
	UObject* ContextRoot = nullptr;
#endif // #if WITH_EDITOR
	{
		if (UCsManager_Achievement* Manager = UCsManager_Achievement::Get(ContextRoot))
		{
			if (!Manager->IsValid(Context, Achievement))
			{
				UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Achievement: %s is NOT Valid. Make sure both QueryAchievements and QueryAchievementDescriptions have been called."), *Ctxt, Achievement.ToChar());
				return;
			}
			Manager->Complete(Achievement);
		}
		else
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: No Manager Achievement of type: UCsManager_Achievement was created."), *Ctxt);
		}
	}
}

void UCsScriptLibrary_Manager_Achievement::BindToEvent_OnComplete(const FString& Context, UObject* WorldContextObject, const FECsAchievement& Achievement, FCsScriptLibraryManagerAchievement_OnComplete Delegate)
{
	using namespace NCsScriptLibraryManagerAchievement::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::BindToEvent_OnComplete : Context;

#if WITH_EDITOR
	typedef NCsAchievement::NManager::FLibrary AchievementManagerLibrary;

	UObject* ContextRoot = AchievementManagerLibrary::GetSafeContextRoot(Ctxt, WorldContextObject);

	if (ContextRoot)
#else
	UObject* ContextRoot = nullptr;
#endif // #if WITH_EDITOR
	{ 
		if (UCsManager_Achievement* Manager = UCsManager_Achievement::Get(ContextRoot))
		{
			if (Delegate.IsBound())
			{
				if (!Manager->OnComplete_ScriptEvent.Contains(Delegate))
				{
					Manager->OnComplete_ScriptEvent.Add(Delegate);
				}
				else
				{
					UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Delegate is already bound."), *Ctxt);
				}
			}
			else
			{
				UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: No Delegate Bound."), *Ctxt);
			}
		}
		else
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: No Manager Achievement of type: UCsManager_Achievement was created."), *Ctxt);
		}
	}
}

bool UCsScriptLibrary_Manager_Achievement::IsCompleted(const FString& Context, UObject* WorldContextObject, const FECsAchievement& Achievement)
{
	using namespace NCsScriptLibraryManagerAchievement::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::IsCompleted : Context;

#if WITH_EDITOR
	typedef NCsAchievement::NManager::FLibrary AchievementManagerLibrary;

	UObject* ContextRoot = AchievementManagerLibrary::GetSafeContextRoot(Ctxt, WorldContextObject);

	if (ContextRoot)
#else
	UObject* ContextRoot = nullptr;
#endif // #if WITH_EDITOR
	{
		if (UCsManager_Achievement* Manager = UCsManager_Achievement::Get(ContextRoot))
		{
			return Manager->IsCompleted(Achievement);
		}
		else
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: No Manager Achievement of type: UCsManager_Achievement was created."), *Ctxt);
		}
	}
	return false;
}

int32 UCsScriptLibrary_Manager_Achievement::GetNumCompleted(const FString& Context, UObject* WorldContextObject)
{
	using namespace NCsScriptLibraryManagerAchievement::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetNumCompleted : Context;

#if WITH_EDITOR
	typedef NCsAchievement::NManager::FLibrary AchievementManagerLibrary;

	UObject* ContextRoot = AchievementManagerLibrary::GetSafeContextRoot(Ctxt, WorldContextObject);

	if (ContextRoot)
#else
	UObject* ContextRoot = nullptr;
#endif // #if WITH_EDITOR
	{
		if (UCsManager_Achievement* Manager = UCsManager_Achievement::Get(ContextRoot))
		{
			return Manager->GetNumCompleted();
		}
		else
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: No Manager Achievement of type: UCsManager_Achievement was created."), *Ctxt);
		}
	}
	return 0;
}

#pragma endregion Complete

// Reset
#pragma region

void UCsScriptLibrary_Manager_Achievement::Reset(const FString& Context, UObject* WorldContextObject, const FECsAchievement& Achievement, const float& Percent /*= 0*/)
{
	using namespace NCsScriptLibraryManagerAchievement::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Reset : Context;

#if WITH_EDITOR
	typedef NCsAchievement::NManager::FLibrary AchievementManagerLibrary;

	UObject* ContextRoot = AchievementManagerLibrary::GetSafeContextRoot(Ctxt, WorldContextObject);

	if (ContextRoot)
#else
	UObject* ContextRoot = nullptr;
#endif // #if WITH_EDITOR
	{
		if (UCsManager_Achievement* Manager = UCsManager_Achievement::Get(ContextRoot))
		{
			if (!Manager->IsValid(Context, Achievement))
			{
				UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: Achievement: %s is NOT Valid. Make sure both QueryAchievements and QueryAchievementDescriptions have been called."), *Ctxt, Achievement.ToChar());
				return;
			}
			Manager->Reset(Achievement, FMath::Clamp(Percent, 0.0f, 1.0f));
		}
		else
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: No Manager Achievement of type UCsManager_Achievement was created."), *Ctxt);
		}
	}
}

void UCsScriptLibrary_Manager_Achievement::ResetAll(const FString& Context, UObject* WorldContextObject)
{
	using namespace NCsScriptLibraryManagerAchievement::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::ResetAll : Context;

#if WITH_EDITOR
	typedef NCsAchievement::NManager::FLibrary AchievementManagerLibrary;

	UObject* ContextRoot = AchievementManagerLibrary::GetSafeContextRoot(Ctxt, WorldContextObject);

	if (ContextRoot)
#else
	UObject* ContextRoot = nullptr;
#endif // #if WITH_EDITOR
	{
		if (UCsManager_Achievement* Manager = UCsManager_Achievement::Get(ContextRoot))
		{
			Manager->ResetAll();
		}
		else
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: No Manager Achievement of type UCsManager_Achievement was created."), *Ctxt);
		}
	}
}

#pragma endregion Reset

// Progress
#pragma region

float UCsScriptLibrary_Manager_Achievement::GetProgress(const FString& Context, UObject* WorldContextObject, const FECsAchievement& Achievement)
{
	using namespace NCsScriptLibraryManagerAchievement::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetProgress : Context;

#if WITH_EDITOR
	typedef NCsAchievement::NManager::FLibrary AchievementManagerLibrary;

	UObject* ContextRoot = AchievementManagerLibrary::GetSafeContextRoot(Ctxt, WorldContextObject);

	if (ContextRoot)
#else
	UObject* ContextRoot = nullptr;
#endif // #if WITH_EDITOR
	{
		if (UCsManager_Achievement* Manager = UCsManager_Achievement::Get(ContextRoot))
		{
			return Manager->GetProgress(Achievement);
		}
		else
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: No Manager Achievement of type UCsManager_Achievement was created."), *Ctxt);
		}
	}
	return 0.0f;
}

float UCsScriptLibrary_Manager_Achievement::GetTotalProgress(const FString& Context, UObject* WorldContextObject)
{
	using namespace NCsScriptLibraryManagerAchievement::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetTotalProgress : Context;

#if WITH_EDITOR
	typedef NCsAchievement::NManager::FLibrary AchievementManagerLibrary;

	UObject* ContextRoot = AchievementManagerLibrary::GetSafeContextRoot(Ctxt, WorldContextObject);

	if (ContextRoot)
#else
	UObject* ContextRoot = nullptr;
#endif // #if WITH_EDITOR
	{
		if (UCsManager_Achievement* Manager = UCsManager_Achievement::Get(ContextRoot))
		{
			return Manager->GetTotalProgress();
		}
		else
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("%s: No Manager Achievement of type UCsManager_Achievement was created."), *Ctxt);
		}
	}
	return 0.0f;
}

#pragma endregion Progress
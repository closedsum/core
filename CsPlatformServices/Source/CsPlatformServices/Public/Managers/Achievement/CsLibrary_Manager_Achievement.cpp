// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Achievement/CsLibrary_Manager_Achievement.h"
#include "CsPlatformServices.h"

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
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsLibrary_Manager_Achievement, Complete);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsLibrary_Manager_Achievement, Reset);
		}
	}
}

UCsLibrary_Manager_Achievement::UCsLibrary_Manager_Achievement(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Complete
#pragma region

void UCsLibrary_Manager_Achievement::Complete(const UObject* WorldContextObject, const FECsAchievement& Achievement)
{
	using namespace NCsScriptLibraryManagerAchievement::NCached;

	const FString& Context = Str::Complete;

#if WITH_EDITOR
	if (UCsManager_Achievement* Manager = UCsManager_Achievement::GetFromWorldContextObject(WorldContextObject))
#else
	if (UCsManager_Achievement* Manager = UCsManager_Achievement::Get())
#endif // #if WITH_EDITOR
	{
		if (!Manager->IsValid(Context, Achievement))
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsLibrary_Manager_Achievement::Complete: Achievement: %s is NOT Valid. Make sure both QueryAchievements and QueryAchievementDescriptions have been called."), Achievement.ToChar());
			return;
		}

		Manager->Complete(Achievement);
	}
	else
	{
		UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsLibrary_Manager_Achievement::Complete: No Manager Achievement of type UCsManager_Achievement was created."));
	}
}

void UCsLibrary_Manager_Achievement::BindToEvent_OnComplete(const UObject* WorldContextObject, const FECsAchievement& Achievement, FCsLibraryManagerAchievement_OnComplete Delegate)
{
#if WITH_EDITOR
	if (UCsManager_Achievement* Manager = UCsManager_Achievement::GetFromWorldContextObject(WorldContextObject))
#else
	if (UCsManager_Achievement* Manager = UCsManager_Achievement::Get())
#endif // #if WITH_EDITOR
	{
		if (Delegate.IsBound())
		{
			if (!Manager->OnComplete_ScriptEvent.Contains(Delegate))
			{
				Manager->OnComplete_ScriptEvent.Add(Delegate);
			}
			else
			{
				UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsLibrary_Manager_HMD::BindToEvent_OnComplete: Delegate is already bound."));
			}
		}
		else
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsLibrary_Manager_HMD::BindToEvent_OnComplete: No Delegate Bound."));
		}
	}
	else
	{
		UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsLibrary_Manager_Achievement::BindToEvent_OnComplete: No Manager Achievement of type UCsManager_Achievement was created."));
	}
}

bool UCsLibrary_Manager_Achievement::IsCompleted(const UObject* WorldContextObject, const FECsAchievement& Achievement)
{
#if WITH_EDITOR
	if (UCsManager_Achievement* Manager = UCsManager_Achievement::GetFromWorldContextObject(WorldContextObject))
#else
	if (UCsManager_Achievement* Manager = UCsManager_Achievement::Get())
#endif // #if WITH_EDITOR
	{
		return Manager->IsCompleted(Achievement);
	}
	else
	{
		UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsLibrary_Manager_Achievement::IsCompleted: No Manager Achievement of type UCsManager_Achievement was created."));
	}
	return false;
}

int32 UCsLibrary_Manager_Achievement::GetNumCompleted(const UObject* WorldContextObject)
{
#if WITH_EDITOR
	if (UCsManager_Achievement* Manager = UCsManager_Achievement::GetFromWorldContextObject(WorldContextObject))
#else
	if (UCsManager_Achievement* Manager = UCsManager_Achievement::Get())
#endif // #if WITH_EDITOR
	{
		return Manager->GetNumCompleted();
	}
	else
	{
		UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsLibrary_Manager_Achievement::GetNumCompleted: No Manager Achievement of type UCsManager_Achievement was created."));
	}
	return 0;
}

#pragma endregion Complete

// Reset
#pragma region

void UCsLibrary_Manager_Achievement::Reset(const UObject* WorldContextObject, const FECsAchievement& Achievement, const float& Percent /*= 0*/)
{
	using namespace NCsScriptLibraryManagerAchievement::NCached;

	const FString& Context = Str::Reset;

#if WITH_EDITOR
	if (UCsManager_Achievement* Manager = UCsManager_Achievement::GetFromWorldContextObject(WorldContextObject))
#else
	if (UCsManager_Achievement* Manager = UCsManager_Achievement::Get())
#endif // #if WITH_EDITOR
	{
		if (!Manager->IsValid(Context, Achievement))
		{
			UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsLibrary_Manager_Achievement::Reset: Achievement: %s is NOT Valid. Make sure both QueryAchievements and QueryAchievementDescriptions have been called."), Achievement.ToChar());
			return;
		}

		Manager->Reset(Achievement, FMath::Clamp(Percent, 0.0f, 1.0f));
	}
	else
	{
		UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsLibrary_Manager_Achievement::Reset: No Manager Achievement of type UCsManager_Achievement was created."));
	}
}

void UCsLibrary_Manager_Achievement::ResetAll(const UObject* WorldContextObject)
{
#if WITH_EDITOR
	if (UCsManager_Achievement* Manager = UCsManager_Achievement::GetFromWorldContextObject(WorldContextObject))
#else
	if (UCsManager_Achievement* Manager = UCsManager_Achievement::Get())
#endif // #if WITH_EDITOR
	{
		Manager->ResetAll();
	}
	else
	{
		UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsLibrary_Manager_Achievement::ResetAll: No Manager Achievement of type UCsManager_Achievement was created."));
	}
}

#pragma endregion Reset

// Progress
#pragma region

float UCsLibrary_Manager_Achievement::GetProgress(const UObject* WorldContextObject, const FECsAchievement& Achievement)
{
#if WITH_EDITOR
	if (UCsManager_Achievement* Manager = UCsManager_Achievement::GetFromWorldContextObject(WorldContextObject))
#else
	if (UCsManager_Achievement* Manager = UCsManager_Achievement::Get())
#endif // #if WITH_EDITOR
	{
		return Manager->GetProgress(Achievement);
	}
	else
	{
		UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsLibrary_Manager_Achievement::GetProgress: No Manager Achievement of type UCsManager_Achievement was created."));
	}
	return 0.0f;
}

float UCsLibrary_Manager_Achievement::GetTotalProgress(const UObject* WorldContextObject)
{
#if WITH_EDITOR
	if (UCsManager_Achievement* Manager = UCsManager_Achievement::GetFromWorldContextObject(WorldContextObject))
#else
	if (UCsManager_Achievement* Manager = UCsManager_Achievement::Get())
#endif // #if WITH_EDITOR
	{
		return Manager->GetTotalProgress();
	}
	else
	{
		UE_LOG(LogCsPlatformServices, Warning, TEXT("UCsLibrary_Manager_Achievement::GetTotalProgress: No Manager Achievement of type UCsManager_Achievement was created."));
	}
	return 0.0f;
}

#pragma endregion Progress
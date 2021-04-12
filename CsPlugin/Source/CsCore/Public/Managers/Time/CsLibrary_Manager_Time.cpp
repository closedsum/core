// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Time/CsLibrary_Manager_Time.h"

// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Managers
#include "Managers/Time/CsManager_Time.h"
// Game
#include "Engine/GameInstance.h"
// World
#include "Engine/World.h"

#if WITH_EDITOR
// Library
#include "Library/CsLibrary_World.h"
#endif // #if WITH_EDITOR

namespace NCsTime
{
	namespace NManager
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsTime::NManager::FLibrary, GetSafeContextRoot);
				}
			}
		}

	#if WITH_EDITOR

		UObject* FLibrary::GetContextRootChecked(const FString& Context, UObject* WorldContext)
		{
			typedef NCsWorld::FLibrary WorldLibrary;

			UWorld* World = WorldLibrary::GetChecked(Context, WorldContext);

			if (WorldLibrary::IsPlayInEditor(World) ||
				WorldLibrary::IsPlayInEditorPreview(World))
			{
				return GEngine;
			}

			UGameInstance* GameInstance = World->GetGameInstance();

			checkf(GameInstance, TEXT("%s: Failed to get GameInstance from World: %s."), *Context, GameInstance);

			return GameInstance;
		}

		UObject* FLibrary::GetSafeContextRoot(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			typedef NCsWorld::FLibrary WorldLibrary;

			UWorld* World = WorldLibrary::GetSafe(Context, WorldContext, Log);

			if (!World)
				return nullptr;

			typedef NCsWorld::FLibrary WorldLibrary;

			if (WorldLibrary::IsPlayInEditor(WorldContext->GetWorld()) ||
				WorldLibrary::IsPlayInEditorPreview(WorldContext->GetWorld()))
			{
				return GEngine;
			}
			else
			{
				return World->GetGameInstance();
			}
		}

		UObject* FLibrary::GetSafeContextRoot(const UObject* WorldContext)
		{
			using namespace NCsTime::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafeContextRoot;

			return GetSafeContextRoot(Context, WorldContext, nullptr);
		}

	#endif // #if WITH_EDITOR

		void FLibrary::UpdateTimeAndCoroutineScheduler(const FString& Context, UObject* WorldContext, const FECsUpdateGroup& Group, const float& DeltaTime)
		{
			UObject* ContextRoot = GetContextRootChecked(Context, WorldContext);

			UCsManager_Time* Manager_Time = UCsManager_Time::Get(ContextRoot);

			Manager_Time->Update(Group, DeltaTime);

			const FCsDeltaTime& ScaledDeltaTime = Manager_Time->GetScaledDeltaTime(Group);

			// Update CoroutineScheduler
			UCsCoroutineScheduler::Get(ContextRoot)->Update(Group, ScaledDeltaTime);
		}

		void FLibrary::SetScaledDeltaTime(const FString& Context, UObject* WorldContext, const FECsUpdateGroup& Group, const float& Scale)
		{
			UCsManager_Time::Get(GetContextRootChecked(Context, WorldContext))->SetScaledDeltaTime(Group, Scale);
		}

		void FLibrary::ResetScaledDeltaTime(const FString& Context, UObject* WorldContext, const FECsUpdateGroup& Group)
		{
			UCsManager_Time::Get(GetContextRootChecked(Context, WorldContext))->ResetScaledDeltaTime(Group);
		}
	}
}
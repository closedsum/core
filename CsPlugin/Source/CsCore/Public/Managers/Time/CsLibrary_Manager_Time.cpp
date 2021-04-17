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
#include "Game/CsLibrary_GameInstance.h"
// Engine
#include "Engine/Engine.h"
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

		UObject* FLibrary::GetContextRootChecked(const FString& Context, UObject* ContextObject)
		{
			typedef NCsWorld::FLibrary WorldLibrary;

			UWorld* World = WorldLibrary::GetSafe(Context, ContextObject, nullptr);

			if (WorldLibrary::IsPlayInEditor(World) ||
				WorldLibrary::IsPlayInEditorPreview(World))
			{
				return GEngine;
			}

			typedef NCsGameInstance::FLibrary GameInstanceLibrary;

			return GameInstanceLibrary::GetChecked(Context, ContextObject);
		}

		UObject* FLibrary::GetSafeContextRoot(const FString& Context, UObject* ContextObject, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			typedef NCsWorld::FLibrary WorldLibrary;

			UWorld* World = WorldLibrary::GetSafe(Context, ContextObject, Log);

			if (WorldLibrary::IsPlayInEditor(World) ||
				WorldLibrary::IsPlayInEditorPreview(World))
			{
				return GEngine;
			}

			typedef NCsGameInstance::FLibrary GameInstanceLibrary;

			return GameInstanceLibrary::GetSafe(Context, ContextObject, Log);
		}

		UObject* FLibrary::GetSafeContextRoot(UObject* ContextObject)
		{
			using namespace NCsTime::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafeContextRoot;

			return GetSafeContextRoot(Context, ContextObject, nullptr);
		}

	#endif // #if WITH_EDITOR

		void FLibrary::UpdateTimeAndCoroutineScheduler(const FString& Context, UObject* ContextObject, const FECsUpdateGroup& Group, const float& DeltaTime)
		{
			UObject* ContextRoot = GetContextRootChecked(Context, ContextObject);

			UCsManager_Time* Manager_Time = UCsManager_Time::Get(ContextRoot);

			Manager_Time->Update(Group, DeltaTime);

			const FCsDeltaTime& ScaledDeltaTime = Manager_Time->GetScaledDeltaTime(Group);

			// Update CoroutineScheduler
			UCsCoroutineScheduler::Get(ContextRoot)->Update(Group, ScaledDeltaTime);
		}

		void FLibrary::SetScaledDeltaTime(const FString& Context, UObject* ContextObject, const FECsUpdateGroup& Group, const float& Scale)
		{
			UCsManager_Time::Get(GetContextRootChecked(Context, ContextObject))->SetScaledDeltaTime(Group, Scale);
		}

		void FLibrary::ResetScaledDeltaTime(const FString& Context, UObject* ContextObject, const FECsUpdateGroup& Group)
		{
			UCsManager_Time::Get(GetContextRootChecked(Context, ContextObject))->ResetScaledDeltaTime(Group);
		}
	}
}
// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Time/CsLibrary_Manager_Time.h"

// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Library
#include "Library/CsLibrary_Valid.h"
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
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsTime::NManager::FLibrary, GetSafe);
				}
			}
		}

		// ContextRoot
		#pragma region

		#if WITH_EDITOR

		UObject* FLibrary::GetContextRootChecked(const FString& Context, const UObject* ContextObject)
		{
			typedef NCsWorld::FLibrary WorldLibrary;

			UWorld* World = WorldLibrary::GetSafe(Context, ContextObject, nullptr);

			if (WorldLibrary::IsPlayInEditor(World) ||
				WorldLibrary::IsPlayInEditorPreview(World))
			{
				return GEngine;
			}

			typedef NCsGameInstance::FLibrary GameInstanceLibrary;

			return GameInstanceLibrary::GetAsObjectChecked(Context, ContextObject);
		}

		UObject* FLibrary::GetSafeContextRoot(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			typedef NCsWorld::FLibrary WorldLibrary;

			UWorld* World = WorldLibrary::GetSafe(Context, ContextObject, Log);

			if (WorldLibrary::IsPlayInEditor(World) ||
				WorldLibrary::IsPlayInEditorPreview(World))
			{
				return GEngine;
			}

			typedef NCsGameInstance::FLibrary GameInstanceLibrary;

			return GameInstanceLibrary::GetSafeAsObject(Context, ContextObject, Log);
		}

		UObject* FLibrary::GetSafeContextRoot(const UObject* ContextObject)
		{
			using namespace NCsTime::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafeContextRoot;

			return GetSafeContextRoot(Context, ContextObject, nullptr);
		}

		#endif // #if WITH_EDITOR

		#pragma endregion ContextRoot

		// Get
		#pragma region

		UCsManager_Time* FLibrary::GetChecked(const FString& Context, const UObject* ContextObject)
		{
			UObject* ContextRoot		  = GetContextRootChecked(Context, ContextObject);
			UCsManager_Time* Manager_Time = UCsManager_Time::Get(ContextRoot);

			CS_IS_PTR_NULL_CHECKED(Manager_Time)
			return Manager_Time;
		}

		UCsManager_Time* FLibrary::GetSafe(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) /*= &NCsPlayback::FLog::Warning*/)
		{
			UObject* ContextRoot = GetSafeContextRoot(Context, ContextObject, Log);

		#if WITH_EDITOR
			if (!ContextRoot)
				return nullptr;
		#endif // #if WITH_EDITOR

			UCsManager_Time* Manager_Time = UCsManager_Time::GetSafe(Context, ContextRoot, Log);

			if (!Manager_Time)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Manager_Time."), *Context));
			}
			return Manager_Time;
		}

		UCsManager_Time* FLibrary::GetSafe(const UObject* ContextObject)
		{
			using namespace NCsTime::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafe;

			return GetSafe(Context, ContextObject, nullptr);
		}

		#pragma endregion Get

		void FLibrary::UpdateTimeAndCoroutineScheduler(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group, const float& DeltaTime)
		{
			UObject* ContextRoot = GetContextRootChecked(Context, ContextObject);

			UCsManager_Time* Manager_Time = UCsManager_Time::Get(ContextRoot);

			Manager_Time->Update(Group, DeltaTime);

			const FCsDeltaTime& ScaledDeltaTime = Manager_Time->GetScaledDeltaTime(Group);

			// Update CoroutineScheduler
			UCsCoroutineScheduler::Get(ContextRoot)->Update(Group, ScaledDeltaTime);
		}

		const FCsTime& FLibrary::GetTimeChecked(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group)
		{
			return GetChecked(Context, ContextObject)->GetTime(Group);
		}

		const FCsDeltaTime& FLibrary::GetTimeSinceStartChecked(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group)
		{
			return GetChecked(Context, ContextObject)->GetTimeSinceStart(Group);
		}

		const FCsDeltaTime& FLibrary::GetSafeTimeSinceStart(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			if (UCsManager_Time* Manager_Time = GetSafe(Context, ContextObject, Log))
			{
				CS_IS_ENUM_STRUCT_VALID_RET_VALUE(EMCsUpdateGroup, FECsUpdateGroup, Group, FCsDeltaTime::Zero)

				return Manager_Time->GetTimeSinceStart(Group);
			}
			return FCsDeltaTime::Zero;
		}

		void FLibrary::SetScaledDeltaTime(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group, const float& Scale)
		{
			GetChecked(Context, ContextObject)->SetScaledDeltaTime(Group, Scale);
		}

		void FLibrary::ResetScaledDeltaTime(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group)
		{
			GetChecked(Context, ContextObject)->ResetScaledDeltaTime(Group);
		}
	}
}
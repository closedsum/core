// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Time/CsLibrary_Manager_TimeImpl.h"

// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Library
#include "Coroutine/CsLibrary_CoroutineScheduler.h"
#include "Managers/Time/CsLibrary_Manager_Time.h"
	// Common
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/Time/CsManager_TimeImpl.h"
// Game
#include "Engine/GameInstance.h"
// World
#include "Engine/World.h"

#if WITH_EDITOR
// Library
	// Common
#include "Library/CsLibrary_World.h"
#include "Game/CsLibrary_GameInstance.h"
// Managers
#include "Singleton/CsGetManagerSingleton.h"
#endif // #if WITH_EDITOR

namespace NCsTime
{
	namespace NManager
	{
		namespace NImpl
		{
			namespace NLibrary
			{
				namespace NCached
				{
					namespace Str
					{
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsTime::NManager::NImpl::FLibrary, GetSafe);
					}
				}
			}

			#define USING_NS_CACHED using namespace NCsTime::NManager::NImpl::NLibrary::NCached;
			#define SET_CONTEXT(__FunctionName) using namespace NCsTime::NManager::NImpl::NLibrary::NCached; \
				const FString& Context = Str::__FunctionName
			#define LogLevel void(*Log)(const FString&) /*=&FCsLog::Warning*/
			#define GameInstanceLibrary NCsGameInstance::FLibrary

			// Get
			#pragma region

			UCsManager_TimeImpl* FLibrary::GetChecked(const FString& Context, const UObject* ContextObject)
			{
			#if UE_BUILD_SHIPPING
				return UCsManager_Time::Get<UCsManager_TimeImpl>(nullptr);
			#else
				return CsTimeManagerLibrary::GetChecked<UCsManager_TimeImpl>(Context, ContextObject);
			#endif // #if UE_BUILD_SHIPPING
			}

			UCsManager_TimeImpl* FLibrary::GetSafe(const FString& Context, const UObject* ContextObject, LogLevel)
			{
				return CsTimeManagerLibrary::GetSafe<UCsManager_TimeImpl>(Context, ContextObject, Log);
			}

			UCsManager_TimeImpl* FLibrary::GetSafe(const UObject* ContextObject)
			{
				SET_CONTEXT(GetSafe);

				return GetSafe(Context, ContextObject, nullptr);
			}

			#pragma endregion Get

			// Time
			#pragma region

			void FLibrary::UpdateTimeAndCoroutineScheduler(const FString& Context, const UObject* ContextObject, const FECsUpdateGroup& Group, const float& DeltaTime)
			{
				UCsManager_TimeImpl* Manager_Time = GetChecked(Context, ContextObject);

				Manager_Time->Update(Group, DeltaTime);

				const FCsDeltaTime& ScaledDeltaTime = Manager_Time->GetScaledDeltaTime(Group);

				// Update CoroutineScheduler
				typedef NCsCoroutine::NScheduler::FLibrary CoroutineSchedulerLibrary;

				CoroutineSchedulerLibrary::UpdateChecked(Context, ContextObject, Group, ScaledDeltaTime);
			}

			#pragma endregion Time

			#undef USING_NS_CACHED
			#undef SET_CONTEXT
			#undef LogLevel
			#undef GameInstanceLibrary
		}
	}
}
// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Coroutine/CsLibrary_CoroutineScheduler.h"

// Coroutine
#include "Coroutine/CsCoroutineSchedule.h"
// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Library/CsLibrary_Valid.h"
// World
#include "Engine/World.h"

#if WITH_EDITOR
// Library
#include "Library/CsLibrary_World.h"
#include "Game/CsLibrary_GameInstance.h"
// Engine
#include "Engine/Engine.h"
#endif // #if WITH_EDITOR

namespace NCsCoroutine
{
	namespace NScheduler
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsCoroutine::NScheduler::FLibrary, GetContextRoot);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsCoroutine::NScheduler::FLibrary, GetSafeContextRoot);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsCoroutine::NScheduler::FLibrary, GetSafe);
				}
			}
		}

		// ContextRoot
		#pragma region

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

			return GameInstanceLibrary::GetAsObjectChecked(Context, ContextObject);
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

			return GameInstanceLibrary::GetSafeAsObject(Context, ContextObject, Log);
		}

		UObject* FLibrary::GetSafeContextRoot(UObject* ContextObject)
		{
			using namespace NCsCoroutine::NScheduler::NLibrary::NCached;

			const FString& Context = Str::GetSafeContextRoot;

			return GetSafeContextRoot(Context, ContextObject, nullptr);
		}

		#endif // #if WITH_EDITOR

		#pragma endregion ContextRoot

		// Get
		#pragma region

		UCsCoroutineScheduler* FLibrary::GetChecked(const FString& Context, UObject* ContextObject)
		{
			UObject* ContextRoot			 = GetContextRootChecked(Context, ContextObject);
			UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get(ContextRoot);

			CS_IS_PTR_NULL_CHECKED(Scheduler)
			return Scheduler;
		}

		UCsCoroutineScheduler* FLibrary::GetSafe(const FString& Context, UObject* ContextObject, void(*Log)(const FString&) /*= &FCsLog::Warning*/)
		{
			UObject* ContextRoot = GetSafeContextRoot(Context, ContextObject, Log);

		#if WITH_EDITOR
			if (!ContextRoot)
				return nullptr;
		#endif // #if WITH_EDITOR

			UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get(ContextRoot);

			if (!Scheduler)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Scheduler."), *Context));
			}
			return Scheduler;
		}

		UCsCoroutineScheduler* FLibrary::GetSafe(UObject* ContextObject)
		{
			using namespace NCsCoroutine::NScheduler::NLibrary::NCached;

			const FString& Context = Str::GetSafe;

			return GetSafe(Context, ContextObject, nullptr);
		}

		#pragma endregion Get
	}
}
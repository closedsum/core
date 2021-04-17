// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Coroutine/CsLibrary_CoroutineScheduler.h"

// Types
#include "Types/CsTypes_Macro.h"
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
			using namespace NCsCoroutine::NScheduler::NLibrary::NCached;

			const FString& Context = Str::GetSafeContextRoot;

			return GetSafeContextRoot(Context, ContextObject, nullptr);
		}

	#endif // #if WITH_EDITOR
	}
}
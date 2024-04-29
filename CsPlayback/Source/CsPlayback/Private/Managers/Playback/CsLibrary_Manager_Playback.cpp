// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Playback/CsLibrary_Manager_Playback.h"
#include "CsPlayback.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Game/CsLibrary_GameInstance.h"
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/Playback/CsManager_Playback.h"
// Game
#include "Engine/GameInstance.h"

namespace NCsPlayback
{
	namespace NManager
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsPlayback::NManager::FLibrary, GetSafeContextRoot);
				}
			}
		}

		// ContextRoot
		#pragma region

		#if WITH_EDITOR

		UObject* FLibrary::GetContextRootChecked(const FString& Context, const UObject* ContextObject)
		{
			typedef NCsGameInstance::FLibrary GameInstanceLibrary;

			return GameInstanceLibrary::GetChecked(Context, ContextObject);
		}

		UObject* FLibrary::GetSafeContextRoot(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) /*=&NCsPlayback::FLog::Warning*/)
		{
			typedef NCsGameInstance::FLibrary GameInstanceLibrary;

			return GameInstanceLibrary::GetSafe(Context, ContextObject, Log);
		}

		UObject* FLibrary::GetSafeContextRoot(const UObject* ContextObject)
		{
			using namespace NCsPlayback::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafeContextRoot;

			return GetSafeContextRoot(Context, ContextObject, nullptr);
		}

		#endif // #if WITH_EDITOR

		#pragma endregion ContextRoot

		// Get
		#pragma region

		UCsManager_Playback* FLibrary::GetChecked(const FString& Context, const UObject* ContextObject)
		{
			UObject* ContextRoot				  = GetContextRootChecked(Context, ContextObject);
			UCsManager_Playback* Manager_Playback = UCsManager_Playback::Get(ContextRoot);

			CS_IS_PTR_NULL_CHECKED(Manager_Playback)
			return Manager_Playback;
		}

		UCsManager_Playback* FLibrary::GetSafe(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) /*=&NCsPlayback::FLog::Warning*/)
		{
			UObject* ContextRoot = GetSafeContextRoot(Context, ContextObject, Log);

		#if WITH_EDITOR
			if (!ContextRoot)
				return nullptr;
		#endif // #if WITH_EDITOR

			UCsManager_Playback* Manager_Playback = UCsManager_Playback::Get(ContextRoot);

			if (!Manager_Playback)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Manager_Playback."), *Context));
			}
			return Manager_Playback;
		}

		#pragma endregion Get

		// State
		#pragma region

		#define StateType NCsPlayback::EState

		void FLibrary::SetPlaybackStateChecked(const FString& Context, const UObject* ContextObject, const StateType& State)
		{
			GetChecked(Context, ContextObject)->SetPlaybackState(State);
		}

		const StateType& FLibrary::GetPlaybackStateChecked(const FString& Context, const UObject* ContextObject)
		{
			return GetChecked(Context, ContextObject)->GetPlaybackState();
		}

		#undef StateType

		#pragma endregion State

		namespace NPlayback
		{
			void FLibrary::SafePlayLatest(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) /*=&NCsPlayback::FLog::Warning*/)
			{
				typedef NCsPlayback::NManager::FLibrary PlaybackManagerLibrary;

				if (UCsManager_Playback* Manager_Playback = PlaybackManagerLibrary::GetSafe(Context, ContextObject, Log))
				{
					Manager_Playback->Playback.SafePlayLatest(Context, Log);
				}
			}

			bool FLibrary::IsSafeSustainedGameEvent(const FString& Context, const UObject* ContextObject, const FECsGameEvent& Event, void(*Log)(const FString&) /*=&NCsPlayback::FLog::Warning*/)
			{
				typedef NCsPlayback::NManager::FLibrary PlaybackManagerLibrary;

				if (UCsManager_Playback* Manager_Playback = PlaybackManagerLibrary::GetSafe(Context, ContextObject, Log))
				{
					CS_IS_ENUM_STRUCT_VALID(EMCsGameEvent, FECsGameEvent, Event)

					return Manager_Playback->Playback.IsSustainedGameEvent(Event);
				}
				return false;
			}
		}
	}
}
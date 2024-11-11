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

using LogClassType = NCsPlayback::FLog;

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

		CS_DEFINE_STATIC_LOG_LEVEL(FLibrary, LogClassType::Warning);

		#define USING_NS_CACHED using namespace NCsPlayback::NManager::NLibrary::NCached;
		#define SET_CONTEXT(__FunctionName) using namespace NCsPlayback::NManager::NLibrary::NCached; \
			const FString& Context = Str::__FunctionName

		// ContextRoot
		#pragma region

		#if WITH_EDITOR

		UObject* FLibrary::GetContextRootChecked(const FString& Context, const UObject* ContextObject)
		{
			return CsGameInstanceLibrary::GetChecked(Context, ContextObject);
		}

		UObject* FLibrary::GetSafeContextRoot(const FString& Context, const UObject* ContextObject, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			return CsGameInstanceLibrary::GetSafe(Context, ContextObject, Log);
		}

		UObject* FLibrary::GetSafeContextRoot(const UObject* ContextObject)
		{
			SET_CONTEXT(GetSafeContextRoot);

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

		UCsManager_Playback* FLibrary::GetSafe(const FString& Context, const UObject* ContextObject, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
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

		void FLibrary::SetPlaybackStateChecked(const FString& Context, const UObject* ContextObject, const CsPlaybackStateType& State)
		{
			GetChecked(Context, ContextObject)->SetPlaybackState(State);
		}

		const CsPlaybackStateType& FLibrary::GetPlaybackStateChecked(const FString& Context, const UObject* ContextObject)
		{
			return GetChecked(Context, ContextObject)->GetPlaybackState();
		}

		#pragma endregion State

		#undef USING_NS_CACHED
		#undef SET_CONTEXT
	}
}

namespace NCsPlayback
{
	namespace NManager
	{
		namespace NPlayback
		{
			CS_DEFINE_STATIC_LOG_LEVEL(FLibrary, LogClassType::Warning);

			void FLibrary::SafePlayLatest(const FString& Context, const UObject* ContextObject, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
			{
				if (UCsManager_Playback* Manager_Playback = CsPlaybackManagerLibrary::GetSafe(Context, ContextObject, Log))
				{
					Manager_Playback->Playback.SafePlayLatest(Context, Log);
				}
			}

			bool FLibrary::IsSafeSustainedGameEvent(const FString& Context, const UObject* ContextObject, const FECsGameEvent& Event, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
			{
				if (UCsManager_Playback* Manager_Playback = CsPlaybackManagerLibrary::GetSafe(Context, ContextObject, Log))
				{
					CS_IS_ENUM_STRUCT_VALID(EMCsGameEvent, FECsGameEvent, Event)

					return Manager_Playback->Playback.IsSustainedGameEvent(Event);
				}
				return false;
			}
		}
	}
}
// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Player/CsLibrary_PlayerTransitionCache.h"

// Library
#include "Game/SeamlessTransition/CsLibrary_GameInstance_SeamlessTransition.h"
#include "Library/CsLibrary_Valid.h"
// Player
#include "Player/CsPlayerTransitionCache.h"

namespace NCsPlayer
{
	namespace NTransition
	{
		namespace NCache
		{
			using LogClassType = NCsSeamlessTransition::FLog;

			CS_DEFINE_STATIC_LOG_LEVEL(FLibrary, LogClassType::Warning);

			using GameInstanceLibrary = NCsGameInstance::NSeamlessTransition::FLibrary;
			using PlayerCacheType = NCsPlayer::NTransition::FCache;

			void FLibrary::Input_AddEventChecked(const FString& Context, const UObject* WorldContext, const FCsGameEventInfo& Info)
			{
				CS_IS_VALID_CHECKED(Info);

				GameInstanceLibrary::GetPlayerTransitionCacheChecked(Context, WorldContext)->InputCache.Events.Add(Info);
			}

			bool FLibrary::Input_SafeAddEvent(const FString& Context, const UObject* WorldContext, const FCsGameEventInfo& Info, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
			{
				CS_IS_VALID(Info)

				if (PlayerCacheType* Cache = GameInstanceLibrary::GetSafePlayerTransitionCache(Context, WorldContext, Log))
				{
					Cache->InputCache.Events.Add(Info);
					return true;
				}
				return false;
			}

			void FLibrary::ResolveChecked(const FString& Context, const UObject* WorldContext)
			{
				GameInstanceLibrary::GetPlayerTransitionCacheChecked(Context, WorldContext)->Resolve(Context, WorldContext);
			}
		}
	}
}
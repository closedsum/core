// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Player/CsLibrary_PlayerTransitionCache.h"

// Library
#include "Game/CsLibrary_GameInstance_SeamlessTransition.h"
#include "Library/CsLibrary_Valid.h"
// Player
#include "Player/CsPlayerTransitionCache.h"

namespace NCsPlayer
{
	namespace NTransition
	{
		namespace NCache
		{
			#define LogLevel void(*Log)(const FString&) /*=&NFnLive::FLog::Warning*/

			using GameInstanceLibrary = NCsGameInstance::NSeamlessTransition::FLibrary;
			using PlayerCacheType = NCsPlayer::NTransition::FCache;

			void FLibrary::Input_AddEventChecked(const FString& Context, const UObject* WorldContext, const FCsGameEventInfo& Info)
			{
				CS_IS_VALID_CHECKED(Info);

				GameInstanceLibrary::GetPlayerTransitionCacheChecked(Context, WorldContext)->InputCache.Events.Add(Info);
			}

			bool FLibrary::Input_SafeAddEvent(const FString& Context, const UObject* WorldContext, const FCsGameEventInfo& Info, LogLevel)
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

			#undef LogLevel
		}
	}
}
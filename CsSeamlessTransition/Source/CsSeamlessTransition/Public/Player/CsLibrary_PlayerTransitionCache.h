// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Managers/Input/GameEvent/CsGameEvent.h"
// Log
#include "Utility/CsSeamlessTransitionLog.h"

class UObject;

namespace NCsPlayer
{
	namespace NTransition
	{
		namespace NCache
		{
			struct CSSEAMLESSTRANSITION_API FLibrary
			{
			#define LogLevel void(*Log)(const FString&) = &NCsSeamlessTransition::FLog::Warning

			public:

				static void Input_AddEventChecked(const FString& Context, const UObject* WorldContext, const FCsGameEventInfo& Info);

				static bool Input_SafeAddEvent(const FString& Context, const UObject* WorldContext, const FCsGameEventInfo& Info, LogLevel);
				FORCEINLINE static bool Input_SafeAddEvent(const FString& Context, const UObject* WorldContext, const FCsGameEventInfo& Info, bool& OutSuccess, LogLevel)
				{
					OutSuccess = Input_SafeAddEvent(Context, WorldContext, Info, Log);
					return OutSuccess;
				}

				static void ResolveChecked(const FString& Context, const UObject* WorldContext);

			#undef LogLevel
			};
		}
	}
}

using CsPlayerTransitionCacheLibray = NCsPlayer::NTransition::NCache::FLibrary;
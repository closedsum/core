// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "CsMacro_Log.h"
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
			private:

				CS_DECLARE_STATIC_LOG_LEVEL

			public:

				static void Input_AddEventChecked(const FString& Context, const UObject* WorldContext, const FCsGameEventInfo& Info);

				static bool Input_SafeAddEvent(const FString& Context, const UObject* WorldContext, const FCsGameEventInfo& Info, CS_FN_PARAM_DEFAULT_LOG_LEVEL);
				FORCEINLINE static bool Input_SafeAddEvent(const FString& Context, const UObject* WorldContext, const FCsGameEventInfo& Info, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
				{
					OutSuccess = Input_SafeAddEvent(Context, WorldContext, Info, Log);
					return OutSuccess;
				}

				static void ResolveChecked(const FString& Context, const UObject* WorldContext);
			};
		}
	}
}

using CsPlayerTransitionCacheLibray = NCsPlayer::NTransition::NCache::FLibrary;
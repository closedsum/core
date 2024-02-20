// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "CsManager_Level_Delegates.generated.h"

USTRUCT()
struct CSCORE_API FCsManager_Level_Delegates_STUB
{
	GENERATED_USTRUCT_BODY()

	FCsManager_Level_Delegates_STUB()
	{
	}
};

class ULevelStreaming;

// ChangeMap
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCsManagerLevel_ChangeMap_OnStart, const FString&, PreviousMap, const FString&, NewMap);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCsManagerLevel_ChangeMap_OnComplete, const FString&, PreviousMap, const FString&, NewMap);
// Streaming
/** Delegate Called when level is streamed in. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCsManagerLevel_LevelStreaming_OnLoaded, ULevelStreaming*, Level);
/** Delegate Called when level is streamed out. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCsManagerLevel_LevelStreaming_OnUnloaded, ULevelStreaming*, Level);
/** Delegate Called when level is added to the world and is visible. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCsManagerLevel_LevelStreaming_OnShown, ULevelStreaming*, Level);
/** Delegate Called when level is no longer visible, may not be removed from world yet. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCsManagerLevel_LevelStreaming_OnHidden, ULevelStreaming*, Level);

namespace NCsLevel
{
	namespace NManager
	{
		DECLARE_MULTICAST_DELEGATE_TwoParams(FChangeMap_OnStart, const FString& /*PreviousMap*/, const FString& /*NewMap*/);
		DECLARE_MULTICAST_DELEGATE_TwoParams(FChangeMap_OnComplete, const FString& /*PreviousMap*/, const FString& /*NewMap*/);

		namespace NLevel
		{
			namespace NStreaming
			{
				/** Delegate Called when level is streamed in. */
				DECLARE_MULTICAST_DELEGATE_OneParam(FOnLoaded, ULevelStreaming* /*Level*/);
				/** Delegate Called when level is streamed out. */
				DECLARE_MULTICAST_DELEGATE_OneParam(FOnUnloaded, ULevelStreaming* /*Level*/);
				/** Delegate Called when level is added to the world and is visible. */
				DECLARE_MULTICAST_DELEGATE_OneParam(FOnShown, ULevelStreaming* /*Level*/);
				/** Delegate Called when level is no longer visible, may not be removed from world yet. */
				DECLARE_MULTICAST_DELEGATE_OneParam(FOnHidden, ULevelStreaming* /*Level*/);
			}
		}
	}
}
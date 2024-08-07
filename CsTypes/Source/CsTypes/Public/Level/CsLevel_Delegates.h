// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "CsLevel_Delegates.generated.h"

USTRUCT()
struct CSTYPES_API FCsLevel_Delegates_STUB
{
	GENERATED_USTRUCT_BODY()

	FCsLevel_Delegates_STUB()
	{
	}
};

class UWorld;
class ULevelStreaming;

// Streaming
/** Delegate Called when level is added to the streaming list of levels for a World. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCsLevel_Streaming_OnAdded, UWorld*, World, ULevelStreaming*, LevelStreaming);

namespace NCsLevel
{
	namespace NStreaming
	{
		namespace NDynamic
		{
			struct CSTYPES_API FDelegates final
			{
			public:

				/** Delegate Called when level is streamed in. */
				DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAdded, UWorld* /*World*/, ULevelStreaming* /*LevelStreaming*/);

				static FOnAdded OnAdded_Event;
			};
		}
	}
}
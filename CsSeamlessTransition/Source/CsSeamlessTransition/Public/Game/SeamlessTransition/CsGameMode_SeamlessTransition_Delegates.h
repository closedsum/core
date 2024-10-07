// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "CsGameMode_SeamlessTransition_Delegates.generated.h"

USTRUCT()
struct CSSEAMLESSTRANSITION_API FCsGameMode_SeamlessTransition_Delegates_STUB
{
	GENERATED_USTRUCT_BODY()

	FCsGameMode_SeamlessTransition_Delegates_STUB()
	{
	}
};

// Seamless Travel
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCsGameMode_PostSeamlessTravel_OnComplete);

namespace NCsGameMode
{
	namespace NSeamlessTravel
	{
		namespace NPost
		{
			DECLARE_MULTICAST_DELEGATE(FOnComplete);
		}
	}
}
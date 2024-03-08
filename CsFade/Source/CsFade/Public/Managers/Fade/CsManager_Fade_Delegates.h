// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "CsManager_Fade_Delegates.generated.h"

USTRUCT()
struct CSFADE_API FCsManager_Fade_Delegates_STUB
{
	GENERATED_USTRUCT_BODY()

	FCsManager_Fade_Delegates_STUB()
	{
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCsManagerFade_OnFadeComplete);

namespace NCsFade
{
	namespace NManager
	{
		namespace NFade
		{
			DECLARE_MULTICAST_DELEGATE(FOnComplete);
		}
	}
}
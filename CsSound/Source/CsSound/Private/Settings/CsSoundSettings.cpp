// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Settings/CsSoundSettings.h"

// Cached
#pragma region

namespace NCsSoundSettings
{
	namespace NCached
	{
		namespace Str
		{
			CSSOUND_API CS_DEFINE_CACHED_STRING(Sound, "UCsSoundSettings::Sound");
		}
	}
}

#pragma endregion Cached

UCsSoundSettings::UCsSoundSettings(const FObjectInitializer& ObjectInitializer) : 
	Super(ObjectInitializer),
	Manager_Sound()
{
}
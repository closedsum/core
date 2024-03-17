// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Settings/CsFXSettings.h"

// Types
#include "Types/CsTypes_Macro.h"

// Cached
#pragma region

namespace NCsFXSettings
{
	namespace NCached
	{
		namespace Str
		{
			CSFX_API CS_DEFINE_CACHED_STRING(FX, "UCsFXSettings::FX");
		}
	}
}

#pragma endregion Cached

UCsFXSettings::UCsFXSettings(const FObjectInitializer& ObjectInitializer) : 
	Super(ObjectInitializer),
	Manager_FX()
{
}
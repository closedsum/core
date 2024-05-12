// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Settings/CsMenuSettings.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsMenuSettings)

// Cached
#pragma region

namespace NCsMenuSettings
{
	namespace NCached
	{
		namespace Str
		{
			CSMENU_API const FString MenuEvent = TEXT("UCsMenuSettings.ECsMenuEvent");
		}
	}
}

#pragma endregion Cached

UCsMenuSettings::UCsMenuSettings(const FObjectInitializer& ObjectInitializer) : 
	Super(ObjectInitializer),
	Manager_Menu()
{
}
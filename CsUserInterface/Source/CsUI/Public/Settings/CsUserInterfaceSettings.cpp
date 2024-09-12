// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Settings/CsUserInterfaceSettings.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsUserInterfaceSettings)

// Cached
#pragma region

namespace NCsUserInterfaceSettings
{
	namespace NCached
	{
		namespace Str
		{
			CSUI_API const FString WidgetActor = TEXT("UCsUserInterfaceSettings.ECsWidgetActor");
			CSUI_API const FString UserWidget = TEXT("UCsUserInterfaceSettings.ECsUserWidget");
			CSUI_API const FString UserWidgetPooled = TEXT("UCsUserInterfaceSettings.ECsUserWidgetPooled");
		}
	}
}

#pragma endregion Cached

UCsUserInterfaceSettings::UCsUserInterfaceSettings(const FObjectInitializer& ObjectInitializer) : 
	Super(ObjectInitializer)
{
}
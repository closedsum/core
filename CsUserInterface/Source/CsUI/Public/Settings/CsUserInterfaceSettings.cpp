// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Settings/CsUserInterfaceSettings.h"
#include "CsUI.h"

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

UCsUserInterfaceSettings::UCsUserInterfaceSettings(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}
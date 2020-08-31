// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Settings/CsDeveloperSettings.h"
#include "CsCore.h"

// Cached
#pragma region

namespace NCsDeveloperSettings
{
	namespace Str
	{
		CSCORE_API const FString InputActionMap = TEXT("UCsDeveloperSettings.ECsInputActionMap");
		CSCORE_API const FString GameEvent = TEXT("UCsDeveloperSettings.ECsGameEvent");
		CSCORE_API const FString FX = TEXT("UCsDeveloperSettings.ECsFX");
		CSCORE_API const FString Sound = TEXT("UCsDeveloperSettings.ECsSound");
	}
}

#pragma endregion Cached

UCsDeveloperSettings::UCsDeveloperSettings(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}
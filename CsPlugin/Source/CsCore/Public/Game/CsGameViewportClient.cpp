// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Game/CsGameViewportClient.h"
#include "CsCore.h"

// Settings
#include "Settings/CsDeveloperSettings.h"

UCsGameViewportClient::UCsGameViewportClient(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

// FViewportClient Interface
#pragma region

bool UCsGameViewportClient::InputKey(const FInputKeyEventArgs& EventArgs)
{
	UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>();

	TArray<int32>& Remap = Settings->Manager_Input.RemappedGamepadControllerIds;

	if (EventArgs.ControllerId < Remap.Num() &&
		EventArgs.IsGamepad())
	{
		FInputKeyEventArgs Args = EventArgs;

		Args.ControllerId = Remap[EventArgs.ControllerId];

		return Super::InputKey(Args);
	}
	return Super::InputKey(EventArgs);
}

bool UCsGameViewportClient::InputAxis(FViewport* InViewport, int32 ControllerId, FKey Key, float Delta, float DeltaTime, int32 NumSamples, bool bGamepad)
{
	UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>();

	TArray<int32>& Remap = Settings->Manager_Input.RemappedGamepadControllerIds;

	int32 AdjustedControlerId = ControllerId < Remap.Num() && Key.IsGamepadKey() ? Remap[ControllerId] : ControllerId;

	return Super::InputAxis(InViewport, AdjustedControlerId, Key, Delta, DeltaTime, NumSamples, bGamepad);
}

#pragma endregion FViewportClient Interface
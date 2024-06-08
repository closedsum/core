// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Game/CsGameViewportClient.h"

// Settings
#include "Settings/CsDeveloperSettings.h"
// Input
#include "GenericPlatform/GenericPlatformInputDeviceMapper.h"
#include "InputKeyEventArgs.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsGameViewportClient)

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

	// Remap the old int32 ControllerId value to the new InputDeviceId
	IPlatformInputDeviceMapper& DeviceMapper = IPlatformInputDeviceMapper::Get();
	FPlatformUserId UserId					 = PLATFORMUSERID_NONE;
	FInputDeviceId DeviceId					 = INPUTDEVICEID_NONE;
	DeviceMapper.RemapControllerIdToPlatformUserAndDevice(AdjustedControlerId, UserId, DeviceId);

	return Super::InputAxis(InViewport, DeviceId, Key, Delta, DeltaTime, NumSamples, bGamepad);
}

#pragma endregion FViewportClient Interface
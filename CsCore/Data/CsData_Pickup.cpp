// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_Pickup.h"
#include "CsCore.h"

ACsData_Pickup::ACsData_Pickup(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Movement
#pragma region

FVector ACsData_Pickup::GetSpawnVelocity() { return FVector::ZeroVector; }
FVector ACsData_Pickup::GetSpawnAcceleration() { return FVector::ZeroVector; }

#pragma endregion Movement

// FX
#pragma region

FCsFxElement* ACsData_Pickup::GetFX(const TCsPickupFX &FxType) { return nullptr; }

#pragma endregion FX

// Sound
#pragma region

FCsSoundElement* ACsData_Pickup::GetSound(const TCsPickupSound &SoundType) { return nullptr; }

#pragma endregion Sound
// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_Pickup.h"
#include "CsCore.h"

// Managers
#include "Managers/Sound/CsManager_Sound.h"

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

const bool& ACsData_Pickup::UseCollectSound() { return ECsCachedReferences::Ref::False; }

FCsSoundElement* ACsData_Pickup::GetSound(const TCsPickupSound &SoundType) { return nullptr; }

void ACsData_Pickup::PlaySound(UWorld* InWorld, const TCsPickupSound &SoundType, UObject* InOwner, UObject* InParent)
{
	FCsSoundElement* SoundElement   = GetSound(SoundType);
	ACsManager_Sound* Manager_Sound = ACsManager_Sound::Get(InWorld);

	Manager_Sound->Play(SoundElement, InOwner, InParent);
}

#pragma endregion Sound
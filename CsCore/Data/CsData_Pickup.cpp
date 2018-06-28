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

FCsFxElement* ACsData_Pickup::GetFX(const FECsPickupFX &FxType) { return nullptr; }

#pragma endregion FX

// Sound
#pragma region

const bool& ACsData_Pickup::UseCollectSound() { return ECsCached::Ref::False; }

FCsSoundElement* ACsData_Pickup::GetSound(const FECsPickupSound &SoundType) { return nullptr; }

void ACsData_Pickup::PlaySound(UWorld* InWorld, const FECsPickupSound &SoundType, UObject* InOwner, UObject* InParent)
{
	FCsSoundElement* SoundElement = GetSound(SoundType);

	if (!SoundElement->Get())
	{
		UE_LOG(LogCs, Warning, TEXT("ACsData_Pickup::PlaySound: Attempting to Play a NULL Sound."));
		return;
	}

	AICsManager_Sound* Manager_Sound = AICsManager_Sound::Get(InWorld);

	FCsSoundPayload* Payload = Manager_Sound->AllocatePayload();
	Payload->Set(SoundElement);
	Payload->Owner = InOwner;
	Payload->Parent = InParent;

	Manager_Sound->Play(Payload);
}

#pragma endregion Sound
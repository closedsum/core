// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_Pickup.h"
#include "CsCore.h"

// Managers
#include "Managers/Sound/CsManager_Sound.h"

UCsData_Pickup::UCsData_Pickup(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Movement
#pragma region

FVector UCsData_Pickup::GetSpawnVelocity() { return FVector::ZeroVector; }
FVector UCsData_Pickup::GetSpawnAcceleration() { return FVector::ZeroVector; }

#pragma endregion Movement

// FX
#pragma region

FCsFxElement* UCsData_Pickup::GetFX(const FECsPickupFX& FxType) { return nullptr; }

#pragma endregion FX

// Sound
#pragma region

const bool& UCsData_Pickup::UseCollectSound() { return NCsCached::Ref::False; }

FCsSoundElement* UCsData_Pickup::GetSound(const FECsPickupSound& SoundType) { return nullptr; }

void UCsData_Pickup::PlaySound(UWorld* InWorld, const FECsPickupSound& SoundType, UObject* InOwner, UObject* InParent)
{
	FCsSoundElement* SoundElement = GetSound(SoundType);

	if (!SoundElement->Get())
	{
		UE_LOG(LogCs, Warning, TEXT("UCsData_Pickup::PlaySound: Attempting to Play a NULL Sound."));
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
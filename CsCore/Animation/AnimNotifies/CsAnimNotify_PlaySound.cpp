// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "Animation/AnimNotifies/CsAnimNotify_PlaySound.h"
#include "CsCore.h"
#include "Common/CsCommon.h"

#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

// Manager
#include "Managers/Sound/CsManager_Sound.h"

/////////////////////////////////////////////////////
// UCsAnimNotify_PlaySound

UCsAnimNotify_PlaySound::UCsAnimNotify_PlaySound()
	: Super()
{
	VolumeMultiplier = 1.f;
	PitchMultiplier = 1.f;

#if WITH_EDITORONLY_DATA
	NotifyColor = FColor(196, 142, 255, 255);
#endif // WITH_EDITORONLY_DATA
}

FString UCsAnimNotify_PlaySound::GetNotifyName_Implementation() const
{
	if (Sound.ToString() == TEXT(""))
		Super::GetNotifyName_Implementation();

	const USoundCue* S = Sound_Internal.IsValid() ? Sound_Internal.Get() : nullptr;

	if (S)
	{
		return S->GetName();
	}
	else
	{
		return Super::GetNotifyName_Implementation();
	}
}

void UCsAnimNotify_PlaySound::Notify(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation)
{
	UWorld* CurrentWorld = MeshComp->GetWorld();

	if (Sound.ToString() == TEXT(""))
		return;

	USoundCue* S = GetSound();

	if (!S)
	{
		S			   = Sound.LoadSynchronous();
		Sound_Internal = S;
	}

	const bool InGame = UCsCommon::IsPlayInGame(CurrentWorld) || UCsCommon::IsPlayInPIE(CurrentWorld);

	// Use Sound Manager
	if (InGame)
	{
		ACsManager_Sound* Manager_Sound = ACsManager_Sound::Get(CurrentWorld);

		SoundElement.Sound = Sound;
	}
	else
	{
		if (bFollow)
		{
			UGameplayStatics::SpawnSoundAttached(S, MeshComp, AttachName, FVector(ForceInit), EAttachLocation::KeepRelativeOffset, false, VolumeMultiplier, PitchMultiplier);
		}
		else
		{
			UGameplayStatics::PlaySoundAtLocation(CurrentWorld, S, MeshComp->GetComponentLocation(), VolumeMultiplier, PitchMultiplier);
		}
	}
}

USoundCue* UCsAnimNotify_PlaySound::GetSound() { return Sound_Internal.IsValid() ? Sound_Internal.Get() : nullptr; }
// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "Animation/AnimNotifies/CsAnimNotify_PlaySound.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Common.h"
#include "Library/CsLibrary_World.h"

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
#if WITH_EDITORONLY_DATA
	NotifyColor = FColor(196, 142, 255, 255);
#endif // WITH_EDITORONLY_DATA
}

FString UCsAnimNotify_PlaySound::GetNotifyName_Implementation() const
{
	if (Sound.Sound)
	{
		return Sound.Sound->GetName();
	}
	else
	{
		return Super::GetNotifyName_Implementation();
	}
}

void UCsAnimNotify_PlaySound::Notify(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation)
{
	if (!Sound.Sound)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsAnimNotify_PlaySound::Notify (%s): No Sound set on Notify for Animation: %s"), *(MeshComp->SkeletalMesh->GetName()), *(Animation->GetName()));
		return;
	}

	UWorld* CurrentWorld = MeshComp->GetWorld();

	// TODO: need to check case of AnimInstance

	const bool InGame = FCsLibrary_World::IsPlayInGame(CurrentWorld) || FCsLibrary_World::IsPlayInPIE(CurrentWorld);

	// Use Sound Manager
	/*
	if (InGame)
	{
		AICsManager_Sound* Manager_Sound = AICsManager_Sound::Get(CurrentWorld);

		SoundElement.Set(Sound.Sound);
		SoundElement.Type = Sound.Type;
		SoundElement.Priority = Sound.Priority;
		SoundElement.Duration = Sound.Sound->GetDuration();
		SoundElement.IsLooping = false;
		SoundElement.VolumeMultiplier = Sound.VolumeMultiplier;
		SoundElement.PitchMultiplier = Sound.PitchMultiplier;
		SoundElement.Bone = Sound.Bone;

		FCsSoundPayload* Payload = Manager_Sound->AllocatePayload();
		Payload->Set(&SoundElement);
		Payload->Owner = MeshComp->GetOwner() ? Cast<UObject>(MeshComp->GetOwner()) : Cast<UObject>(MeshComp->GetAttachParent());
		Payload->Parent = MeshComp;

		Manager_Sound->Play(Payload);
	}
	// Editor
	else
	{
		if (Sound.Bone != NAME_None)
		{
			UGameplayStatics::SpawnSoundAttached(Sound.Sound, MeshComp, Sound.Bone, FVector(ForceInit), EAttachLocation::KeepRelativeOffset, false, Sound.VolumeMultiplier, Sound.PitchMultiplier);
		}
		else
		{
			UGameplayStatics::PlaySoundAtLocation(CurrentWorld, Sound.Sound, MeshComp->GetComponentLocation(), Sound.VolumeMultiplier, Sound.PitchMultiplier);
		}
	}
	*/
}
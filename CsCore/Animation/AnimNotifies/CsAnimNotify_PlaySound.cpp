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
	UWorld* CurrentWorld = MeshComp->GetWorld();

	// TODO: need to check case of AnimInstance

	const bool InGame = UCsCommon::IsPlayInGame(CurrentWorld) || UCsCommon::IsPlayInPIE(CurrentWorld);

	// Use Sound Manager
	if (InGame &&
		Sound.Sound)
	{
		ACsManager_Sound* Manager_Sound = ACsManager_Sound::Get(CurrentWorld);

		SoundElement.Set(Sound.Sound);
		SoundElement.Type = Sound.Type;
		SoundElement.Priority = Sound.Priority;
		SoundElement.Duration = Sound.Sound->GetDuration();
		SoundElement.IsLooping = false;
		SoundElement.VolumeMultiplier = Sound.VolumeMultiplier;
		SoundElement.PitchMultiplier = Sound.PitchMultiplier;
		SoundElement.Bone = Sound.Bone;

		Manager_Sound->Play(&SoundElement, MeshComp->GetAttachParent(), MeshComp);
	}
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
}
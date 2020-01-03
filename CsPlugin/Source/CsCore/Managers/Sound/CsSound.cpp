// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Sound/CsSound.h"
#include "CsCore.h"
#include "Library/CsLibrary_Common.h"

ACsSound::ACsSound(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	AudioComponent = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("AudioComponent"));

	AudioComponent->bAutoActivate				 = false;
	AudioComponent->bStopWhenOwnerDestroyed		 = true;
	AudioComponent->bShouldRemainActiveIfDropped = false;
	AudioComponent->Mobility				     = EComponentMobility::Movable;

	RootComponent = AudioComponent;

	DefaultAttenuation = ObjectInitializer.CreateDefaultSubobject<USoundAttenuation>(this, TEXT("AudioAttenuation"));

	FSoundAttenuationSettings NewAttenuationSettings;
	DefaultAttenuation->Attenuation					 = NewAttenuationSettings;
	DefaultAttenuation->Attenuation.AttenuationShape = EAttenuationShape::Sphere;
	AudioComponent->AttenuationSettings				 = DefaultAttenuation;

	SetRemoteRoleForBackwardsCompat(ROLE_None);
	bReplicates		   = false;
	bReplicateMovement = false;
	bHidden			   = true;
	bCanBeDamaged	   = false;
}

void ACsSound::Init(const int32 &Index, const FECsSoundType &InType)
{
	PoolIndex = Index;
	Type = InType;

	Cache.Set(Index, this);
	Cache.Type = Type;
}

void ACsSound::Init(const int32 &Index)
{
	Init(Index, EMCsSoundType::Get().GetMAX());
}

void ACsSound::Allocate(FCsSoundPayload* Payload)
{
	Cache.Init(Payload, GetWorld()->GetTimeSeconds(), GetWorld()->GetRealTimeSeconds(), UCsLibrary_Common::GetCurrentFrame(GetWorld()));

	Play();
}

void ACsSound::DeAllocate()
{
	Super::DeAllocate();

	Cache.Reset();
}

bool ACsSound::Play()
{
	if (!AudioComponent)
	{
		UE_LOG(LogCs, Warning, TEXT("ACsSound::Play (%s): AudioComponent is NULL."), *GetName())
		return false;
	}

	USoundCue* Cue = Cache.GetCue();
	AudioComponent->SetSound(Cue);

	if (const FSoundAttenuationSettings* Settings = Cue->GetAttenuationSettingsToApply())
		AudioComponent->AttenuationSettings->Attenuation = *Settings;

#if WITH_EDITOR
	if (UCsLibrary_Common::IsPlayInEditorPreview(GetWorld()))
	{
		AudioComponent->bAllowSpatialization = false;
		AudioComponent->bIsUISound = true;
	}
	else
#endif // #if WITH_EDITOR
	{
		AudioComponent->bAllowSpatialization = Cache.bSpatialize;
	}
	AudioComponent->AttenuationSettings->Attenuation.bSpatialize = Cache.bSpatialize;

	AudioComponent->SetVolumeMultiplier(Cache.VolumeMultiplier);
	AudioComponent->SetPitchMultiplier(Cache.PitchMultiplier);

	SetActorHiddenInGame(false);

	UObject* Parent = Cache.GetParent();

	// Actors
	if (AActor* Actor = Cast<AActor>(Parent))
	{
		SetActorLocation(Actor->GetActorLocation());
		AttachToActor(Actor, FAttachmentTransformRules::KeepRelativeTransform, Cache.Bone);
	}
	// Component
	else
	if (USceneComponent*Component = Cast<USceneComponent>(Parent))
	{
		SetActorLocation(Component->GetComponentLocation());
		AttachToComponent(Component, FAttachmentTransformRules::KeepRelativeTransform, Cache.Bone);
	}
	else
	{
		SetActorLocation(Cache.Location);
	}

	AudioComponent->Activate(true);
	AudioComponent->Play();
	return true;
}

bool ACsSound::Stop()
{
	SetActorRelativeLocation(FVector::ZeroVector, false, nullptr, ETeleportType::TeleportPhysics);
	SetActorLocation(FVector(0.0f, 0.0f, 10000.0f), false, nullptr, ETeleportType::TeleportPhysics);
	DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);

	if (AudioComponent)
	{
		AudioComponent->Deactivate();
		AudioComponent->Stop();

		AudioComponent->SetVolumeMultiplier(1.f);
		AudioComponent->SetPitchMultiplier(1.f);

		FSoundAttenuationSettings NewAttenuationSettings;
		DefaultAttenuation->Attenuation = NewAttenuationSettings;
		DefaultAttenuation->Attenuation.AttenuationShape = EAttenuationShape::Sphere;
		AudioComponent->AttenuationSettings = DefaultAttenuation;

		AudioComponent->SetSound(nullptr);

		AudioComponent->SetWorldLocation(FVector(10000.0f, 10000.0f, 10000.0f)); // reset the audio component 
		AudioComponent->bAllowSpatialization = false;
	}
	SetActorHiddenInGame(true);

	return true;
}
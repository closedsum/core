// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Sound/CsSoundPooledImpl.h"
#include "CsCore.h"

#include "Library/CsLibrary_Common.h"
// Sound
#include "Managers/Sound/Cache/CsSoundPooledCacheImpl.h"

ACsSoundPooledImpl::ACsSoundPooledImpl(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	AudioComponent = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("AudioComponent"));

	AudioComponent->bAutoActivate				 = false;
	AudioComponent->bStopWhenOwnerDestroyed		 = true;
	AudioComponent->bShouldRemainActiveIfDropped = false;
	AudioComponent->Mobility				     = EComponentMobility::Movable;

	RootComponent = AudioComponent;

	/*
	SoundAttenuation = ObjectInitializer.CreateDefaultSubobject<USoundAttenuation>(this, TEXT("SoundAttenuation"));

	FSoundAttenuationSettings NewAttenuationSettings;
	SoundAttenuation->Attenuation					 = NewAttenuationSettings;
	SoundAttenuation->Attenuation.AttenuationShape   = EAttenuationShape::Sphere;
	AudioComponent->AttenuationSettings				 = SoundAttenuation;
	*/

	SetRemoteRoleForBackwardsCompat(ROLE_None);
	bReplicates		   = false;
	SetReplicatingMovement(false);
	SetHidden(true);
	SetCanBeDamaged(false);
}

// UObject Interface
#pragma region

void ACsSoundPooledImpl::BeginDestroy()
{
	Super::BeginDestroy();

	if (Cache)
	{
		delete Cache;
		Cache = nullptr;
	}
}

#pragma endregion UObject Interface

// AActor Interface
#pragma region

void ACsSoundPooledImpl::BeginPlay()
{
	Super::BeginPlay();

	AudioComponent->SetComponentTickEnabled(false);

	SetActorTickEnabled(false);

	ConstructCache();
}

#pragma endregion AActor Interface

// ICsUpdate
#pragma region

void ACsSoundPooledImpl::Update(const FCsDeltaTime& DeltaTime)
{
}

#pragma endregion ICsUpdate

void ACsSoundPooledImpl::ConstructCache()
{
	Cache = new FCsSoundPooledCacheImpl();
}

// ICsPooledObject
#pragma region

ICsPooledObjectCache* ACsSoundPooledImpl::GetCache() const
{
	return Cache;
}

void ACsSoundPooledImpl::Allocate(ICsPooledObjectPayload* Payload)
{
	Play();
}

void ACsSoundPooledImpl::Deallocate()
{
}

#pragma endregion ICsPooledObject

bool ACsSoundPooledImpl::Play()
{
	checkf(AudioComponent, TEXT("ACsSoundPooledImpl::Play: AudioComponent is NULL."));

	/*
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
	*/
	return true;
}

bool ACsSoundPooledImpl::Stop()
{
	/*
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
	*/
	return true;
}
// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Sound/CsSound.h"
#include "CsCore.h"

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

void ACsSound::Init(const int32 &Index)
{
	PoolIndex = Index;

	Cache.Set(Index, this);
}

template<typename T>
void ACsSound::Allocate(const uint16& ActiveIndex, FCsSoundElement* InElement, const float &Time, const float &RealTime, const uint64 &Frame, UObject* InOwner, UObject* InParent, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&))
{
	Cache.Init<T>(ActiveIndex, InElement, Time, RealTime, Frame, InOwner, InParent, InObject, OnDeAllocate);
}

template<typename T>
void ACsSound::Allocate(const uint16& ActiveIndex, FCsSoundElement* InElement, const float &Time, const float &RealTime, const uint64 &Frame, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&))
{
	Cache.Init<T>(ActiveIndex, InElement, Time, RealTime, Frame, InObject, OnDeAllocate);
}

template<typename T>
void ACsSound::Allocate(const uint16& ActiveIndex, FCsSoundElement* InElement, const float &Time, const float &RealTime, const uint64 &Frame, UObject* InOwner, const FVector &InLocation, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&))
{
	Cache.Init<T>(ActiveIndex, InElement, Time, RealTime, Frame, InOwner, InLocation, InObject, OnDeAllocate);
}

template<typename T>
void ACsSound::Allocate(const uint16& ActiveIndex, FCsSoundElement* InElement, const float &Time, const float &RealTime, const uint64 &Frame, const FVector &InLocation, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&))
{
	Cache.Init<T>(ActiveIndex, InElement, Time, RealTime, Frame, nullptr, InLocation, InObject, OnDeAllocate);
}

void ACsSound::Allocate(const uint16& ActiveIndex, FCsSoundElement* InElement, const float &Time, const float &RealTime, const uint64 &Frame, UObject* InOwner, UObject* InParent, const FVector &InLocation)
{
	Cache.Init(ActiveIndex, InElement, Time, RealTime, Frame, InOwner, InParent, InLocation);
}

void ACsSound::Allocate(const uint16& ActiveIndex, FCsSoundElement* InElement, const float &Time, const float &RealTime, const uint64 &Frame, UObject* InOwner, UObject* InParent)
{
	Cache.Init(ActiveIndex, InElement, Time, RealTime, Frame, InOwner, InParent);
}

void ACsSound::Allocate(const uint16& ActiveIndex, FCsSoundElement* InElement, const float &Time, const float &RealTime, const uint64 &Frame, UObject* InOwner, const FVector &InLocation)
{
	Cache.Init(ActiveIndex, InElement, Time, RealTime, Frame, InOwner, InLocation);
}

void ACsSound::Allocate(const uint16& ActiveIndex, FCsSoundElement* InElement, const float &Time, const float &RealTime, const uint64 &Frame, const FVector &InLocation)
{
	Cache.Init(ActiveIndex, InElement, Time, RealTime, Frame, InLocation);
}

void ACsSound::Allocate(const uint16& ActiveIndex, FCsSoundElement* InElement, const float &Time, const float &RealTime, const uint64 &Frame)
{
	Cache.Init(ActiveIndex, InElement, Time, RealTime, Frame);
}

void ACsSound::DeAllocate()
{
	Super::DeAllocate();

	Cache.Reset();
}

bool ACsSound::Play()
{
	/*
	if (!AudioComponent)
		return false;

	StartTime = inStartTime;

	AudioComponent->SetSound(Cue);
	AudioComponent->AttenuationSettings->Attenuation = *(Cue->GetAttenuationSettingsToApply());
	SetActorHiddenInGame(false);

	// Actors
	if (AActor* Actor = Cast<AActor>(Parent))
	{
		SetActorLocation(Actor->GetActorLocation());
		AttachToActor(Actor, FAttachmentTransformRules::KeepRelativeTransform, NAME_None);
	}
	// Component
	else
	if (USceneComponent*Component = Cast<USceneComponent>(Parent))
	{
		SetActorLocation(Component->GetComponentLocation());
		AttachToComponent(Component, FAttachmentTransformRules::KeepRelativeTransform, NAME_None);
	}
	else
	{
		SetActorLocation(Location);
	}

	AudioComponent->Activate(true);
	AudioComponent->Play(StartTime);
	*/
	return true;
}

bool ACsSound::Stop()
{
	SetActorRelativeLocation(FVector::ZeroVector, false, nullptr, ETeleportType::TeleportPhysics);
	SetActorLocation(FVector(0.0f, 0.0f, 10000.0f), false, nullptr, ETeleportType::TeleportPhysics);
	DetachRootComponentFromParent();

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
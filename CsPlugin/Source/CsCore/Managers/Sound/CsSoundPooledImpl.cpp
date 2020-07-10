// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Sound/CsSoundPooledImpl.h"
#include "CsCore.h"

#include "Library/CsLibrary_Common.h"
// Sound
#include "Managers/Sound/Cache/CsSoundPooledCacheImpl.h"
#include "Managers/Sound/Payload/CsSoundPooledPayloadImpl.h"

// Cached
#pragma region

namespace NCsSoundPooledImplCached
{
	namespace Str
	{
		const FString Update = TEXT("ACsSoundPooledImpl::Update");
		const FString Allocate = TEXT("ACsSoundPooledImpl::Allocate");
		const FString Play = TEXT("ACsSoundPooledImpl::Play");
	}
}

#pragma endregion Cached

ACsSoundPooledImpl::ACsSoundPooledImpl(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	AudioComponent = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("AudioComponent"));

	AudioComponent->bAutoActivate				 = false;
	AudioComponent->bStopWhenOwnerDestroyed		 = true;
	AudioComponent->bShouldRemainActiveIfDropped = false;
	AudioComponent->Mobility				     = EComponentMobility::Movable;
	AudioComponent->PrimaryComponentTick.bStartWithTickEnabled = false;

	AudioComponent->Deactivate();

	RootComponent = AudioComponent;

	PrimaryActorTick.bCanEverTick		   = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

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
	using namespace NCsSoundPooledImplCached;

	// TODO: This should be opaque
	
	FCsSoundPooledCacheImpl* CacheImpl = NCsInterfaceMap::PureStaticCastChecked<FCsSoundPooledCacheImpl>(Str::Update, Cache);

	CacheImpl->Update(DeltaTime);
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
	using namespace NCsSoundPooledImplCached;

	Cache->Allocate(Payload);

	ICsSoundPooledPayload* SoundPayload = NCsInterfaceMap::GetInterfaceChecked<ICsSoundPooledPayload>(Str::Allocate, Payload);

	Play(SoundPayload);
}

void ACsSoundPooledImpl::Deallocate()
{
	Stop();

	Cache->Deallocate();
}

#pragma endregion ICsPooledObject

void ACsSoundPooledImpl::Play(ICsSoundPooledPayload* Payload)
{
	using namespace NCsSoundPooledImplCached;

	checkf(AudioComponent, TEXT("ACsSoundPooledImpl::Play: AudioComponent is NULL."));
	
	USoundBase* Sound = Payload->GetSound();

	checkf(Sound, TEXT("ACsSoundPooledImpl::Play: Sound is NULL."));

	SetActorTickEnabled(true);

	ICsPooledObjectPayload* ObjectPayload = NCsInterfaceMap::GetInterfaceChecked<ICsPooledObjectPayload>(Str::Allocate, Payload);

	// If the Parent is set, attach the Sound to the Parent
	if (USceneComponent* Parent = Cast<USceneComponent>(ObjectPayload->GetParent()))
	{
		AttachToComponent(Parent, NCsAttachmentTransformRules::ToRule(Payload->GetAttachmentTransformRule()), Payload->GetBone());

		const FTransform& Transform = Payload->GetTransform();
		const int32& TransformRules = Payload->GetTransformRules();

		// Location | Rotation | Scale
		if (TransformRules == NCsTransformRules::All)
		{
			SetActorRelativeTransform(Transform);
		}
		else
		{
			// Location
			if (CS_TEST_BLUEPRINT_BITFLAG(TransformRules, ECsTransformRules::Location))
			{
				SetActorRelativeLocation(Transform.GetLocation());
			}
			// Rotation
			if (CS_TEST_BLUEPRINT_BITFLAG(TransformRules, ECsTransformRules::Rotation))
			{
				SetActorRelativeRotation(Transform.GetRotation().Rotator());
			}
			// Scale
			if (CS_TEST_BLUEPRINT_BITFLAG(TransformRules, ECsTransformRules::Scale))
			{
				SetActorRelativeScale3D(Transform.GetScale3D());
			}
		}
	}
	// NO Parent, set the World Transform of the Sound
	else
	{
		SetActorTransform(Payload->GetTransform());
	}

	AudioComponent->SetSound(Sound);
	AudioComponent->AttenuationSettings = Payload->GetSoundAttenuation();

	// Check for 3D sound (set bAllowSpatialization)
	if (AudioComponent->AttenuationSettings)
	{
		if (AudioComponent->AttenuationSettings->Attenuation.bSpatialize)
		{
			AudioComponent->bAllowSpatialization = true;
		}
	}
	else
	{
		if (const FSoundAttenuationSettings* AttenuationSettings = Sound->GetAttenuationSettingsToApply())
		{
			AudioComponent->bAllowSpatialization = AttenuationSettings->bSpatialize;
		}
	}
	AudioComponent->Activate(true);
	AudioComponent->Play();
}

void ACsSoundPooledImpl::Stop()
{
	checkf(AudioComponent, TEXT("ACsSoundPooledImpl::Stop: AudioComponent is NULL."));

	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	AudioComponent->Deactivate();
	AudioComponent->Stop();

	AudioComponent->SetVolumeMultiplier(1.f);
	AudioComponent->SetPitchMultiplier(1.f);

	AudioComponent->AttenuationSettings = nullptr;

	AudioComponent->SetSound(nullptr);
	SetActorTickEnabled(false);

	AudioComponent->bAllowSpatialization = false;
}
// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Sound/CsSoundPooledImpl.h"
#include "CsCore.h"

#include "Library/CsLibrary_Common.h"
// Sound
#include "Managers/Sound/Cache/CsCache_SoundImpl.h"
#include "Managers/Sound/Payload/CsPayload_SoundImpl.h"

#if WITH_EDITOR
// Library
#include "Library/CsLibrary_World.h"
#endif // #if WITH_EDITOR

// Cached
#pragma region

namespace NCsSoundPooledImpl
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsSoundPooledImpl, Update);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsSoundPooledImpl, Allocate);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsSoundPooledImpl, Play);
		}
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

void ACsSoundPooledImpl::PostInitializeComponents()
{
	Super::PostInitializeComponents();

#if WITH_EDITOR
	if (FCsLibrary_World::IsPlayInEditor(GetWorld()) ||
		FCsLibrary_World::IsPlayInEditorPreview(GetWorld()))
	{
		ConstructCache();
	}
#endif // #if WITH_EDITOR

}
void ACsSoundPooledImpl::FellOutOfWorld(const UDamageType& DmgType)
{
	Cache->QueueDeallocate();
}

void ACsSoundPooledImpl::OutsideWorldBounds()
{
	Cache->QueueDeallocate();
}

#pragma endregion AActor Interface

// ICsUpdate
#pragma region

void ACsSoundPooledImpl::Update(const FCsDeltaTime& DeltaTime)
{
	using namespace NCsSoundPooledImpl::NCached;

	// TODO: This should be opaque
	
	typedef NCsSound::NCache::FImpl CacheImplType;

	CacheImplType* CacheImpl = NCsInterfaceMap::PureStaticCastChecked<CacheImplType>(Str::Update, Cache);

	CacheImpl->Update(DeltaTime);
}

#pragma endregion ICsUpdate

// ICsPause
#pragma region

void ACsSoundPooledImpl::Pause(bool bPaused)
{
	checkf(AudioComponent, TEXT("ACsSoundPooledImpl::Pause: AudioComponent is NULL."));

	AudioComponent->SetPaused(bPaused);
}

#pragma endregion ICsPause

void ACsSoundPooledImpl::ConstructCache()
{
	typedef NCsSound::NCache::FImpl CacheImplType;

	Cache = new CacheImplType();
}

// ICsPooledObject
#pragma region

#define CacheType NCsPooledObject::NCache::ICache
CacheType* ACsSoundPooledImpl::GetCache() const
{
#undef CacheType
	return Cache;
}

#define PooledPayloadType NCsPooledObject::NPayload::IPayload
void ACsSoundPooledImpl::Allocate(PooledPayloadType* Payload)
{
#undef PooledPayloadType

	using namespace NCsSoundPooledImpl::NCached;

	Cache->Allocate(Payload);

	typedef NCsSound::NPayload::IPayload SoundPayloadType;

	SoundPayloadType* SoundPayload = NCsInterfaceMap::GetInterfaceChecked<SoundPayloadType>(Str::Allocate, Payload);

	Play(SoundPayload);
}

void ACsSoundPooledImpl::Deallocate()
{
	Stop();

	Cache->Deallocate();
}

#pragma endregion ICsPooledObject

#define SoundPayloadType NCsSound::NPayload::IPayload
void ACsSoundPooledImpl::Play(SoundPayloadType* Payload)
{
#undef SoundPayloadType

	using namespace NCsSoundPooledImpl::NCached;

	checkf(AudioComponent, TEXT("ACsSoundPooledImpl::Play: AudioComponent is NULL."));
	
	// TODO: Add IsValidChecked in PayloadLibrary

	USoundBase* Sound = Payload->GetSound();

	checkf(Sound, TEXT("ACsSoundPooledImpl::Play: Sound is NULL."));

	SetActorTickEnabled(true);

	typedef NCsPooledObject::NPayload::IPayload PooledPayloadType;

	PooledPayloadType* PooledPayload = NCsInterfaceMap::GetInterfaceChecked<PooledPayloadType>(Str::Play, Payload);

	// If the Parent is set, attach the Sound to the Parent
	USceneComponent* Parent = nullptr;

	UObject* Object = PooledPayload->GetParent();

		// SceneComponent
	if (USceneComponent* Component = Cast<USceneComponent>(Object))
		Parent = Component;
		// Actor -> Get RootComponent
	else
	if (AActor* Actor = Cast<AActor>(Object))
		Parent = Actor->GetRootComponent();

	if (Parent)
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
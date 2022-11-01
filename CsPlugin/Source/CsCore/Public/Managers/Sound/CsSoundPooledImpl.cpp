// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Sound/CsSoundPooledImpl.h"
#include "CsCore.h"

// CVars
#include "Managers/Sound/CsCVars_Sound.h"
// Types
#include "Types/CsTypes_Math.h"
// Library
#include "Managers/Pool/Payload/CsLibrary_Payload_PooledObject.h"
#include "Library/CsLibrary_Valid.h"
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
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsSoundPooledImpl, Stop);
		}
	}
}

#pragma endregion Cached

ACsSoundPooledImpl::ACsSoundPooledImpl(const FObjectInitializer& ObjectInitializer) : 
	Super(ObjectInitializer),
	AudioComponent(nullptr),
	Cache(nullptr),
	CacheImpl(nullptr),
	PreserveChangesToDefaultMask(0),
	ChangesToDefaultMask(0),
	Type(),
	AttachToBone(NAME_None)
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
	typedef NCsWorld::FLibrary WorldLibrary;

	if (WorldLibrary::IsPlayInEditor(GetWorld()) ||
		WorldLibrary::IsPlayInEditorPreview(GetWorld()))
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

	Cache	  = new CacheImplType();
	CacheImpl = (CacheImplType*)Cache;
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

	PreserveChangesToDefaultMask = Payload->GetPreserveChangesFromDefaultMask();

	typedef NCsPooledObject::NPayload::FLibrary PooledPayloadLibrary;
	typedef NCsSound::NPayload::IPayload SoundPayloadType;

	SoundPayloadType* SoundPayload = PooledPayloadLibrary::GetInterfaceChecked<SoundPayloadType>(Str::Allocate, Payload);

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

	const FString& Context = Str::Play;

	CS_IS_PTR_NULL_CHECKED(AudioComponent)
	
	// TODO: Add IsValidChecked in PayloadLibrary

	USoundBase* Sound = Payload->GetSound();

	CS_IS_PTR_NULL_CHECKED(Sound)

	SetActorTickEnabled(true);

	typedef NCsPooledObject::NPayload::IPayload PooledPayloadType;

	PooledPayloadType* PooledPayload = NCsInterfaceMap::GetInterfaceChecked<PooledPayloadType>(Str::Play, Payload);

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

	// Attach and set Transform
	if (AudioComponent->bAllowSpatialization)
		Handle_AttachAndSetTransform(PooledPayload, Payload);

	AudioComponent->Activate(true);
	AudioComponent->Play();

	CS_NON_SHIPPING_EXPR(LogChangeCounter());
}

void ACsSoundPooledImpl::Stop()
{
	using namespace NCsSoundPooledImpl::NCached;

	const FString& Context = Str::Stop;

	CS_IS_PTR_NULL_CHECKED(AudioComponent)

	if (AudioComponent->bAllowSpatialization)
		Handle_ClearAttachAndTransform();

	AudioComponent->Deactivate();
	AudioComponent->Stop();

	AudioComponent->SetVolumeMultiplier(1.f);
	AudioComponent->SetPitchMultiplier(1.f);

	AudioComponent->AttenuationSettings = nullptr;

	AudioComponent->SetSound(nullptr);
	SetActorTickEnabled(false);

	AudioComponent->bAllowSpatialization = false;

	CS_NON_SHIPPING_EXPR(LogChangeCounter());
}

#define PooledPayloadType NCsPooledObject::NPayload::IPayload
#define SoundPayloadType NCsSound::NPayload::IPayload
void ACsSoundPooledImpl::Handle_AttachAndSetTransform(PooledPayloadType* Payload, SoundPayloadType* SoundPayload)
{
#undef PooledPayloadType
#undef SoundPayloadType

	CS_NON_SHIPPING_EXPR(Log_AttachAndSetTransform(Payload, SoundPayload));

	// If the Parent is set, attach the SkeletalMeshActor to the Parent
	USceneComponent* Parent = nullptr;

	UObject* Object = Payload->GetParent();

	// SceneComponent
	if (USceneComponent* Component = Cast<USceneComponent>(Object))
		Parent = Component;
	// Actor -> Get RootComponent
	else
	if (AActor* Actor = Cast<AActor>(Object))
		Parent = Actor->GetRootComponent();

	const FTransform& Transform = SoundPayload->GetTransform();
	const int32& TransformRules = SoundPayload->GetTransformRules();

	typedef NCsSound::NPayload::EChange ChangeType;
	typedef NCsSound::NPayload::NChange::FCounter ChangeCounter;
	#define ChangeHelper NCsSound::NPayload::NChange

	if (Parent)
	{
		const ECsAttachmentTransformRules& Rule = SoundPayload->GetAttachmentTransformRule();
		const FName& Bone						= SoundPayload->GetBone();

		bool PerformAttach = true;
		bool IsPreserved = false;

		// If Attach and Transform are the SAME, Do Nothing
		if (GetRootComponent()->GetAttachParent() == Parent &&
			AttachToBone == Bone)
		{
			// Check Attachment Rule
			IsPreserved   = ChangeHelper::HasAttach(PreserveChangesToDefaultMask & ChangesToDefaultMask, Rule);
			PerformAttach = !IsPreserved;

			if (IsPreserved)
				ChangeCounter::Get().AddPreserved();
		}

		// Attach
		if (PerformAttach)
		{
			AttachToBone = Bone;

			GetRootComponent()->AttachToComponent(Parent, NCsAttachmentTransformRules::ToRule(Rule), Bone);
			ChangeCounter::Get().AddChanged();
		}

		CS_SET_BITFLAG(ChangesToDefaultMask, ChangeHelper::FromTransformAttachmentRule(Rule));

		bool PerformTransform = true;
		IsPreserved			  = false;

		// If Transform has NOT changed, don't update it.
		if (CS_TEST_BITFLAG(PreserveChangesToDefaultMask, ChangeType::Transform) &&
			CS_TEST_BITFLAG(ChangesToDefaultMask, ChangeType::Transform))
		{
			IsPreserved		 = NCsTransformRules::AreTransformsEqual(GetRootComponent()->GetRelativeTransform(), Transform, TransformRules);
			PerformTransform = !IsPreserved;

			if (IsPreserved)
				ChangeCounter::Get().AddPreserved();
		}

		// Set Transform
		if (PerformTransform)
		{
			NCsTransformRules::SetRelativeTransform(GetRootComponent(), Transform, TransformRules);
			ChangeCounter::Get().AddChanged();
		}
		CS_SET_BITFLAG(ChangesToDefaultMask, ChangeType::Transform);
	}
	// NO Parent, set the World Transform of the SkeletalMeshComponent
	else
	{
		bool PerformTransform = true;
		bool IsPreserved	  = false;

		// If Transform has NOT changed, don't update it.
		if (CS_TEST_BITFLAG(PreserveChangesToDefaultMask, ChangeType::Transform) &&
			CS_TEST_BITFLAG(ChangesToDefaultMask, ChangeType::Transform))
		{
			IsPreserved		 = NCsTransformRules::AreTransformsEqual(GetRootComponent()->GetRelativeTransform(), Transform, TransformRules);
			PerformTransform = !IsPreserved;

			if (IsPreserved)
				ChangeCounter::Get().AddPreserved();
		}

		if (PerformTransform)
		{
			NCsTransformRules::SetTransform(this, Transform, TransformRules);
			ChangeCounter::Get().AddChanged();
		}

		AttachToBone = NAME_None;
	}
	CS_SET_BITFLAG(ChangesToDefaultMask, ChangeType::Transform);

	#undef ChangeHelper
}

#define PooledPayloadType NCsPooledObject::NPayload::IPayload
#define SoundPayloadType NCsSound::NPayload::IPayload
void ACsSoundPooledImpl::Log_AttachAndSetTransform(PooledPayloadType* Payload, SoundPayloadType* SoundPayload)
{
#undef PooledPayloadType
#undef SoundPayloadType

}

void ACsSoundPooledImpl::Handle_ClearAttachAndTransform()
{
	typedef NCsSound::NPayload::EChange ChangeType;
	typedef NCsSound::NPayload::NChange::FCounter ChangeCounter;
	#define ChangeHelper NCsSound::NPayload::NChange
	
	const uint32 Mask = PreserveChangesToDefaultMask & ChangesToDefaultMask;

	// If Attached, check if the Attach should be PERSERVED
	if (GetRootComponent()->GetAttachParent())
	{
		if (ChangeHelper::HasAttach(Mask))
		{
			// Do Nothing
			ChangeCounter::Get().AddPreserved();
			ChangeCounter::Get().AddPreserved();
		}
		else
		{
			DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
			SetActorRelativeTransform(FTransform::Identity);
			CS_CLEAR_BITFLAG(ChangesToDefaultMask, ChangeHelper::GetAttachAsMask(Mask));
			CS_CLEAR_BITFLAG(ChangesToDefaultMask, ChangeType::Transform);
			AttachToBone = NAME_None;
			ChangeCounter::Get().AddCleared();
			ChangeCounter::Get().AddCleared();
		}
	}
	// If NOT Attached, check if Transform should be PRESERVED
	else
	if (CS_TEST_BITFLAG(Mask, ChangeType::Transform))
	{
		// Do Nothing	
		ChangeCounter::Get().AddPreserved();
	}
	else
	{
		SetActorRelativeTransform(FTransform::Identity);
		CS_CLEAR_BITFLAG(ChangesToDefaultMask, ChangeType::Transform);
		ChangeCounter::Get().AddCleared();
	}

	#undef ChangeHelper
}

void ACsSoundPooledImpl::LogChangeCounter()
{
	if (CS_CVAR_LOG_IS_SHOWING(LogSoundPooledChangeCounter))
	{
		typedef NCsSound::NPayload::NChange::FCounter ChangeCounter;

		UE_LOG(LogCs, Warning, TEXT("ACsSoundPooledImpl::LogChangeCounter: %s."), *(ChangeCounter::Get().ToString()));
	}
}
// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Sound/CsSoundPooledImpl.h"
#include "CsSound.h"

// CVars
#include "Managers/Sound/CsCVars_Sound.h"
// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Types
#include "Types/CsTypes_Math_Library.h"
// Library
#include "Managers/Time/CsLibrary_Manager_Time.h"
#include "Coroutine/CsLibrary_CoroutineScheduler.h"
	// Payload
#include "Managers/Pool/Payload/CsLibrary_Payload_PooledObject.h"
	// Common
#include "Library/CsLibrary_Valid.h"
// Sound
#include "Sound/SoundBase.h"
#include "Components/AudioComponent.h"
#include "Managers/Sound/Cache/CsCache_SoundImpl.h"
#include "Managers/Sound/Payload/CsPayload_SoundImpl.h"

#if WITH_EDITOR
// Library
#include "Library/CsLibrary_World.h"
#endif // #if WITH_EDITOR

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsSoundPooledImpl)

// Cached
#pragma region

namespace NCsSoundPooledImpl
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsSoundPooledImpl, Update);
			// ICsPooledObject
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsSoundPooledImpl, Allocate);
			// ICsSoundPooled
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsSoundPooledImpl, Stop);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsSoundPooledImpl, Stop_Internal);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsSoundPooledImpl, FadeIn);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsSoundPooledImpl, FadeOut);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsSoundPooledImpl, Play);	
		}

		namespace Name
		{
			// ICsSoundPooled
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(ACsSoundPooledImpl, Stop_Internal);
		}
	}
}

#pragma endregion Cached

ACsSoundPooledImpl::ACsSoundPooledImpl(const FObjectInitializer& ObjectInitializer) : 
	Super(ObjectInitializer),
	AudioComponent(nullptr),
	bShutdown(false),
	Cache(nullptr),
	CacheImpl(nullptr),
	PreserveChangesToDefaultMask(0),
	ChangesToDefaultMask(0),
	// Sound Pooled
	StopHandle(),
	Type(),
	InitialVolume(0.0f),
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
	
	Shutdown();
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
	if (CsWorldLibrary::IsPlayInEditor(GetWorld()) ||
		CsWorldLibrary::IsPlayInEditorPreview(GetWorld()))
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
	static const float MIN_TIME_FOR_PAUSE = 2.0f;

	if (Cache->GetLifeTime() - Cache->GetElapsedTime().Time >= MIN_TIME_FOR_PAUSE)
	{
		checkf(AudioComponent, TEXT("ACsSoundPooledImpl::Pause: AudioComponent is NULL."));

		AudioComponent->SetPaused(bPaused);
	}
}

#pragma endregion ICsPause

// ICsShutdown
#pragma region

void ACsSoundPooledImpl::Shutdown()
{
	if (Cache)
	{
		delete Cache;
		Cache = nullptr;
	}
	bShutdown = true;
}

#pragma endregion ICsShutdown


void ACsSoundPooledImpl::ConstructCache()
{
	typedef NCsSound::NCache::FImpl CacheImplType;

	Cache	  = new CacheImplType();
	CacheImpl = (CacheImplType*)Cache;

	CacheImpl->SetAudioComponent(AudioComponent);
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

	InitialVolume = SoundPayload->GetSound()->GetDuration();

	Play(SoundPayload);
}

void ACsSoundPooledImpl::Deallocate()
{
	Stop();

	Cache->Deallocate();
}

#pragma endregion ICsPooledObject

// ICsSoundPooled
#pragma region

void ACsSoundPooledImpl::Stop(const float& FadeOutTime /*=0.0f*/)
{
	using namespace NCsSoundPooledImpl::NCached;

	const FString& Context = Str::Stop;

	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(FadeOutTime, 0.0f)

	CS_IS_PTR_NULL_CHECKED(AudioComponent)

	if (FadeOutTime > 0.0f)
	{
		typedef NCsCoroutine::NScheduler::FLibrary CoroutineSchedulerLibrary;

		const FECsUpdateGroup& UpdateGroup = NCsUpdateGroup::GameState;

		CoroutineSchedulerLibrary::EndAndInvalidateChecked(Context, this, UpdateGroup, StopHandle);

		// TODO: Have a way of passing the UpdateGroup

		UCsCoroutineScheduler* Scheduler = CoroutineSchedulerLibrary::GetChecked(Context, this);

		typedef NCsCoroutine::NPayload::FImpl PayloadType;

		PayloadType* Payload = Scheduler->AllocatePayload(UpdateGroup);

		#define COROUTINE Stop_Internal

		typedef NCsTime::NManager::FLibrary TimeManagerLibrary;

		Payload->CoroutineImpl.BindUObject(this, &ACsSoundPooledImpl::COROUTINE);
		Payload->StartTime = TimeManagerLibrary::GetTimeChecked(Context, this, UpdateGroup);
		Payload->Owner.SetObject(this);
		Payload->SetName(Str::COROUTINE);
		Payload->SetFName(Name::COROUTINE);

		#undef COROUTINE

		static const int32 FADE_OUT_TIME = 0;
		Payload->SetValue_Float(FADE_OUT_TIME, FadeOutTime);

		StopHandle = Scheduler->Start(Payload);
	}
	else
	{
		if (AudioComponent->bAllowSpatialization)
			Handle_ClearAttachAndTransform();

		AudioComponent->Deactivate();
		AudioComponent->Stop();

		AudioComponent->SetVolumeMultiplier(1.f);
		AudioComponent->SetPitchMultiplier(1.f);

		AudioComponent->AttenuationSettings = nullptr;

		AudioComponent->SetSound(nullptr);
		AudioComponent->SetPaused(false);
		SetActorTickEnabled(false);

		AudioComponent->bAllowSpatialization = false;

		Cache->QueueDeallocate();

		CS_NON_SHIPPING_EXPR(LogChangeCounter());
	}
}

void ACsSoundPooledImpl::FadeIn(const float& Duration)
{
	using namespace NCsSoundPooledImpl::NCached;

	const FString& Context = Str::FadeIn;

	CS_IS_FLOAT_GREATER_THAN_CHECKED(Duration, 0.0f)

	CS_IS_PTR_NULL_CHECKED(AudioComponent)

	//AudioComponent->AdjustVolume(0.0f, 0.0f);
	AudioComponent->AdjustVolume(Duration, InitialVolume);
}

void ACsSoundPooledImpl::FadeOut(const float& Duration) 
{
	using namespace NCsSoundPooledImpl::NCached;

	const FString& Context = Str::FadeOut;

	CS_IS_FLOAT_GREATER_THAN_CHECKED(Duration, 0.0f)

	CS_IS_PTR_NULL_CHECKED(AudioComponent)

	static const float VERY_LOW_VOLUME = 0.01f;
	AudioComponent->AdjustVolume(Duration, VERY_LOW_VOLUME);
}

#pragma endregion ICsSoundPooled

// SoundPooled
#pragma region

char ACsSoundPooledImpl::Stop_Internal(FCsRoutine* R)
{
	static const int32 FADE_OUT_TIME = 0;
	const float& FadeOutTime = R->GetValue_Float(FADE_OUT_TIME);

	CS_COROUTINE_BEGIN(R);

	AudioComponent->FadeOut(FadeOutTime, 0.0f);

	CS_COROUTINE_WAIT_UNTIL(R, R->GetElapsedTime().Time > FadeOutTime);

	Stop(0.0f);

	CS_COROUTINE_END(R);
}

#pragma endregion SoundPooled

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

	AudioComponent->SetPitchMultiplier(Payload->GetPitchMultiplier());
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

	const float& FadeInTime = Payload->GetFadeInTime();

	if (FadeInTime > 0)
	{
		AudioComponent->FadeIn(FadeInTime, Sound->GetVolumeMultiplier());
	}
	else
	{
		AudioComponent->Play();
	}

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

	const FTransform3f& Transform = SoundPayload->GetTransform();
	const int32& TransformRules   = SoundPayload->GetTransformRules();

	typedef NCsSound::NPayload::EChange ChangeType;
	typedef NCsSound::NPayload::NChange::FCounter ChangeCounter;
	#define ChangeHelper NCsSound::NPayload::NChange

	if (Parent)
	{
		const FAttachmentTransformRules& Rule = SoundPayload->GetAttachmentTransformRule();
		const FName& Bone					  = SoundPayload->GetBone();

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

			GetRootComponent()->AttachToComponent(Parent, Rule, Bone);
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
			SetActorRelativeTransform(FTransform3d::Identity);
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
		SetActorRelativeTransform(FTransform3d::Identity);
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

		UE_LOG(LogCsSound, Warning, TEXT("ACsSoundPooledImpl::LogChangeCounter: %s."), *(ChangeCounter::Get().ToString()));
	}
}
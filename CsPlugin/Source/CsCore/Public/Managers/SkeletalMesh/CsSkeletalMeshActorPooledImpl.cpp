// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/SkeletalMesh/CsSkeletalMeshActorPooledImpl.h"
#include "CsCore.h"

#include "Library/CsLibrary_Common.h"
// Sound
#include "Managers/SkeletalMesh/Cache/CsCache_SkeletalMeshActorImpl.h"
#include "Managers/SkeletalMesh/Payload/CsPayload_SkeletalMeshActorImpl.h"

// Cached
#pragma region

namespace NCsSkeletalMeshActorImpl
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsSkeletalMeshActorPooledImpl, Update);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsSkeletalMeshActorPooledImpl, Allocate);
		}
	}
}

#pragma endregion Cached

ACsSkeletalMeshActorPooledImpl::ACsSkeletalMeshActorPooledImpl(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick		   = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
}

// UObject Interface
#pragma region

void ACsSkeletalMeshActorPooledImpl::BeginDestroy()
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

void ACsSkeletalMeshActorPooledImpl::BeginPlay()
{
	Super::BeginPlay();

	GetSkeletalMeshComponent()->SetComponentTickEnabled(false);

	SetActorTickEnabled(false);

	ConstructCache();
}

void ACsSkeletalMeshActorPooledImpl::FellOutOfWorld(const UDamageType& DmgType)
{
	Cache->QueueDeallocate();
}

void ACsSkeletalMeshActorPooledImpl::OutsideWorldBounds()
{
	Cache->QueueDeallocate();
}

#pragma endregion AActor Interface

// ICsUpdate
#pragma region

void ACsSkeletalMeshActorPooledImpl::Update(const FCsDeltaTime& DeltaTime)
{
	using namespace NCsSkeletalMeshActorImpl::NCached;

	const FString& Context = Str::Update;

	// TODO: This should be opaque
	
	typedef NCsSkeletalMeshActor::NCache::FImpl CacheImplType;

	CacheImplType* CacheImpl = NCsInterfaceMap::PureStaticCastChecked<CacheImplType>(Context, Cache);

	CacheImpl->Update(DeltaTime);
}

#pragma endregion ICsUpdate

void ACsSkeletalMeshActorPooledImpl::ConstructCache()
{
	typedef NCsSkeletalMeshActor::NCache::FImpl CacheImplType;

	Cache = new CacheImplType();
}

// ICsPooledObject
#pragma region

#define PayloadType NCsPooledObject::NPayload::IPayload
void ACsSkeletalMeshActorPooledImpl::Allocate(PayloadType* Payload)
{
#undef PayloadType

	using namespace NCsSkeletalMeshActorImpl::NCached;

	const FString& Context = Str::Allocate;

	Cache->Allocate(Payload);

	typedef NCsSkeletalMeshActor::NPayload::IPayload PayloadType;

	PayloadType* SkeletalMeshPayload = NCsInterfaceMap::GetInterfaceChecked<PayloadType>(Context, Payload);

	/*
	checkf(AudioComponent, TEXT("ACsSoundPooledImpl::Play: AudioComponent is NULL."));

	USoundBase* Sound = Payload->GetSound();

	checkf(Sound, TEXT("ACsSoundPooledImpl::Play: Sound is NULL."));

	SetActorTickEnabled(true);

	typedef NCsPooledObject::NPayload::IPayload PayloadInterfaceType;

	PayloadInterfaceType* ObjectPayload = NCsInterfaceMap::GetInterfaceChecked<PayloadInterfaceType>(Str::Play, Payload);

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
	AudioComponent->Activate(true);
	*/
}

void ACsSkeletalMeshActorPooledImpl::Deallocate()
{
	Deallocate_Internal();
	Cache->Deallocate();
}

#pragma endregion ICsPooledObject

void ACsSkeletalMeshActorPooledImpl::Deallocate_Internal()
{
	USkeletalMeshComponent* Component = GetSkeletalMeshComponent();

	checkf(Component, TEXT("ACsSkeletalMeshActorPooledImpl::Deallocate_Internal: GetSkeletalMeshComponent() is NULL."));

	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	Component->SetSkeletalMesh(nullptr);
	Component->SetHiddenInGame(true);
	Component->SetComponentTickEnabled(false);

	SetActorTickEnabled(false);
}
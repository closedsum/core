// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/StaticMesh/CsStaticMeshActorPooledImpl.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Common.h"
#include "Managers/Pool/Payload/CsLibrary_Payload_PooledObject.h"
// Sound
#include "Managers/StaticMesh/Cache/CsCache_StaticMeshActorImpl.h"
#include "Managers/StaticMesh/Payload/CsPayload_StaticMeshActorImpl.h"

// Cached
#pragma region

namespace NCsStaticMeshActorImpl
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsStaticMeshActorPooledImpl, Update);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsStaticMeshActorPooledImpl, Allocate);
		}
	}
}

#pragma endregion Cached

ACsStaticMeshActorPooledImpl::ACsStaticMeshActorPooledImpl(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick		   = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
}

// UObject Interface
#pragma region

void ACsStaticMeshActorPooledImpl::BeginDestroy()
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

void ACsStaticMeshActorPooledImpl::BeginPlay()
{
	Super::BeginPlay();

	GetStaticMeshComponent()->SetComponentTickEnabled(false);

	SetActorTickEnabled(false);

	ConstructCache();
}

void ACsStaticMeshActorPooledImpl::FellOutOfWorld(const UDamageType& DmgType)
{
	Cache->QueueDeallocate();
}

void ACsStaticMeshActorPooledImpl::OutsideWorldBounds()
{
	Cache->QueueDeallocate();
}

#pragma endregion AActor Interface

// ICsUpdate
#pragma region

void ACsStaticMeshActorPooledImpl::Update(const FCsDeltaTime& DeltaTime)
{
	using namespace NCsStaticMeshActorImpl::NCached;

	const FString& Context = Str::Update;

	CacheImpl->Update(DeltaTime);
}

#pragma endregion ICsUpdate

void ACsStaticMeshActorPooledImpl::ConstructCache()
{
	typedef NCsStaticMeshActor::NCache::FImpl CacheImplType;

	CacheImpl = new CacheImplType();
	Cache	  = CacheImpl;
}

// ICsPooledObject
#pragma region

#define PayloadType NCsPooledObject::NPayload::IPayload
void ACsStaticMeshActorPooledImpl::Allocate(PayloadType* Payload)
{
#undef PayloadType

	using namespace NCsStaticMeshActorImpl::NCached;

	const FString& Context = Str::Allocate;

	Cache->Allocate(Payload);

	typedef NCsStaticMeshActor::NPayload::IPayload PayloadType;
	typedef NCsPooledObject::NPayload::FLibrary PooledPayloadLibrary;

	PayloadType* StaticMeshPayload = PooledPayloadLibrary::GetInterfaceChecked<PayloadType>(Context, Payload);

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

void ACsStaticMeshActorPooledImpl::Deallocate()
{
	Deallocate_Internal();
	Cache->Deallocate();
}

#pragma endregion ICsPooledObject

void ACsStaticMeshActorPooledImpl::Deallocate_Internal()
{
	UStaticMeshComponent* Component = GetStaticMeshComponent();

	checkf(Component, TEXT("ACsStaticMeshActorPooledImpl::Deallocate_Internal: GetStaticMeshComponent() is NULL."));

	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	Component->SetStaticMesh(nullptr);
	Component->SetHiddenInGame(true);
	Component->SetComponentTickEnabled(false);

	SetActorTickEnabled(false);
}
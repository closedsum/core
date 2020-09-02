// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/WidgetActor/CsWidgetActorPooledImpl.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Macro.h"
#include "Types/CsTypes_AttachDetach.h"
#include "Types/CsTypes_Math.h"
// Library
#include "Managers/Pool/Cache/CsLibrary_PooledObjectCache.h"
#include "Managers/Pool/Payload/CsLibrary_Payload_PooledObject.h"
// Pooled Object
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"
// WidgetActor
#include "Managers/WidgetActor/Cache/CsCache_WidgetActorImpl.h"
#include "Managers/WidgetActor/Payload/CsPayload_WidgetActorImpl.h"
// Components
#include "Components/CsWidgetComponent.h"

// Cached
#pragma region

namespace NCsWidgetActorPooledImplCached
{
	namespace Str
	{
		const FString Update = TEXT("ACsWidgetActorPooledImpl::Update");
		const FString Allocate = TEXT("ACsWidgetActorPooledImpl::Allocate");
	}
}

#pragma endregion Cached

ACsWidgetActorPooledImpl::ACsWidgetActorPooledImpl(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

// UObject Interface
#pragma region

void ACsWidgetActorPooledImpl::BeginDestroy()
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

void ACsWidgetActorPooledImpl::FellOutOfWorld(const UDamageType& DmgType)
{
	Deallocate_Internal();
	Cache->QueueDeallocate();
}

void ACsWidgetActorPooledImpl::OutsideWorldBounds()
{
	Deallocate_Internal();
	Cache->QueueDeallocate();
}

#pragma endregion AActor Interface

// ICsUpdate
#pragma region

void ACsWidgetActorPooledImpl::Update(const FCsDeltaTime& DeltaTime)
{
	using namespace NCsWidgetActorPooledImplCached;

	const FString& Context = Str::Update;

	FCsCache_WidgetActorImpl* CacheImpl = FCsLibrary_PooledObjectCache::PureStaticCastChecked<FCsCache_WidgetActorImpl>(Context, Cache);

	CacheImpl->Update(DeltaTime);
}

#pragma endregion ICsUpdate

// ICsPooledObject
#pragma region

ICsPooledObjectCache* ACsWidgetActorPooledImpl::GetCache() const
{
	return Cache;
}

void ACsWidgetActorPooledImpl::Allocate(ICsPayload_PooledObject* Payload)
{
	using namespace NCsWidgetActorPooledImplCached;

	const FString& Context = Str::Allocate;

	FCsCache_WidgetActorImpl* CacheImpl = FCsLibrary_PooledObjectCache::PureStaticCastChecked<FCsCache_WidgetActorImpl>(Context, Cache);

	CacheImpl->Allocate(Payload);

	CacheImpl->SetWidgetComponent(WidgetComponent);

	ICsPayload_WidgetActor* WidgetActorPayload = FCsLibrary_Payload_PooledObject::GetInterfaceChecked<ICsPayload_WidgetActor>(Context, Payload);

	SetActorTickEnabled(true);
	SetActorHiddenInGame(false);

	// If the Parent is set, attach the FX to the Parent
	if (USceneComponent* Parent = Cast<USceneComponent>(Payload->GetParent()))
	{
		AttachToComponent(Parent, NCsAttachmentTransformRules::ToRule(WidgetActorPayload->GetAttachmentTransformRule()), WidgetActorPayload->GetBone());

		const FTransform& Transform = WidgetActorPayload->GetTransform();
		const int32& TransformRules = WidgetActorPayload->GetTransformRules();
		
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
	// NO Parent, set the World Transform of the FX
	else
	{
		SetActorTransform(WidgetActorPayload->GetTransform());
	}

	//FXComponent->SetAsset(FXPayload->GetFXSystem());

	WidgetComponent->Activate();
}

void ACsWidgetActorPooledImpl::Deallocate()
{
	Deallocate_Internal();
	Cache->Deallocate();
}

#pragma endregion ICsPooledObject

void ACsWidgetActorPooledImpl::Deallocate_Internal()
{
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	SetActorTickEnabled(false);
	SetActorHiddenInGame(true);

	// TODO: "Free" Widget
	//WidgetComponent->SetWidget(nullptr);
}

void ACsWidgetActorPooledImpl::ConstructCache()
{
	Cache = new FCsCache_WidgetActorImpl();
}
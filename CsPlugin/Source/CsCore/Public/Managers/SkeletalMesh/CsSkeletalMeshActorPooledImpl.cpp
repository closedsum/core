// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/SkeletalMesh/CsSkeletalMeshActorPooledImpl.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_AttachDetach.h"
#include "Types/CsTypes_Math.h"
// Library
#include "Managers/Pool/Payload/CsLibrary_Payload_PooledObject.h"
#include "Managers/SkeletalMesh/Payload/CsLibrary_Payload_SkeletalMeshActor.h"
#include "Library/CsLibrary_Material.h"
// SkeletalMesh
#include "Managers/SkeletalMesh/Cache/CsCache_SkeletalMeshActorImpl.h"
#include "Managers/SkeletalMesh/Payload/CsPayload_SkeletalMeshActorImpl.h"
#include "Managers/SkeletalMesh/Params/CsParams_SkeletalMeshActor.h"

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

ACsSkeletalMeshActorPooledImpl::ACsSkeletalMeshActorPooledImpl(const FObjectInitializer& ObjectInitializer) : 
	Super(ObjectInitializer),
	Cache(nullptr),
	CacheImpl(nullptr)
{
	PrimaryActorTick.bCanEverTick		   = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetSkeletalMeshComponent()->SetNotifyRigidBodyCollision(false);
	GetSkeletalMeshComponent()->SetGenerateOverlapEvents(false);
	GetSkeletalMeshComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetSkeletalMeshComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	GetSkeletalMeshComponent()->SetHiddenInGame(true);
	GetSkeletalMeshComponent()->SetComponentTickEnabled(false);
	GetSkeletalMeshComponent()->bNoSkeletonUpdate = true;
	GetSkeletalMeshComponent()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::OnlyTickPoseWhenRendered;
	GetSkeletalMeshComponent()->KinematicBonesUpdateType = EKinematicBonesUpdateToPhysics::SkipAllBones;
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
		CacheImpl = nullptr;
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
	CacheImpl->Update(DeltaTime);
}

#pragma endregion ICsUpdate

void ACsSkeletalMeshActorPooledImpl::ConstructCache()
{
	typedef NCsSkeletalMeshActor::NCache::FImpl CacheImplType;

	Cache = new CacheImplType();
	CacheImpl = (CacheImplType*)Cache;
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

	typedef NCsPooledObject::NPayload::FLibrary PooledPayloadLibrary;
	typedef NCsSkeletalMeshActor::NPayload::IPayload SkeletalMeshPayloadType;

	SkeletalMeshPayloadType* SkeletalMeshPayload = PooledPayloadLibrary::GetInterfaceChecked<SkeletalMeshPayloadType>(Context, Payload);

	// Set SkeletalMesh
	GetMeshComponent()->SetSkeletalMesh(SkeletalMeshPayload->GetSkeletalMesh());
	// Set Materials
	typedef NCsMaterial::FLibrary MaterialLibrary;

	MaterialLibrary::SetMaterialsChecked(Context, GetMeshComponent(), SkeletalMeshPayload->GetMaterials());

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

	const FTransform& Transform = SkeletalMeshPayload->GetTransform();
	const int32& TransformRules = SkeletalMeshPayload->GetTransformRules();

	if (Parent)
	{
		// TODO: Add check if Bone is Valid for SkeletalMeshComponent
		GetMeshComponent()->AttachToComponent(Parent, NCsAttachmentTransformRules::ToRule(SkeletalMeshPayload->GetAttachmentTransformRule()), SkeletalMeshPayload->GetBone());

		NCsTransformRules::SetRelativeTransform(GetMeshComponent(), Transform, TransformRules);
	}
	// NO Parent, set the World Transform of the SkeletalMeshComponent
	else
	{
		NCsTransformRules::SetTransform(this, Transform, TransformRules);
	}

	SetActorTickEnabled(true);

	GetMeshComponent()->bNoSkeletonUpdate		 = false;
	GetMeshComponent()->KinematicBonesUpdateType = EKinematicBonesUpdateToPhysics::SkipSimulatingBones;

	GetMeshComponent()->SetHiddenInGame(false);
	GetMeshComponent()->SetComponentTickEnabled(true);

	// Evaluate any Params
	typedef NCsSkeletalMeshActor::NParams::IParams ParamsType;

	if (ParamsType* Params = SkeletalMeshPayload->GetParams())
	{
		// OneShot
		{
			typedef NCsSkeletalMeshActor::NParams::NAnim::NSequence::FOneShot ShotType;

			if (ShotType* Shot = NCsInterfaceMap::SafePureStaticCastChecked<ShotType, ParamsType>(Context, Params))
			{
				UAnimSequence* Anim = Shot->GetAnim();

				GetMeshComponent()->PlayAnimation(Anim, false);
			}
		}
	}
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
	SetActorRelativeTransform(FTransform::Identity);

	Component->bNoSkeletonUpdate = true;
	Component->KinematicBonesUpdateType = EKinematicBonesUpdateToPhysics::SkipAllBones;
	Component->SetSkeletalMesh(nullptr);
	Component->SetHiddenInGame(true);
	Component->SetComponentTickEnabled(false);

	SetActorTickEnabled(false);
}
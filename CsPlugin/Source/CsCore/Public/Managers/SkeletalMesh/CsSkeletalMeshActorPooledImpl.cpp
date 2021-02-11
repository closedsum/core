// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/SkeletalMesh/CsSkeletalMeshActorPooledImpl.h"
#include "CsCore.h"

// CVars
#include "Managers/SkeletalMesh/CsCVars_SkeletalMeshActor.h"
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
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsSkeletalMeshActorPooledImpl, Handle_SetSkeletalMesh);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsSkeletalMeshActorPooledImpl, Handle_SetMaterials);
		}
	}
}

#pragma endregion Cached

ACsSkeletalMeshActorPooledImpl::ACsSkeletalMeshActorPooledImpl(const FObjectInitializer& ObjectInitializer) : 
	Super(ObjectInitializer),
	Cache(nullptr),
	CacheImpl(nullptr),
	PreserveChangesToDefaultMask(0),
	ChangesToDefaultMask(0),
	ChangesFromLastMask(0),
	AttachToBone(NAME_None)
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

	PreserveChangesToDefaultMask = Payload->GetPreserveChangesFromDefaultMask();

	typedef NCsPooledObject::NPayload::FLibrary PooledPayloadLibrary;
	typedef NCsSkeletalMeshActor::NPayload::IPayload SkeletalMeshPayloadType;

	SkeletalMeshPayloadType* SkeletalMeshPayload = PooledPayloadLibrary::GetInterfaceChecked<SkeletalMeshPayloadType>(Context, Payload);

	// Set SkeletalMesh
	Handle_SetSkeletalMesh(SkeletalMeshPayload);
	// Set Materials
	Handle_SetMaterials(SkeletalMeshPayload);
	// Attach and set Transform
	Handle_AttachAndSetTransform(Payload, SkeletalMeshPayload);

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

	Handle_ClearAttachAndTransform();

	Component->bNoSkeletonUpdate = true;
	Component->KinematicBonesUpdateType = EKinematicBonesUpdateToPhysics::SkipAllBones;

	Handle_ClearSkeletalMesh();

	Component->SetHiddenInGame(true);
	Component->SetComponentTickEnabled(false);

	SetActorTickEnabled(false);

	PreserveChangesToDefaultMask = 0;
	ChangesFromLastMask = 0;
}

#define SkeletalMeshPayloadType NCsSkeletalMeshActor::NPayload::IPayload
void ACsSkeletalMeshActorPooledImpl::Handle_SetSkeletalMesh(SkeletalMeshPayloadType* Payload)
{
#undef SkeletalMeshPayloadType

	CS_NON_SHIPPING_EXPR(LogSetSkeletalMesh(Payload));

	USkeletalMesh* Mesh = Payload->GetSkeletalMesh();

	typedef NCsSkeletalMeshActor::NPayload::EChange ChangeType;
	typedef NCsSkeletalMeshActor::NPayload::NChange::FCounter ChangeCounter;

	// If ALREADY set SkeletalMesh and the trying to the SAME SkeletalMesh, Do Nothing
	if (CS_TEST_BITFLAG(PreserveChangesToDefaultMask, ChangeType::SkeletalMesh) &&
		CS_TEST_BITFLAG(ChangesToDefaultMask, ChangeType::SkeletalMesh))
	{
		if (GetMeshComponent()->SkeletalMesh != Mesh)
		{
			GetMeshComponent()->SetSkeletalMesh(Mesh);

			CS_SET_BITFLAG(ChangesFromLastMask, ChangeType::SkeletalMesh);

			ChangeCounter::Get().AddChanged();
		}
		else
		{
			ChangeCounter::Get().AddPreserved();
		}
	}
	else
	{
		GetMeshComponent()->SetSkeletalMesh(Mesh);
		ChangeCounter::Get().AddChanged();
	}
	CS_SET_BITFLAG(ChangesToDefaultMask, ChangeType::SkeletalMesh);
}

#define SkeletalMeshPayloadType NCsSkeletalMeshActor::NPayload::IPayload
void ACsSkeletalMeshActorPooledImpl::LogSetSkeletalMesh(SkeletalMeshPayloadType* Payload)
{
#undef SkeletalMeshPayloadType

	using namespace NCsSkeletalMeshActorImpl::NCached;

	const FString& Context = Str::Handle_SetSkeletalMesh;

	if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogSkeletalMeshActorPooledChange) ||
		FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogSkeletalMeshActorPooledChangeSet))
	{
		USkeletalMesh* Mesh = Payload->GetSkeletalMesh();

		typedef NCsSkeletalMeshActor::NPayload::EChange ChangeType;
		typedef NCsSkeletalMeshActor::NPayload::NChange::FCounter ChangeCounter;

		// Check if SkeletalMesh should be PRESERVED
		if (CS_TEST_BITFLAG(PreserveChangesToDefaultMask, ChangeType::SkeletalMesh))
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s"), *Context, *(ChangeCounter::Get().ToString()));

			// Check if the SkeletalMesh changed
			if (GetMeshComponent()->SkeletalMesh != Mesh)
			{
				if (CS_TEST_BITFLAG(ChangesToDefaultMask, ChangeType::SkeletalMesh))
				{
					UE_LOG(LogCs, Warning, TEXT(" %s -> %s."), *(GetMeshComponent()->SkeletalMesh ->GetName()), *(Mesh->GetName()));
				}
				else
				{
					UE_LOG(LogCs, Warning, TEXT(" NULL -> %s."), *(Mesh->GetName()));
				}
			}
			else
			{
				UE_LOG(LogCs, Warning, TEXT(" (PRESERVED) %s."), *(GetMeshComponent()->SkeletalMesh->GetName()));
			}
		}
	}
}

#define SkeletalMeshPayloadType NCsSkeletalMeshActor::NPayload::IPayload
void ACsSkeletalMeshActorPooledImpl::Handle_SetMaterials(SkeletalMeshPayloadType* Payload)
{
#undef SkeletalMeshPayloadType

	using namespace NCsSkeletalMeshActorImpl::NCached;

	const FString& Context = Str::Handle_SetMaterials;

	CS_NON_SHIPPING_EXPR(LogSetMaterials(Payload));

	typedef NCsSkeletalMeshActor::NPayload::EChange ChangeType;
	typedef NCsSkeletalMeshActor::NPayload::NChange::FCounter ChangeCounter;
	typedef NCsMaterial::FLibrary MaterialLibrary;

	USkeletalMeshComponent* Component			 = GetMeshComponent();
	const TArray<UMaterialInterface*>& Materials = Payload->GetMaterials();

	// If SkeletalMesh has NOT changed and Materials are the SAME, Do Nothing
	if (!CS_TEST_BITFLAG(ChangesFromLastMask, ChangeType::SkeletalMesh) &&
		CS_TEST_BITFLAG(PreserveChangesToDefaultMask, ChangeType::Materials) &&
		CS_TEST_BITFLAG(ChangesToDefaultMask, ChangeType::Materials))
	{
		bool Different = false;

		const int32 Count = Materials.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			if (Component->GetMaterial(I) != Materials[I])
			{
				Different = true;
				false;
			}
		}

		if (Different)
		{
			MaterialLibrary::SetMaterialsChecked(Context, Component, Materials);
			ChangeCounter::Get().AddChanged();
		}
		else
		{
			ChangeCounter::Get().AddPreserved();
		}
	}
	else
	{
		MaterialLibrary::SetMaterialsChecked(Context, GetMeshComponent(), Materials);
		ChangeCounter::Get().AddChanged();
	}
	CS_SET_BITFLAG(ChangesToDefaultMask, ChangeType::Materials);
}

#define SkeletalMeshPayloadType NCsSkeletalMeshActor::NPayload::IPayload
void ACsSkeletalMeshActorPooledImpl::LogSetMaterials(SkeletalMeshPayloadType* Payload)
{
#undef SkeletalMeshPayloadType

	using namespace NCsSkeletalMeshActorImpl::NCached;

	const FString& Context = Str::Handle_SetMaterials;

	if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogSkeletalMeshActorPooledChange) ||
		FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogSkeletalMeshActorPooledChangeSet))
	{
		typedef NCsSkeletalMeshActor::NPayload::EChange ChangeType;
		typedef NCsSkeletalMeshActor::NPayload::NChange::FCounter ChangeCounter;
		typedef NCsMaterial::FLibrary MaterialLibrary;

		USkeletalMeshComponent* Component			 = GetMeshComponent();
		const TArray<UMaterialInterface*>& Materials = Payload->GetMaterials();
		
		const int32 Count = Materials.Num();

		// Check if Materials should be PRESERVED
		if (CS_TEST_BITFLAG(PreserveChangesToDefaultMask, ChangeType::Materials))
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s"), *Context, *(ChangeCounter::Get().ToString()));

			// Check if the SkeletalMesh changed
			if (CS_TEST_BITFLAG(ChangesFromLastMask, ChangeType::SkeletalMesh))
			{
				UE_LOG(LogCs, Warning, TEXT(" (CHANGED) SkeletalMesh"));
				UE_LOG(LogCs, Warning, TEXT(" Materials [%d]"), Count);

				for (int32 I = 0; I < Count; ++I)
				{
					UE_LOG(LogCs, Warning, TEXT("  [%d] %s"), I, *(Materials[I]->GetName()));
				}
			}
			// Check if the previous Materials are the SAME as the Materials to be SET
			else
			if (CS_TEST_BITFLAG(ChangesToDefaultMask, ChangeType::Materials))
			{
				bool Different = false;

				for (int32 I = 0; I < Count; ++I)
				{
					if (Component->GetMaterial(I) != Materials[I])
					{
						Different = true;
						false;
					}
				}
				
				if (Different)
				{
					UE_LOG(LogCs, Warning, TEXT(" (CHANGED) Materials [%d]"), Count);

					for (int32 I = 0; I < Count; ++I)
					{
						UE_LOG(LogCs, Warning, TEXT("  [%d] %s -> %s"), I, *(Component->GetMaterial(I)->GetName()), *(Materials[I]->GetName()));
					}
				}
				else
				{
					UE_LOG(LogCs, Warning, TEXT(" (PRESERVED) Materials [%d]"), Count);

					for (int32 I = 0; I < Count; ++I)
					{
						UE_LOG(LogCs, Warning, TEXT("  [%d] %s"), I, *(Materials[I]->GetName()));
					}
				}
			}
			// Default -> SET
			else
			{
				UE_LOG(LogCs, Warning, TEXT(" DEFAULT -> Materials [%d]"), Count);

				for (int32 I = 0; I < Count; ++I)
				{
					UE_LOG(LogCs, Warning, TEXT("  [%d] %s"), I, *(Materials[I]->GetName()));
				}
			}
		}
	}
}

#define PayloadType NCsPooledObject::NPayload::IPayload
#define SkeletalMeshPayloadType NCsSkeletalMeshActor::NPayload::IPayload
void ACsSkeletalMeshActorPooledImpl::Handle_AttachAndSetTransform(PayloadType* Payload, SkeletalMeshPayloadType* SkeletalMeshPayload)
{
#undef PayloadType
#undef SkeletalMeshPayloadType

	CS_NON_SHIPPING_EXPR(LogAttachAndSetTransform(Payload, SkeletalMeshPayload));

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

	typedef NCsSkeletalMeshActor::NPayload::EChange ChangeType;
	typedef NCsSkeletalMeshActor::NPayload::NChange::FCounter ChangeCounter;
	#define ChangeHelper NCsSkeletalMeshActor::NPayload::NChange

	if (Parent)
	{
		const ECsAttachmentTransformRules& Rule = SkeletalMeshPayload->GetAttachmentTransformRule();
		const FName& Bone						= SkeletalMeshPayload->GetBone();

		bool PerformAttach = true;
		bool IsPreserved = false;

		// If Attach and Transform are the SAME, Do Nothing
		if (GetMeshComponent()->GetAttachParent() == Parent &&
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
			GetMeshComponent()->AttachToComponent(Parent, NCsAttachmentTransformRules::ToRule(Rule), SkeletalMeshPayload->GetBone());
			ChangeCounter::Get().AddChanged();
		}

		CS_SET_BITFLAG(ChangesToDefaultMask, ChangeHelper::FromTransformAttachmentRule(Rule));

		bool PerformTransform = true;
		IsPreserved			  = false;

		// If Transform has NOT changed, don't update it.
		if (CS_TEST_BITFLAG(PreserveChangesToDefaultMask, ChangeType::Transform) &&
			CS_TEST_BITFLAG(ChangesToDefaultMask, ChangeType::Transform))
		{
			IsPreserved		 = NCsTransformRules::AreTransformsEqual(GetMeshComponent()->GetRelativeTransform(), Transform, TransformRules);
			PerformTransform = !IsPreserved;

			if (IsPreserved)
				ChangeCounter::Get().AddPreserved();
		}

		// Set Transform
		if (PerformTransform)
		{
			NCsTransformRules::SetRelativeTransform(GetMeshComponent(), Transform, TransformRules);
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
			IsPreserved		 = NCsTransformRules::AreTransformsEqual(GetMeshComponent()->GetRelativeTransform(), Transform, TransformRules);
			PerformTransform = !IsPreserved;

			if (IsPreserved)
				ChangeCounter::Get().AddPreserved();
		}

		if (PerformTransform)
		{
			NCsTransformRules::SetTransform(this, Transform, TransformRules);
			ChangeCounter::Get().AddChanged();
		}
	}
	CS_SET_BITFLAG(ChangesToDefaultMask, ChangeType::Transform);

	#undef ChangeHelper
}

#define PayloadType NCsPooledObject::NPayload::IPayload
#define SkeletalMeshPayloadType NCsSkeletalMeshActor::NPayload::IPayload
void ACsSkeletalMeshActorPooledImpl::LogAttachAndSetTransform(PayloadType* Payload, SkeletalMeshPayloadType* SkeletalMeshPayload)
{
#undef PayloadType
#undef SkeletalMeshPayloadType

}

void ACsSkeletalMeshActorPooledImpl::Handle_ClearSkeletalMesh()
{
	typedef NCsSkeletalMeshActor::NPayload::EChange ChangeType;
	typedef NCsSkeletalMeshActor::NPayload::NChange::FCounter ChangeCounter;

	// If SkeletalMesh is SET and meant to be PRESERVED, Do Nothing
	if (CS_TEST_BITFLAG(PreserveChangesToDefaultMask, ChangeType::SkeletalMesh) &&
		CS_TEST_BITFLAG(ChangesToDefaultMask, ChangeType::SkeletalMesh))
	{
		// Do Nothing
		ChangeCounter::Get().AddPreserved();
		ChangeCounter::Get().AddPreserved();
	}
	else
	{
		GetMeshComponent()->SetSkeletalMesh(nullptr);
		CS_CLEAR_BITFLAG(ChangesToDefaultMask, ChangeType::SkeletalMesh);
		CS_CLEAR_BITFLAG(ChangesToDefaultMask, ChangeType::Materials);
		ChangeCounter::Get().AddCleared();
		ChangeCounter::Get().AddCleared();
	}
}

void ACsSkeletalMeshActorPooledImpl::Handle_ClearAttachAndTransform()
{
	typedef NCsSkeletalMeshActor::NPayload::EChange ChangeType;
	typedef NCsSkeletalMeshActor::NPayload::NChange::FCounter ChangeCounter;
	#define ChangeHelper NCsSkeletalMeshActor::NPayload::NChange
	
	const uint32 Mask = PreserveChangesToDefaultMask & ChangesToDefaultMask;

	// If Attached, check if the Attach should be PERSERVED
	if (GetMeshComponent()->GetAttachParent())
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
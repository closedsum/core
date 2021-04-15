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
// Animation
#include "Animation/AnimInstance.h"

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
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsSkeletalMeshActorPooledImpl, Handle_SetAnimInstance);
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
	PrimaryActorTick.bStartWithTickEnabled = true;

	GetSkeletalMeshComponent()->SetNotifyRigidBodyCollision(false);
	GetSkeletalMeshComponent()->SetGenerateOverlapEvents(false);
	GetSkeletalMeshComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetSkeletalMeshComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	GetSkeletalMeshComponent()->SetHiddenInGame(true);
	GetSkeletalMeshComponent()->SetCastShadow(false);
	GetSkeletalMeshComponent()->SetReceivesDecals(false);
	GetSkeletalMeshComponent()->bUseAsOccluder = false;
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

#define PooledPayloadType NCsPooledObject::NPayload::IPayload
void ACsSkeletalMeshActorPooledImpl::Allocate(PooledPayloadType* Payload)
{
#undef PooledPayloadType

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
	GetMeshComponent()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
	GetMeshComponent()->KinematicBonesUpdateType = EKinematicBonesUpdateToPhysics::SkipSimulatingBones;

	GetMeshComponent()->SetHiddenInGame(false);
	GetMeshComponent()->SetComponentTickEnabled(true);

	// Evaluate any Params
	typedef NCsSkeletalMeshActor::NParams::IParams ParamsType;

	if (ParamsType* Params = SkeletalMeshPayload->GetParams())
	{
		// OneShot - Anim Sequence
		{
			typedef NCsSkeletalMeshActor::NParams::NAnim::NSequence::FOneShot ShotType;

			if (ShotType* Shot = NCsInterfaceMap::SafePureStaticCastChecked<ShotType, ParamsType>(Context, Params))
			{
				UAnimSequence* Anim = Shot->GetAnim();

				GetMeshComponent()->PlayAnimation(Anim, false);
			}
		}
		// One Shot - Anim Montage
		{
			typedef NCsSkeletalMeshActor::NParams::NAnim::NMontage::FOneShot ShotType;

			if (ShotType* Shot = NCsInterfaceMap::SafePureStaticCastChecked<ShotType, ParamsType>(Context, Params))
			{
				Handle_SetAnimInstance(Shot);

				UAnimMontage* Anim			= Shot->GetAnim();
				UAnimInstance* AnimInstance = GetMeshComponent()->GetAnimInstance();

				AnimInstance->Montage_Play(Anim, Shot->GetPlayRate());
			}
		}
	}
	CS_NON_SHIPPING_EXPR(LogChangeCounter());
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
	Component->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::OnlyTickPoseWhenRendered;
	Component->KinematicBonesUpdateType = EKinematicBonesUpdateToPhysics::SkipAllBones;

	Handle_ClearSkeletalMesh();

	Component->SetHiddenInGame(true);
	Component->SetComponentTickEnabled(false);

	SetActorTickEnabled(false);

	PreserveChangesToDefaultMask = 0;
	ChangesFromLastMask = 0;

	CS_NON_SHIPPING_EXPR(LogChangeCounter());
}

#define SkeletalMeshPayloadType NCsSkeletalMeshActor::NPayload::IPayload
void ACsSkeletalMeshActorPooledImpl::Handle_SetSkeletalMesh(SkeletalMeshPayloadType* Payload)
{
#undef SkeletalMeshPayloadType

	CS_NON_SHIPPING_EXPR(Log_SetSkeletalMesh(Payload));

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
		CS_SET_BITFLAG(ChangesFromLastMask, ChangeType::SkeletalMesh);
		ChangeCounter::Get().AddChanged();
	}
	CS_SET_BITFLAG(ChangesToDefaultMask, ChangeType::SkeletalMesh);
}

#define SkeletalMeshPayloadType NCsSkeletalMeshActor::NPayload::IPayload
void ACsSkeletalMeshActorPooledImpl::Log_SetSkeletalMesh(SkeletalMeshPayloadType* Payload)
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

	CS_NON_SHIPPING_EXPR(Log_SetMaterials(Payload));

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
				break;
			}
		}

		if (Different)
		{
			MaterialLibrary::SetChecked(Context, Component, Materials);
			ChangeCounter::Get().AddChanged();
		}
		else
		{
			ChangeCounter::Get().AddPreserved();
		}
	}
	else
	{
		MaterialLibrary::SetChecked(Context, GetMeshComponent(), Materials);
		ChangeCounter::Get().AddChanged();
	}
	CS_SET_BITFLAG(ChangesToDefaultMask, ChangeType::Materials);
}

#define SkeletalMeshPayloadType NCsSkeletalMeshActor::NPayload::IPayload
void ACsSkeletalMeshActorPooledImpl::Log_SetMaterials(SkeletalMeshPayloadType* Payload)
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
						break;
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

#define PooledPayloadType NCsPooledObject::NPayload::IPayload
#define SkeletalMeshPayloadType NCsSkeletalMeshActor::NPayload::IPayload
void ACsSkeletalMeshActorPooledImpl::Handle_AttachAndSetTransform(PooledPayloadType* Payload, SkeletalMeshPayloadType* SkeletalMeshPayload)
{
#undef PooledPayloadType
#undef SkeletalMeshPayloadType

	CS_NON_SHIPPING_EXPR(Log_AttachAndSetTransform(Payload, SkeletalMeshPayload));

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
			AttachToBone = Bone;

			GetMeshComponent()->AttachToComponent(Parent, NCsAttachmentTransformRules::ToRule(Rule), Bone);
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

		AttachToBone = NAME_None;
	}
	CS_SET_BITFLAG(ChangesToDefaultMask, ChangeType::Transform);

	#undef ChangeHelper
}

#define PooledPayloadType NCsPooledObject::NPayload::IPayload
#define SkeletalMeshPayloadType NCsSkeletalMeshActor::NPayload::IPayload
void ACsSkeletalMeshActorPooledImpl::Log_AttachAndSetTransform(PooledPayloadType* Payload, SkeletalMeshPayloadType* SkeletalMeshPayload)
{
#undef PooledPayloadType
#undef SkeletalMeshPayloadType

}

#define ShotType NCsSkeletalMeshActor::NParams::NAnim::NMontage::FOneShot
void ACsSkeletalMeshActorPooledImpl::Handle_SetAnimInstance(ShotType* Shot)
{
#undef ShotType

	using namespace NCsSkeletalMeshActorImpl::NCached;

	const FString& Context = Str::Handle_SetAnimInstance;

	CS_NON_SHIPPING_EXPR(Log_SetAnimInstance(Shot));

	UClass* Class = Shot->GetClass();

	typedef NCsSkeletalMeshActor::NPayload::EChange ChangeType;
	typedef NCsSkeletalMeshActor::NPayload::NChange::FCounter ChangeCounter;

	bool SetAnimInstance = true;

	// If ALREADY set AnimInstance and trying to the SAME AnimInstance, Do Nothing
	if (CS_TEST_BITFLAG(PreserveChangesToDefaultMask, ChangeType::AnimInstance) &&
		CS_TEST_BITFLAG(ChangesToDefaultMask, ChangeType::AnimInstance))
	{
		UAnimInstance* AnimInstance = GetMeshComponent()->GetAnimInstance();

		// Check if the AnimInstance has changed
		if (CS_TEST_BITFLAG(ChangesFromLastMask, ChangeType::SkeletalMesh))
		{
			if (AnimInstance &&
				AnimInstance->GetClass()->GetName() == Class->GetName())
			{
				// Check Skeletons
				// NOTE: Not sure if this is necessary
				USkeleton* Skeleton = nullptr;

				// AnimBlueprintGeneratedClass
				if (UAnimBlueprintGeneratedClass* ABpGC = Cast<UAnimBlueprintGeneratedClass>(Class))
					Skeleton = ABpGC->GetTargetSkeleton();
				// AnimInstance
				else
				if (UAnimInstance* NewAnimInstance = Cast<UAnimInstance>(Class))
					Skeleton = NewAnimInstance->CurrentSkeleton;

				if (AnimInstance->CurrentSkeleton == Skeleton)
				{
					SetAnimInstance = false;
				}
			}
		}
		else
		if (AnimInstance->GetClass()->GetName() == Class->GetName())
		{
			SetAnimInstance = false;
		}
	}
	
	if (SetAnimInstance)
	{
		GetMeshComponent()->SetAnimInstanceClass(Class);
		ChangeCounter::Get().AddChanged();
	}
	checkf(GetMeshComponent()->GetAnimInstance(), TEXT("%s: Failed to set AnimInstance with Class: %s."), *Context, *(Shot->GetClass()->GetName()));
	CS_SET_BITFLAG(ChangesToDefaultMask, ChangeType::AnimInstance);
}

#define ShotType NCsSkeletalMeshActor::NParams::NAnim::NMontage::FOneShot
void ACsSkeletalMeshActorPooledImpl::Log_SetAnimInstance(ShotType* Shot)
{
#undef ShotType

	using namespace NCsSkeletalMeshActorImpl::NCached;

	const FString& Context = Str::Handle_SetAnimInstance;

	if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogSkeletalMeshActorPooledChange) ||
		FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogSkeletalMeshActorPooledChangeSet))
	{
		UClass* Class = Shot->GetClass();

		typedef NCsSkeletalMeshActor::NPayload::EChange ChangeType;
		typedef NCsSkeletalMeshActor::NPayload::NChange::FCounter ChangeCounter;

		// If ALREADY set AnimInstance and trying to the SAME AnimInstance, Do Nothing
		if (CS_TEST_BITFLAG(PreserveChangesToDefaultMask, ChangeType::AnimInstance))
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s"), *Context, *(ChangeCounter::Get().ToString()));

			// Check if the AnimInstance changed
			if (UAnimInstance* AnimInstance = GetMeshComponent()->GetAnimInstance())
			{
				if (AnimInstance->GetName() != Class->GetName())
				{
					if (CS_TEST_BITFLAG(ChangesToDefaultMask, ChangeType::AnimInstance))
					{
						UE_LOG(LogCs, Warning, TEXT(" %s -> %s."), *(AnimInstance->GetName()), *(Class->GetName()));
					}
				}
				else
				{
					UE_LOG(LogCs, Warning, TEXT(" (PRESERVED) %s."), *(AnimInstance->GetName()));
				}
			}
			else
			{
				UE_LOG(LogCs, Warning, TEXT(" NULL -> %s."), *(Class->GetName()));
			}
		}
	}
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
		ChangeCounter::Get().AddPreserved();
	}
	else
	{
		GetMeshComponent()->SetSkeletalMesh(nullptr);
		CS_CLEAR_BITFLAG(ChangesToDefaultMask, ChangeType::SkeletalMesh);
		CS_CLEAR_BITFLAG(ChangesToDefaultMask, ChangeType::Materials);
		CS_CLEAR_BITFLAG(ChangesToDefaultMask, ChangeType::AnimInstance);
		ChangeCounter::Get().AddCleared();
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

void ACsSkeletalMeshActorPooledImpl::Handle_ClearAnimInstance()
{
	if (UAnimInstance* AnimInstance = GetMeshComponent()->GetAnimInstance())
	{
		AnimInstance->StopAllMontages(0.0f);
	}
	GetMeshComponent()->Stop();
}

void ACsSkeletalMeshActorPooledImpl::LogChangeCounter()
{
	if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogSkeletalMeshActorPooledChangeCounter))
	{
		typedef NCsSkeletalMeshActor::NPayload::NChange::FCounter ChangeCounter;

		UE_LOG(LogCs, Warning, TEXT("ACsSkeletalMeshActorPooledImpl::LogChangeCounter: %s."), *(ChangeCounter::Get().ToString()));
	}
}
// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/StaticMesh/CsStaticMeshActorPooledImpl.h"
#include "CsStaticMesh.h"

// CVars
#include "Managers/StaticMesh/CsCVars_StaticMeshActor.h"
// Types
#include "Types/CsTypes_AttachDetach.h"
#include "Types/CsTypes_Math_Library.h"
// Library
#include "Managers/Pool/Payload/CsLibrary_Payload_PooledObject.h"
#include "Managers/StaticMesh/Payload/CsLibrary_Payload_StaticMeshActor.h"
#include "Material/CsLibrary_Material.h"
#include "Library/CsLibrary_SkeletalMesh.h"
#include "Library/CsLibrary_Array.h"
// StaticMesh
#include "Engine/StaticMesh.h"
#include "Managers/StaticMesh/Cache/CsCache_StaticMeshActorImpl.h"
#include "Managers/StaticMesh/Payload/CsPayload_StaticMeshActorImpl.h"
// Material
#include "Materials/MaterialInterface.h"
// Components
#include "Components/StaticMeshComponent.h"

#if WITH_EDITOR
// Library
	// Common
#include "Library/CsLibrary_World.h"
#endif // #if WITH_EDITOR

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsStaticMeshActorPooledImpl)

// Cached
#pragma region

namespace NCsStaticMeshActorPooledImpl
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsStaticMeshActorPooledImpl, Update);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsStaticMeshActorPooledImpl, Allocate);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsStaticMeshActorPooledImpl, Handle_SetStaticMesh);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsStaticMeshActorPooledImpl, Handle_SetMaterials);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsStaticMeshActorPooledImpl, Handle_AttachAndSetTransform);
		}
	}
}

#pragma endregion Cached

ACsStaticMeshActorPooledImpl::ACsStaticMeshActorPooledImpl(const FObjectInitializer& ObjectInitializer) : 
	Super(ObjectInitializer),
	// Shutdown
	bShutdown(false),
	// PooledObject
	Cache(nullptr),
	CacheImpl(nullptr),
	PreserveChangesToDefaultMask(0),
	ChangesToDefaultMask(0),
	ChangesFromLastMask(0),
	// Materials
	MIDs(),
	// Set / Clear Changes
	AttachToBone(NAME_None)
{
	PrimaryActorTick.bCanEverTick		   = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetStaticMeshComponent()->SetNotifyRigidBodyCollision(false);
	GetStaticMeshComponent()->SetGenerateOverlapEvents(false);
	GetStaticMeshComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetStaticMeshComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	GetStaticMeshComponent()->SetHiddenInGame(true);
	GetStaticMeshComponent()->SetCastShadow(false);
	GetStaticMeshComponent()->SetReceivesDecals(false);
	GetStaticMeshComponent()->bUseAsOccluder = false;
	GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);
	GetStaticMeshComponent()->SetComponentTickEnabled(false);
}

// UObject Interface
#pragma region

void ACsStaticMeshActorPooledImpl::BeginDestroy()
{
	Super::BeginDestroy();
	
	Shutdown();
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

void ACsStaticMeshActorPooledImpl::PostInitializeComponents()
{
	Super::PostInitializeComponents();

#if WITH_EDITOR
	if (CsWorldLibrary::IsPlayInEditorOrEditorPreview(this))
	{
		GetStaticMeshComponent()->SetComponentTickEnabled(false);

		SetActorTickEnabled(false);

		ConstructCache();
	}
#endif // #if WITH_EDITOR
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
	using namespace NCsStaticMeshActorPooledImpl::NCached;

	const FString& Context = Str::Update;

	CacheImpl->Update(DeltaTime);
}

#pragma endregion ICsUpdate

// ICsShutdown
#pragma region

void ACsStaticMeshActorPooledImpl::Shutdown()
{
	if (Cache)
	{
		delete Cache;
		Cache = nullptr;
		CacheImpl = nullptr;
	}

	typedef NCsMaterial::NMID::FLibrary MIDLibrary;

	MIDLibrary::Destroy(MIDs);

	bShutdown = true;
}

#pragma endregion ICsShutdown

// PooledObject
#pragma region

void ACsStaticMeshActorPooledImpl::ConstructCache()
{
	typedef NCsStaticMeshActor::NCache::FImpl CacheImplType;

	CacheImpl = new CacheImplType();
	Cache	  = CacheImpl;
}

#pragma endregion PooledObject

// ICsPooledObject
#pragma region

#define PooledPayloadType NCsPooledObject::NPayload::IPayload
void ACsStaticMeshActorPooledImpl::Allocate(PooledPayloadType* Payload)
{
#undef PooledPayloadType

	using namespace NCsStaticMeshActorPooledImpl::NCached;

	const FString& Context = Str::Allocate;

	Cache->Allocate(Payload);

	typedef NCsPooledObject::NPayload::FLibrary PooledPayloadLibrary;
	typedef NCsStaticMeshActor::NPayload::IPayload StaticMeshPayloadType;
	
	StaticMeshPayloadType* StaticMeshPayload = PooledPayloadLibrary::GetInterfaceChecked<StaticMeshPayloadType>(Context, Payload);

	// Set StaticMesh
	Handle_SetStaticMesh(StaticMeshPayload);
	// Set Materials
	Handle_SetMaterials(StaticMeshPayload);
	// Attach and set Transform
	Handle_AttachAndSetTransform(Payload, StaticMeshPayload);

	SetActorTickEnabled(true);

	GetMeshComponent()->SetCastShadow(StaticMeshPayload->CastShadow());
	GetMeshComponent()->SetReceivesDecals(StaticMeshPayload->ReceivesDecals());
	GetMeshComponent()->bUseAsOccluder = StaticMeshPayload->UseAsOccluder();
	GetMeshComponent()->SetRenderCustomDepth(StaticMeshPayload->UseRenderCustomDepth());
	GetMeshComponent()->SetCustomDepthStencilValue(StaticMeshPayload->GetCustomDepthStencilValue());
	GetMeshComponent()->SetHiddenInGame(false);
	GetMeshComponent()->SetComponentTickEnabled(true);

	SetActorTickEnabled(true);
}

void ACsStaticMeshActorPooledImpl::Deallocate()
{
	Deallocate_Internal();
	Cache->Deallocate();
}

#pragma endregion ICsPooledObject

// PooledOject
#pragma region

void ACsStaticMeshActorPooledImpl::Deallocate_Internal()
{
	UStaticMeshComponent* Component = GetStaticMeshComponent();

	checkf(Component, TEXT("ACsStaticMeshActorPooledImpl::Deallocate_Internal: GetStaticMeshComponent() is NULL."));

	Handle_ClearAttachAndTransform();
	Handle_ClearStaticMesh();

	Tags.Reset(Tags.Max());

	Component->SetRenderCustomDepth(false);
	Component->SetCustomDepthStencilValue(0);
	Component->SetHiddenInGame(true);
	Component->SetComponentTickEnabled(false);
	Component->ComponentTags.Reset(Component->ComponentTags.Max());

	SetActorTickEnabled(false);

	PreserveChangesToDefaultMask = 0;
	ChangesFromLastMask = 0;

	CS_NON_SHIPPING_EXPR(LogChangeCounter());
}

#pragma region PooledObject

// Set / Clear Changes
#pragma region

#define PooledPayloadType NCsPooledObject::NPayload::IPayload
#define StaticMeshPayloadType NCsStaticMeshActor::NPayload::IPayload

void ACsStaticMeshActorPooledImpl::Handle_SetStaticMesh(StaticMeshPayloadType* Payload)
{
	CS_NON_SHIPPING_EXPR(Log_SetStaticMesh(Payload));

	UStaticMesh* Mesh = Payload->GetStaticMesh();

	typedef NCsStaticMeshActor::NPayload::EChange ChangeType;
	typedef NCsStaticMeshActor::NPayload::NChange::FCounter ChangeCounter;

	// If ALREADY set StaticMesh and the trying to the SAME StaticMesh, Do Nothing
	if (CS_TEST_BITFLAG(PreserveChangesToDefaultMask, ChangeType::StaticMesh) &&
		CS_TEST_BITFLAG(ChangesToDefaultMask, ChangeType::StaticMesh))
	{
		if (GetMeshComponent()->GetStaticMesh() != Mesh)
		{
			GetMeshComponent()->SetStaticMesh(Mesh);
			CS_SET_BITFLAG(ChangesFromLastMask, ChangeType::StaticMesh);
			ChangeCounter::Get().AddChanged();
		}
		else
		{
			ChangeCounter::Get().AddPreserved();
		}
	}
	else
	{
		GetMeshComponent()->SetStaticMesh(Mesh);
		CS_SET_BITFLAG(ChangesFromLastMask, ChangeType::StaticMesh);
		ChangeCounter::Get().AddChanged();
	}
	CS_SET_BITFLAG(ChangesToDefaultMask, ChangeType::StaticMesh);
}

void ACsStaticMeshActorPooledImpl::Log_SetStaticMesh(StaticMeshPayloadType* Payload)
{
	using namespace NCsStaticMeshActorPooledImpl::NCached;

	const FString& Context = Str::Handle_SetStaticMesh;

	if (CS_CVAR_LOG_IS_SHOWING(LogStaticMeshActorPooledChange) ||
		CS_CVAR_LOG_IS_SHOWING(LogStaticMeshActorPooledChangeSet))
	{
		UStaticMesh* Mesh = Payload->GetStaticMesh();

		typedef NCsStaticMeshActor::NPayload::EChange ChangeType;
		typedef NCsStaticMeshActor::NPayload::NChange::FCounter ChangeCounter;

		// Check if SkeletalMesh should be PRESERVED
		if (CS_TEST_BITFLAG(PreserveChangesToDefaultMask, ChangeType::StaticMesh))
		{
			UE_LOG(LogCsStaticMesh, Warning, TEXT("%s: %s"), *Context, *(ChangeCounter::Get().ToString()));

			// Check if the SkeletalMesh changed
			if (GetMeshComponent()->GetStaticMesh() != Mesh)
			{
				if (CS_TEST_BITFLAG(ChangesToDefaultMask, ChangeType::StaticMesh))
				{
					UE_LOG(LogCsStaticMesh, Warning, TEXT(" %s -> %s."), *(GetMeshComponent()->GetStaticMesh()->GetName()), *(Mesh->GetName()));
				}
				else
				{
					UE_LOG(LogCsStaticMesh, Warning, TEXT(" NULL -> %s."), *(Mesh->GetName()));
				}
			}
			else
			{
				UE_LOG(LogCsStaticMesh, Warning, TEXT(" (PRESERVED) %s."), *(GetMeshComponent()->GetStaticMesh()->GetName()));
			}
		}
	}
}

void ACsStaticMeshActorPooledImpl::Handle_SetMaterials(StaticMeshPayloadType* Payload)
{
	using namespace NCsStaticMeshActorPooledImpl::NCached;

	const FString& Context = Str::Handle_SetMaterials;

	CS_NON_SHIPPING_EXPR(Log_SetMaterials(Payload));

	typedef NCsStaticMeshActor::NPayload::EChange ChangeType;
	typedef NCsStaticMeshActor::NPayload::NChange::FCounter ChangeCounter;
	typedef NCsMaterial::FLibrary MaterialLibrary;
	typedef NCsMaterial::NMID::FLibrary MIDLibrary;

	UStaticMeshComponent* Component				 = GetMeshComponent();
	const TArray<UMaterialInterface*>& Materials = Payload->GetMaterials();

	// If StaticMesh has NOT changed and Materials are the SAME, Do Nothing
	if (!CS_TEST_BITFLAG(ChangesFromLastMask, ChangeType::StaticMesh) &&
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
			if (Payload->ShouldGenerateMIDs())
				MIDLibrary::SetChecked(Context, Component, Materials, MIDs);
			else
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
		if (Materials.Num() > CS_EMPTY)
		{
			if (Payload->ShouldGenerateMIDs())
				MIDLibrary::SetChecked(Context, Component, Materials, MIDs);
			else
				MaterialLibrary::SetChecked(Context, Component, Materials);
			ChangeCounter::Get().AddChanged();
		}
	}
	CS_SET_BITFLAG(ChangesToDefaultMask, ChangeType::Materials);
}

void ACsStaticMeshActorPooledImpl::Log_SetMaterials(StaticMeshPayloadType* Payload)
{
	using namespace NCsStaticMeshActorPooledImpl::NCached;

	const FString& Context = Str::Handle_SetMaterials;

	if (CS_CVAR_LOG_IS_SHOWING(LogStaticMeshActorPooledChange) ||
		CS_CVAR_LOG_IS_SHOWING(LogStaticMeshActorPooledChangeSet))
	{
		typedef NCsStaticMeshActor::NPayload::EChange ChangeType;
		typedef NCsStaticMeshActor::NPayload::NChange::FCounter ChangeCounter;
		typedef NCsMaterial::FLibrary MaterialLibrary;

		UStaticMeshComponent* Component				 = GetMeshComponent();
		const TArray<UMaterialInterface*>& Materials = Payload->GetMaterials();
		
		const int32 Count = Materials.Num();

		// Check if Materials should be PRESERVED
		if (CS_TEST_BITFLAG(PreserveChangesToDefaultMask, ChangeType::Materials))
		{
			UE_LOG(LogCsStaticMesh, Warning, TEXT("%s: %s"), *Context, *(ChangeCounter::Get().ToString()));

			// Check if the SkeletalMesh changed
			if (CS_TEST_BITFLAG(ChangesFromLastMask, ChangeType::StaticMesh))
			{
				UE_LOG(LogCsStaticMesh, Warning, TEXT(" (CHANGED) StaticMesh"));
				UE_LOG(LogCsStaticMesh, Warning, TEXT(" Materials [%d]"), Count);

				for (int32 I = 0; I < Count; ++I)
				{
					UE_LOG(LogCsStaticMesh, Warning, TEXT("  [%d] %s"), I, *(Materials[I]->GetName()));
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
					UE_LOG(LogCsStaticMesh, Warning, TEXT(" (CHANGED) Materials [%d]"), Count);

					for (int32 I = 0; I < Count; ++I)
					{
						UE_LOG(LogCsStaticMesh, Warning, TEXT("  [%d] %s -> %s"), I, *(Component->GetMaterial(I)->GetName()), *(Materials[I]->GetName()));
					}
				}
				else
				{
					UE_LOG(LogCsStaticMesh, Warning, TEXT(" (PRESERVED) Materials [%d]"), Count);

					for (int32 I = 0; I < Count; ++I)
					{
						UE_LOG(LogCsStaticMesh, Warning, TEXT("  [%d] %s"), I, *(Materials[I]->GetName()));
					}
				}
			}
			// Default -> SET
			else
			{
				UE_LOG(LogCsStaticMesh, Warning, TEXT(" DEFAULT -> Materials [%d]"), Count);

				for (int32 I = 0; I < Count; ++I)
				{
					UE_LOG(LogCsStaticMesh, Warning, TEXT("  [%d] %s"), I, *(Materials[I]->GetName()));
				}
			}
		}
	}
}

void ACsStaticMeshActorPooledImpl::Handle_AttachAndSetTransform(PooledPayloadType* Payload, StaticMeshPayloadType* StaticMeshPayload)
{
	using namespace NCsStaticMeshActorPooledImpl::NCached;

	const FString& Context = Str::Handle_AttachAndSetTransform;

	CS_NON_SHIPPING_EXPR(Log_AttachAndSetTransform(Payload, StaticMeshPayload));

	// If the Parent is set, attach the StaticMeshActor to the Parent
	USceneComponent* Parent = nullptr;

	UObject* Object = Payload->GetParent();

	// SceneComponent
	if (USceneComponent* Component = Cast<USceneComponent>(Object))
		Parent = Component;
	// Actor -> Get RootComponent
	else
	if (AActor* Actor = Cast<AActor>(Object))
		Parent = Actor->GetRootComponent();;

	const FTransform3f& Transform = StaticMeshPayload->GetTransform();
	const int32& TransformRules   = StaticMeshPayload->GetTransformRules();

	typedef NCsStaticMeshActor::NPayload::EChange ChangeType;
	typedef NCsStaticMeshActor::NPayload::NChange::FCounter ChangeCounter;
	#define ChangeHelper NCsStaticMeshActor::NPayload::NChange
	typedef NCsArray::FLibrary ArrayLibrary;

	if (Parent)
	{
		const FAttachmentTransformRules& Rule = StaticMeshPayload->GetAttachmentTransformRule();
		const FName& Bone					  = StaticMeshPayload->GetBone();

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

			typedef NCsSkeletalMesh::FLibrary SkeletalMeshLibrary;

			check(SkeletalMeshLibrary::ConditionalIsBoneOrSocketValidChecked(Context, Parent, Bone));

			GetMeshComponent()->AttachToComponent(Parent, Rule, Bone);
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

		ArrayLibrary::ResetAndAppend<FName>(GetMeshComponent()->ComponentTags, StaticMeshPayload->GetTags());
	}
	// NO Parent, set the World Transform of the StaticMeshComponent
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

		ArrayLibrary::ResetAndAppend<FName>(Tags, StaticMeshPayload->GetTags());
	}
	CS_SET_BITFLAG(ChangesToDefaultMask, ChangeType::Transform);

	#undef ChangeHelper
}

void ACsStaticMeshActorPooledImpl::Log_AttachAndSetTransform(PooledPayloadType* Payload, StaticMeshPayloadType* StaticMeshPayload)
{
}

#undef PooledPayloadType
#undef StaticMeshPayloadType

void ACsStaticMeshActorPooledImpl::Handle_ClearStaticMesh()
{
	typedef NCsStaticMeshActor::NPayload::EChange ChangeType;
	typedef NCsStaticMeshActor::NPayload::NChange::FCounter ChangeCounter;
	typedef NCsMaterial::NMID::FLibrary MIDLibrary;

	// If StaticMesh is SET and meant to be PRESERVED, Do Nothing
	if (CS_TEST_BITFLAG(PreserveChangesToDefaultMask, ChangeType::StaticMesh) &&
		CS_TEST_BITFLAG(ChangesToDefaultMask, ChangeType::StaticMesh))
	{
		// Do Nothing
		ChangeCounter::Get().AddPreserved();
		ChangeCounter::Get().AddPreserved();
	}
	else
	{
		GetMeshComponent()->SetStaticMesh(nullptr);
		MIDLibrary::Destroy(MIDs);
		CS_CLEAR_BITFLAG(ChangesToDefaultMask, ChangeType::StaticMesh);
		CS_CLEAR_BITFLAG(ChangesToDefaultMask, ChangeType::Materials);
		ChangeCounter::Get().AddCleared();
		ChangeCounter::Get().AddCleared();
	}
}

void ACsStaticMeshActorPooledImpl::Handle_ClearAttachAndTransform()
{
	typedef NCsStaticMeshActor::NPayload::EChange ChangeType;
	typedef NCsStaticMeshActor::NPayload::NChange::FCounter ChangeCounter;
	#define ChangeHelper NCsStaticMeshActor::NPayload::NChange
	
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

void ACsStaticMeshActorPooledImpl::LogChangeCounter()
{
	if (CS_CVAR_LOG_IS_SHOWING(LogStaticMeshActorPooledChangeCounter))
	{
		typedef NCsStaticMeshActor::NPayload::NChange::FCounter ChangeCounter;

		UE_LOG(LogCsStaticMesh, Warning, TEXT("ACsStaticMeshActorPooledImpl::LogChangeCounter: %s."), *(ChangeCounter::Get().ToString()));
	}
}

#pragma endregion Set / Clear Changes
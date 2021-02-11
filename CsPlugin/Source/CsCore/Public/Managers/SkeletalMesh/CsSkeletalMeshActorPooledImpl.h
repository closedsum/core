// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Animation/SkeletalMeshActor.h"
// Interfaces
#include "Managers/Time/CsUpdate.h"
#include "Managers/Pool/CsPooledObject.h"
#include "Managers/SkeletalMesh/CsSkeletalMeshActor.h"
// Types
#include "Managers/SkeletalMesh/CsSkeletalMeshActorPooled.h"
#include "Managers/SkeletalMesh/CsTypes_SkeletalMeshActor.h"

#include "CsSkeletalMeshActorPooledImpl.generated.h"

class UAudioComponent;
class UDamageType;

// NCsPooledObject::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NPayload, IPayload)
// NCsSkeletalMeshActor::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsSkeletalMeshActor, NPayload, IPayload)
// NCsSkeletalMeshActor::NCache::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsSkeletalMeshActor, NCache, FImpl)

/**
* 
*/
UCLASS()
class CSCORE_API ACsSkeletalMeshActorPooledImpl : public ASkeletalMeshActor,
											      public ICsUpdate,
												  public ICsPooledObject,
												  public ICsSkeletalMeshActor
{
	GENERATED_UCLASS_BODY()

#define CacheType NCsPooledObject::NCache::ICache
#define CacheImplType NCsSkeletalMeshActor::NCache::FImpl
#define PayloadType NCsPooledObject::NPayload::IPayload
#define SkeletalMeshPayloadType NCsSkeletalMeshActor::NPayload::IPayload

// UObject Interface
#pragma region
public:

	virtual void BeginDestroy() override;

#pragma endregion UObject Interface

// AActor Interface
#pragma region
public:

	virtual void BeginPlay() override;

	virtual void FellOutOfWorld(const UDamageType& DmgType) override;

	virtual void OutsideWorldBounds() override;

#pragma endregion AActor Interface

// ICsUpdate
#pragma region
public:

	void Update(const FCsDeltaTime& DeltaTime);

#pragma endregion ICsUpdate

protected:

	CacheType* Cache;
	CacheImplType* CacheImpl;

	void ConstructCache();

	uint32 PreserveChangesToDefaultMask;
	uint32 ChangesToDefaultMask;
	uint32 ChangesFromLastMask;

// ICsPooledObject
#pragma region
public:

	FORCEINLINE CacheType* GetCache() const { return Cache; }

	void Allocate(PayloadType* Payload);

	void Deallocate();

#pragma endregion ICsPooledObject

// ICsSkeletalMeshActor
#pragma region
public:

	FORCEINLINE USkeletalMeshComponent* GetMeshComponent() const
	{
		return GetSkeletalMeshComponent();
	}

#pragma endregion ICsSkeletalMeshActor

protected:

	void Deallocate_Internal();

	void Handle_SetSkeletalMesh(SkeletalMeshPayloadType* Payload);
	void LogSetSkeletalMesh(SkeletalMeshPayloadType* Payload);

	void Handle_SetMaterials(SkeletalMeshPayloadType* Payload);
	void LogSetMaterials(SkeletalMeshPayloadType* Payload);

	FName AttachToBone;

	void Handle_AttachAndSetTransform(PayloadType* Payload, SkeletalMeshPayloadType* SkeletalMeshPayload);
	void LogAttachAndSetTransform(PayloadType* Payload, SkeletalMeshPayloadType* SkeletalMeshPayload);

	void Handle_ClearSkeletalMesh();
	void Handle_ClearAttachAndTransform();

#undef CacheType
#undef CacheImplType
#undef PayloadType
#undef SkeletalMeshPayloadType
};
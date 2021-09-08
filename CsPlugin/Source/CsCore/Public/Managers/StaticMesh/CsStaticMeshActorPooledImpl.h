// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Engine/StaticMeshActor.h"
// Interfaces
#include "Managers/Time/CsUpdate.h"
#include "Managers/Pool/CsPooledObject.h"
#include "Managers/StaticMesh/CsStaticMeshActor.h"
// Types
#include "Managers/StaticMesh/CsStaticMeshActorPooled.h"
#include "Managers/StaticMesh/CsTypes_StaticMeshActor.h"

#include "CsStaticMeshActorPooledImpl.generated.h"

class UAudioComponent;
class UDamageType;

// NCsPooledObject::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NPayload, IPayload)
// NCsStaticMeshActor::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsStaticMeshActor, NPayload, IPayload)
// NCsStaticMeshActor::NCache::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsStaticMeshActor, NCache, FImpl)

/**
* 
*/
UCLASS()
class CSCORE_API ACsStaticMeshActorPooledImpl : public AStaticMeshActor,
											    public ICsUpdate,
												public ICsPooledObject,
												public ICsStaticMeshActor
{
	GENERATED_UCLASS_BODY()

#define CacheType NCsPooledObject::NCache::ICache
#define CacheImplType NCsStaticMeshActor::NCache::FImpl
#define PooledPayloadType NCsPooledObject::NPayload::IPayload
#define StaticMeshPayloadType NCsStaticMeshActor::NPayload::IPayload

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

	void Allocate(PooledPayloadType* Payload);

	void Deallocate();

#pragma endregion ICsPooledObject

// ICsStaticMeshActor
#pragma region
public:

	FORCEINLINE UStaticMeshComponent* GetMeshComponent() const
	{
		return GetStaticMeshComponent();
	}

#pragma endregion ICsStaticMeshActor

protected:

	void Deallocate_Internal();

	void Handle_SetStaticMesh(StaticMeshPayloadType* Payload);
	void Log_SetStaticMesh(StaticMeshPayloadType* Payload);

	void Handle_SetMaterials(StaticMeshPayloadType* Payload);
	void Log_SetMaterials(StaticMeshPayloadType* Payload);

	FName AttachToBone;

	void Handle_AttachAndSetTransform(PooledPayloadType* Payload, StaticMeshPayloadType* SkeletalMeshPayload);
	void Log_AttachAndSetTransform(PooledPayloadType* Payload, StaticMeshPayloadType* SkeletalMeshPayload);

	void Handle_ClearStaticMesh();
	void Handle_ClearAttachAndTransform();

	void LogChangeCounter();

#undef CacheType
#undef CacheImplType
#undef PooledPayloadType
#undef StaticMeshPayloadType
};
// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Engine/StaticMeshActor.h"
// Interfaces
#include "Update/CsUpdate.h"
#include "Shutdown/CsShutdown.h"
#include "Managers/Pool/CsPooledObject.h"
#include "Managers/StaticMesh/CsStaticMeshActor.h"
// Types
#include "Managers/StaticMesh/CsStaticMeshActorPooled.h"
#include "Managers/StaticMesh/CsTypes_StaticMeshActor.h"

#include "CsStaticMeshActorPooledImpl.generated.h"

// PooledPayloadType (NCsPooledObject::NPayload::IPayload)
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NPayload, IPayload)
// PayloadType (NCsStaticMeshActor::NPayload::IPayload)
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsStaticMeshActor, NPayload, IPayload)
// CacheImplType (NCsStaticMeshActor::NCache::NImpl::FImpl)
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsStaticMeshActor, NCache, NImpl, FImpl)

class UMaterialInstanceDynamic;

/**
* 
*/
UCLASS()
class CSSTATICMESH_API ACsStaticMeshActorPooledImpl : public AStaticMeshActor,
													  public ICsUpdate,
													  public ICsShutdown,
													  public ICsPooledObject,
													  public ICsStaticMeshActor
{
	GENERATED_UCLASS_BODY()

private:

	using CacheType = NCsPooledObject::NCache::ICache;
	using CacheImplType = NCsStaticMeshActor::NCache::NImpl::FImpl;
	using PooledPayloadType = NCsPooledObject::NPayload::IPayload;
	using PayloadType = NCsStaticMeshActor::NPayload::IPayload;

// UObject Interface
#pragma region
public:

	virtual void BeginDestroy() override;

#pragma endregion UObject Interface

// AActor Interface
#pragma region
public:

	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

	virtual void FellOutOfWorld(const UDamageType& DmgType) override;

	virtual void OutsideWorldBounds() override;

#pragma endregion AActor Interface

// ICsUpdate
#pragma region
public:

	void Update(const FCsDeltaTime& DeltaTime);

#pragma endregion ICsUpdate

// ICsShutdown
#pragma region
public:

	void Shutdown();

	FORCEINLINE bool HasShutdown() const { return bShutdown; }
#pragma endregion ICsShutdown

// Shutdown
#pragma region
private:

	bool bShutdown;

#pragma endregion Shutdown

// PooledObject
#pragma region
protected:

	CacheType* Cache;

	CacheImplType* CacheImpl;

	void ConstructCache();

	uint32 PreserveChangesToDefaultMask;
	uint32 ChangesToDefaultMask;
	uint32 ChangesFromLastMask;

#pragma endregion PooledObject

// ICsPooledObject
#pragma region
public:

	FORCEINLINE CacheType* GetCache() const { return Cache; }

	void Allocate(PooledPayloadType* Payload);

	void Deallocate();

#pragma endregion ICsPooledObject

// PooledObject
#pragma region
protected:

	void Deallocate_Internal();

#pragma endregion PooledObject

// ICsStaticMeshActor
#pragma region
public:

	FORCEINLINE UStaticMeshComponent* GetMeshComponent() const { return GetStaticMeshComponent(); }
	FORCEINLINE const TArray<UMaterialInstanceDynamic*>& GetMIDs() const { return  MIDs; }

#pragma endregion ICsStaticMeshActor

// Materials
#pragma region
protected:

	UPROPERTY()
	TArray<UMaterialInstanceDynamic*> MIDs;

#pragma endregion Materials

// Set / Clear Changes
#pragma region
protected:

	void Handle_SetStaticMesh(PayloadType* Payload);
	void Log_SetStaticMesh(PayloadType* Payload);

	void Handle_SetMaterials(PayloadType* Payload);
	void Log_SetMaterials(PayloadType* Payload);

	FName AttachToBone;

	void Handle_AttachAndSetTransform(PooledPayloadType* Payload, PayloadType* SkeletalMeshPayload);
	void Log_AttachAndSetTransform(PooledPayloadType* Payload, PayloadType* SkeletalMeshPayload);

	void Handle_ClearStaticMesh();
	void Handle_ClearAttachAndTransform();

	void LogChangeCounter();

#pragma endregion Set / Clear Changes
};
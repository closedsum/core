// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Engine/StaticMeshActor.h"
#include "Managers/Time/CsUpdate.h"
#include "Managers/Pool/CsPooledObject.h"
#include "Managers/StaticMesh/CsStaticMeshActorPooled.h"
#include "Managers/StaticMesh/CsTypes_StaticMeshActor.h"

#include "CsStaticMeshActorPooledImpl.generated.h"

class UAudioComponent;
class UDamageType;
struct ICsPooledObjectCache;
struct ICsPayload_PooledObject;
struct ICsPayload_StaticMeshActor;

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

	ICsPooledObjectCache* Cache;

	void ConstructCache();

// ICsPooledObject
#pragma region
public:

	ICsPooledObjectCache* GetCache() const;

	void Allocate(ICsPayload_PooledObject* Payload);

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
};
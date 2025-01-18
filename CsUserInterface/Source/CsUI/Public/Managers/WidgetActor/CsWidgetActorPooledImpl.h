// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "GameFramework/Actor.h"
// Interfaces
#include "Update/CsUpdate.h"
#include "Shutdown/CsShutdown.h"
#include "Managers/Pool/CsPooledObject.h"
#include "Managers/WidgetActor/CsWidgetActor.h"

#include "CsWidgetActorPooledImpl.generated.h"

// NCsPooledObject::NCache::ICache
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NCache, ICache)
// NCsWidgetActor::NCache::NImpl::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsWidgetActor, NCache, NImpl, FImpl)
// NCsPooledObject::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NPayload, IPayload)

class UCsWidgetComponent;
struct FCsUserWidgetPooled;

UCLASS()
class CSUI_API ACsWidgetActorPooledImpl : public AActor,
										  public ICsUpdate,
										  public ICsShutdown,
										  public ICsPooledObject,
										  public ICsWidgetActor
{
	GENERATED_UCLASS_BODY()

using CacheType = NCsPooledObject::NCache::ICache;
using CacheImplType = NCsWidgetActor::NCache::NImpl::FImpl;
using PooledPayloadType = NCsPooledObject::NPayload::IPayload;

// UObject Interface
#pragma region
public:

	virtual void BeginDestroy() override;

#pragma endregion UObject Interface

// AActor Interface
#pragma region
protected:

	virtual void BeginPlay() override;

#pragma endregion AActor Interface

// AActor Interface
#pragma region
public:

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

	CacheType* Cache;
	CacheImplType* CacheImpl;

	void ConstructCache();

#pragma endregion PooledObject

// ICsWidgetActor
#pragma region
public:

	FORCEINLINE UCsWidgetComponent* GetWidgetComponent() const { return WidgetComponent; }

#pragma endregion ICsWidgetActor

protected:

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UCsWidgetComponent* WidgetComponent;

	FCsUserWidgetPooled* UserWidgetPooled;
};
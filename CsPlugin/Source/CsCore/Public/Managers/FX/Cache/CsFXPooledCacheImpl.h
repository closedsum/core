// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/Cache/CsPooledObjectCache.h"
#include "Managers/FX/Cache/CsFXPooledCache.h"
#include "Containers/CsWeakObjectPtr.h"

#pragma once

class UObject;
struct FCsInterfaceMap;
struct ICsPayload_PooledObject;

/**
* Basic implementation for Cache implementing the interfaces:
* ICsPooledObjectCache and ICsFXPooledCache. This only supports 
* a bare minimum functionality. For custom functionality create
* another implementation
*/
struct CSCORE_API FCsFXPooledCacheImpl final : public ICsPooledObjectCache,
											   public ICsFXPooledCache
{
public:

	static const FName Name;

private:

	// ICsGetInterfaceMap

	FCsInterfaceMap* InterfaceMap;

	// ICsPooledObjectCache

	int32 Index;

	bool bAllocated;

	bool bQueueDeallocate;

	ECsPooledObjectState State;

	ECsPooledObjectUpdate UpdateType;

	TCsWeakObjectPtr<UObject> Instigator;

	TCsWeakObjectPtr<UObject> Owner;

	TCsWeakObjectPtr<UObject> Parent;

	float WarmUpTime;

	float LifeTime;

	FCsTime StartTime;

	FCsDeltaTime ElapsedTime;

	// ICsProjectileCache

	UNiagaraComponent* FXComponent;

	ECsFXDeallocateMethod DeallocateMethod;

	float QueuedLifeTime;

public:

	FCsFXPooledCacheImpl();

	~FCsFXPooledCacheImpl();

// ICsGetInterfaceMap
#pragma region
public:

	FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
	{
		return InterfaceMap;
	}

#pragma endregion ICsGetInterfaceMap

// ICsPooledObjectCache
#pragma region
public:

	FORCEINLINE void Init(const int32& InIndex)
	{
		Index = InIndex;
	}

	FORCEINLINE const int32& GetIndex() const
	{
		return Index;
	}

	void Allocate(ICsPayload_PooledObject* Payload);

	FORCEINLINE const bool& IsAllocated() const
	{
		return bAllocated;
	}

	void Deallocate();

	void QueueDeallocate();

	bool ShouldDeallocate() const;

	FORCEINLINE const ECsPooledObjectState& GetState() const
	{
		return State;
	}

	FORCEINLINE const ECsPooledObjectUpdate& GetUpdateType() const
	{
		return UpdateType;
	}

	FORCEINLINE UObject* GetInstigator() const
	{
		return Instigator.Get();
	}

	FORCEINLINE UObject* GetOwner() const
	{
		return Owner.Get();
	}

	FORCEINLINE UObject* GetParent() const
	{
		return Parent.Get();
	}

	FORCEINLINE const float& GetWarmUpTime() const
	{
		return WarmUpTime;
	}

	FORCEINLINE const float& GetLifeTime() const
	{
		return LifeTime;
	}

	FORCEINLINE const FCsTime& GetStartTime() const
	{
		return StartTime;
	}

	FORCEINLINE const FCsDeltaTime& GetElapsedTime() const
	{
		return ElapsedTime;
	}

	bool HasLifeTimeExpired();

	void Reset();

#pragma endregion ICsPooledObjectCache

public:

	FORCEINLINE void SetLifeTime(const float& InLifeTime)
	{
		LifeTime = InLifeTime;
	}

// ICsFXPooledCache
#pragma region
public:

	FORCEINLINE UNiagaraComponent* GetFXComponent() const
	{
		return FXComponent;
	}

#pragma endregion ICsFXPooledCache

public:

	FORCEINLINE void SetFXComponent(UNiagaraComponent* InFXComponent)
	{
		FXComponent = InFXComponent;
	}

public:

	void Update(const FCsDeltaTime& DeltaTime);

	//void SetData(ICsData_Projectile* InData);
};
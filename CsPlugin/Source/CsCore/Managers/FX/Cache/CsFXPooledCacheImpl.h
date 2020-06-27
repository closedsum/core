// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/CsPooledObjectCache.h"
#include "Managers/FX/Cache/CsFXPooledCache.h"
#include "Containers/CsWeakObjectPtr.h"

#pragma once

class UObject;
struct FCsInterfaceMap;
struct ICsPooledObjectPayload;
//class ICsData_Projectile;

struct CSCORE_API FCsFXPooledCacheImpl : public ICsPooledObjectCache,
										 public ICsFXPooledCache
{
public:

	static const FName Name;

private:

	FCsInterfaceMap* InterfaceMap;

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

	//ICsData_Projectile* Data;

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

	void Allocate(ICsPooledObjectPayload* Payload);

	FORCEINLINE const bool& IsAllocated() const
	{
		return bAllocated;
	}

	void Deallocate();

	FORCEINLINE void QueueDeallocate()
	{
		bQueueDeallocate = true;
	}

	FORCEINLINE const bool& ShouldDeallocate() const
	{
		return bQueueDeallocate;
	}

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

// ICsProjectileCache
#pragma region
public:

#pragma endregion ICsProjectileCache

public:

	void Update(const FCsDeltaTime& DeltaTime);

	//void SetData(ICsData_Projectile* InData);
};
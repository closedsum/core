// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/CsPooledObjectCache.h"
#include "Cache/CsProjectileCache.h"
#include "Containers/CsWeakObjectPtr.h"

#pragma once

class UObject;
struct FCsInterfaceMap;
struct ICsPooledObjectPayload;
class ICsData_Projectile;

struct CSPRJ_API FCsProjectilePooledCacheImpl : public ICsPooledObjectCache,
												public ICsProjectileCache
{
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

	ICsData_Projectile* Data;

public:

	FCsProjectilePooledCacheImpl();

	~FCsProjectilePooledCacheImpl();

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

	void Allocate(ICsPooledObjectPayload* Payload, const FCsTime& InTime);

	FORCEINLINE const bool& IsAllocated() const
	{
		return bAllocated;
	}

	void Deallocate()
	{
		bAllocated = false;
		bQueueDeallocate = false;
	}

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
};
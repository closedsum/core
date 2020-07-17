// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/CsTypes_Pool.h"
#include "Managers/Pool/Cache/CsPooledObjectCache.h"
#include "Containers/CsWeakObjectPtr.h"
#pragma once

class UObject;
struct FCsInterfaceMap;

/**
*/
struct CSTD_API FCsTdCreepPooledCacheImpl : public ICsPooledObjectCache
{
public:

	static const FName Name;

public:

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

	FCsInterfaceMap* InterfaceMap;

	FCsTdCreepPooledCacheImpl();

	~FCsTdCreepPooledCacheImpl();

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

	FORCEINLINE bool ShouldDeallocate() const
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

	FORCEINLINE bool HasLifeTimeExpired()
	{
		return false;
	}

	void Reset();

#pragma endregion ICsPooledObjectCache
};
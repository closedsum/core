// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/Time/CsTypes_Time.h"
#include "GenericPlatform/GenericPlatformAffinity.h"

class UObject;
struct FCsRunnablePayload;
struct FCsRunnableTaskPayload;

/**
*/
struct CSCORE_API FCsRunnableCache
{
public:

	int32 Index;

	bool bAllocated;

	bool bQueueDeallocate;

	TWeakObjectPtr<UObject> Owner;

	FCsTime Time;

	uint32 StackSize;

	EThreadPriority ThreadPriority;

public:

	FCsRunnableCache() :
		Index(INDEX_NONE),
		bAllocated(false),
		bQueueDeallocate(false),
		Owner(nullptr),
		Time(),
		StackSize(0),
		ThreadPriority(EThreadPriority::TPri_Normal)
	{
	}

	virtual ~FCsRunnableCache() {}

	void Init(const int32& InIndex)
	{
		Index = InIndex;
	}

	FORCEINLINE const int32& GetIndex() const
	{
		return Index;
	}

	FORCEINLINE void SetIndex(const int32& InIndex)
	{
		Index = InIndex;
	}

	void Allocate(FCsRunnablePayload* Payload);

	FORCEINLINE const bool& IsAllocated() const
	{
		return bAllocated;
	}

	FORCEINLINE void Deallocate()
	{
		Reset();
	}

	FORCEINLINE void QueueDeallocate()
	{
		bQueueDeallocate = true;
	}

	FORCEINLINE bool ShouldDeallocate() const
	{
		return bQueueDeallocate;
	}

	UObject* GetOwner() { return Owner.IsValid() ? Owner.Get() : nullptr; }

	template<typename T>
	T* GetOwner() { return Cast<T>(GetOwner()); }

	void Reset()
	{
		bAllocated = false;
		bQueueDeallocate = false;

		Owner.Reset();
		Owner = nullptr;
		Time.Reset();
		StackSize = 0;
		ThreadPriority = EThreadPriority::TPri_Normal;
	}
};
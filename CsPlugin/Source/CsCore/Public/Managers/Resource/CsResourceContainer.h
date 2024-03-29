// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

/**
* Container to store any resource. Usually the resource will be a struct.
* The container only holds a reference to the resource. It is not responsible
* for releasing or destroying the resource.
*/
template<typename ResourceType>
struct TCsResourceContainer
{
private:

	/** Index of the container stored in the internal list in NCsResource::NManager::IManager. */
	int32 Index;

	/** Whether the container is allocated or not. */
	bool bAllocated;

	/** A reference to the resource. */
	ResourceType* Resource;

public:

	TCsResourceContainer() :
		Index(INDEX_NONE),
		bAllocated(false),
		Resource(nullptr)
	{
	}

	virtual ~TCsResourceContainer() {}

	FORCEINLINE const int32& GetIndex() const
	{
		return Index;
	}

	FORCEINLINE void SetIndex(const int32& InIndex)
	{
		Index = InIndex;
	}

	FORCEINLINE const bool& IsAllocated() const
	{
		return bAllocated;
	}

	FORCEINLINE void Allocate()
	{
		bAllocated = true;
	}

	FORCEINLINE void Deallocate()
	{
		bAllocated = false;
	}

	FORCEINLINE void Reset()
	{
		Deallocate();
	}

	FORCEINLINE ResourceType* Get()
	{
		return Resource;
	}

	FORCEINLINE const ResourceType* Get() const
	{
		return Resource;
	}

	FORCEINLINE ResourceType& GetRef()
	{
		return *Resource;
	}

	FORCEINLINE const ResourceType& GetRef() const
	{
		return *Resource;
	}

	FORCEINLINE void Set(ResourceType* InResource)
	{
		Resource = InResource;
	}
};
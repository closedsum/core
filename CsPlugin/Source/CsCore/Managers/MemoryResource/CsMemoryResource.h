// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

/**
* Container to store any resource. Usually the resource will be a struct.
* The container only holds a reference to the resource. It is not responsible
* for releasing or destroying the resource.
*/
template<typename ResourceType>
struct TCsMemoryResource
{
private:

	/** Index of the container stored in the internal list in TCsManager_MemoryResource. */
	int32 Index;

	/** Whether the container is allocated or not. */
	bool bAllocated;

	/** A reference to the resource. */
	ResourceType* Resource;

public:

	TCsMemoryResource() :
		Index(INDEX_NONE),
		bAllocated(false),
		Resource(nullptr)
	{
	}

	virtual ~TCsMemoryResource() {}

	const int32& GetIndex() const
	{
		return Index;
	}

	void SetIndex(const int32& InIndex)
	{
		Index = InIndex;
	}

	const bool& IsAllocated() const
	{
		return bAllocated;
	}

	void Allocate()
	{
		bAllocated = true;
	}

	void Deallocate()
	{
		bAllocated = false;
	}

	void Reset()
	{
		Deallocate();
	}

	ResourceType* Get()
	{
		return Resource;
	}

	void Set(ResourceType* InResource)
	{
		Resource = InResource;
	}
};
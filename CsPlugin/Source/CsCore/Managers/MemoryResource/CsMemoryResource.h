// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

template<typename ResourceType>
struct TCsMemoryResource
{
private:

	int32 Index;

	bool bAllocated;

	ResourceType* Resource;

public:

	TCsMemoryResource() :
		Index(INDEX_NONE),
		bAllocated(false),
		Resource(nullptr)
	{
	}

	virtual ~TRsMemoryResource() {}

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
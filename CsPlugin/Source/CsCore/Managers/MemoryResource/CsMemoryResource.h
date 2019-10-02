// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

struct ICsMemoryResource
{
public:

	virtual ~ICsMemoryResource() {}

	virtual const int32& GetIndex() const = 0;

	virtual void SetIndex(const int32& InIndex) = 0;

	virtual const bool& IsAllocated() const = 0;

	virtual void Allocate() = 0;

	virtual void Deallocate() = 0;

	virtual void Reset() = 0;

	virtual void* Get() = 0;

	virtual void Set(void* InResource) = 0;
};

struct FCsMemoryResource : public ICsMemoryResource
{
private:

	int32 Index;

	bool bAllocated;

	void* Resource;

public:

	FCsMemoryResource() :
		Index(INDEX_NONE),
		bAllocated(false),
		Resource(nullptr)
	{

	}

	virtual ~FCsMemoryResource()
	{
		delete Resource;
	}

// ICsMemoryResource
#pragma region
public:

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

	void* Get()
	{
		return Resource;
	}

	template<typename T>
	T* Get()
	{
		return (T*)Get();
	}

	void Set(void* InResource)
	{
		Resource = InResource;
	}

#pragma endregion ICsMemoryResource
};
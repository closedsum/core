// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

template<typename ResourceType>
class FCsManager_MemoryResource
{
public:

	FCsManager_MemoryResource() :
		Name(),
		Pool(),
		Links(),
		PoolSize(0),
		PoolIndex(INDEX_NONE),
		ActiveHead(nullptr),
		ActiveTail(nullptr),
		ActiveSize(0)
	{
		ContructResourceContainter_Impl.BindRaw(this, &FCsManager_MemoryResource::ConstructResourceContainer);
		ConstructResource_Impl.BindRaw(this, &FCsManager_MemoryResource::ConstructResource);
	}

	virtual ~FCsManager_MemoryResource()
	{
		Shutdown();
	}

private:

	FString Name;

	TArray<ICsMemoryResource*> Pool;
	TArray<TLinkedList<ICsMemoryResource*>*> Links;
	int32 PoolSize;
	int32 PoolIndex;
	TLinkedList<ICsMemoryResource*>* ActiveHead;
	TLinkedList<ICsMemoryResource*>* ActiveTail;
	int32 ActiveSize;

public:

	void Init(const FString& InName)
	{
		Name = InName;
	}

	void Clear()
	{
	}

	void Shutdown()
	{
		Clear();

		// Pool
		{
			const int32 Count = Pool.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				ICsMemoryResource* M = Pool[I];
				delete M;
				Pool[I] = nullptr;
			}
			Pool.Reset();
		}
		PoolSize = 0;
		PoolIndex = 0;

		// Links
		{
			const int32 Count = Links.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				TLinkedList<ICsMemoryResource*>* L = Links[I];
				(**L) = nullptr;
				delete L;
				Links[I] = nullptr;
			}
			Links.Reset();
		}
		ActiveSize = 0;

		ContructResourceContainter_Impl.Unbind();
	}

	virtual ICsMemoryResource* ConstructResourceContainer()
	{
		return new FCsMemoryResource();
	}

	TBaseDelegate<ICsMemoryResource*> ContructResourceContainter_Impl;

	virtual ResourceType* ConstructResource()
	{
		return new ResourceType();
	}

	TBaseDelegate<ResourceType*> ConstructResource_Impl;

	void CreatePool(const int32& Size)
	{
		Pool.Reserve(Size);
		Links.Reserve(Size);

		for (int32 I = 0; I < Size; ++I)
		{
			Add(1);
		}
	}

	void Add(const int32 Count = 1)
	{
		for (int32 I = 0; I < Count; ++I)
		{
			ICsMemoryResource* M = ContructResourceContainter_Impl.Execute();
			M->SetIndex(PoolSize);
			M->Set(ConstructResource_Impl.Execute());
			Pool.Add(M);
			++PoolSize;

			// Add Link
			Links.Add(new TLinkedList<ICsMemoryResource*>());
			// Set Element for Link
			TLinkedList<ICsMemoryResource*>* Link = Links.Last();
			(**Link) = M;
		}
	}

protected:

	void AddActiveLink(TLinkedList<ICsMemoryResource*>* Link)
	{
		if (ActiveTail)
		{
			Link->LinkAfter(ActiveTail);
			ActiveTail = Link;
		}
		else
		{
			ActiveHead = Link;
			ActiveTail = ActiveHead;
		}
	}

	void RemoveActiveLink(TLinkedList<ICsMemoryResource*>* Link)
	{
		// Check to Update HEAD
		if (Link == ActiveHead)
		{
			if (ActiveSize > CS_SINGLETON)
			{
				ActiveHead = Link->GetNextLink();
			}
			else
			{
				ActiveHead = nullptr;
				ActiveTail = nullptr;
			}
		}
		Link->Unlink();
	}

public:

	ICsMemoryResource* Allocate()
	{
		if (IsExhausted())
		{
			checkf(0, TEXT("%s::Allocate: Pool is exhausted."), *Name);
			return nullptr;
		}

		for (int32 I = 0; I < PoolSize; ++I)
		{
			PoolIndex			 = (PoolIndex + 1) % PoolSize;
			ICsMemoryResource* M = Pool[PoolIndex];

			if (!M->IsAllocated())
			{
				M->Allocate();
				AddActiveLink(Links[PoolIndex]);
				++ActiveSize;
				return M;
			}
		}
		checkf(0, TEXT("%s::Allocate: Pool is exhausted."), *Name);
		return nullptr;
	}

	template<typename ResourceContainerType>
	ResourceContainerType* Allocate()
	{
		return (ResourceContainerType*)Allocate();
	}

	ICsMemoryResource* SafeAllocate()
	{
		if (IsExhausted())
		{
			Add(1);
		}

		for (int32 I = 0; I < PoolSize; ++I)
		{
			PoolIndex			 = (PoolIndex + 1) % PoolSize;
			ICsMemoryResource* M = Pool[PoolIndex];

			if (!M->IsAllocated())
			{
				M->Allocate();
				AddActiveLink(Links[PoolIndex]);
				++ActiveSize;
				return M;
			}
		}
		checkf(0, TEXT("%s::Allocate: Pool is exhausted."), *Name);
		return nullptr;
	}

	template<typename ResourceContainerType>
	ResourceContainerType* SafeAllocate()
	{
		return (ResourceContainerType*)SafeAllocate();
	}

	bool Deallocate(ICsMemoryResource* Resource)
	{
		if (!Resource->IsAllocated())
			return false;

		checkf(Resource->Get(), TEXT("%s::Deallocate: Resource is NULL."), *Name);

		const int32& Index = Resource->GetIndex();

		checkf(Index >= 0 && Index < PoolSize, TEXT("%s::Deallocate: Index: %d (< 0 or >= %d) of Resource Container is NOT Valid."), *Name, Index, PoolSize);

		ICsMemoryResource* R = Pool[Index];

		checkf(R == Resource, TEXT("%s::Deallocate: Resource is NOT contained in Pool."), *Name);

		RemoveActiveLink(Links[Index]);
		--ActiveSize;
		return true;
	}

	bool Deallocate(ResourceType* Resource)
	{
		TLinkedList<ICsMemoryResource*>* Current = ActiveHead;
		TLinkedList<ICsMemoryResource*>* Next = Current;

		while (Next)
		{
			Current				 = Next;
			ICsMemoryResource* M = **Current;
			Next				 = Current->GetNextLink();

			ResourceType* R = (ResourceType*)M->Get();

			if (R == Resource)
			{
				RemoveActiveLink(Current);
				--ActiveSize;
				return true;
			}
		}
		return false;
	}

	bool IsExhausted() const
	{
		return PoolSize == ActiveSize;
	}
};
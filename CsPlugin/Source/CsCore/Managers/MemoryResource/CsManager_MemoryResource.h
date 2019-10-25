// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Managers/MemoryResource/CsMemoryResource.h"

template<typename ResourceType, typename ResourceContainerType = TCsMemoryResource<ResourceType>, uint32 SIZE = 128>
class TCsManager_MemoryResource
{
	static_assert(std::is_base_of<TCsMemoryResource<ResourceType>, ResourceContainerType>(), "TCsManager_MemoryResource: ResourceContainerType does NOT implement interface: TCsMemoryResource<ResourceType>.");

public:

	TCsManager_MemoryResource() :
		Name(),
		ResourceContainers(),
		Resources(),
		Pool(),
		PoolSize(0),
		PoolSizeMinusOne(0),
		PoolIndex(INDEX_NONE),
		Links(),
		ActiveHead(nullptr),
		ActiveTail(nullptr),
		ActiveSize(0)
	{
		// Make PoolSize a power of 2.
		PoolSize = SIZE;
		--PoolSize;
		PoolSize |= PoolSize >> 1;
		PoolSize |= PoolSize >> 2;
		PoolSize |= PoolSize >> 4;
		PoolSize |= PoolSize >> 8;
		PoolSize |= PoolSize >> 16;
		++PoolSize;

		PoolSizeMinusOne = PoolSize - 1;

		CreatePool();
	}

	virtual ~TCsManager_MemoryResource()
	{
		Shutdown();
	}

private:

	FString Name;

	TArray<ResourceContainerType> ResourceContainers;
	TArray<ResourceType> Resources;
	TArray<ResourceContainerType*> Pool;

	int32 PoolSize;
	int32 PoolSizeMinusOne;
	uint32 PoolIndex;

	TArray<TLinkedList<ResourceContainerType*>> Links;

	TLinkedList<ResourceContainerType*>* ActiveHead;
	TLinkedList<ResourceContainerType*>* ActiveTail;
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
			for (int32 I = 0; I < PoolSize; ++I)
			{
				Pool[I] = nullptr;
			}
			Pool.Reset();
		}
		PoolSize = 0;
		PoolSizeMinusOne = 0;
		PoolIndex = 0;

		Resources.Reset();

		// Links
		{
			for (TLinkedList<ResourceContainerType*>& Link : Links)
			{
				(*Link) = nullptr;
			}
			Links.Reset();
		}
		ActiveHead = nullptr;
		ActiveTail = nullptr;
		ActiveSize = 0;

		ResourceContainers.Reset();
	}

private:

	void CreatePool()
	{
		ResourceContainers.Reserve(PoolSize);
		ResourceContainers.AddDefaulted(PoolSize);

		Resources.Reserve(PoolSize);
		Resources.AddDefaulted(PoolSize);

		Pool.Reserve(PoolSize);

		Links.Reserve(PoolSize);
		Links.AddDefaulted(PoolSize);

		for (int32 I = 0; I < PoolSize; ++I)
		{
			ResourceContainerType* M = &(ResourceContainers[I]);
			M->SetIndex(I);
			ResourceType* R = &(Resources[I]);
			M->Set(R);
			Pool.Add(M);

			// Set Element for Link
			TLinkedList<ResourceContainerType*>& Link = Links[I];
			(*Link) = M;
		}
	}

	void AddActiveLink(TLinkedList<ResourceContainerType*>* Link)
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

	void RemoveActiveLink(TLinkedList<ResourceContainerType*>* Link)
	{
		// Check to Update HEAD
		if (Link == ActiveHead)
		{
			if (ActiveSize > RS_SINGLETON)
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

	TLinkedList<ResourceContainerType*>* GetActiveHead()
	{
		return ActiveHead;
	}

	TLinkedList<ResourceContainerType*>* GetActiveTail()
	{
		return ActiveTail;
	}

	ResourceContainerType* AllocateAfter(ResourceContainerType* ResourceContainer)
	{
		checkf(ResourceContainer, TEXT("%s::AllocateAfter: ResourceContainer is NULL."));

		if (IsExhausted())
		{
			checkf(0, TEXT("%s::AllocateAfter: Pool is exhausted."), *Name);
			return nullptr;
		}

		// New Resource
		ResourceContainerType* R				  = nullptr;
		TLinkedList<ResourceContainerType*>* Link = nullptr;
		
		for (int32 I = 0; I < PoolSize; ++I)
		{
			PoolIndex				 = (PoolIndex + 1) & PoolSizeMinusOne;
			ResourceContainerType* M = Pool[PoolIndex];

			if (!M->IsAllocated())
			{
				M->Allocate();
				R    = M;
				Link = &(Links[PoolIndex]);
				break;
			}
		}

		if (!R)
		{
			checkf(0, TEXT("%s::AllocateAfter: Pool is exhausted."), *Name);
			return nullptr;
		}

		// Resource to Link After
		const int32& LinkAfterIndex = ResourceContainer->GetIndex();

		TLinkedList<ResourceContainerType*>* LinkAfter = &(Links[LinkAfterIndex]);

		// Make Resource (Link) LinkAfter the link for ResourceContainer (LinkAfter)
		Link->LinkAfter(LinkAfter);

		if (LinkAfter == ActiveTail)
		{
			ActiveTail = Link;
		}
		++ActiveSize;
		return R;
	}

	ResourceContainerType* AllocateBefore(ResourceContainerType* ResourceContainer)
	{
		checkf(ResourceContainer, TEXT("%s::AllocateBefore: ResourceContainer is NULL."));

		if (IsExhausted())
		{
			checkf(0, TEXT("%s::AllocateBefore: Pool is exhausted."), *Name);
			return nullptr;
		}

		// New Resource
		ResourceContainerType* R				  = nullptr;
		TLinkedList<ResourceContainerType*>* Link = nullptr;
		
		for (int32 I = 0; I < PoolSize; ++I)
		{
			PoolIndex				 = (PoolIndex + 1) & PoolSizeMinusOne;
			ResourceContainerType* M = Pool[PoolIndex];

			if (!M->IsAllocated())
			{
				M->Allocate();
				R    = M;
				Link = &(Links[PoolIndex]);
				break;
			}
		}

		if (!R)
		{
			checkf(0, TEXT("%s::AllocateBefore: Pool is exhausted."), *Name);
			return nullptr;
		}

		// Resource to Link Before
		const int32& LinkBeforeIndex = ResourceContainer->GetIndex();

		TLinkedList<ResourceContainerType*>* LinkBefore = &(Links[LinkBeforeIndex]);

		// Make Resource (Link) LinkBefore the link for ResourceContainer (LinkBefore)
		Link->LinkBefore(LinkBefore);

		if (LinkBefore == ActiveHead)
		{
			ActiveHead = Link;
		}
		++ActiveSize;
		return R;
	}

	ResourceContainerType* Allocate()
	{
		if (IsExhausted())
		{
			checkf(0, TEXT("%s::Allocate: Pool is exhausted."), *Name);
			return nullptr;
		}

		for (int32 I = 0; I < PoolSize; ++I)
		{
			PoolIndex				 = (PoolIndex + 1) & PoolSizeMinusOne;
			ResourceContainerType* M = Pool[PoolIndex];

			if (!M->IsAllocated())
			{
				M->Allocate();
				AddActiveLink(&(Links[PoolIndex]));
				++ActiveSize;
				return M;
			}
		}
		checkf(0, TEXT("%s::Allocate: Pool is exhausted."), *Name);
		return nullptr;
	}

	bool Deallocate(ResourceContainerType* ResourceContainer)
	{
		if (!ResourceContainer->IsAllocated())
			return false;

		checkf(ResourceContainer->Get(), TEXT("%s::Deallocate: Resource is NULL."), *Name);

		const int32& Index = ResourceContainer->GetIndex();

		checkf(Index >= 0 && Index < PoolSize, TEXT("%s::Deallocate: Index: %d (< 0 or >= %d) of Resource Container is NOT Valid."), *Name, Index, PoolSize);

		ResourceContainerType* M = Pool[Index];

		checkf(M == ResourceContainer, TEXT("%s::Deallocate: Resource is NOT contained in Pool."), *Name);

		M->Deallocate();
		RemoveActiveLink(&(Links[Index]));
		--ActiveSize;
		return true;
	}

	bool Deallocate(ResourceType* Resource)
	{
		TLinkedList<ResourceContainerType*>* Current = ActiveHead;
		TLinkedList<ResourceContainerType*>* Next	   = Current;

		while (Next)
		{
			Current					 = Next;
			ResourceContainerType* M = **Current;
			Next					 = Current->GetNextLink();

			ResourceType* R = M->Get();

			if (R == Resource)
			{
				M->Deallocate();
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
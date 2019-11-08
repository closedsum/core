// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Managers/MemoryResource/CsMemoryResource.h"
#include "Types/CsTypes_Macro.h"
#include "Containers/CsDoubleLinkedList.h"

template<typename ResourceType, typename ResourceContainerType = TCsMemoryResource<ResourceType>, uint32 BUCKET_SIZE = 128>
class TCsManager_MemoryResource
{
	static_assert(std::is_base_of<TCsMemoryResource<ResourceType>, ResourceContainerType>(), "TCsManager_MemoryResource: ResourceContainerType does NOT implement interface: IRsMemoryResource.");

public:

	TCsManager_MemoryResource() :
		Name(),
		ResourceContainers(),
		Resources(),
		Pool(),
		PoolSize(0),
		PoolSizeMinusOne(0),
		PoolIndex(0),
		Links(),
		ActiveHead(nullptr),
		ActiveTail(nullptr),
		ActiveSize(0)
	{
		Name = TEXT("TCsManager_MemoryResource");

		// Make PoolSize a power of 2.
		PoolSize = BUCKET_SIZE;
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

	/** Name of the Manager */
	FString Name;

	/** List of ResourceContainerTypes */
	TArray<ResourceContainerType> ResourceContainers;
	/** List of ResourceTypes */
	TArray<ResourceType> Resources;
	/** List of references to ResourceContainerTypes. These references map one to one with
		the elements in ResourceContainers. */
	TArray<ResourceContainerType*> Pool;

	/** Size of the pool */
	int32 PoolSize;
	/** One minus size of the pool. This is cached for ease of use. */
	int32 PoolSizeMinusOne;
	/** Index of the last allocated ResourceContainerType in Pool. */
	uint32 PoolIndex;

	/** List of LinkedList elements storing references to ResourceContainerTypes */
	TArray<TCsDoubleLinkedList<ResourceContainerType*>> Links;

	/** Current head of the linked list of allocated ResourceContainerTypes */
	TCsDoubleLinkedList<ResourceContainerType*>* ActiveHead;
	/** Current tail of the linked list of allocated ResourceContainerTypes */
	TCsDoubleLinkedList<ResourceContainerType*>* ActiveTail;
	/** The current number of allocated ResourceContainerTypes */
	int32 ActiveSize;

public:

	/**
	* Set the name of the Manager. This is mostly used for debugging.
	*  Default value is TCsManager_MemoryResource.
	*
	* @param InName		Name to set for the Manager.
	*/
	void SetName(const FString& InName)
	{
		Name = InName;
	}

	/**
	* Clear
	*/
	void Clear()
	{
	}

	/**
	* Releases all memory and resets and containers.
	*/
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
			for (TCsDoubleLinkedList<ResourceContainerType*>& Link : Links)
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

// Pool
#pragma region
private:

	/**
	* Creates a pool of resource containers and resources of size PoolSize.
	*/
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
			TCsDoubleLinkedList<ResourceContainerType*>& Link = Links[I];
			(*Link) = M;
		}
	}

public:

	/**
	* Get a reference to the Pool.
	*
	* return a reference to the Pool.
	*/
	FORCEINLINE const TArray<ResourceContainerType*>& GetPool() const
	{
		return Pool;
	}

	/**
	* Get the pool size.
	* 
	* return Pool Size
	*/
	FORCEINLINE const int32& GetPoolSize() const
	{
		return PoolSize;
	}

	/**
	* Check if all the resources have been allocated.
	*
	* return Whether all resources have been allocated.
	*/
	FORCEINLINE bool IsExhausted() const
	{
		return PoolSize == ActiveSize;
	}

	/**
	*
	*
	* @param Index
	* return ResourceContainerType
	*/
	FORCEINLINE ResourceContainerType* GetAt(const int32& Index) const
	{
		checkf(Index > INDEX_NONE && Index < PoolSize, TEXT("%s::GetAt: Index is >= 0 and < PoolSize: %d"), *Name, PoolSize);

		return Pool[Index];
	}

	/**
	*
	* @param Resource	Resource to find the associated container for.
	* return Resource Container associated with the Resource
	*/
	ResourceContainerType* GetContainer(ResourceType* Resource)
	{
		checkf(Resource, TEXT("%s::GetContainer: Resource is NULL."), *Name);

		TCsDoubleLinkedList<ResourceContainerType*>* Current = ActiveHead;
		TCsDoubleLinkedList<ResourceContainerType*>* Next   = Current;

		while (Next)
		{
			Current					 = Next;
			ResourceContainerType* M = **Current;
			Next					 = Current->GetNextLink();

			ResourceType* R = M->Get();

			if (R == Resource)
			{
				return M;
			}
		}
		return nullptr;
	}

#pragma endregion Pool

// Linked List
#pragma region
private:

	/**
	* Add a link, LinkedList pointer to a ResourceContainerType, to the end, ActiveTail,
	*  of the active linked list, list of Resources that have been allocated.
	*
	* @param Link	Pointer to LinkedList element containing a ResourceContainerType.
	*/
	void AddActiveLink(TCsDoubleLinkedList<ResourceContainerType*>* Link)
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

	/**
	* Add a link, LinkedList pointer to a ResourceContainerTytpe, after the ResourceContainer
	*  in the active linked list, list of ResourceTypes that have been allocated. 
	*  This is equivalent to inserting a linked list element after another element.
	*
	* @param Link					Pointer to LinkedList element containing a ResourceContainerType.
	* @param ResourceContainer		Container for a ResourceType
	*/
	void AddActiveLinkAfter(TCsDoubleLinkedList<ResourceContainerType*>* Link, ResourceContainerType* ResourceContainer)
	{
		// Resource to Link After
		const int32& LinkAfterIndex = ResourceContainer->GetIndex();

		TCsDoubleLinkedList<ResourceContainerType*>* LinkAfter = &(Links[LinkAfterIndex]);

		// Make Resource (Link) LinkAfter the link for ResourceContainer (LinkAfter)
		Link->LinkAfter(LinkAfter);

		if (LinkAfter == ActiveTail)
		{
			ActiveTail = Link;
		}
	}

	/**
	* Add a link, LinkedList pointer to a ResourceContainerTytpe, before the ResourceContainer
	*  in the active linked list, list of ResourceTypes that have been allocated.
	*  This is equivalent to inserting a linked list element before another element.
	*
	* @param Link					Pointer to LinkedList element containing a ResourceContainerType.
	* @param ResourceContainer		Container for a ResourceType
	*/
	void AddActiveLinkBefore(TCsDoubleLinkedList<ResourceContainerType*>* Link, ResourceContainerType* ResourceContainer)
	{
		// Resource to Link Before
		const int32& LinkBeforeIndex = ResourceContainer->GetIndex();

		TCsDoubleLinkedList<ResourceContainerType*>* LinkBefore = &(Links[LinkBeforeIndex]);

		// Make Resource (Link) LinkBefore the link for ResourceContainer (LinkBefore)
		Link->LinkBefore(LinkBefore);

		if (LinkBefore == ActiveHead)
		{
			ActiveHead = Link;
		}
	}

	/**
	* Remove a link, LinkedList pointer to a ResourceContainerType, from the active linked
	*  list, list of ResourceTypes that have been allocated.
	*
	* @param Link	Pointer to LinkedList element containing a ResourceContainerType.
	*/
	void RemoveActiveLink(TCsDoubleLinkedList<ResourceContainerType*>* Link)
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
		// Check to Update TAIL
		else
		if (Link == ActiveTail)
		{
			ActiveTail = Link->GetPrevLink();
		}
		Link->Unlink();
	}

public:

	/**
	* Get the current head of the active linked list.
	*
	* return Active Head.
	*/
	FORCEINLINE TCsDoubleLinkedList<ResourceContainerType*>* GetActiveHead()
	{
		return ActiveHead;
	}

	/**
	* Get the current tail of the active linked list.
	*
	* return Active Tail.
	*/
	FORCEINLINE TCsDoubleLinkedList<ResourceContainerType*>* GetActiveTail()
	{
		return ActiveTail;
	}

#pragma endregion LinkedList

// Allocate
#pragma region
public:

	/**
	* Allocate a ResourceType and add the corresponding linked list element after
	*  another ResourceContainerType. This is equivalent to inserting a linked list element
	*  after another element. 
	*
	* @param ResourceContainer		Container for a ResourceType.
	* return ResourceContainerType	Allocated ResourceType wrapped in a container.
	*/
	ResourceContainerType* AllocateAfter(ResourceContainerType* ResourceContainer)
	{
		checkf(ResourceContainer, TEXT("%s::AllocateAfter: ResourceContainer is NULL."), *Name);

		checkf(ResourceContainer->IsAllocated(), TEXT("%s:AllocateAfter: ResourceContainer must be Allocated."), *Name);

		checkf(!IsExhausted(), TEXT("%s::AllocateAfter: Pool is exhausted."), *Name);

		// New Resource
		ResourceContainerType* R				  = nullptr;
		TCsDoubleLinkedList<ResourceContainerType*>* Link = nullptr;
		
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

		checkf(R, TEXT("%s::AllocateAfter: Pool is exhausted."), *Name);

		AddActiveLinkAfter(Link, ResourceContainer);
		++ActiveSize;
		return R;
	}

	/**
	* Allocate a ResourceType and add the corresponding linked list element AFTER
	*  the ActiveHead. This is equivalent to inserting a linked list element
	*  after the head of the list.
	*
	* return ResourceContainerType	Allocated ResourceType wrapped in a container.
	*/
	ResourceContainerType* AllocateAfterHead()
	{
		if (ActiveHead)
			return AllocateAfter(**ActiveHead);
		return Allocate();
	}

	/**
	* Allocate a ResourceType and add the corresponding linked list element before
	*  another ResourceContainerType. This is equivalent to inserting a linked list element
	*  before another element.
	*
	* @param ResourceContainer		Container for a ResourceType.
	* return ResourceContainerType	Allocated ResourceType wrapped in a container.
	*/
	ResourceContainerType* AllocateBefore(ResourceContainerType* ResourceContainer)
	{
		checkf(ResourceContainer, TEXT("%s::AllocateBefore: ResourceContainer is NULL."), *Name);

		checkf(ResourceContainer->IsAllocated(), TEXT("%s:AllocateBefore: ResourceContainer must be Allocated."), *Name);

		checkf(!IsExhausted(), TEXT("%s::AllocateBefore: Pool is exhausted."), *Name);

		// New Resource
		ResourceContainerType* R				  = nullptr;
		TCsDoubleLinkedList<ResourceContainerType*>* Link = nullptr;
		
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

		checkf(R, TEXT("%s::AllocateBefore: Pool is exhausted."), *Name);

		AddActiveLinkBefore(Link, ResourceContainer);
		++ActiveSize;
		return R;
	}

	/**
	* Allocate a ResourceType and add the corresponding linked list element BEFORE
	*  the ActiveHead. This is equivalent to inserting a linked list element
	*  after the head of the list.
	*
	* return ResourceContainerType	Allocated ResourceType wrapped in a container.
	*/
	ResourceContainerType* AllocateBeforeHead()
	{
		if (ActiveHead)
			return AllocateBefore(**ActiveHead);
		return Allocate();
	}

	/**
	* Allocate a ResourceType and add the corresponding linked list element to the 
	*  end of the list
	*
	* return ResourceContainerType	Allocated ResourceType wrapped in a container.
	*/
	ResourceContainerType* Allocate()
	{
		checkf(!IsExhausted(), TEXT("%s::Allocate: Pool is exhausted."), *Name);

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

#pragma endregion Allocate

// Deallocate
#pragma region
public:

	/**
	* Deallocate a ResourceType and remove the corresponding linked list element from the
	*  active linked list.
	*
	* @param ResourceContainer		Container for a ResourceType to deallocate.
	* return Success				Whether the Deallocated preformed successfully or not.
	*/
	bool Deallocate(ResourceContainerType* ResourceContainer)
	{
		checkf(ResourceContainer, TEXT("%s::Deallocate: ResourceContainer is NULL."), *Name);

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

	/**
	* Deallocate a ResourceType and remove the corresponding linked list element from the
	*  active linked list.
	*
	* @param Resource	ResourceType to deallocate.
	* return Success	Whether the Deallocated preformed successfully or not.
	*/
	bool Deallocate(ResourceType* Resource)
	{
		checkf(Resource, TEXT("%s::Deallocate: Resource is NULL."), *Name);

		ResourceContainerType* ResourceContainer = GetContainer(Resource);

		return Deallocate(ResourceContainer);
	}

#pragma endregion Deallocate

// Queue
#pragma region
public:

	/**
	* Allocate and add the element to end of the list of allocated
	*  ResourceContainerTypes. This is equivalent to calling Allocate().
	*
	* return ResourceContainerType
	*/
	ResourceContainerType* Enqueue()
	{
		return Allocate();
	}

	/**
	* Deallocate the current head of the list of allocated ResourceContainerTypes.
	*  This is equivalent to called Deallocate on the ActiveHead.
	*
	* return ResourceContainerType
	*/
	ResourceContainerType* Dequeue()
	{
		if (ActiveHead)
		{
			if (Deallocate(**ActiveHead))
				return **ActiveHead;
		}
		return nullptr;
	}

#pragma endregion Queue

// Stack
#pragma region
public:

	/**
	* Allocate and add the element AFTER the head of the list of allocated 
	*  ResourceContainerTypes. This is equivalent to calling AllocateAfterHead().
	*
	* return ResourceContainerType
	*/
	ResourceContainerType* Push()
	{
		return AllocateAfterHead();
	}

	/**
	* Deallocate the head of the list of allocated ResourceContainerTypes. 
	*  This is equivalent to calling Deallocate() on the ActiveHead.
	*
	* return ResourceContainerType
	*/
	ResourceContainerType* Pop()
	{
		if (ActiveHead)
		{
			if (Deallocate(**ActiveHead))
				return **ActiveHead;
		}
		return nullptr;
	}

#pragma endregion Stack
};
// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#ifndef __CS_MANAGER_RESOURCE_POINTER_TYPE_H__
#define __CS_MANAGER_RESOURCE_POINTER_TYPE_H__

#pragma once

#include "Managers/Resource/Csmanager_Resource.h"
#include "Managers/Resource/CsResourceContainer.h"
#include "Types/CsTypes_Macro.h"
#include "Containers/CsDoubleLinkedList.h"

template<typename ResourceType, typename ResourceContainerType = TCsResourceContainer<ResourceType>>
class TCsManager_ResourcePointerType : public ICsManager_Resource
{
	static_assert(std::is_base_of<TCsResourceContainer<ResourceType>, ResourceContainerType>(), "TCsManager_ResourcePointerType: ResourceContainerType does NOT implement interface: ICsResourceContainer.");

public:

	TCsManager_ResourcePointerType() :
		Name(),
		Resources(),
		Pool(),
		PoolSize(0),
		PoolSizeMinusOne(0),
		PoolIndex(0),
		Links(),
		AllocatedHead(nullptr),
		AllocatedTail(nullptr),
		AllocatedSize(0)
	{
		Name = TEXT("TCsManager_ResourcePointerType");
	}

	virtual ~TCsManager_ResourcePointerType()
	{
		Shutdown();
	}

private:

	/** Name of the Manager */
	FString Name;

	/** List of ResourceTypes */
	TArray<ResourceType*> Resources;
	/** List of references to ResourceContainerTypes. */
	TArray<ResourceContainerType*> Pool;

	/** Size of the pool */
	int32 PoolSize;
	/** One minus size of the pool. This is cached for ease of use. */
	int32 PoolSizeMinusOne;
	/** Index of the last allocated ResourceContainerType in Pool. */
	uint32 PoolIndex;

	/** List of LinkedList elements storing references to ResourceContainerTypes */
	TArray<TCsDoubleLinkedList<ResourceContainerType*>*> Links;

	/** Current head of the linked list of allocated ResourceContainerTypes */
	TCsDoubleLinkedList<ResourceContainerType*>* AllocatedHead;
	/** Current tail of the linked list of allocated ResourceContainerTypes */
	TCsDoubleLinkedList<ResourceContainerType*>* AllocatedTail;
	/** The current number of allocated ResourceContainerTypes */
	int32 AllocatedSize;

public:

	/**
	* Set the name of the Manager. This is mostly used for debugging.
	*  Default value is TCsManager_ResourcePointerType.
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
			for (TCsDoubleLinkedList<ResourceContainerType*>* Link : Links)
			{
				(**Link) = nullptr;
			}
			Links.Reset();
		}
		AllocatedHead = nullptr;
		AllocatedTail = nullptr;
		AllocatedSize = 0;
	}

// Pool
#pragma region
public:

	/**
	* Creates a pool of resource containers and resources of size PoolSize.
	*
	* @param InSize		Size of the pool.
	*/
	void CreatePool(const int32& InSize)
	{
		checkf(InSize > 0, TEXT("TCsManager_MemoryResource::CreatePool: InSize must be GREATER THAN 0."));

		Shutdown();

		Resources.Reserve(PoolSize);

		Pool.Reserve(PoolSize);

		Links.Reserve(PoolSize);
		Links.AddDefaulted(PoolSize);

		for (int32 I = 0; I < PoolSize; ++I)
		{
			ResourceContainerType* M = new ResourceContainerType();
			M->SetIndex(I);
			Pool.Add(M);

			// Set Element for Link
			TCsDoubleLinkedList<ResourceContainerType*>* Link = Links[I];
			(**Link) = M;
		}
	}

	/**
	*
	*
	* @param Resource
	*/
	void Add(ResourceType* Resource)
	{
		if (Resources.Num() < PoolSize)
		{
			const int32 Index = Resources.Num();

			Resources.Add(Resource);
			Pool[Index]->Set(Resource);
		}
		else
		{
			ResourceContainerType* M = new ResourceContainerType();
			M->SetIndex(PoolSize);
			M->Set(Resource);
			Pool.Add(M);
			Resources.Add(R);

			// Set Element for Link
			TCsDoubleLinkedList<ResourceContainerType*>* Link = new TCsDoubleLinkedList<ResourceContainerType*>();
			Links.Add(Link);
			(**Link) = M;

			++PoolSize;
		}
	}

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
		return PoolSize == AllocatedSize;
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

		TCsDoubleLinkedList<ResourceContainerType*>* Current = AllocatedHead;
		TCsDoubleLinkedList<ResourceContainerType*>* Next    = Current;

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
	* Add a link, LinkedList pointer to a ResourceContainerType, to the end, AllocatedTail,
	*  of the allocated linked list, list of Resources that have been allocated.
	*
	* @param Link	Pointer to LinkedList element containing a ResourceContainerType.
	*/
	void AddAllocatedLink(TCsDoubleLinkedList<ResourceContainerType*>* Link)
	{
		if (AllocatedTail)
		{ 
			Link->LinkAfter(AllocatedTail);
			AllocatedTail = Link;
		}
		else
		{
			AllocatedHead = Link;
			AllocatedTail = AllocatedHead;
		}
	}

	/**
	* Add a link, LinkedList pointer to a ResourceContainerTytpe, after the ResourceContainer
	*  in the allocated linked list, list of ResourceTypes that have been allocated. 
	*  This is equivalent to inserting a linked list element after another element.
	*
	* @param Link					Pointer to LinkedList element containing a ResourceContainerType.
	* @param ResourceContainer		Container for a ResourceType
	*/
	void AddAllocatedLinkAfter(TCsDoubleLinkedList<ResourceContainerType*>* Link, ResourceContainerType* ResourceContainer)
	{
		// Resource to Link After
		const int32& LinkAfterIndex = ResourceContainer->GetIndex();

		TCsDoubleLinkedList<ResourceContainerType*>* LinkAfter = &(Links[LinkAfterIndex]);

		// Make Resource (Link) LinkAfter the link for ResourceContainer (LinkAfter)
		Link->LinkAfter(LinkAfter);

		if (LinkAfter == AllocatedTail)
		{
			AllocatedTail = Link;
		}
	}

	/**
	* Add a link, LinkedList pointer to a ResourceContainerTytpe, before the ResourceContainer
	*  in the allocated linked list, list of ResourceTypes that have been allocated.
	*  This is equivalent to inserting a linked list element before another element.
	*
	* @param Link					Pointer to LinkedList element containing a ResourceContainerType.
	* @param ResourceContainer		Container for a ResourceType
	*/
	void AddAllocatedLinkBefore(TCsDoubleLinkedList<ResourceContainerType*>* Link, ResourceContainerType* ResourceContainer)
	{
		// Resource to Link Before
		const int32& LinkBeforeIndex = ResourceContainer->GetIndex();

		TCsDoubleLinkedList<ResourceContainerType*>* LinkBefore = &(Links[LinkBeforeIndex]);

		// Make Resource (Link) LinkBefore the link for ResourceContainer (LinkBefore)
		Link->LinkBefore(LinkBefore);

		if (LinkBefore == AllocatedHead)
		{
			AllocatedHead = Link;
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
		if (Link == AllocatedHead)
		{
			if (AllocatedSize > CS_SINGLETON)
			{
				AllocatedHead = Link->GetNextLink();
			}
			else
			{
				AllocatedHead = nullptr;
				AllocatedTail = nullptr;
			}
		}
		// Check to Update TAIL
		else
		if (Link == AllocatedTail)
		{
			AllocatedTail = Link->GetPrevLink();
		}
		Link->Unlink();
	}

public:

	/**
	* Get the current head of the allocated linked list.
	*
	* return Allocated Head.
	*/
	FORCEINLINE TCsDoubleLinkedList<ResourceContainerType*>* GetAllocatedHead()
	{
		return AllocatedHead;
	}

	/**
	* Get the current tail of the allocated linked list.
	*
	* return Allocated Tail.
	*/
	FORCEINLINE TCsDoubleLinkedList<ResourceContainerType*>* GetAllocatedTail()
	{
		return AllocatedTail;
	}

#pragma endregion LinkedList

// Allocate
#pragma region
public:

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
			PoolIndex				 = (PoolIndex + 1) % PoolSizeMinusOne;
			ResourceContainerType* M = Pool[PoolIndex];

			if (!M->IsAllocated())
			{
				M->Allocate();
				AddAllocatedLink(&(Links[PoolIndex]));
				++AllocatedSize;
				return M;
			}
		}
		checkf(0, TEXT("%s::Allocate: Pool is exhausted."), *Name);
		return nullptr;
	}

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
		ResourceContainerType* R						  = nullptr;
		TCsDoubleLinkedList<ResourceContainerType*>* Link = nullptr;
		
		for (int32 I = 0; I < PoolSize; ++I)
		{
			PoolIndex				 = (PoolIndex + 1) % PoolSizeMinusOne;
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

		AddAllocatedLinkAfter(Link, ResourceContainer);
		++AllocatedSize;
		return R;
	}

	/**
	* Allocate a ResourceType and add the corresponding linked list element AFTER
	*  the AllocatedHead. This is equivalent to inserting a linked list element
	*  after the head of the list.
	*
	* return ResourceContainerType	Allocated ResourceType wrapped in a container.
	*/
	ResourceContainerType* AllocateAfterHead()
	{
		if (AllocatedHead)
			return AllocateAfter(**AllocatedHead);
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
		ResourceContainerType* R						  = nullptr;
		TCsDoubleLinkedList<ResourceContainerType*>* Link = nullptr;
		
		for (int32 I = 0; I < PoolSize; ++I)
		{
			PoolIndex				 = (PoolIndex + 1) % PoolSizeMinusOne;
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

		AddAllocatedLinkBefore(Link, ResourceContainer);
		++AllocatedSize;
		return R;
	}

	/**
	* Allocate a ResourceType and add the corresponding linked list element BEFORE
	*  the AllocatedHead. This is equivalent to inserting a linked list element
	*  after the head of the list.
	*
	* return ResourceContainerType	Allocated ResourceType wrapped in a container.
	*/
	ResourceContainerType* AllocateBeforeHead()
	{
		if (AllocatedHead)
			return AllocateBefore(**AllocatedHead);
		return Allocate();
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
		--AllocatedSize;
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

	/**
	*
	*
	* return
	*/
	bool DeallocateHead()
	{
		if (!AllocatedHead)
			return false;
		return Deallocate(**AllocatedHead);
	}

	/**
	*
	*/
	void DeallocateAll()
	{
		TCsDoubleLinkedList<ResourceContainerType*>* Current = AllocatedHead;
		TCsDoubleLinkedList<ResourceContainerType*>* Next    = Current;

		while (Next)
		{
			Current = Next;
			ResourceContainerType* M = **Current;

			const int32& Index = M->GetIndex();

			M->Deallocate();
			RemoveActiveLink(&(Links[Index]));
			--AllocatedSize;
		}
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
	*  This is equivalent to called Deallocate on the AllocatedHead.
	*
	* return ResourceContainerType
	*/
	ResourceContainerType* Dequeue()
	{
		if (AllocatedHead)
		{
			if (Deallocate(**AllocatedHead))
				return **AllocatedHead;
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
	*  This is equivalent to calling Deallocate() on the AllocatedHead.
	*
	* return ResourceContainerType
	*/
	ResourceContainerType* Pop()
	{
		if (AllocatedHead)
		{
			if (Deallocate(**AllocatedHead))
				return **AllocatedHead;
		}
		return nullptr;
	}

#pragma endregion Stack
};

#endif // #ifndef __CS_MANAGER_RESOURCE_POINTER_TYPE_H__
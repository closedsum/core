/// <reference path="../../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

// Library
var NJsCommon = require('Cs/Library/Library_Common.js');
// Resource
var ResourceContainerType = require('Cs/Managers/Resource/ResourceContainer.js');
// Utility
var FJsAllocationOrder = require('Cs/Utility/AllocationOrder.js');
const FJsDoubleLinkedListNode = require('Cs/Containers/DoubleLinkedListNode');

// "typedefs" - classes
var CommonLibrary = NJsCommon.FLibrary;

// "typedefs" - functions
var checkf = CommonLibrary.checkf;
var IsValidObject = CommonLibrary.IsValidObject;
var IsNullObject = CommonLibrary.IsNullObject;

const INDEX_NONE = -1;

module.exports = class FJsManager_Resource_Fixed
{
    constructor()
    {
        this.Name = "FJsManager_Resource_Fixed";

        this.ResourceContainers = []
        this.Resources = [];
        this.Pool = [];

        this.PoolSize = 0;
        this.PoolSizeMinusOne = 0;
        this.PoolIndex = 0;

        this.AdvancePoolIndex = this.AdvancePoolIndexByOrder;

        this.Links = [];
        this.AllocatedHead = null;
        this.AllocatedTail = null;
        this.AllocatedSize = 0;

        this.AllocationOrder = new FJsAllocationOrder();
    }

    // public
    Clear() { }

    Shutdown()
    {
        this.Clear();

        // Pool
        this.Pool = []
        this.PoolSize = 0;
        this.PoolSizeMinusOne = 0;
        this.PoolIndex = 0;

        this.Resources = [];

        // Links
        this.Links = [];
        this.AllocatedHead = null;
        this.AllocatedTail = null;
        this.AllocatedSize = 0;

        this.AllocationOrder.Shutdown();

        this.ResourceContainers = [];
    }

	// Pool
	// #region Pool
    // public
    CreatePool(size, resourceClassType)
	{
		checkf(CommonLibrary.IsInt(size), "FJsManager_Resource_Fixed.CreatePool. size is NOT an Integer.");

        checkf(size > 0, "FJsManager_Resource_Fixed.CreatePool. size: %d is NOT > 0.", size);

        this.Shutdown();

        // Make PoolSize a power of 2.
        this.PoolSize = size;
        --this.PoolSize;
        this.PoolSize |= this.PoolSize >> 1;
        this.PoolSize |= this.PoolSize >> 2;
        this.PoolSize |= this.PoolSize >> 4;
        this.PoolSize |= this.PoolSize >> 8;
        this.PoolSize |= this.PoolSize >> 16;
        ++this.PoolSize;

        this.PoolSizeMinusOne = this.PoolSize - 1;

        this.ResourceContainers = new Array(this.PoolSize);
        this.Resources          = new Array(this.PoolSize);

        for (let i = 0; i < this.PoolSize; ++i)
        {
			this.ResourceContainers[i] = new ResourceContainerType();
            this.Resources[i] = new resourceClassType();
        }

        this.Pool = new Array(this.PoolSize);

        this.Links = new Array(this.PoolSize);

        for (let i = 0; i < this.PoolSize; ++i)
        {
            this.Links[i] = new FJsDoubleLinkedListNode();
        }

        this.AllocationOrder.Create(this.PoolSize);

        for (let i = 0; i < this.PoolSize; ++i)
        {
			let m = this.ResourceContainers[i];
            m.SetIndex(i);
			let r = this.Resources[i];
			m.Set(r);
            this.Pool[i] = m;

            // Set Element for Link
            let link = this.Links[i];
            link.Element = m;
        }
    }

	/**
	* Get a reference to the Pool.
	*
	* return a reference to the Pool.
	*/
	GetPool() { return this.Pool; }

	/**
	* Get the number of elements in the pool.
	*
	* return Pool Size
	*/
	GetPoolSize() { return this.PoolSize; }

	/**
	* Get the number of allocated elements.
	*
	* return Allocated Size.
	*/
	GetAllocatedSize() { return this.AllocatedSize; }

	/**
	* Check if all the resources have been allocated.
	*
	* return Whether all resources have been allocated.
	*/
    IsExhausted() {	return this.PoolSize === this.AllocatedSize; }

	AdvancePoolIndexByIncrement() { this.PoolIndex = (this.PoolIndex + 1) & this.PoolSizeMinusOne; }

	AdvancePoolIndexByOrder() { this.PoolIndex = this.AllocationOrder.Advance(); }

	/**
	*
	*
	* @param index
	* return ResourceContainerType
	*/
    GetAt(index)
	{
        checkf(index > INDEX_NONE && index < this.PoolSize, "%s.GetAt: Index is >= 0 and < PoolSize: %d", this.Name, this.PoolSize);

		return this.Pool[index];
	}

	/**
	*
	*
	* @param index
	* return ResourceType
	*/
    GetResourceAt(index)
	{
        checkf(index > INDEX_NONE && index < this.PoolSize, "%s.GetResourceAt: Index is >= 0 and < PoolSize: %d", this.Name, this.PoolSize);

		return this.Pool[index].Get();
	}

	/**
	*
	* @param resource	Resource to find the associated container for.
	* return Resource	Container associated with the Resource
	*/
	GetAllocatedContainer(resource)
	{
		checkf(IsValidObject(resource), "%s.GetAllocatedContainer: Resource is NULL.", this.Name);

		let current = this.AllocatedHead;
		let next    = current;

		while (next !== null)
		{
            current = next;
            let m   = current.Element;
			next	= current.GetNextLink();

			let r = m.Get();

            if (r === resource)
			{
				return m;
			}
		}
		return null;
    }

	// #endregion Pool

	// Linked List
	// #region Linked List
    // private

	/**
	* Add a link, LinkedList pointer to a ResourceContainerType, to the end, AllocatedTail,
	*  of the allocated linked list, list of Resources that have been allocated.
	*
	* @param link	Pointer to LinkedList element containing a ResourceContainerType.
	*/
	AddAllocatedLink(link)
	{
		if (IsValidObject(this.AllocatedTail))
		{
			link.LinkAfter(this.AllocatedTail);
			this.AllocatedTail = link;
		}
		else
		{
			this.AllocatedHead = link;
			this.AllocatedTail = this.AllocatedHead;
		}
	}

	/**
	* Add a link, LinkedList pointer to a ResourceContainerTytpe, after the ResourceContainer
	*  in the active linked list, list of ResourceTypes that have been allocated. 
	*  This is equivalent to inserting a linked list element after another element.
	*
	* @param link					Pointer to LinkedList element containing a ResourceContainerType.
	* @param resourceContainer		Container for a ResourceType
	*/
	AddAllocatedLinkAfter(link, resourceContainer)
	{
		// Resource to Link After
		let linkAfterIndex = resourceContainer.GetIndex();

		let linkAfter = this.Links[linkAfterIndex];

		// Make Resource (Link) LinkAfter the link for ResourceContainer (LinkAfter)
		link.LinkAfter(linkAfter);

		if (linkAfter === this.AllocatedTail)
		{
			this.AllocatedTail = link;
		}
	}

	/**
	* Add a link, LinkedList pointer to a ResourceContainerTytpe, before the ResourceContainer
	*  in the allocated linked list, list of ResourceTypes that have been allocated.
	*  This is equivalent to inserting a linked list element before another element.
	*
	* @param link					Pointer to LinkedList element containing a ResourceContainerType.
	* @param resourceContainer		Container for a ResourceType
	*/
	AddAllocatedLinkBefore(link, resourceContainer)
	{
		// Resource to Link Before
		let linkBeforeIndex = resourceContainer.GetIndex();

		let linkBefore = this.Links[linkBeforeIndex];

		// Make Resource (Link) LinkBefore the link for ResourceContainer (LinkBefore)
		link.LinkBefore(linkBefore);

		if (linkBefore === this.AllocatedHead)
		{
			this.AllocatedHead = link;
		}
	}

	/**
	* Remove a link, LinkedList pointer to a ResourceContainerType, from the allocated linked
	*  list, list of ResourceTypes that have been allocated.
	*
	* @param link	Pointer to LinkedList element containing a ResourceContainerType.
	*/
	RemoveActiveLink(link)
	{
		// Check to Update HEAD
		if (link === this.AllocatedHead)
		{
			this.AllocatedHead = link.GetNextLink();

			if (!IsValidObject(this.AllocatedHead))
			{
				this.AllocatedTail = null;
			}
		}
		// Check to Update TAIL
		else
		if (link === this.AllocatedTail)
		{
			this.AllocatedTail = link.GetPrevLink();
		}
		link.Unlink();
	}

   // public

	/**
	* Get the current head of the allocated linked list.
	*
	* return Allocated Head.
	*/
	GetAllocatedHead() { return this.AllocatedHead; }

	/**
	* Get the current tail of the active linked list.
	*
	* return Active Tail.
	*/
	GetAllocatedTail() { return this.AllocatedTail; }

	// #endregion Linked List

	// Allocate
	// #region Allocate
	// public

	/**
	* Allocate a ResourceType and add the corresponding linked list element to the 
	*  end of the list
	*
	* return ResourceContainerType	Allocated ResourceType wrapped in a container.
	*/
	Allocate()
	{
		checkf(!this.IsExhausted(), "%s.Allocate: Pool is exhausted.", this.Name);

		for (let i = 0; i < this.PoolSize; ++i)
		{
			this.AdvancePoolIndex();

			let m = this.Pool[this.PoolIndex];

			if (!m.IsAllocated())
			{
				checkf(m.Get(), "%s.Allocate: Resource is NULL. Container %d no longer holds a reference to a resource.", this.Name, this.PoolIndex);

				m.Allocate();
				this.AddAllocatedLink(this.Links[this.PoolIndex]);
				++this.AllocatedSize;
				return m;
			}
		}
		checkf(false, "%s::Allocate: Pool is exhausted.", this.Name);
		return null;
	}

	/**
	* Allocate a ResourceType and add the corresponding linked list element to the
	*  end of the list
	*
	* return ResourceType	Allocated ResourceType
	*/
	AllocateResource()
	{
		return this.Allocate().Get();
	}

	/**
	* Allocate a ResourceType and add the corresponding linked list element after
	*  another ResourceContainerType. This is equivalent to inserting a linked list element
	*  after another element. 
	*
	* @param resourceContainer		Container for a ResourceType.
	* return ResourceContainerType	Allocated ResourceType wrapped in a container.
	*/
	AllocateAfter(resourceContainer)
	{
		checkf(IsValidObject(ResourceContainer), "%s::AllocateAfter: ResourceContainer is NULL.", this.Name);

		checkf(resourceContainer.IsAllocated(), "%s::AllocateAfter: ResourceContainer must be Allocated.", this.Name);

		checkf(!this.IsExhausted(), "%s::AllocateAfter: Pool is exhausted.", this.Name);

		// New Resource
		let r	 = null;
		let link = null;
		
		for (let i = 0; i < this.PoolSize; ++i)
		{
			this.PoolIndex = (this.PoolIndex + 1) & this.PoolSizeMinusOne;
			let m		   = this.Pool[this.PoolIndex];

			if (!m.IsAllocated())
			{
				checkf(IsValidObject(m.Get()), "%s:AllocateAfter: Resource is NULL. Container %d no longer holds a reference to a resource.", this.Name, this.PoolIndex);

				m.Allocate();
				r    = m;
				link = links[this.PoolIndex];
				break;
			}
		}

		checkf(IsValidObject(r), "%s::AllocateAfter: Pool is exhausted.", this.Name);

		this.AddAllocatedLinkAfter(link, resourceContainer);
		++this.AllocatedSize;
		return r;
	}

	/**
	* Allocate a ResourceType and add the corresponding linked list element AFTER
	*  the AllocatedHead. This is equivalent to inserting a linked list element
	*  after the head of the list.
	*
	* return ResourceContainerType	Allocated ResourceType wrapped in a container.
	*/
	AllocateAfterHead()
	{
		if (IsValidObject(this.AllocatedHead))
			return this.AllocateAfter(this.AllocatedHead.Element);
		return this.Allocate();
	}

	/**
	* Allocate a ResourceType and add the corresponding linked list element before
	*  another ResourceContainerType. This is equivalent to inserting a linked list element
	*  before another element.
	*
	* @param resourceContainer		Container for a ResourceType.
	* return ResourceContainerType	Allocated ResourceType wrapped in a container.
	*/
	AllocateBefore(resourceContainer)
	{
		checkf(IsValidObject(resourceContainer), "%s.AllocateBefore: ResourceContainer is NULL.", this.Name);

		checkf(resourceContainer.IsAllocated(), "%s.AllocateBefore: ResourceContainer must be Allocated.", this.Name);

		checkf(!this.IsExhausted(), "%s.AllocateBefore: Pool is exhausted.", this.Name);

		// New Resource
		let r	 = null;
		let link = null;
		
		for (let i = 0; i < this.PoolSize; ++i)
		{
			this.PoolIndex = (this.PoolIndex + 1) & this.PoolSizeMinusOne;
			let m		   = this.Pool[this.PoolIndex];

			if (!m.IsAllocated())
			{
				checkf(IsValidObject(m.Get()), "%s.AllocateBefore: Resource is NULL. Container %d no longer holds a reference to a resource.", this.Name, this.PoolIndex);

				m.Allocate();
				r    = m;
				link = this.Links[this.PoolIndex];
				break;
			}
		}

		checkf(IsValidObject(r), "%s.AllocateBefore: Pool is exhausted.", this.Name);

		this.AddAllocatedLinkBefore(link, resourceContainer);
		++this.AllocatedSize;
		return r;
	}

	/**
	* Allocate a ResourceType and add the corresponding linked list element BEFORE
	*  the AllocatedHead. This is equivalent to inserting a linked list element
	*  after the head of the list.
	*
	* return ResourceContainerType	Allocated ResourceType wrapped in a container.
	*/
	AllocateBeforeHead()
	{
		if (IsValidObject(this.AllocatedHead))
			return this.AllocateBefore(this.AllocatedHead.Element);
		return this.Allocate();
	}

	// #endregion Allocate

	// Deallocate
	// #region Deallocate
	// public:

	/**
	* Deallocate a ResourceType and remove the corresponding linked list element from the
	*  allocated linked list.
	*
	* @param resourceContainer		Container for a ResourceType to deallocate.
	* return Success				Whether the Deallocate performed successfully or not.
	*/
	Deallocate(resourceContainer)
	{
		checkf(IsValidObject(resourceContainer), "%s.Deallocate: ResourceContainer is NULL.", this.Name);

		if (!resourceContainer.IsAllocated())
			return false;

		checkf(IsValidObject(resourceContainer.Get()), "%s.Deallocate: Resource is NULL.", this.Name);

		let index = resourceContainer.GetIndex();

		checkf(index >= 0 && index < this.PoolSize, "%s.Deallocate: index: %d (< 0 or >= %d) of Resource Container is NOT Valid.", this.Name, index, this.PoolSize);

		let m = this.Pool[index];

		checkf(m === resourceContainer, "%s.Deallocate: Resource is NOT contained in Pool.", this.Name);

		m.Deallocate();
		this.RemoveActiveLink(this.Links[index]);
		this.AllocationOrder.Promote(index);
		--this.AllocatedSize;
		return true;
	}

	/**
	* Deallocate a ResourceType and remove the corresponding linked list element from the
	*  allocated linked list.
	*
	* @param resource	ResourceType to deallocate.
	* return Success	Whether the Deallocate performed successfully or not.
	*/
	DeallocateByResource(resource)
	{
		checkf(IsValidObject(resource), "%s.Deallocate: Resource is NULL.", this.Name);

		let resourceContainer = this.GetAllocatedContainer(resource);

		return this.Deallocate(resourceContainer);
	}

	/**
	* Deallocate a ResourceType and remove the corresponding linked list element from the
	*  allocated linked list.
	*
	* @param index		Index of the ResourceType to deallocate
	* return Success
	*/
	DeallocateAtByIndex(index)
	{
		checkf(index >= 0 && index < this.PoolSize, "%s.DeallocateAt: index: %d (< 0 or >= %d) is NOT Valid.", this.Name, index, this.PoolSize);

		let m = this.Pool[index];

		if (!m.IsAllocated())
			return false;

		checkf(IsValidObject(m.Get()), "%s.DeallocateAt: Resource is NULL.", this.Name);

		m.Deallocate();
		this.RemoveActiveLink(this.Links[index]);
		this.AllocationOrder.Promote(index);
		--this.AllocatedSize;
		return true;
	}

	/**
	* Deallocate a ResourceType and remove the corresponding linked list element from the
	*  allocated linked list.
	*
	* @param resource	ResourceType to deallocate.
	* @param index		Index of the ResourceType to deallocate
	* return Success
	*/
	DeallocateAt(resource, index)
	{
		checkf(IsValidObject(resource), "%s.Deallocate: resource is NULL.", this.Name);

		checkf(index >= 0 && index < this.PoolSize, "%s.DeallocateAt: index: %d (< 0 or >= %d) is NOT Valid.", this.Name, this.index, this.PoolSize);

		let m = this.Pool[index];

		if (!m.IsAllocated())
			return false;

		checkf(IsValidObject(m.Get()), "%s.DeallocateAt: resource is NULL.", this.Name);

		checkf(resource === m.Get(), "%s.DeallocateAt: resource at index: %d is NOT contained in Pool.", this.Name, this.index);

		m.Deallocate();
		this.RemoveActiveLink(this.Links[index]);
		this.AllocationOrder.Promote(index);
		--this.AllocatedSize;
		return true;
	}

	/**
	*
	*
	* return
	*/
	DeallocateHead()
	{
		if (IsNullObject(this.AllocatedHead))
			return false;
		return this.Deallocate(this.AllocatedHead.Element);
	}

	/**
	*
	*/
	DeallocateAll()
	{
		let current = this.AllocatedHead;
		let next	= current;

		while (next != null)
		{
			current	= next;
			let m	= current.Element;

			let index = m.GetIndex();

			m.Deallocate();
			this.RemoveActiveLink(this.Links[index]);
			--this.AllocatedSize;
		}
		this.AllocationOrder.Reset();
	}

	// #endregion Deallocate

	// Queue
	// #region Queue
	// public:

	/**
	* Allocate and add the element to end of the list of allocated
	*  ResourceContainerTypes. This is equivalent to calling Allocate().
	*
	* return ResourceContainerType
	*/
	Enqueue() { return this.Allocate(); }

	/**
	* Deallocate the current head of the list of allocated ResourceContainerTypes.
	*  This is equivalent to called Deallocate on the AllocatedHead.
	*
	* return ResourceContainerType
	*/
	Dequeue()
	{
		if (this.AllocatedHead)
		{
			if (this.Deallocate(this.AllocatedHead.Element))
				return this.AllocatedHead.Element;
		}
		return null;
	}

	// #endregion Queue

	// Stack
	// #region Stack
	// public:

	/**
	* Allocate and add the element AFTER the head of the list of allocated 
	*  ResourceContainerTypes. This is equivalent to calling AllocateAfterHead().
	*
	* return ResourceContainerType
	*/
	Push() { return this.AllocateAfterHead(); }

	/**
	* Deallocate the head of the list of allocated ResourceContainerTypes. 
	*  This is equivalent to calling Deallocate() on the AllocatedHead.
	*
	* return ResourceContainerType
	*/
	Pop()
	{
		if (IsValidObject(this.AllocatedHead))
		{
			if (this.Deallocate(this.AllocatedHead.Element))
				return this.AllocatedHead.Element;
		}
		return null;
	}

	// #endregion Stack
};
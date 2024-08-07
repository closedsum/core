// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core

// ; typing info for auto-completion in Visual Studio Code
// Library
/// <reference path="../../Library/Library_Common.ts">/>
// Utility
/// <reference path="../../Utility/AllocationOrder.ts">/>
// Resource
/// <reference path="ResourceContainer.ts">/>

"use strict"

// Library
var NJsCommon = require('Cs/Library/Library_Common.js');
// Resource
/** @type {FJsResourceContainer} */
var ResourceContainerType = require('Cs/Managers/Resource/ResourceContainer.js');
// Utility
/** @type {FJsAllocationOrder} */
var FJsAllocationOrder = require('Cs/Utility/AllocationOrder.js');
/** @type {FJsDoubleLinkedListNode} */
var FJsDoubleLinkedListNode = require('Cs/Containers/DoubleLinkedListNode');

// "typedefs" - library
/** @type {CommonLibrary} */ var CommonLibrary = NJsCommon.FLibrary;

// "typedefs" - functions
var check			= CommonLibrary.check;
var checkf 			= CommonLibrary.checkf;
var IsValidObject 	= CommonLibrary.IsValidObject;
var IsNullObject 	= CommonLibrary.IsNullObject;
var IsIntChecked	= CommonLibrary.IsIntChecked;
var IsIntChecked2	= CommonLibrary.IsIntChecked2;

const INDEX_NONE = -1;

module.exports = class FJsManager_Resource_Fixed
{
    constructor()
    {
        /** @type {string} */ this.Name = "FJsManager_Resource_Fixed";

        /** @type {FJsResourceContainer[]} */ 	this.ResourceContainers = []
        /** @type {any[]} */					this.Resources = [];
        /** @type {FJsResourceContainer[]} */	this.Pool = [];

        /** @type {number} */	this.PoolSize = 0;
        /** @type {number} */	this.PoolSizeMinusOne = 0;
        /** @type {number} */	this.PoolIndex = 0;

        /** @type {function} */ this.AdvancePoolIndex = this.AdvancePoolIndexByOrder;

        /** @type {FJsDoubleLinkedListNode[]} */	this.Links = [];
        /** @type {FJsDoubleLinkedListNode} */		this.AllocatedHead = null;
        /** @type {FJsDoubleLinkedListNode} */		this.AllocatedTail = null;
        /** @type {number} */ 						this.AllocatedSize = 0;

        /** @type {FJsAllocationOrder} */ this.AllocationOrder = new FJsAllocationOrder();
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
        checkf(size > 0, "FJsManager_Resource_Fixed.CreatePool. size: " + size + " is NOT > 0.");

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

        this.Pool  = new Array(this.PoolSize);
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
	* @returns {any[]} a reference to the Pool.
	*/
	/*any[]*/ GetPool() { return this.Pool; }

	/**
	* Get the number of elements in the pool.
	*
	* @returns {number} Pool Size
	*/
	/*number*/ GetPoolSize() { return this.PoolSize; }

	/**
	* Get the number of allocated elements.
	*
	* @returns {number} Allocated Size.
	*/
	/*number*/ GetAllocatedSize() { return this.AllocatedSize; }

	/**
	* Check if all the resources have been allocated.
	*
	* @returns {boolean} Whether all resources have been allocated.
	*/
    /*boolean*/ IsExhausted() {	return this.PoolSize === this.AllocatedSize; }

	AdvancePoolIndexByIncrement() { this.PoolIndex = (this.PoolIndex + 1) & this.PoolSizeMinusOne; }

	AdvancePoolIndexByOrder() { this.PoolIndex = this.AllocationOrder.Advance(); }

	/**
	*
	*
	* @param {number} 				  index
	* @returns {FJsResourceContainer} ResourceContainerType
	*/
    /*FJsResourceContainer*/ GetAt(index /*number*/)
	{
		check(IsIntChecked2(index));
        checkf(index > INDEX_NONE && index < this.PoolSize, this.Name + ".GetAt: Index: " + index + " is NOT >= 0 and < PoolSize: " + this.PoolSize);
		return this.Pool[index];
	}

	/**
	*
	* @param {string}				  context
	* @param {number} 				  index
	* @returns {FJsResourceContainer} ResourceContainerType
	*/
    /*FJsResourceContainer*/ GetAtChecked(context /*string*/, index /*number*/)
	{
		check(IsIntChecked(context, index));
        checkf(index > INDEX_NONE && index < this.PoolSize, context + ": Index: " + index + " is NOT >= 0 and < PoolSize: " + this.PoolSize);
		return this.Pool[index];
	}

	/**
	*
	*
	* @param {number} 	index
	* @returns {any} 	ResourceType
	*/
    /*any*/ GetResourceAt(index /*number*/)
	{
        checkf(index > INDEX_NONE && index < this.PoolSize, this.Name + ".GetResourceAt: Index: " + index + " is >= 0 and < PoolSize: " + this.PoolSize);
		return this.Pool[index].Get();
	}

	/**
	*
	* @param {any}						resource	Resource to find the associated container for.
	* @returns {FJsResourceContainer}	Resource	Container associated with the Resource
	*/
	/*FJsResourceContainer*/ GetAllocatedContainer(resource /*any*/)
	{
		checkf(IsValidObject(resource), this.Name + ".GetAllocatedContainer: Resource is NULL.");

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
	* @param {FJsDoubleLinkedListNode} link	Pointer to LinkedList element containing a ResourceContainerType.
	*/
	AddAllocatedLink(link /*FJsDoubleLinkedListNode*/)
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
	* @param {FJsDoubleLinkedListNode} 	link					Pointer to LinkedList element containing a ResourceContainerType.
	* @param {FJsResourceContainer} 	resourceContainer		Container for a ResourceType
	*/
	AddAllocatedLinkAfter(link /*FJsDoubleLinkedListNode*/, resourceContainer /*FJsResourceContainer*/)
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
	* @param {FJsDoubleLinkedListNode}	link					Pointer to LinkedList element containing a ResourceContainerType.
	* @param {FJsResourceContainer}		resourceContainer		Container for a ResourceType
	*/
	AddAllocatedLinkBefore(link /*FJsDoubleLinkedListNode*/, resourceContainer /*FJsResourceContainer*/)
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
	* @param {FJsDoubleLinkedListNode} link	Pointer to LinkedList element containing a ResourceContainerType.
	*/
	RemoveActiveLink(link /*FJsDoubleLinkedListNode*/)
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
	* @returns {FJsDoubleLinkedListNode} Allocated Head.
	*/
	/*FJsDoubleLinkedListNode*/ GetAllocatedHead() { return this.AllocatedHead; }

	/**
	* Get the current tail of the active linked list.
	*
	* @returns {FJsDoubleLinkedListNode}  Active Tail.
	*/
	/*FJsDoubleLinkedListNode*/ GetAllocatedTail() { return this.AllocatedTail; }

	// #endregion Linked List

	// Allocate
	// #region Allocate
	// public

	/**
	* Allocate a ResourceType and add the corresponding linked list element to the 
	*  end of the list
	*
	* @returns {FJsResourceContainer} ResourceContainerType	Allocated ResourceType wrapped in a container.
	*/
	/*FJsResourceContainer*/ Allocate()
	{
		checkf(!this.IsExhausted(), this.Name + ".Allocate: Pool is exhausted.");

		for (let i = 0; i < this.PoolSize; ++i)
		{
			this.AdvancePoolIndex();

			let m = this.Pool[this.PoolIndex];

			if (!m.IsAllocated())
			{
				checkf(IsValidObject(m.Get()), this.Name + ".Allocate: Resource is NULL. Container " + this.PoolIndex + " no longer holds a reference to a resource.");

				m.Allocate();
				this.AddAllocatedLink(this.Links[this.PoolIndex]);
				++this.AllocatedSize;
				return m;
			}
		}
		checkf(false, this.Name + ".Allocate: Pool is exhausted.");
		return null;
	}

	/**
	* Allocate a ResourceType and add the corresponding linked list element to the
	*  end of the list
	*
	* @returns {any} ResourceType	Allocated ResourceType
	*/
	/*any*/ AllocateResource()
	{
		return this.Allocate().Get();
	}

	/**
	* Allocate a ResourceType and add the corresponding linked list element after
	*  another ResourceContainerType. This is equivalent to inserting a linked list element
	*  after another element. 
	*
	* @param {FJsResourceContainer}		resourceContainer		Container for a ResourceType.
	* @returns {FJsResourceContainer} 	ResourceContainerType	Allocated ResourceType wrapped in a container.
	*/
	/*FJsResourceContainer*/ AllocateAfter(resourceContainer /*FJsResourceContainer*/)
	{
		checkf(IsValidObject(ResourceContainer), this.Name + ".AllocateAfter: ResourceContainer is NULL.");
		checkf(resourceContainer.IsAllocated(), this.Name + ".AllocateAfter: ResourceContainer must be Allocated.");
		checkf(!this.IsExhausted(), this.Name + ".AllocateAfter: Pool is exhausted.");

		// New Resource
		let r	 = null;
		let link = null;
		
		for (let i = 0; i < this.PoolSize; ++i)
		{
			this.PoolIndex = (this.PoolIndex + 1) & this.PoolSizeMinusOne;
			let m		   = this.Pool[this.PoolIndex];

			if (!m.IsAllocated())
			{
				checkf(IsValidObject(m.Get()), this.Name + ".AllocateAfter: Resource is NULL. Container " + this.PoolIndex + " no longer holds a reference to a resource.");

				m.Allocate();
				r    = m;
				link = this.Links[this.PoolIndex];
				break;
			}
		}

		checkf(IsValidObject(r), this.Name + ".AllocateAfter: Pool is exhausted.");

		this.AddAllocatedLinkAfter(link, resourceContainer);
		++this.AllocatedSize;
		return r;
	}

	/**
	* Allocate a ResourceType and add the corresponding linked list element AFTER
	*  the AllocatedHead. This is equivalent to inserting a linked list element
	*  after the head of the list.
	*
	* @returns {FJsResourceContainer} ResourceContainerType	Allocated ResourceType wrapped in a container.
	*/
	/*FJsResourceContainer*/ AllocateAfterHead()
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
	* @param {FJsResourceContainer} 	resourceContainer		Container for a ResourceType.
	* @returns {FJsResourceContainer}	ResourceContainerType	Allocated ResourceType wrapped in a container.
	*/
	/*FJsResourceContainer*/ AllocateBefore(resourceContainer /*FJsResourceContainer*/)
	{
		checkf(IsValidObject(resourceContainer), this.Name + ".AllocateBefore: ResourceContainer is NULL.");
		checkf(resourceContainer.IsAllocated(), this.Name + ".AllocateBefore: ResourceContainer must be Allocated.");
		checkf(!this.IsExhausted(), this.Name + ".AllocateBefore: Pool is exhausted.");

		// New Resource
		let r	 = null;
		let link = null;
		
		for (let i = 0; i < this.PoolSize; ++i)
		{
			this.PoolIndex = (this.PoolIndex + 1) & this.PoolSizeMinusOne;
			let m		   = this.Pool[this.PoolIndex];

			if (!m.IsAllocated())
			{
				checkf(IsValidObject(m.Get()), this.Name + ".AllocateBefore: Resource is NULL. Container " + this.PoolIndex + " no longer holds a reference to a resource.");

				m.Allocate();
				r    = m;
				link = this.Links[this.PoolIndex];
				break;
			}
		}

		checkf(IsValidObject(r), this.Name + ".AllocateBefore: Pool is exhausted.");

		this.AddAllocatedLinkBefore(link, resourceContainer);
		++this.AllocatedSize;
		return r;
	}

	/**
	* Allocate a ResourceType and add the corresponding linked list element BEFORE
	*  the AllocatedHead. This is equivalent to inserting a linked list element
	*  after the head of the list.
	*
	* @returns {FJsResourceContainer} ResourceContainerType	Allocated ResourceType wrapped in a container.
	*/
	/*FJsResourceContainer*/ AllocateBeforeHead()
	{
		if (IsValidObject(this.AllocatedHead))
			return this.AllocateBefore(this.AllocatedHead.Element);
		return this.Allocate();
	}

	/**
	* @param {string} 		context 
	* @param {number} 		index		int
	* @returns {boolean}
	*/
	/*boolean*/ IsAllocatedChecked(context /*string*/, index /*number*/)
	{
		return this.GetAtChecked(context, index).IsAllocated();
	}

	/**
	* @param {number} 		index		int
	* @returns {boolean}
	*/
	/*boolean*/ IsAllocated(index /*number*/)
	{
		return this.GetAt(index).IsAllocated();
	}

	// #endregion Allocate

	// Deallocate
	// #region Deallocate
	// public:

	/**
	* Deallocate a ResourceType and remove the corresponding linked list element from the
	*  allocated linked list.
	*
	* @param {FJsResourceContainer} resourceContainer	Container for a ResourceType to deallocate.
	* @returns {boolean} 			Success				Whether the Deallocate performed successfully or not.
	*/
	/*boolean*/ Deallocate(resourceContainer /*FJsResourceContainer*/)
	{
		checkf(IsValidObject(resourceContainer), this.Name + ".Deallocate: ResourceContainer is NULL.");

		if (!resourceContainer.IsAllocated())
			return false;

		checkf(IsValidObject(resourceContainer.Get()), this.Name + ".Deallocate: Resource is NULL.");

		let index = resourceContainer.GetIndex();

		checkf(index >= 0 && index < this.PoolSize, this.Name + ".Deallocate: index: " + index + " (< 0 or >= " + this.PoolIndex + ") of Resource Container is NOT Valid.");

		let m = this.Pool[index];

		checkf(m === resourceContainer, this.Name + ".Deallocate: Resource is NOT contained in Pool.");

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
	* @param {any}			resource	ResourceType to deallocate.
	* @returns {boolean} 	Success		Whether the Deallocate performed successfully or not.
	*/
	/*boolean*/ DeallocateByResource(resource /*any*/)
	{
		checkf(IsValidObject(resource), this.Name + ".Deallocate: Resource is NULL.");

		let resourceContainer = this.GetAllocatedContainer(resource);

		return this.Deallocate(resourceContainer);
	}

	/**
	* Deallocate a ResourceType and remove the corresponding linked list element from the
	*  allocated linked list.
	*
	* @param {number} 		index		Index of the ResourceType to deallocate
	* @returns {boolean} 	Success
	*/
	/*boolean*/ DeallocateAtByIndex(index /*number*/)
	{
		checkf(index >= 0 && index < this.PoolSize, this.Name + ".DeallocateAt: index: " + index + " (< 0 or >= " + this.PoolSize + ") is NOT Valid.");

		let m = this.Pool[index];

		if (!m.IsAllocated())
			return false;

		checkf(IsValidObject(m.Get()), this.Name + ".DeallocateAt: Resource is NULL.");

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
	* @param {any} 		resource	ResourceType to deallocate.
	* @param {number} 	index		Index of the ResourceType to deallocate
	* @return {boolean} Success
	*/
	/*boolean*/ DeallocateAt(resource /*any*/, index /*number*/)
	{
		checkf(IsValidObject(resource), this.Name + ".Deallocate: resource is NULL.");
		checkf(index >= 0 && index < this.PoolSize, this.Name + ".DeallocateAt: index: " + index + " (< 0 or >= " + this.PoolSize + ") is NOT Valid.");

		let m = this.Pool[index];

		if (!m.IsAllocated())
			return false;

		checkf(IsValidObject(m.Get()), this.Name + ".DeallocateAt: resource is NULL.");
		checkf(resource === m.Get(), this.Name + ".DeallocateAt: resource at index: " + this.index + " is NOT contained in Pool.");

		m.Deallocate();
		this.RemoveActiveLink(this.Links[index]);
		this.AllocationOrder.Promote(index);
		--this.AllocatedSize;
		return true;
	}

	/**
	*
	*
	* @returns {boolean}
	*/
	/*boolean*/ DeallocateHead()
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
			next	= current.GetNextLink()

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
	* @returns {FJsResourceContainer} ResourceContainerType
	*/
	/*FJsResourceContainer*/ Enqueue() { return this.Allocate(); }

	/**
	* Deallocate the current head of the list of allocated ResourceContainerTypes.
	*  This is equivalent to called Deallocate on the AllocatedHead.
	*
	* @returns {FJsResourceContainer} ResourceContainerType
	*/
	/*FJsResourceContainer*/ Dequeue()
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
	* @returns {FJsResourceContainer} ResourceContainerType
	*/
	/*FJsResourceContainer*/ Push() { return this.AllocateAfterHead(); }

	/**
	* Deallocate the head of the list of allocated ResourceContainerTypes. 
	*  This is equivalent to calling Deallocate() on the AllocatedHead.
	*
	* @returns {FJsResourceContainer} ResourceContainerType
	*/
	/*FJsResourceContainer*/ Pop()
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
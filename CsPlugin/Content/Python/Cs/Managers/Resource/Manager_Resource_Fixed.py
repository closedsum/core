# Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
# MIT License: https://opensource.org/license/mit/
# Free for use and distribution: https://github.com/closedsum/core
from typing import TypeVar, Generic, Type

# IMPORT

# Library
# - Cs/Library/Library_Common.py
import Cs.Library.Library_Common as Cs_Library_Common
# Resource
# - Cs/Managers/Resource/ResourceContainer.py
import Cs.Managers.Resource.ResourceContainer as Cs_ResourceContainer
# Utility
# - Cs/Utility/AllocationOrder.py
import Cs.Utility.AllocationOrder as Cs_AllocationOrder
# Containers
# - Cs/Containers/DoubleLinkedListNode.py
import Cs.Containers.DoubleLinkedListNode as Cs_DoubleLinkedListNode

# "typedefs" - library (py)
CommonLibrary = Cs_Library_Common.NPyCommon.FLibrary

# "typedefs" - types
FPyResourceContainer = Cs_ResourceContainer.FPyResourceContainer
FPyAllocationOrder = Cs_AllocationOrder.FPyAllocationOrder
FPyDoubleLinkedListNode = Cs_DoubleLinkedListNode.FPyDoubleLinkedListNode

# "typedefs" - functions
check			= CommonLibrary.check
checkf 			= CommonLibrary.checkf
IsValidObject 	= CommonLibrary.IsValidObject
IsIntChecked	= CommonLibrary.IsIntChecked
IsIntChecked2	= CommonLibrary.IsIntChecked2

INDEX_NONE = -1

T = TypeVar('T')

class FPyManager_Resource_Fixed(Generic[T]):
	def __init__(self):
		self.Name: str = "FPyManager_Resource_Fixed"

		self.ResourceContainers: list[FPyResourceContainer[T]] = []
		self.Resources: list[T] = []
		self.Pool: list[FPyResourceContainer[T]] = []
		
		self.PoolSize: int = 0
		self.PoolSizeMinusOne: int = 0
		self.PoolIndex: int = 0
		
		self.AdvancePoolIndex: any = self.AdvancePoolIndexByOrder
		
		self.Links: list[FPyDoubleLinkedListNode[FPyResourceContainer[T]]] = []
		self.AllocatedHead: FPyDoubleLinkedListNode[FPyResourceContainer[T]] = None
		self.AllocatedTail: FPyDoubleLinkedListNode[FPyResourceContainer[T]] = None
		self.AllocatedSize: int = 0
		
		self.AllocationOrder: FPyAllocationOrder = FPyAllocationOrder()

    # public
	def Clear(self):
		pass
	
	def Shutdown(self):
		self.Clear()

        # Pool
		self.Pool = []
		self.PoolSize = 0
		self.PoolSizeMinusOne = 0
		self.PoolIndex = 0
		
		self.Resources = []

        # Links
		self.Links = []
		self.AllocatedHead = None
		self.AllocatedTail = None
		self.AllocatedSize = 0
		
		self.AllocationOrder.Shutdown()
		
		self.ResourceContainers = []

	# Pool
	#region Pool
    # public
	def CreatePool(self, size: int, resourceClassType: Type[T]):
		context: str = __class__.CreatePool.__qualname__

		checkf(type(size) is int, f"{context}: size is NOT an Integer.")
		checkf(size > 0, f"{context}: size: {size} is NOT > 0.")
		
		self.Shutdown()

        # Make PoolSize a power of 2.
		self.PoolSize = size
		self.PoolSize -= 1
		self.PoolSize |= self.PoolSize >> 1
		self.PoolSize |= self.PoolSize >> 2
		self.PoolSize |= self.PoolSize >> 4
		self.PoolSize |= self.PoolSize >> 8
		self.PoolSize |= self.PoolSize >> 16
		self.PoolSize += 1
		
		self.PoolSizeMinusOne = self.PoolSize - 1
		
		self.ResourceContainers = [None] * self.PoolSize
		self.Resources          = [None] * self.PoolSize
		
		for i in range(0, self.PoolSize):
			self.ResourceContainers[i] = FPyResourceContainer[T]()
			self.Resources[i] = resourceClassType()
			
		self.Pool  = [None] * self.PoolSize
		self.Links = [None] * self.PoolSize
		
		for i in range(0, self.PoolSize):
			self.Links[i] = FPyDoubleLinkedListNode[FPyResourceContainer[T]]()
			
		self.AllocationOrder.Create(self.PoolSize)
		
		for i in range(0, self.PoolSize):
			m: FPyResourceContainer[T] = self.ResourceContainers[i]
			m.SetIndex(i)
			r: T = self.Resources[i]
			m.Set(r)
			self.Pool[i] = m

            # Set Element for Link
			link: FPyDoubleLinkedListNode[FPyResourceContainer[T]] = self.Links[i]
			link.Element = m

	def GetPool(self) -> list[FPyResourceContainer[T]]:
		"""
		Get a reference to the Pool.

		:return list[FPyResourceContainer[T]]:
		""" 
		return self.Pool
	def GetPoolSize(self) -> int:
		"""
		Get the number of elements in the pool.

		:return int: Pool Size
		"""
		return self.PoolSize
	def GetAllocatedSize(self) -> int:
		"""
		Get the number of allocated elements.

		:return int: Allocated Size.
		"""
		return self.AllocatedSize
	def IsExhausted(self) -> bool:
		"""
		Check if all the resources have been allocated.

		:return bool: Whether all resources have been allocated.
		"""
		return self.PoolSize == self.AllocatedSize
	
	def AdvancePoolIndexByIncrement(self):
		self.PoolIndex = (self.PoolIndex + 1) & self.PoolSizeMinusOne

	def AdvancePoolIndexByOrder(self):
		self.PoolIndex = self.AllocationOrder.Advance()
		
	def GetAt(self, index: int) -> FPyResourceContainer[T]:
		check(IsIntChecked2(index))
		checkf((index > INDEX_NONE) and (index < self.PoolSize), f"{self.Name}.GetAt: Index: {index} is NOT >= 0 and < PoolSize: {self.PoolSize}")
		return self.Pool[index]

	def GetAtChecked(self, context: str, index: int) -> FPyResourceContainer[T]:
		check(IsIntChecked(context, index))
		checkf((index > INDEX_NONE) and (index < self.PoolSize), f"{context}: Index: {index} is NOT >= 0 and < PoolSize: {self.PoolSize}")
		return self.Pool[index]
	
	def GetResourceAt(self, index: int) -> T:
		check(IsIntChecked2(index))
		checkf((index > INDEX_NONE) and (index < self.PoolSize), f"{self.Name}.GetResourceAt: Index: {index} is NOT >= 0 and < PoolSize: {self.PoolSize}")
		return self.Pool[index].Get()

	def GetAllocatedContainer(self, resource: T) -> FPyResourceContainer[T]:
		"""
		Get the FPyResourceContainer[T] associated with the resource.

		Args:
			resource (T): Resource to find the associated container for.

		Returns:
			FPyResourceContainer[T]
		"""
		checkf(IsValidObject(resource), f"{self.Name}.GetAllocatedContainer: Resource is NULL.")

		current: FPyDoubleLinkedListNode[FPyResourceContainer[T]] = self.AllocatedHead
		next: FPyDoubleLinkedListNode[FPyResourceContainer[T]]    = current

		while next != None:
			current 				   = next
			m: FPyResourceContainer[T] = current.Element
			next					   = current.GetNextLink()

			r: T = m.Get()
			
			if r == resource:
				return m
		return None

	#endregion Pool

	# Linked List
	#region Linked List
    # private

	def AddAllocatedLink(self, link: FPyDoubleLinkedListNode[FPyResourceContainer[T]]):
		"""
		Add a link, LinkedList pointer to a FPyResourceContainer, to the end, AllocatedTail,
		 of the allocated linked list, list of Resources that have been allocated.

		:param FPyDoubleLinkedListNode[FPyResourceContainer[T]] link: Pointer to LinkedList element containing a FPyResourceContainer.
		"""
		if IsValidObject(self.AllocatedTail) == True:
			link.LinkAfter(self.AllocatedTail)
			self.AllocatedTail = link
		else:
			self.AllocatedHead = link
			self.AllocatedTail = self.AllocatedHead

	def AddAllocatedLinkAfter(self, link: FPyDoubleLinkedListNode[FPyResourceContainer[T]], resourceContainer: FPyResourceContainer[T]):
		"""
		Add a link, LinkedList pointer to a ResourceContainerTytpe, after the ResourceContainer
		 in the active linked list, list of ResourceTypes that have been allocated.
		 This is equivalent to inserting a linked list element after another element.

		:param FPyDoubleLinkedListNode[FPyResourceContainer[T]] link: 			Pointer to LinkedList element containing a FPyResourceContainer.
		:param FPyResourceContainer[T] resourceContainer: Container for a ResourceType
		"""
		# Resource to Link After
		linkAfterIndex: int = resourceContainer.GetIndex()

		linkAfter: FPyDoubleLinkedListNode[FPyResourceContainer[T]] = self.Links[linkAfterIndex]

		# Make Resource (Link) LinkAfter the link for ResourceContainer (LinkAfter)
		link.LinkAfter(linkAfter)

		if linkAfter == self.AllocatedTail:
			self.AllocatedTail = link

	def AddAllocatedLinkBefore(self, link: FPyDoubleLinkedListNode[FPyResourceContainer[T]], resourceContainer: FPyResourceContainer[T]):
		"""
		Add a link, LinkedList pointer to a ResourceContainerTytpe, before the ResourceContainer
		 in the allocated linked list, list of ResourceTypes that have been allocated.
		 This is equivalent to inserting a linked list element before another element.

		:param FPyDoubleLinkedListNode[FPyResourceContainer[T]] link: 			Pointer to LinkedList element containing a FPyResourceContainer.
		:param FPyResourceContainer[T] resourceContainer: Container for a ResourceType
		"""
		# Resource to Link Before
		linkBeforeIndex: int = resourceContainer.GetIndex()

		linkBefore: FPyDoubleLinkedListNode[FPyResourceContainer[T]] = self.Links[linkBeforeIndex]

		# Make Resource (Link) LinkBefore the link for ResourceContainer (LinkBefore)
		link.LinkBefore(linkBefore)

		if linkBefore == self.AllocatedHead:
			self.AllocatedHead = link

	def RemoveActiveLink(self, link: FPyDoubleLinkedListNode[FPyResourceContainer[T]]):
		"""
		Remove a link, LinkedList pointer to a FPyResourceContainer, from the allocated linked
		 list, list of ResourceTypes that have been allocated.

		:param FPyDoubleLinkedListNode[FPyResourceContainer[T]] link: 			Pointer to LinkedList element containing a FPyResourceContainer.
		"""
		# Check to Update HEAD
		if link == self.AllocatedHead:
			self.AllocatedHead = link.GetNextLink()

			if IsValidObject(self.AllocatedHead) == False:
				self.AllocatedTail = None
		# Check to Update TAIL
		elif link == self.AllocatedTail:
			self.AllocatedTail = link.GetPrevLink()
		link.Unlink()

   # public

	def GetAllocatedHead(self) -> FPyDoubleLinkedListNode[FPyResourceContainer[T]]:
		"""
		Get the current head of the allocated linked list.

		:return FPyDoubleLinkedListNode[FPyResourceContainer[T]]:
		"""
		return self.AllocatedHead
	def GetAllocatedTail(self) -> FPyDoubleLinkedListNode[FPyResourceContainer[T]]:
		"""
		Get the current tail of the active linked list.

		:return FPyDoubleLinkedListNode[FPyResourceContainer[T]]:
		"""
		return self.AllocatedTail

	#endregion Linked List

	# Allocate
	#region Allocate
	# public

	def Allocate(self) -> FPyResourceContainer[T]:
		"""
		Allocate a ResourceType and add the corresponding linked list element to the 
		 end of the list

		:return FPyResourceContainer[T]:
		"""
		checkf(self.IsExhausted() == False, f"{self.Name}.Allocate: Pool is exhausted.")

		for i in range(0, self.PoolSize):
			self.AdvancePoolIndex()

			m: FPyResourceContainer[T] = self.Pool[self.PoolIndex]

			if m.IsAllocated() == False:
				checkf(IsValidObject(m.Get()), f"{self.Name}.Allocate: Resource is NULL. Container {self.PoolIndex} no longer holds a reference to a resource.")

				m.Allocate()
				self.AddAllocatedLink(self.Links[self.PoolIndex])
				self.AllocatedSize += 1
				return m
		checkf(False, f"{self.Name}.Allocate: Pool is exhausted.")
		return None

	def AllocateResource(self) -> T:
		"""
		Allocate a ResourceType and add the corresponding linked list element to the
		 end of the list

		:return T ResourceType:	Allocated ResourceType
		"""
		return self.Allocate().Get()
	
	def AllocateAfter(self, resourceContainer: FPyResourceContainer[T]) -> FPyResourceContainer[T]:
		"""
		Allocate a ResourceType and add the corresponding linked list element after
		 another FPyResourceContainer. This is equivalent to inserting a linked list element
		 after another element. 

		:param FPyResourceContainer[T]	resourceContainer:	Container for a ResourceType.
		:return FPyResourceContainer[T] ResourceType:		Allocated ResourceType wrapped in a container.
		"""
		checkf(IsValidObject(resourceContainer), f"{self.Name}.AllocateAfter: resourceContainer is NULL.")
		checkf(resourceContainer.IsAllocated(), f"{self.Name}.AllocateAfter: ResourceContainer must be Allocated.")
		checkf(self.IsExhausted() == False, f"{self.Name}.AllocateAfter: Pool is exhausted.")

		# New Resource
		r: FPyResourceContainer[T]	 	  = None
		link: FPyDoubleLinkedListNode[FPyResourceContainer[T]] = None
		
		for i in range(0, self.PoolSize):
			self.PoolIndex 			= (self.PoolIndex + 1) & self.PoolSizeMinusOne
			m: FPyResourceContainer[T]	= self.Pool[self.PoolIndex]

			if m.IsAllocated() == False:
				checkf(IsValidObject(m.Get()), f"{self.Name}.AllocateAfter: Resource is NULL. Container {self.PoolIndex} no longer holds a reference to a resource.")

				m.Allocate()
				r    = m
				link = self.Links[self.PoolIndex]
				break

		checkf(IsValidObject(r), f"{self.Name}.AllocateAfter: Pool is exhausted.")

		self.AddAllocatedLinkAfter(link, resourceContainer)
		self.AllocatedSize += 1
		return r
	
	def AllocateAfterHead(self) -> FPyResourceContainer[T]:
		"""
		Allocate a ResourceType and add the corresponding linked list element AFTER
		 the AllocatedHead. This is equivalent to inserting a linked list element
		 after the head of the list.

		:return FPyResourceContainer[T] ResourceContainerType:	Allocated ResourceType wrapped in a container.
		"""
		if IsValidObject(self.AllocatedHead) == True:
			return self.AllocateAfter(self.AllocatedHead.Element)
		return self.Allocate()

	def AllocateBefore(self, resourceContainer: FPyResourceContainer[T]) -> FPyResourceContainer[T]:
		"""
		Allocate a ResourceType and add the corresponding linked list element before
		 another FPyResourceContainer. This is equivalent to inserting a linked list element
		 before another element.

		:param FPyResourceContainer[T] resourceContainer:		Container for a ResourceType.
		:return FPyResourceContainer[T] resourceContainerType:	Allocated ResourceType wrapped in a container.
		"""
		checkf(IsValidObject(resourceContainer), f"{self.Name}.AllocateBefore: ResourceContainer is NULL.")
		checkf(resourceContainer.IsAllocated(), f"{self.Name}.AllocateBefore: ResourceContainer must be Allocated.")
		checkf(self.IsExhausted() == False, f"{self.Name}.AllocateBefore: Pool is exhausted.")

		# New Resource
		r: FPyResourceContainer[T]	 	  = None
		link: FPyDoubleLinkedListNode[FPyResourceContainer[T]] = None
		
		for i in range(0, self.PoolSize):
			self.PoolIndex 			= (self.PoolIndex + 1) & self.PoolSizeMinusOne
			m: FPyResourceContainer[T]	= self.Pool[self.PoolIndex]

			if m.IsAllocated() == False:
				checkf(IsValidObject(m.Get()), f"{self.Name}.AllocateBefore: Resource is NULL. Container {self.PoolIndex} no longer holds a reference to a resource.")

				m.Allocate()
				r    = m
				link = self.Links[self.PoolIndex]
				break

		checkf(IsValidObject(r), f"{self.Name}.AllocateBefore: Pool is exhausted.")

		self.AddAllocatedLinkBefore(link, resourceContainer)
		self.AllocatedSize += 1
		return r

	def AllocateBeforeHead(self) -> FPyResourceContainer[T]:
		"""
		Allocate a ResourceType and add the corresponding linked list element BEFORE
		 the AllocatedHead. This is equivalent to inserting a linked list element
		 after the head of the list.

		:return FPyResourceContainer[T] resourceContainerType:	Allocated ResourceType wrapped in a container.
		"""
		if IsValidObject(self.AllocatedHead) == True:
			return self.AllocateBefore(self.AllocatedHead.Element)
		return self.Allocate()

	def IsAllocatedChecked(self, context: str, index: int) -> bool:
		return self.GetAtChecked(context, index).IsAllocated()

	def IsAllocated(self, index: int) -> bool:
		return self.GetAt(index).IsAllocated()

	#endregion Allocate

	# Deallocate
	#region Deallocate
	# public:

	def Deallocate(self, resourceContainer: FPyResourceContainer[T]) -> bool:
		"""
		Deallocate a ResourceType and remove the corresponding linked list element from the
		 allocated linked list.

		:param FPyResourceContainer[T] resourceContainer:	Container for a ResourceType to deallocate.
		:return bool success:							Whether the Deallocate performed successfully or not.
		"""
		checkf(IsValidObject(resourceContainer), f"{self.Name}.Deallocate: ResourceContainer is NULL.")

		if resourceContainer.IsAllocated() == False:
			return False

		checkf(IsValidObject(resourceContainer.Get()), f"{self.Name}.Deallocate: Resource is NULL.")

		index: int = resourceContainer.GetIndex()

		checkf((index >= 0) and (index < self.PoolSize), f"{self.Name}.Deallocate: index: {index} (< 0 or >= {self.PoolIndex}) of Resource Container is NOT Valid.")

		m: FPyResourceContainer[T] = self.Pool[index]

		checkf(m == resourceContainer, f"{self.Name}.Deallocate: Resource is NOT contained in Pool.")

		m.Deallocate();
		self.RemoveActiveLink(self.Links[index])
		self.AllocationOrder.Promote(index)
		self.AllocatedSize -= 1
		return True

	def DeallocateByResource(self, resource: T) -> bool:
		"""
		Deallocate a ResourceType and remove the corresponding linked list element from the
		 allocated linked list.

		:param T resource:	ResourceType to deallocate.
		:return bool success:	Whether the Deallocate performed successfully or not.
		"""
		checkf(IsValidObject(resource), f"{self.Name}.Deallocate: Resource is NULL.")

		resourceContainer: FPyResourceContainer[T] = self.GetAllocatedContainer(resource)

		return self.Deallocate(resourceContainer)

	def DeallocateAtByIndex(self, index: int) -> bool:
		"""
		Deallocate a ResourceType and remove the corresponding linked list element from the
		 allocated linked list.

		:param int index:		Index of the ResourceType to deallocate
		:return bool success:	Whether the Deallocate performed successfully or not.
		"""
		check(IsIntChecked2(index))
		checkf((index >= 0) and (index < self.PoolSize), f"{self.Name}.DeallocateAt: index: {index} (< 0 or >= {self.PoolSize}) is NOT Valid.")

		m: FPyResourceContainer[T] = self.Pool[index]

		if m.IsAllocated() == False:
			return False

		checkf(IsValidObject(m.Get()), f"{self.Name}.DeallocateAt: Resource is NULL.")

		m.Deallocate();
		self.RemoveActiveLink(self.Links[index])
		self.AllocationOrder.Promote(index)
		self.AllocatedSize -= 1
		return True

	def DeallocateAt(self, resource: T, index: int) -> bool:
		"""
		Deallocate a ResourceType and remove the corresponding linked list element from the
		 allocated linked list.s

		:param T resource: 	ResourceType to deallocate.
		:param int index:		Index of the ResourceType to deallocate
		:return bool success:	Whether the Deallocate performed successfully or not.
		"""
		checkf(IsValidObject(resource), f"{self.Name}.Deallocate: resource is NULL.")
		check(IsIntChecked2(index))
		checkf((index >= 0) and (index < self.PoolSize), f"{self.Name}.DeallocateAt: index: {index} (< 0 or >= {self.PoolSize}) is NOT Valid.")

		m: FPyResourceContainer[T] = self.Pool[index]

		if m.IsAllocated() == False:
			return False

		checkf(IsValidObject(m.Get()), f"{self.Name}.DeallocateAt: resource is NULL.")
		checkf(resource == m.Get(), f"{self.Name}.DeallocateAt: resource at index: {index} is NOT contained in Pool.")

		m.Deallocate()
		self.RemoveActiveLink(self.Links[index])
		self.AllocationOrder.Promote(index)
		self.AllocatedSize -= 1
		return True

	def DeallocateHead(self) -> bool:
		if self.AllocatedHead == None:
			return False
		return self.Deallocate(self.AllocatedHead.Element)

	def DeallocateAll(self):
		current: FPyDoubleLinkedListNode[FPyResourceContainer[T]] = self.AllocatedHead
		next: FPyDoubleLinkedListNode[FPyResourceContainer[T]]	 = current

		while next != None:
			current					= next
			m: FPyResourceContainer[T]	= current.Element
			next					= current.GetNextLink()

			index: int = m.GetIndex()

			m.Deallocate()
			self.RemoveActiveLink(self.Links[index])
			self.AllocatedSize -= 1
		self.AllocationOrder.Reset()

	#endregion Deallocate

	# Queue
	#region Queue
	# public:

	def Enqueue(self) -> FPyResourceContainer[T]:
		"""
		Allocate and add the element to end of the list of allocated
		 ResourceContainerTypes. This is equivalent to calling Allocate().

		:return FPyResourceContainer[T] resourceContainerType:
		"""
		return self.Allocate()

	def Dequeue(self) -> FPyResourceContainer[T]:
		"""
		Deallocate the current head of the list of allocated ResourceContainerTypes.
		 This is equivalent to called Deallocate on the AllocatedHead.

		:return FPyResourceContainer[T] resourceContainerType:
		"""
		if IsValidObject(self.AllocatedHead) == True:
			if self.Deallocate(self.AllocatedHead.Element) == True:
				return self.AllocatedHead.Element
		return None

	# #endregion Queue

	# Stack
	#region Stack
	# public:

	def Push(self) -> FPyResourceContainer[T]:
		"""
		Allocate and add the element AFTER the head of the list of allocated 
		 ResourceContainerTypes. This is equivalent to calling AllocateAfterHead().

		:return FPyResourceContainer[T] resourceContainerType:
		"""
		return self.AllocateAfterHead()

	def Pop(self) -> FPyResourceContainer[T]:
		"""
		Deallocate the head of the list of allocated ResourceContainerTypes. 
		 This is equivalent to calling Deallocate() on the AllocatedHead.

		:return FPyResourceContainer[T] resourceContainerType:
		"""
		if IsValidObject(self.AllocatedHead) == True:
			if self.Deallocate(self.AllocatedHead.Element) == True:
				return self.AllocatedHead.Element
		return None
	
	#endregion Stack
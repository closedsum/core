// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Types/CsTypes_Macro.h"
// Resource
#include "Managers/Resource/CsManager_Resource.h"
#include "Managers/Resource/CsResourceContainer.h"
// Utility
#include "Utility/CsAllocationOrder.h"

namespace NCsResource
{
	namespace NManager
	{
		namespace NValue
		{
			namespace NAbstract
			{
				template<typename ResourceType, typename ResourceContainerType = TCsResourceContainer<ResourceType>, uint32 BUCKET_SIZE = 128>
				class TFixed : public NCsResource::NManager::IManager
				{
					static_assert(std::is_base_of<TCsResourceContainer<ResourceType>, ResourceContainerType>(), "NCsResource::NManager::NValue::NAbstract::TFixed: ResourceContainerType does NOT implement interface: ICsResourceContainer.");

					static_assert(std::is_abstract<ResourceType>(), "NCsResource::NManager::NValue::NAbstract::TFixed: ResourceType must be Abstract.");
	
				public:

					TFixed() :
						Name(),
						Name_Internal(),
						ResourceContainers(),
						Resources(),
						Pool(),
						PoolSize(0),
						PoolSizeMinusOne(0),
						PoolIndex(0),
						AdvancePoolIndex(),
						Links(),
						AllocatedHead(nullptr),
						AllocatedTail(nullptr),
						AllocatedSize(0),
						AllocationOrder(),
						ConstructResourceType_Impl()
					{
						Name		  = TEXT("NCsResource::NManager::NValue::NAbstract::TFixed");
						Name_Internal = FName(*Name);

						AdvancePoolIndex = &TFixed<ResourceType, ResourceContainerType, BUCKET_SIZE>::AdvancePoolIndexByOrder;

						if (BUCKET_SIZE > 0)
							CreatePool(BUCKET_SIZE);
					}

					virtual ~TFixed()
					{
						Shutdown();
					}

				private:

					/** String Name of the Manager */
					FString Name;
					/** FName of the Manager */
					FName Name_Internal;

					/** List of ResourceContainerTypes */
					TArray<ResourceContainerType> ResourceContainers;
					/** List of ResourceTypes */
					TArray<ResourceType*> Resources;
					/** List of references to ResourceContainerTypes. These references map one to one with
						the elements in ResourceContainers. */
					TArray<ResourceContainerType*> Pool;

					/** Size of the pool */
					int32 PoolSize;
					/** One minus size of the pool. This is cached for ease of use. */
					int32 PoolSizeMinusOne;
					/** Index of the last allocated ResourceContainerType in Pool. */
					uint32 PoolIndex;

					/** Function pointer to "advance" / choose the next Index used to allocate from the Pool. */
					void (NCsResource::NManager::NValue::NAbstract::TFixed<ResourceType, ResourceContainerType, BUCKET_SIZE>::* AdvancePoolIndex)();

					/** List of LinkedList elements storing references to ResourceContainerTypes */
					TArray<TCsDoubleLinkedList<ResourceContainerType*>> Links;

					/** Current head of the linked list of allocated ResourceContainerTypes */
					TCsDoubleLinkedList<ResourceContainerType*>* AllocatedHead;
					/** Current tail of the linked list of allocated ResourceContainerTypes */
					TCsDoubleLinkedList<ResourceContainerType*>* AllocatedTail;
					/** The current number of allocated ResourceContainerTypes */
					int32 AllocatedSize;

					FCsAllocationOrder AllocationOrder;

				public:

					/**
					*
					*
					* return
					*/
					FORCEINLINE const FString& GetName() const
					{
						return  Name;
					}

					/**
					* Set the name of the Manager.
					*  Default value is NCsResource::NManager::NValue::NAbstract::TFixed.
					*
					* @param InName		Name to set for the Manager.
					*/
					void SetName(const FString& InName)
					{
						Name		  = InName;
						Name_Internal = FName(*Name);
					}

					/**
					*
					*
					* return
					*/
					FORCEINLINE const FName& GetFName() const 
					{
						return Name_Internal;
					}

					/**
					* Set the name of the Manager.
					*  Default value is NCsResource::NManager::NValue::NAbstract::TFixed.
					*
					* @param InName		Name to set for the Manager.
					*/
					void SetFName(const FName& InName)
					{
						Name_Internal = InName;
						Name		  = Name_Internal.ToString();
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
						// Resources
						{
							for (int32 I = 0; I < PoolSize; ++I)
							{
								ResourceType* R = Resources[I];
								delete R;
								Resources[I] = nullptr;
							}
							Resources.Reset();
						}
						// Links
						{
							for (TCsDoubleLinkedList<ResourceContainerType*>& Link : Links)
							{
								(*Link) = nullptr;
							}
							Links.Reset();
						}

						PoolSize = 0;
						PoolSizeMinusOne = 0;
						PoolIndex = 0;

						AllocatedHead = nullptr;
						AllocatedTail = nullptr;
						AllocatedSize = 0;

						AllocationOrder.Shutdown();

						ResourceContainers.Reset();
					}

				// Pool
				#pragma region
				public:

					/**
					*
					*
					* return Resource
					*/
					TDelegate<ResourceType* /*Resource*/()> ConstructResourceType_Impl;

					/**
					* Creates a pool of resource containers and resources of size PoolSize.
					*
					* @param InSize		Size of the pool.
					*/
					void CreatePool(const int32& InSize)
					{
						Shutdown();

						// Make PoolSize a power of 2.
						PoolSize = InSize;
						--PoolSize;
						PoolSize |= PoolSize >> 1;
						PoolSize |= PoolSize >> 2;
						PoolSize |= PoolSize >> 4;
						PoolSize |= PoolSize >> 8;
						PoolSize |= PoolSize >> 16;
						++PoolSize;

						PoolSizeMinusOne = PoolSize - 1;

						ResourceContainers.Reset(PoolSize);
						ResourceContainers.AddDefaulted(PoolSize);

						Resources.Reset(PoolSize);

						Pool.Reset(PoolSize);

						Links.Reset(PoolSize);
						Links.AddDefaulted(PoolSize);

						AllocationOrder.Create(PoolSize);

						for (int32 I = 0; I < PoolSize; ++I)
						{
							ResourceContainerType* M = &(ResourceContainers[I]);
							M->SetIndex(I);

							checkf(ConstructResourceType_Impl.IsBound(), TEXT("%s::CreatePool: ConstructResourceType_Impl is NOT Bound."), *Name);

							ResourceType* R = ConstructResourceType_Impl.Execute();

							checkf(R, TEXT("%s::CreatePool: Failed to Construct ResourceType."), *Name);

							M->Set(R);
							Pool.Add(M);
							Resources.Add(R);

							// Set Element for Link
							TCsDoubleLinkedList<ResourceContainerType*>& Link = Links[I];
							(*Link) = M;
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
					* Get the number of elements in the pool.
					* 
					* return Pool Size
					*/
					FORCEINLINE const int32& GetPoolSize() const
					{
						return PoolSize;
					}

					/**
					* Get the number of allocated elements.
					*
					* return Allocated Size.
					*/
					FORCEINLINE const int32& GetAllocatedSize() const
					{
						return AllocatedSize;
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

					FORCEINLINE void AdvancePoolIndexByIncrement() { PoolIndex = (PoolIndex + 1) & PoolSizeMinusOne; }

					FORCEINLINE void AdvancePoolIndexByOrder() { PoolIndex = AllocationOrder.Advance(); }

					/**
					* Get the container of type: ResourceContainerType holding a 
					* resource of type: ResourceType at the specified Index.
					*
					* @param Index	Index of the container to get.
					* return		Resource Container of type: ResourceContainerType
					*/
					FORCEINLINE ResourceContainerType* GetAt(const int32& Index) const
					{
						checkf(Index > INDEX_NONE && Index < PoolSize, TEXT("%s::GetAt: Index is >= 0 and < PoolSize: %d"), *Name, PoolSize);

						return Pool[Index];
					}

					/**
					* Get the resource of type: ResourceType at the specified Index.
					*
					* @param Index	Index of the resource to get.		
					* return		ResourceType
					*/
					FORCEINLINE ResourceType* GetResourceAt(const int32& Index) const
					{
						checkf(Index > INDEX_NONE && Index < PoolSize, TEXT("%s::GetResourceAt: Index is >= 0 and < PoolSize: %d"), *Name, PoolSize);

						return Pool[Index]->Get();
					}

					/**
					*
					* @param Resource	Resource to find the associated container for.
					* return			Resource Container associated with the Resource
					*/
					ResourceContainerType* GetContainer(ResourceType* Resource) const
					{
						checkf(Resource, TEXT("%s::GetContainer: Resource is NULL."), *Name);

						const int32 Count = Resources.Num();

						for (int32 I = 0; I < Count; ++I)
						{

							if (Resources[I] == Resource)
							{
								return Pool[I];
							}
						}
						return nullptr;
					}

					/**
					*
					* @param Resource	Resource to find the associated container for.
					* return			Resource Container associated with the Resource
					*/
					const ResourceContainerType* GetContainer(const ResourceType* Resource) const
					{
						checkf(Resource, TEXT("%s::GetContainer: Resource is NULL."), *Name);

						const int32 Count = Resources.Num();

						for (int32 I = 0; I < Count; ++I)
						{
			
							if (Resources[I] == Resource)
							{
								return Pool[I];
							}
						}
						return nullptr;
					}

					/**
					* Get the container that holds the Resource of type: ResourceType.
					* NOTE: This process is O(n). 
					* 
					* @param Resource	Resource to find the associated container for.
					* return			Resource Container associated with the Resource.
					*/
					ResourceContainerType* GetAllocatedContainer(ResourceType* Resource) const
					{
						checkf(Resource, TEXT("%s::GetAllocatedContainer: Resource is NULL."), *Name);

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

					/**
					* Get the container that holds the Resource of type: ResourceType.
					* NOTE: This process is O(n). 
					* 
					* @param Resource	Resource to find the associated container for.
					* return			Resource Container associated with the Resource.
					*/
					const ResourceContainerType* GetAllocatedContainer(const ResourceType* Resource) const
					{
						checkf(Resource, TEXT("%s::GetAllocatedContainer: Resource is NULL."), *Name);

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

					/**
					* Performs checks on ResourceContainer to see if it belongs to this manager.
					*
					* @param Context			Calling context.
					* @param ResourceContainer	Resource Container to perform checks on.
					*/
					bool IsValidChecked(const FString& Context, const ResourceContainerType* ResourceContainer) const
					{
						checkf(ResourceContainer, TEXT("%s: ResourceContainer is NULL."), *Context);

						checkf(ResourceContainer->Get(), TEXT("%s: Resource is NULL."), *Context);

						const int32& Index = ResourceContainer->GetIndex();

						checkf(Index >= 0 && Index < PoolSize, TEXT("%s: Index: %d (< 0 or >= %d) of Resource Container is NOT Valid."), *Context, Index, PoolSize);
		
						ResourceContainerType* M = Pool[Index];

						checkf(M == ResourceContainer, TEXT("%s: Resource is NOT contained in Pool."), *Name);

						return true;
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
					FORCEINLINE void AddAllocatedLink(TCsDoubleLinkedList<ResourceContainerType*>* Link)
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
					FORCEINLINE void AddAllocatedLinkAfter(TCsDoubleLinkedList<ResourceContainerType*>* Link, ResourceContainerType* ResourceContainer)
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
					FORCEINLINE void AddAllocatedLinkBefore(TCsDoubleLinkedList<ResourceContainerType*>* Link, ResourceContainerType* ResourceContainer)
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
					FORCEINLINE void RemoveActiveLink(TCsDoubleLinkedList<ResourceContainerType*>* Link)
					{
						// Check to Update HEAD
						if (Link == AllocatedHead)
						{
							AllocatedHead = Link->GetNextLink();

							if (!AllocatedHead)
							{
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
							//PoolIndex				 = (PoolIndex + 1) & PoolSizeMinusOne;
							((*this).*AdvancePoolIndex)();
			
							ResourceContainerType* M = Pool[PoolIndex];

							if (!M->IsAllocated())
							{
								checkf(M->Get(), TEXT("%s:Allocate: Resource is NULL. Container %d no longer holds a reference to a resource."), *Name, PoolIndex);

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
						ResourceContainerType* R				  = nullptr;
						TCsDoubleLinkedList<ResourceContainerType*>* Link = nullptr;
		
						for (int32 I = 0; I < PoolSize; ++I)
						{
							//PoolIndex				 = (PoolIndex + 1) & PoolSizeMinusOne;
							((*this).*AdvancePoolIndex)();

							ResourceContainerType* M = Pool[PoolIndex];

							if (!M->IsAllocated())
							{
								checkf(M->Get(), TEXT("%s:AllocateAfter: Resource is NULL. Container %d no longer holds a reference to a resource."), *Name, PoolIndex);

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
						ResourceContainerType* R				  = nullptr;
						TCsDoubleLinkedList<ResourceContainerType*>* Link = nullptr;
		
						for (int32 I = 0; I < PoolSize; ++I)
						{
							//PoolIndex				 = (PoolIndex + 1) & PoolSizeMinusOne;
							((*this).*AdvancePoolIndex)();

							ResourceContainerType* M = Pool[PoolIndex];

							if (!M->IsAllocated())
							{
								checkf(M->Get(), TEXT("%s:AllocateBefore: Resource is NULL. Container %d no longer holds a reference to a resource."), *Name, PoolIndex);

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
						AllocationOrder.Promote(Index);
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

						ResourceContainerType* ResourceContainer = GetAllocatedContainer(Resource);

						return Deallocate(ResourceContainer);
					}

					/**
					* Deallocate a ResourceType and remove the corresponding linked list element from the
					*  allocated linked list.
					*
					* @param Index		Index of the ResourceType to deallocate
					* return Success
					*/
					bool DeallocateAt(const int32& Index)
					{
						checkf(Index >= 0 && Index < PoolSize, TEXT("%s::DeallocateAt: Index: %d (< 0 or >= %d) is NOT Valid."), *Name, Index, PoolSize);

						ResourceContainerType* M = Pool[Index];

						if (!M->IsAllocated())
							return false;

						checkf(M->Get(), TEXT("%s::DeallocateAt: Resource is NULL."), *Name);

						M->Deallocate();
						RemoveActiveLink(&(Links[Index]));
						AllocationOrder.Promote(Index);
						--AllocatedSize;
						return true;
					}

					/**
					* Deallocate a ResourceType and remove the corresponding linked list element from the
					*  allocated linked list.
					*
					* @param Resource	ResourceType to deallocate.
					* @param Index		Index of the ResourceType to deallocate
					* return Success
					*/
					bool DeallocateAt(ResourceType* Resource, const int32& Index)
					{
						checkf(Resource, TEXT("%s::Deallocate: Resource is NULL."), *Name);

						checkf(Index >= 0 && Index < PoolSize, TEXT("%s::DeallocateAt: Index: %d (< 0 or >= %d) is NOT Valid."), *Name, Index, PoolSize);

						ResourceContainerType* M = Pool[Index];

						if (!M->IsAllocated())
							return false;

						checkf(M->Get(), TEXT("%s::DeallocateAt: Resource is NULL."), *Name);

						checkf(Resource == M->Get(), TEXT("%s::DeallocateAt: Resource at Index: %d is NOT contained in Pool."), *Name, Index);

						M->Deallocate();
						RemoveActiveLink(&(Links[Index]));
						AllocationOrder.Promote(Index);
						--AllocatedSize;
						return true;
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
							Current					 = Next;
							ResourceContainerType* M = **Current;
							Next					 = Current->GetNextLink();

							const int32& Index = M->GetIndex();

							M->Deallocate();
							RemoveActiveLink(&(Links[Index]));
							--AllocatedSize;
						}
						AllocationOrder.Reset();
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
			}
		}
	}
}
// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Managers/Pool/CsPooledObject.h"
#include "CsCVars.h"
#include "Containers/CsDoubleLinkedList.h"
#include "GameFramework/Actor.h"

// Structs
#pragma region

class UWorld;
class UObject;
class UClass;

struct CSCORE_API FCsManagerPooledObjectConstructParams
{
public:

	UClass* Class;

	FString ClassName;

	ECsPooledObjectConstruction ConstructionType;

	FActorSpawnParameters ConstructionInfo;

	bool bReplicates;

	FCsManagerPooledObjectConstructParams() :
		Class(nullptr),
		ClassName(),
		ConstructionType(ECsPooledObjectConstruction::Object),
		ConstructionInfo(),
		bReplicates(false)
	{
	}

	virtual ~FCsManagerPooledObjectConstructParams() {}
};

struct CSCORE_API FCsManagerPooledObjectParams
{
public:

	FString Name;

	UWorld* World;

	FECsCVarLog LogType;

	FCsManagerPooledObjectConstructParams ConstructParams;

	FCsManagerPooledObjectParams() :
		Name(),
		World(nullptr),
		LogType(),
		ConstructParams()
	{
	}

	virtual ~FCsManagerPooledObjectParams() {}
};

#pragma endregion Structs

// ICsManager_PooledObject
#pragma region


class CSCORE_API ICsManager_PooledObject
{
public:

	virtual ~ICsManager_PooledObject() {}

	virtual void Init(const FCsManagerPooledObjectParams& Params)  = 0;

	virtual void Clear() = 0;
	virtual void Shutdown() = 0;

	virtual UWorld* GetCurrentWorld() = 0;

	virtual float GetCurrentTimeSeconds() = 0;

// Pool
#pragma region
public:

	virtual void CreatePool(const int32& Size) = 0;

	virtual const int32& GetPoolSize() = 0;
	virtual int32 GetAllocatedObjectsSize() = 0;

	virtual bool IsExhausted() = 0;

#pragma endregion Pool

// Update
#pragma region
public:

	virtual void Update(const FCsDeltaTime& DeltaTime) = 0;

	//virtual FCsManagerPooledObject_OnUpdate_Object& GetOnUpdate_Object_Event() = 0;

#pragma endregion Update

// Payload
#pragma region
public:

	virtual void ConstructPayloads(const int32& Size) = 0;

	virtual void DeconstructPayloads() = 0;

#pragma endregion Payload

// Destroy
#pragma region
public:

	virtual bool Destroy(const int32& Index) = 0;
	virtual bool Destroy(UObject* Object) = 0;

#pragma endregion Destroy

// Script
#pragma region
public:

	virtual FCsPooledObject::FScript_GetCache& GetScript_GetCache_Impl() = 0;

	virtual FCsPooledObject::FScript_Allocate& GetScript_Allocate_Impl() = 0;

	virtual FCsPooledObject::FScript_Deallocate& GetScript_Deallocate_Impl() = 0;

	virtual FCsPooledObject::FScript_Update& GetScript_Update_Impl() = 0;

#pragma endregion Script
};

#pragma endregion ICsManager_PooledObject

// Enums
#pragma region

enum class ECsManagerPooledObjectFunctionNames : uint8
{
	Update,
	Deallocate,
	DeallocateAll,
	Spawn,
	ECsManagerPooledObjectFunctionNames_MAX,
};

#pragma endregion Enums

class UWorld;
class UObject;
class UClass;

template<typename InterfaceType, typename InterfaceContainerType, typename PayloadType>
class TCsManager_PooledObject_Abstract
{
	static_assert(std::is_abstract<InterfaceType>(), "TCsManager_PooledObject_Abstract: InterfaceType MUST be abstract.");

	// TODO: Check InterfaceType implements _getUObject
 
	static_assert(std::is_base_of<FCsPooledObject, InterfaceContainerType>(), "TCsManager_PooledObject_Abstract: InterfaceContainerType is NOT a child of: FCsPooledObject.");

	static_assert(std::is_abstract<PayloadType>(), "TCsManager_PooledObject_Abstract: PayloadType MUST be abstract.");

	static_assert(std::is_base_of<ICsGetInterfaceMap, PayloadType>(), "TCsManager_PooledObject_Abstract: PayloadType does NOT implement the interface: ICsGetInterfaceMap.");

public:
	TCsManager_PooledObject_Abstract()
	{
		Name = TEXT("TCsManager_PooledObject_Abstract");

		CurrentWorld = nullptr;

		OnAddToPool_Event.Clear();
		OnDeallocate_Event.Clear();

		Pool.Reset();
		PoolSize = 0;
		PoolIndex = 0;

		ConstructContainer_Impl.BindRaw(this, &TCsManager_PooledObject_Abstract<InterfaceType, InterfaceContainerType, PayloadType>::ConstructContainer);
		ConstructObject_Impl.BindRaw(this, &TCsManager_PooledObject_Abstract<InterfaceType, InterfaceContainerType, PayloadType>::ConstructObject);

		AllocatedObjects.Reset();

		Payloads.Reset();
		PayloadSize = 0;
		PayloadIndex = 0;

		OnSpawn_Event.Clear();
	}

	virtual ~TCsManager_PooledObject_Abstract()
	{
		Shutdown();
	}

protected:

	/** */
	FString Name;

public:

	/**
	*
	*
	* @param Params
	*/
	virtual void Init(const FCsManagerPooledObjectParams& Params)
	{
		Name		 = Params.Name;
		CurrentWorld = Params.World;
		LogType		 = Params.LogType;

		ConstructParams = Params.ConstructParams;

		FunctionNames[(uint8)ECsManagerPooledObjectFunctionNames::Update]		 = Name + TEXT("::Update");
		FunctionNames[(uint8)ECsManagerPooledObjectFunctionNames::Deallocate]	 = Name + TEXT("::Deallocate");
		FunctionNames[(uint8)ECsManagerPooledObjectFunctionNames::DeallocateAll] = Name + TEXT("::DeallocateAll");
		FunctionNames[(uint8)ECsManagerPooledObjectFunctionNames::Spawn]		 = Name + TEXT("::Spawn");
	}

	/**
	*
	*/
	virtual void Clear()
	{
		for (InterfaceContainerType* O : Pool)
		{
			if (O->IsObject())
			{
				if (UObject* Object = O->GetSafeObject())
				{
					if (!Object->IsPendingKill())
					{
						O->Deallocate();
						DeconstructObject(O);
					}
				}
			}
			else
			{
				O->Deallocate();
				DeconstructObject(O);
			}
		}

		Pool.Reset();
		PoolSize = 0;
		AllocatedObjects.Reset();

		for (ICsPooledObjectPayload* P : PooledObjectPayloads)
		{
			P->Reset();
		}
		OnAddToPool_Event.Clear();
		OnDeallocate_Event.Clear();
	}

	/**
	*
	*/
	virtual void Shutdown()
	{
		Clear();

		// Links
		{
			const int32 Count = Links.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				TLinkedList<InterfaceContainerType*>* L = Links[I];
				delete L;
				Links[I] = nullptr;
			}
			Links.Reset();
		}
		// Payloads
		{
			const int32 Count = Payloads.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				PayloadType* P = Payloads[I];
				delete P;
				Payloads[I] = nullptr;
			}
			Payloads.Reset();
			PooledObjectPayloads.Reset();
		}

		OnUpdate_Object_Event.Clear();
	}

	/** */
	TWeakObjectPtr<UWorld> CurrentWorld;

	/**
	*
	*
	* return	World associated with the pool.
	*/
	UWorld* GetCurrentWorld()
	{
		return CurrentWorld.IsValid() ? CurrentWorld.Get() : nullptr;
	}

	/**
	* Get the current time in seconds.
	*
	* return	Current time in seconds.
	*/
	virtual float GetCurrentTimeSeconds()
	{
		return GetCurrentWorld() ? GetCurrentWorld()->GetTimeSeconds() : 0.0f;
	}

	/**
	*
	* return Container
	*/
	TBaseDelegate<InterfaceContainerType*> ConstructContainer_Impl;

protected:

	InterfaceContainerType* ConstructContainer()
	{
		return new InterfaceContainerType();
	}

// Object
#pragma region
public:

	/**
	* Creates a pooled object of type ICsPooledObject.
	*
	* return
	*/
	virtual InterfaceContainerType* ConstructObject()
	{
		UClass* Class = ConstructParams.Class;

		checkf(Class, TEXT("%s:ConstructObject: No Class set."), *Name);

		UObject* Object = nullptr;

		// Actor
		if (ConstructParams.ConstructionType == ECsPooledObjectConstruction::Actor)
		{
			AActor* Actor = GetCurrentWorld()->SpawnActor<AActor>(Class, ConstructParams.ConstructionInfo);

			if (!ConstructParams.bReplicates)
			{
				Actor->SetReplicates(false);
				Actor->Role = ROLE_None;
				GetCurrentWorld()->RemoveNetworkActor(Actor);
			}

			checkf(Actor, TEXT("%s:ContructObject: Actor did NOT spawn."), *Name);

			Object = Actor;
		}

		if (Object)
		{
			InterfaceContainerType* O = ConstructContainer_Impl.Execute();

			O->SetObject(Object);

			O->Script_GetCache_Impl	 = Script_GetCache_Impl;
			O->Script_Allocate_Impl   = Script_Allocate_Impl;
			O->Script_Deallocate_Impl = Script_Deallocate_Impl;
			O->Script_Update_Impl	 = Script_Update_Impl;

#if WITH_EDITOR
			// ICsPooledObject Script Interface
			if (O->IsScript())
			{
				const FString ObjectName = Object->GetName();
				const FString ClassName = Class->GetName();

				checkf(O->Script_GetCache_Impl.IsBound(), TEXT("%s::ConstructObject: Object: %s with Class: %s implements a script interface of type: ICsPooledObject. Script_Update_Impl is NOT bound to any function."), *Name, *ObjectName, *ClassName);

				checkf(O->Script_Allocate_Impl.IsBound(), TEXT("%s:ConstructObject: Object: %s with Class: %s implements a script interface of type: ICsPooledObject. Script_Allocate_Impl is NOT bound to any function."), *Name, *ObjectName, *ClassName);

				checkf(O->Script_Deallocate_Impl.IsBound(), TEXT("%s:ConstructObject: Object: %s with Class: %s implements a script interface of type: ICsPooledObject. Script_Deallocate_Impl is NOT bound to any function."), *Name, *ObjectName, *ClassName);
			}
			// ICsUpdate Script Interface
			if (O->IsScriptUpdate())
			{
				const FString ObjectName = Object->GetName();
				const FString ClassName  = Class->GetName();

				checkf(O->Script_Update_Impl.IsBound(), TEXT("%s:ConstructObject: Object: %s with Class: %s implements a script interface of type: ICsUpdate. Script_Update_Impl is NOT bound to any function."), *Name, *ObjectName, *ClassName);
			}
#endif // #if WITH_EDITOR

			OnConstructObject_Event.Broadcast(O);

			return O;
		}
		checkf(0, TEXT("%s:ConstructObject: Failed to Construct Object with Class: %s."), *Name, *(Class->GetName()));
		return nullptr;
	}

	/**
	*
	*
	* return Object
	*/
	TBaseDelegate<InterfaceContainerType* /*Object*/> ConstructObject_Impl;

	/**
	*
	*
	*
	* @param Object
	*/
	TMulticastDelegate<void, const InterfaceContainerType* /*Object*/> OnConstructObject_Event;

	/**
	* Delete (or mark for deconstruction) a pooled object.
	*
	* @param Object		Container holding a pooled object.
	*/
	virtual void DeconstructObject(InterfaceContainerType* Object)
	{
		if (UObject* O = Object->GetObject())
			O->MarkPendingKill();
	}

	/**
	* Get the name of a pooled object.
	*
	* @param Object		Container holding a pooled object.
	* return			Name of the pooled object.
	*/
	virtual FString GetObjectName(const InterfaceContainerType* Object)
	{
		if (Object->IsObject())
			return Object->GetObject()->GetName();
		return NCsCached::Str::Empty;
	}

#pragma endregion Object

// Pool
#pragma region
protected:

	/** */
	FString FunctionNames[(uint8)ECsManagerPooledObjectFunctionNames::ECsManagerPooledObjectFunctionNames_MAX];

	/** */
	FCsManagerPooledObjectConstructParams ConstructParams;

	/** */
	TArray<InterfaceContainerType*> Pool;
	/** */
	TArray<TLinkedList<InterfaceContainerType*>*> Links;
	/** */
	int32 PoolSize;
	/** */
	int32 PoolIndex;

	/** */
	TArray<InterfaceContainerType*> AllocatedObjects;
	/** */
	TLinkedList<InterfaceContainerType*>* AllocatedHead;
	/** */
	TLinkedList<InterfaceContainerType*>* AllocatedTail;
	/** */
	int32 AllocatedObjectsSize;

public:

	/**
	*
	*
	* @param Size
	*/
	virtual void CreatePool(const int32& Size)
	{
		checkf(Size > 0, TEXT("%s::CreatePool: Size must be GREATER THAN 0."), *Name);

		PoolSize = Size;

		Pool.Reserve(PoolSize);
		Links.Reserve(PoolSize);
		AllocatedObjects.Reserve(PoolSize);

		for (int32 I = 0; I < Size; ++I)
		{
			InterfaceContainerType* O = ConstructObject_Impl.Execute();
			UObject* Object			  = O->GetObject();

#if WITH_EDITOR
			// ICsPooledObject Script Interface
			if (O->IsScript())
			{
				const FString ObjectName = Object->GetName();
				UClass* Class			 = Object->GetClass();
				const FString ClassName  = Class->GetName();

				checkf(O->Script_GetCache_Impl.IsBound(), TEXT("%s:CreatePool: Object: %s with Class: %s implements a script interface of type: ICsPooledObject. Script_GetCache_Impl is NOT bound to any function."), *Name, *ObjectName, *ClassName);

				checkf(O->Script_Allocate_Impl.IsBound(), TEXT("%s:CreatePool: Object: %s with Class: %s implements a script interface of type: ICsPooledObject. Script_Allocate_Impl is NOT bound to any function."), *Name, *ClassName);

				checkf(O->Script_Deallocate_Impl.IsBound(), TEXT("%s:CreatePool: Object: %s with Class: %s implements a script interface of type: ICsPooledObject. Script_Deallocate_Impl is NOT bound to any function."), *Name, *ClassName);
			}
			// ICsUpdate Script Interface
			if (O->IsScriptUpdate())
			{
				const FString ObjectName = Object->GetName();
				UClass* Class			 = Object->GetClass();
				const FString ClassName  = Class->GetName();

				checkf(O->Script_Update_Impl.IsBound(), TEXT("%s:CreatePool: Object: %s with Class: %s implements a script interface of type: ICsUpdate. Script_Update_Impl is NOT bound to any function."), *Name, *ClassName);
			}
#endif // #if WTIH_EDITOR

			O->GetCache()->Init(I);
			O->Deallocate();

			Pool.Add(O);

			// Add Link
			Links.Add(new TLinkedList<InterfaceContainerType*>());
			// Set Element for Link
			TLinkedList<InterfaceContainerType*>* Link = Links.Last();
			(**Link)								  = O;

			OnAddToPool_Event.Broadcast(O);
		}
	}

	// Add
#pragma region
public:

		// Pool
#pragma region

	/**
	* Adds an Object to the pool.
	*  The Object must implement the interface: ICsPooledObject.
	*
	* @param InterfaceObject	Object that implements the interface: ICsPooledObject.
	* @param Object				UObject reference.
	* return					Container holding a reference to a pooled object.
	*							Pooled Object implements the interface: ICsPooledObject.
	*/
	const InterfaceContainerType* AddToPool(InterfaceType* InterfaceObject, UObject* Object)
	{
		checkf(Object, TEXT("%s::AddToPool: Object is NULL."), *Name);

		InterfaceContainerType* O = ConstructContainer_Impl.Execute();
		Pool.Add(O);

		O->SetObject(Object);

		O->Script_GetCache_Impl   = Script_GetCache_Impl;
		O->Script_Allocate_Impl   = Script_Allocate_Impl;
		O->Script_Deallocate_Impl = Script_Deallocate_Impl;
		O->Script_Update_Impl	 = Script_Update_Impl;

		const int32& Index = O->GetCache()->GetIndex();

		checkf(Index == INDEX_NONE, TEXT("%s::AddToPool: PooledObject is already a part of an existing pool."), *Name);

#if WITH_EDITOR
		// ICsPooledObject Script Interface
		if (O->IsScript())
		{
			const FString ObjectName = Object->GetName();
			UClass* Class			 = Object->GetClass();
			const FString ClassName  = Class->GetName();

			checkf(O->Script_GetCache_Impl.IsBound(), TEXT("%s:AddToPool: Object: %s with Class: %s implements a script interface of type: ICsPooledObject. Script_GetCache_Impl is NOT bound to any function."), *Name, *ObjectName, *ClassName);

			checkf(O->Script_Allocate_Impl.IsBound(), TEXT("%s:AddToPool: Object: %s with Class: %s implements a script interface of type: ICsPooledObject. Script_Allocate_Impl is NOT bound to any function."), *Name, *ClassName);

			checkf(O->Script_Deallocate_Impl.IsBound(), TEXT("%s:AddToPool: Object: %s with Class: %s implements a script interface of type: ICsPooledObject. Script_Deallocate_Impl is NOT bound to any function."), *Name, *ClassName);
		}
		// ICsUpdate Script Interface
		if (O->IsScriptUpdate())
		{
			const FString ObjectName = Object->GetName();
			UClass* Class			 = Object->GetClass();
			const FString ClassName  = Class->GetName();

			checkf(O->Script_Update_Impl.IsBound(), TEXT("%s:AddToPool: Object: %s with Class: %s implements a script interface of type: ICsUpdate. Script_Update_Impl is NOT bound to any function."), *Name, *ClassName);
		}
#endif // #if WITH_EDITOR

		O->GetCache()->Init(PoolSize);
		O->Deallocate();

		// Add Link
		Links.Add(new TLinkedList<InterfaceContainerType*>());
		// Set Element for Link
		TLinkedList<InterfaceContainerType*>* Link = Links.Last();
		(**Link) = O;

		++PoolSize;

		OnAddToPool_UpdateScriptDelegates_Impl.ExecuteIfBound(O);
		OnAddToPool_Event.Broadcast(O);

		return O;
	}

	/**
	* Adds an Object to the pool.
	*  Object must implement the interface: ICsPooledObject.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object that implements the interface: ICsPooledObject.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsPooledObject.
	*/
	const InterfaceContainerType* AddToPool(InterfaceType* Object)
	{
		return AddToPool(Object, Object->_getUObject());
	}

	template<typename OtherInterfaceType, typename ContainerType>
	const ContainerType* AddToPool(OtherInterfaceType* Object)
	{
		static_assert(std::is_abstract<OtherInterfaceType>(), "TCsManager_PooledObject_Abstract::AddToPool: OtherInterfaceType is NOT an abstract class.");

		static_assert(std::is_base_of<InterfaceContainerType, ContainerType>(), "TCsManager_PooledObject_Abstract::AddToPool: ContainerType is NOT a child of InterfaceContainerType.");

#if WITH_EDITOR
		const ContainerType* Ptr = dynamic_cast<const ContainerType*>(AddToPool(Object));

		checkf(Ptr, TEXT("%s::AddToPool: Failed to cast to ContainerType."), *Name);

		return Ptr;
#else
		return static_cast<ContainerType*>(AddToPool(Object->_getUObject()));
#endif // #if WITH_EDITOR
	}

	/**
	* Adds an Object to the pool.
	*  Object must implement the interface: ICsPooledObject or the UClass
	*  associated with the Object have ImplementsInterface(UCsPooledObject::StaticClass()) == true.
	*
	* @param Object		Object or Object->GetClass() that implements the interface: ICsPooledObject.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object or UClass associated with Pooled Object implements
	*					the interface: ICsPooledObject.
	*/
	const InterfaceContainerType* AddToPool(UObject* Object)
	{
		return AddToPool(nullptr, Object);
	}

	template<typename ContainerType>
	const ContainerType* AddToPool(UObject* Object)
	{
		static_assert(std::is_base_of<InterfaceContainerType, ContainerType>(), "TCsManager_PooledObject_Abstract::AddToPool ContainerType is NOT a child of InterfaceContainerType.");
		
#if WITH_EDITOR
		const ContainerType* Ptr = dynamic_cast<const ContainerType*>(AddToPool(Object));

		checkf(Ptr, TEXT("%s::AddToPool: Failed to cast to ContainerType."), *Name);

		return Ptr;
#else
		return static_cast<const ContainerType*>(AddToPool(Object));
#endif // #if WITH_EDITOR
	}

	/** Delegate called after Adding an Object to the pool.
	*
	* @param Object
	*/
	TMulticastDelegate<void, const InterfaceContainerType* /*Object*/> OnAddToPool_Event;

	/**
	* 
	*
	* @param Object
	*/
	TBaseDelegate<void, InterfaceContainerType* /*Object*/> OnAddToPool_UpdateScriptDelegates_Impl;

#pragma endregion Pool

	// Allocated Objects
#pragma region

	/**
	* Adds an Object to the allocated objects. 
	* If the Object is NOT added to the pool, add it to the pool.
	*  Object must implement the interface: ICsPooledObject.
	*
	* @param InterfaceObject	Object that implements the interface: ICsPooledObject.
	* @param Object				UObject reference.
	* return					Container holding a reference to a pooled object.
	*							Pooled Object implements the interface: ICsPooledObject.
	*/
	const InterfaceContainerType* AddToAllocatedObjects(InterfaceType* InterfaceObject, UObject* Object)
	{
		checkf(Object, TEXT("%s:AddToAllocatedObjects: Object is NULL."), *Name);

		int32 Index   = INDEX_NONE;
		UClass* Class = Object->GetClass();

		// Interface
		if (ICsPooledObject* P = Cast<ICsPooledObject>(Object))
		{
			Index = P->GetCache()->GetIndex();
		}
		// Script Interface
		else
		if (Class->ImplementsInterface(UCsPooledObject::StaticClass()))
		{
			checkf(Script_GetCache_Impl.IsBound(), TEXT("%s:AddToAllocatedObjects: Script_GetCache_Impl is NOT bound to any function."), *Name);

			Index = Script_GetCache_Impl.Execute(Object)->GetIndex();
		}
		else
		{
			checkf(0, TEXT("%s:AddToAllocatedObjects: Object: %s with Class: %s does NOT implement the interface: ICsPooledObject."), *Name, *(Object->GetName()), *(Class->GetName()));
		}

		// Add to pool
		if (Index == INDEX_NONE)
		{
			const InterfaceContainerType* O = AddToPool(InterfaceObject, Object);

			AddToAllocatedObjects_Internal(const_cast<InterfaceContainerType*>(O));

			return O;
		}
		// Already exists in pool
		else
		{
			checkf(PoolSize > 0, TEXT("%s:AddToAllocatedObjects: No pool created. Call CreatePool."), *Name);

			checkf(Index >= 0 && Index < PoolSize, TEXT("%s:AddToAllocatedObjects: Index: %d is NOT Valid for this pool."), *Name, Index);

			InterfaceContainerType* O = Pool[Index];

			if (O->GetCache()->IsAllocated())
				return O;

			AddToAllocatedObjects_Internal(O);

			return O;
		}
	}

	/**
	* Adds an Object to the Allocated Objects.
	* If the Object is NOT added to the pool, add it to the pool.
	*  Object must implement the interface: ICsPooledObject.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object that implements the interface: ICsPooledObject.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsPooledObject.
	*/
	const InterfaceContainerType* AddToAllocatedObjects(InterfaceType* Object)
	{
		checkf(Object, TEXT("%s::AddToAllocatedObjects: Object is NULL."));

		return AddToAllocatedObjects(Object, Object->_getUObject());
	}

	/**
	* Adds an Object to the allocated objects.
	* If the Object is NOT added to the pool, add it to the pool.
	*  Object must implement the interface: ICsPooledObject or the UClass
	*  associated with the Object have ImplementsInterface(UCsPooledObject::StaticClass()) == true.
	*
	* @param Object		Object or Object->GetClass() that implements the interface: ICsPooledObject.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object or UClass associated with Pooled Object implements
	*					the interface: ICsPooledObject.
	*/
	const InterfaceContainerType* AddToAllocatedObjects(UObject* Object)
	{
		return AddToAllocatedObjects(nullptr, Object);
	}

protected:

	/**
	*
	*
	* @param Object
	*/
	virtual void AddToAllocatedObjects_Internal(InterfaceContainerType* Object)
	{
		const int32& Index = Object->GetCache()->GetIndex();

		TLinkedList<InterfaceContainerType*>* Link = Links[Index];

		AddAllocatedLink(Link);
		AllocatedObjects.Add(Object);
	}

#pragma endregion Allocated Objects

#pragma endregion Add

	// Linked List
#pragma region
public:

	FORCEINLINE const TLinkedList<InterfaceContainerType*>* GetAllocatedHead()
	{
		return AllocatedHead;
	}

	FORCEINLINE const TLinkedList<InterfaceContainerType*>* GetAllocatedTail()
	{
		return AllocatedTail;
	}

protected:

	/**
	*
	*
	* @param Link
	*/
	void AddAllocatedLink(TLinkedList<InterfaceContainerType*>* Link)
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
	*
	*
	* @param Link
	*/
	void RemoveAllocatedLink(TLinkedList<InterfaceContainerType*>* Link)
	{
		// Check to Update HEAD
		if (Link == AllocatedHead)
		{
			if (AllocatedObjectsSize > CS_SINGLETON)
			{
				AllocatedHead = Link->GetNextLink();
			}
			else
			{
				AllocatedHead = nullptr;
				AllocatedTail = nullptr;
			}
		}
		Link->Unlink();
	}

#pragma endregion Linked List

public:

	/**
	* Get the pool.
	*  Pool is an array of containers holding references to objects that
	*  implement the interface: ICsPooledObject.
	*
	* return	Pool
	*/
	FORCEINLINE const TArray<InterfaceContainerType*>& GetPool()
	{
		return Pool;
	}

	/**
	* Get the allocated objects.
	*  Allocated Objects are an array of containers holding references to objects that
	*  implement the interface: ICsPooledObject.
	*
	* return	Allocated Objects
	*/
	FORCEINLINE const TArray<InterfaceContainerType*>& GetAllocatedObjects()
	{
		return AllocatedObjects;
	}

	/**
	* Get the number of elements in the pool.
	*
	* return	Number of elements in the pool.
	*/
	FORCEINLINE const int32& GetPoolSize()
	{
		return PoolSize;
	}

	/**
	* Get the number of allocated objects.
	*
	* return	Number of allocated objects.
	*/
	FORCEINLINE int32 GetAllocatedObjectsSize()
	{
		return AllocatedObjectsSize;
	}

	/**
	* Get whether all elements in the pool have been allocated.
	*
	* return	All elements allocated or not.
	*/
	FORCEINLINE bool IsExhausted()
	{
		return AllocatedObjectsSize == PoolSize;
	}

	// Find
#pragma region
public:

	/**
	* Find the container holding a reference to a pooled object in the pool by Index.
	*
	* @param Index	Index of the pooled object.
	* return		Container holding a reference to a pooled object.
	*				Pooled Object implements the interface: ICsPooledObject.
	*/
	FORCEINLINE const InterfaceContainerType* FindObject(const int32& Index)
	{
		checkf(Index > 0 && Index < PoolSize, TEXT("FCsManager_PooledObject::FindObject: Index: %d is NOT valid for pool."), Index);

		return Pool[Index];
	}

	/**
	* Find the container holding a reference to a pooled object in the pool by Interface.
	*  Object must implement the interface: ICsPooledObject.
	*
	* @param Object		Object of interface type: ICsPooledObject.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsPooledObject.
	*/
	FORCEINLINE const InterfaceContainerType* FindObject(InterfaceType* Object)
	{
		checkf(Object, TEXT("%s::FindObject: Object is NULL."), *Name);

		return FindObject(Object->_getUObject());
	}

	/**
	* Find the container holding a reference to a pooled object in the pool by UObject.
	*  Object must implement the interface: ICsPooledObject or the UClass
	*  associated with the Object have ImplementsInterface(UCsPooledObject::StaticClass()) == true.
	*
	* @param Object		Object or Object->GetClass() that implements the interface: ICsPooledObject.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object or UClass associated with Pooled Object implements
	*					the interface: ICsPooledObject.
	*/
	const InterfaceContainerType* FindObject(UObject* Object)
	{
		checkf(Object, TEXT("%s::FindObject: Object is NULL."), *Name);

		UClass* Class = Object->GetClass();
		int32 Index   = INDEX_NONE;

		// Interface
		if (ICsPooledObject* Interface = Cast<ICsPooledObject>(Object))
		{
			Index = Interface->GetCache()->GetIndex();
		}
		// Script Interface
		else
		if (Class->ImplementsInterface(UCsPooledObject::StaticClass()))
		{
			checkf(Script_GetCache_Impl.IsBound(), TEXT("%s::FindObject: Object: %s with Class: %s does NOT have Script_GetCache_Impl Bound to any function."), *Name, *(Object->GetName()), *(Class->GetName()));

			Index = Script_GetCache_Impl.Execute(Object)->GetIndex();
		}
		// INVALID
		else
		{
			checkf(false, TEXT("%s::FindObject: Object: %s with Class: %s does NOT implement interface: ICsPooledObject."), *Name, *(Object->GetName()), *(Class->GetName()));

			return nullptr;
		}
	
		checkf(Index != INDEX_NONE && Index < PoolSize, TEXT("%s::FindObject: Object: %s with Class: %s is already in a pool."), *Name, *(Object->GetName()), *(Class->GetName()));

		InterfaceContainerType* O = Pool[Index];

		checkf(O->GetObject() == Object, TEXT("%s::FindObject: Object: %s with Class: %s is NOT this pool."), *Name, *(Object->GetName()), *(Class->GetName()));

		return O;
	}

	/**
	* Safely, via checks, find the container holding a reference to a pooled object in the pool by Index.
	*
	* @param Index	Index of the pooled object.
	* return		Container holding a reference to a pooled object.
	*				Pooled Object implements the interface: ICsPooledObject.
	*/
	const InterfaceContainerType* FindSafeObject(const int32& Index)
	{
		if (Index < 0 || Index >= PoolSize)
			return nullptr;
		return Pool[Index];
	}

	/**
	* Safely, via checks, find the container holding a reference to a pooled object in the pool by the Interface.
	*
	* @param Object		Object that implements the interface: ICsPooledObject.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsPooledObject.
	*/
	const InterfaceContainerType* FindSafeObject(InterfaceType* Object)
	{
		if (!Object)
			return nullptr;

		return FindSafeObject(Object->_getUObject());
	}

	/**
	* Safely, via checks, find the container holding a reference to a pooled object in the pool by the UObject.
	*
	* @param Object		Object or Object->GetClass() that implements the interface: ICsPooledObject.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object or UClass associated with Pooled Object implements
	*					the interface: ICsPooledObject.
	*/
	const InterfaceContainerType* FindSafeObject(UObject* Object)
	{
		if (!Object)
			return nullptr;

		UClass* Class = Object->GetClass();
		int32 Index   = INDEX_NONE;

		// Interface
		if (ICsPooledObject* Interface = Cast<ICsPooledObject>(Object))
		{
			Index = Interface->GetCache()->GetIndex();
		}
		// Script Interface
		else
		if (Class->ImplementsInterface(UCsPooledObject::StaticClass()))
		{
			if (!Script_GetCache_Impl.IsBound())
				return nullptr;

			Index = Script_GetCache_Impl.Execute(Object)->GetIndex();
		}
		// INVALID
		else
		{
			return nullptr;
		}
	
		if (Index == INDEX_NONE && Index >= PoolSize)
			return nullptr;

		InterfaceContainerType* O = Pool[Index];

		if (O->GetObject() != Object)
			return nullptr;

		return O;
	}

#pragma endregion Find
	 
#pragma endregion Pool

// Update
#pragma region
public:

	/**
	*
	*
	* @param DeltaTime
	*/
	virtual void Update(const FCsDeltaTime& DeltaTime)
	{
		TLinkedList<InterfaceContainerType*>* Current = AllocatedHead;
		TLinkedList<InterfaceContainerType*>* Next	 = Current;

		int32 NewSize = 0;

		while (Next)
		{
			Current					  = Next;
			InterfaceContainerType* O = **Current;
			Next					  = Current->GetNextLink();

			if (O->GetCache()->GetUpdateType() == ECsPooledObjectUpdate::Manager)
			{
				O->Update(DeltaTime);
			}

			// Check if PooledObject is queued for Deallocation
			if (O->GetCache()->ShouldDeallocate())
			{
#if !UE_BUILD_SHIPPING
				//LogTransaction(FunctionNames[(uint8)ECsManagerPooledObjectFunctionNames::Update], ECsPoolTransaction::Deallocate, O);
#endif // #if !UE_BUILD_SHIPPING
				O->Deallocate();
				RemoveAllocatedLink(Current);

				OnDeallocate_Event.Broadcast(O);
				continue;
			}

			// Check if PooledObject was Deallocated NOT in a normal way (i.e. Out of Bounds)
			if (!O->GetCache()->IsAllocated())
			{
#if !UE_BUILD_SHIPPING
				//UE_LOG(LogCs, Warning, TEXT("%s::OnTick: %s: %s at PoolIndex: %d was prematurely deallocated NOT in a normal way."), *Name, *(ConstructParams.ClassName), *(GetObjectName(O)), O.GetCache()->GetIndex());

				//LogTransaction(FunctionNames[(uint8)ECsManagerPooledObjectFunctionNames::Update], ECsPoolTransaction::Deallocate, O);
#endif // #if !UE_BUILD_SHIPPING
				RemoveAllocatedLink(Current);
				continue;
			}

			// Check if PooledObject LifeTime has expired.
			if (O->GetCache()->HasLifeTimeExpired())
			{
#if !UE_BUILD_SHIPPING
				//LogTransaction(FunctionNames[(uint8)ECsManagerPooledObjectFunctionNames::Update], ECsPoolTransaction::Deallocate, O);
#endif // #if !UE_BUILD_SHIPPING
				O->Deallocate();
				RemoveAllocatedLink(Current);

				OnDeallocate_Event.Broadcast(O);
				continue;
			}

			if (NewSize < AllocatedObjectsSize)
			{
				AllocatedObjects[NewSize] = O;
			}

			OnUpdate_Object_Event.Broadcast(O);
			++NewSize;
		}

		for (int32 I = AllocatedObjectsSize - 1; I >= NewSize; --I)
		{
			AllocatedObjects.RemoveAt(I, 1, false);
		}
		AllocatedObjectsSize = AllocatedObjects.Num();
	}

	/**
	*
	* @param Object
	*/
	TMulticastDelegate<void, const InterfaceContainerType* /*Object*/> OnUpdate_Object_Event;

#pragma endregion Update

// Allocate / DeAllocate
#pragma region
protected:

	/**
	*
	*
	* @param Payload
	* return
	*/
	InterfaceContainerType* Allocate(PayloadType* Payload)
	{
		if (IsExhausted())
		{
			checkf(0, TEXT("%s::Allocate: Pool is exhausted. Pool Size is %d."), *Name, PoolSize);
			return nullptr;
		}

		for (int32 I = 0; I < PoolSize; ++I)
		{
			PoolIndex				  = (PoolIndex + 1) % PoolSize;
			InterfaceContainerType* O = Pool[PoolIndex];

			if (!O->GetCache()->IsAllocated())
			{
				FCsInterfaceMap* InterfaceMap = Payload->GetInterfaceMap();

				checkf(InterfaceMap, TEXT("%s::Spawn: InterfaceMap is NULL. PayloadType failed to propertly implement method: GetInterfaceMap for interface: ICsGetInterfaceMap."), *Name);

				ICsPooledObjectPayload* P = InterfaceMap->Get<ICsPooledObjectPayload>();

				O->Allocate(P);
				return O;
			}
		}
		checkf(0, TEXT("%s::Allocate: Pool is exhausted. Pool Size is %d."), *Name, PoolSize);
		return nullptr;
	}

public:

	/**
	*
	*  NOTE: This process is O(n). Consider queueing the deallocate.
	*
	* @param Index
	* return
	*/
	bool Deallocate(const int32& Index)
	{
		// Check if Index is valid
		if (Index >= PoolSize)
		{
			//UE_LOG(LogCs, Warning, TEXT("%s::DeAllocate: %s with PoolIndex: %d is NOT in the Pool. Call AddToPool."), *Name, *(ConstructParams.ClassName), Index);
			return false;
		}
		// Check if object is already deallocated
		if (Links[Index] != AllocatedHead &&
			!Links[Index]->IsLinked())
		{
			//UE_LOG(LogCs, Warning, TEXT("%s::DeAllocate: %s at PoolIndex: %d is already deallocated or not in the Pool."), *Name, *(ConstructParams.ClassName), Index);
			return false;
		}
		// Check if object is already deallocated
		if (AllocatedObjectsSize == CS_EMPTY)
		{
			//UE_LOG(LogCs, Warning, TEXT("%s::DeAllocate: %s at PoolIndex: %d is already deallocated or not in the Pool."), *Name, *(ConstructParams.ClassName), Index);
			return false;
		}

		TLinkedList<InterfaceContainerType*>* Link = Links[Index];
		InterfaceContainerType* O				   = **Link;

#if !UE_BUILD_SHIPPING
		LogTransaction(FunctionNames[(uint8)ECsManagerPooledObjectFunctionNames::Deallocate], ECsPoolTransaction::Deallocate, O);
#endif // #if !UE_BUILD_SHIPPING

		O->Deallocate();
		RemoveAllocatedLink(Link);

		// Update AllocatedObjects
		TLinkedList<InterfaceContainerType*>* Current = AllocatedHead;
		TLinkedList<InterfaceContainerType*>* Next    = Current;

		int32 NewSize = 0;

		while (Next)
		{
			Current = Next;
			O		= **Current;
			Next	= Current->GetNextLink();

			if (NewSize < AllocatedObjectsSize)
			{
				AllocatedObjects[NewSize] = O;
			}

			++NewSize;
		}

		for (int32 I = AllocatedObjectsSize - 1; I >= NewSize; --I)
		{
			AllocatedObjects.RemoveAt(I, 1, false);
		}
		AllocatedObjectsSize = AllocatedObjects.Num();

		OnDeallocate_Event.Broadcast(O);
		return true;
	}

	/** Delegate type when deallocating a pooled object.
	*
	* @param Object
	*/
	TMulticastDelegate<void, const InterfaceContainerType* /*Object*/> OnDeallocate_Event;

	/**
	*
	*/
	void DeallocateAll()
	{
		for (InterfaceContainerType& O : AllocatedObjects)
		{
#if !UE_BUILD_SHIPPING
			//LogTransaction(FunctionNames[(uint8)ECsManagerPooledObjectFunctionNames::DeallocateAll], ECsPoolTransaction::Deallocate, O);
#endif // #if !UE_BUILD_SHIPPING
			O.Deallocate();
			OnDeallocate_Event.Broadcast(O);
		}

		AllocatedObjects.Reset(PoolSize);

		TLinkedList<InterfaceContainerType>* Current = AllocatedHead;
		TLinkedList<InterfaceContainerType>* Next	 = Current;


		while (Next)
		{
			Current = Next;
			Next	= Current->GetNextLink();

			Current->Unlink();
		}

		AllocatedHead = nullptr;
		AllocatedTail = nullptr;
	}

#pragma endregion Allocate / DeAllocate

// Payload
#pragma region
protected:

	/** */
	TArray<PayloadType*> Payloads;
	/** */
	TArray<ICsPooledObjectPayload*> PooledObjectPayloads;
	/** */
	int32 PayloadSize;
	/** */
	int32 PayloadIndex;

public:

	/**
	*
	*
	* @param Size
	*/
	void ConstructPayloads(const int32& Size)
	{
		checkf(ConstructPayload_Impl.IsBound(), TEXT("%s::ConstructPaylaods: ConstructPayload_Impl is NOT bound."), *Name);

		PayloadSize = Size;

		Payloads.Reserve(PayloadSize);
		PooledObjectPayloads.Reserve(PayloadSize);

		for (int32 I = 0; I < Size; ++I)
		{
			Payloads.Add(ConstructPayload_Impl.Execute());

			checkf(Payloads[I], TEXT("%s::ConstructPayloads: Failed to construct payload of type: PayloadType."), *Name);

			FCsInterfaceMap* InterfaceMap = Payloads[I]->GetInterfaceMap();

			checkf(InterfaceMap, TEXT("%s::ConstructPayloads:InterfaceMap is NULL. PayloadType failed to propertly implement method: GetInterfaceMap for interface: ICsGetInterfaceMap."), *Name);

			ICsPooledObjectPayload* P = InterfaceMap->Get<ICsPooledObjectPayload>();

			PooledObjectPayloads.Add(P);
		}
	}

	/**
	*
	* @param Size
	*/
	TBaseDelegate<PayloadType*> ConstructPayload_Impl;

	/**
	*
	*/
	void DeconstructPayloads()
	{
		for (int32 I = 0; I < PayloadSize; ++I)
		{
			PayloadType* P = Payloads[I];
			delete P;
			Payloads[I] = nullptr;
		}
		Payloads.Reset(PayloadSize);
		PooledObjectPayloads.Reset(PayloadSize);
		PayloadSize = 0;
	}

	/**
	*
	*
	* return
	*/
	PayloadType* AllocatePayload()
	{
		for (int32 I = 0; I < PayloadSize; ++I)
		{
			PayloadIndex			  = (PayloadIndex + 1) % PayloadSize;
			PayloadType* Payload	  = Payloads[PayloadIndex];
			ICsPooledObjectPayload* P = PooledObjectPayloads[PayloadIndex];

			if (!P->IsAllocated())
			{
				P->Allocate();
				return Payload;
			}
		}
		checkf(0, TEXT("%s::AllocatePayload: Pool is exhausted. Pool Size = %d."), *Name, PayloadSize);
		return nullptr;
	}

#pragma endregion Payload

// Log
#pragma region
protected:

	FECsCVarLog LogType;

	virtual void LogTransaction(const FString& FunctionName, const ECsPoolTransaction& Transaction, const InterfaceContainerType* Object)
	{
		if (FCsCVarLogMap::Get().IsShowing(LogType))
		{
			/*
			const FString& TransactionAsString = NCsPoolTransaction::ToActionString(Transaction);

			ICsPooledObject* Interface  = Object->GetInterface();
			const FString ObjectName	= GetObjectName(Object);
			const float CurrentTime		= GetCurrentTimeSeconds();
			const UObject* ObjectOwner	= Interface->GetCache()->GetOwner();
			const FString OwnerName		= ObjectOwner ? ObjectOwner->GetName() : NCsCached::Str::None;
			const UObject* Parent		= Interface->GetCache()->GetParent();
			const FString ParentName	= Parent ? Parent->GetName() : NCsCached::Str::None;

			if (ObjectOwner && Parent)
			{
				//UE_LOG(LogCs, Warning, TEXT("%s: %s %s: %s of Type: %s at %f for %s attached to %s."), *FunctionName, *TransactionAsString, *(ConstructParams.ClassName), *ObjectName, CurrentTime, *OwnerName, *ParentName);
			}
			else
			if (ObjectOwner)
			{
				//UE_LOG(LogCs, Warning, TEXT("%s: %s %s: %s of Type: %s at %f for %s."), *FunctionName, *TransactionAsString, *(ConstructParams.ClassName), *ObjectName, CurrentTime, *OwnerName);
			}
			else
			if (Parent)
			{
				//UE_LOG(LogCs, Warning, TEXT("%s: %s %s: %s of Type: %s at %f attached to %s."), *FunctionName, *TransactionAsString, *(ConstructParams.ClassName), *ObjectName, CurrentTime, *ParentName);
			}
			else
			{
				//UE_LOG(LogCs, Warning, TEXT("%s: %s %s: %s of Type: %s at %f."), *FunctionName, *TransactionAsString, *(ConstructParams.ClassName), *ObjectName, CurrentTime);
			}
			*/
		}
	}

#pragma endregion Log

// Spawn
#pragma region
public:

	/**
	*
	*
	* @param Payload
	* return
	*/
	const InterfaceContainerType* Spawn(PayloadType* Payload)
	{
		InterfaceContainerType* O = Allocate(Payload);

		LogTransaction(FunctionNames[(uint8)ECsManagerPooledObjectFunctionNames::Spawn], ECsPoolTransaction::Allocate, O);

		FCsInterfaceMap* InterfaceMap = Payload->GetInterfaceMap();

		checkf(InterfaceMap, TEXT("%s::Spawn: InterfaceMap is NULL. PayloadType failed to propertly implement method: GetInterfaceMap for interface: ICsGetInterfaceMap."), *Name);

		ICsPooledObjectPayload* P = InterfaceMap->Get<ICsPooledObjectPayload>();
		P->Reset();

		AddToAllocatedObjects_Internal(O);
		OnSpawn_Event.Broadcast(O);
		return O;
	}


	/**
	*
	* @param Object
	*/
	TMulticastDelegate<void, const InterfaceContainerType* /*Object*/> OnSpawn_Event;

#pragma endregion Spawn

// Destroy
#pragma region
public:

	/**
	*
	*  NOTE: This process is O(n). Consider queueing the deallocate.
	*
	* @param Index
	* return
	*/
	virtual bool Destroy(const int32& Index)
	{
		return Deallocate(Index);
	}

	/**
	*
	*  NOTE: This process is O(n). Consider queueing the deallocate.
	*
	* @param Object
	* return
	*/
	virtual bool Destroy(InterfaceType* Object)
	{
		return Destroy(Object->_getUObject());
	}

	/**
	*
	*  NOTE: This process is O(n). Consider queueing the deallocate.
	*
	* @param Object
	* return
	*/
	virtual bool Destroy(UObject* Object)
	{
		const InterfaceContainerType* O = FindObject(Object);
		return Destroy(O->GetCache()->GetIndex());
	}

#pragma endregion Destroy

// Script
#pragma region
public:

	FCsPooledObject::FScript_GetCache Script_GetCache_Impl;

	FCsPooledObject::FScript_Allocate Script_Allocate_Impl;

	FCsPooledObject::FScript_Deallocate Script_Deallocate_Impl;

	FCsPooledObject::FScript_Update Script_Update_Impl;

#pragma endregion Script
};
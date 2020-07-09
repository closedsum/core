// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#pragma once
#include "Managers/Pool/CsManager_PooledObject_Abstract.h"
#include "Managers/Pool/CsPooledObject.h"
#include "CsCVars.h"

// ICsManager_PooledObject_Map
#pragma region

class ICsManager_PooledObject_Map
{
public:

	virtual ~ICsManager_PooledObject_Map() {}

	virtual void Clear() = 0;
	virtual void Shutdown() = 0;

	virtual UWorld* GetCurrentWorld() = 0;
};

#pragma endregion ICsManager_PooledObject_Map

// Enums
#pragma region

enum class ECsManagerPooledObjectMapFunctionNames : uint8
{
	OnTick,
	Deallocate,
	DeallocateAll,
	Spawn,
	ECsManagerPooledObjectMapFunctionNames_MAX,
};

#pragma endregion Enums

// Structs
#pragma region

#pragma endregion Structs

class UWorld;
class UObject;
class UClass;
class AActor;
class ICsPooledObject;
struct ICsPooledObjectPayload;

template<typename InterfaceType, typename InterfaceContainerType, typename PayloadType, typename KeyType>
class TCsManager_PooledObject_Map : public ICsManager_PooledObject_Map
{
	static_assert(std::is_abstract<InterfaceType>(), "TCsManager_PooledObject_Map: InterafaceType MUST be abstract.");

	// TODO: Check InterfaceType implements _getUObject

	static_assert(std::is_base_of<FCsPooledObject, InterfaceContainerType>(), "TCsManager_PooledObject_Map: InterfaceContainerType is NOT a child of: FCsPooledObject.");

	static_assert(std::is_abstract<PayloadType>(), "TCsManager_PooledObject_Map: PayloadType MUST be abstract.");

	static_assert(std::is_base_of<ICsGetInterfaceMap, PayloadType>(), "TCsManager_PooledObject_Map: PayloadType does NOT implement the interface: ICsGetInterfaceMap.");

private:

	typedef TCsManager_PooledObject_Abstract<InterfaceType, InterfaceContainerType, PayloadType> TManager_PooledObject_Abstract;

// Structs
#pragma region
public:

	struct FCsManagerPooledObjectMapParams
	{
	public:

		FString Name;

		UWorld* World;

		FECsCVarLog LogType;

		TMap<KeyType, FCsManagerPooledObjectParams> ObjectParams;

		FCsManagerPooledObjectMapParams() :
			Name(),
			World(nullptr),
			LogType(),
			ObjectParams()
		{
		}
	};

#pragma endregion Structs

public:
	TCsManager_PooledObject_Map() :
		Name(),
		CurrentWorld(nullptr),
		CurrentConstructObjectType(),
		ConstructContainer_Impl(),
		Pools(),
		ConstructManagerPooledObjects_Impl(),
		OnCreatePool_AddToPool_Event(),
		CurrentCreatePoolType(),
		OnAddToPool_Event(),
		OnAddToAllocatedObjects_Event(),
		OnPreUpdate_Pool_Impl(),
		OnUpdate_Object_Event(),
		OnPostUpdate_Pool_Impl(),
		CurrentUpdatePoolType(),
		CurrentConstructPayloadType(),
		ConstructPayload_Impl(),
		LogTransaction_Impl(),
		LogType(),
		OnSpawn_Event(),
		Script_GetCache_Impl(),
		Script_Allocate_Impl(),
		Script_Deallocate_Impl(),
		Script_Update_Impl(),
		Script_OnConstructObject_Impl()
	{
		ConstructManagerPooledObjects_Impl.BindRaw(this, &TCsManager_PooledObject_Map<InterfaceType, InterfaceContainerType, PayloadType, KeyType>::ConstructManagerPooledObjects);

		OnAddToPool_Event.Clear();
		OnSpawn_Event.Clear();
		OnDestroy_Event.Clear();
	}

	virtual ~TCsManager_PooledObject_Map()
	{
		Shutdown();
	}

protected:

	FString Name;

public:

	/**
	* Init
	*/
	virtual void Init(const FCsManagerPooledObjectMapParams& Params)
	{
		Name			= Params.Name;
		CurrentWorld	= Params.World;
		LogType			= Params.LogType;

		for (const TPair<KeyType, FCsManagerPooledObjectParams>& Pair : Params.ObjectParams)
		{
			const KeyType& Key								= Pair.Key;
			const FCsManagerPooledObjectParams& ObjectParam = Pair.Value;

			TManager_PooledObject_Abstract* Pool = ConstructManagerPooledObjects_Impl.Execute(Key);

			Pool->LogTransaction_Impl = LogTransaction_Impl;

			Pool->ConstructContainer_Impl.BindRaw(this, &TCsManager_PooledObject_Map<InterfaceType, InterfaceContainerType, PayloadType, KeyType>::ConstructContainer_Internal);
			Pool->ConstructPayload_Impl.BindRaw(this, &TCsManager_PooledObject_Map<InterfaceType, InterfaceContainerType, PayloadType, KeyType>::ConstructPayload_Internal);

			// Bind the appropriate Script delegates.
			Pool->Script_GetCache_Impl			= Script_GetCache_Impl;
			Pool->Script_Allocate_Impl			= Script_Allocate_Impl;
			Pool->Script_Deallocate_Impl		= Script_Deallocate_Impl;
			Pool->Script_Update_Impl			= Script_Update_Impl;
			Pool->Script_OnConstructObject_Impl = Script_OnConstructObject_Impl;

			// Create pool
			if (ObjectParam.bCreatePool)
			{
				CurrentCreatePoolType = Key;

				// Add delegates to capture events when calling CreatePool

					// Bind to OnConstructObject so the event OnConstructObject_Event can properly broadcast events.
				FDelegateHandle OnConstructObjectHandle = Pool->OnConstructObject_Event.AddRaw(this, &TCsManager_PooledObject_Map<InterfaceType, InterfaceContainerType, PayloadType, KeyType>::OnConstructObject);
					// Bind to OnAddToPool so the event OnAddToPool_Event can properly broadcast events.
				FDelegateHandle OnAddToPoolHandle = Pool->OnAddToPool_Event.AddRaw(this, &TCsManager_PooledObject_Map<InterfaceType, InterfaceContainerType, PayloadType, KeyType>::OnCreatePool_AddToPool);

				Pool->Init(ObjectParam);

				// Remove any delegates used to capture events when calling CreatePool
				Pool->OnConstructObject_Event.Remove(OnConstructObjectHandle);
				Pool->OnAddToPool_Event.Remove(OnAddToPoolHandle);
			}
			else
			{
				Pool->Init(ObjectParam);
			}

			// Bind to OnUpdate_Pool_Object so the event OnUpdate_Object_Event can properly broadcast events.
			Pool->OnUpdate_Object_Event.AddRaw(this, &TCsManager_PooledObject_Map<InterfaceType, InterfaceContainerType, PayloadType, KeyType>::OnUpdate_Pool_Object);

			Pools.Add(Key, Pool);
		}

		FunctionNames[(uint8)ECsManagerPooledObjectMapFunctionNames::OnTick]		 = Name + TEXT("::OnTick");
		FunctionNames[(uint8)ECsManagerPooledObjectMapFunctionNames::Deallocate]	 = Name + TEXT("::Deallocate");
		FunctionNames[(uint8)ECsManagerPooledObjectMapFunctionNames::DeallocateAll] = Name + TEXT("::DeallocateAll");
		FunctionNames[(uint8)ECsManagerPooledObjectMapFunctionNames::Spawn]		 = Name + TEXT("::Spawn");
	}

	/**
	* Resets all memory allocations
	*/
	virtual void Clear()
	{
		for (TPair<KeyType, TManager_PooledObject_Abstract*>& Pair : Pools)
		{
			Pair.Value->Clear();
		}

		OnAddToPool_Event.Clear();
		OnSpawn_Event.Clear();
		OnDestroy_Event.Clear();
	}

	/**
	* Resets and deletes all memory allocation. Called when terminating the manager
	*/
	virtual void Shutdown()
	{
		Clear();

		ConstructManagerPooledObjects_Impl.Unbind();

		for (TPair<KeyType, TManager_PooledObject_Abstract*>& Pair : Pools)
		{
			TManager_PooledObject_Abstract* Pool = Pair.Value;
			Pool->Shutdown();
			delete Pool;
			Pair.Value = nullptr;
		}
		
		Pools.Reset();
	}

	TWeakObjectPtr<UWorld> CurrentWorld;

	UWorld* GetCurrentWorld()
	{
		return CurrentWorld.IsValid() ? CurrentWorld.Get() : nullptr;
	}

	virtual float GetCurrentTimeSeconds()
	{
		return GetCurrentWorld() ? GetCurrentWorld()->GetTimeSeconds() : 0.0f;
	}

	virtual const FString& KeyTypeToString(const KeyType& Type)
	{
		return NCsCached::Str::Empty;
	}

	virtual bool IsValidKey(const KeyType& Type)
	{
		return true;
	}

// Object
#pragma region
private:

	KeyType CurrentConstructObjectType;

protected:

	/**
	* Creates a pooled object of type: ICsPooledObject
	*
	* @param Type
	* return		
	*/
	InterfaceContainerType* ConstructObject(const KeyType& Type)
	{
		checkf(IsValidKey(Type), TEXT("%s::ConstructObject: Type: %s is NOT a valid Key."), *Name, *KeyTypeToString(Type));

		CurrentConstructObjectType = Type;

		return Pools[Type]->ConstructObject();
	}

public:

	/**
	*
	*
	* @param Type
	* return		Event for OnConstructObject for Type.
	*/
	FORCEINLINE TMulticastDelegate<void, const InterfaceContainerType*>& GetOnConstructObject_Event(const KeyType& Type)
	{
		checkf(IsValidKey(Type), TEXT("%s::GetOnConstructObject_Event: Type: %s is NOT a valid Key."), *Name, *KeyTypeToString(Type));

		return Pools[Type]->OnConstructObject_Event;
	}

public:

	/**
	*
	*
	* @param Type
	* return
	*/
	TBaseDelegate<InterfaceContainerType*, const KeyType& /*Type*/> ConstructContainer_Impl;

private:

	InterfaceContainerType* ConstructContainer_Internal()
	{
		return ConstructContainer_Impl.Execute(CurrentConstructObjectType);
	}

protected:

	/**
	* Destroys or deletes the object.
	*
	* @param O
	*/
	virtual void DeconstructObject(const InterfaceContainerType* O)
	{
	}

	/**
	*
	*
	* @param O
	* return 
	*/
	FORCEINLINE FString GetObjectName(const InterfaceContainerType* O)
	{
		checkf(O, TEXT("%s::GetObjectName: O is NULL."), *Name);

		return O->GetObject()->GetName();
	}

#pragma endregion Object

// Pool
#pragma region
protected:

	FString FunctionNames[(uint8)ECsManagerPooledObjectMapFunctionNames::ECsManagerPooledObjectMapFunctionNames_MAX];

	TMap<KeyType, TManager_PooledObject_Abstract*> Pools;

public:

	/** 
	* 
	* @param Type
	* return		Object
	*/
	TBaseDelegate<TManager_PooledObject_Abstract* /*Object*/, const KeyType& /*Type*/> ConstructManagerPooledObjects_Impl;

	/**
	*
	*
	* @param Type
	* return
	*/
	TManager_PooledObject_Abstract* ConstructManagerPooledObjects(const KeyType& Type)
	{
		return new TManager_PooledObject_Abstract();
	}

	/**
	*
	*
	* @param Type
	* return
	*/
	TManager_PooledObject_Abstract* GetManagerPooledObjects(const KeyType& Type)
	{
		checkf(IsValidKey(Type), TEXT("%s::GetManagerPooledObjects: Type: %s is NOT a valid Key."), *Name, *KeyTypeToString(Type));

#if WITH_EDITOR
		TManager_PooledObject_Abstract** PoolPtr = Pools.Find(Type);

		checkf(PoolPtr, TEXT("%s::GetManagerPooledObjects: No Pool found for Type: %s. Call CreatePool."), *Name, *KeyTypeToString(Type));

		return *PoolPtr;
#else
		return Pools[Type];
#endif // #if WITH_EDITOR
	}

	/** Event called after constructing an Object of specified Type when creating a pool. 
	*
	* @param Type
	* @param Object
	*/
	TMulticastDelegate<void, const KeyType& /*Type*/, const InterfaceContainerType* /*Object*/> OnConstructObject_Event;

protected:

	void OnConstructObject(const InterfaceContainerType* Object)
	{
		OnConstructObject_Event.Broadcast(CurrentCreatePoolType, Object);
	}

public:

	/**
	*
	*
	* @param Params
	* @param Type
	* @param Size
	*/
	void CreatePool(const FCsManagerPooledObjectParams& Params, const KeyType& Type, const int32& Size)
	{
		checkf(IsValidKey(Type), TEXT("%s::CreatePool: Type: %s is NOT a valid Key."), *Name, *KeyTypeToString(Type));

		TManager_PooledObject_Abstract** PoolPtr = Pools.Find(Type);
		TManager_PooledObject_Abstract* Pool	 = nullptr;

		bool PoolCreated = false;

		if (!PoolPtr)
		{
			Pool = ConstructManagerPooledObjects_Impl.Execute(Type);

			Pool->LogTransaction_Impl = LogTransaction_Impl;

			Pool->ConstructContainer_Impl.BindRaw(this, &TCsManager_PooledObject_Map<InterfaceType, InterfaceContainerType, PayloadType, KeyType>::ConstructContainer_Internal);
			Pool->ConstructPayload_Impl.BindRaw(this, &TCsManager_PooledObject_Map<InterfaceType, InterfaceContainerType, PayloadType, KeyType>::ConstructPayload_Internal);
			
			// Bind the appropriate Script delegates.
			Pool->Script_GetCache_Impl			= Script_GetCache_Impl;
			Pool->Script_Allocate_Impl			= Script_Allocate_Impl;
			Pool->Script_Deallocate_Impl		= Script_Deallocate_Impl;
			Pool->Script_Update_Impl			= Script_Update_Impl;
			Pool->Script_OnConstructObject_Impl = Script_OnConstructObject_Impl;

			// Create pool
			if (Params.bCreatePool)
			{
				CurrentCreatePoolType = Type;

				// Add delegates to capture events when calling CreatePool

					// Bind to OnConstructObject so the event OnConstructObject_Event can properly broadcast events.
				FDelegateHandle OnConstructObjectHandle = Pool->OnConstructObject_Event.AddRaw(this, &TCsManager_PooledObject_Map<InterfaceType, InterfaceContainerType, PayloadType, KeyType>::OnConstructObject);
					// Bind to OnAddToPool so the event OnAddToPool_Event can properly broadcast events.
				FDelegateHandle OnAddToPoolHandle = Pool->OnAddToPool_Event.AddRaw(this, &TCsManager_PooledObject_Map<InterfaceType, InterfaceContainerType, PayloadType, KeyType>::OnCreatePool_AddToPool);

				Pool->Init(Params);

				// Remove any delegates used to capture events when calling CreatePool
				Pool->OnConstructObject_Event.Remove(OnConstructObjectHandle);
				Pool->OnAddToPool_Event.Remove(OnAddToPoolHandle);
			}
			else
			{
				Pool->Init(Params);
			}

			PoolCreated = Params.bCreatePool;

			Pools.Add(Type, Pool);
		}
		else
		{
			Pool = *PoolPtr;

			Pool->Shutdown();

			// Log Warning
		}

		// If CreatePool was NOT called via Init
		if (!PoolCreated)
		{
			CurrentCreatePoolType = Type;

			// Add delegates to capture events when calling CreatePool

				// Bind to OnConstructObject so the event OnConstructObject_Event can properly broadcast events.
			FDelegateHandle OnConstructObjectHandle = Pool->OnConstructObject_Event.AddRaw(this, &TCsManager_PooledObject_Map<InterfaceType, InterfaceContainerType, PayloadType, KeyType>::OnConstructObject);
				// Bind to OnAddToPool so the event OnAddToPool_Event can properly broadcast events.
			FDelegateHandle OnAddToPoolHandle = Pool->OnAddToPool_Event.AddRaw(this, &TCsManager_PooledObject_Map<InterfaceType, InterfaceContainerType, PayloadType, KeyType>::OnCreatePool_AddToPool);

			Pool->CreatePool(Size);

			// Remove any delegates used to capture events when calling CreatePool
			Pool->OnConstructObject_Event.Remove(OnConstructObjectHandle);
			Pool->OnAddToPool_Event.Remove(OnAddToPoolHandle);
		}
		else
		{
			Pool->CreatePool(Size);
		}

		// Bind to OnUpdate_Pool_Object so the event OnUpdate_Object_Event can properly broadcast events.
		Pool->OnUpdate_Object_Event.AddRaw(this, &TCsManager_PooledObject_Map<InterfaceType, InterfaceContainerType, PayloadType, KeyType>::OnUpdate_Pool_Object);
	}

	/**
	*
	*
	* @param Params
	* @param Type
	* @param Size
	*/
	virtual void CreatePool(const KeyType& Type, const int32& Size)
	{
		checkf(IsValidKey(Type), TEXT("%s::CreatePool: Type: %s is NOT a valid Key."), *Name, *KeyTypeToString(Type));

		FCsManagerPooledObjectParams Params;
		Params.Name		= Name + TEXT("_") + KeyTypeToString(Type);
		Params.World	= GetCurrentWorld();
		Params.LogType  = LogType;

		CreatePool(Params, Type, Size);
	}

	/** Event called after adding an Object to the pool of specified Type when creating a pool. 
	*
	* @param Type
	* @param Object
	*/
	TMulticastDelegate<void, const KeyType& /*Type*/, const InterfaceContainerType* /*Object*/> OnCreatePool_AddToPool_Event;

private:

	KeyType CurrentCreatePoolType;

	void OnCreatePool_AddToPool(const InterfaceContainerType* Object)
	{
		OnCreatePool_AddToPool_Event.Broadcast(CurrentCreatePoolType, Object);
		OnAddToPool_Event.Broadcast(CurrentCreatePoolType, Object);
	}

	// Add
#pragma region
public:

		// Pool
#pragma region
public:

	/**
	* Adds an Object to the pool for the appropriate Type.
	*  The Object must implement the interface: ICsPooledObject.
	*
	* @param Type				Type of pool to add the Object to.
	* @param InterfaceObject	Object that implements the interface: ICsPooledObject.
	* @param Object				UObject reference.
	* return					Container holding a reference to a pooled object.
	*							Pooled Object implements the interface: ICsPooledObject.
	*/
	const InterfaceContainerType* AddToPool(const KeyType& Type, InterfaceType* InterfaceObject, UObject* Object)
	{
		const InterfaceContainerType* O = GetManagerPooledObjects(Type)->AddToPool(InterfaceObject, Object);

		OnAddToPool_Event.Broadcast(Type, O);
		 
		return O;
	}

	/**
	* Adds an Object to the pool for the appropriate Type.
	*  Object must implement the interface: ICsPooledObject.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object that implements the interface: ICsPooledObject.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsPooledObject.
	*/
	const InterfaceContainerType* AddToPool(const KeyType& Type, InterfaceType* Object)
	{
		return AddToPool(Type, Object, Object->_getUObject());
	}

	/**
	* Adds an Object to the pool for the appropriate Type.
	*  Object must implement the interface: ICsPooledObject or the UClass 
	*  associated with the Object have ImplementsInterface(UCsPooledObject::StaticClass()) == true.
	*
	* @param Type		Type of the pool to add the object to.
	* @param Object		Object or Object->GetClass() that implements the interface: ICsPooledObject.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object or UClass associated with Pooled Object implements
	*					the interface: ICsPooledObject.
	*/
	const InterfaceContainerType* AddToPool(const KeyType& Type, UObject* Object)
	{
		return AddToPool(Type, nullptr, Object);
	}

	template<typename ContainerType>
	const ContainerType* AddToPool(const KeyType& Type, UObject* Object)
	{
		static_assert(std::is_base_of<InterfaceContainerType, ContainerType>(), "");
	
		return static_cast<const ContainerType*>(AddToPool(Type, Object));
	}

	/**
	* Event called after adding an Object to the pool of specified Type. 
	*
	* @param Type
	* @param Object
	*/
	TMulticastDelegate<void, const KeyType& /*Type*/, const InterfaceContainerType* /*Object*/> OnAddToPool_Event;

#pragma endregion Pool

		// Allocated Objects
#pragma region
public:

	/**
	* Adds an Object to the allocated objects for the appropriate Type.
	* If the Object is NOT added to the pool, add it to the pool.
	*  Object must implement the interface: ICsPooledObject.
	*
	* @param Type				Type of pool to add the Object to.
	* @param InterfaceObject	Object that implements the interface: ICsPooledObject.
	* @param Object				UObject reference.
	* return					Container holding a reference to a pooled object.
	*							Pooled Object implements the interface: ICsPooledObject.
	*/
	const InterfaceContainerType* AddToAllocatedObjects(const KeyType& Type, InterfaceType* InterfaceObject, UObject* Object)
	{
		checkf(Object, TEXT("%s::AddToAllocatedObjects: Object is NULL."), *Name);

		const InterfaceContainerType* O = GetManagerPooledObjects(Type)->AddToAllocatedObjects(InterfaceObject, Object);

		OnAddToAllocatedObjects_Event.Broadcast(Type, O);

		return O;
	}

	/**
	* Adds an Object to the allocated objects for the appropriate Type.
	* If the Object is NOT added to the pool, add it to the pool.
	*  Object must implement the interface: ICsPooledObject.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object that implements the interface: ICsPooledObject.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsPooledObject.
	*/
	const InterfaceContainerType* AddToAllocatedObjects(const KeyType& Type, InterfaceType* Object)
	{
		checkf(Object, TEXT("%s::AddToAllocatedObjects: Object is NULL."));

		return AddToAllocatedObjects(Type, Object, Object->_getUObject());
	}

	/**
	* Adds an Object to the allocated objects for the appropriate Type.
	* If the Object is NOT added to the pool, add it to the pool.
	*  Object must implement the interface: ICsPooledObject or the UClass
	*  associated with the Object have ImplementsInterface(UCsPooledObject::StaticClass()) == true.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object or Object->GetClass() that implements the interface: ICsPooledObject.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object or UClass associated with Pooled Object implements
	*					the interface: ICsPooledObject.
	*/
	const InterfaceContainerType* AddToAllocatedObjects(const KeyType& Type, UObject* Object)
	{
		return AddToAllocatedObjects(Type, nullptr, Object);
	}

	/** 
	* Event called after AddToAllocatedObjects has completed. 
	*
	* @param Type
	* @param Object
	*/
	TMulticastDelegate<void, const KeyType& /*Type*/, const InterfaceContainerType* /*Object*/> OnAddToAllocatedObjects_Event;

#pragma endregion Allocated Objects

#pragma endregion Add

public:

	/**
	* Get the pool for the appropriate Type.
	*  Pool is an array of containers holding references to objects that 
	*  implement the interface: ICsPooledObject.
	*
	* @param Type	Type of pool to get.
	* return		Pool associated with the type.
	*/
	FORCEINLINE const TArray<InterfaceContainerType*>& GetPool(const KeyType& Type)
	{
		return GetManagerPooledObjects(Type)->GetPool();
	}

	/**
	* Get the allocated objects for the appropriate Type.
	*  Allocated Objects are an array of containers holding references to objects that
	*  implement the interface: ICsPooledObject.
	*
	* @param Type	Type of allocated objects to get.
	* return		Allocated Objects associated with the Type.
	*/
	FORCEINLINE const TArray<InterfaceContainerType*>& GetAllocatedObjects(const KeyType& Type)
	{
		return GetManagerPooledObjects(Type)->GetAllocatedObjects();
	}

	/**
	* Get the number of elements in the pool for the appropriate Type.
	*
	*
	* @param Type	Type of pool.
	* return		Number of elements in the pool for the associated Type.
	*/
	FORCEINLINE const int32& GetPoolSize(const KeyType& Type)
	{
		return GetManagerPooledObjects(Type)->GetPoolSize();
	}

	/**
	* Get the number of allocated objects for the appropriate Type.
	*
	* @param Type	Type of allocated objects.
	* return		Number of allocated objects for the associated Type.
	*/ 
	FORCEINLINE int32 GetAllocatedObjectsSize(const KeyType& Type)
	{
		return GetManagerPooledObjects(Type)->GetAllocatedObjectsSize();
	}

	/**
	* Get whether all elements in the pool for the appropriate Type 
	* have been allocated.
	*
	@ @param Type	Type of pool to check against.
	* return		All elements allocated or not.
	*/
	FORCEINLINE bool IsExhausted(const KeyType& Type)
	{
		return GetManagerPooledObjects(Type)->IsExhausted();
	}

	// Find
#pragma region
public:

	/**
	* Find the container holding reference to a pooled object from the pool 
	* for the appropriate Type by Index.
	*
	* @param Type	Type of pool to add the Object to.
	* @param Index	Index of the pooled object.
	* return		Container holding a reference to a pooled object.
	*				Pooled Object implements the interface: ICsPooledObject.
	*/
	FORCEINLINE const InterfaceContainerType* FindObject(const KeyType& Type, const int32& Index)
	{
		return GetManagerPooledObjects(Type)->FindObject(Index);
	}

	/**
	* Find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by Interface.
	*  Object must implement the interface: ICsPooledObject.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object of interface type: ICsPooledObject.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsPooledObject.
	*/
	FORCEINLINE const InterfaceContainerType* FindObject(const KeyType& Type, InterfaceType* Object)
	{
		return GetManagerPooledObjects(Type)->FindObject(Object);
	}

	/**
	* Find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by UObject.
	*  Object must implement the interface: ICsPooledObject or the UClass
	*  associated with the Object have ImplementsInterface(UCsPooledObject::StaticClass()) == true.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object or Object->GetClass() that implements the interface: ICsPooledObject.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object or UClass associated with Pooled Object implements
	*					the interface: ICsPooledObject.
	*/
	FORCEINLINE const InterfaceContainerType* FindObject(const KeyType& Type, UObject* Object)
	{
		return GetManagerPooledObjects(Type)->FindObject(Object);
	}

	/**
	* Safely, via checks, find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by Index.
	*
	* @param Type	Type of pool to add the Object to.
	* @param Index	Index of the pooled object.
	* return		Container holding a reference to a pooled object.
	*				Pooled Object implements the interface: ICsPooledObject.
	*/
	FORCEINLINE const InterfaceContainerType* FindSafeObject(const KeyType& Type, const int32& Index)
	{
		return GetManagerPooledObjects(Type)->FindSafeObject(Index);
	}

	/**
	* Safely, via checks, find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by the Interface.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object that implements the interface: ICsPooledObject.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsPooledObject.
	*/
	FORCEINLINE const InterfaceContainerType* FindSafeObject(const KeyType& Type, InterfaceType* Object)
	{
		return GetManagerPooledObjects(Type)->FindSafeObject(Object);
	}

	/**
	* Safely, via checks, find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by the UObject.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object or Object->GetClass() that implements the interface: ICsPooledObject.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object or UClass associated with Pooled Object implements
	*					the interface: ICsPooledObject.
	*/
	FORCEINLINE const InterfaceContainerType* FindSafeObject(const KeyType& Type, UObject* Object)
	{
		return GetManagerPooledObjects(Type)->FindObject(Object);
	}

#pragma endregion Find

#pragma endregion Pool

// Update
#pragma region
public:

	virtual void Update(const FCsDeltaTime& DeltaTime)
	{
		for (TPair<KeyType, TManager_PooledObject_Abstract*>& Pair : Pools)
		{
			CurrentUpdatePoolType = Pair.Key;

			OnPreUpdate_Pool_Impl.ExecuteIfBound(CurrentUpdatePoolType);

			Pair.Value->Update(DeltaTime);

			OnPostUpdate_Pool_Impl.ExecuteIfBound(CurrentUpdatePoolType);
		}
	}

	/**
	* Delegated called when before a pool is updated.
	*
	* @param KeyType	Current type of pool.
	*/
	TBaseDelegate<void, const KeyType& /*Type*/> OnPreUpdate_Pool_Impl;

	/**
	* Event called when updating a pooled object.
	*
	* @param Type		Current type of pool.
	* @param Object		Container holding a pooled object.
	*/
	TMulticastDelegate<void, const KeyType& /*Type*/, const InterfaceContainerType* /*Object*/> OnUpdate_Object_Event;

	/**
	* Delegate called after a pool is updated.
	*
	* @param KeyType	Current type of pool.
	*/
	TBaseDelegate<void, const KeyType& /*Type*/> OnPostUpdate_Pool_Impl;

private:

	KeyType CurrentUpdatePoolType;

	void OnUpdate_Pool_Object(const InterfaceContainerType* Object)
	{
		OnUpdate_Object_Event.Broadcast(CurrentCreatePoolType, Object);
	}

#pragma endregion Update

// Payload
#pragma region
private:

	KeyType CurrentConstructPayloadType;

public:

	/**
	* Create a number (Size) of payload objects for the appropriate Type.
	*  Payload implements the interface: ICsPooledObjectPayload.
	*
	* @param Type	Type of payload.
	* @param Size	Number of payload objects to create.
	*/
	void ConstructPayloads(const KeyType& Type, const int32& Size)
	{
		CurrentConstructPayloadType = Type;

		GetManagerPooledObjects(Type)->ConstructPayloads(Size);
	}

	/**
	*
	*
	* @param Type
	* return
	*/
	TBaseDelegate<PayloadType*, const KeyType& /*Type*/> ConstructPayload_Impl;

private:

	PayloadType* ConstructPayload_Internal()
	{
		return ConstructPayload_Impl.Execute(CurrentConstructPayloadType);
	}

public:

	/**
	* Delete all payload objects for the appropriate Type.
	*
	* @param Type	Type of payload.
	*/
	void DeconstructPayloads(const KeyType& Type)
	{
		GetManagerPooledObjects(Type)->DeconstructPayloads();
	}

	/**
	* Get a payload object from a pool of payload objects for the appropriate Type.
	*  Payload implements the interface: ICsPooledObjectPayload and PayloadType.
	*
	* @param Type	Type of payload.
	* return		Payload that implements the interface: ICsPooledObjectPayload
					and PayloadType.
	*/
	FORCEINLINE PayloadType* AllocatePayload(const KeyType& Type)
	{
		return GetManagerPooledObjects(Type)->AllocatePayload();
	}

	/**
	* Get a payload object from a pool of payload objects for the appropriate Type.
	*  Payload implements the interface: ICsPooledObjectPayload and PayloadType
	*
	* @param Context	Calling context.
	* @param Type		Type of payload.
	* return			PayloadTypeImpl that implements the interface: ICsPooledObjectPayload
	*					and PayloadType.
	*/
	template<typename PayloadTypeImpl>
	FORCEINLINE PayloadTypeImpl* AllocatePayload(const FString& Context, const KeyType& Type)
	{
		return GetManagerPooledObjects(Type)->AllocatePayload<PayloadTypeImpl>(Context);
	}

	/**
	* Get a payload object from a pool of payload objects for the appropriate Type.
	*  Payload implements the interface: ICsPooledObjectPayload and PayloadType
	*
	* @param Type	Type of payload.
	* return		PayloadTypeImpl that implements the interface: ICsPooledObjectPayload
	*				and PayloadType.
	*/
	template<typename PayloadTypeImpl>
	FORCEINLINE PayloadTypeImpl* AllocatePayload(const KeyType& Type)
	{
		return GetManagerPooledObjects(Type)->AllocatePayload<PayloadTypeImpl>();
	}

	/**
	*
	*
	* @param Type
	* return
	*/
	FORCEINLINE const int32& GetPayloadSize(const KeyType& Type)
	{
		return GetManagerPooledObjects(Type)->GetPayloadSize();
	}

#pragma endregion Payload

// Log
#pragma region
public:

	TBaseDelegate<void, const FString& /*Context*/, const ECsPoolTransaction& /*Transaction*/, const InterfaceContainerType* /*Object*/> LogTransaction_Impl;

protected:

	FECsCVarLog LogType;

#pragma endregion Log

// Spawn
#pragma region
public:

	/**
	* Spawn a pooled object from a pool for the appropriate Type with 
	* information stored in the Payload.
	*
	* @param Type		Type of pool to spawn from.
	* @param Payload	Payload to use when spawning from pool.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsPooledObject.
	*/
	const InterfaceContainerType* Spawn(const KeyType& Type, PayloadType* Payload)
	{
		const InterfaceContainerType* Object = GetManagerPooledObjects(Type)->Spawn(Payload);

		OnSpawn_Event.Broadcast(Type, Object);
		return Object;
	}

	template<typename OtherContainerType, typename OtherPayloadType>
	const OtherContainerType* Spawn(const KeyType& Type, OtherPayloadType* Payload)
	{
		const OtherContainerType* Object = GetManagerPooledObjects(Type)->Spawn<OtherContainerType, OtherPayloadType>(Payload);

		OnSpawn_Event.Broadcast(Type, static_cast<const InterfaceContainerType*>(Object));
		return Object;
	}

	/** 
	*
	*
	* @param Type
	* @param Object 
	*/
	TMulticastDelegate<void, const KeyType& /*Type*/, const InterfaceContainerType* /*Object*/> OnSpawn_Event;

#pragma endregion Spawn

// Destroy
#pragma region
public:

	/**
	* Destroy a pooled object with specified Index from a pool for the
	* appropriate Type.
	*  NOTE: This process is O(n). Consider queuing the deallocate.
	*
	* @param Type	Type of pool to destroy from.
	* @param Index	Index of the object in the pool.
	* return		Whether successfully destroyed the object or not.
	*/
	bool Destroy(const KeyType& Type, const int32& Index)
	{
		TManager_PooledObject_Abstract* Pool = GetManagerPooledObjects(Type);

		if (Pool->Destroy(Index))
		{
			const InterfaceContainerType* Object = Pool->FindObject(Index);

			OnDestroy_Event.Broadcast(Type, Object);
			return true;
		}
		return false;
	}

	/**
	* Destroy an object from a pool for the appropriate Type.
	*  Object must implement the interface: ICsPooledObject.
	*  NOTE: This process is O(n). Consider queuing the deallocate.
	*
	* @param Type		Type of pool to destroy from.
	* @param Object		Object that implements the interface: ICsPooledObject.
	* return			Whether successfully destroyed the object or not.
	*/
	bool Destroy(const KeyType& Type, InterfaceType* Object)
	{
		checkf(IsValidKey(Type), TEXT("%s::Destroy: Type: %s is NOT a valid Key."), *Name, *KeyTypeToString(Type));

		return Destroy(Type, Object->_getUObject());
	}

	/**
	* Destroy an object from a pool for the appropriate Type.
	*  Object must implement the interface: ICsPooledObject or the UClass
	*  associated with the Object have ImplementsInterface(UCsPooledObject::StaticClass()) == true.
	*  NOTE: This process is O(n). Consider queuing the deallocate.
	*
	* @param Type		Type of pool to destroy from.
	* @param Object		Object or Object->GetClass() that implements the interface: ICsPooledObject.
	* return			Whether successfully destroyed the object or not.
	*/
	bool Destroy(const KeyType& Type, UObject* Object)
	{
		checkf(Object, TEXT("%s::Destroy: Object is NULL."), *Name);

		TManager_PooledObject_Abstract* Pool = GetManagerPooledObjects(Type);

		if (Pool->Destroy(Object))
		{
			const InterfaceContainerType* O = Pool->FindObject(Object);

			OnDestroy_Event.Broadcast(Type, O);
			return true;
		}
		return false;
	}

	/**
	* Destroy an object.
	*  Object must implement the interface: ICsPooledObject.
	*  NOTE: This process is O(n). Consider queueing the deallocate.
	*
	* @param Object		Object that implements the interface: ICsPooledObject.
	* return			Whether successfully destroyed the object or not.
	*/
	bool Destroy(InterfaceType* Object)
	{
		checkf(Object, TEXT("%s::Destroy: Object is NULL."), *Name);

		return Destroy(Object->_getUObject());
	}

	/**
	* Destroy an object.
	*  Object must implement the interface: ICsPooledObject or the UClass
	*  associated with the Object have ImplementsInterface(UCsPooledObject::StaticClass()) == true.
	*  NOTE: This process is O(n). Consider queueing the deallocate.
	*
	* @param Object		Object or Object->GetClass() that implements the interface: ICsPooledObject.
	* return			Whether successfully destroyed the object or not.
	*/
	bool Destroy(UObject* Object)
	{
		checkf(Object, TEXT("%s::Destroy: Object is NULL."), *Name);

		for (TPair<KeyType, TManager_PooledObject_Abstract*>& Pair : Pools)
		{
			const KeyType& Key					 = Pair.Key;
			TManager_PooledObject_Abstract* Pool = Pair.Value;

			const InterfaceContainerType* O = Pool->FindSafeObject(Object);

			if (!O)
				continue;

			const int32& Index = O->GetCache()->GetIndex();

			if (Pool->Destroy(Index))
			{
				OnDestroy_Event.Broadcast(Key, O);
				return true;
			}
		}
		return false;
	}

	/** 
	*
	* 
	* @param Type
	* @param Object
	*/
	TMulticastDelegate<void, const KeyType& /*Type*/, const InterfaceContainerType* /*Object*/> OnDestroy_Event;

#pragma endregion Destroy

// Script
#pragma region
public:

	// ICsPooledObject

	FCsPooledObject::FScript_GetCache Script_GetCache_Impl;

	FCsPooledObject::FScript_Allocate Script_Allocate_Impl;

	FCsPooledObject::FScript_Deallocate Script_Deallocate_Impl;

	// ICsUpdate

	FCsPooledObject::FScript_Update Script_Update_Impl;

	// ICsOnConstructObject

	FCsPooledObject::FScript_OnConstructObject Script_OnConstructObject_Impl;

#pragma endregion Script
};
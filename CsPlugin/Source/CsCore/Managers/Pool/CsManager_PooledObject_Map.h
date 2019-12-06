// Copyright 2017 Respawn Entertainment, Inc. All rights reserved.

#pragma once
#include "Managers/Pool/CsManager_PooledObject.h"
#include "Managers/Pool/CsPooledObject.h"
#include "CsCVars.h"

// ICsManager_PooledObject_Map
#pragma region

class CSCORE_API ICsManager_PooledObject_Map
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

template<typename KeyType>
class TCsManager_PooledObject_Map : public ICsManager_PooledObject_Map
{
	
// Structs
#pragma region
public:

	struct FCsManagerPooledObjectMapParams
	{
	public:

		FString Name;

		UWorld* World;

		FECsCVarLog LogType;

		TMap<KeyType, FCsManagerPooledObjectConstructParams> ConstructParams;

		FCsManagerPooledObjectMapParams() :
			Name(),
			World(nullptr),
			LogType(),
			ConstructParams()
		{
		}
	};

#pragma endregion Structs

public:
	TCsManager_PooledObject_Map()
	{
		Name = NCsCached::Str::Empty;
		CurrentWorld = nullptr;

		ConstructParams.Reset();

		ConstructManagerPooledObjects_Impl.BindRaw(this, &TCsManager_PooledObject_Map<KeyType>::ConstructManagerPooledObjects);

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

		ConstructParams = Params.ConstructParams;

		for (TPair<KeyType, FCsManagerPooledObjectConstructParams>& Pair : ConstructParams)
		{
			const KeyType& Key = Pair.Key;

			FCsManagerPooledObjectParams P;
			P.Name			  = Name + TEXT("_") + KeyTypeToString(Key);
			P.World			  = Params.World;
			P.LogType		  = LogType;
			P.ConstructParams = Pair.Value;

			ICsManager_PooledObject* Pool = ConstructManagerPooledObjects_Impl.Execute(Key);
			Pool->Init(P);

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
		for (TPair<KeyType, ICsManager_PooledObject*>& Pair : Pools)
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

		for (TPair<KeyType, ICsManager_PooledObject*>& Pair : Pools)
		{
			ICsManager_PooledObject* Pool = Pair.Value;
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

// Object
#pragma region
protected:

	/**
	* Creates a pooled object of type ICsPooledObject
	*/
	virtual FCsPooledObject ConstructObject(const KeyType& Type)
	{
		return Pools[Type]->ConstructObject();
	}

protected:

	/**
	* Destroys or deletes the object.
	*
	* @param O
	*/
	virtual void DeconstructObject(const FCsPooledObject& O)
	{
	}

	/**
	*
	*
	* @param O
	* return 
	*/
	virtual FString GetObjectName(const FCsPooledObject& O)
	{
		return NCsCached::Str::Empty;
	}

#pragma endregion Object

// Pool
#pragma region
protected:

	FString FunctionNames[(uint8)ECsManagerPooledObjectMapFunctionNames::ECsManagerPooledObjectMapFunctionNames_MAX];

	TMap<KeyType, FCsManagerPooledObjectConstructParams> ConstructParams;

	TMap<KeyType, ICsManager_PooledObject*> Pools;

public:

	/** */
	TBaseDelegate<ICsManager_PooledObject* /*Object*/, const KeyType& /*Type*/> ConstructManagerPooledObjects_Impl;

	/**
	*
	*
	* @param Type
	* return
	*/
	ICsManager_PooledObject* ConstructManagerPooledObjects(const KeyType& Type)
	{
		return new FCsManager_PooledObject();
	}

	/**
	*
	*
	* @param Type
	* return
	*/
	ICsManager_PooledObject* GetManagerPooledObjects(const KeyType& Type)
	{
		return CheckAndAddType(Type);
	}

	/**
	*
	*
	* @param Params
	* @param Type
	* @param Size
	*/
	virtual void CreatePool(const FCsManagerPooledObjectParams& Params, const KeyType& Type, const int32& Size)
	{
		ICsManager_PooledObject** PoolPtr = Pools.Find(Type);
		ICsManager_PooledObject* Pool	   = nullptr;

		if (!PoolPtr)
		{
			Pool = ConstructManagerPooledObjects_Impl.Execute(Type);

			Pool->Init(Params);
			Pools.Add(Type, Pool);
		}
		else
		{
			Pool = *PoolPtr;

			Pool->Shutdown();

			// Log Warning
		}

		// Bind the appropriate Script delegates.
		Pool->GetScript_GetCache_Impl() = Script_GetCache_Impl;
		Pool->GetScript_Allocate_Impl() = Script_Allocate_Impl;
		Pool->GetScript_Deallocate_Impl() = Script_Deallocate_Impl;

		// Bind to OnAddToPool so the event OnAddToPool_Event can properly broadcast events.
		CurrentCreatePoolType = Type;
		FDelegateHandle Handle = Pool->GetOnAddToPool_Event().AddRaw(this, &TCsManager_PooledObject_Map<KeyType>::OnCreatePool_AddToPool);

		Pool->CreatePool(Size);

		Pool->GetOnAddToPool_Event().Remove(Handle);

		// Bind to OnUpdate_Pool_Object so the event OnUpdate_Object_Event can properly broadcast events.
		Pool->GetOnUpdate_Object_Event().AddRaw(this, &TCsManager_PooledObject_Map<KeyType>::OnUpdate_Pool_Object);
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
		FCsManagerPooledObjectParams Params;
		Params.Name		= Name + TEXT("_") + KeyTypeToString(Type);
		Params.World	= GetCurrentWorld();
		Params.LogType  = LogType;

		CreatePool(Params, Type, Size);
	}

	/** Event called after adding an Object to the pool of specified Type when creating a pool. */
	TMulticastDelegate<void, const KeyType& /*Type*/, const FCsPooledObject& /*Object*/> OnCreatePool_AddToPool_Event;

private:

	KeyType CurrentCreatePoolType;

	void OnCreatePool_AddToPool(const FCsPooledObject& Object)
	{
		OnCreatePool_AddToPool_Event.Broadcast(CurrentCreatePoolType, Object);
	}

private:

	/**
	*
	*
	* @param Type
	* return
	*/
	ICsManager_PooledObject* CheckAndAddType(const KeyType& Type)
	{
		ICsManager_PooledObject** PoolPtr = Pools.Find(Type);
		ICsManager_PooledObject* Pool     = nullptr;

		if (!PoolPtr)
		{
			Pool = new FCsManager_PooledObject();

			FCsManagerPooledObjectParams Params;
			Params.Name		= Name + TEXT("_") + KeyTypeToString(Type);
			Params.World	= GetCurrentWorld();
			Params.LogType	= LogType;

			Pool->Init(Params);
			Pools.Add(Type, Pool);

			// Bind the appropriate Script delegates.
			Pool->GetScript_GetCache_Impl() = Script_GetCache_Impl;
			Pool->GetScript_Allocate_Impl() = Script_Allocate_Impl;
			Pool->GetScript_Deallocate_Impl() = Script_Deallocate_Impl;

			// Bind to OnUpdate_Pool_Object so the event OnUpdate_Object_Event can properly broadcast events.
			Pool->GetOnUpdate_Object_Event().AddRaw(this, &TCsManager_PooledObject_Map<KeyType>::OnUpdate_Pool_Object);
		}
		else
		{
			Pool = *PoolPtr;
		}
		return Pool;
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
	* @param Type			Type of pool to add the Object to.
	* @param PooledObject	Object that implements the interface: ICsPooledObject.
	* @param Object			UObject reference.
	* return				Container holding a reference to a pooled object.
	*						Pooled Object implements the interface: ICsPooledObject.
	*/
	const FCsPooledObject& AddToPool(const KeyType& Type, ICsPooledObject* PooledObject, UObject* Object)
	{
		const FCsPooledObject& O = CheckAndAddType(Type)->AddToPool(PooledObject, Object);

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
	const FCsPooledObject& AddToPool(const KeyType& Type, ICsPooledObject* Object)
	{
		return AddToPool(Type, Object, nullptr);
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
	const FCsPooledObject& AddToPool(const KeyType& Type, UObject* Object)
	{
		const FCsPooledObject& O = CheckAndAddType(Type)->AddToPool(Object);

		OnAddToPool_Event.Broadcast(Type, O);

		return O;
	}

	/** Event called after adding an Object to the pool of specified Type. */
	TMulticastDelegate<void, const KeyType& /*Type*/, const FCsPooledObject& /*Object*/> OnAddToPool_Event;

#pragma endregion Pool

		// Allocated Objects
#pragma region
public:

	/**
	* Adds an Object to the allocated objects for the appropriate Type.
	* If the Object is NOT added to the pool, add it to the pool.
	*  Object must implement the interface: ICsPooledObject.
	*
	* @param Type			Type of pool to add the Object to.
	* @param PooledObject	Object that implements the interface: ICsPooledObject.
	* @param Object			UObject reference.
	* return				Container holding a reference to a pooled object.
	*						Pooled Object implements the interface: ICsPooledObject.
	*/
	const FCsPooledObject& AddToAllocatedObjects(const KeyType& Type, ICsPooledObject* PooledObject, UObject* Object)
	{
		checkf(PooledObject, TEXT("%s::AddToAllocatedObjects: PooledObject is NULL."), *Name);

		checkf(PooledObject == Cast<ICsPooledObject>(Object), TEXT("%s::AddToAllocatedObjects: PooledObject != Object. These must be the SAME object."), *Name);

		ICsManager_PooledObject* Pool = CheckAndAddType(Type);

		const int32& Index = PooledObject->GetCache()->GetIndex();

		if (Index == INDEX_NONE)
		{
			Pool->AddToPool(PooledObject, Object);
		}

		checkf(Index < Pool->GetPoolSize(), TEXT("%::AddToAllocatedObjects: PooledObject is in another pool."), *Name);

		const FCsPooledObject& O = Pool->AddToAllocatedObjects(PooledObject, Object);

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
	const FCsPooledObject& AddToAllocatedObjects(const KeyType& Type, ICsPooledObject* Object)
	{
		return AddToAllocatedObjects(Type, Object, nullptr);
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
	const FCsPooledObject& AddToAllocatedObjects(const KeyType& Type, UObject* Object)
	{
		checkf(Object, TEXT("%s::AddToAllocatedObjects: Object is NULL."), *Name);

		ICsManager_PooledObject* Pool = CheckAndAddType(Type);

		const FCsPooledObject& FoundObject = Pool->FindSafeObject(Object);

		if (!FoundObject.IsValid())
		{
			Pool->AddToPool(Object);
		}

		const FCsPooledObject& O = Pool->AddToAllocatedObjects(Object);

		OnAddToAllocatedObjects_Event.Broadcast(Type, O);

		return O;
	}

	/** Event called after AddToAllocatedObjects has completed. */
	TMulticastDelegate<void, const KeyType& /*Type*/, const FCsPooledObject& /*Object*/> OnAddToAllocatedObjects_Event;

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
	FORCEINLINE const TArray<FCsPooledObject>& GetPool(const KeyType& Type)
	{
		return CheckAndAddType(Type)->GetPool();
	}

	/**
	* Get the allocated objects for the appropriate Type.
	*  Allocated Objects are an array of containers holding references to objects that
	*  implement the interface: ICsPooledObject.
	*
	* @param Type	Type of allocated objects to get.
	* return		Allocated Objects associated with the Type.
	*/
	FORCEINLINE const TArray<FCsPooledObject>& GetAllocatedObjects(const KeyType& Type)
	{
		return CheckAndAddType(Type)->GetAllocatedObjects();
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
		return CheckAndAddType(Type)->GetPoolSize();
	}

	/**
	* Get the number of allocated objects for the appropriate Type.
	*
	* @param Type	Type of allocated objects.
	* return		Number of allocated objects for the associated Type.
	*/ 
	FORCEINLINE int32 GetAllocatedObjectsSize(const KeyType& Type)
	{
		return CheckAndAddType(Type)->GetAllocatedObjectsSize();
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
		return CheckAndAddType(Type)->IsExhausted();
	}

	// Find
#pragma region
public:



#pragma endregion Find

#pragma endregion Pool

// Update
#pragma region
public:

	virtual void Update(const float& DeltaTime)
	{
		for (TPair<KeyType, ICsManager_PooledObject*>& Pair : Pools)
		{
			CurrentUpdatePoolType = Pair.Key;

			OnPreUpdate_Pool_Impl.ExecuteIfBound(CurrentUpdatePoolType);

			Pair.Value->Update(DeltaTime);

			OnPostUpdate_Pool_Impl.ExecuteIfBound(CurrentUpdatePoolType);
		}
	}

	/**
	* Delegate type for updating before a pool is updated.
	*
	* @param KeyType	Current type of pool.
	*/
	DECLARE_DELEGATE_OneParam(FOnPreUpdate_Pool, const KeyType& /*Type*/);

	/** Delegate called before a pool is updated. */
	FOnPreUpdate_Pool OnPreUpdate_Pool_Impl;

	/**
	* Delegate type for updating a pooled object.
	*
	* @param Type		Current type of pool.
	* @param Object		Container holding a pooled object.
	*/
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnUpdate_Object, const KeyType& /*Type*/, const FCsPooledObject& /*Object*/);

	/** Event called when updating a pooled object. */
	FOnUpdate_Object OnUpdate_Object_Event;

	/**
	* Delegate type for updating after a pool is updated.
	*
	* @param KeyType	Current type of pool.
	*/
	DECLARE_DELEGATE_OneParam(FOnPostUpdate_Pool, const KeyType& /*Type*/);

	/** Delegate called after a pool is updated. */
	FOnPostUpdate_Pool OnPostUpdate_Pool_Impl;

private:

	KeyType CurrentUpdatePoolType;

	void OnUpdate_Pool_Object(const FCsPooledObject& Object)
	{
		OnUpdate_Object_Event.Broadcast(CurrentCreatePoolType, Object);
	}

#pragma endregion Update

// Payload
#pragma region
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
		CheckAndAddType(Type)->ConstructPayloads(Size);
	}

	/**
	* Delete all payload objects for the appropriate Type.
	*
	* @param Type	Type of payload.
	*/
	void DeconstructPayloads(const KeyType& Type)
	{
		CheckAndAddType(Type)->DeconstructPayloads();
	}

	/**
	* Get a payload object from a pool of payload objects for the appropriate Type.
	*  Payload implements the interface: ICsPooledObjectPayload.
	*
	* @param Type	Type of payload.
	* return		Payload that implements the interface: ICsPooledObjectPayload.
	*/
	FORCEINLINE ICsPooledObjectPayload* AllocatePayload(const KeyType& Type)
	{
		return CheckAndAddType(Type)->AllocatePayload();
	}

	template<typename PayloadType>
	FORCEINLINE PayloadType* AllocatePayload(const KeyType& Type)
	{
		static_assert(std::is_base_of<ICsPooledObjectPayload, PayloadType>(), "TCsManager_PooledObject_Map::AllocatePayload: PayloadType does NOT implement interface: ICsPooledObjectPayload.");

		return (PayloadType*)(AllocatePayload(Type));
	}

#pragma endregion Payload

// Log
#pragma region
protected:

	virtual void Log(const FString& InLog){}

	FECsCVarLog LogType;

	virtual void LogTransaction(const FString& FunctionName, const ECsPoolTransaction& Transaction, ICsPooledObject* O)
	{

	}

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
	virtual const FCsPooledObject& Spawn(const KeyType& Type, ICsPooledObjectPayload* Payload)
	{
		ICsManager_PooledObject* Pool = CheckAndAddType(Type);

		const FCsPooledObject& Object = Pool->Spawn(Payload);

		OnSpawn_Event.Broadcast(Type, Object);
		return Object;
	}

	/** */
	TMulticastDelegate<void, const KeyType& /*Type*/, const FCsPooledObject&> OnSpawn_Event;

#pragma endregion Spawn

// Destroy
#pragma region
public:

	/**
	* Destroy a pooled object with specified Index from a pool for the
	* appropriate Type.
	*
	* @param Type	Type of pool to destroy from.
	* @param Index	Index of the object in the pool.
	* return		Whether successfully destroyed the object or not.
	*/
	virtual bool Destroy(const KeyType& Type, const int32& Index)
	{
		ICsManager_PooledObject* Pool = CheckAndAddType(Type);

		if (Pool->Destroy(Index))
		{
			const FCsPooledObject& Object = Pool->FindObject(Index);

			OnDestroy_Event.Broadcast(Type, Object);
			return true;
		}
		return false;
	}

	/**
	* Destroy an object from a pool for the appropriate Type.
	*  Object must implement the interface: ICsPooledObject.
	*
	* @param Type		Type of pool to destroy from.
	* @param Object		Object that implements the interface: ICsPooledObject.
	* return			Whether successfully destroyed the object or not.
	*/
	virtual bool Destroy(const KeyType& Type, ICsPooledObject* Object)
	{
		ICsManager_PooledObject* Pool = CheckAndAddType(Type);

		if (Pool->Destroy(Object))
		{
			const FCsPooledObject& O = Pool->FindObject(Object);

			OnDestroy_Event.Broadcast(Type, O);
			return true;
		}
		return false;
	}

	/**
	* Destroy an object.
	*  Object must implement the interface: ICsPooledObject.
	*
	* @param Object		Object that implements the interface: ICsPooledObject.
	* return			Whether successfully destroyed the object or not.
	*/
	virtual bool Destroy(ICsPooledObject* Object)
	{
		for (TPair<KeyType, ICsManager_PooledObject*>& Pair : Pools)
		{
			const KeyType& Key			   = Pair.Key;
			ICsManager_PooledObject* Pool = Pair.Value;

			const int32& Index = Object->GetCache()->GetIndex();

			if (Index >= Pool->GetPoolSize())
				continue;

			if (Pool->Destroy(Object))
			{
				const FCsPooledObject& O = Pool->FindObject(Object);

				OnDestroy_Event.Broadcast(Key, O);
				return true;
			}
		}
		return false;
	}

	/** */
	TMulticastDelegate<void, const KeyType& /*Type*/, const FCsPooledObject& /*Object*/> OnDestroy_Event;

#pragma endregion Destroy

// Script
#pragma region
public:

	FCsPooledObject::FScript_GetCache Script_GetCache_Impl;

	FCsPooledObject::FScript_Allocate Script_Allocate_Impl;

	FCsPooledObject::FScript_Deallocate Script_Deallocate_Impl;

#pragma endregion Script
};
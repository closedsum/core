// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#pragma once
#include "Managers/Pool/CsPooledObject.h"
#include "CsCVars.h"
#include "Containers/CsDoubleLinkedList.h"

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

class UWorld;
class UObject;
class ICsPooledObject;

DECLARE_MULTICAST_DELEGATE_OneParam(FCsManagerPooledObject_OnAddToPool, const FCsPooledObject& /*Object*/);

DECLARE_DELEGATE_OneParam(FCsManagerPooledObject_ConstructPayloads, const int32& /*Size*/);

/**
*
*
* @param Object
*/
DECLARE_MULTICAST_DELEGATE_OneParam(FCsManagerPooledObject_OnUpdate_Object, const FCsPooledObject& /*Object*/);

class CSCORE_API ICsManager_PooledObject
{
public:

	virtual ~ICsManager_PooledObject() {}

	virtual void Init(const FCsManagerPooledObjectParams& Params)  = 0;

	virtual void Clear() = 0;
	virtual void Shutdown() = 0;

	virtual UWorld* GetCurrentWorld() = 0;

	virtual float GetCurrentTimeSeconds() = 0;

// Object
#pragma region
public:

	virtual FCsPooledObject ConstructObject() = 0;

	virtual void DeconstructObject(FCsPooledObject& Object) = 0;

	virtual FString GetObjectName(const FCsPooledObject& Object) = 0;

#pragma endregion Object

// Pool
#pragma region
public:

	virtual void CreatePool(const int32& Size) = 0;

	// Add
#pragma region
public:

		// Pool
#pragma region
public:

	virtual const FCsPooledObject& AddToPool(ICsPooledObject* PooledObject, UObject* Object) = 0;
	virtual const FCsPooledObject& AddToPool(ICsPooledObject* Object) = 0;
	virtual const FCsPooledObject& AddToPool(UObject* Object) = 0;

	virtual FCsManagerPooledObject_OnAddToPool& GetOnAddToPool_Event() = 0;

#pragma endregion Pool

		// Allocated Objects
#pragma region
public:

	virtual const FCsPooledObject& AddToAllocatedObjects(ICsPooledObject* PooledObject, UObject* Object) = 0;
	virtual const FCsPooledObject& AddToAllocatedObjects(ICsPooledObject* Object) = 0;
	virtual const FCsPooledObject& AddToAllocatedObjects(UObject* Object) = 0;

#pragma endregion Allocated Objects

#pragma endregion Add

public:

	virtual const TArray<FCsPooledObject>& GetPool() = 0;

	virtual const TArray<FCsPooledObject>& GetAllocatedObjects() = 0;

	virtual const int32& GetPoolSize() = 0;
	virtual int32 GetAllocatedObjectsSize() = 0;

	virtual bool IsExhausted() = 0;

	// Find
#pragma region
public:

	virtual const FCsPooledObject& FindObject(const int32& Index) = 0;
	virtual const FCsPooledObject& FindObject(ICsPooledObject* Object) = 0;
	virtual const FCsPooledObject& FindObject(UObject* Object) = 0;

	virtual const FCsPooledObject& FindSafeObject(const int32& Index) = 0;
	virtual const FCsPooledObject& FindSafeObject(ICsPooledObject* Object) = 0;
	virtual const FCsPooledObject& FindSafeObject(UObject* Object) = 0;

#pragma endregion Find

#pragma endregion Pool

// Update
#pragma region
public:

	virtual void Update(const float& DeltaTime) = 0;

	virtual FCsManagerPooledObject_OnUpdate_Object& GetOnUpdate_Object_Event() = 0;

#pragma endregion Update

// Payload
#pragma region
public:

	virtual void ConstructPayloads(const int32& Size) = 0;

	virtual FCsManagerPooledObject_ConstructPayloads& GetConstructPayloads_Impl() = 0;

	virtual void DeconstructPayloads() = 0;

	virtual ICsPooledObjectPayload* AllocatePayload() = 0;

#pragma endregion Payload

// Spawn
#pragma region
public:

	virtual const FCsPooledObject& Spawn(ICsPooledObjectPayload* Payload) = 0;

#pragma endregion Spawn

// Destroy
#pragma region
public:

	virtual bool Destroy(const int32& Index) = 0;
	virtual bool Destroy(ICsPooledObject* Object) = 0;

#pragma endregion Destroy

// Script
#pragma region
public:

	virtual FCsPooledObject::FScript_GetCache& GetScript_GetCache_Impl() = 0;

	virtual FCsPooledObject::FScript_Allocate& GetScript_Allocate_Impl() = 0;

	virtual FCsPooledObject::FScript_Deallocate& GetScript_Deallocate_Impl() = 0;

#pragma endregion Script
};

#pragma endregion ICsManager_PooledObject

// Enums
#pragma region

enum class ECsManagerPooledObjectFunctionNames : uint8
{
	OnTick,
	Deallocate,
	DeallocateAll,
	Spawn,
	ECsManagerPooledObjectFunctionNames_MAX,
};

#pragma endregion Enums

class UWorld;
class UObject;
class UClass;

class CSCORE_API FCsManager_PooledObject : public ICsManager_PooledObject
{
public:
	FCsManager_PooledObject();

	virtual ~FCsManager_PooledObject();

protected:

	/** */
	FString Name;

public:

	/**
	*
	*
	* @param Params
	*/
	virtual void Init(const FCsManagerPooledObjectParams& Params);

	/**
	*
	*/
	virtual void Clear();

	/**
	*
	*/
	virtual void Shutdown();

	/** */
	TWeakObjectPtr<UWorld> CurrentWorld;

	/**
	*
	*
	* return	World associated with the pool.
	*/
	UWorld* GetCurrentWorld();

	/**
	* Get the current time in seconds.
	*
	* return	Current time in seconds.
	*/
	virtual float GetCurrentTimeSeconds();

// Object
#pragma region
public:

	/**
	* Creates a pooled object of type ICsPooledObject.
	*
	* return
	*/
	virtual FCsPooledObject ConstructObject();

	/**
	*
	*
	* return Object
	*/
	DECLARE_DELEGATE_RetVal(FCsPooledObject /*Object*/, FConstructObject)

	FConstructObject ConstructObject_Impl;

	/**
	*
	*
	*
	* @param Object
	*/
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnConstructObject, const FCsPooledObject& /*Object*/);

	/** */
	FOnConstructObject OnConstructObject_Event;

	/**
	* Delete (or mark for deconstruction) a pooled object.
	*
	* @param Object		Container holding a pooled object.
	*/
	virtual void DeconstructObject(FCsPooledObject& Object);

	/**
	* Get the name of a pooled object.
	*
	* @param Object		Container holding a pooled object.
	* return			Name of the pooled object.
	*/
	virtual FString GetObjectName(const FCsPooledObject& Object);

#pragma endregion Object

// Pool
#pragma region
protected:

	/** */
	FString FunctionNames[(uint8)ECsManagerPooledObjectFunctionNames::ECsManagerPooledObjectFunctionNames_MAX];

	/** */
	FCsManagerPooledObjectConstructParams ConstructParams;

	/** */
	TArray<FCsPooledObject> Pool;
	/** */
	TArray<TLinkedList<FCsPooledObject>*> Links;
	/** */
	int32 PoolSize;
	/** */
	int32 PoolIndex;

	/** */
	TArray<FCsPooledObject> AllocatedObjects;
	/** */
	TLinkedList<FCsPooledObject>* AllocatedHead;
	/** */
	TLinkedList<FCsPooledObject>* AllocatedTail;
	/** */
	int32 AllocatedObjectsSize;

public:

	/**
	*
	*
	* @param Size
	*/
	virtual void CreatePool(const int32& Size);

	// Add
#pragma region
public:

		// Pool
#pragma region

	/**
	* Adds an Object to the pool.
	*  The Object must implement the interface: ICsPooledObject.
	*
	* @param PooledObject	Object that implements the interface: ICsPooledObject.
	* @param Object			UObject reference.
	* return				Container holding a reference to a pooled object.
	*						Pooled Object implements the interface: ICsPooledObject.
	*/
	const FCsPooledObject& AddToPool(ICsPooledObject* PooledObject, UObject* Object);

	/**
	* Adds an Object to the pool.
	*  Object must implement the interface: ICsPooledObject.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object that implements the interface: ICsPooledObject.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsPooledObject.
	*/
	const FCsPooledObject& AddToPool(ICsPooledObject* Object);

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
	const FCsPooledObject& AddToPool(UObject* Object);

	/** Delegate called after Adding an Object to the pool. */
	FCsManagerPooledObject_OnAddToPool OnAddToPool_Event;

	FORCEINLINE FCsManagerPooledObject_OnAddToPool& GetOnAddToPool_Event()
	{
		return OnAddToPool_Event;
	}

#pragma endregion Pool

	// Allocated Objects
#pragma region

	/**
	* Adds an Object to the allocated objects. 
	* If the Object is NOT added to the pool, add it to the pool.
	*  Object must implement the interface: ICsPooledObject.
	*
	* @param PooledObject	Object that implements the interface: ICsPooledObject.
	* @param Object			UObject reference.
	* return				Container holding a reference to a pooled object.
	*						Pooled Object implements the interface: ICsPooledObject.
	*/
	const FCsPooledObject& AddToAllocatedObjects(ICsPooledObject* PooledObject, UObject* Object);

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
	const FCsPooledObject& AddToAllocatedObjects(ICsPooledObject* Object);

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
	const FCsPooledObject& AddToAllocatedObjects(UObject* Object);

protected:

	/**
	*
	*
	* @param Object
	*/
	virtual void AddToAllocatedObjects_Internal(const FCsPooledObject& Object);

#pragma endregion Allocated Objects

#pragma endregion Add

	// Linked List
#pragma region
public:

	FORCEINLINE const TLinkedList<FCsPooledObject>* GetAllocatedHead()
	{
		return AllocatedHead;
	}

	FORCEINLINE const TLinkedList<FCsPooledObject>* GetAllocatedTail()
	{
		return AllocatedTail;
	}

protected:

	/**
	*
	*
	* @param Link
	*/
	void AddAllocatedLink(TLinkedList<FCsPooledObject>* Link);

	/**
	*
	*
	* @param Link
	*/
	void RemoveAllocatedLink(TLinkedList<FCsPooledObject>* Link);

#pragma endregion Linked List

public:

	/**
	* Get the pool.
	*  Pool is an array of containers holding references to objects that
	*  implement the interface: ICsPooledObject.
	*
	* return	Pool
	*/
	FORCEINLINE const TArray<FCsPooledObject>& GetPool()
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
	FORCEINLINE const TArray<FCsPooledObject>& GetAllocatedObjects()
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
	* Find the container holding a pooled object in the pool by Index.
	*
	* @param Index	Index of the pooled object.
	* return		Container for the pooled object.
	*/
	FORCEINLINE const FCsPooledObject& FindObject(const int32& Index)
	{
		checkf(Index > 0 && Index < PoolSize, TEXT("FCsManager_PooledObject::FindObject: Index: %d is NOT valid for pool."), Index);

		return Pool[Index];
	}

	/**
	* Find the container holding a pooled object in the pool by the interface.
	*
	* @param Object		Object of interface type: ICsPooledObject.
	* return			Container for the pooled object.
	*/
	FORCEINLINE const FCsPooledObject& FindObject(ICsPooledObject* Object)
	{
		const FCsPooledObject& O = FindObject(Object->GetCache()->GetIndex());

		checkf(Object == O.GetInterface(), TEXT("FCsManager_PooledObject::FindObject: Object is NOT apart of this pool."));
		
		return O;
	}

	const FCsPooledObject& FindObject(UObject* Object);

	/**
	* Safely, via checks, find the container holding a pooled object in the pool by Index.
	*
	* @param Index	Index of the pooled object.
	* return		Container for the pooled object.
	*/
	const FCsPooledObject& FindSafeObject(const int32& Index);

	/**
	* Safely, via checks, find the container holding a pooled object in the pool by the interface.
	*
	* @param Object		Object that implements the interface: ICsPooledObject.
	* return			Container holding a pooled object.
	*/
	const FCsPooledObject& FindSafeObject(ICsPooledObject* Object);

	const FCsPooledObject& FindSafeObject(UObject* Object);

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
	virtual void Update(const float& DeltaTime);

	FCsManagerPooledObject_OnUpdate_Object OnUpdate_Object_Event;

	FORCEINLINE FCsManagerPooledObject_OnUpdate_Object& GetOnUpdate_Object_Event()
	{
		return OnUpdate_Object_Event;
	}

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
	const FCsPooledObject& Allocate(ICsPooledObjectPayload* Payload);

public:

	/**
	*
	*
	* @param Index
	* return
	*/
	bool Deallocate(const int32& Index);

	/**
	* Delegate type when deallocating a pooled object.
	*
	* @param Object
	*/
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnDeallocate, const FCsPooledObject& /*Object*/);

	/** Delegate called after deallocating a pooled object. */
	FOnDeallocate OnDeallocate_Event;

	/**
	*
	*/
	void DeallocateAll();

#pragma endregion Allocate / DeAllocate

// Payload
#pragma region
protected:

	/** */
	TArray<ICsPooledObjectPayload*> Payloads;
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
	template<typename PayloadType>
	void ConstructPayloads(const int32& Size)
	{
		PayloadSize = Size;

		for (int32 I = 0; I < Size; ++I)
		{
			Payloads.Add(new PayloadType());
		}
	}

	/**
	*
	*
	* @param Size
	*/
	void ConstructPayloads(const int32& Size);

protected:

	/**
	*
	*
	* @param Size
	*/
	void ConstructPayloads_Internal(const int32& Size);

public:

	FCsManagerPooledObject_ConstructPayloads ConstructPayloads_Impl;

	FORCEINLINE FCsManagerPooledObject_ConstructPayloads& GetConstructPayloads_Impl()
	{
		return ConstructPayloads_Impl;
	}
	
	/**
	*
	*/
	void DeconstructPayloads();

	/**
	*
	*
	* return
	*/
	ICsPooledObjectPayload* AllocatePayload();

#pragma endregion Payload

// Log
#pragma region
protected:

	FECsCVarLog LogType;

	virtual void LogTransaction(const FString& FunctionName, const ECsPoolTransaction& Transaction, const FCsPooledObject& Object);

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
	virtual const FCsPooledObject& Spawn(ICsPooledObjectPayload* Payload);

	/**
	*
	*
	* @param Object
	*/
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnSpawn, const FCsPooledObject& /*Object*/);

	/** */
	FOnSpawn OnSpawn_Event;

#pragma endregion Spawn

// Destroy
#pragma region
public:

	/**
	*
	*
	* @param Index
	* return
	*/
	virtual bool Destroy(const int32& Index);

	/**
	*
	*
	* @param Object
	* return
	*/
	virtual bool Destroy(ICsPooledObject* Object);

#pragma endregion Destroy

// Script
#pragma region
public:

	FCsPooledObject::FScript_GetCache Script_GetCache_Impl;

	FORCEINLINE FCsPooledObject::FScript_GetCache& GetScript_GetCache_Impl()
	{
		return Script_GetCache_Impl;
	}

	FCsPooledObject::FScript_Allocate Script_Allocate_Impl;

	FORCEINLINE FCsPooledObject::FScript_Allocate& GetScript_Allocate_Impl()
	{
		return Script_Allocate_Impl;
	}

	FCsPooledObject::FScript_Deallocate Script_Deallocate_Impl;

	FORCEINLINE FCsPooledObject::FScript_Deallocate& GetScript_Deallocate_Impl()
	{
		return Script_Deallocate_Impl;
	}

#pragma endregion Script
};
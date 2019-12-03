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

	virtual void DeconstructObject(const FCsPooledObject& Object) = 0;

	virtual FString GetObjectName(const FCsPooledObject& Object) = 0;

#pragma endregion Object

// Pool
#pragma region
public:

	virtual void CreatePool(const int32& Size) = 0;

	// Add
#pragma region
public:

	virtual const FCsPooledObject& AddToPool(ICsPooledObject* PooledObject, UObject* Object) = 0;
	virtual const FCsPooledObject& AddToPool(ICsPooledObject* Object) = 0;
	virtual const FCsPooledObject& AddToPool(UObject* Object) = 0;

	virtual FCsManagerPooledObject_OnAddToPool& GetOnAddToPool_Event() = 0;

	virtual const FCsPooledObject& AddToAllocatedPool(ICsPooledObject* PooledObject, UObject* Object) = 0;
	virtual const FCsPooledObject& AddToAllocatedPool(ICsPooledObject* Object) = 0;
	virtual const FCsPooledObject& AddToAllocatedPool(UObject* Object) = 0;

#pragma endregion Add

public:

	virtual const TArray<FCsPooledObject>& GetPool() = 0;

	virtual const TArray<FCsPooledObject>& GetAllAllocatedObjects() = 0;

	virtual const int32& GetPoolSize() = 0;
	virtual int32 GetAllocatedPoolSize() = 0;

	virtual bool IsExhausted() = 0;

	// Find
#pragma region
public:

	virtual const FCsPooledObject& FindObject(const int32& Index) = 0;
	virtual const FCsPooledObject& FindObject(ICsPooledObject* Object) = 0;

	virtual const FCsPooledObject& FindSafeObject(const int32& Index) = 0;
	virtual const FCsPooledObject& FindSafeObject(ICsPooledObject* Object) = 0;

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

	FString Name;

public:

	virtual void Init(const FCsManagerPooledObjectParams& Params);

	virtual void Clear();

	virtual void Shutdown();

	TWeakObjectPtr<UWorld> CurrentWorld;

	UWorld* GetCurrentWorld();

	virtual float GetCurrentTimeSeconds();

// Object
#pragma region
public:

	/**
	* Creates a pooled object of type ICsPooledObject
	*/
	virtual FCsPooledObject ConstructObject();

	/**
	*
	*/
	DECLARE_DELEGATE_RetVal(FCsPooledObject /*Object*/, FConstructObject)

	FConstructObject ConstructObject_Impl;

	/*
	*
	*/
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnConstructObject, const FCsPooledObject& /*Object*/);

	FOnConstructObject OnConstructObject_Event;

	virtual void DeconstructObject(const FCsPooledObject& Object);

	virtual FString GetObjectName(const FCsPooledObject& Object);

#pragma endregion Object

// Pool
#pragma region
protected:

	FString FunctionNames[(uint8)ECsManagerPooledObjectFunctionNames::ECsManagerPooledObjectFunctionNames_MAX];

	FCsManagerPooledObjectConstructParams ConstructParams;

	TArray<FCsPooledObject> Pool;
	TArray<TLinkedList<FCsPooledObject>*> Links;
	int32 PoolSize;
	int32 PoolIndex;

	TArray<FCsPooledObject> AllocatedObjects;
	TLinkedList<FCsPooledObject>* AllocatedHead;
	TLinkedList<FCsPooledObject>* AllocatedTail;
	int32 AllocatedObjectsSize;

public:

	virtual void CreatePool(const int32& Size);

	// Add
#pragma region
public:

	/**
	* Adds an Object to the pool.
	*  The Object must implement the interface: ICsPooledObject.
	*
	* @param PooledObject	Object that implements the interface: ICsPooledObject.
	* @param Object			UObject reference.
	* return				Reference to the container for the Pooled Object.
	*/
	const FCsPooledObject& AddToPool(ICsPooledObject* PooledObject, UObject* Object);

	/**
	* Adds an Object to the pool.
	*  The Object must implement the interface: ICsPooledObject.
	*
	* @param Object		UObject reference.
	* return			Reference to the container for the Pooled Object.
	*/
	const FCsPooledObject& AddToPool(ICsPooledObject* Object);

	/**
	* Adds an Object to the pool.
	*  The Object must implement the interface: ICsPooledObject.
	*
	* @param Object		UObject reference.
	* return			Reference to the container for the PooledObject.
	*/
	const FCsPooledObject& AddToPool(UObject* Object);

	/** Delegate called after Adding an Object to the pool. */
	FCsManagerPooledObject_OnAddToPool OnAddToPool_Event;

	FORCEINLINE FCsManagerPooledObject_OnAddToPool& GetOnAddToPool_Event()
	{
		return OnAddToPool_Event;
	}

	const FCsPooledObject& AddToAllocatedPool(ICsPooledObject* PooledObject, UObject* Object);
	const FCsPooledObject& AddToAllocatedPool(ICsPooledObject* Object);
	const FCsPooledObject& AddToAllocatedPool(UObject* Object);

protected:

	virtual void AddToAllocatedPool_Internal(const FCsPooledObject& Object);

	void AddAllocatedLink(TLinkedList<FCsPooledObject>* Link);
	void RemoveAllocatedLink(TLinkedList<FCsPooledObject>* Link);

#pragma endregion Add

public:

	FORCEINLINE const TArray<FCsPooledObject>& GetPool()
	{
		return Pool;
	}

	FORCEINLINE const TArray<FCsPooledObject>& GetAllAllocatedObjects()
	{
		return AllocatedObjects;
	}

	FORCEINLINE const int32& GetPoolSize()
	{
		return PoolSize;
	}

	FORCEINLINE int32 GetAllocatedPoolSize()
	{
		return AllocatedObjectsSize;
	}

	FORCEINLINE bool IsExhausted()
	{
		return AllocatedObjectsSize == PoolSize;
	}

	// Find
#pragma region
public:

	FORCEINLINE const FCsPooledObject& FindObject(const int32& Index)
	{
		checkf(Index > 0 && Index < PoolSize, TEXT("FCsManager_PooledObject::FindObject: Index: %d is NOT valid for pool."), Index);

		return Pool[Index];
	}

	FORCEINLINE const FCsPooledObject& FindObject(ICsPooledObject* Object)
	{
		const FCsPooledObject& O = FindObject(Object->GetCache()->GetIndex());

		checkf(Object == O.GetInterface(), TEXT("FCsManager_PooledObject::FindObject: Object is NOT apart of this pool."));
		
		return O;
	}

	const FCsPooledObject& FindSafeObject(const int32& Index);
	const FCsPooledObject& FindSafeObject(ICsPooledObject* Object);

#pragma endregion Find

#pragma endregion Pool

// Update
#pragma region
public:

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

	const FCsPooledObject& Allocate(ICsPooledObjectPayload* Payload);

public:

	bool Deallocate(const int32& index);

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnDeallocate, const FCsPooledObject&);

	FOnDeallocate OnDeallocate_Event;

	void DeallocateAll();

#pragma endregion Allocate / DeAllocate

// Payload
#pragma region
protected:

	TArray<ICsPooledObjectPayload*> Payloads;
	int32 PayloadSize;
	int32 PayloadIndex;

public:

	template<typename PayloadType>
	void ConstructPayloads(const int32& Size)
	{
		PayloadSize = Size;

		for (int32 I = 0; I < Size; ++I)
		{
			Payloads.Add(new PayloadType());
		}
	}

	void ConstructPayloads(const int32& Size);

protected:

	void ConstructPayloads_Internal(const int32& Size);

public:

	FCsManagerPooledObject_ConstructPayloads ConstructPayloads_Impl;

	FORCEINLINE FCsManagerPooledObject_ConstructPayloads& GetConstructPayloads_Impl()
	{
		return ConstructPayloads_Impl;
	}

	void DeconstructPayloads();

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

	virtual const FCsPooledObject& Spawn(ICsPooledObjectPayload* Payload);

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnSpawn, const FCsPooledObject&);

	FOnSpawn OnSpawn_Event;

#pragma endregion Spawn

// Destroy
#pragma region
public:

	virtual bool Destroy(const int32& Index);
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
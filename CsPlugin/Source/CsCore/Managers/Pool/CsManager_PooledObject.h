// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#pragma once
#include "Managers/Pool/CsPooledObject.h"
#include "CsCVars.h"

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

DECLARE_DELEGATE_OneParam(FCsManagerPooledObject_CreatePayloads, const int32& /*Size*/);

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

	virtual void AddToPool(ICsPooledObject* PooledObject, UObject* Object) = 0;
	virtual void AddToPool(ICsPooledObject* Object) = 0;

	virtual FCsManagerPooledObject_OnAddToPool& GetOnAddToPool_Event() = 0;

	virtual void AddToAllocatedPool(ICsPooledObject* PooledObject, UObject* Object) = 0;
	virtual void AddToAllocatedPool(ICsPooledObject* Object) = 0;

	virtual const TArray<FCsPooledObject>& GetAllAllocatedObjects() = 0;

	virtual const TArray<FCsPooledObject>& GetObjects() = 0;

	virtual const int32& GetPoolSize() = 0;
	virtual int32 GetAllocatedPoolSize() = 0;

	virtual bool IsExhausted() = 0;

	virtual const FCsPooledObject& FindObject(const int32& Index) = 0;
	virtual const FCsPooledObject& FindObject(ICsPooledObject* Object) = 0;

#pragma endregion Pool

// Update
#pragma region
public:

	virtual void Update(const float& DeltaTime) = 0;

#pragma endregion Update

// Payload
#pragma region
public:

	virtual void CreatePayloads(const int32& Size) = 0;

	virtual FCsManagerPooledObject_CreatePayloads& GetCreatePayloads_Impl() = 0;

	virtual void DestroyPayloads() = 0;

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

	virtual void AddToPool(ICsPooledObject* PooledObject, UObject* Object);
	virtual void AddToPool(ICsPooledObject* Object);

	FCsManagerPooledObject_OnAddToPool OnAddToPool_Event;

	FORCEINLINE FCsManagerPooledObject_OnAddToPool& GetOnAddToPool_Event()
	{
		return OnAddToPool_Event;
	}

public: 

	virtual void AddToAllocatedPool(ICsPooledObject* PooledObject, UObject* Object);
	virtual void AddToAllocatedPool(ICsPooledObject* Object);

protected:

	virtual void AddToAllocatedPool_Internal(const FCsPooledObject& Object);

	virtual void AddAllocatedLink(TLinkedList<FCsPooledObject>* Link);
	virtual void RemoveAllocatedLink(TLinkedList<FCsPooledObject>* Link);

public:

	const TArray<FCsPooledObject>& GetObjects();

	const TArray<FCsPooledObject>& GetAllAllocatedObjects();

	const int32& GetPoolSize();
	int32 GetAllocatedPoolSize();

	bool IsExhausted();

	const FCsPooledObject& FindObject(const int32& Index);
	const FCsPooledObject& FindObject(ICsPooledObject* Object);

#pragma endregion Pool

// Tick
#pragma region
public:

	virtual void Update(const float& DeltaTime);

	/**
	*
	*
	* @param Object
	*/
	DECLARE_DELEGATE_OneParam(FOnUpdate_Handle_Object, const FCsPooledObject& /*Object*/);

	FOnUpdate_Handle_Object OnUpdate_Handle_Object;

#pragma endregion Tick

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
	void CreatePayloads(const int32& Size)
	{
		PayloadSize = Size;

		for (int32 I = 0; I < Size; ++I)
		{
			Payloads.Add(new PayloadType());
		}
	}

	void CreatePayloads(const int32& Size);

protected:

	void CreatePayloads_Internal(const int32& Size);

public:

	FCsManagerPooledObject_CreatePayloads CreatePayloads_Impl;

	FORCEINLINE FCsManagerPooledObject_CreatePayloads& GetCreatePayloads_Impl()
	{
		return CreatePayloads_Impl;
	}

	void DestroyPayloads();

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
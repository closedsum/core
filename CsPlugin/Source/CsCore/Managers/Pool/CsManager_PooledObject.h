// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#pragma once
#include "Managers/Pool/CsTypes_Pool.h"
#include "CsCVars.h"

enum class ECsManagerPooledObjectFunctionNames : uint8
{
	OnTick,
	Deallocate,
	DeallocateAll,
	Spawn,
	ECsManagerPooledObjectFunctionNames_MAX,
};

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

	DECLARE_DELEGATE_RetVal(FCsPooledObject, FConstructObject)

	FConstructObject ConstructObject_Impl;

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnConstructObject, const FCsPooledObject&);

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

	TArray<FCsPooledObject> ActiveObjects;
	TLinkedList<FCsPooledObject>* ActiveHead;
	TLinkedList<FCsPooledObject>* ActiveTail;
	int32 ActiveObjectsSize;

public:

	virtual void CreatePool(const int32& Size);

	virtual void AddToPool(ICsPooledObject* PooledObject, UObject* Object);
	virtual void AddToPool(ICsPooledObject* Object);

	FCsManagerPooledObject_OnAddToPool OnAddToPool_Event;

	FCsManagerPooledObject_OnAddToPool& GetOnAddToPool_Event();

public: 

	virtual void AddToActivePool(ICsPooledObject* PooledObject, UObject* Object);
	virtual void AddToActivePool(ICsPooledObject* Object);

protected:

	virtual void AddToActivePool_Internal(const FCsPooledObject& Object);

	virtual void AddActiveLink(TLinkedList<FCsPooledObject>* Link);
	virtual void RemoveActiveLink(TLinkedList<FCsPooledObject>* Link);

public:

	const TArray<FCsPooledObject>& GetObjects();

	const TArray<FCsPooledObject>& GetAllActiveObjects();

	const int32& GetPoolSize();
	int32 GetActivePoolSize();

	bool IsExhausted();

	const FCsPooledObject& FindObject(const int32& Index);
	const FCsPooledObject& FindObject(ICsPooledObject* Object);

#pragma endregion Pool

// Tick
#pragma region
public:

	virtual void OnTick(const float &DeltaTime);

	DECLARE_DELEGATE_OneParam(FOnTick_Handle_Object, const FCsPooledObject&);

	FOnTick_Handle_Object OnTick_Handle_Object;

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

	FCsManagerPooledObject_CreatePayloads& GetCreatePayloads_Impl();

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
};
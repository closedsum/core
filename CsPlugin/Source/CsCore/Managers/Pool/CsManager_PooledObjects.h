// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#pragma once
#include "Managers/Pool/CsTypes_Pool.h"
#include "CsCVars.h"

enum class ERsManagerPooledObjectsFunctionNames : uint8
{
	OnTick,
	Deallocate,
	DeallocateAll,
	Spawn,
	ERsManagerPooledObjectsFunctionNames_MAX,
};

class UWorld;
class UObject;
class UClass;
class ICsPooledObject;
struct ICsPooledObjectPayload;

class FCsManager_PooledObjects : public ICsManager_PooledObjects
{
public:
	FCsManager_PooledObjects();

	virtual ~FCsManager_PooledObjects();

public:
	FString Name;
	FString ObjectClassName;

	UClass* ObjectClass;

public:

	virtual void Init(const FString& InName, UClass* InObjectClass, UWorld* World, const FECsCVarLog& InLogType);

	virtual void Clear();

	virtual void Shutdown();

	TWeakObjectPtr<UWorld> CurrentWorld;

	UWorld* GetCurrentWorld();

	virtual float GetCurrentTimeSeconds();

	// Object
#pragma region
protected:

	virtual ICsPooledObject* ConstructObject();

	DECLARE_DELEGATE_RetVal(ICsPooledObject*, FConstructObject)

	FConstructObject ConstructObject_Call;

	virtual void DeconstructObject(ICsPooledObject* Object);

	virtual FString GetObjectName(ICsPooledObject* Object);

#pragma endregion Object

	// Pool
#pragma region
protected:

	FString FunctionNames[(uint8)ERsManagerPooledObjectsFunctionNames::ERsManagerPooledObjectsFunctionNames_MAX];

	TArray<ICsPooledObject*> Pool;
	TArray<TLinkedList<ICsPooledObject*>*> Links;
	int32 PoolSize;
	int32 PoolIndex;

	TArray<ICsPooledObject*> ActiveObjects;
	TLinkedList<ICsPooledObject*>* ActiveHead;
	TLinkedList<ICsPooledObject*>* ActiveTail;
	int32 ActiveObjectsSize;

public:

	virtual void CreatePool(const int32& Size);

	virtual void AddToPool(ICsPooledObject* Object);

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnAddToPool, ICsPooledObject*);

	FOnAddToPool OnAddToPool_Event;

public:

	virtual void AddToActivePool(ICsPooledObject* Object);

protected:

	virtual void AddToActivePool_Internal(ICsPooledObject* Object);

	virtual void AddActiveLink(TLinkedList<ICsPooledObject*>* Link);
	virtual void RemoveActiveLink(TLinkedList<ICsPooledObject*>* Link);

public:

	const TArray<ICsPooledObject*>& GetAllActiveObjects();

	const TArray<ICsPooledObject*>& GetObjects();

	int32 GetActivePoolSize();

	bool IsExhausted();

#pragma endregion Pool

	// Tick
#pragma region
protected:

	virtual void OnTick(const float &DeltaTime);

	DECLARE_DELEGATE_OneParam(FOnTick_Handle_Object, ICsPooledObject*);

	FOnTick_Handle_Object OnTick_Handle_Object;

#pragma endregion Tick

	// Allocate / DeAllocate
#pragma region
protected:

	ICsPooledObject* Allocate(ICsPooledObjectPayload* Payload);

public:

	bool Deallocate(const int32& index);

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnDeallocate, ICsPooledObject*);

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

	ICsPooledObjectPayload* AllocatePayload();

#pragma endregion Payload

	// Log
#pragma region
protected:

	FECsCVarLog LogType;

	virtual void LogTransaction(const FString& FunctionName, const ECsPoolTransaction& Transaction, ICsPooledObject* o);

#pragma endregion Log

	// Spawn
#pragma region
public:

	virtual ICsPooledObject* Spawn(ICsPooledObjectPayload* Payload);

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnSpawn, ICsPooledObject*);

	FOnSpawn OnSpawn_Event;

#pragma endregion Spawn
};
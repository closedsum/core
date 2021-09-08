// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "GameFramework/Actor.h"
#include "Managers/Pool/CsTypes_Pool.h"
#include "CsCVars.h"
#include "CsManager.generated.h"

UCLASS()
class CSCORE_API ACsManager : public AActor
{
	GENERATED_UCLASS_BODY()
};

enum class ECsManagerPooledObjectsFunctionNames : uint8
{
	OnTick,
	DeAllocate,
	DeAllocateAll,
	Spawn,
	ECsManagerPooledObjectsFunctionNames_MAX,
};

template<typename ObjectType, typename PayloadType, int32 PAYLOAD_SIZE = 1>
class TCsManager_PooledObjects
{
public:
	TCsManager_PooledObjects()
	{
		PoolSize = 0;
		PoolIndex = 0;
		PayloadIndex = 0;

		ConstructObject_Call.BindRaw(this, &TCsManager_PooledObjects::ConstructObject);
	}

	virtual ~TCsManager_PooledObjects()
	{
		Shutdown();
	}

public:
	FString Name;
	FString ObjectClassName;

	TWeakObjectPtr<class UWorld> CurrentWorld;

	TDelegate<ObjectType*()> ConstructObject_Call;

	TMulticastDelegate<void(ObjectType*)> OnAddToPool_Event;
	TMulticastDelegate<void(ObjectType*)> OnDeAllocate_Event;

	TAutoConsoleVariable<int32>* LogTransactions;

	TDelegate<void(ObjectType*)> OnTick_Handle_Object;

protected:
	FString FunctionNames[(uint8)ECsManagerPooledObjectsFunctionNames::ECsManagerPooledObjectsFunctionNames_MAX];

	TArray<ObjectType*> Pool;
	int32 PoolSize;
	int32 PoolIndex;
	TMap<int, ObjectType*> ActiveObjects;

	PayloadType* Payloads[PAYLOAD_SIZE];
	int32 PayloadIndex;

public:

	virtual void Init(const FString& name, const FString& objectClassName, UWorld* world, TAutoConsoleVariable<int32>* logTransactions)
	{
		Name = name;
		ObjectClassName = objectClassName;
		CurrentWorld = world;
		LogTransactions = logTransactions;

		FunctionNames[(uint8)ECsManagerPooledObjectsFunctionNames::OnTick] = Name + TEXT("::OnTick");
		FunctionNames[(uint8)ECsManagerPooledObjectsFunctionNames::DeAllocate] = Name + TEXT("::DeAllocate");
		FunctionNames[(uint8)ECsManagerPooledObjectsFunctionNames::DeAllocateAll] = Name + TEXT("::DeAllocateAll");
		FunctionNames[(uint8)ECsManagerPooledObjectsFunctionNames::Spawn] = Name + TEXT("::Spawn");
	}

	virtual void DeconstructObject(ObjectType* o)
	{
		delete o;
	}

	virtual void Clear()
	{
		for (ObjectType* o : Pool)
		{
			o->DeAllocate();
			DeconstructObject(o);
		}

		Pool.Reset();
		PoolSize = 0;
		ActiveObjects.Reset();

		for (int32 i = 0; i < PAYLOAD_SIZE; ++i)
		{
			Payloads[i]->Reset();
		}
		OnAddToPool_Event.Clear();
		OnDeAllocate_Event.Clear();
	}

	virtual void Shutdown()
	{
		Clear();

		OnTick_Handle_Object.Unbind();
		ConstructObject_Call.Unbind();
	}

	virtual ObjectType* ConstructObject()
	{
		return nullptr;
	}

	virtual FString GetObjectName(ObjectType* o)
	{
		return NCsCached::Str::Empty;
	}

	virtual void CreatePool(const int32& size)
	{
		PoolSize = size;

		for (int32 i = 0; i < size; ++i)
		{
			ObjectType* o = ConstructObject_Call.Execute();
			o->Init(i);
			o->OnCreatePool();
			o->DeAllocate();
			Pool.Add(o);
			OnAddToPool_Event.Broadcast(o);
		}
	}

	virtual void AddToPool(ObjectType* o)
	{
		Pool.Add(o);
		PoolSize = Pool.Num();
		o->Init(Pool.Num() - 1);
	}

	virtual void AddToActivePool(ObjectType* o)
	{
		o->Cache.bAllocated = true;

		ActiveObjects.Add(o->Cache.Index, o);
	}

	class UWorld* GetCurrentWorld()
	{
		return CurrentWorld.IsValid() ? CurrentWorld.Get() : nullptr;
	}

	virtual void LogTransaction(const FString& functionName, const ECsPoolTransaction& transaction, ObjectType* o)
	{
		if ((*LogTransactions)->GetInt() == CS_CVAR_SHOW_LOG)
		{
			const FString& transactionAsString = NCsPoolTransaction::ToActionString(transaction);

			const FString objectName	= GetObjectName(o);
			const float currentTime		= GetCurrentTimeSeconds();
			const UObject* objectOwner	= o->Cache.GetOwner();
			const FString ownerName		= objectOwner ? objectOwner->GetName() : NCsCached::Str::None;
			const UObject* parent		= o->Cache.GetParent();
			const FString parentName	= parent ? parent->GetName() : NCsCached::Str::None;

			FString log = NCsCached::Str::Empty;

			if (objectOwner && parent)
			{
				log = FString::Printf(TEXT("%s: %s %s: %s of Type: %s at %f for %s attached to %s."), *functionName, *transactionAsString, *ObjectClassName, *objectName, currentTime, *ownerName, *parentName);
			}
			else
			if (objectOwner)
			{
				log = FString::Printf(TEXT("%s: %s %s: %s of Type: %s at %f for %s."), *functionName, *transactionAsString, *ObjectClassName, *objectName, currentTime, *ownerName);
			}
			else
			if (parent)
			{
				log = FString::Printf(TEXT("%s: %s %s: %s of Type: %s at %f attached to %s."), *functionName, *transactionAsString, *ObjectClassName, *objectName, currentTime, *parentName);
			}
			else
			{
				log = FString::Printf(TEXT("%s: %s %s: %s of Type: %s at %f."), *functionName, *transactionAsString, *ObjectClassName, *objectName, currentTime);
			}
			Log(log);
		}
	}

	virtual void Log(const FString& outLog) {}

	virtual float GetCurrentTimeSeconds()
	{
		return GetCurrentWorld() ? GetCurrentWorld()->GetTimeSeconds() : 0.0f;
	}

	virtual void OnTick(const float &deltaTime)
	{
		TArray<int32> keys;
		ActiveObjects.GetKeys(keys);

		for (const int32& key : keys)
		{
			ObjectType* o = ActiveObjects[key];

			// Check if ObjectType was DeAllocated NOT in a normal way (i.e. Out of Bounds)

			if (!o->Cache.bAllocated)
			{
				OnTick_Log_PrematureDeAllocation(o);

				LogTransaction(FunctionNames[(uint8)ECsManagerPooledObjectsFunctionNames::OnTick], ECsPoolTransaction::Deallocate, o);

				ActiveObjects.Remove(key);
				continue;
			}

			if (!o->Cache.bLifeTime)
			{
				OnTick_Handle_Object.ExecuteIfBound(o);
				continue;
			}

			if (GetCurrentTimeSeconds() - o->Cache.Time > o->Cache.LifeTime)
			{
				LogTransaction(FunctionNames[(uint8)ECsManagerPooledObjectsFunctionNames::OnTick], ECsPoolTransaction::Deallocate, o);

				o->DeAllocate();
				ActiveObjects.Remove(key);

				OnDeAllocate_Event.Broadcast(o);
				continue;
			}

			OnTick_Handle_Object.ExecuteIfBound(o);
		}
	}

	void OnTick_Log_PrematureDeAllocation(ObjectType* o)
	{
		const FString log = FString::Printf(TEXT("%s::OnTick: %s: %s at PoolIndex: %d was prematurely deallocted NOT in a normal way."), *Name, *ObjectClassName, *(GetObjectName(o)), o->Cache.Index);

		Log(log);
	}

	const TMap<int32, ObjectType*>& GetAllActiveObjects()
	{
		return ActiveObjects;
	}

	const TArray<ObjectType*>& GetObjects()
	{
		return Pool;
	}

	int32 GetActivePoolSize()
	{
		return ActiveObjects.Num();
	}

	bool IsExhausted()
	{
		return ActiveObjects.Num() == Pool.Num();
	}

	// Allocate / DeAllocate
#pragma region

	virtual ObjectType* Allocate()
	{
		if (IsExhausted())
		{
			checkf(0, TEXT("%s::Allocate: Pool: is exhausted"), *Name);
			return nullptr;
		}

		for (int32 i = 0; i < PoolSize; ++i)
		{
			PoolIndex	  = (PoolIndex + 1) % PoolSize;
			ObjectType* o = Pool[PoolIndex];

			if (!o->Cache.bAllocated)
			{
				o->Cache.bAllocated = true;
				return o;
			}
		}
		checkf(0, TEXT("%s::Allocate: Pool: %s is exhausted"), *Name);
		return nullptr;
	}

	bool DeAllocate(const int32& index)
	{
		if (ActiveObjects.Num() == CS_EMPTY ||
			!ActiveObjects.Find(index))
		{
			//UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("%s::DeAllocate: %s at PoolIndex: %d is already deallocated."), *Name, *ObjectClassName, index);
			return false;
		}

		ObjectType* o = ActiveObjects[index];

		LogTransaction(FunctionNames[(uint8)ECsManagerPooledObjectsFunctionNames::DeAllocate], ECsPoolTransaction::Deallocate, o);

		o->DeAllocate();
		ActiveObjects.Remove(index);

		OnDeAllocate_Event.Broadcast(o);
		return true;
	}

	void DeAllocateAll()
	{
		TArray<int32> keys;
		ActiveObjects.GetKeys(keys);

		for (const int32& key : keys)
		{
			ObjectType* o = ActiveObjects[key];

			LogTransaction(FunctionNames[(uint8)ECsManagerPooledObjectsFunctionNames::DeAllocateAll], ECsPoolTransaction::Deallocate, o);

			o->DeAllocate();
			ActiveObjects.Remove(key);
		}
	}

#pragma endregion Allocate / DeAllocate

	// Payload
#pragma region

	PayloadType* AllocatePayload()
	{
		for (int32 i = 0; i < PAYLOAD_SIZE; ++i)
		{
			PayloadIndex		 = (PayloadIndex + 1) % PAYLOAD_SIZE;
			PayloadType* Payload = Payloads[PayloadIndex];

			if (!Payload->bAllocated)
			{
				Payload->bAllocated = true;
				return Payload;
			}
		}
		checkf(0, TEXT("%s::AllocatePayload: Pool is exhausted"), *Name);
		return nullptr;
	}

#pragma endregion Payload

	virtual ObjectType* Spawn(PayloadType* payload)
	{
		ObjectType* o = Allocate();

		o->Allocate(payload);

		LogTransaction(FunctionNames[(uint8)ECsManagerPooledObjectsFunctionNames::Spawn], ECsPoolTransaction::Allocate, o);
		payload->Reset();
		AddToActivePool(o);
		return o;
	}
};

template<typename EnumType, typename ObjectType, typename PayloadType, int32 PAYLOAD_SIZE = 1>
class TCsManager_PooledObjects_TMap
{
public:
	TCsManager_PooledObjects_TMap()
	{
		PayloadIndex = 0;

		ConstructObject_Call.BindRaw(this, &TCsManager_PooledObjects_TMap::ConstructObject);
	}

	virtual ~TCsManager_PooledObjects_TMap()
	{
		Shutdown();
	}

public:
	FString Name;
	FString ObjectClassName;

	TWeakObjectPtr<class UWorld> CurrentWorld;

	TDelegate<ObjectType*(const EnumType&)> ConstructObject_Call;

	TMulticastDelegate<void(const EnumType&, ObjectType*)> OnAddToPool_Event;
	TMulticastDelegate<void(const EnumType&, ObjectType*)> OnDeAllocate_Event;

	TAutoConsoleVariable<int32>* LogTransactions;

	TDelegate<void(ObjectType*)> OnTick_Handle_Object;

protected:
	FString FunctionNames[(uint8)ECsManagerPooledObjectsFunctionNames::ECsManagerPooledObjectsFunctionNames_MAX];

	TArray<ObjectType*> Pool;
	int32 PoolSize;
	TMap<EnumType, TArray<ObjectType*>> Pools;
	TMap<EnumType, int32> PoolSizes;
	TMap<EnumType, int32> PoolIndices;
	TMap<EnumType, TMap<int32, ObjectType*>> ActiveObjects;

	PayloadType* Payloads[PAYLOAD_SIZE];
	int32 PayloadIndex;

public:

	virtual void Init(const FString& name, const FString& objectClassName, UWorld* world, TAutoConsoleVariable<int32>* logTransactions)
	{
		Name			= name;
		ObjectClassName = objectClassName;
		CurrentWorld	= world;
		LogTransactions = logTransactions;

		FunctionNames[(uint8)ECsManagerPooledObjectsFunctionNames::OnTick] = Name + TEXT("::OnTick");
		FunctionNames[(uint8)ECsManagerPooledObjectsFunctionNames::DeAllocate] = Name + TEXT("::DeAllocate");
		FunctionNames[(uint8)ECsManagerPooledObjectsFunctionNames::DeAllocateAll] = Name + TEXT("::DeAllocateAll");
		FunctionNames[(uint8)ECsManagerPooledObjectsFunctionNames::Spawn] = Name + TEXT("::Spawn");
	}

	virtual void DeconstructObject(ObjectType* o)
	{
		delete o;
	}

	virtual void Clear()
	{
		for (ObjectType* o : Pool)
		{
			o->DeAllocate();
			DeconstructObject(o);
		}

		PoolSize = 0;

		Pool.Reset();
		Pools.Reset();
		PoolSizes.Reset();
		PoolIndices.Reset();
		ActiveObjects.Reset();

		for (int32 i = 0; i < PAYLOAD_SIZE; ++i)
		{
			Payloads[i]->Reset();
		}
		OnAddToPool_Event.Clear();
		OnDeAllocate_Event.Clear();
	}

	virtual void Shutdown()
	{
		Clear();

		OnTick_Handle_Object.Unbind();
		ConstructObject_Call.Unbind();
	}

	virtual ObjectType* ConstructObject(const EnumType& e)
	{
		return nullptr;
	}

	virtual FString GetObjectName(ObjectType* o)
	{
		return NCsCached::Str::Empty;
	}

	virtual void CreatePool(const EnumType& e, const int32& size)
	{
		PoolSizes.Add(e, size);
		PoolIndices.Add(e, 0);

		TArray<ObjectType*> pool;

		for (int32 i = 0; i < size; ++i)
		{
			ObjectType* o = ConstructObject_Call.Execute(e);
			o->Init(i, e);
			o->OnCreatePool();
			o->DeAllocate();
			Pool.Add(o);
			pool.Add(o);
			OnAddToPool_Event.Broadcast(e, o);
		}
		Pools.Add(e, pool);
		PoolSize = Pool.Num();
	}

	virtual void AddToPool(const EnumType& e, ObjectType* o)
	{
		int32* size = PoolSizes.Find(e);

		if (size)
			++(*size);
		else
			PoolSizes.Add(e, 1);

		int32* index = PoolIndices.Find(e);

		if (!index)
			PoolIndices.Add(e, 0);

		Pool.Add(o);
		PoolSize = Pool.Num();

		TArray<ObjectType*>* poolPtr = Pools.Find(e);

		if (poolPtr)
		{
			poolPtr->Add(o);
		}
		else
		{
			TArray<ObjectType*> pool;
			pool.Add(o);
			Pools.Add(e, pool);

			poolPtr = Pools.Find(e);
		}

		o->Init(poolPtr->Num() - 1, e);
	}

	virtual void AddToActivePool(const EnumType& e, ObjectType* o)
	{
		o->Cache.bAllocated = true;

		// Add to ActiveObjects
		TMap<int32, ObjectType*>* poolPtr = ActiveObjects.Find(e);

		if (poolPtr)
		{
			poolPtr->Add(o->Cache.Index, o);
		}
		else
		{
			TMap<int32, ObjectType*> pool;
			pool.Add(o->Cache.Index, o);
			ActiveObjects.Add(e, pool);
		}
	}

	class UWorld* GetCurrentWorld()
	{
		return CurrentWorld.IsValid() ? CurrentWorld.Get() : nullptr;
	}

	virtual const FString& EnumTypeToString(const EnumType& e)
	{
		return NCsCached::Str::Empty;
	}

	virtual const FString& EnumTypeToString(const int32& index)
	{
		return NCsCached::Str::Empty;
	}

	virtual void LogTransaction(const FString& functionName, const ECsPoolTransaction& transaction, ObjectType* o)
	{
		if ((*LogTransactions)->GetInt() == CS_CVAR_SHOW_LOG)
		{
			const FString& transactionAsString = NCsPoolTransaction::ToActionString(transaction);

			const FString objectName	= GetObjectName(o);
			const FString typeAsString  = EnumTypeToString(o->Cache.Type);
			const float currentTime	    = GetCurrentTimeSeconds();
			const UObject* objectOwner  = o->Cache.GetOwner();
			const FString ownerName	    = objectOwner ? objectOwner->GetName() : NCsCached::Str::None;
			const UObject* parent	    = o->Cache.GetParent();
			const FString parentName    = parent ? parent->GetName() : NCsCached::Str::None;

			FString log = NCsCached::Str::Empty;

			if (objectOwner && parent)
			{
				log = FString::Printf(TEXT("%s: %s %s: %s of Type: %s at %f for %s attached to %s."), *functionName, *transactionAsString, *ObjectClassName, *objectName, *typeAsString, currentTime, *ownerName, *parentName);
			}
			else
			if (objectOwner)
			{
				log = FString::Printf(TEXT("%s: %s %s: %s of Type: %s at %f for %s."), *functionName, *transactionAsString, *ObjectClassName, *objectName, *typeAsString, currentTime, *ownerName);
			}
			else
			if (parent)
			{
				log = FString::Printf(TEXT("%s: %s %s: %s of Type: %s at %f attached to %s."), *functionName, *transactionAsString, *ObjectClassName, *objectName, *typeAsString, currentTime, *parentName);
			}
			else
			{
				log = FString::Printf(TEXT("%s: %s %s: %s of Type: %s at %f."), *functionName, *transactionAsString, *ObjectClassName, *objectName, *typeAsString, currentTime);
			}
			Log(log);
		}
	}

	virtual float GetCurrentTimeSeconds()
	{
		return GetCurrentWorld() ? GetCurrentWorld()->GetTimeSeconds() : 0.0f;
	}

	virtual void OnTick(const float& deltaTime)
	{
		TArray<EnumType> enumKeys;
		ActiveObjects.GetKeys(enumKeys);

		for (const EnumType& key : enumKeys)
		{
			TMap<int32, ObjectType*>& objects = ActiveObjects[key];

			TArray<int32> indexKeys;
			objects.GetKeys(indexKeys);

			for (const int32& index : indexKeys)
			{
				ObjectType* o = objects[index];

				// Check if ObjectType was DeAllocated NOT in a normal way (i.e. Out of Bounds)

				if (!o->Cache.bAllocated)
				{
					OnTick_Log_PrematureDeAllocation(key, o);

					LogTransaction(FunctionNames[(uint8)ECsManagerPooledObjectsFunctionNames::OnTick], ECsPoolTransaction::Deallocate, o);

					objects.Remove(index);
					continue;
				}

				if (!o->Cache.bLifeTime)
				{
					OnTick_Handle_Object.ExecuteIfBound(o);
					continue;
				}

				if (GetCurrentTimeSeconds() - o->Cache.Time > o->Cache.LifeTime)
				{
					LogTransaction(FunctionNames[(uint8)ECsManagerPooledObjectsFunctionNames::OnTick], ECsPoolTransaction::Deallocate, o);

					o->DeAllocate();
					objects.Remove(index);

					OnDeAllocate_Event.Broadcast(key, o);
					continue;
				}

				OnTick_Handle_Object.ExecuteIfBound(o);
			}
		}
	}

	void OnTick_Log_PrematureDeAllocation(const EnumType& e, ObjectType* o)
	{
		const FString log = FString::Printf(TEXT("%s::OnTick: %s: %s of type: %s at PoolIndex: %d was prematurely deallocted NOT in a normal way."), *Name, *ObjectClassName, *GetObjectName(o), *EnumTypeToString(e), o->Cache.Index);

		Log(log);
	}

	virtual void Log(const FString &log) {}

	const TArray<ObjectType*>& GetAllObjects()
	{
		return Pool;
	}

	void GetAllActiveObjects(TArray<ObjectType*>& outObjects)
	{
		TArray<EnumType> enumKeys;
		ActiveObjects.GetKeys(enumKeys);

		for (const EnumType& key : enumKeys)
		{
			TMap<int32, ObjectType*>& objects = ActiveObjects[key];

			TArray<int32> indexKeys;
			objects.GetKeys(indexKeys);

			for (const int32& index : indexKeys)
			{
				outObjects.Add(objects[index]);
			}
		}
	}

	const TArray<ObjectType*>* GetObjects(const EnumType& type)
	{
		return Pools.Find(type);
	}

	int32 GetActivePoolSize(const EnumType& e)
	{
		TMap<int32, ObjectType*>* objectsPtr = ActiveObjects.Find(e);

		if (!objectsPtr)
			return CS_EMPTY;
		return objectsPtr->Num();
	}

	bool IsExhausted(const EnumType& e)
	{
		TArray<ObjectType*>* poolPtr = Pools.Find(e);

		if (!poolPtr)
			return true;

		return GetActivePoolSize(e) >= poolPtr->Num();
	}

	// Allocate / DeAllocate
#pragma region

	virtual ObjectType* Allocate(const EnumType& e)
	{
		TArray<ObjectType*>* pool = Pools.Find(e);
		const int32 size		  = *(PoolSizes.Find(e));

		if (size == CS_EMPTY)
		{
			checkf(0, TEXT("%s::Allocate: Pool: %s is exhausted"), *Name, *EnumTypeToString(e));
			return nullptr;
		}

		for (int32 i = 0; i < size; ++i)
		{
			int32* poolIndexPtr = PoolIndices.Find(e);
			*poolIndexPtr		= (*poolIndexPtr + 1) % size;
			ObjectType* o		= (*pool)[*poolIndexPtr];

			if (!o->Cache.bAllocated)
			{
				o->Cache.bAllocated = true;
				return o;
			}
		}
		checkf(0, TEXT("%s::Allocate: Pool: %s is exhausted"), *Name, *EnumTypeToString(e));
		return nullptr;
	}

	bool DeAllocate(const EnumType& e, const int32& index)
	{
		TMap<int32, ObjectType*>* objectsPtr = ActiveObjects.Find(e);

		if (!objectsPtr ||
			!objectsPtr->Find(index))
		{
			//UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("%s::DeAllocate: %s of Type: %s at PoolIndex: %d is already deallocated."), *Name, *ObjectClassName, *EnumTypeToString(e), index);
			return false;
		}

		ObjectType* o = (*objectsPtr)[index];

		LogTransaction(FunctionNames[(uint8)ECsManagerPooledObjectsFunctionNames::DeAllocate], ECsPoolTransaction::Deallocate, o);

		o->DeAllocate();
		objectsPtr->Remove(index);

		OnDeAllocate_Event.Broadcast(e, o);
		return true;
	}

	void DeAllocateAll()
	{
		TArray<EnumType> enumKeys;
		ActiveObjects.GetKeys(enumKeys);

		for (const EnumType& key : enumKeys)
		{
			TMap<int32, ObjectType*>& objects = ActiveObjects[key];

			TArray<int32> indexKeys;
			objects.GetKeys(indexKeys);

			for (const int32& index : indexKeys)
			{
				ObjectType* o = objects[index];

				LogTransaction(FunctionNames[(uint8)ECsManagerPooledObjectsFunctionNames::DeAllocateAll], ECsPoolTransaction::Deallocate, o);

				o->DeAllocate();
				objects.Remove(index);
			}
		}
	}

#pragma endregion Allocate / DeAllocate

	// Payload
#pragma region

	PayloadType* AllocatePayload()
	{
		for (int32 i = 0; i < PAYLOAD_SIZE; ++i)
		{
			PayloadIndex		 = (PayloadIndex + 1) % PAYLOAD_SIZE;
			PayloadType* Payload = Payloads[PayloadIndex];

			if (!Payload->bAllocated)
			{
				Payload->bAllocated = true;
				return Payload;
			}
		}
		checkf(0, TEXT("%s::AllocatePayload: Pool is exhausted"), *Name);
		return nullptr;
	}

#pragma endregion Payload

	ObjectType* Spawn(const EnumType& e, PayloadType* payload)
	{
		ObjectType* o = Allocate(e);

		o->Allocate(payload);

		LogTransaction(FunctionNames[(uint8)ECsManagerPooledObjectsFunctionNames::Spawn], ECsPoolTransaction::Allocate, o);
		payload->Reset();
		AddToActivePool(e, o);
		return o;
	}
};
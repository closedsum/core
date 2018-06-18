// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "GameFramework/Actor.h"
#include "Types/CsTypes_Pool.h"
#include "CsCVars.h"
#include "CsManager.generated.h"

// OnAllocate
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsManager_OnAllocate, const int32&, PoolIndex);
DECLARE_MULTICAST_DELEGATE_OneParam(FBindableEvent_CsManager_OnAllocate, const uint16&);
// OnDeAllocate
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsManager_OnDeAllocate, const int32&, PoolIndex);
DECLARE_MULTICAST_DELEGATE_OneParam(FBindableEvent_CsManager_OnDeAllocate, const uint16&);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FBindableDynEvent_CsManager_OnDeAllocateEX, const int32&, PoolIndex, const int32&, ActiveIndex, const uint8&, Type);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FBindableEvent_CsManager_OnDeAllocateEX, const uint16&, const uint16&, const uint8&);
// OnCreatePool
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsManager_OnCreatePool, UObject*, Object, const uint8&, Type);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsManager_OnCreatePool, UObject*, const uint8&);

UCLASS()
class CSCORE_API ACsManager : public AActor
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, Category = "Pool")
	virtual void Clear();
	UFUNCTION(BlueprintCallable, Category = "Pool")
	virtual void Shutdown();
	
	UFUNCTION(BlueprintCallable, Category = "Pool")
	virtual void CreatePool(const TSubclassOf<class UObject> &ObjectClass, const uint8 &Type, const int32 &Size);
	virtual void CreatePool(const TSubclassOf<class UObject> &ObjectClass, const int32 &Size);
	virtual void CreatePool(const int32 &Size);
	UFUNCTION(BlueprintCallable, Category = "Pool")
	void CreatePool_Script(const int32 &Size);

	UPROPERTY(BlueprintAssignable, Category = "Pool")
	FBindableDynEvent_CsManager_OnCreatePool OnCreatePool_ScriptEvent;

	FBindableEvent_CsManager_OnCreatePool OnCreatePool_Event;

	UFUNCTION(BlueprintCallable, Category = "Pool")
	virtual void AddToPool(UObject* InObject, const uint8 &Type);
	virtual void AddToPool(const TSubclassOf<class UObject> &ObjectClass, const uint8 &Type, const int32 &Size);
	UFUNCTION(BlueprintCallable, Category = "Pool")
	virtual void AddToActivePool(UObject* InObject, const uint8 &Type);
	UFUNCTION(BlueprintCallable, Category = "Pool")
	virtual int32 GetActivePoolSize(const uint8& Type);
	UFUNCTION(BlueprintCallable, Category = "Pool")
	virtual bool IsExhausted(const uint8 &Type);
	virtual void OnTick(const float &DeltaSeconds);

	UFUNCTION(BlueprintCallable, Category = "Pool")
	virtual void LogTransaction(const FString &FunctionName, const TEnumAsByte<ECsPoolTransaction::Type> &Transaction, UObject* InObject);

// Allocate
#pragma region
public:

	UPROPERTY(BlueprintAssignable, Category = "Pool")
	FBindableDynEvent_CsManager_OnAllocate OnAllocate_ScriptEvent;

	FBindableEvent_CsManager_OnAllocate OnAllocate_Event;
	
#pragma endregion Allocate

// DeAllocate
#pragma region
public:

	virtual void DeAllocate(const int32 &Index);
	UFUNCTION(BlueprintCallable, Category = "Pool")
	void DeAllocate_Script(const int32 &Index);
	UFUNCTION(BlueprintCallable, Category = "Pool")
	virtual void DeAllocate(const uint8 &Type, const int32 &Index);

	UPROPERTY(BlueprintAssignable, Category = "Pool")
	FBindableDynEvent_CsManager_OnDeAllocate OnDeAllocate_ScriptEvent;

	FBindableEvent_CsManager_OnDeAllocate OnDeAllocate_Event;

	UPROPERTY(BlueprintAssignable, Category = "Pool")
	FBindableDynEvent_CsManager_OnDeAllocateEX OnDeAllocateEX_ScriptEvent;

	FBindableEvent_CsManager_OnDeAllocateEX OnDeAllocateEX_Event;

	UFUNCTION(BlueprintCallable, Category = "Pool")
	virtual void DeAllocateAll();

	UFUNCTION(BlueprintCallable, Category = "Pool")
	void DeAllocateAll_Script();

#pragma endregion DeAllocate

	UPROPERTY(BlueprintReadWrite, Category = "Pool")
	int32 PoolSize;
};

namespace ECsManagerPooledObjectsFunctionNames
{
	enum Type
	{
		OnTick,
		DeAllocate,
		DeAllocateAll,
		Spawn,
		ECsManagerPooledObjectsFunctionNames_MAX,
	};
}

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

	TBaseDelegate<ObjectType*> ConstructObject_Call;

	TMulticastDelegate<void, ObjectType*> OnAddToPool_Event;
	TMulticastDelegate<void, ObjectType*> OnDeAllocate_Event;

	TAutoConsoleVariable<int32>* LogTransactions;

	TBaseDelegate<void, ObjectType*> OnTick_Handle_Object;

protected:
	FString FunctionNames[ECsManagerPooledObjectsFunctionNames::ECsManagerPooledObjectsFunctionNames_MAX];

	TArray<ObjectType*> Pool;
	int32 PoolSize;
	int32 PoolIndex;
	TArray<ObjectType*> ActiveObjects;

	PayloadType Payloads[PAYLOAD_SIZE];
	int32 PayloadIndex;

public:

	virtual void Init(const FString& name, const FString &objectClassName, UWorld* world, TAutoConsoleVariable<int32>* logTransactions)
	{
		Name = name;
		ObjectClassName = objectClassName;
		CurrentWorld = world;
		LogTransactions = logTransactions;

		FunctionNames[ECsManagerPooledObjectsFunctionNames::OnTick] = Name + TEXT("::OnTick");
		FunctionNames[ECsManagerPooledObjectsFunctionNames::DeAllocate] = Name + TEXT("::DeAllocate");
		FunctionNames[ECsManagerPooledObjectsFunctionNames::DeAllocateAll] = Name + TEXT("::DeAllocateAll");
		FunctionNames[ECsManagerPooledObjectsFunctionNames::Spawn] = Name + TEXT("::Spawn");
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
			Payloads[i].Reset();
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
		return ECsCached::Str::Empty;
	}

	virtual void CreatePool(const int32 &size)
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
		// TODO: Data needs to be set somewhere
		o->Cache.Init(0, nullptr, 0.0f, 0.0f, 0);
	}

	virtual void AddToActivePool(ObjectType* o)
	{
		o->Cache.IsAllocated = true;

		ActiveObjects.Add(o);
	}

	class UWorld* GetCurrentWorld()
	{
		return CurrentWorld.IsValid() ? CurrentWorld.Get() : nullptr;
	}

	virtual void LogTransaction(const FString &functionName, const TEnumAsByte<ECsPoolTransaction::Type> &transaction, ObjectType* o)
	{
		if ((*LogTransactions)->GetInt() == CS_CVAR_SHOW_LOG)
		{
			const FString& transactionAsString = ECsPoolTransaction::ToActionString(transaction);

			const FString objectName	= GetObjectName(o);
			const float currentTime		= GetCurrentTimeSeconds();
			const UObject* objectOwner	= o->Cache.GetOwner();
			const FString ownerName		= objectOwner ? objectOwner->GetName() : ECsCached::Str::None;
			const UObject* parent		= o->Cache.GetParent();
			const FString parentName	= parent ? parent->GetName() : ECsCached::Str::None;

			FString log = ECsCached::Str::Empty;

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
		const int32 objectCount = ActiveObjects.Num();
		int32 earliestIndex		= objectCount;

		for (int32 i = objectCount - 1; i >= 0; --i)
		{
			ObjectType* o = ActiveObjects[i];

			// Check if ObjectType was DeAllocated NOT in a normal way (i.e. Out of Bounds)

			if (!o->Cache.IsAllocated)
			{
				OnTick_Log_PrematureDeAllocation(o);

				LogTransaction(FunctionNames[ECsManagerPooledObjectsFunctionNames::OnTick], ECsPoolTransaction::Deallocate, o);

				ActiveObjects.RemoveAt(i);

				if (i < earliestIndex)
					earliestIndex = i;
				continue;
			}

			if (!o->Cache.bLifeTime)
			{
				OnTick_Handle_Object.ExecuteIfBound(o);
				continue;
			}

			if (GetCurrentTimeSeconds() - o->Cache.Time > o->Cache.LifeTime)
			{
				LogTransaction(FunctionNames[ECsManagerPooledObjectsFunctionNames::OnTick], ECsPoolTransaction::Deallocate, o);

				o->DeAllocate();
				ActiveObjects.RemoveAt(i);

				OnDeAllocate_Event.Broadcast(o);

				if (i < earliestIndex)
					earliestIndex = i;
				continue;
			}

			OnTick_Handle_Object.ExecuteIfBound(o);
		}

		// Update ActiveIndex
		if (earliestIndex != objectCount)
		{
			const int32 max = ActiveObjects.Num();

			for (int32 i = earliestIndex; i < max; ++i)
			{
				ObjectType* o = ActiveObjects[i];
				o->Cache.SetActiveIndex(i);
			}
		}
	}

	void OnTick_Log_PrematureDeAllocation(ObjectType* o)
	{
		const FString log = FString::Printf(TEXT("%s::OnTick: %s: %s at PoolIndex: %d was prematurely deallocted NOT in a normal way."), *Name, *ObjectClassName, *(GetObjectName(o)), o->Cache.Index);

		Log(log);
	}

	const TArray<ObjectType*>& GetAllActiveObjects()
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
			PoolIndex	  = (PoolIndex + i) % PoolSize;
			ObjectType* o = Pool[PoolIndex];

			if (!o->Cache.IsAllocated)
			{
				o->Cache.IsAllocated = true;
				return o;
			}
		}
		checkf(0, TEXT("%s::Allocate: Pool: %s is exhausted"), *Name);
		return nullptr;
	}

	bool DeAllocate(const int32 &index)
	{
		if (ActiveObjects.Num() == CS_EMPTY)
		{
			UE_LOG(LogCs, Warning, TEXT("%s::DeAllocate: %s at PoolIndex: %d is already deallocated."), *Name, *ObjectClassName, index);
			return false;
		}

		const int32 count = ActiveObjects.Num();

		for (int32 i = count - 1; i >= 0; --i)
		{
			ObjectType* o = ActiveObjects[i];

			// Update ActiveIndex
			if (i > CS_FIRST)
			{
				o->Cache.DecrementActiveIndex();
			}

			if (o->Cache.Index == index)
			{
				LogTransaction(FunctionNames[ECsManagerPooledObjectsFunctionNames::DeAllocate], ECsPoolTransaction::Deallocate, o);

				o->DeAllocate();
				ActiveObjects.RemoveAt(i);

				OnDeAllocate_Event.Broadcast(o);
				return true;
			}
		}

		// Correct on Cache "Miss"
		for (int32 i = 1; i < count; ++i)
		{
			ObjectType* o = ActiveObjects[i];
			// Reset ActiveIndex
			o->Cache.SetActiveIndex(i);
		}
		UE_LOG(LogCs, Warning, TEXT("%s::DeAllocate: %s at PoolIndex: %d is already deallocated."), *Name, *ObjectClassName, index);
		return false;
	}

	void DeAllocateAll()
	{
		const int32 count = ActiveObjects.Num();

		for (int32 i = count - 1; i >= 0; --i)
		{
			ObjectType* o = ActiveObjects[i];

			LogTransaction(FunctionNames[ECsManagerPooledObjectsFunctionNames::DeAllocateAll], ECsPoolTransaction::Deallocate, o);

			o->DeAllocate();
			ActiveObjects.RemoveAt(i);
		}
	}

#pragma endregion Allocate / DeAllocate

	// Payload
#pragma region

	PayloadType* AllocatePayload()
	{
		for (int32 i = 0; i < PAYLOAD_SIZE; ++i)
		{
			const int32 index = (PayloadIndex + i) % PAYLOAD_SIZE;
			PayloadType* Payload = &(Payloads[index]);

			if (!Payload->IsAllocated)
			{
				Payload->IsAllocated = true;
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

		o->Allocate(GetActivePoolSize(), payload);

		LogTransaction(FunctionNames[ECsManagerPooledObjectsFunctionNames::Spawn], ECsPoolTransaction::Allocate, o);
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

	TBaseDelegate<ObjectType*, const EnumType&> ConstructObject_Call;

	TMulticastDelegate<void, const EnumType&, ObjectType*> OnAddToPool_Event;
	TMulticastDelegate<void, const EnumType&, ObjectType*> OnDeAllocate_Event;

	TAutoConsoleVariable<int32>* LogTransactions;

	TBaseDelegate<void, ObjectType*> OnTick_Handle_Object;

protected:
	FString FunctionNames[ECsManagerPooledObjectsFunctionNames::ECsManagerPooledObjectsFunctionNames_MAX];

	TArray<ObjectType*> Pool;
	int32 PoolSize;
	TMap<EnumType, TArray<ObjectType*>> Pools;
	TMap<EnumType, int32> PoolSizes;
	TMap<EnumType, int32> PoolIndices;
	TMap<EnumType, TArray<ObjectType*>> ActiveObjects;

	PayloadType Payloads[PAYLOAD_SIZE];
	int32 PayloadIndex;

public:

	virtual void Init(const FString& name, const FString &objectClassName, UWorld* world, TAutoConsoleVariable<int32>* logTransactions)
	{
		Name			= name;
		ObjectClassName = objectClassName;
		CurrentWorld	= world;
		LogTransactions = logTransactions;

		FunctionNames[ECsManagerPooledObjectsFunctionNames::OnTick] = Name + TEXT("::OnTick");
		FunctionNames[ECsManagerPooledObjectsFunctionNames::DeAllocate] = Name + TEXT("::DeAllocate");
		FunctionNames[ECsManagerPooledObjectsFunctionNames::DeAllocateAll] = Name + TEXT("::DeAllocateAll");
		FunctionNames[ECsManagerPooledObjectsFunctionNames::Spawn] = Name + TEXT("::Spawn");
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
			Payloads[i].Reset();
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
		return ECsCached::Str::Empty;
	}

	virtual void CreatePool(const EnumType &e, const int32 &size)
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

	virtual void AddToPool(const EnumType &e, ObjectType* o)
	{
		int32* size = PoolSizes.Find(e);

		if (size)
			(*size)++;
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
		// TODO: Data needs to be set somewhere
		o->Cache.Init(0, nullptr, 0.0f, 0.0f, 0);
	}

	virtual void AddToActivePool(const EnumType &e, ObjectType* o)
	{
		o->Cache.IsAllocated = true;

		// Add to ActiveObjects
		TArray<ObjectType*>* poolPtr = ActiveObjects.Find(e);

		if (poolPtr)
		{
			poolPtr->Add(o);
		}
		else
		{
			TArray<ObjectType*> pool;
			pool.Add(o);
			ActiveObjects.Add(e, pool);
		}
	}

	class UWorld* GetCurrentWorld()
	{
		return CurrentWorld.IsValid() ? CurrentWorld.Get() : nullptr;
	}

	virtual const FString& EnumTypeToString(const EnumType &e)
	{
		return ECsCached::Str::Empty;
	}

	virtual const FString& EnumTypeToString(const int32& index)
	{
		return ECsCached::Str::Empty;
	}

	virtual void LogTransaction(const FString &functionName, const TEnumAsByte<ECsPoolTransaction::Type> &transaction, ObjectType* o)
	{
		if ((*LogTransactions)->GetInt() == CS_CVAR_SHOW_LOG)
		{
			const FString& transactionAsString = ECsPoolTransaction::ToActionString(transaction);

			const FString objectName	= GetObjectName(o);
			const FString typeAsString  = EnumTypeToString(o->Cache.Type);
			const float currentTime	    = GetCurrentTimeSeconds();
			const UObject* objectOwner  = o->Cache.GetOwner();
			const FString ownerName	    = objectOwner ? objectOwner->GetName() : ECsCached::Str::None;
			const UObject* parent	    = o->Cache.GetParent();
			const FString parentName    = parent ? parent->GetName() : ECsCached::Str::None;

			FString log = ECsCached::Str::Empty;

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

	virtual void OnTick(const float &deltaTime)
	{
		TArray<EnumType> Keys;
		ActiveObjects.GetKeys(Keys);

		for (const EnumType& key : Keys)
		{
			TArray<ObjectType*>& objects = ActiveObjects[key];

			const int32 objectCount = objects.Num();
			int32 earliestIndex		= objectCount;

			for (int32 j = objectCount - 1; j >= 0; --j)
			{
				ObjectType* o = objects[j];

				// Check if ObjectType was DeAllocated NOT in a normal way (i.e. Out of Bounds)

				if (!o->Cache.IsAllocated)
				{
					OnTick_Log_PrematureDeAllocation(key, o);

					LogTransaction(FunctionNames[ECsManagerPooledObjectsFunctionNames::OnTick], ECsPoolTransaction::Deallocate, o);

					objects.RemoveAt(j);

					if (j < earliestIndex)
						earliestIndex = j;
					continue;
				}

				if (!o->Cache.bLifeTime)
				{
					OnTick_Handle_Object.ExecuteIfBound(o);
					continue;
				}

				if (GetCurrentTimeSeconds() - o->Cache.Time > o->Cache.LifeTime)
				{
					LogTransaction(FunctionNames[ECsManagerPooledObjectsFunctionNames::OnTick], ECsPoolTransaction::Deallocate, o);

					o->DeAllocate();
					objects.RemoveAt(j);

					OnDeAllocate_Event.Broadcast(key, o);

					if (j < earliestIndex)
						earliestIndex = j;
					continue;
				}

				OnTick_Handle_Object.ExecuteIfBound(o);
			}

			// Update ActiveIndex
			if (earliestIndex != objectCount)
			{
				const int32 max = objects.Num();
				
				for (int32 j = earliestIndex; j < max; ++j)
				{
					ObjectType* o = objects[j];
					o->Cache.SetActiveIndex(j);
				}
			}
		}
	}

	void OnTick_Log_PrematureDeAllocation(const EnumType& e, ObjectType* o)
	{
		const FString log = FString::Printf(TEXT("%s::OnTick: %s: %s of type: %s at PoolIndex: %d was prematurely deallocted NOT in a normal way."), *Name, *ObjectClassName, *GetObjectName(o), *EnumTypeToString(e), o->Cache.Index);

		Log(log);
	}

	virtual void Log(const FString &log) {}

	void GetAllActiveObjects(TArray<ObjectType*> &outObjects)
	{
		TArray<EnumType> keys;
		ActiveObjects.GetKeys(keys);

		for (const EnumType& key : keys)
		{
			TArray<ObjectType*>& objects = ActiveObjects[key];

			for (ObjectType* o : objects)
			{
				outObjects.Add(o);
			}
		}
	}

	const TArray<ObjectType*>* GetObjects(const EnumType& type)
	{
		return Pools.Find(type);
	}

	int32 GetActivePoolSize(const EnumType &e)
	{
		TArray<ObjectType*>* objectsPtr = ActiveObjects.Find(e);

		if (!objectsPtr)
			return CS_EMPTY;
		return objectsPtr->Num();
	}

	bool IsExhausted(const EnumType &e)
	{
		TArray<ObjectType*>* poolPtr = Pools.Find(e);

		if (!poolPtr)
			return true;

		return GetActivePoolSize(e) >= poolPtr->Num();
	}

	// Allocate / DeAllocate
#pragma region

	virtual ObjectType* Allocate(const EnumType &e)
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
			*poolIndexPtr		= (*poolIndexPtr + i) % size;
			ObjectType* o		= (*pool)[*poolIndexPtr];

			if (!o->Cache.IsAllocated)
			{
				o->Cache.IsAllocated = true;
				return o;
			}
		}
		checkf(0, TEXT("%s::Allocate: Pool: %s is exhausted"), *Name, *EnumTypeToString(e));
		return nullptr;
	}

	bool DeAllocate(const EnumType &e, const int32 &index)
	{
		TArray<ObjectType*>* objectsPtr = ActiveObjects.Find(e);

		if (!objectsPtr)
		{
			UE_LOG(LogCs, Warning, TEXT("%s::DeAllocate: %s of Type: %s at PoolIndex: %d is already deallocated."), *Name, *ObjectClassName, *EnumTypeToString(e), index);
			return false;
		}

		const int32 count = objectsPtr->Num();

		for (int32 i = count - 1; i >= 0; --i)
		{
			ObjectType* o = (*objectsPtr)[i];

			// Update ActiveIndex
			if (i > CS_FIRST)
			{
				o->Cache.DecrementActiveIndex();
			}

			if (o->Cache.Index == index)
			{
				LogTransaction(FunctionNames[ECsManagerPooledObjectsFunctionNames::DeAllocate], ECsPoolTransaction::Deallocate, o);

				o->DeAllocate();
				objectsPtr->RemoveAt(i);

				OnDeAllocate_Event.Broadcast(e, o);
				return true;
			}
		}

		// Correct on Cache "Miss"
		for (int32 i = 1; i < count; ++i)
		{
			ObjectType* o = (*objectsPtr)[i];
			// Reset ActiveIndex
			o->Cache.SetActiveIndex(i);
		}
		UE_LOG(LogCs, Warning, TEXT("%s::DeAllocate: %s of Type: %s at PoolIndex: %d is already deallocated."), *Name, *ObjectClassName, *EnumTypeToString(e), index);
		return false;
	}

	void DeAllocateAll()
	{
		TArray<EnumType> keys;
		ActiveObjects.GetKeys(keys);

		for (const EnumType& key : keys)
		{
			TArray<ObjectType*>& objects = ActiveObjects[key];

			const int32 objectCount = objects.Num();

			for (int32 i = objectCount - 1; i >= 0; --i)
			{
				ObjectType* o = objects[i];

				LogTransaction(FunctionNames[ECsManagerPooledObjectsFunctionNames::DeAllocateAll], ECsPoolTransaction::Deallocate, o);

				o->DeAllocate();
				objects.RemoveAt(i);
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
			const int32 index    = (PayloadIndex + i) % PAYLOAD_SIZE;
			PayloadType* Payload = &(Payloads[index]);

			if (!Payload->IsAllocated)
			{
				Payload->IsAllocated = true;
				return Payload;
			}
		}
		checkf(0, TEXT("%s::AllocatePayload: Pool is exhausted"), *Name);
		return nullptr;
	}

#pragma endregion Payload

	ObjectType* Spawn(const EnumType &e, PayloadType* payload)
	{
		ObjectType* o = Allocate(e);

		o->Allocate(GetActivePoolSize(e), payload);

		LogTransaction(FunctionNames[ECsManagerPooledObjectsFunctionNames::Spawn], ECsPoolTransaction::Allocate, o);
		payload->Reset();
		AddToActivePool(e, o);
		return o;
	}
};
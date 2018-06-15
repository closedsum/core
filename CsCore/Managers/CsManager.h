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

template<typename EnumType, typename ObjectType, typename PayloadType, int32 PAYLOAD_SIZE = 1>
class TCsManagerPooledObjects
{
public:
	TCsManagerPooledObjects()
	{
		ConstructObject_Call.BindRaw(this, &TCsManagerPooledObjects::ConstructObject);
	}

	virtual ~TCsManagerPooledObjects()
	{
		Shutdown();
	}

public:
	FString Name;
	FString ObjectClassName;

	TWeakObjectPtr<class UWorld> CurrentWorld;

	TBaseDelegate<ObjectType*, const EnumType&> ConstructObject_Call;

	TMulticastDelegate<void, const EnumType&, ObjectType*> OnAddToPool_Event;
	TMulticastDelegate<void, const EnumType&, int32> OnDeAllocate_Event;

	TAutoConsoleVariable<int32>* LogTransactions;

	TBaseDelegate<void, ObjectType*> OnTick_Handle_Object;

protected:
	FString FunctionNames[ECsManagerPooledObjectsFunctionNames::ECsManagerPooledObjectsFunctionNames_MAX];

	TMap<EnumType, int32> PoolSizes;
	TArray<ObjectType*> Pool;
	TMap<EnumType, TArray<ObjectType*>> Pools;
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
		PoolSizes.Reset();

		const int32 count = Pool.Num();

		for (int32 i = 0; i < count; ++i)
		{
			Pool[i]->DeAllocate();
			DeconstructObject(Pool[i]);
		}

		Pool.Reset();
		Pools.Reset();
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

		TArray<ObjectType*>* poolPtr = Pools.Find(e);

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
			const FString& TransactionAsString = ECsPoolTransaction::ToActionString(transaction);

			const FString ObjectName	= GetObjectName(o);
			const FString TypeAsString  = EnumTypeToString(o->Cache.Type);
			const float CurrentTime	    = GetCurrentTimeSeconds();
			const UObject* ObjectOwner  = o->Cache.GetOwner();
			const FString OwnerName	    = ObjectOwner ? ObjectOwner->GetName() : ECsCached::Str::None;
			const UObject* Parent	    = o->Cache.GetParent();
			const FString ParentName    = Parent ? Parent->GetName() : ECsCached::Str::None;

			FString OutLog = ECsCached::Str::Empty;

			if (ObjectOwner && Parent)
			{
				OutLog = FString::Printf(TEXT("%s: %s %s: %s of Type: %s at %f for %s attached to %s."), *functionName, *TransactionAsString, *ObjectClassName, *ObjectName, *TypeAsString, CurrentTime, *OwnerName, *ParentName);
			}
			else
			if (ObjectOwner)
			{
				OutLog = FString::Printf(TEXT("%s: %s %s: %s of Type: %s at %f for %s."), *functionName, *TransactionAsString, *ObjectClassName, *ObjectName, *TypeAsString, CurrentTime, *OwnerName);
			}
			else
			if (Parent)
			{
				OutLog = FString::Printf(TEXT("%s: %s %s: %s of Type: %s at %f attached to %s."), *functionName, *TransactionAsString, *ObjectClassName, *ObjectName, *TypeAsString, CurrentTime, *ParentName);
			}
			else
			{
				OutLog = FString::Printf(TEXT("%s: %s %s: %s of Type: %s at %f."), *functionName, *TransactionAsString, *ObjectClassName, *ObjectName, *TypeAsString, CurrentTime);
			}
			LogTransaction_Internal(OutLog);
		}
	}

	virtual void LogTransaction_Internal(const FString& outLog){}

	virtual float GetCurrentTimeSeconds()
	{
		return GetCurrentWorld() ? GetCurrentWorld()->GetTimeSeconds() : 0.0f;
	}

	void OnTick(const float &deltaTime)
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
					//UE_LOG(LogCs, Warning, TEXT("ACsManager_InteractiveActor::OnTick: InteractiveActor: %s at PoolIndex: %s was prematurely deallocted NOT in a normal way."), *(Actor->GetName()), Actor->Cache.Index);

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

					OnDeAllocate_Event.Broadcast(key, o->Cache.Index);

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

	ObjectType* Allocate(const EnumType &e)
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

		const int32 keyCount = keys.Num();

		for (int32 i = 0; i < keyCount; ++i)
		{
			const EnumType& key = keys[i];

			TArray<ObjectType*>& objects = ActiveObjects[key];

			const int32 objectCount = objects.Num();

			for (int32 j = objectCount - 1; j >= 0; --j)
			{
				LogTransaction(FunctionNames[ECsManagerPooledObjectsFunctionNames::DeAllocateAll], ECsPoolTransaction::Deallocate, objects[j]);

				objects[j]->DeAllocate();
				objects.RemoveAt(j);
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
// Copyright 2017 Respawn Entertainment, Inc. All rights reserved.

#pragma once
#include "Managers/Pool/CsPooledObject.h"
#include "CsCVars.h"

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
		return NRsCached::Str::Empty;
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
	* Destroys or deletes the object
	*/
	virtual void DeconstructObject(const FCsPooledObject& O)
	{
	}

	virtual FString GetObjectName(const FCsPooledObject& O)
	{
		return NRsCached::Str::Empty;
	}

#pragma endregion Object

// Pool
#pragma region
protected:

	FString FunctionNames[(uint8)ECsManagerPooledObjectMapFunctionNames::ECsManagerPooledObjectMapFunctionNames_MAX];

	TMap<KeyType, FCsManagerPooledObjectConstructParams> ConstructParams;

	TMap<KeyType, ICsManager_PooledObject*> Pools;

public:

	TBaseDelegate<ICsManager_PooledObject*, const KeyType&> ConstructManagerPooledObjects_Impl;

	ICsManager_PooledObject* ConstructManagerPooledObjects(const KeyType& Type)
	{
		return new FCsManager_PooledObject();
	}

	ICsManager_PooledObject* GetPool(const KeyType& Type)
	{
		return CheckAndAddType(Type);
	}

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

		CurrentCreatePoolType = Type;
		FDelegateHandle Handle = Pool->GetOnAddToPool_Event().AddRaw(this, &TRsManager_PooledObjects_Map<KeyType>::OnCreatePool_AddToPool);

		Pool->CreatePool(Size);

		Pool->GetOnAddToPool_Event().Remove(Handle);
	}

	virtual void CreatePool(const KeyType& Type, const int32& Size)
	{
		FCsManagerPooledObjectParams Params;
		Params.Name		= Name + TEXT("_") + KeyTypeToString(Type);
		Params.World	= GetCurrentWorld();
		Params.LogType  = LogType;

		CreatePool(Params, Type, Size);
	}

private:

	KeyType CurrentCreatePoolType;

	void OnCreatePool_AddToPool(const FCsPooledObject& Object)
	{
		OnAddToPool_Event.Broadcast(CurrentCreatePoolType, Object);
	}

private:

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
		}
		else
		{
			Pool = *PoolPtr;
		}
		return Pool;
	}

public:

	virtual void AddToPool(const KeyType& Type, ICsPooledObject* PooledObject, UObject* Object)
	{
		ICsManager_PooledObject* Pool = CheckAndAddType(Type);

		Pool->AddToPool(PooledObject, Object);

		const TArray<FCsPooledObject>& Objects = Pool->GetObjects();
		const int32& Index					   = PooledObject->GetCache()->GetIndex();
		const FCsPooledObject& O			   = Objects[Index];

		OnAddToPool_Event.Broadcast(Type, O);
	}

	virtual void AddToPool(const KeyType& Type, ICsPooledObject* Object)
	{
		AddToPool(Type, Object, nullptr);
	}

	TMulticastDelegate<void, const KeyType&, const FCsPooledObject&> OnAddToPool_Event;

	virtual void AddToActivePool(const KeyType& Type, ICsPooledObject* PooledObject, UObject* Object)
	{
		ICsManager_PooledObject* Pool = CheckAndAddType(Type);

		const int32& Index = PooledObject->GetCache()->GetIndex();

		checkf(Index < Pool->GetPoolSize(), TEXT("%:AddToActivePool: PooledObject is in another pool."), *Name);

		if (Index <= INDEX_NONE)
		{
			AddToPool(Type, PooledObject, Object);
		}

		Pool->AddToActivePool(PooledObject, Object);

		const TArray<FCsPooledObject>& Objects = Pool->GetObjects();
		const FCsPooledObject& O			   = Objects[Index];

		OnAddToActivePool_Event.Broadcast(Type, O);
	}

	virtual void AddToActivePool(const KeyType& Type, ICsPooledObject* Object)
	{
		AddToActivePool(Type, Object, nullptr);
	}

	TMulticastDelegate<void, const KeyType&, const FCsPooledObject&> OnAddToActivePool_Event;

public:

	const TArray<FCsPooledObject>& GetAllActiveObjects(const KeyType& Type)
	{
		ICsManager_PooledObject* Pool = CheckAndAddType(Type);
		return Pool->GetAllActiveObjects();
	}

	const TArray<FCsPooledObject>& GetObjects(const KeyType& Type)
	{
		ICsManager_PooledObject* Pool = CheckAndAddType(Type);
		return Pool->GetObjects();
	}

	int32 GetActivePoolSize(const KeyType& Type)
	{
		ICsManager_PooledObject* Pool = CheckAndAddType(Type);
		return Pool->GetActivePoolSize();
	}

	bool IsExhausted(const KeyType& Type)
	{
		ICsManager_PooledObject* Pool = CheckAndAddType(Type);
		return Pool->IsExhausted();
	}

#pragma endregion Pool

// Tick
#pragma region
public:

	virtual void OnTick(const float& DeltaTime)
	{
		for (TPair<KeyType, ICsManager_PooledObject*>& Pair : Pools)
		{
			Pair.Value->OnTick(DeltaTime);
		}
	}

#pragma endregion Tick

// Payload
#pragma region
public:

	void CreatePayloads(const KeyType& Type, const int32& Size)
	{
		ICsManager_PooledObject* Pool = CheckAndAddType(Type);
		Pool->CreatePayloads(Size);
	}

	void DestroyPayloads(const KeyType& Type)
	{
		ICsManager_PooledObject* Pool = CheckAndAddType(Type);
		Pool->DestroyPayloads();
	}

	ICsPooledObjectPayload* AllocatePayload(const KeyType& Type)
	{
		ICsManager_PooledObject* Pool = CheckAndAddType(Type);

		ICsPooledObjectPayload* Payload = Pool->AllocatePayload();

		checkf(Payload, TEXT("%s::AllocatePayload: Pool: %s is exhausted"), *Name, *KeyTypeToString(Type));

		return Payload;
	}

#pragma endregion Payload

// Log
#pragma region
protected:

	virtual void Log(const FString& InLog){}

	FECsCVarLog LogType;

	virtual void LogTransaction(const FString& FunctionName, const ERsPoolTransaction& Transaction, ICsPooledObject* O)
	{

	}

#pragma endregion Log

// Spawn
#pragma region
public:

	virtual const FCsPooledObject& Spawn(const KeyType& Type, ICsPooledObjectPayload* Payload)
	{
		ICsManager_PooledObject* Pool = CheckAndAddType(Type);

		const FCsPooledObject& Object = Pool->Spawn(Payload);

		OnSpawn_Event.Broadcast(Type, Object);
		return Object;
	}

	TMulticastDelegate<void, const KeyType&, const FCsPooledObject&> OnSpawn_Event;

#pragma endregion Spawn

// Destroy
#pragma region
public:

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

	TMulticastDelegate<void, const KeyType&, const FCsPooledObject&> OnDestroy_Event;

#pragma endregion Destroy
};
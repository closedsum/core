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
	* Destroys or deletes the object
	*/
	virtual void DeconstructObject(const FCsPooledObject& O)
	{
	}

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

	TBaseDelegate<ICsManager_PooledObject*, const KeyType&> ConstructManagerPooledObjects_Impl;

	ICsManager_PooledObject* ConstructManagerPooledObjects(const KeyType& Type)
	{
		return new FCsManager_PooledObject();
	}

	ICsManager_PooledObject* GetManagerPooledObjects(const KeyType& Type)
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

		// Bind the appropriate Script delegates.
		Pool->GetScript_GetCache_Impl() = Script_GetCache_Impl;
		Pool->GetScript_Allocate_Impl() = Script_Allocate_Impl;
		Pool->GetScript_Deallocate_Impl() = Script_Deallocate_Impl;

		// Bind to OnAddToPool so the event OnAddToPool_Event can properly broadcast events.
		CurrentCreatePoolType = Type;
		FDelegateHandle Handle = Pool->GetOnAddToPool_Event().AddRaw(this, &TCsManager_PooledObject_Map<KeyType>::OnCreatePool_AddToPool);

		Pool->CreatePool(Size);

		Pool->GetOnAddToPool_Event().Remove(Handle);

		Pool->GetOnUpdate_Object_Event().AddRaw(this, &TCsManager_PooledObject_Map<KeyType>::OnUpdate_Pool_Object);
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

	// Add
#pragma region
public:

	/**
	* Adds an Object to the pool of appropriate Type.
	*  The Object must implement the interface: ICsPooledObject.
	*
	* @param Type			Type of pool to add the Object to.
	* @param PooledObject	Object that implements the interface: ICsPooledObject.
	* @param Object			UObject reference.
	* return				Reference to the container for the Pooled Object.
	*/
	const FCsPooledObject& AddToPool(const KeyType& Type, ICsPooledObject* PooledObject, UObject* Object)
	{
		ICsManager_PooledObject* Pool = CheckAndAddType(Type);

		const FCsPooledObject& O = Pool->AddToPool(PooledObject, Object);

		OnAddToPool_Event.Broadcast(Type, O);

		return O;
	}

	const FCsPooledObject& AddToPool(const KeyType& Type, ICsPooledObject* Object)
	{
		return AddToPool(Type, Object, nullptr);
	}

	const FCsPooledObject& AddToPool(const KeyType& Type, UObject* Object)
	{
		ICsManager_PooledObject* Pool = CheckAndAddType(Type);

		const FCsPooledObject& O = Pool->AddToPool(Object);

		OnAddToPool_Event.Broadcast(Type, O);

		return O;
	}

	/** */
	TMulticastDelegate<void, const KeyType& /*Type*/, const FCsPooledObject& /*Object*/> OnAddToPool_Event;

	const FCsPooledObject& AddToAllocatedObjects(const KeyType& Type, ICsPooledObject* PooledObject, UObject* Object)
	{
		checkf(PooledObject, TEXT("%s::AddToAllocatedObjects: PooledObject is NULL."), *Name);

		ICsManager_PooledObject* Pool = CheckAndAddType(Type);

		const int32& Index = PooledObject->GetCache()->GetIndex();

		checkf(Index < Pool->GetPoolSize(), TEXT("%::AddToAllocatedObjects: PooledObject is in another pool."), *Name);

		const FCsPooledObject& O = Pool->AddToAllocatedObjects(PooledObject, Object);

		OnAddToAllocatedObjects_Event.Broadcast(Type, O);

		return O;
	}

	const FCsPooledObject& AddToAllocatedObjects(const KeyType& Type, ICsPooledObject* Object)
	{
		return AddToAllocatedObjects(Type, Object, nullptr);
	}

	const FCsPooledObject& AddToAllocatedObjects(const KeyType& Type, UObject* Object)
	{
		checkf(Object, TEXT("%s::AddToAllocatedObjects: Object is NULL."), *Name);

		ICsManager_PooledObject* Pool = CheckAndAddType(Type);

		const FCsPooledObject& O = Pool->AddToAllocatedObjects(Object);

		OnAddToAllocatedObjects_Event.Broadcast(Type, O);

		return O;
	}

	/** */
	TMulticastDelegate<void, const KeyType& /*Type*/, const FCsPooledObject& /*Object*/> OnAddToAllocatedObjects_Event;

#pragma endregion Add

public:

	FORCEINLINE const TArray<FCsPooledObject>& GetPool(const KeyType& Type)
	{
		return CheckAndAddType(Type)->GetPool();
	}

	FORCEINLINE const TArray<FCsPooledObject>& GetAllocatedObjects(const KeyType& Type)
	{
		return CheckAndAddType(Type)->GetAllocatedObjects();
	}

	FORCEINLINE const int32& GetPoolSize(const KeyType& Type)
	{
		return CheckAndAddType(Type)->GetPoolSize();
	}

	FORCEINLINE int32 GetAllocatedObjectsSize(const KeyType& Type)
	{
		return CheckAndAddType(Type)->GetAllocatedObjectsSize();
	}

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
	* @param KeyType	Current type of pool.
	* @param Object		Container holding a pooled object.
	*/
	DECLARE_DELEGATE_TwoParams(FOnUpdate_Object, const KeyType& /*Type*/, const FCsPooledObject& /*Object*/);

	/** Delegate called when updating a pooled object. */
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
		OnUpdate_Object_Event.Execute(CurrentCreatePoolType, Object);
	}

#pragma endregion Update

// Payload
#pragma region
public:

	void ConstructPayloads(const KeyType& Type, const int32& Size)
	{
		ICsManager_PooledObject* Pool = CheckAndAddType(Type);
		Pool->ConstructPayloads(Size);
	}

	void DeconstructPayloads(const KeyType& Type)
	{
		ICsManager_PooledObject* Pool = CheckAndAddType(Type);
		Pool->DeconstructPayloads();
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

	virtual void LogTransaction(const FString& FunctionName, const ECsPoolTransaction& Transaction, ICsPooledObject* O)
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

// Script
#pragma region
public:

	FCsPooledObject::FScript_GetCache Script_GetCache_Impl;

	FCsPooledObject::FScript_Allocate Script_Allocate_Impl;

	FCsPooledObject::FScript_Deallocate Script_Deallocate_Impl;

#pragma endregion Script
};
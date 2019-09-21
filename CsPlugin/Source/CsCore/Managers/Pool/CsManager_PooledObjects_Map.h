// Copyright 2017 Respawn Entertainment, Inc. All rights reserved.

#pragma once
#include "Managers/Pool/CsPooledObject.h"
#include "CsCVars.h"

enum class ECsManagerPooledObjectsMapFunctionNames : uint8
{
	OnTick,
	Deallocate,
	DeallocateAll,
	Spawn,
	ECsManagerPooledObjectsMapFunctionNames_MAX,
};

class UWorld;
class UObject;
class UClass;
class ICsPooledObject;
struct ICsPooledObjectPayload;

template<typename KeyType>
class TCsManager_PooledObjects_Map : public ICsManager_PooledObjects
{
public:
	TCsManager_PooledObjects_Map()
	{
		Name = NCsCached::Str::Empty;
		ClassNames.Reset();
		ClassMap.Reset();

		CurrentWorld = nullptr;

		OnAddToPool_Event.Clear();
		OnDeallocate_Event.Clear();

		Pool.Reset();
		PoolSize = 0;
		Pools.Reset();
		PoolSizes.Reset();
		PoolIndices.Reset();

		ActiveObjects.Reset();
		ActiveObjectSizes.Reset();

		Payloads.Reset();
		PayloadSizes.Reset();;
		PayloadIndices.Reset();

		OnSpawn_Event.Clear();
	}

	virtual ~TCsManager_PooledObjects_Map()
	{
		Shutdown();
	}

protected:

	FString Name;
	
	TMap<KeyType, FString> ClassNames;
	TMap<KeyType, UClass*> ClassMap;

	ECsPooledObjectConstruction ConstructionType;

public:

	/**
	* Init
	*/
	virtual void Init(const FString& InName, TMap<KeyType, UClass*>& InClassMap, UWorld* World, const ERsPooledObjectConstruction& InConstructionType, const FERsCVarLog& InLogType)
	{
		Name = InName;
		
		ClassMap = InClassMap;

		for (TPair<KeyType, UClass*> Pair : ClassMap)
		{
			ClassNames.Add(Pair.Key, Pair.Value->GetName());
		}

		CurrentWorld	 = World;
		ConstructionType = InConstructionType;
		LogType			 = InLogType;

		ConstructObject_Call.BindRaw(this, &TCsManager_PooledObjects_Map::ConstructObject);

		FunctionNames[(uint8)ECsManagerPooledObjectsMapFunctionNames::OnTick]		 = Name + TEXT("::OnTick");
		FunctionNames[(uint8)ECsManagerPooledObjectsMapFunctionNames::Deallocate]	 = Name + TEXT("::Deallocate");
		FunctionNames[(uint8)ECsManagerPooledObjectsMapFunctionNames::DeallocateAll] = Name + TEXT("::DeallocateAll");
		FunctionNames[(uint8)ECsManagerPooledObjectsMapFunctionNames::Spawn]		 = Name + TEXT("::Spawn");
	}

	/**
	* Resets but does NOT delete memory allocations
	*/
	virtual void Clear()
	{
		for (ICsPooledObject* O : Pool)
		{
			O->Deallocate();
			DeconstructObject(O);
		}

		Pool.Reset();
		PoolSize = 0;

		for (TPair<KeyType, TArray<ICsPooledObject*>>& Pair : Pools)
		{
			Pair.Value.Reset();
		}

		for (TPair<KeyType, int32>& Pair : PoolSizes)
		{
			Pair.Value = 0;
		}
		
		for (TPair<KeyType, TArray<ICsPooledObject*>>& Pair : ActiveObjects)
		{
			Pair.Value.Reset();
		}

		for (TPair<KeyType, TArray<ICsPooledObjectPayload*>>& Pair : Payloads)
		{
			for (ICsPooledObjectPayload* P : Pair.Value)
			{
				P->Reset();
			}
		}
		OnAddToPool_Event.Clear();
		OnDeallocate_Event.Clear();
	}

	/**
	* Resets and deletes all memory allocation. Called when terminating the manager
	*/
	virtual void Shutdown()
	{
		Clear();

		for (TPair<KeyType, TArray<ICsPooledObjectPayload*>>& Pair : Payloads)
		{
			for (ICsPooledObjectPayload* P : Pair.Value)
			{
				delete P;
			}
		}

		Payloads.Reset();

		OnTick_Handle_Object.Unbind();
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

	virtual const FString& KeyTypeToString(const int32& Index)
	{
		return NCsCached::Str::Empty;
	}

// Object
#pragma region
protected:

	/**
	* Creates a pooled object of type IRsPooledObject
	*/
	virtual ICsPooledObject* ConstructObject(const KeyType& Type)
	{
		return nullptr;
	}

	/** Delegate for calling ConstructObject. This is provided to override the base behavior */
	TBaseDelegate<ICsPooledObject*, const KeyType&> ConstructObject_Call;

	/**
	* Destroys or deletes the object
	*/
	virtual void DeconstructObject(ICsPooledObject* O)
	{
	}

	virtual FString GetObjectName(ICsPooledObject* O)
	{
		return NCsCached::Str::Empty;
	}

#pragma endregion Object

// Pool
#pragma region
protected:

	FString FunctionNames[(uint8)ECsManagerPooledObjectsMapFunctionNames::ECsManagerPooledObjectsMapFunctionNames_MAX];

	TArray<ICsPooledObject*> Pool;
	int32 PoolSize;
	TMap<KeyType, TArray<ICsPooledObject*>> Pools;
	TMap<KeyType, TArray<TLinkedList<ICsPooledObject*>*>> Links;
	TMap<KeyType, int32> PoolSizes;
	TMap<KeyType, int32> PoolIndices;

	TMap<KeyType, TArray<ICsPooledObject*>> ActiveObjects;
	TMap<KeyType, TLinkedList<ICsPooledObject*>*> ActiveHeads;
	TMap<KeyType, TLinkedList<ICsPooledObject*>*> ActiveTails;
	TMap<KeyType, int32> ActiveObjectSizes;

public:

	virtual void CreatePool(const KeyType& Type, const int32& Size)
	{
		PoolSize += Size;

		TArray<ICsPooledObject*>& P = Pools.Add(Type);
		TArray<TLinkedList<ICsPooledObject*>*>& L = Links.Add(Type);
		PoolSizes.Add(Type, Size);
		PoolIndices.Add(Type, 0);
		
		P.Reserve(Size);

		TArray<ICsPooledObject*>& A = ActiveObjects.Add(Type);
		ActiveObjectSizes.Add(Type, 0);
		
		A.Reserve(Size);

		ActiveHeads.Add(Type, nullptr);
		ActiveTails.Add(Type, nullptr);

		for (int32 I = 0; I < Size; ++I)
		{
			ICsPooledObject* O = ConstructObject_Call.Execute(Type);
			O->GetCache()->Init(I);
			O->Deallocate();
			P.Add(O);
			Pool.Add(O);

			// Add Link
			L.Add(new TLinkedList<ICsPooledObject*>());
			// Set Element for Link
			TLinkedList<ICsPooledObject*>* Link = L.Last();
			**Link = O;

			OnAddToPool_Event.Broadcast(Type, O);
		}
	}

private:

	void CheckAndAddType(const KeyType& Type)
	{
		if (!Pools.Find(Type))
		{
			Pools.Add(Type);
			Links.Add(Type);
			PoolSizes.Add(Type, 0);
			PoolIndices.Add(Type, 0);
			ActiveObjects.Add(Type);
			ActiveObjectSizes.Add(Type, 0);
			ActiveHeads.Add(Type, nullptr);
			ActiveTails.Add(Type, nullptr);
		}
	}

public:

	virtual void AddToPool(const KeyType& Type, ICsPooledObject* Object)
	{
		CheckAndAddType(Type);

		TArray<ICsPooledObject*>& P = Pools[Type];
		P.Add(Object);
		Pool.Add(Object);
		int32& Size = PoolSizes[Type];
		PoolIndices[Type];
		Size = P.Num();
		PoolSize += Size;
		Object->GetCache()->Init(Pool.Num() - 1);
		Object->Deallocate();

		// Add Link
		TArray<TLinkedList<ICsPooledObject*>*>& L = Links[Type];
		L.Add(new TLinkedList<ICsPooledObject*>());
		// Set Element for Link
		TLinkedList<ICsPooledObject*>* Link = L.Last();
		**Link								= Object;

		TArray<ICsPooledObject*>& A = ActiveObjects[Type];

		A.Reserve(A.Num() + 1);

		OnAddToPool_Event.Broadcast(Type, Object);
	}

	TMulticastDelegate<void, const KeyType&, ICsPooledObject*> OnAddToPool_Event;

	virtual void AddToActivePool(const KeyType& Type, ICsPooledObject* Object)
	{
		CheckAndAddType(Type);
		// TODO: Do check is Object is in Pool
		AddToActivePool_Internal(Type, Object);
	}

protected:

	virtual void AddToActivePool_Internal(const KeyType& Type, ICsPooledObject* Object)
	{
		AddActiveLink(Type, Links[Type][Object->GetCache()->GetIndex()]);
		TArray<ICsPooledObject*>& A = ActiveObjects[Type];
		A.Add(Object);
	}

	virtual void AddActiveLink(const KeyType& Type, TLinkedList<ICsPooledObject*>* Link)
	{
		TLinkedList<ICsPooledObject*>*& Tail = ActiveTails[Type];

		if (Tail)
		{
			Link->LinkAfter(Tail);
			Tail = Link;
		}
		else
		{
			TLinkedList<ICsPooledObject*>*& Head = ActiveHeads[Type];

			Head = Link;
			Tail = Link;
		}
	}

	virtual void RemoveActiveLink(const KeyType& Type, TLinkedList<ICsPooledObject*>* Link)
	{
		TLinkedList<ICsPooledObject*>*& Head = ActiveHeads[Type];

		// Check to Update HEAD
		if (Link == Head)
		{
			if (ActiveObjectSizes[Type] > RS_SINGLETON)
			{
				Head = Link->GetNextLink();
			}
			else
			{
				Head			  = nullptr;
				ActiveTails[Type] = nullptr;
			}
		}
		Link->Unlink();
	}

public:

	const TArray<ICsPooledObject*>& GetAllActiveObjects(const KeyType& Type)
	{
		CheckAndAddType(Type);
		return ActiveObjects[Type];
	}

	const TArray<ICsPooledObject*>& GetObjects(const KeyType& Type)
	{
		CheckAndAddType(Type);
		return Pools[Type];
	}

	const int32& GetActivePoolSize(const KeyType& Type)
	{
		CheckAndAddType(Type);
		return ActiveObjectSizes[Type];
	}

	bool IsExhausted(const KeyType& Type)
	{
		CheckAndAddType(Type);
		return PoolSizes[Type] == ActiveObjectSizes[Type];
	}

#pragma endregion Pool

// Tick
#pragma region
protected:

	virtual void OnTick(const float &DeltaTime)
	{
		for (TPair<KeyType, TLinkedList<ICsPooledObject*>*>& Pair : ActiveHeads)
		{
			const KeyType& Type = Pair.Key;

			TLinkedList<ICsPooledObject*>* Current = Pair.Value;
			TLinkedList<ICsPooledObject*>* Next    = Current;

			int32 NewSize = 0;

			TArray<ICsPooledObject*>& A = ActiveObjects[Type];
			int32& Size					= ActiveObjectSizes[Type];

			while (Next)
			{
				Current			   = Next;
				ICsPooledObject* O = **Current;
				Next			   = Current->GetNextLink();

				// Check if ObjectType was Deallocated NOT in a normal way (i.e. Out of Bounds)

				if (!O->GetCache()->IsAllocated())
				{
#if !UE_BUILD_SHIPPING
					//UE_LOG(LogRs, Warning, TEXT("%s::OnTick: %s: %s at PoolIndex: %d was prematurely deallocated NOT in a normal way."), *Name, *ObjectClassName, *(GetObjectName(O)), O->GetCache()->GetIndex());

					//LogTransaction(FunctionNames[(uint8)ERsManagerPooledObjectsFunctionNames::OnTick], ERsPoolTransaction::Deallocate, O);
#endif // #if !UE_BUILD_SHIPPING
					RemoveActiveLink(Type, Current);
					continue;
				}

				if (!O->GetCache()->UseLifeTime())
				{
					OnTick_Handle_Object.ExecuteIfBound(Type, O);
					continue;
				}

				if (GetCurrentTimeSeconds() - O->GetCache()->GetTime() > O->GetCache()->GetLifeTime())
				{
#if !UE_BUILD_SHIPPING
					//LogTransaction(FunctionNames[(uint8)ERsManagerPooledObjectsFunctionNames::OnTick], ERsPoolTransaction::Deallocate, O);
#endif // #if !UE_BUILD_SHIPPING
					O->Deallocate();
					RemoveActiveLink(Type, Current);

					OnDeallocate_Event.Broadcast(Type, O);
					continue;
				}

				if (NewSize < Size)
					A[NewSize] = O;

				OnTick_Handle_Object.ExecuteIfBound(Type, O);
				++NewSize;
			}

			for (int32 I = Size - 1; I >= NewSize; --I)
			{
				A.RemoveAt(I, 1, false);
			}
			Size = A.Num();
		}
	}

	TBaseDelegate<void, const KeyType&, ICsPooledObject*> OnTick_Handle_Object;

#pragma endregion Tick

// Allocate / DeAllocate
#pragma region
protected:

	ICsPooledObject* Allocate(const KeyType& Type, ICsPooledObjectPayload* Payload)
	{
		if (IsExhausted(Type))
		{
			checkf(0, TEXT("%s::Allocate: Pool: %s is exhausted"), *Name, *KeyTypeToString(Type));
			return nullptr;
		}

		TArray<ICsPooledObject*>& P = Pools[Type];
		const int32& Size			= PoolSizes[Type];
		int32& PoolIndex			= PoolIndices[Type];

		for (int32 I = 0; I < Size; ++I)
		{
			PoolIndex		   = (PoolIndex + 1) % Size;
			ICsPooledObject* O = P[PoolIndex];

			if (!O->GetCache()->IsAllocated())
			{
				O->Allocate(Payload);
				return O;
			}
		}
		checkf(0, TEXT("%s::Allocate: Pool: %s is exhausted"), *Name, *KeyTypeToString(Type));
		return nullptr;
	}

public:

	bool Deallocate(const KeyType& Type, const int32& Index)
	{
		CheckAndAddType(Type);

		if (Index >= PoolSizes[Type])
		{
			//UE_LOG(LogRs, Warning, TEXT("%s::DeAllocate: %s with PoolIndex: %d is NOT in the Pool. Call AddToPool."), *Name, *ObjectClassName, Index);
			return false;
		}

		TArray<TLinkedList<ICsPooledObject*>*>& L = Links[Type];
		TLinkedList<ICsPooledObject*>*& Head	  = ActiveHeads[Type];

		if (L[Index] != Head &&
			!L[Index]->IsLinked())
		{
			//UE_LOG(LogRs, Warning, TEXT("%s::DeAllocate: %s at PoolIndex: %d is already deallocated or not in the Pool."), *Name, *ObjectClassName, Index);
			return false;
		}

		if (ActiveObjectsSize == RS_EMPTY)
		{
			//UE_LOG(LogRs, Warning, TEXT("%s::DeAllocate: %s at PoolIndex: %d is already deallocated or not in the Pool."), *Name, *ObjectClassName, Index);
			return false;
		}

	
		TLinkedList<ICsPooledObject*>* Link = L[Index];
		ICsPooledObject* O					= **Link;

#if !UE_BUILD_SHIPPING
		//LogTransaction(FunctionNames[(uint8)ERsManagerPooledObjectsFunctionNames::Deallocate], ERsPoolTransaction::Deallocate, O);
#endif // #if !UE_BUILD_SHIPPING

		O->Deallocate();
		RemoveActiveLink(Type, Link);

		TLinkedList<ICsPooledObject*>* Current = Head;
		TLinkedList<ICsPooledObject*>* Next	   = Current;

		int32 NewSize = 0;

		TArray<ICsPooledObject*>& A = ActiveObjects[Type];
		int32& Size					= ActiveObjectSizes[Size];

		while (Next)
		{
			Current	 = Next;
			O		 = **Current;
			Next	 = Current->GetNextLink();

			if (NewSize < Size)
			{
				A[NewSize] = O;
			}

			++NewSize;
		}

		for (int32 I = Size - 1; I >= NewSize; --I)
		{
			A.RemoveAt(I, 1, false);
		}
		Size = A.Num();

		OnDeallocate_Event.Broadcast(O);
		return true;
	}

	TMulticastDelegate<void, const KeyType&, ICsPooledObject*> OnDeallocate_Event;

	void DeallocateAll()
	{
		for (TPair<KeyType, TLinkedList<ICsPooledObject*>*>& Pair : ActiveHeads)
		{
			const KeyType& Type = Pair.Key;

			TArray<ICsPooledObject*>& A = ActiveObjects[Type];

			for (ICsPooledObject* O : A)
			{
#if !UE_BUILD_SHIPPING
				//LogTransaction(FunctionNames[(uint8)ERsManagerPooledObjectsFunctionNames::DeallocateAll], ERsPoolTransaction::Deallocate, O);
#endif // #if !UE_BUILD_SHIPPING
				O->Deallocate();
				OnDeallocate_Event.Broadcast(Type, O);
			}

			A.Reset(PoolSizes[Type]);

			TLinkedList<ICsPooledObject*>* Current = Pair.Value;
			TLinkedList<ICsPooledObject*>* Next    = Current;

			while (Next)
			{
				Current = Next;
				Next = Current->GetNextLink();

				Current->Unlink();
			}

			Pair.Value		  = nullptr;
			ActiveTails[Type] = nullptr;
		}
	}

#pragma endregion Allocate / DeAllocate

// Payload
#pragma region
protected:

	TMap<KeyType, TArray<ICsPooledObjectPayload*>> Payloads;
	TMap<KeyType, int32> PayloadSizes;
	TMap<KeyType, int32> PayloadIndices;

public:

	template<typename PayloadType>
	void CreatePayloads(const KeyType& Type, const int32& Size)
	{
		TArray<ICsPooledObjectPayload*>& P = Payloads.Add(Type);
		PayloadSizes.Add(Type, Size);
		PayloadIndices.Add(Type, 0);

		for (int32 I = 0; I < Size; ++I)
		{
			P.Add(new PayloadType());
		}
	}

	ICsPooledObjectPayload* AllocatePayload(const KeyType& Type)
	{
		CheckAndAddType(Type);

		TArray<ICsPooledObjectPayload*>& P = Payloads[Type];
		const int32& PayloadSize		   = PayloadSizes[Type];
		int32& PayloadIndex				   = PayloadIndices[Type];

		for (int32 I = 0; I < PayloadSize; ++I)
		{
			PayloadIndex					= (PayloadIndex + 1) % PayloadSize;
			ICsPooledObjectPayload* Payload = P[PayloadIndex];

			if (!Payload->IsAllocated())
			{
				Payload->Allocate();
				return Payload;
			}
		}
		checkf(0, TEXT("%s::AllocatePayload: Pool: %s is exhausted"), *Name, *KeyTypeToString(Type));
		return nullptr;
	}

#pragma endregion Payload

// Log
#pragma region
protected:

	FECsCVarLog LogType;

	//virtual void LogTransaction(const FString& FunctionName, const ERsPoolTransaction& Transaction, IRsPooledObject* o);

#pragma endregion Log

// Spawn
#pragma region
public:

	virtual ICsPooledObject* Spawn(const KeyType& Type, ICsPooledObjectPayload* Payload)
	{
		CheckAndAddType(Type);

		ICsPooledObject* O = Allocate(Type, Payload);

		//LogTransaction(FunctionNames[(uint8)ERsManagerPooledObjectsFunctionNames::Spawn], ERsPoolTransaction::Allocate, O);
		Payload->Reset();
		AddToActivePool_Internal(Type, O);
		OnSpawn_Event.Broadcast(Type, O);
		return O;
	}

	TMulticastDelegate<void, const KeyType&, ICsPooledObject*> OnSpawn_Event;

#pragma endregion Spawn
};
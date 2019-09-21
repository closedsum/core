// Copyright 2017 Respawn Entertainment, Inc. All rights reserved.

#include "Managers/Pool/CsManager_PooledObjects.h"
#include "CsCore.h"

#include "Managers/Pool/CsPooledObject.h"

FCsManager_PooledObjects::FCsManager_PooledObjects()
{
	Name			= NCsCached::Str::Empty;
	ObjectClassName = NCsCached::Str::Empty;

	CurrentWorld = nullptr;

	OnAddToPool_Event.Clear();
	OnDeallocate_Event.Clear();

	Pool.Reset();
	PoolSize = 0;
	PoolIndex = 0;

	ActiveObjects.Reset();

	Payloads.Reset();
	PayloadSize = 0;
	PayloadIndex = 0;

	OnSpawn_Event.Clear();
}

FCsManager_PooledObjects::~FCsManager_PooledObjects()
{
	Shutdown();
}

void FCsManager_PooledObjects::Init(const FString& InName, UClass* InObjectClass, UWorld* World, const FECsCVarLog& InLogType)
{
	Name			= InName;
	ObjectClass		= InObjectClass;
	ObjectClassName = ObjectClass->GetName();
	CurrentWorld	= World;
	LogType			= InLogType;

	ConstructObject_Call.BindRaw(this, &FCsManager_PooledObjects::ConstructObject);

	FunctionNames[(uint8)ERsManagerPooledObjectsFunctionNames::OnTick]		  = Name + TEXT("::OnTick");
	FunctionNames[(uint8)ERsManagerPooledObjectsFunctionNames::Deallocate]	  = Name + TEXT("::Deallocate");
	FunctionNames[(uint8)ERsManagerPooledObjectsFunctionNames::DeallocateAll] = Name + TEXT("::DeallocateAll");
	FunctionNames[(uint8)ERsManagerPooledObjectsFunctionNames::Spawn]		  = Name + TEXT("::Spawn");
}

void FCsManager_PooledObjects::Clear()
{
	for (ICsPooledObject* O : Pool)
	{
		O->Deallocate();
		DeconstructObject(O);
	}

	Pool.Reset();
	PoolSize = 0;
	ActiveObjects.Reset();

	for (ICsPooledObjectPayload* P : Payloads)
	{
		P->Reset();
	}
	OnAddToPool_Event.Clear();
	OnDeallocate_Event.Clear();
}

void FCsManager_PooledObjects::Shutdown()
{
	Clear();

	for (TLinkedList<ICsPooledObject*>* L : Links)
	{
		delete L;
	}
	Links.Reset();

	for (ICsPooledObjectPayload* P : Payloads)
	{
		delete P;
	}
	Payloads.Reset();

	OnTick_Handle_Object.Unbind();
}

UWorld* FCsManager_PooledObjects::GetCurrentWorld()
{
	return CurrentWorld.IsValid() ? CurrentWorld.Get() : nullptr;
}

float FCsManager_PooledObjects::GetCurrentTimeSeconds()
{
	return GetCurrentWorld() ? GetCurrentWorld()->GetTimeSeconds() : 0.0f;
}

// Object
#pragma region

ICsPooledObject* FCsManager_PooledObjects::ConstructObject()
{
	return nullptr;
}

void FCsManager_PooledObjects::DeconstructObject(ICsPooledObject* Object)
{
}

FString FCsManager_PooledObjects::GetObjectName(ICsPooledObject* Object)
{
	return NCsCached::Str::Empty;
}

#pragma endregion Object

// Pool
#pragma region

void FCsManager_PooledObjects::CreatePool(const int32& Size)
{
	PoolSize = Size;

	Pool.Reserve(PoolSize);
	Links.Reserve(PoolSize);
	ActiveObjects.Reserve(PoolSize);

	for (int32 I = 0; I < Size; ++I)
	{
		ICsPooledObject* O = ConstructObject_Call.Execute();
		O->GetCache()->Init(I);
		O->Deallocate();
		Pool.Add(O);

		// Add Link
		Links.Add(new TLinkedList<ICsPooledObject*>());
		// Set Element for Link
		TLinkedList<ICsPooledObject*>* Link = Links.Last();
		**Link								= O;

		OnAddToPool_Event.Broadcast(O);
	}
}

void FCsManager_PooledObjects::AddToPool(ICsPooledObject* Object)
{
	Pool.Add(Object);
	PoolSize = Pool.Num();
	Object->GetCache()->Init(Pool.Num() - 1);
	Object->Deallocate();

	// Add Link
	Links.Add(new TLinkedList<ICsPooledObject*>());
	// Set Element for Link
	TLinkedList<ICsPooledObject*>* Link = Links.Last();
	**Link								= Object;

	ActiveObjects.Reserve(ActiveObjects.Num() + 1);

	OnAddToPool_Event.Broadcast(Object);
}

void FCsManager_PooledObjects::AddToActivePool(ICsPooledObject* Object)
{
	// TODO: Do check is Object is in Pool
	AddToActivePool_Internal(Object);
}

void FCsManager_PooledObjects::AddToActivePool_Internal(ICsPooledObject* Object)
{
	TLinkedList<ICsPooledObject*>* Link = Links[Object->GetCache()->GetIndex()];

	AddActiveLink(Link);
	ActiveObjects.Add(Object);
}

void FCsManager_PooledObjects::AddActiveLink(TLinkedList<ICsPooledObject*>* Link)
{
	if (ActiveTail)
	{
		Link->LinkAfter(ActiveTail);
		ActiveTail = Link;
	}
	else
	{
		ActiveHead = Link;
		ActiveTail = ActiveHead;
	}
}

void FCsManager_PooledObjects::RemoveActiveLink(TLinkedList<ICsPooledObject*>* Link)
{
	// Check to Update HEAD
	if (Link == ActiveHead)
	{
		if (ActiveObjectsSize > CS_SINGLETON)
		{
			ActiveHead = Link->GetNextLink();
		}
		else
		{
			ActiveHead = nullptr;
			ActiveTail = nullptr;
		}
	}
	Link->Unlink();
}

const TArray<ICsPooledObject*>& FCsManager_PooledObjects::GetAllActiveObjects()
{
	return ActiveObjects;
}

const TArray<ICsPooledObject*>& FCsManager_PooledObjects::GetObjects()
{
	return Pool;
}

int32 FCsManager_PooledObjects::GetActivePoolSize()
{
	return ActiveObjectsSize;
}

bool FCsManager_PooledObjects::IsExhausted()
{
	return ActiveObjectsSize == PoolSize;
}

#pragma endregion Pool

// Tick
#pragma region

void FCsManager_PooledObjects::OnTick(const float &DeltaTime)
{
	TLinkedList<ICsPooledObject*>* Current = ActiveHead;
	TLinkedList<ICsPooledObject*>* Next    = Current;

	int32 NewSize = 0;

	while (Next)
	{
		Current			   = Next;
		ICsPooledObject* O = **Current;
		Next			   = Current->GetNextLink();

		// Check if ObjectType was Deallocated NOT in a normal way (i.e. Out of Bounds)

		if (!O->GetCache()->IsAllocated())
		{
#if !UE_BUILD_SHIPPING
			UE_LOG(LogCs, Warning, TEXT("%s::OnTick: %s: %s at PoolIndex: %d was prematurely deallocated NOT in a normal way."), *Name, *ObjectClassName, *(GetObjectName(O)), O->GetCache()->GetIndex());

			LogTransaction(FunctionNames[(uint8)ERsManagerPooledObjectsFunctionNames::OnTick], ECsPoolTransaction::Deallocate, O);
#endif // #if !UE_BUILD_SHIPPING
			RemoveActiveLink(Current);
			continue;
		}

		if (!O->GetCache()->UseLifeTime())
		{
			OnTick_Handle_Object.ExecuteIfBound(O);
			continue;
		}

		if (GetCurrentTimeSeconds() - O->GetCache()->GetTime() > O->GetCache()->GetLifeTime())
		{
#if !UE_BUILD_SHIPPING
			LogTransaction(FunctionNames[(uint8)ERsManagerPooledObjectsFunctionNames::OnTick], ECsPoolTransaction::Deallocate, O);
#endif // #if !UE_BUILD_SHIPPING
			O->Deallocate();
			RemoveActiveLink(Current);

			OnDeallocate_Event.Broadcast(O);
			continue;
		}

		if (NewSize < ActiveObjectsSize)
		{
			ActiveObjects[NewSize] = O;
		}

		OnTick_Handle_Object.ExecuteIfBound(O);
		++NewSize;
	}

	for (int32 I = ActiveObjectsSize - 1; I >= NewSize; --I)
	{
		ActiveObjects.RemoveAt(I, 1, false);
	}
	ActiveObjectsSize = ActiveObjects.Num();
}

#pragma endregion Tick

// Allocate / DeAllocate
#pragma region

ICsPooledObject* FCsManager_PooledObjects::Allocate(ICsPooledObjectPayload* Payload)
{
	if (IsExhausted())
	{
		checkf(0, TEXT("%s::Allocate: Pool is exhausted"), *Name);
		return nullptr;
	}

	for (int32 I = 0; I < PoolSize; ++I)
	{
		PoolIndex		   = (PoolIndex + 1) % PoolSize;
		ICsPooledObject* O = Pool[PoolIndex];

		if (!O->GetCache()->IsAllocated())
		{
			O->Allocate(Payload);
			return O;
		}
	}
	checkf(0, TEXT("%s::Allocate: Pool is exhausted"), *Name);
	return nullptr;
}

bool FCsManager_PooledObjects::Deallocate(const int32& Index)
{
	if (Index >= PoolSize)
	{
		UE_LOG(LogCs, Warning, TEXT("%s::DeAllocate: %s with PoolIndex: %d is NOT in the Pool. Call AddToPool."), *Name, *ObjectClassName, Index);
		return false;
	}

	if (Links[Index] != ActiveHead && 
		!Links[Index]->IsLinked())
	{
		UE_LOG(LogCs, Warning, TEXT("%s::DeAllocate: %s at PoolIndex: %d is already deallocated or not in the Pool."), *Name, *ObjectClassName, Index);
		return false;
	}

	if (ActiveObjectsSize == CS_EMPTY)
	{
		UE_LOG(LogCs, Warning, TEXT("%s::DeAllocate: %s at PoolIndex: %d is already deallocated or not in the Pool."), *Name, *ObjectClassName, Index);
		return false;
	}

	
	TLinkedList<ICsPooledObject*>* Link = Links[Index];
	ICsPooledObject* O					= **Link;

#if !UE_BUILD_SHIPPING
	LogTransaction(FunctionNames[(uint8)ERsManagerPooledObjectsFunctionNames::Deallocate], ECsPoolTransaction::Deallocate, O);
#endif // #if !UE_BUILD_SHIPPING

	O->Deallocate();
	RemoveActiveLink(Link);

	TLinkedList<ICsPooledObject*>* Current = ActiveHead;
	TLinkedList<ICsPooledObject*>* Next	   = Current;

	int32 NewSize = 0;

	while (Next)
	{
		Current	 = Next;
		O		 = **Current;
		Next	 = Current->GetNextLink();

		if (NewSize < ActiveObjectsSize)
		{
			ActiveObjects[NewSize] = O;
		}

		++NewSize;
	}

	for (int32 I = ActiveObjectsSize - 1; I >= NewSize; --I)
	{
		ActiveObjects.RemoveAt(I, 1, false);
	}
	ActiveObjectsSize = ActiveObjects.Num();

	OnDeallocate_Event.Broadcast(O);
	return true;
}

void FCsManager_PooledObjects::DeallocateAll()
{
	for (ICsPooledObject* O : ActiveObjects)
	{
#if !UE_BUILD_SHIPPING
		LogTransaction(FunctionNames[(uint8)ERsManagerPooledObjectsFunctionNames::DeallocateAll], ECsPoolTransaction::Deallocate, O);
#endif // #if !UE_BUILD_SHIPPING
		O->Deallocate();
		OnDeallocate_Event.Broadcast(O);
	}

	ActiveObjects.Reset(PoolSize);

	TLinkedList<ICsPooledObject*>* Current = ActiveHead;
	TLinkedList<ICsPooledObject*>* Next = Current;


	while (Next)
	{
		Current = Next;
		Next	= Current->GetNextLink();
		
		Current->Unlink();
	}

	ActiveHead = nullptr;
	ActiveTail = nullptr;
}

#pragma endregion Allocate / DeAllocate

// Payload
#pragma region

ICsPooledObjectPayload* FCsManager_PooledObjects::AllocatePayload()
{
	for (int32 I = 0; I < PayloadSize; ++I)
	{
		PayloadIndex					= (PayloadIndex + 1) % PayloadSize;
		ICsPooledObjectPayload* Payload = Payloads[PayloadIndex];

		if (!Payload->IsAllocated())
		{
			Payload->Allocate();
			return Payload;
		}
	}
	checkf(0, TEXT("%s::AllocatePayload: Pool is exhausted"), *Name);
	return nullptr;
}

#pragma endregion Payload

// Log
#pragma region

void FCsManager_PooledObjects::LogTransaction(const FString& FunctionName, const ECsPoolTransaction& Transaction, ICsPooledObject* O)
{
	if (FCsCVarLogMap::Get().IsShowing(LogType))
	{
		const FString& TransactionAsString = NCsPoolTransaction::ToActionString(Transaction);

		const FString ObjectName	= GetObjectName(O);
		const float CurrentTime		= GetCurrentTimeSeconds();
		const UObject* ObjectOwner	= O->GetCache()->GetOwner();
		const FString OwnerName		= ObjectOwner ? ObjectOwner->GetName() : NCsCached::Str::None;
		const UObject* Parent		= O->GetCache()->GetParent();
		const FString ParentName	= Parent ? Parent->GetName() : NCsCached::Str::None;

		if (ObjectOwner && Parent)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s %s: %s of Type: %s at %f for %s attached to %s."), *FunctionName, *TransactionAsString, *ObjectClassName, *ObjectName, CurrentTime, *OwnerName, *ParentName);
		}
		else
		if (ObjectOwner)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s %s: %s of Type: %s at %f for %s."), *FunctionName, *TransactionAsString, *ObjectClassName, *ObjectName, CurrentTime, *OwnerName);
		}
		else
		if (Parent)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s %s: %s of Type: %s at %f attached to %s."), *FunctionName, *TransactionAsString, *ObjectClassName, *ObjectName, CurrentTime, *ParentName);
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s %s: %s of Type: %s at %f."), *FunctionName, *TransactionAsString, *ObjectClassName, *ObjectName, CurrentTime);
		}
	}
}

#pragma endregion Log

// Spawn
#pragma region

ICsPooledObject* FCsManager_PooledObjects::Spawn(ICsPooledObjectPayload* Payload)
{
	ICsPooledObject* O = Allocate(Payload);

	LogTransaction(FunctionNames[(uint8)ERsManagerPooledObjectsFunctionNames::Spawn], ECsPoolTransaction::Allocate, O);
	Payload->Reset();
	AddToActivePool_Internal(O);
	OnSpawn_Event.Broadcast(O);
	return O;
}

#pragma endregion Spawn
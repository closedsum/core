// Copyright 2017 Respawn Entertainment, Inc. All rights reserved.

#include "Managers/Pool/CsManager_PooledObject.h"
#include "CsCore.h"

#include "Managers/Pool/CsPooledObject.h"

FCsManager_PooledObject::FCsManager_PooledObject()
{
	Name			= NCsCached::Str::Empty;

	CurrentWorld = nullptr;

	OnAddToPool_Event.Clear();
	OnDeallocate_Event.Clear();

	Pool.Reset();
	PoolSize = 0;
	PoolIndex = 0;

	ConstructObject_Impl.BindRaw(this, &FCsManager_PooledObject::ConstructObject);

	ActiveObjects.Reset();

	Payloads.Reset();
	PayloadSize = 0;
	PayloadIndex = 0;

	CreatePayloads_Impl.BindRaw(this, &FCsManager_PooledObject::CreatePayloads_Internal);

	OnSpawn_Event.Clear();
}

FCsManager_PooledObject::~FCsManager_PooledObject()
{
	Shutdown();
}

void FCsManager_PooledObject::Init(const FCsManagerPooledObjectParams& Params)
{
	Name		= Params.Name;
	CurrentWorld = Params.World;
	LogType		 = Params.LogType;

	ConstructParams = Params.ConstructParams;

	FunctionNames[(uint8)ECsManagerPooledObjectFunctionNames::OnTick]		  = Name + TEXT("::OnTick");
	FunctionNames[(uint8)ECsManagerPooledObjectFunctionNames::Deallocate]	  = Name + TEXT("::Deallocate");
	FunctionNames[(uint8)ECsManagerPooledObjectFunctionNames::DeallocateAll] = Name + TEXT("::DeallocateAll");
	FunctionNames[(uint8)ECsManagerPooledObjectFunctionNames::Spawn]		  = Name + TEXT("::Spawn");
}

void FCsManager_PooledObject::Clear()
{
	for (FCsPooledObject& O : Pool)
	{
		ICsPooledObject* Interface = O.GetInterface();

		if (O.IsObject())
		{
			if (UObject* Object = O.GetSafeObject())
			{
				if (!Object->IsPendingKill())
				{
					Interface->Deallocate();
					DeconstructObject(O);
				}
			}
		}
		else
		{
			Interface->Deallocate();
			DeconstructObject(O);
		}
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

void FCsManager_PooledObject::Shutdown()
{
	Clear();

	// Links
	{
		const int32 Count = Links.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			TLinkedList<FCsPooledObject>* L = Links[I];
			delete L;
			Links[I] = nullptr;
		}
		Links.Reset();
	}
	// Payloads
	{
		const int32 Count = Payloads.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			ICsPooledObjectPayload* P = Payloads[I];
			delete P;
			Payloads[I] = nullptr;
		}
		Payloads.Reset();
	}

	OnTick_Handle_Object.Unbind();
}

UWorld* FCsManager_PooledObject::GetCurrentWorld()
{
	return CurrentWorld.IsValid() ? CurrentWorld.Get() : nullptr;
}

float FCsManager_PooledObject::GetCurrentTimeSeconds()
{
	return GetCurrentWorld() ? GetCurrentWorld()->GetTimeSeconds() : 0.0f;
}

// Object
#pragma region

FCsPooledObject FCsManager_PooledObject::ConstructObject()
{
	UClass* Class = ConstructParams.Class;

	checkf(Class, TEXT("%s:ConstructObject: No Class set."), *Name);

	// Actor
	if (ConstructParams.ConstructionType == ECsPooledObjectConstruction::Actor)
	{
		AActor* Actor = GetCurrentWorld()->SpawnActor<AActor>(Class, ConstructParams.ConstructionInfo);

		if (!ConstructParams.bReplicates)
		{
			Actor->SetReplicates(false);
			Actor->Role = ROLE_None;
			GetCurrentWorld()->RemoveNetworkActor(Actor);
		}

		checkf(Actor, TEXT("%s:ContructObject: Actor did NOT spawn."), *Name);

		FCsPooledObject Object;

		if (ICsPooledObject* O = Cast<ICsPooledObject>(Actor))
		{
			Object.SetInterface(O);
		}
		else
		if (Class->ImplementsInterface(UCsPooledObject::StaticClass()))
		{
			Object.SetScript();
		}
		else
		{
			checkf(false, TEXT("%s:ContructObject: Actor: %s does NOT implement the interface: ICsPooledObject."), *Name, *(Actor->GetName()));
		}

		Object.SetObject(Actor);

		OnConstructObject_Event.Broadcast(Object);

		return Object;
	}
	checkf(0, TEXT("%s:ConstructObject: Failed to Construct Object with Class: %s."), *Name, *(Class->GetName()));
	return FCsPooledObject();
}

void FCsManager_PooledObject::DeconstructObject(const FCsPooledObject& Object)
{
}

FString FCsManager_PooledObject::GetObjectName(const FCsPooledObject& Object)
{
	if (Object.IsObject())
		return Object.GetObject()->GetName();
	return NCsCached::Str::Empty;
}

#pragma endregion Object

// Pool
#pragma region

void FCsManager_PooledObject::CreatePool(const int32& Size)
{
	PoolSize = Size;

	Pool.Reserve(PoolSize);
	Links.Reserve(PoolSize);
	ActiveObjects.Reserve(PoolSize);

	for (int32 I = 0; I < Size; ++I)
	{
		FCsPooledObject O = ConstructObject_Impl.Execute();

#if WITH_EDITOR
		if (O.IsScript())
		{
			checkf(O.Script_GetCache_Impl.IsBound(), TEXT("%s:CreatePool: Failed to Construct Object with Class: %s. Script_GetCache_Impl is NOT bound for Object implementing script interface."));

			checkf(O.Script_Allocate_Impl.IsBound(), TEXT("%s:CreatePool: Failed to Construct Object with Class: %s. Script_Allocate_Impl is NOT bound for Object implementing script interface."));

			checkf(O.Script_Deallocate_Impl.IsBound(), TEXT("%s:CreatePool: Failed to Construct Object with Class: %s. Script_Deallocate_Impl is NOT bound for Object implementing script interface."));
		}
#endif // #if WTIH_EDITOR

		ICsPooledObject* Interface = O.GetInterface();

		checkf(Interface, TEXT("%s:CreatePool: Failed to Construct Object with Class: %s."), *Name, *(ConstructParams.ClassName));

		O.GetCache()->Init(I);
		O.Deallocate();

		Pool.Add(O);

		// Add Link
		Links.Add(new TLinkedList<FCsPooledObject>());
		// Set Element for Link
		TLinkedList<FCsPooledObject>* Link = Links.Last();
		(**Link)						   = O;

		OnAddToPool_Event.Broadcast(O);
	}
}

void FCsManager_PooledObject::AddToPool(ICsPooledObject* PooledObject, UObject* Object)
{
	const int32& Index = PooledObject->GetCache()->GetIndex();

	if (Index < INDEX_NONE)
	{
		return;
	}

	if (Index >= PoolSize)
	{
		return;
	}

	PooledObject->GetCache()->Init(PoolSize);
	PooledObject->Deallocate();
	Pool.AddDefaulted();
	FCsPooledObject& O = Pool.Last();
	O.SetInterface(PooledObject);
	O.SetObject(Object);

	// Add Link
	Links.Add(new TLinkedList<FCsPooledObject>());
	// Set Element for Link
	TLinkedList<FCsPooledObject>* Link = Links.Last();
	(**Link) = O;

	++PoolSize;

	OnAddToPool_Event.Broadcast(O);
}

void FCsManager_PooledObject::AddToPool(ICsPooledObject* Object)
{
	AddToPool(Object, nullptr);
}

FCsManagerPooledObject_OnAddToPool& FCsManager_PooledObject::GetOnAddToPool_Event()
{
	return OnAddToPool_Event;
}

void FCsManager_PooledObject::AddToActivePool(ICsPooledObject* PooledObject, UObject* Object)
{
	// TODO: Do check is Object is in Pool
	//AddToActivePool_Internal(Object);
}

void FCsManager_PooledObject::AddToActivePool(ICsPooledObject* Object)
{

}

void FCsManager_PooledObject::AddToActivePool_Internal(const FCsPooledObject& Object)
{
	const int32& Index = Object.GetCache()->GetIndex();

	TLinkedList<FCsPooledObject>* Link = Links[Index];

	AddActiveLink(Link);
	ActiveObjects.Add(Object);
}

void FCsManager_PooledObject::AddActiveLink(TLinkedList<FCsPooledObject>* Link)
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

void FCsManager_PooledObject::RemoveActiveLink(TLinkedList<FCsPooledObject>* Link)
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

const TArray<FCsPooledObject>& FCsManager_PooledObject::GetObjects()
{
	return Pool;
}

const TArray<FCsPooledObject>& FCsManager_PooledObject::GetAllActiveObjects()
{
	return ActiveObjects;
}

const int32& FCsManager_PooledObject::GetPoolSize()
{
	return PoolSize;
}

int32 FCsManager_PooledObject::GetActivePoolSize()
{
	return ActiveObjectsSize;
}

bool FCsManager_PooledObject::IsExhausted()
{
	return ActiveObjectsSize == PoolSize;
}

const FCsPooledObject& FCsManager_PooledObject::FindObject(const int32& Index)
{
	if (Index >= PoolSize)
	{
		//Log
		return FCsPooledObject::Empty;
	}
	return Pool[Index];
}

const FCsPooledObject& FCsManager_PooledObject::FindObject(ICsPooledObject* Object)
{
	const FCsPooledObject& O = FindObject(Object->GetCache()->GetIndex());

	if (Object == O.GetInterface())
		return O;
	return FCsPooledObject::Empty;
}

#pragma endregion Pool

// Tick
#pragma region

void FCsManager_PooledObject::OnTick(const float &DeltaTime)
{
	TLinkedList<FCsPooledObject>* Current = ActiveHead;
	TLinkedList<FCsPooledObject>* Next    = Current;

	int32 NewSize = 0;

	while (Next)
	{
		Current			   = Next;
		FCsPooledObject& O = **Current;
		Next			   = Current->GetNextLink();

		// Check if ObjectType was Deallocated NOT in a normal way (i.e. Out of Bounds)

		if (!O.GetCache()->IsAllocated())
		{
#if !UE_BUILD_SHIPPING
			UE_LOG(LogCs, Warning, TEXT("%s::OnTick: %s: %s at PoolIndex: %d was prematurely deallocated NOT in a normal way."), *Name, *(ConstructParams.ClassName), *(GetObjectName(O)), O.GetCache()->GetIndex());

			LogTransaction(FunctionNames[(uint8)ECsManagerPooledObjectFunctionNames::OnTick], ECsPoolTransaction::Deallocate, O);
#endif // #if !UE_BUILD_SHIPPING
			RemoveActiveLink(Current);
			continue;
		}

		if (!O.GetCache()->UseLifeTime())
		{
			OnTick_Handle_Object.ExecuteIfBound(O);
			continue;
		}

		if (GetCurrentTimeSeconds() - O.GetCache()->GetTime() > O.GetCache()->GetLifeTime())
		{
#if !UE_BUILD_SHIPPING
			LogTransaction(FunctionNames[(uint8)ECsManagerPooledObjectFunctionNames::OnTick], ECsPoolTransaction::Deallocate, O);
#endif // #if !UE_BUILD_SHIPPING
			O.Deallocate();
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

const FCsPooledObject& FCsManager_PooledObject::Allocate(ICsPooledObjectPayload* Payload)
{
	if (IsExhausted())
	{
		checkf(0, TEXT("%s::Allocate: Pool is exhausted"), *Name);
		return FCsPooledObject::Empty;
	}

	for (int32 I = 0; I < PoolSize; ++I)
	{
		PoolIndex		   = (PoolIndex + 1) % PoolSize;
		FCsPooledObject& O = Pool[PoolIndex];
		
		if (!O.GetCache()->IsAllocated())
		{
			O.Allocate(Payload);
			return O;
		}
	}
	checkf(0, TEXT("%s::Allocate: Pool is exhausted"), *Name);
	return FCsPooledObject::Empty;
}

bool FCsManager_PooledObject::Deallocate(const int32& Index)
{
	if (Index >= PoolSize)
	{
		UE_LOG(LogCs, Warning, TEXT("%s::DeAllocate: %s with PoolIndex: %d is NOT in the Pool. Call AddToPool."), *Name, *(ConstructParams.ClassName), Index);
		return false;
	}

	if (Links[Index] != ActiveHead && 
		!Links[Index]->IsLinked())
	{
		UE_LOG(LogCs, Warning, TEXT("%s::DeAllocate: %s at PoolIndex: %d is already deallocated or not in the Pool."), *Name, *(ConstructParams.ClassName), Index);
		return false;
	}

	if (ActiveObjectsSize == CS_EMPTY)
	{
		UE_LOG(LogCs, Warning, TEXT("%s::DeAllocate: %s at PoolIndex: %d is already deallocated or not in the Pool."), *Name, *(ConstructParams.ClassName), Index);
		return false;
	}

	TLinkedList<FCsPooledObject>* Link = Links[Index];
	FCsPooledObject& O				   = **Link;

#if !UE_BUILD_SHIPPING
	LogTransaction(FunctionNames[(uint8)ECsManagerPooledObjectFunctionNames::Deallocate], ECsPoolTransaction::Deallocate, O);
#endif // #if !UE_BUILD_SHIPPING

	O.Deallocate();
	RemoveActiveLink(Link);

	TLinkedList<FCsPooledObject>* Current = ActiveHead;
	TLinkedList<FCsPooledObject>* Next	   = Current;

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

void FCsManager_PooledObject::DeallocateAll()
{
	for (FCsPooledObject& O : ActiveObjects)
	{
#if !UE_BUILD_SHIPPING
		LogTransaction(FunctionNames[(uint8)ECsManagerPooledObjectFunctionNames::DeallocateAll], ECsPoolTransaction::Deallocate, O);
#endif // #if !UE_BUILD_SHIPPING
		O.Deallocate();
		OnDeallocate_Event.Broadcast(O);
	}

	ActiveObjects.Reset(PoolSize);

	TLinkedList<FCsPooledObject>* Current = ActiveHead;
	TLinkedList<FCsPooledObject>* Next	  = Current;


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

void FCsManager_PooledObject::CreatePayloads(const int32& Size)
{
	CreatePayloads_Impl.Execute(Size);
}

void FCsManager_PooledObject::CreatePayloads_Internal(const int32& Size)
{
	PayloadSize = Size;

	Payloads.Reserve(PayloadSize);

	for (int32 I = 0; I < Size; ++I)
	{
		Payloads.Add(new FCsPooledObjectPayload());
	}
}

FCsManagerPooledObject_CreatePayloads& FCsManager_PooledObject::GetCreatePayloads_Impl()
{
	return CreatePayloads_Impl;
}

void FCsManager_PooledObject::DestroyPayloads()
{
	for (int32 I = 0; I < PayloadSize; ++I)
	{
		ICsPooledObjectPayload* P = Payloads[I];
		delete P;
		Payloads[I] = nullptr;
	}
	Payloads.Reset(PayloadSize);
	PayloadSize = 0;
}

ICsPooledObjectPayload* FCsManager_PooledObject::AllocatePayload()
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

void FCsManager_PooledObject::LogTransaction(const FString& FunctionName, const ECsPoolTransaction& Transaction, const FCsPooledObject& Object)
{
	if (FCsCVarLogMap::Get().IsShowing(LogType))
	{
		const FString& TransactionAsString = NCsPoolTransaction::ToActionString(Transaction);

		ICsPooledObject* Interface  = Object.GetInterface();
		const FString ObjectName	= GetObjectName(Object);
		const float CurrentTime		= GetCurrentTimeSeconds();
		const UObject* ObjectOwner	= Interface->GetCache()->GetOwner();
		const FString OwnerName		= ObjectOwner ? ObjectOwner->GetName() : NCsCached::Str::None;
		const UObject* Parent		= Interface->GetCache()->GetParent();
		const FString ParentName	= Parent ? Parent->GetName() : NCsCached::Str::None;

		if (ObjectOwner && Parent)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s %s: %s of Type: %s at %f for %s attached to %s."), *FunctionName, *TransactionAsString, *(ConstructParams.ClassName), *ObjectName, CurrentTime, *OwnerName, *ParentName);
		}
		else
		if (ObjectOwner)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s %s: %s of Type: %s at %f for %s."), *FunctionName, *TransactionAsString, *(ConstructParams.ClassName), *ObjectName, CurrentTime, *OwnerName);
		}
		else
		if (Parent)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s %s: %s of Type: %s at %f attached to %s."), *FunctionName, *TransactionAsString, *(ConstructParams.ClassName), *ObjectName, CurrentTime, *ParentName);
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s %s: %s of Type: %s at %f."), *FunctionName, *TransactionAsString, *(ConstructParams.ClassName), *ObjectName, CurrentTime);
		}
	}
}

#pragma endregion Log

// Spawn
#pragma region

const FCsPooledObject& FCsManager_PooledObject::Spawn(ICsPooledObjectPayload* Payload)
{
	const FCsPooledObject& O = Allocate(Payload);

	LogTransaction(FunctionNames[(uint8)ECsManagerPooledObjectFunctionNames::Spawn], ECsPoolTransaction::Allocate, O);
	Payload->Reset();
	AddToActivePool_Internal(O);
	OnSpawn_Event.Broadcast(O);
	return O;
}

#pragma endregion Spawn

// Destroy
#pragma region

bool FCsManager_PooledObject::Destroy(const int32& Index)
{
	return Deallocate(Index);
}

bool FCsManager_PooledObject::Destroy(ICsPooledObject* Object)
{
	return Destroy(Object->GetCache()->GetIndex());
}

#pragma endregion Destroy
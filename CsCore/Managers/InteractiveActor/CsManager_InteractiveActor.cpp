// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/InteractiveActor/CsManager_InteractiveActor.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Common/CsCommon.h"
#include "Managers/InteractiveActor/CsInteractiveActor.h"
#include "Game/CsGameState.h"

// Data
#include "Data/CsData_Interactive.h"

namespace ECsManagerInteractiveActorCachedString
{
	namespace Str
	{
		const FString OnTick = TEXT("ACsManager_InteractiveActor::OnTick");
		const FString DeAllocate = TEXT("ACsManager_InteractiveActor::DeAllocate");
		const FString DeAllocateAll = TEXT("ACsManager_InteractiveActor::DeAllocateAll");
		const FString WakeUp = TEXT("ACsManager_InteractiveActor::WakeUp");
	}
}

ACsManager_InteractiveActor::ACsManager_InteractiveActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	InteractiveTypeToString = nullptr;

	PoolSize = 1;
}

/*static*/ ACsManager_InteractiveActor* ACsManager_InteractiveActor::Get(UWorld* InWorld)
{
	return InWorld->GetGameState<ACsGameState>()->Manager_InteractiveActor;
}

void ACsManager_InteractiveActor::Clear()
{
	Super::Clear();

	Pool.Reset();
	Pools.Reset();
	PoolSizes.Reset();
	PoolIndices.Reset();
	ActiveActors.Reset();
}

void ACsManager_InteractiveActor::Shutdown()
{
	Super::Shutdown();

	const int32 Count = Pool.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		if (Pool[I] && !Pool[I]->IsPendingKill())
			Pool[I]->Destroy(true);
	}
	Clear();
}

void ACsManager_InteractiveActor::Destroyed()
{
	const int32 Count = Pool.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		if (Pool[I] && !Pool[I]->IsPendingKill())
			Pool[I]->Destroy(true);
	}
	Clear();

	Super::Destroyed();
}

void ACsManager_InteractiveActor::Init(const TCsInteractiveType &InInteractiveType_MAX, TCsInteractiveTypeToString InInteractiveTypeToString)
{
	InteractiveType_MAX     = InInteractiveType_MAX;
	INTERACTIVE_TYPE_MAX	= (uint8)InInteractiveType_MAX;
	InteractiveTypeToString = InInteractiveTypeToString;
}

void ACsManager_InteractiveActor::CreatePool(const TSubclassOf<class UObject> &ObjectClass, const uint8 &Type, const int32 &Size)
{
	const TCsInteractiveType ClassType = (TCsInteractiveType)Type;

	PoolSizes.Add(ClassType, Size);

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnInfo.ObjectFlags |= RF_Transient;

	PoolIndices.Add(ClassType, 0);

	TArray<ACsInteractiveActor*> ActorPool;

	for (int32 I = 0; I < Size; ++I)
	{
		ACsInteractiveActor* Actor = GetWorld()->SpawnActor<ACsInteractiveActor>(ObjectClass, SpawnInfo);
		Actor->SetReplicates(false);
		Actor->Role = ROLE_None;
		GetWorld()->RemoveNetworkActor(Actor);
		Actor->Init(I, ClassType);
		Actor->DeAllocate();
		Actor->OnCreatePool();
		Pool.Add(Actor);
		ActorPool.Add(Actor);
	}
	Pools.Add(ClassType, ActorPool);
}

void ACsManager_InteractiveActor::AddToPool(UObject* InObject, const uint8& Type)
{
	checkf(InObject, TEXT("ACsManager_InteractiveActor::AddToPool: InObject is NULL."));

	ACsInteractiveActor* Actor = Cast<ACsInteractiveActor>(InObject);

	checkf(Actor, TEXT("ACsManager_InteractiveActor::AddToPool: InObject (%s) is NOT type ACsInteraciveActor."), *InObject->GetClass()->GetName());

	const TCsInteractiveType ClassType = (TCsInteractiveType)Type;

	uint16* Size = PoolSizes.Find(ClassType);

	if (Size)
		(*Size)++;
	else
		PoolSizes.Add(ClassType, 1);

	uint16* Index = PoolIndices.Find(ClassType);

	if (!Index)
		PoolIndices.Add(ClassType, 0);

	Pool.Add(Actor);

	TArray<ACsInteractiveActor*>* PoolPtr = Pools.Find(ClassType);

	if (PoolPtr)
	{
		PoolPtr->Add(Actor);
	}
	else
	{
		TArray<ACsInteractiveActor*> ActorPool;
		ActorPool.Add(Actor);
		Pools.Add(ClassType, ActorPool);

		PoolPtr = Pools.Find(ClassType);
	}

	Actor->Init(PoolPtr->Num() - 1, ClassType);
	// TODO: Data needs to be set somewhere
	Actor->Cache.Init(0, nullptr, GetWorld()->GetTimeSeconds(), GetWorld()->GetRealTimeSeconds(), UCsCommon::GetCurrentFrame(GetWorld()));
}

void ACsManager_InteractiveActor::AddToActivePool(UObject* InObject, const uint8& Type)
{
	checkf(InObject, TEXT("ACsManager_InteractiveActor::AddToActivePool: InObject is NULL."));

	ACsInteractiveActor* Actor = Cast<ACsInteractiveActor>(InObject);

	checkf(Actor, TEXT("ACsManager_InteractiveActor::AddToActivePool: InObject (%s) is NOT type ACsInteraciveActor."), *InObject->GetClass()->GetName());

	const TCsInteractiveType ClassType = (TCsInteractiveType)Type;

	Actor->Cache.IsAllocated = true;

	if (TArray<ACsInteractiveActor*>* ActorsPtr = ActiveActors.Find(ClassType))
	{
		ActorsPtr->Add(Actor);
	}
	else
	{
		TArray<ACsInteractiveActor*> Actors;
		Actors.Add(Actor);
		ActiveActors.Add(ClassType, Actors);
	}
	Actor->Cache.OnDeAllocate_Event.AddUObject(this, &ACsManager_InteractiveActor::OnDeAllocate);
}

void ACsManager_InteractiveActor::OnTick(const float &DeltaSeconds)
{
	const int32 PoolCount = ActiveActors.Num();

	for (int32 I = PoolCount - 1; I >= 0; --I)
	{
		const TCsInteractiveType Type			= (TCsInteractiveType)I;
		TArray<ACsInteractiveActor*>* ActorsPtr = ActiveActors.Find(Type);

		const int32 ActorCount = ActorsPtr->Num();
		int32 EarliestIndex    = ActorCount;

		for (int32 J = ActorCount - 1; J >= 0; --J)
		{
			ACsInteractiveActor* Actor = (*ActorsPtr)[J];

			// Check if InteractiveActor was DeAllocated NOT in a normal way (i.e. Out of Bounds)

			if (!Actor->Cache.IsAllocated)
			{
				UE_LOG(LogCs, Warning, TEXT("ACsManager_InteractiveActor::OnTick: InteractiveActor: %s at PoolIndex: %s was prematurely deallocted NOT in a normal way."), *(Actor->GetName()), Actor->Cache.Index);

				LogTransaction(ECsManagerInteractiveActorCachedString::Str::OnTick, ECsPoolTransaction::Deallocate, Actor);

				ActorsPtr->RemoveAt(J);

				if (J < EarliestIndex)
					EarliestIndex = J;
				continue;
			}

			if (!Actor->Cache.UseLifeTime)
				continue;

			if (GetWorld()->GetTimeSeconds() - Actor->Cache.Time > Actor->Cache.LifeTime)
			{
				LogTransaction(ECsManagerInteractiveActorCachedString::Str::OnTick, ECsPoolTransaction::Deallocate, Actor);

				Actor->DeAllocate();
				ActorsPtr->RemoveAt(J);

				if (J < EarliestIndex)
					EarliestIndex = J;
			}
		}

		// Update ActiveIndex
		if (EarliestIndex != ActorCount)
		{
			const uint16 Max = ActorsPtr->Num();

			for (uint16 J = EarliestIndex; J < Max; J++)
			{
				ACsInteractiveActor* Actor = (*ActorsPtr)[J];
				Actor->Cache.SetActiveIndex(J);
			}
		}
	}
}

void ACsManager_InteractiveActor::GetAllActiveActors(TArray<class ACsInteractiveActor*> &OutActors)
{
	for (int32 I = 0; I < InteractiveType_MAX; ++I)
	{
		TArray<ACsInteractiveActor*>* Actors = ActiveActors.Find((TCsInteractiveType)I);

		if (!Actors)
			continue;

		const int32 Count = Actors->Num();

		for (int32 J = 0; J < Count; J++)
		{
			OutActors.Add((*Actors)[J]);
		}
	}
}

int32 ACsManager_InteractiveActor::GetActivePoolSize(const uint8& Type)
{
	TArray<ACsInteractiveActor*>* ActorsPtr = ActiveActors.Find((TCsInteractiveType)Type);

	if (!ActorsPtr)
		return CS_EMPTY;
	return ActorsPtr->Num();
}

bool ACsManager_InteractiveActor::IsExhausted(const uint8 &Type)
{
	const TCsInteractiveType ClassType = (TCsInteractiveType)Type;

	TArray<ACsInteractiveActor*>* PoolPtr = Pools.Find(ClassType);

	if (!PoolPtr)
		return true;

	return GetActivePoolSize(Type) >= PoolPtr->Num();
}

void ACsManager_InteractiveActor::LogTransaction(const FString &FunctionName, const TEnumAsByte<ECsPoolTransaction::Type> &Transaction, UObject* InObject)
{
	if (CsCVarLogManagerInteractiveActorTransactions->GetInt() == CS_CVAR_SHOW_LOG)
	{
		ACsInteractiveActor* Actor = Cast<ACsInteractiveActor>(InObject);

		const FString TransactionAsString = ECsPoolTransaction::ToActionString(Transaction);

		const FString ActorName	   = Actor->GetName();
		const FString TypeAsString = (*InteractiveTypeToString)((TCsInteractiveType)Actor->Cache.Type);
		const float CurrentTime	   = GetWorld()->GetTimeSeconds();
		const UObject* ActorOwner  = Actor->Cache.GetOwner();
		const FString OwnerName	   = ActorOwner ? ActorOwner->GetName() : ECsCachedString::Str::None;
		const UObject* Parent	   = Actor->Cache.GetParent();
		const FString ParentName   = Parent ? Parent->GetName() : ECsCachedString::Str::None;

		if (ActorOwner && Parent)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s InteractiveActor: %s of Type: %s at %f for %s attached to %s."), *FunctionName, *TransactionAsString, *ActorName, *TypeAsString, CurrentTime, *OwnerName, *ParentName);
		}
		else
		if (ActorOwner)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s Emitter: %s of Type: %s at %f for %s."), *FunctionName, *TransactionAsString, *ActorName, *TypeAsString, CurrentTime, *OwnerName);
		}
		else
		if (Parent)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s Emitter: %s of Type: %s at %f attached to %s."), *TransactionAsString, *FunctionName, *ActorName, *TypeAsString, CurrentTime, *ParentName);
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s Emitter: %s of Type: %s at %f."), *FunctionName, *TransactionAsString, *ActorName, *TypeAsString, CurrentTime);
		}
	}
}

ACsInteractiveActor* ACsManager_InteractiveActor::Allocate(const TCsInteractiveType &Type)
{
	TArray<ACsInteractiveActor*>* ActorPool = Pools.Find(Type);
	const uint16 Size						= *(PoolSizes.Find(Type));

	if (Size == CS_EMPTY)
	{
		checkf(0, TEXT("ACsManager_InteractiveActor::Allocate: Pool: %s is exhausted"), *(*InteractiveTypeToString(Type)));
		return nullptr;
	}

	for (uint16 I = 0; I < Size; ++I)
	{
		uint16* PoolIndexPtr	   = (PoolIndices.Find(Type));
		*PoolIndexPtr			   = (*PoolIndexPtr + I) % Size;
		ACsInteractiveActor* Actor = (*ActorPool)[*PoolIndexPtr];

		if (!Actor->Cache.IsAllocated)
		{
			Actor->Cache.IsAllocated = true;
			return Actor;
		}
	}
	checkf(0, TEXT("ACsManager_InteractiveActor::Allocate: Pool: %s is exhausted"), *(*InteractiveTypeToString(Type)));
	return nullptr;
}

void ACsManager_InteractiveActor::DeAllocate(const uint8 &Type, const int32 &Index)
{
	const TCsInteractiveType ClassType = (TCsInteractiveType)Type;

	TArray<ACsInteractiveActor*>* Actors = ActiveActors.Find(ClassType);

	if (!Actors)
	{
		UE_LOG(LogCs, Warning, TEXT("ACsManager_InteractiveActor::DeAllocate: InteractiveActor of Type: %s at PoolIndex: %d is already deallocated."), *((*InteractiveTypeToString)(ClassType)), Index);
		return;
	}

	const uint8 Count = Actors->Num();

	for (int32 I = Count - 1; I >= 0; --I)
	{
		ACsInteractiveActor* Actor = (*Actors)[I];

		// Update ActiveIndex
		if (I > CS_FIRST)
		{
			Actor->Cache.DecrementActiveIndex();
		}

		if (Actor->Cache.Index == Index)
		{
			LogTransaction(ECsManagerInteractiveActorCachedString::Str::DeAllocate, ECsPoolTransaction::Deallocate, Actor);

			Actor->DeAllocate();
			Actors->RemoveAt(I);

#if WITH_EDITOR
			OnDeAllocateEX_ScriptEvent.Broadcast(Index, I, Actor->Cache.Type);
#endif // #if WITH_EDITOR
			OnDeAllocateEX_Internal_Event.Broadcast(Index, I, (TCsInteractiveType)Actor->Cache.Type);
			return;
		}
	}

	// Correct on Cache "Miss"
	for (int32 I = 1; I < Count; ++I)
	{
		ACsInteractiveActor* Actor = (*Actors)[I];
		// Reset ActiveIndex
		Actor->Cache.SetActiveIndex(I);
	}
	UE_LOG(LogCs, Warning, TEXT("ACsManager_InteractiveActor::DeAllocate: InteractiveActor of Type: %s at PoolIndex: %d is already deallocated."), *((*InteractiveTypeToString)(ClassType)), Index);
}

void ACsManager_InteractiveActor::DeAllocateAll()
{
	const uint8 Count = (uint8)InteractiveType_MAX;

	for (uint8 I = 0; I < Count; ++I)
	{
		const TCsInteractiveType Type = (TCsInteractiveType)I;

		TArray<ACsInteractiveActor*>* Actors = ActiveActors.Find(Type);

		if (!Actors)
			continue;

		const int32 ActorCount = Actors->Num();

		for (int32 J = ActorCount - 1; J >= 0; --J)
		{
			LogTransaction(ECsManagerInteractiveActorCachedString::Str::DeAllocateAll, ECsPoolTransaction::Deallocate, (*Actors)[J]);

			(*Actors)[J]->DeAllocate();
			Actors->RemoveAt(J);
		}
	}
}

void ACsManager_InteractiveActor::OnDeAllocate(const uint16& Index, const uint16& ActiveIndex, const uint8 &Type)
{
#if WITH_EDITOR
	OnDeAllocateEX_ScriptEvent.Broadcast((int32)Index, (int32)ActiveIndex, Type);
#endif // #if WITH_EDITOR
	OnDeAllocateEX_Internal_Event.Broadcast(Index, ActiveIndex, (TCsInteractiveType)Type);
}

ACsInteractiveActor* ACsManager_InteractiveActor::WakeUp(const TCsInteractiveType &Type, ACsData_Interactive* InData, void* Payload, UObject* InOwner, UObject* Parent)
{
	ACsInteractiveActor* Actor = Allocate(Type);

	Actor->Allocate(GetActivePoolSize((uint8)Type), InData, Payload, InOwner, Parent);

	LogTransaction(ECsManagerInteractiveActorCachedString::Str::WakeUp, ECsPoolTransaction::Allocate, Actor);

	AddToActivePool(Actor, (uint8)Type);
	return Actor;
}

ACsInteractiveActor* ACsManager_InteractiveActor::WakeUp(const TCsInteractiveType &Type, ACsData_Interactive* InData, void* Payload, UObject* InOwner)
{
	return WakeUp(Type, InData, Payload, InOwner, nullptr);
}

ACsInteractiveActor* ACsManager_InteractiveActor::WakeUp(const TCsInteractiveType &Type, ACsData_Interactive* InData, void* Payload)
{
	return WakeUp(Type, InData, Payload, nullptr, nullptr);
}

ACsInteractiveActor* ACsManager_InteractiveActor::WakeUp(const TCsInteractiveType &Type, ACsData_Interactive* InData)
{
	return WakeUp(Type, InData, nullptr, nullptr, nullptr);
}

template<typename T>
void ACsManager_InteractiveActor::WakeUp(const TCsInteractiveType &Type, ACsInteractiveActor* &OutActor, ACsData_Interactive* InData, void* Payload, UObject* InOwner, UObject* Parent, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&))
{
	OutActor = Allocate(Type);

	OutActor->Allocate<T>(GetActivePoolSize((uint8)Type), InData, Payload, InOwner, Parent, InObject, OnDeAllocate);

	LogTransaction(ECsManagerInteractiveActorCachedString::Str::WakeUp, ECsPoolTransaction::Allocate, Actor);

	AddToActivePool(Actor, (uint8)Type);
}

template<typename T>
void ACsManager_InteractiveActor::WakeUp(const TCsInteractiveType &Type, ACsInteractiveActor* &OutActor, ACsData_Interactive* InData, void* Payload, UObject* InOwner, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&))
{
	WakeUp<T>(Type, OutActor, InData, Payload, nullptr, InOwner, InObject, OnDeAllocate);
}

template<typename T>
void ACsManager_InteractiveActor::WakeUp(const TCsInteractiveType &ClassType, ACsInteractiveActor* &OutActor, ACsData_Interactive* InData, void* Payload, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&))
{
	WakeUp<T>(Type, OutActor, InData, Payload, nullptr, nullptr, InObject, OnDeAllocate);
}
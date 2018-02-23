// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/AI/CsManager_AI.h"
#include "CsCore.h"
#include "AI/CsAIPawn.h"
#include "Game/CsGameState.h"

ACsManager_AI::ACsManager_AI(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	AITypeToString = nullptr;

	PoolSize = 1;
}

void ACsManager_AI::Shutdown()
{
	Super::Shutdown();

	const int32 Count = Pool.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		if (Pool[I] && !Pool[I]->IsPendingKill())
			Pool[I]->Destroy(true);
	}
	Pool.Reset();
	Pools.Reset();
	PoolSizes.Reset();
	PoolIndices.Reset();
	ActiveAIPawns.Reset();
}

void ACsManager_AI::Destroyed()
{
	const int32 Count = Pool.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		if (Pool[I] && !Pool[I]->IsPendingKill())
			Pool[I]->Destroy(true);
	}
	Pool.Reset();
	Pools.Reset();
	PoolSizes.Reset();
	PoolIndices.Reset();
	ActiveAIPawns.Reset();

	Super::Destroyed();
}

/*static*/ ACsManager_AI* ACsManager_AI::Get(UWorld* InWorld)
{
	return InWorld->GetGameState<ACsGameState>()->Manager_AI;
}

void ACsManager_AI::Init(const TCsAIType &InAIType_MAX, TCsAITypeToString InAITypeToString)
{
	AIType_MAX     = InAIType_MAX;
	AITypeToString = InAITypeToString;
}

void ACsManager_AI::CreatePool(const TSubclassOf<class UObject> &ObjectClass, const uint8 &Type, const int32 &Size)
{
	const TCsAIType ClassType = (TCsAIType)Type;

	PoolSizes.Add(ClassType, Size);

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnInfo.ObjectFlags |= RF_Transient;

	PoolIndices.Add(ClassType, 0);

	TArray<ACsAIPawn*> PawnPool;

	for (int32 I = 0; I < Size; ++I)
	{
		ACsAIPawn* Pawn = GetWorld()->SpawnActor<ACsAIPawn>(ObjectClass, SpawnInfo);
		Pawn->Init(I, ClassType);
		Pawn->OnCreatePool();
		Pool.Add(Pawn);
		PawnPool.Add(Pawn);
	}
	Pools.Add(ClassType, PawnPool);
}

void ACsManager_AI::AddToPool(UObject* InObject, const uint8& Type)
{
	checkf(InObject, TEXT("ACsManager_AI::AddToPool: InObject is NULL."));

	ACsAIPawn* Actor = Cast<ACsAIPawn>(InObject);

	checkf(Actor, TEXT("ACsManager_AI::AddToPool: InObject (%s) is NOT type ACsAIPawn."), *InObject->GetClass()->GetName());

	const TCsAIType ClassType = (TCsAIType)Type;

	uint8* Size = PoolSizes.Find(ClassType);

	if (Size)
		(*Size)++;
	else
		PoolSizes.Add(ClassType, 1);

	uint8* Index = PoolIndices.Find(ClassType);

	if (!Index)
		PoolIndices.Add(ClassType, 0);

	Pool.Add(Actor);

	TArray<ACsAIPawn*>* ActorPoolPtr = Pools.Find(ClassType);

	if (ActorPoolPtr)
	{
		ActorPoolPtr->Add(Actor);
	}
	else
	{
		TArray<ACsAIPawn*> ActorPool;
		ActorPool.Add(Actor);
		Pools.Add(ClassType, ActorPool);

		ActorPoolPtr = Pools.Find(ClassType);
	}
	Actor->Init(ActorPoolPtr->Num() - 1, ClassType);
}

void ACsManager_AI::AddToActivePool(UObject* InObject, const uint8& Type)
{
	checkf(InObject, TEXT("ACsManager_AI::AddToActivePool: InObject is NULL."));

	ACsAIPawn* Actor = Cast<ACsAIPawn>(InObject);

	checkf(Actor, TEXT("ACsManager_AI::AddToActivePool: InObject (%s) is NOT type ACsAIPawn."), *InObject->GetClass()->GetName());

	const TCsAIType ClassType = (TCsAIType)Type;

	TArray<ACsAIPawn*>* ActorPoolPtr = ActiveAIPawns.Find(ClassType);

	Actor->Cache.IsAllocated = true;

	if (ActorPoolPtr)
	{
		ActorPoolPtr->Add(Actor);
	}
	else
	{
		TArray<ACsAIPawn*> ActorPool;
		ActorPool.Add(Actor);
		ActiveAIPawns.Add(ClassType, ActorPool);
	}
}

void ACsManager_AI::OnTick(const float &DeltaSeconds)
{
	/*
	const uint8 Count = ActiveWidgetActors.Num();

	for (int32 I = Count - 1; I >= 0; --I)
	{
	ACsWidgetActor* Widget = ActiveWidgetActors[I];

	if (GetWorld()->TimeSeconds - Sound->Cache.Time > Sound->Cache.Duration)
	{
	Widget->DeAllocate();
	ActiveWidgetActors.RemoveAt(I);
	}
	}
	*/
}

int32 ACsManager_AI::GetActivePoolSize(const uint8 &Type)
{
	TArray<ACsAIPawn*>* PawnsPtr = ActiveAIPawns.Find((TCsAIType)Type);

	if (!PawnsPtr)
		return CS_EMPTY;
	return PawnsPtr->Num();
}

ACsAIPawn* ACsManager_AI::Allocate(const TCsAIType &Type)
{
	TArray<ACsAIPawn*>* ActorPool = Pools.Find(Type);
	const uint8 Size			  = *(PoolSizes.Find(Type));

	for (uint8 I = 0; I < Size; ++I)
	{
		uint8* PoolIndexPtr	= (PoolIndices.Find(Type));
		*PoolIndexPtr		= (*PoolIndexPtr + I) % Size;
		ACsAIPawn* Actor	= (*ActorPool)[*PoolIndexPtr];

		if (!Actor->Cache.IsAllocated)
		{
			Actor->Cache.IsAllocated = true;
			return Actor;
		}
	}
	checkf(0, TEXT("ACsManager_AI::Allocate: Pool: %s is exhausted"), *(*AITypeToString(Type)));
	return nullptr;
}

void ACsManager_AI::DeAllocate(const uint8 &Type, const int32 &Index)
{
	const TCsAIType ClassType = (TCsAIType)Type;

	TArray<ACsAIPawn*>* Actors = ActiveAIPawns.Find(ClassType);

	if (!Actors)
	{
		UE_LOG(LogCs, Warning, TEXT("ACsManager_AI::DeAllocate: AI Pawn of Type: %s at Index: %d is already deallocated."), *((*AITypeToString)(ClassType)), Index);
		return;
	}

	const uint8 Count = Actors->Num();

	for (int32 I = Count - 1; I >= 0; --I)
	{
		ACsAIPawn* Actor = (*Actors)[I];

		if (Actor->PoolIndex == Index)
		{
			Actor->DeAllocate();
			Actors->RemoveAt(I);
			return;
		}
	}
	UE_LOG(LogCs, Warning, TEXT("ACsManager_AI::DeAllocate: AI Pawn of Type: %s at Index: %d is already deallocated."), *((*AITypeToString)(ClassType)), Index);
}

void ACsManager_AI::DeAllocateAll()
{
	const uint8 Count = (uint8)AIType_MAX;

	for (uint8 I = 0; I < Count; ++I)
	{
		const TCsAIType Type = (TCsAIType)I;

		TArray<ACsAIPawn*>* Actors = ActiveAIPawns.Find(Type);

		if (!Actors)
			continue;

		const int32 ActorCount = Actors->Num();

		for (int32 J = ActorCount - 1; J >= 0; --J)
		{
			(*Actors)[J]->DeAllocate();
			Actors->RemoveAt(J);
		}
	}
}

ACsAIPawn* ACsManager_AI::WakeUp(const TCsAIType &Type, UObject* InOwner, UObject* Parent)
{
	ACsAIPawn* Actor = Allocate(Type);

	Actor->Allocate(GetActivePoolSize((uint8)Type), GetWorld()->TimeSeconds, GetWorld()->RealTimeSeconds, 0, InOwner, Parent);
	AddToActivePool(Actor, (uint8)Type);
	return Actor;
}

ACsAIPawn* ACsManager_AI::WakeUp(const TCsAIType &Type, UObject* InOwner)
{
	return WakeUp(Type, InOwner, nullptr);
}

ACsAIPawn* ACsManager_AI::WakeUp(const TCsAIType &Type)
{
	return WakeUp(Type, nullptr, nullptr);
}

template<typename T>
void ACsManager_AI::WakeUp(const TCsAIType &Type, ACsAIPawn* &OutPawn, UObject* InOwner, UObject* Parent, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&))
{
	OutPawn = Allocate(Type);

	OutPawn->Allocate<T>(GetActivePoolSize((uint8)Type), GetWorld()->TimeSeconds, GetWorld()->RealTimeSeconds, 0, InOwner, Parent, InObject, OnDeAllocate);
	AddToActivePool(Actor, (uint8)Type);
}

template<typename T>
void ACsManager_AI::WakeUp(const TCsAIType &Type, ACsAIPawn* &OutPawn, UObject* InOwner, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&))
{
	WakeUp<T>(Type, OutPawn, nullptr, InOwner, InObject, OnDeAllocate);
}

template<typename T>
void ACsManager_AI::WakeUp(const TCsAIType &ClassType, ACsAIPawn* &OutPawn, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&))
{
	WakeUp<T>(Type, OutPawn, nullptr, nullptr, InObject, OnDeAllocate);
}
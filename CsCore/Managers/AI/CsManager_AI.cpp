// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/AI/CsManager_AI.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Common/CsCommon.h"

#include "AI/CsAIController.h"
#include "AI/Pawn/CsAIPawn.h"
#include "Game/CsGameState.h"

// Cache
#pragma region

namespace ECsManagerAICached
{
	namespace Str
	{
		// Functions
		const FString WakeUp = TEXT("ACsManager_AI::WakeUp");
		const FString DeAllocate = TEXT("ACsManager_AI::DeAllocate");
		const FString DeAllocateAll = TEXT("ACsManager_AI::DeAllocateAll");
	};
}

#pragma endregion Cache

ACsManager_AI::ACsManager_AI(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	AITypeToString = nullptr;

	PoolSize = 1;
}

void ACsManager_AI::Shutdown()
{
	Super::Shutdown();

	int32 Count = ControllerPool.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		if (ControllerPool[I] && !ControllerPool[I]->IsPendingKill())
		{
			ControllerPool[I]->UnPossess();
			ControllerPool[I]->Destroy(true);
		}
	}
	ControllerPool.Reset();
	ControllerPools.Reset();
	ActiveControllers.Reset();

	Count = Pool.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		if (Pool[I] && !Pool[I]->IsPendingKill())
			Pool[I]->Destroy(true);
	}
	Pool.Reset();
	Pools.Reset();
	PoolSizes.Reset();
	PoolIndices.Reset();
	ActivePawns.Reset();
}

void ACsManager_AI::Destroyed()
{
	Shutdown();

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
	TArray<ACsAIController*> TempControllerPool;

	for (int32 I = 0; I < Size; ++I)
	{
		ACsAIPawn* Pawn = GetWorld()->SpawnActor<ACsAIPawn>(ObjectClass, SpawnInfo);
		Pawn->Init(I, ClassType);
		Pawn->OnCreatePool();
		Pool.Add(Pawn);
		PawnPool.Add(Pawn);

		ACsAIController* Controller = Cast<ACsAIController>(Pawn->Controller);

		ControllerPool.Add(Controller);
		TempControllerPool.Add(Controller);
	}
	Pools.Add(ClassType, PawnPool);
	ControllerPools.Add(ClassType, TempControllerPool);
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

	TArray<ACsAIPawn*>* ActorPoolPtr = ActivePawns.Find(ClassType);

	Actor->Cache.IsAllocated = true;

	if (ActorPoolPtr)
	{
		ActorPoolPtr->Add(Actor);
	}
	else
	{
		TArray<ACsAIPawn*> ActorPool;
		ActorPool.Add(Actor);
		ActivePawns.Add(ClassType, ActorPool);
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
	TArray<ACsAIPawn*>* PawnsPtr = ActivePawns.Find((TCsAIType)Type);

	if (!PawnsPtr)
		return CS_EMPTY;
	return PawnsPtr->Num();
}

void ACsManager_AI::LogTransaction(const FString &FunctionName, const TEnumAsByte<ECsPoolTransaction::Type> &Transaction, class UObject* InObject)
{
	if (CsCVarLogManagerAITransactions->GetInt() == CS_CVAR_SHOW_LOG)
	{
		ACsAIPawn* Pawn = Cast<ACsAIPawn>(InObject);

		const FString& TransactionAsString = ECsPoolTransaction::ToActionString(Transaction);

		const FString PawnName			= Pawn->GetName();
		//const FString DataName		= Pawn->Cache.GetData()->ShortCode.ToString();
		const float CurrentTime			= GetWorld()->GetTimeSeconds();
		const UObject* PawnOwner		= Pawn->Cache.GetOwner();
		const FString OwnerName			= PawnOwner ? PawnOwner->GetName() : TEXT("None");
		const UObject* Parent			= Pawn->Cache.GetParent();
		const FString ParentName		= Parent ? Parent->GetName() : TEXT("None");
		const FString LocationAsString	= Pawn->GetActorLocation().ToString();
		const FString RotationAsString	= Pawn->GetActorRotation().ToString();

		if (PawnOwner && Parent)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s Pawn: %s at %f for %s attached to %s at %s facing %s."), *FunctionName, *TransactionAsString, *PawnName, CurrentTime, *OwnerName, *ParentName, *LocationAsString, *RotationAsString);
		}
		else
		if (PawnOwner)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s Pawn: %s at %f for %s at %s facing %s."), *FunctionName, *TransactionAsString, *PawnName, CurrentTime, *OwnerName, *LocationAsString, *RotationAsString);
		}
		else
		if (Parent)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s Pawn: %s at %f attached to %s at %s facing %s."), *TransactionAsString, *FunctionName, *PawnName, CurrentTime, *ParentName, *LocationAsString, *RotationAsString);
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s Pawn: %s at %f at %s facing %s."), *FunctionName, *TransactionAsString, *PawnName, CurrentTime, *LocationAsString, *RotationAsString);
		}
}
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

	TArray<ACsAIPawn*>* Actors = ActivePawns.Find(ClassType);

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
			LogTransaction(ECsManagerAICached::Str::DeAllocate, ECsPoolTransaction::Deallocate, Actor);

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

		TArray<ACsAIPawn*>* Actors = ActivePawns.Find(Type);

		if (!Actors)
			continue;

		const int32 ActorCount = Actors->Num();

		for (int32 J = ActorCount - 1; J >= 0; --J)
		{
			LogTransaction(ECsManagerAICached::Str::DeAllocateAll, ECsPoolTransaction::Deallocate, (*Actors)[J]);

			(*Actors)[J]->DeAllocate();
			Actors->RemoveAt(J);
		}
	}
}

// Payload
#pragma region

FCsAIPawnPayload* ACsManager_AI::AllocatePayload()
{
	for (uint8 I = 0; I < CS_AI_PAWN_PAYLOAD_SIZE; ++I)
	{
		const uint8 Index		  = (PayloadIndex + I) % CS_AI_PAWN_PAYLOAD_SIZE;
		FCsAIPawnPayload* Payload = &(Payloads[Index]);

		if (!Payload->IsAllocated)
		{
			Payload->IsAllocated = true;
			return Payload;
		}
	}
	checkf(0, TEXT("UICsManager_Widget::AllocatePayload: Pool is exhausted"));
	return nullptr;
}

#pragma endregion Payload

// Wake Up
#pragma region

ACsAIPawn* ACsManager_AI::WakeUp(const TCsAIType &Type, FCsAIPawnPayload* Payload, UObject* InOwner, UObject* Parent)
{
	ACsAIPawn* Actor = Allocate(Type);

	Actor->Allocate(GetActivePoolSize((uint8)Type), Payload, GetWorld()->GetTimeSeconds(), GetWorld()->GetRealTimeSeconds(), UCsCommon::GetCurrentFrame(GetWorld()), InOwner, Parent);

	LogTransaction(ECsManagerAICached::Str::WakeUp, ECsPoolTransaction::Allocate, Actor);

	AddToActivePool(Actor, (uint8)Type);
	Payload->Reset();
	return Actor;
}

ACsAIPawn* ACsManager_AI::WakeUp(const TCsAIType &Type, FCsAIPawnPayload* Payload, UObject* InOwner)
{
	return WakeUp(Type, Payload, InOwner, nullptr);
}

ACsAIPawn* ACsManager_AI::WakeUp(const TCsAIType &Type, FCsAIPawnPayload* Payload)
{
	return WakeUp(Type, Payload, nullptr, nullptr);
}

template<typename T>
void ACsManager_AI::WakeUp(const TCsAIType &Type, ACsAIPawn* &OutPawn, FCsAIPawnPayload* Payload, UObject* InOwner, UObject* Parent, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&))
{
	OutPawn = Allocate(Type);

	OutPawn->Allocate<T>(GetActivePoolSize((uint8)Type), Payload, GetWorld()->GetTimeSeconds(), GetWorld()->GetRealTimeSeconds(), UCsCommon::GetCurrentFrame(GetWorld()), InOwner, Parent, InObject, OnDeAllocate);

	LogTransaction(ECsManagerAICached::Str::WakeUp, ECsPoolTransaction::Allocate, OutPawn);

	AddToActivePool(Actor, (uint8)Type);
	Payload->Reset();
}

template<typename T>
void ACsManager_AI::WakeUp(const TCsAIType &Type, ACsAIPawn* &OutPawn, FCsAIPawnPayload* Payload, UObject* InOwner, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&))
{
	WakeUp<T>(Type, OutPawn, Payload, nullptr, InOwner, InObject, OnDeAllocate);
}

template<typename T>
void ACsManager_AI::WakeUp(const TCsAIType &ClassType, ACsAIPawn* &OutPawn, FCsAIPawnPayload* Payload, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&))
{
	WakeUp<T>(Type, OutPawn, Payload, nullptr, nullptr, InObject, OnDeAllocate);
}

#pragma endregion Wake Up
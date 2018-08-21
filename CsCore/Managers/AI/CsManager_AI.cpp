// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/AI/CsManager_AI.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Common/CsCommon.h"

#include "AI/CsAIController.h"
// Player
#include "Player/CsPlayerState.h"
// Game
#include "Game/CsGameState.h"

// static initializations
TWeakObjectPtr<UObject> AICsManager_AI::MyOwner;

// Internal
#pragma region

FCsManager_AI::~FCsManager_AI() {}

void FCsManager_AI::DeconstructObject(ACsAIPawn* a)
{
	if (a && !a->IsPendingKill())
		a->Destroy(true);
}

void FCsManager_AI::Shutdown()
{
	for (ACsAIController* Controller : ControllerPool)
	{
		if (Controller && !Controller->IsPendingKill())
		{
			Controller->UnPossess();
			Controller->Destroy(true);
		}
	}
	ControllerPool.Reset();
	Super::Shutdown();
}

FString FCsManager_AI::GetObjectName(ACsAIPawn* a)
{
	return a->GetName();
}

void FCsManager_AI::CreatePool(const FECsAIType &e, const int32 &size)
{
	PoolSizes.Add(e, size);
	PoolIndices.Add(e, 0);

	TArray<ACsAIPawn*> pool;

	for (int32 i = 0; i < size; ++i)
	{
		ACsAIPawn* o = ConstructObject_Call.Execute(e);
		o->Init(i, e);
		o->OnCreatePool();
		o->DeAllocate();
		Pool.Add(o);
		pool.Add(o);

		ACsAIController* controller = Cast<ACsAIController>(o->Controller);

		ControllerPool.Add(controller);

		OnAddToPool_Event.Broadcast(e, o);
	}
	Pools.Add(e, pool);
	PoolSize = Pool.Num();
}

void FCsManager_AI::AddToPool(const FECsAIType &e, ACsAIPawn* a)
{
	Super::AddToPool(e, a);

	ACsAIController* controller = Cast<ACsAIController>(a->Controller);

	ControllerPool.Add(controller);
}

const FString& FCsManager_AI::EnumTypeToString(const FECsAIType &e)
{
	return e.Name;
}

const FString& FCsManager_AI::EnumTypeToString(const int32 &index)
{
	return EMCsAIType::Get().GetEnumAt(index).Name;
}

void FCsManager_AI::LogTransaction(const FString &functionName, const TEnumAsByte<ECsPoolTransaction::Type> &transaction, ACsAIPawn* o)
{
	if ((*LogTransactions)->GetInt() == CS_CVAR_SHOW_LOG)
	{
		const FString& transactionAsString = ECsPoolTransaction::ToActionString(transaction);

		const FString objectName		= GetObjectName(o);
		const FString typeAsString		= EnumTypeToString(o->Cache.Type);
		const float currentTime			= GetCurrentTimeSeconds();
		const UObject* objectOwner		= o->Cache.GetOwner();
		const FString ownerName			= objectOwner ? objectOwner->GetName() : ECsCached::Str::None;
		const UObject* parent			= o->Cache.GetParent();
		const FString parentName		= parent ? parent->GetName() : ECsCached::Str::None;
		const FString locationAsString	= o->GetActorLocation().ToString();
		const FString rotationAsString	= o->GetActorRotation().ToString();

		FString log = ECsCached::Str::Empty;

		if (objectOwner && parent)
		{
			log = FString::Printf(TEXT("%s: %s %s: %s of Type: %s at %f for %s attached to %s at %s facing %s."), *functionName, *transactionAsString, *ObjectClassName, *objectName, *typeAsString, currentTime, *ownerName, *parentName, *locationAsString, *rotationAsString);
		}
		else
		if (objectOwner)
		{
			log = FString::Printf(TEXT("%s: %s %s: %s of Type: %s at %f for %s at %s facing %s."), *functionName, *transactionAsString, *ObjectClassName, *objectName, *typeAsString, currentTime, *ownerName, *locationAsString, *rotationAsString);
		}
		else
		if (parent)
		{
			log = FString::Printf(TEXT("%s: %s %s: %s of Type: %s at %f attached to %s at %s facing %s."), *functionName, *transactionAsString, *ObjectClassName, *objectName, *typeAsString, currentTime, *parentName, *locationAsString, *rotationAsString);
		}
		else
		{
			log = FString::Printf(TEXT("%s: %s %s: %s of Type: %s at %f at %s facing %s."), *functionName, *transactionAsString, *ObjectClassName, *objectName, *typeAsString, currentTime, *locationAsString, *rotationAsString);
		}
		Log(log);
	}
}

void FCsManager_AI::Log(const FString& log)
{
	UE_LOG(LogCs, Warning, TEXT("%s"), *log);
}

#pragma endregion // Internal

AICsManager_AI::AICsManager_AI(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Internal = new FCsManager_AI();
	Internal->Init(TEXT("AICsManager_AI"), TEXT("ACsAIPawn"), nullptr, &CsCVarLogManagerAITransactions);
	Internal->ConstructObject_Call.Unbind();
	Internal->ConstructObject_Call.BindUObject(this, &AICsManager_AI::ConstructObject);
}

/*static*/ UObject* AICsManager_AI::GetMyOwner() { return MyOwner.IsValid() ? MyOwner.Get() : nullptr; }

/*static*/ void AICsManager_AI::Init(UObject* InOwner)
{
	MyOwner = InOwner;
}

/*static*/ AICsManager_AI* AICsManager_AI::Get(UWorld* InWorld)
{
	return InWorld->GetGameState<ACsGameState>()->Manager_AI;
}

void AICsManager_AI::Clear()
{
	Internal->Clear();
}

void AICsManager_AI::Shutdown()
{
	Clear();
	Internal->Shutdown();
	delete Internal;
}

void AICsManager_AI::Destroyed()
{
	Shutdown();

	Super::Destroyed();
}

ACsAIPawn* AICsManager_AI::ConstructObject(const FECsAIType &Type)
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnInfo.ObjectFlags |= RF_Transient;

	ACsAIPawn* Actor = GetWorld()->SpawnActor<ACsAIPawn>(ClassMap.Find(Type) ? ClassMap[Type] : ACsAIPawn::StaticClass(), SpawnInfo);
	return Actor;
}

void AICsManager_AI::CreatePool(const FECsAIType &Type, const int32 &Size)
{
	Internal->CreatePool(Type, Size);
}

void AICsManager_AI::AddToPool(const FECsAIType &Type, ACsAIPawn* Actor)
{
	Internal->AddToPool(Type, Actor);
}

void AICsManager_AI::AddToActivePool(const FECsAIType &Type, ACsAIPawn* Actor)
{
	Internal->AddToActivePool(Type, Actor);
}

void AICsManager_AI::OnTick(const float &DeltaTime)
{
	Internal->OnTick(DeltaTime);
}

const TArray<ACsAIPawn*>& AICsManager_AI::GetAllPawns()
{
	return Internal->GetAllObjects();
}

void AICsManager_AI::GetAllActivePawns(TArray<ACsAIPawn*> &OutActors)
{
	Internal->GetAllActiveObjects(OutActors);
}

const TArray<ACsAIPawn*>* AICsManager_AI::GetPawns(const FECsAIType& Type)
{
	return Internal->GetObjects(Type);
}

int32 AICsManager_AI::GetActivePoolSize(const FECsAIType &Type)
{
	return Internal->GetActivePoolSize(Type);
}

bool AICsManager_AI::IsExhausted(const FECsAIType &Type)
{
	return Internal->IsExhausted(Type);
}

bool AICsManager_AI::DeAllocate(const FECsAIType &Type, const int32 &Index)
{
	return Internal->DeAllocate(Type, Index);
}

void AICsManager_AI::DeAllocateAll()
{
	return Internal->DeAllocateAll();
}

FCsAIPawnPayload* AICsManager_AI::AllocatePayload()
{
	return Internal->AllocatePayload();
}

ACsAIPawn* AICsManager_AI::Spawn(const FECsAIType &Type, FCsAIPawnPayload &Payload)
{
	return Internal->Spawn(Type, &Payload);
}

ACsAIPawn* AICsManager_AI::Spawn(const FECsAIType &Type, FCsAIPawnPayload *Payload)
{
	return Internal->Spawn(Type, Payload);
}
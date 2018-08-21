// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/FX/CsManager_FX.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Common/CsCommon.h"

#include "Game/CsGameState.h"

#if WITH_EDITOR
#include "Animation/CsAnimInstance.h"
#endif // #if WITH_EDITOR

// static initializations
TWeakObjectPtr<UObject> AICsManager_FX::MyOwner;

// Internal
#pragma region

FCsManager_FX::~FCsManager_FX() {}

// Interface
#pragma region

void FCsManager_FX::DeconstructObject(ACsEmitter* a)
{
	if (a && !a->IsPendingKill())
		a->Destroy(true);
}

FString FCsManager_FX::GetObjectName(ACsEmitter* a)
{
	return a->GetName();
}

void FCsManager_FX::LogTransaction(const FString &functionName, const TEnumAsByte<ECsPoolTransaction::Type> &transaction, ACsEmitter* o)
{
	if ((*LogTransactions)->GetInt() == CS_CVAR_SHOW_LOG)
	{
		const FString& transactionAsString = ECsPoolTransaction::ToActionString(transaction);

		const FString objectName	= GetObjectName(o);
		const FString particleName	= o->Cache.GetParticle()->GetName();
		const float currentTime		= GetCurrentTimeSeconds();
		const UObject* objectOwner	= o->Cache.GetOwner();
		const FString ownerName		= objectOwner ? objectOwner->GetName() : ECsCached::Str::None;
		const UObject* parent		= o->Cache.GetParent();
		const FString parentName	= parent ? parent->GetName() : ECsCached::Str::None;

		FString log = ECsCached::Str::Empty;

		if (objectOwner && parent)
		{
			log = FString::Printf(TEXT("%s: %s %s: %s with Particle: %s at %f for %s attached to %s."), *functionName, *transactionAsString, *ObjectClassName, *objectName, currentTime, *ownerName, *parentName);
		}
		else
		if (objectOwner)
		{
			log = FString::Printf(TEXT("%s: %s %s: %s with Particle: %s at %f for %s."), *functionName, *transactionAsString, *ObjectClassName, *objectName, currentTime, *ownerName);
		}
		else
		if (parent)
		{
			log = FString::Printf(TEXT("%s: %s %s: %s with Particle: %s at %f attached to %s."), *functionName, *transactionAsString, *ObjectClassName, *objectName, currentTime, *parentName);
		}
		else
		{
			if (o->Cache.Location != FVector::ZeroVector)
			{
				const FString locationAsString = o->Cache.Location.ToString();

				log = FString::Printf(TEXT("%s: %s %s: %s with Particle: %s at %f at %s."), *functionName, *transactionAsString, *ObjectClassName, *objectName, *particleName, currentTime, *locationAsString);
			}
			else
			{
				log = FString::Printf(TEXT("%s: %s %s: %s with Particle: %s at %f."), *functionName, *transactionAsString, *ObjectClassName, *objectName, *particleName, currentTime);
			}
		}
		Log(log);
	}
}

void FCsManager_FX::Log(const FString& log)
{
	UE_LOG(LogCs, Warning, TEXT("%s"), *log);
}

void FCsManager_FX::OnTick(const float &deltaTime)
{
	TArray<int32> keys;
	ActiveObjects.GetKeys(keys);

	for (const int32& key : keys)
	{
		ACsEmitter* o = ActiveObjects[key];

		// Check if ObjectType was DeAllocated NOT in a normal way (i.e. Out of Bounds)

		if (!o->Cache.IsAllocated)
		{
			OnTick_Log_PrematureDeAllocation(o);

			LogTransaction(FunctionNames[ECsManagerPooledObjectsFunctionNames::OnTick], ECsPoolTransaction::Deallocate, o);

			ActiveObjects.Remove(key);
			continue;
		}

		if (!o->Cache.bLifeTime)
		{
			OnTick_Handle_Object.ExecuteIfBound(o);
			continue;
		}

		// Check Dying
		if (o->Cache.IsDying)
		{
			if (GetCurrentTimeSeconds() - o->Cache.DeathStartTime > o->Cache.DeathTime)
			{
				LogTransaction(FunctionNames[ECsManagerPooledObjectsFunctionNames::OnTick], ECsPoolTransaction::Deallocate, o);

				o->DeAllocate();
				ActiveObjects.Remove(key);

				OnDeAllocate_Event.Broadcast(o);
			}
		}
		// Check Normal Lifetime
		else
		{
			if (GetCurrentTimeSeconds() - o->Cache.Time > o->Cache.LifeTime)
			{
				if (o->Cache.DeathTime > 0.0f)
				{
					LogTransaction(FunctionNames[ECsManagerPooledObjectsFunctionNames::OnTick], ECsPoolTransaction::PreDeallocate, o);

					o->StartDeath();
				}
				else
				{
					LogTransaction(FunctionNames[ECsManagerPooledObjectsFunctionNames::OnTick], ECsPoolTransaction::Deallocate, o);

					o->DeAllocate();
					ActiveObjects.Remove(key);

					OnDeAllocate_Event.Broadcast(o);
				}
			}
		}

		OnTick_Handle_Object.ExecuteIfBound(o);
	}
}

ACsEmitter* FCsManager_FX::Allocate()
{
	int32 oldestIndex = INDEX_NONE;
	float oldestTime = GetCurrentTimeSeconds();

	for (int32 i = 0; i < PoolSize; ++i)
	{
		PoolIndex	  = (PoolIndex + i) % PoolSize;
		ACsEmitter* e = Pool[PoolIndex];

		if (e->Cache.Time < oldestTime)
		{
			oldestIndex = PoolIndex;
			oldestTime = e->Cache.Time;
		}

		if (!e->Cache.IsAllocated)
		{
			e->Cache.IsAllocated = true;
			return e;
		}
	}
#if WITH_EDITOR
	if (UCsCommon::IsPlayInEditorPreview(GetCurrentWorld()))
	{
		UE_LOG(LogCs, Warning, TEXT("ACsManager_FX::Allocate: Warning. Pool is exhausted. Using Oldest Active Emitter."));

		const int32& key = Pool[PoolIndex]->Cache.Index;

		if (ActiveObjects.Find(key))
			ActiveObjects.Remove(key);
		return Pool[oldestIndex];
	}
#endif // #if WITH_EDITOR
	checkf(0, TEXT("ACsManager_FX::Allocate: Pool is exhausted"));
	return nullptr;
}

#pragma endregion Interface

#if WITH_EDITOR
void FCsManager_FX::ToggleEmitterEditorIcons(const bool &toggle)
{
	for (int32 i = 0; i < PoolSize; ++i)
	{
		ACsEmitter* e = Pool[i];

		e->GetSpriteComponent()->SetVisibility(toggle);
		e->GetSpriteComponent()->SetHiddenInGame(!toggle);
		e->GetArrowComponent()->SetVisibility(toggle);
		e->GetArrowComponent()->SetHiddenInGame(!toggle);
	}
}

#endif // #if WITH_EDITOR

#pragma endregion // Internal

AICsManager_FX::AICsManager_FX(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Internal = new FCsManager_FX();
	Internal->Init(TEXT("AICsManager_FX"), TEXT("ACsEmitter"), nullptr, &CsCVarLogManagerFxTransactions);
	Internal->ConstructObject_Call.Unbind();
	Internal->ConstructObject_Call.BindUObject(this, &AICsManager_FX::ConstructObject);
}

void AICsManager_FX::PostActorCreated()
{
	Super::PostActorCreated();

	Internal->CurrentWorld = GetWorld();
}

/*static*/ UObject* AICsManager_FX::GetMyOwner() { return MyOwner.IsValid() ? MyOwner.Get() : nullptr; }

/*static*/ void AICsManager_FX::Init(UObject* InOwner)
{
	MyOwner = InOwner;
}

/*static*/ AICsManager_FX* AICsManager_FX::Get(UWorld* InWorld)
{
#if WITH_EDITOR 
	// In Editor Preview Window
	if (UCsCommon::IsPlayInEditorPreview(InWorld))
	{
		if (UCsAnimInstance* AnimInstance = Cast<UCsAnimInstance>(GetMyOwner()))
			return AnimInstance->GetManager_FX();
	}
	// In Game
	else
#endif // #if WITH_EDITOR
	{
		return Cast<ACsGameState>(GetMyOwner())->Manager_FX;
	}
	return nullptr;
}

void AICsManager_FX::Clear()
{
	Internal->Clear();
}

void AICsManager_FX::Shutdown()
{
	Clear();
	Internal->Shutdown();
	delete Internal;
}

void AICsManager_FX::Destroyed()
{
	Shutdown();

	Super::Destroyed();
}

ACsEmitter* AICsManager_FX::ConstructObject()
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnInfo.ObjectFlags |= RF_Transient;

	ACsEmitter* Actor = GetWorld()->SpawnActor<ACsEmitter>(ACsEmitter::StaticClass(), SpawnInfo);
	Actor->SetReplicates(false);
	Actor->Role = ROLE_None;
	GetWorld()->RemoveNetworkActor(Actor);
	return Actor;
}

void AICsManager_FX::CreatePool(const int32 &Size)
{
	Internal->CreatePool(Size);
}

void AICsManager_FX::AddToPool(ACsEmitter* Actor)
{
	Internal->AddToPool(Actor);
}

void AICsManager_FX::AddToActivePool(ACsEmitter* Actor)
{
	Internal->AddToActivePool(Actor);
}

void AICsManager_FX::OnTick(const float &DeltaTime)
{
	Internal->OnTick(DeltaTime);
}

const TMap<int32, ACsEmitter*>& AICsManager_FX::GetAllActiveActors()
{
	return Internal->GetAllActiveObjects();
}

const TArray<ACsEmitter*>& AICsManager_FX::GetActors()
{
	return Internal->GetObjects();
}

int32 AICsManager_FX::GetActivePoolSize()
{
	return Internal->GetActivePoolSize();
}

bool AICsManager_FX::IsExhausted()
{
	return Internal->IsExhausted();
}

bool AICsManager_FX::DeAllocate(const int32 &Index)
{
	return Internal->DeAllocate(Index);
}

void AICsManager_FX::DeAllocateAll()
{
	return Internal->DeAllocateAll();
}

FCsFxPayload* AICsManager_FX::AllocatePayload()
{
	return Internal->AllocatePayload();
}

ACsEmitter* AICsManager_FX::Play(FCsFxPayload &Payload)
{
	return Internal->Spawn(&Payload);
}

ACsEmitter* AICsManager_FX::Play(FCsFxPayload *Payload)
{
	return Internal->Spawn(Payload);
}

#if WITH_EDITOR

void AICsManager_FX::ToggleEmitterEditorIcons(const bool &Toggle)
{
	Internal->ToggleEmitterEditorIcons(Toggle);
}

#endif // #if WITH_EDITOR
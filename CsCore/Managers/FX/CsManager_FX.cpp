// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/FX/CsManager_FX.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Types/CsTypes.h"
#include "Common/CsCommon.h"
#include "Managers/FX/CsEmitter.h"
#include "Game/CsGameState.h"

ACsManager_FX::ACsManager_FX(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	EmitterClass = ACsEmitter::StaticClass();
}

/*static*/ ACsManager_FX* ACsManager_FX::Get(UWorld* InWorld)
{
	return InWorld->GetGameState<ACsGameState>()->Manager_FX;
}

void ACsManager_FX::Clear()
{
	Super::Clear();

	Pool.Reset();
	ActiveEmitters.Reset();
}

void ACsManager_FX::Shutdown()
{
	Super::Shutdown();

	const int32 Count = Pool.Num();

	for (int32 I = 0; I < Count; I++)
	{
		if (Pool[I] && !Pool[I]->IsPendingKill())
			Pool[I]->Destroy(true);
	}
	Clear();
}

void ACsManager_FX::Destroyed()
{
	const int32 Count = Pool.Num();

	for (int32 I = 0; I < Count; I++)
	{
		if (Pool[I] && !Pool[I]->IsPendingKill())
			Pool[I]->Destroy(true);
	}
	Clear();

	Super::Destroyed();
}

void ACsManager_FX::CreatePool(const int32 &Size)
{
	PoolSize = Size;

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnInfo.ObjectFlags |= RF_Transient;

	PoolIndex = 0;

	for (int32 I = 0; I < PoolSize; I++)
	{
		ACsEmitter* Emitter = GetWorld()->SpawnActor<ACsEmitter>(EmitterClass, SpawnInfo);
		Emitter->SetReplicates(false);
		Emitter->Role = ROLE_None;
		GetWorld()->RemoveNetworkActor(Emitter);
		Emitter->Init(I);
		Emitter->DeAllocate();
		Pool.Add(Emitter);
	}
}

void ACsManager_FX::OnTick(const float &DeltaSeconds)
{
	const uint8 Count   = ActiveEmitters.Num();
	uint8 EarliestIndex = Count;

	for (int32 I = Count - 1; I >= 0; I--)
	{
		ACsEmitter* Emitter = ActiveEmitters[I];

		// Check if Emitter was DeAllocated NOT in a normal way (i.e. Out of Bounds)
		if (!Emitter->Cache.IsAllocated)
		{
			UE_LOG(LogCs, Warning, TEXT("ACsManager_FX::OnTick: Emitter: %s at PoolIndex: %s was prematurely deallocted NOT in a normal way."), *(Emitter->GetName()), Emitter->Cache.Index);

			LogTransaction(TEXT("ACsManager_FX::OnTick"), ECsPoolTransaction::Deallocate, Emitter);

			ActiveEmitters.RemoveAt(I);

			if (I < EarliestIndex)
				EarliestIndex = I;
			continue;
		}

		// Check Dying
		if (Emitter->Cache.IsDying)
		{
			if (GetWorld()->GetTimeSeconds() - Emitter->Cache.DeathStartTime > Emitter->Cache.DeathTime)
			{
				LogTransaction(TEXT("ACsManager_FX::OnTick"), ECsPoolTransaction::Deallocate, Emitter);

				Emitter->DeAllocate();
				ActiveEmitters.RemoveAt(I);

				if (I < EarliestIndex)
					EarliestIndex = I;
			}
		}
		// Check Normal Lifetime
		else
		{
			if (GetWorld()->GetTimeSeconds() - Emitter->Cache.Time > Emitter->Cache.LifeTime)
			{
				if (Emitter->Cache.DeathTime > 0.0f)
				{
					LogTransaction(TEXT("ACsManager_FX::OnTick"), ECsPoolTransaction::PreDeallocate, Emitter);

					Emitter->StartDeath();
				}
				else
				{
					LogTransaction(TEXT("ACsManager_FX::OnTick"), ECsPoolTransaction::Deallocate, Emitter);

					Emitter->DeAllocate();
					ActiveEmitters.RemoveAt(I);

					if (I < EarliestIndex)
						EarliestIndex = I;
				}
			}
		}
	}
	// Update ActiveIndex
	if (EarliestIndex != Count)
	{
		const uint8 Max = ActiveEmitters.Num();

		for (uint8 I = EarliestIndex; I < Max; I++)
		{
			ACsEmitter* Emitter				  = ActiveEmitters[I];
			Emitter->Cache.ActiveIndex		  = I;
			Emitter->Cache.ActiveIndex_Script = I;
		}
	}
}

void ACsManager_FX::LogTransaction(const FString &FunctionName, const TEnumAsByte<ECsPoolTransaction::Type> &Transaction, UObject* InObject)
{
	if (CsCVarLogManagerFxTransactions->GetInt() == CS_CVAR_SHOW_LOG)
	{
		ACsEmitter* Emitter = Cast<ACsEmitter>(InObject);

		FString TransactionAsString = TEXT("");
		
		if (Transaction == ECsPoolTransaction::Allocate)
			TransactionAsString = TEXT("Allocating");
		else
		if (Transaction == ECsPoolTransaction::PreDeallocate)
			TransactionAsString = TEXT("PreDeAllocating");
		else
		if (Transaction == ECsPoolTransaction::Deallocate)
			TransactionAsString = TEXT("DeAllocating");

		const FString EmitterName   = Emitter->GetName();
		const FString ParticleName  = Emitter->Cache.GetParticle()->GetName();
		const float CurrentTime		= GetWorld()->GetTimeSeconds();
		const UObject* EmitterOwner = Emitter->Cache.GetOwner();
		const FString OwnerName		= EmitterOwner ? EmitterOwner->GetName() : TEXT("");
		const UObject* Parent		= Emitter->Cache.GetParent();
		const FString ParentName	= Parent ? Parent->GetName() : TEXT("");

		if (EmitterOwner && Parent)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s Emitter: %s with Particle: %s at %f for %s attached to %s."), *FunctionName, *TransactionAsString, *EmitterName, *ParticleName, CurrentTime, *OwnerName, *ParentName);
		}
		else
		if (EmitterOwner)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s Emitter: %s with Particle: %s at %f for %s."), *FunctionName, *TransactionAsString, *EmitterName, *ParticleName, CurrentTime, *OwnerName);
		}
		else
		if (Parent)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s Emitter: %s with Particle: %s at %f attached to %s."), *TransactionAsString, *FunctionName, *EmitterName, *ParticleName, CurrentTime, *ParentName);
		}
		else
		{
			if (Emitter->Cache.Location != FVector::ZeroVector)
			{
				const FString LocationAsString = Emitter->Cache.Location.ToString();

				UE_LOG(LogCs, Warning, TEXT("%s: %s Emitter: %s with Particle: %s at %f at %s."), *FunctionName, *TransactionAsString, *EmitterName, *ParticleName, CurrentTime, *LocationAsString);
			}
			else
			{
				UE_LOG(LogCs, Warning, TEXT("%s: %s Emitter: %s with Particle: %s at %f."), *FunctionName, *TransactionAsString, *EmitterName, *ParticleName, CurrentTime);
			}
		}
	}
}

ACsEmitter* ACsManager_FX::Allocate()
{
	int32 OldestIndex = INDEX_NONE;
	float OldestTime  = GetWorld()->GetTimeSeconds();

	for (uint8 I = 0; I < PoolSize; ++I)
	{
		PoolIndex			= (PoolIndex + I) % PoolSize;
		ACsEmitter* Emitter = Pool[PoolIndex];

		if (Emitter->Cache.Time < OldestTime)
		{
			OldestIndex = PoolIndex;
			OldestTime  = Emitter->Cache.Time;
		}

		if (!Emitter->Cache.IsAllocated)
		{
			Emitter->Cache.IsAllocated = true;
			return Emitter;
		}
	}
#if WITH_EDITOR
	if (UCsCommon::IsPlayInEditorPreview(GetWorld()))
	{
		UE_LOG(LogCs, Warning, TEXT("ACsManager_FX::Allocate: Warning. Pool is exhausted. Using Oldest Active Emitter."));
		
		const int32 Index = ActiveEmitters.Find(Pool[PoolIndex]);

		if (Index != INDEX_NONE)
			ActiveEmitters.RemoveAt(Index);
		return Pool[OldestIndex];
	}
#endif // #if WITH_EDITOR
	checkf(0, TEXT("ACsManager_FX::Allocate: Pool is exhausted"));
	return nullptr;
}

void ACsManager_FX::DeAllocate(const int32 &Index)
{
	const uint8 Count = ActiveEmitters.Num();

	for (int32 I = Count - 1; I >= 0; I--)
	{
		ACsEmitter* Emitter = ActiveEmitters[I];

		// Update ActiveIndex
		if (I > CS_FIRST)
		{
			Emitter->Cache.ActiveIndex--;
			Emitter->Cache.ActiveIndex_Script--;
		}

		if (Emitter->PoolIndex == Index)
		{
			LogTransaction(TEXT("ACsManager_FX::DeAllocate"), ECsPoolTransaction::Allocate, Emitter);

			Emitter->DeAllocate();
			ActiveEmitters.RemoveAt(I);

#if WITH_EDITOR
			OnDeAllocate_ScriptEvent.Broadcast(Index);
#endif // #if WITH_EDITOR
			OnDeAllocate_Event.Broadcast(Index);
			return;
		}
	}

	// Correct on Cache "Miss"
	for (int32 I = 1; I < Count; I++)
	{
		ACsEmitter* Emitter = ActiveEmitters[I];
		// Reset ActiveIndex
		Emitter->Cache.ActiveIndex++;
		Emitter->Cache.ActiveIndex_Script++;
	}
	UE_LOG(LogCs, Warning, TEXT("ACsManager_FX::DeAllocate: Emitter with PoolIndex: %s is already deallocated."), Index);
}

ACsEmitter* ACsManager_FX::Play(FCsFxElement* InFX, UObject* InOwner, UObject* InParent)
{
	if (!InFX->Get())
	{
		UE_LOG(LogCs, Warning, TEXT("ACsManager_FX::Play: Attempting to Play a NULL ParticleSystem."));
		return nullptr;
	}

	ACsEmitter* Emitter = Allocate();
	const int32 Count   = ActiveEmitters.Num();
	
	Emitter->Allocate((uint16)Count, InFX, GetWorld()->GetTimeSeconds(), GetWorld()->GetRealTimeSeconds(), 0, InOwner, InParent);

	LogTransaction(TEXT("ACsManager_FX::Play"), ECsPoolTransaction::Allocate, Emitter);

	ActiveEmitters.Add(Emitter);
	Emitter->Play();
	return Emitter;
}

ACsEmitter* ACsManager_FX::Play(FCsFxElement* InFX, UObject* InOwner)
{
	return Play(InFX, InOwner, nullptr);
}

ACsEmitter* ACsManager_FX::Play(FCsFxElement* InFX)
{
	return Play(InFX, nullptr, nullptr);
}

ACsEmitter* ACsManager_FX::Play(FCsFxElement* InFX, UObject* InOwner, const FVector &Location, const FRotator &Rotation)
{
	if (!InFX->Get())
	{
		UE_LOG(LogCs, Warning, TEXT("ACsManager_FX::Play: Attempting to Play a NULL ParticleSystem."));
		return nullptr;
	}

	ACsEmitter* Emitter = Allocate();
	const int32 Count   = ActiveEmitters.Num();

	Emitter->Allocate((uint16)Count, InFX, GetWorld()->GetTimeSeconds(), GetWorld()->GetRealTimeSeconds(), 0, InOwner, nullptr, Location, Rotation);

	LogTransaction(TEXT("ACsManager_FX::Play"), ECsPoolTransaction::Allocate, Emitter);

	ActiveEmitters.Add(Emitter);
	Emitter->Play();
	return Emitter;
}

ACsEmitter* ACsManager_FX::Play(FCsFxElement* InFX, UObject* InOwner, UObject* InParent, const FRotator &Rotation)
{
	if (!InFX->Get())
	{
		UE_LOG(LogCs, Warning, TEXT("ACsManager_FX::Play: Attempting to Play a NULL ParticleSystem."));
		return nullptr;
	}

	ACsEmitter* Emitter = Allocate();
	const int32 Count = ActiveEmitters.Num();

	Emitter->Allocate((uint16)Count, InFX, GetWorld()->GetTimeSeconds(), GetWorld()->GetRealTimeSeconds(), 0, InOwner, InParent, Rotation);

	LogTransaction(TEXT("ACsManager_FX::Play"), ECsPoolTransaction::Allocate, Emitter);

	ActiveEmitters.Add(Emitter);
	Emitter->Play();
	return Emitter;
}

template<typename T>
void ACsManager_FX::Play(ACsEmitter* OutEmitter, FCsFxElement* InFX, UObject* InOwner, UObject* InParent, T* InObject, void (T::*OnDeAllocate)())
{
	if (!InFX->Get())
	{
		UE_LOG(LogCs, Warning, TEXT("ACsManager_FX::Play: Attempting to Play a NULL ParticleSystem."));
		return nullptr;
	}

	OutEmitter		  = Allocate();
	const int32 Count = ActiveEmitters.Num();

	OutEmitter->Allocate<T>((uint16)Count, InFX, GetWorld()->GetTimeSeconds(), GetWorld()->GetRealTimeSeconds(), 0, InOwner, InParent, InObject, OnDeAllocate);

	LogTransaction(TEXT("ACsManager_FX::Play"), ECsPoolTransaction::Allocate, Emitter);

	ActiveEmitters.Add(OutEmitter);
	OutEmitter->Play();
}

template<typename T>
void ACsManager_FX::Play(ACsEmitter* OutEmitter, FCsFxElement* InFX, UObject* InOwner, T* InObject, void (T::*OnDeAllocate)())
{
	Play(OutEmitter, InFX, nullptr, InOwner, InObject, OnDeAllocate);
}

template<typename T>
void ACsManager_FX::Play(ACsEmitter* OutEmitter, FCsFxElement* InFX, T* InObject, void (T::*OnDeAllocate)())
{
	Play(OutEmitter, InFX, nullptr, nullptr, InObject, OnDeAllocate);
}

template<typename T>
void ACsManager_FX::Play(ACsEmitter* OutEmitter, FCsFxElement* InFX, UObject* InOwner, const FVector &Location, const FRotator &Rotation, T* InObject, void (T::*OnDeAllocate)())
{
	if (!InFX->Get())
	{
		UE_LOG(LogCs, Warning, TEXT("ACsManager_FX::Play: Attempting to Play a NULL ParticleSystem."));
		return nullptr;
	}

	OutEmitter		  = Allocate();
	const int32 Count = ActiveEmitters.Num();

	OutEmitter->Allocate<T>((uint16)Count, InFX, GetWorld()->GetTimeSeconds(), GetWorld()->GetRealTimeSeconds(), 0, InOwner, Location, Rotation, InObject, OnDeAllocate);

	LogTransaction(TEXT("ACsManager_FX::Play"), ECsPoolTransaction::Allocate, Emitter);

	ActiveEmitters.Add(OutEmitter);
	OutEmitter->Play();
}

ACsEmitter* ACsManager_FX::Play_Script(FCsFxElement& InFX, UObject* InOwner, UObject* InParent)
{
	return Play(&InFX, InOwner, InParent);
}

ACsEmitter* ACsManager_FX::Play_ScriptEX(FCsFxElement& InFX, UObject* InOwner, const FVector &Location, const FRotator &Rotation)
{
	return Play(&InFX, InOwner, Location, Rotation);
}

#if WITH_EDITOR

void ACsManager_FX::ToggleEmitterEditorIcons(const bool &Toggle)
{
	for (uint8 I = 0; I < PoolSize; ++I)
	{
		ACsEmitter* Emitter = Pool[I];

		Emitter->GetSpriteComponent()->SetVisibility(Toggle);
		Emitter->GetSpriteComponent()->SetHiddenInGame(!Toggle);
		Emitter->GetArrowComponent()->SetVisibility(Toggle);
		Emitter->GetArrowComponent()->SetHiddenInGame(!Toggle);
	}
}

#endif // #if WITH_EDITOR
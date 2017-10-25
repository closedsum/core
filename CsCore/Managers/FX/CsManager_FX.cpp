// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/FX/CsManager_FX.h"
#include "CsCore.h"
#include "Types/CsTypes.h"
#include "Common/CsCommon.h"
#include "Managers/FX/CsEmitter.h"

ACsManager_FX::ACsManager_FX(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	EmitterClass = ACsEmitter::StaticClass();
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
	Pool.Reset();
	ActiveEmitters.Reset();
}

void ACsManager_FX::Destroyed()
{
	const int32 Count = Pool.Num();

	for (int32 I = 0; I < Count; I++)
	{
		if (Pool[I] && !Pool[I]->IsPendingKill())
			Pool[I]->Destroy(true);
	}
	Pool.Reset();
	ActiveEmitters.Reset();

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

void ACsManager_FX::PostActorCreated()
{
	Super::PostActorCreated();
}

void ACsManager_FX::OnTick(const float &DeltaSeconds)
{
	const uint8 Count = ActiveEmitters.Num();

	for (int32 I = Count - 1; I >= 0; I--)
	{
		ACsEmitter* Emitter = ActiveEmitters[I];

		// Check Dying
		if (Emitter->Cache.IsDying)
		{
			if (GetWorld()->GetTimeSeconds() - Emitter->Cache.DeathStartTime > Emitter->Cache.DeathTime)
			{
				Emitter->DeAllocate();
				ActiveEmitters.RemoveAt(I);
			}
		}
		// Check Normal Lifetime
		else
		{
			if (GetWorld()->GetTimeSeconds() - Emitter->Cache.Time > Emitter->Cache.LifeTime)
			{
				if (Emitter->Cache.DeathTime > 0.0f)
				{
					Emitter->StartDeath();
				}
				else
				{
					Emitter->DeAllocate();
					ActiveEmitters.RemoveAt(I);
				}
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

		if (Emitter->PoolIndex == Index)
		{
			Emitter->DeAllocate();
			ActiveEmitters.RemoveAt(I);
			return;
		}
	}
}

ACsEmitter* ACsManager_FX::Play(FCsFxElement* InFX, UObject* InOwner, UObject* Parent)
{
	UParticleSystem* Particle = InFX->Get();

	if (!Particle)
	{
		UE_LOG(LogCs, Warning, TEXT("ACsManager_FX::Play: Warning. Trying to Allocate Emitter with nullptr Particle System."));
		return nullptr;
	}

	ACsEmitter* Emitter = Allocate();

	ActiveEmitters.Add(Emitter);

	Emitter->Allocate(InFX, GetWorld()->TimeSeconds, GetWorld()->RealTimeSeconds, 0, InOwner, Parent);
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

ACsEmitter* ACsManager_FX::Play(FCsFxElement* InFX, UObject* InOwner, const FVector &Location)
{
	ACsEmitter* Emitter = Allocate();

	Emitter->Allocate(InFX, GetWorld()->TimeSeconds, GetWorld()->RealTimeSeconds, 0, InOwner, nullptr, Location);
	Emitter->Play();
	return Emitter;
}

template<typename T>
void ACsManager_FX::Play(ACsEmitter* OutEmitter, FCsFxElement* InFX, UObject* InOwner, UObject* Parent, T* InObject, void (T::*OnDeAllocate)())
{
	OutEmitter = Allocate();

	OutEmitter->Allocate<T>(InFX, GetWorld()->TimeSeconds, GetWorld()->RealTimeSeconds, 0, InOwner, Parent, InObject, OnDeAllocate);
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
void ACsManager_FX::Play(ACsEmitter* OutEmitter, FCsFxElement* InFX, UObject* InOwner, const FVector &Location, T* InObject, void (T::*OnDeAllocate)())
{
	OutEmitter = Allocate();

	OutEmitter->Allocate<T>(InFX, GetWorld()->TimeSeconds, GetWorld()->RealTimeSeconds, 0, InOwner, Location, InObject, OnDeAllocate);
	OutEmitter->Play();
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
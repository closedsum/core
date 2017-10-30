// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Sound/CsManager_Sound.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Managers/Sound/CsSound.h"
#include "Common/CsCommon.h"
#include "Game/CsGameState.h"

ACsManager_Sound::ACsManager_Sound(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	SoundClass = ACsSound::StaticClass();

	PoolSize = CS_SOUND_POOL_SIZE;
}

void ACsManager_Sound::Shutdown()
{
	Super::Shutdown();

	const int32 Count = Pool.Num();

	for (int32 I = 0; I < Count; I++)
	{
		if (Pool[I] && !Pool[I]->IsPendingKill())
			Pool[I]->Destroy(true);
	}
	Pool.Reset();
	ActiveSounds.Reset();
}

void ACsManager_Sound::Destroyed()
{
	const int32 Count = Pool.Num();

	for (int32 I = 0; I < Count; I++)
	{
		if (Pool[I] && !Pool[I]->IsPendingKill())
			Pool[I]->Destroy(true);
	}
	Pool.Reset();
	ActiveSounds.Reset();

	Super::Destroyed();
}

void ACsManager_Sound::CreatePool(const int32 &Size)
{
	PoolSize = Size;

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnInfo.ObjectFlags |= RF_Transient;

	PoolIndex = 0;

	for (int32 I = 0; I < Size; I++)
	{
		ACsSound* Sound = GetWorld()->SpawnActor<ACsSound>(SoundClass, SpawnInfo);
		Sound->SetReplicates(false);
		Sound->Role = ROLE_None;
		GetWorld()->RemoveNetworkActor(Sound);
		Sound->Init(I);
		Pool.Add(Sound);
	}
}

void ACsManager_Sound::PostActorCreated()
{
	Super::PostActorCreated();

#if WITH_EDITOR
	if (UCsCommon::IsPlayInEditorPreview(GetWorld()))
		return;
#endif // #if WITH_EDITOR
	CreatePool(CS_SOUND_POOL_SIZE);
}

void ACsManager_Sound::OnTick(const float &DeltaSeconds)
{
	const uint8 Count = ActiveSounds.Num();

	for (int32 I = Count - 1; I >= 0; I--)
	{
		ACsSound* Sound = ActiveSounds[I];

		if (GetWorld()->TimeSeconds - Sound->Cache.Time > Sound->Cache.Duration)
		{
			LogTransaction(TEXT("ACsManager_Sound::Play"), ECsPoolTransaction::Deallocate, Sound);

			Sound->DeAllocate();
			ActiveSounds.RemoveAt(I);
		}
	}
}

/*static*/ ACsManager_Sound* ACsManager_Sound::Get(UWorld* InWorld)
{
	return InWorld->GetGameState<ACsGameState>()->Manager_Sound;
}

void ACsManager_Sound::LogTransaction(const FString &FunctionName, const TEnumAsByte<ECsPoolTransaction::Type> &Transaction, UObject* InObject)
{
	if (CsCVarLogManagerSoundTransactions->GetInt() == CS_CVAR_SHOW_LOG)
	{
		ACsSound* Sound = Cast<ACsSound>(InObject);

		const FString TransactionAsString = Transaction == ECsPoolTransaction::Allocate ? TEXT("Allocating") : TEXT("DeAllocating");

		const FString SoundName   = Sound->GetName();
		const FString CueName	  = Sound->Cache.GetCue()->GetName();
		const float CurrentTime   = GetWorld()->GetTimeSeconds();
		const UObject* SoundOwner = Sound->Cache.GetOwner();
		const FString OwnerName	  = SoundOwner ? SoundOwner->GetName() : TEXT("");
		const UObject* Parent	  = Sound->Cache.GetParent();
		const FString ParentName  = Parent ? Parent->GetName() : TEXT("");

		if (SoundOwner && Parent)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s Sound: %s with Cue: %s at %f for %s attached to %s."), *FunctionName, *TransactionAsString, *SoundName, *CueName, CurrentTime, *OwnerName, *ParentName);
		}
		else
		if (SoundOwner)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s Sound: %s with Cue: %s at %f for %s."), *FunctionName, *TransactionAsString, *SoundName, *CueName, CurrentTime, *OwnerName);
		}
		else
		if (Parent)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s Sound: %s with Cue: %s at %f attached to %s."), *TransactionAsString, *FunctionName, *SoundName, *CueName, CurrentTime, *ParentName);
		}
		else
		{
			if (Sound->Cache.Location != FVector::ZeroVector)
			{
				const FString LocationAsString = Sound->Cache.Location.ToString();

				UE_LOG(LogCs, Warning, TEXT("%s: %s Sound: %s with Cue: %s at %f at %s."), *FunctionName, *TransactionAsString, *SoundName, *CueName, CurrentTime, *ParentName, *LocationAsString);
			}
			else
			{
				UE_LOG(LogCs, Warning, TEXT("%s: %s Sound: %s with Cue: %s at %f."), *FunctionName, *TransactionAsString, *SoundName, *CueName, CurrentTime, *ParentName);
			}
		}
	}
}

ACsSound* ACsManager_Sound::Allocate()
{
	for (uint8 I = 0; I < PoolSize; ++I)
	{
		PoolIndex		= (PoolIndex + I) % PoolSize;
		ACsSound* Sound = Pool[PoolIndex];

		if (!Sound->Cache.IsAllocated)
		{
			Sound->Cache.IsAllocated = true;

#if WITH_EDITOR
			OnAllocate_ScriptEvent.Broadcast(PoolIndex);
#endif // #if WITH_EDITOR
			OnAllocate_Event.Broadcast(PoolIndex);
			return Sound;
		}
	}
	checkf(0, TEXT("ACsManager_Sound::Allocate: Pool is exhausted"));
	return nullptr;
}

void ACsManager_Sound::DeAllocate(const int32 &Index)
{
	const uint8 Count = ActiveSounds.Num();

	for (int32 I = Count - 1; I >= 0; I--)
	{
		ACsSound* Sound = ActiveSounds[I];

		if (Sound->PoolIndex == Index)
		{
			LogTransaction(TEXT("ACsManager_Sound::DeAllocate"), ECsPoolTransaction::Deallocate, Sound);

			Sound->DeAllocate();
			ActiveSounds.RemoveAt(I);

#if WITH_EDITOR
			OnDeAllocate_ScriptEvent.Broadcast(Index);
#endif // #if WITH_EDITOR
			OnDeAllocate_Event.Broadcast(Index);
			return;
		}
	}
}

ACsSound* ACsManager_Sound::Play(FCsSoundElement* InSound, UObject* InOwner, UObject* InParent)
{
	checkf(InSound->Get(), TEXT("ACsManager_Sound::Play: Attemping to Play a NULL Sound."));

	ACsSound* Sound	= Allocate();

	const int32 Count = ActiveSounds.Num();

	Sound->Allocate((uint16)Count, InSound, GetWorld()->GetTimeSeconds(), GetWorld()->GetRealTimeSeconds(), 0, InOwner, InParent);

	LogTransaction(TEXT("ACsManager_Sound::Play"), ECsPoolTransaction::Allocate, Sound);

	if (Count >= CS_MAX_CONCURRENT_SOUNDS)
	{
		UE_LOG(LogCs, Warning, TEXT("ACsManager_Sound::Play: Warning more than %d Sounds playing at once."), CS_MAX_CONCURRENT_SOUNDS);
		UE_LOG(LogCs, Warning, TEXT("ACsManager_Sound::Play: Remove Sound."));

		ActiveSounds.RemoveAt(0);
	}
	else
	{
		ActiveSounds.Add(Sound);
	}
	Sound->Play();
	return Sound;
}

ACsSound* ACsManager_Sound::Play(FCsSoundElement* InSound, UObject* InOwner)
{
	return Play(InSound, InOwner, nullptr);
}

ACsSound* ACsManager_Sound::Play(FCsSoundElement* InSound)
{
	return Play(InSound, nullptr, nullptr);
}

ACsSound* ACsManager_Sound::Play(FCsSoundElement* InSound, UObject* InOwner, const FVector &Location)
{
	ACsSound* Sound	= Allocate();

	const int32 Count = ActiveSounds.Num();

	Sound->Allocate((uint16)Count, InSound, GetWorld()->GetTimeSeconds(), GetWorld()->GetRealTimeSeconds(), 0, InOwner, nullptr, Location);

	LogTransaction(TEXT("ACsManager_Sound::Play"), ECsPoolTransaction::Allocate, Sound);

	if (Count >= CS_MAX_CONCURRENT_SOUNDS)
	{
		UE_LOG(LogCs, Warning, TEXT("ACsManager_Sound::Play: Warning more than %d Sounds playing at once"), CS_MAX_CONCURRENT_SOUNDS);
		UE_LOG(LogCs, Warning, TEXT("ACsManager_Sound::Play: Remove Sound"));

		ActiveSounds.RemoveAt(0);
	}
	else
	{
		ActiveSounds.Add(Sound);
	}
	Sound->Play();
	return Sound;
}

template<typename T>
void ACsManager_Sound::Play(ACsSound* OutSound, FCsSoundElement* InSound, UObject* InOwner, UObject* InParent, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&))
{
	OutSound = Allocate();

	const int32 Count = ActiveSounds.Num();

	OutSound->Allocate<T>((uint16)Count, InSound, GetWorld()->GetTimeSeconds(), GetWorld()->GetRealTimeSeconds(), 0, InOwner, InParent, InObject, OnDeAllocate);

	LogTransaction(TEXT("ACsManager_Sound::Play"), ECsPoolTransaction::Allocate, Sound);

	if (Count >= CS_MAX_CONCURRENT_SOUNDS)
	{
		UE_LOG(LogCs, Warning, TEXT("ACsManager_Sound::Play: Warning more than %d Sounds playing at once"), CS_MAX_CONCURRENT_SOUNDS);
		UE_LOG(LogCs, Warning, TEXT("ACsManager_Sound::Play: Remove Sound"));

		ActiveSounds.RemoveAt(0);
	}
	else
	{
		ActiveSounds.Add(OutSound);
	}
	OutSound->Play();
}

template<typename T>
void ACsManager_Sound::Play(ACsSound* OutSound, FCsSoundElement* InSound, UObject* InOwner, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&))
{
	Play(OutSound, InSound, nullptr, InOwner, InObject, OnDeAllocate);
}

template<typename T>
void ACsManager_Sound::Play(ACsSound* OutSound, FCsSoundElement* InSound, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&))
{
	Play(OutSound, InSound, nullptr, nullptr, InObject, OnDeAllocate);
}

template<typename T>
void ACsManager_Sound::Play(ACsSound* OutSound, FCsSoundElement* InSound, UObject* InOwner, const FVector &Location, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&))
{
	OutSound = Allocate();

	const int32 Count = ActiveSounds.Num();

	OutSound->Allocate<T>((uint16)Count, InSound, GetWorld()->GetTimeSeconds(), GetWorld()->GetRealTimeSeconds(), 0, InOwner, Location, InObject, OnDeAllocate);

	LogTransaction(TEXT("ACsManager_Sound::Play"), ECsPoolTransaction::Allocate, Sound);

	if (Count >= CS_MAX_CONCURRENT_SOUNDS)
	{
		UE_LOG(LogCs, Warning, TEXT("ACsManager_Sound::Play: Warning more than %d Sounds playing at once"), CS_MAX_CONCURRENT_SOUNDS);
		UE_LOG(LogCs, Warning, TEXT("ACsManager_Sound::Play: Remove Sound"));

		ActiveSounds.RemoveAt(0);
	}
	else
	{
		ActiveSounds.Add(OutSound);
	}
	OutSound->Play();
}

ACsSound* ACsManager_Sound::Play_Script(FCsSoundElement &InSound, UObject* InOwner, UObject* InParent)
{
	return Play(&InSound, InOwner, InParent);
}

ACsSound* ACsManager_Sound::Play_ScriptEX(FCsSoundElement &InSound, UObject* InOwner, const FVector &Location)
{
	return Play(&InSound, InOwner, Location);
}
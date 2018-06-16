// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Sound/CsManager_Sound.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Common/CsCommon.h"

#include "Managers/Sound/CsSound.h"

#include "Game/CsGameState.h"
#include "Animation/CsAnimInstance.h"

// static initializations
TWeakObjectPtr<UObject> AICsManager_Sound::MyOwner;

// Internal
#pragma region

FCsManager_Sound::~FCsManager_Sound() {}

	// Interface
#pragma region

void FCsManager_Sound::DeconstructObject(ACsSound* a)
{
	if (a && !a->IsPendingKill())
		a->Destroy(true);
}

FString FCsManager_Sound::GetObjectName(ACsSound* a)
{
	return a->GetName();
}

void FCsManager_Sound::Log_Internal(const FString& log)
{
	UE_LOG(LogCs, Warning, TEXT("%s"), *log);
}

ACsSound* FCsManager_Sound::Spawn(FCsSoundPayload* payload)
{
	ACsSound* o = Allocate();

	o->Allocate(GetActivePoolSize(), payload);

	LogTransaction(FunctionNames[ECsManagerPooledObjectsFunctionNames::Spawn], ECsPoolTransaction::Allocate, o);
	payload->Reset();

	if (GetActivePoolSize() >= CS_MAX_CONCURRENT_SOUNDS)
	{
		UE_LOG(LogCs, Warning, TEXT("ACsManager_Sound::Play: Warning more than %d Sounds playing at once"), CS_MAX_CONCURRENT_SOUNDS);
		UE_LOG(LogCs, Warning, TEXT("ACsManager_Sound::Play: Remove Sound"));

		ActiveObjects.RemoveAt(0);
	}
	else
	{
		ActiveObjects.Add(o);
	}
	AddToActivePool(o);
	return o;
}

#pragma endregion Interface

void FCsManager_Sound::Stop(FCsSoundElement* InSound, UObject* InOwner, UObject* InParent)
{
	if (!InSound->Get())
	{
		UE_LOG(LogCs, Warning, TEXT("CsManager_Sound::Stop: Attemping to Stop a NULL Sound."));
		return;
	}

#if WITH_EDITOR
	// For Play in Preview
	if (InOwner)
	{
		if (UWorld* CurrentWorld = InOwner->GetWorld())
		{
			if (UCsCommon::IsPlayInEditorPreview(CurrentWorld) || UCsCommon::IsPlayInEditor(CurrentWorld))
				return;
		}
	}
#endif // #if WITH_EDITOR

	const int32 Count   = ActiveObjects.Num();

	if (Count == CS_EMPTY)
		return;

	int32 EarliestIndex = Count;

	for (int32 I = Count - 1; I >= 0; --I)
	{
		ACsSound* Sound = ActiveObjects[I];

		if (InSound->Get() != Sound->Cache.GetCue())
			continue;
		if (InOwner != Sound->Cache.GetOwner())
			continue;
		if (InParent != Sound->Cache.GetParent())
			continue;

		if (I < EarliestIndex)
			EarliestIndex = I;

		LogTransaction(TEXT("CsManager_Sound::Stop"), ECsPoolTransaction::Deallocate, Sound);

		Sound->DeAllocate();
		ActiveObjects.RemoveAt(I);

/*
#if WITH_EDITOR
		OnDeAllocate_ScriptEvent.Broadcast(I);
#endif // #if WITH_EDITOR
		OnDeAllocate_Event.Broadcast(I);
		*/
	}

	if (EarliestIndex != Count)
	{
		for (int32 I = EarliestIndex; I < Count; ++I)
		{
			ACsSound* Sound = ActiveObjects[I];
			// Reset ActiveIndex
			Sound->Cache.SetActiveIndex(I);
		}
	}
}

#pragma endregion // Internal

AICsManager_Sound::AICsManager_Sound(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Internal = new FCsManager_Sound();
	Internal->Init(TEXT("CsManager_Sound"), TEXT("ACsSound"), nullptr, &CsCVarLogManagerSoundTransactions);
	Internal->ConstructObject_Call.Unbind();
	Internal->ConstructObject_Call.BindUObject(this, &AICsManager_Sound::ConstructObject);
}

/*static*/ UObject* AICsManager_Sound::GetMyOwner() { return MyOwner.IsValid() ? MyOwner.Get() : nullptr; }

/*static*/ void AICsManager_Sound::Init(UObject* InOwner)
{
	MyOwner = InOwner;
}

/*static*/ AICsManager_Sound* AICsManager_Sound::Get(UWorld* InWorld)
{
#if WITH_EDITOR 
	// In Editor Preview Window
	if (UCsCommon::IsPlayInEditorPreview(InWorld))
	{
		if (UCsAnimInstance* AnimInstance = Cast<UCsAnimInstance>(GetMyOwner()))
			return AnimInstance->GetManager_Sound();
	}
	// In Game
	else
#endif // #if WITH_EDITOR
	{
		return Cast<ACsGameState>(GetMyOwner())->Manager_Sound;
	}
	return nullptr;
}

void AICsManager_Sound::Clear()
{
	Internal->Clear();
}

void AICsManager_Sound::Shutdown()
{
	Clear();
	Internal->Shutdown();
	delete Internal;
}

void AICsManager_Sound::Destroyed()
{
	Shutdown();

	Super::Destroyed();
}

ACsSound* AICsManager_Sound::ConstructObject()
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnInfo.ObjectFlags |= RF_Transient;

	ACsSound* Actor = GetWorld()->SpawnActor<ACsSound>(ACsSound::StaticClass(), SpawnInfo);
	Actor->SetReplicates(false);
	Actor->Role = ROLE_None;
	GetWorld()->RemoveNetworkActor(Actor);
	return Actor;
}

void AICsManager_Sound::CreatePool(const int32 &Size)
{
	Internal->CreatePool(Size);
}

void AICsManager_Sound::AddToPool(ACsSound* Actor)
{
	Internal->AddToPool(Actor);
}

void AICsManager_Sound::AddToActivePool(ACsSound* Actor)
{
	Internal->AddToActivePool(Actor);
}

void AICsManager_Sound::OnTick(const float &DeltaTime)
{
	Internal->OnTick(DeltaTime);
}

const TArray<ACsSound*>& AICsManager_Sound::GetAllActiveActors()
{
	return Internal->GetAllActiveObjects();
}

const TArray<ACsSound*>& AICsManager_Sound::GetActors()
{
	return Internal->GetObjects();
}

int32 AICsManager_Sound::GetActivePoolSize()
{
	return Internal->GetActivePoolSize();
}

bool AICsManager_Sound::IsExhausted()
{
	return Internal->IsExhausted();
}

bool AICsManager_Sound::DeAllocate(const int32 &Index)
{
	return Internal->DeAllocate(Index);
}

void AICsManager_Sound::DeAllocateAll()
{
	return Internal->DeAllocateAll();
}

FCsSoundPayload* AICsManager_Sound::AllocatePayload()
{
	return Internal->AllocatePayload();
}

ACsSound* AICsManager_Sound::Play(FCsSoundPayload &Payload)
{
	return Internal->Spawn(&Payload);
}

ACsSound* AICsManager_Sound::Play(FCsSoundPayload *Payload)
{
	return Internal->Spawn(Payload);
}

// Stop
#pragma region

void AICsManager_Sound::Stop(FCsSoundElement* InSound, UObject* InOwner, UObject* InParent)
{
	Internal->Stop(InSound, InOwner, InParent);
}

#pragma endregion Stop

/*
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

UE_LOG(LogCs, Warning, TEXT("%s: %s Sound: %s with Cue: %s at %f at %s."), *FunctionName, *TransactionAsString, *SoundName, *CueName, CurrentTime, *LocationAsString);
}
else
{
UE_LOG(LogCs, Warning, TEXT("%s: %s Sound: %s with Cue: %s at %f."), *FunctionName, *TransactionAsString, *SoundName, *CueName, CurrentTime);
}
}
}
}
*/
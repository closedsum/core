// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/InteractiveActor/CsDamageableActor.h"
#include "CsCore.h"
#include "CsCVars.h"

#include "Coroutine/CsCoroutineScheduler.h"

// Data
#include "Data/CsData_Damageable.h"

// Cache
#pragma region

namespace NCsDamageableActorCached
{
	namespace Str
	{
		const FString Respawn_Internal = TEXT("ACsDamageableActor::Respawn_Internal");
	}

	namespace Name
	{
		const FName Respawn_Internal = FName("ACsDamageableActor::Respawn_Internal");
	}
}

#pragma endregion Cache

// Enums
#pragma region

	// DamageableActorRoutine
CS_DEFINE_ENUM_MAP_BODY(EMCsDamageableActorRoutine)

namespace NCsDamageableActorRoutine
{
	namespace Ref
	{
		CSCORE_API const Type Respawn_Internal = EMCsDamageableActorRoutine::Get().Add(Type::Respawn_Internal, TEXT("Respawn_Internal"));
		CSCORE_API const Type ECsDamageableActorRoutine_MAX = EMCsDamageableActorRoutine::Get().Add(Type::ECsDamageableActorRoutine_MAX, TEXT("ECsDamageableActorRoutine_MAX"), TEXT("MAX"));
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsDamageableActorRoutine_MAX;
}

#pragma endregion Enums

ACsDamageableActor::ACsDamageableActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Warning_FellOutOfWorld	   = TEXT("ACsDamageableActor::FellOutOfWorld");
	Warning_OutsideWorldBounds = TEXT("ACsDamageableActor::OutsideWorldBounds");
}

// Routines
#pragma region

bool ACsDamageableActor::AddRoutine_Internal(struct FCsRoutine* Routine, const uint8& InType)
{
	if (Super::AddRoutine_Internal(Routine, InType))
		return true;

	const ECsDamageableActorRoutine& RoutineType = EMCsDamageableActorRoutine::Get()[InType];

	// Respawn_Internal
	if (RoutineType == ECsDamageableActorRoutine::Respawn_Internal)
	{
		Respawn_Internal_Routine = Routine;
		return true;
	}
	checkf(0, TEXT("ACsDamageableActor::AddRoutine_Internal: Adding a Routine of unknown Type"));
	return false;
}

bool ACsDamageableActor::RemoveRoutine_Internal(struct FCsRoutine* Routine, const uint8& InType)
{
	if (Super::RemoveRoutine_Internal(Routine, InType))
		return true;

	const ECsDamageableActorRoutine& RoutineType = EMCsDamageableActorRoutine::Get()[InType];

	// Respawn_Internal
	if (RoutineType == ECsDamageableActorRoutine::Respawn_Internal)
	{
		check(Respawn_Internal_Routine == Routine);
		Respawn_Internal_Routine = nullptr;
		return true;
	}
	checkf(0, TEXT("ACsDamageableActor::AddRoutine_Internal: Removing a Routine of unknown Type"));
	return false;
}

void ACsDamageableActor::ClearRoutines()
{
	Super::ClearRoutines();
}

#pragma endregion Routines

void ACsDamageableActor::Despawn()
{
	Hide();

#if WITH_EDITOR
	OnDespawn_ScriptEvent.Broadcast(Cache.Index);
#endif // #if WITH_EDITOR
	OnDespawn_Event.Broadcast(Cache.Index);
}

void ACsDamageableActor::Respawn()
{
#if WITH_EDITOR 
	if (Override_Respawn_ScriptEvent.IsBound())
	{
		if (CsCVarLogOverrideFunctions->GetInt() == CS_CVAR_DISPLAY)
		{
			UE_LOG(LogCs, Warning, TEXT("ACsDamageableActor::Respawn (%s): Using Override Function."), *GetName());
		}
		Override_Respawn_ScriptEvent.Broadcast(Cache.Index);
		return;
	}
#endif // #if WITH_EDITOR

	if (Respawn_Internal_Routine && Respawn_Internal_Routine->IsValid())
		Respawn_Internal_Routine->End(ECsCoroutineEndReason::UniqueInstance);

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();
	FCsCoroutinePayload* Payload	 = Scheduler->AllocatePayload();

	const ECsCoroutineSchedule& Schedule = NCsCoroutineSchedule::Ref::Tick;

	Payload->Schedule		= Schedule;
	Payload->Function		= &ACsDamageableActor::Respawn_Internal;
	Payload->Actor			= this;
	//Payload->Stop			= &ACsWeapon::FireWeapon_StopCondition;
	Payload->Add			= &ACsDamageableActor::AddRoutine;
	Payload->Remove			= &ACsDamageableActor::RemoveRoutine;
	Payload->Type			= (uint8)ECsDamageableActorRoutine::Respawn_Internal;
	Payload->bDoInit		= true;
	Payload->bPerformFirstRun = false;
	Payload->Name			= NCsDamageableActorCached::Name::Respawn_Internal;
	Payload->NameAsString	= NCsDamageableActorCached::Str::Respawn_Internal;

	FCsRoutine* R = Scheduler->Allocate(Payload);

	Scheduler->StartRoutine(Schedule, R);
}

PT_THREAD(ACsDamageableActor::Respawn_Internal(struct FCsRoutine* r))
{
	ACsDamageableActor* d	 = Cast<ACsDamageableActor>(r->GetActor());
	UCsCoroutineScheduler* s = UCsCoroutineScheduler::Get();
	UWorld* w			     = d->GetWorld();

	ACsData_Damageable* data = Cast<ACsData_Damageable>(d->Cache.GetData());

	const float CurrentTime = w->GetTimeSeconds();
	const float StartTime   = r->startTime;

	CS_COROUTINE_BEGIN(r);

	CS_COROUTINE_WAIT_UNTIL(r, CurrentTime - r->startTime >= d->RespawnTime);

	d->Health = data->GetHealth();

	d->Show();

#if WITH_EDITOR
	d->OnRespawn_ScriptEvent.Broadcast(d->Cache.Index);
#endif // #if WITH_EDITOR
	d->OnRespawn_Event.Broadcast(d->Cache.Index);

	CS_COROUTINE_END(r);
}

void ACsDamageableActor::ApplyDamage(FCsDamageEvent* Event)
{
	Health -= FMath::CeilToInt(Event->Damage);

	if (Health <= 0)
	{
		// DeAllocate
		if (RespawnTime <= 0.0f)
		{
			Cache.bLifeTime = true;
			Cache.LifeTime	= 0.0f;
		}
		// Setup Respawn
		else
		{
			Despawn();
			Respawn();
		}
	}
}
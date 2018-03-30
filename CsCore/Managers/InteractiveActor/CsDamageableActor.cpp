// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/InteractiveActor/CsDamageableActor.h"
#include "CsCore.h"
#include "CsCVars.h"

#include "Coroutine/CsCoroutineScheduler.h"

// Data
#include "Data/CsData_Damageable.h"

// Cache
#pragma region

namespace ECsDamageableActorCachedString
{
	namespace Str
	{
		const FString Respawn_Internal = TEXT("ACsDamageableActor::Respawn_Internal");
	}
}

namespace ECsDamageableActorCachedName
{
	namespace Name
	{
		const FName Respawn_Internal = FName("ACsDamageableActor::Respawn_Internal");
	}
}

#pragma endregion Cache

// Enums
#pragma region

UENUM(BlueprintType)
namespace ECsDamageableActorRoutine
{
	enum Type
	{
		Respawn_Internal				UMETA(DisplayName = "Respawn_Internal"),
		ECsDamageableActorRoutine_MAX	UMETA(Hidden),
	};
}

namespace ECsDamageableActorRoutine
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString Respawn_Internal = TCsString(TEXT("Respawn_Internal"), TEXT("respawn_internal"), TEXT("respawn internal"));
	}

	inline FString ToString(const Type &EType)
	{
		if (EType == Type::Respawn_Internal) { return Str::Respawn_Internal.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	inline Type ToType(const FString &String)
	{
		if (String == Str::Respawn_Internal) { return Type::Respawn_Internal; }
		return Type::ECsDamageableActorRoutine_MAX;
	}
}

#define ECS_DAMAGEABLE_ACTOR_ROUTINE_MAX (uint8)ECsDamageableActorRoutine::ECsDamageableActorRoutine_MAX
typedef ECsDamageableActorRoutine::Type TCsDamageableActorRoutine;

#pragma endregion Enums

ACsDamageableActor::ACsDamageableActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Warning_FellOutOfWorld	   = TEXT("ACsDamageableActor::FellOutOfWorld");
	Warning_OutsideWorldBounds = TEXT("ACsDamageableActor::OutsideWorldBounds");
}

// Routines
#pragma region

bool ACsDamageableActor::AddRoutine_Internal(struct FCsRoutine* Routine, const uint8 &InType)
{
	if (Super::AddRoutine_Internal(Routine, InType))
		return true;

	const TCsDamageableActorRoutine RoutineType = (TCsDamageableActorRoutine)InType;

	// Respawn_Internal
	if (RoutineType == ECsDamageableActorRoutine::Respawn_Internal)
	{
		Respawn_Internal_Routine = Routine;
		return true;
	}
	checkf(0, TEXT("ACsDamageableActor::AddRoutine_Internal: Adding a Routine of unknown Type"));
	return false;
}

bool ACsDamageableActor::RemoveRoutine_Internal(struct FCsRoutine* Routine, const uint8 &InType)
{
	if (Super::RemoveRoutine_Internal(Routine, InType))
		return true;

	const TCsDamageableActorRoutine RoutineType = (TCsDamageableActorRoutine)InType;

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

	const TCsCoroutineSchedule Schedule = ECsCoroutineSchedule::Tick;

	Payload->Schedule		= Schedule;
	Payload->Function		= &ACsDamageableActor::Respawn_Internal;
	Payload->Actor			= this;
	//Payload->Stop			= &ACsWeapon::FireWeapon_StopCondition;
	Payload->Add			= &ACsDamageableActor::AddRoutine;
	Payload->Remove			= &ACsDamageableActor::RemoveRoutine;
	Payload->Type			= (uint8)ECsDamageableActorRoutine::Respawn_Internal;
	Payload->DoInit			= true;
	Payload->PerformFirstRun = false;
	Payload->Name			= ECsDamageableActorCachedName::Name::Respawn_Internal;
	Payload->NameAsString	= ECsDamageableActorCachedString::Str::Respawn_Internal;

	FCsRoutine* R = Scheduler->Allocate(Payload);

	Scheduler->StartRoutine(Schedule, R);
}

PT_THREAD(ACsDamageableActor::Respawn_Internal(struct FCsRoutine* r))
{
	ACsDamageableActor* d	 = Cast<ACsDamageableActor>(r->GetActor());
	UCsCoroutineScheduler* s = r->scheduler;
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
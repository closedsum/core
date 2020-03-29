// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/InteractiveActor/CsDamageableActor.h"
#include "CsCoreDEPRECATED.h"
#include "CsCVars.h"

// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Data
#include "Data/CsData_Damageable.h"
// Managers
#include "Managers/Time/CsManager_Time.h"

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
namespace NCsDamageableActorRoutine
{
	namespace Ref
	{
		CSCOREDEPRECATED_API const Type Respawn_Internal = EMCsDamageableActorRoutine::Get().Add(Type::Respawn_Internal, TEXT("Respawn_Internal"));
		CSCOREDEPRECATED_API const Type ECsDamageableActorRoutine_MAX = EMCsDamageableActorRoutine::Get().Add(Type::ECsDamageableActorRoutine_MAX, TEXT("ECsDamageableActorRoutine_MAX"), TEXT("MAX"));
	}

	CSCOREDEPRECATED_API const uint8 MAX = (uint8)Type::ECsDamageableActorRoutine_MAX;
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

	if (Respawn_Internal_Routine)
		Respawn_Internal_Routine->End(ECsCoroutineEndReason::UniqueInstance);

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get(GetGameInstance());

	const FECsUpdateGroup Group = NCsUpdateGroup::GameState;

	FCsResource_CoroutinePayload* PayloadContainer = Scheduler->AllocatePayload(Group);
	FCsCoroutinePayload* Payload				   = PayloadContainer->Get();

	Payload->Coroutine.BindStatic(&ACsDamageableActor::Respawn_Internal);
	Payload->StartTime = UCsManager_Time::Get(GetGameInstance())->GetTime(Group);
	Payload->Owner.SetObject(this);

	Payload->SetName(NCsDamageableActorCached::Name::Respawn_Internal);
	Payload->SetNameAsString(NCsDamageableActorCached::Str::Respawn_Internal);

	Scheduler->Start(Payload);
}

PT_THREAD(ACsDamageableActor::Respawn_Internal(FCsRoutine* R))
{
	ACsDamageableActor* D = R->GetOwnerAsObject<ACsDamageableActor>();

	UCsData_Damageable* Data = Cast<UCsData_Damageable>(D->Cache.GetData());

	const FCsTime& CurrentTime = UCsManager_Time::Get(D->GetGameInstance())->GetTime(R->Group);
	const FCsTime& StartTime   = R->StartTime;

	CS_COROUTINE_BEGIN(R);

	CS_COROUTINE_WAIT_UNTIL(R, CurrentTime.Time - StartTime.Time >= D->RespawnTime);

	D->Health = Data->GetHealth();

	D->Show();

#if WITH_EDITOR
	D->OnRespawn_ScriptEvent.Broadcast(D->Cache.Index);
#endif // #if WITH_EDITOR
	D->OnRespawn_Event.Broadcast(D->Cache.Index);

	CS_COROUTINE_END(R);
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
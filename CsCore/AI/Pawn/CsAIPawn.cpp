// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "AI/Pawn/CsAIPawn.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Coroutine/CsCoroutineScheduler.h"

#include "AI/CsAIController.h"
#include "AI/CsAIPlayerState.h"

// Data
#include "Data/CsData_Character.h"
// Managers
#include "Managers/Trace/CsManager_Trace.h"
// Game
#include "Game/CsGameState.h"
// Player
#include "AI/CsAIPlayerState.h"
#include "Player/CsPlayerPawn.h"
// Weapon
#include "Weapon/CsWeapon.h"
// UI
//#include "Components/CsWidgetComponent.h"
//#include "UI/Simple/CsWidget_ProgressBar.h"

// Enums
#pragma region

namespace ECsPawnRoutine
{
	CSCORE_API const FECsPawnRoutine StartShootForCount_Internal = EMCsPawnRoutine::Get().Create(TEXT("StartShootForCount_Internal"));
	CSCORE_API const FECsPawnRoutine StartShootForDuration_Internal = EMCsPawnRoutine::Get().Create(TEXT("StartShootForDuration_Internal"));
}

#pragma endregion Enums

// Cache
#pragma region

namespace ECsAIPawnCached
{
	namespace Name
	{
		// Functions
		const FName StartShootForCount_Internal = FName("ACsAIPawn::StartShootForCount_Internal");
		const FName StartShootForDuration_Internal = FName("ACsAIPawn::StartShootForDuration_Internal");
	}

	namespace Str
	{
		// Functions
		const FString StartShootForCount_Internal = TEXT("ACsAIPawn::StartShootForCount_Internal");
		const FString StartShootForDuration_Internal = TEXT("ACsAIPawn::StartShootForDuration_Internal");
	}
}

#pragma endregion Cache

ACsAIPawn::ACsAIPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bUseControllerRotationYaw = true;

	AutoPossessPlayer = EAutoReceiveInput::Disabled;
	AutoPossessAI	  = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ACsAIController::StaticClass();

	// Behavior Tree

		// Shoot
	StartShootEvent = EMCsGameEvent::Get().GetMAX();
	StopShootEvent = EMCsGameEvent::Get().GetMAX();
}

void ACsAIPawn::Init(const int32 &Index, const FECsAIType &InType)
{
	PoolIndex	= Index;
	Type		= InType;

	Cache.Set(Index, this);
}

void ACsAIPawn::OnCreatePool()
{
	SetActorHiddenInGame(true);
}

void ACsAIPawn::OnPostCreatePool(){}

void ACsAIPawn::Allocate(const int32 &ActiveIndex, FCsAIPawnPayload* Payload)
{
	Cache.Init(ActiveIndex, Payload, GetWorld()->GetTimeSeconds(), GetWorld()->GetRealTimeSeconds(), UCsCommon::GetCurrentFrame(GetWorld()));

	Allocate_Internal(Payload);
}

void ACsAIPawn::Allocate_Internal(FCsAIPawnPayload* Payload)
{
	if (Payload->TeleportLocation || Payload->TeleportRotation)
	{
		SpawnLocation = Payload->TeleportLocation ? Payload->Location : GetActorLocation();
		SpawnRotation = Payload->TeleportRotation ? Payload->Rotation : GetActorRotation();

		TeleportTo(SpawnLocation, SpawnRotation, false, false);
	}
	SetActorHiddenInGame(false);
}

void ACsAIPawn::DeAllocate()
{
	Cache.Reset();

	SetActorHiddenInGame(true);
}

void ACsAIPawn::OnTick_HandleCVars(const float &DeltaSeconds){}

// State
#pragma region

void ACsAIPawn::OnChange_Health(const float &Value)
{
	ACsAIPlayerState* MyPlayerState = Cast<ACsAIPlayerState>(PlayerState);

	OnChange_Health_Event.Broadcast(MyPlayerState->UniqueMappingId, Health, MaxHealth);
#if WITH_EDITOR
	OnChange_Health_ScriptEvent.Broadcast(MyPlayerState->UniqueMappingId, Health, MaxHealth);
#endif // #if WITH_EDITOR
}

#pragma endregion State

// Routines
#pragma region

bool ACsAIPawn::AddRoutine_Internal(FCsRoutine* Routine, const uint8 &InType)
{
	if (Super::AddRoutine_Internal(Routine, InType))
		return true;

	const FECsPawnRoutine& RoutineType = EMCsPawnRoutine::Get()[InType];

	// StartShootForCount_Internal
	if (RoutineType == ECsPawnRoutine::StartShootForCount_Internal)
	{
		CheckLinkedToPlayerState_Internal_Routine = Routine;
		return true;
	}
	// StartShootForDuration_Internal
	if (RoutineType == ECsPawnRoutine::StartShootForDuration_Internal)
	{
		HandleRespawnTimer_Internal_Routine = Routine;
		return true;
	}
	return false;
}

bool ACsAIPawn::RemoveRoutine_Internal(FCsRoutine* Routine, const uint8 &InType)
{
	if (Super::RemoveRoutine_Internal(Routine, InType))
		return true;

	const FECsPawnRoutine& RoutineType = EMCsPawnRoutine::Get()[InType];

	// StartShootForCount_Internal
	if (RoutineType == ECsPawnRoutine::StartShootForCount_Internal)
	{
		check(CheckLinkedToPlayerState_Internal_Routine == Routine);
		CheckLinkedToPlayerState_Internal_Routine = nullptr;
		return true;
	}
	// StartShootForDuration_Internal
	if (RoutineType == ECsPawnRoutine::StartShootForDuration_Internal)
	{
		check(HandleRespawnTimer_Internal_Routine == Routine);
		HandleRespawnTimer_Internal_Routine = nullptr;
		return true;
	}
	return false;
}

#pragma endregion Routines

// View
#pragma region

void ACsAIPawn::PerformViewTrace_Response(const uint8 &RequestId, FCsTraceResponse* Response)
{
	Super::PerformViewTrace_Response(RequestId, Response);
	
	if (CsCVarDrawAIViewTraceHitLocation->GetInt() == CS_CVAR_DRAW)
	{
		DrawDebugSphere(GetWorld(), ViewTraceInfo.HitLocation, 32.0f, 16, FColor::Green, false, GetWorld()->GetDeltaSeconds() + 0.0005f, 0, 1.0f);
	}
}

#pragma endregion View

// Behavior Tree
#pragma region

void ACsAIPawn::SetTargetActor(AActor* Target)
{
	MyTargetActor = Target;
}

void ACsAIPawn::SetTargetLocation(const FVector &Target)
{
	MyTargetLocation = Target;
}

	// LookAt
#pragma region

FRotator ACsAIPawn::GetFinalLookAtRotation(AActor* Target, const FName &Bone) { return FRotator(CurrentAimPitch, CurrentAimYaw, 0.0f); }
FRotator ACsAIPawn::GetFinalLookAtRotation(const FVector &Target){ return FRotator(CurrentAimPitch, CurrentAimYaw, 0.0f); }
void ACsAIPawn::LookAtLocation(const FVector &Target, const float &LookRate, const float &LookTime){}
void ACsAIPawn::LookAtActor(AActor* Target, const FName &Bone, const float &LookRate, const float &LookTime){}
void ACsAIPawn::StopLookAt(const float &BlendOutRate){}

#pragma endregion LookAt

	// AimAt
#pragma region

void ACsAIPawn::ResetAimAt(const float &BlendOutTime){}

void ACsAIPawn::AimAtLocation(const FVector &Target){}
void ACsAIPawn::AimAtActor(AActor* Target, const FName &Bone){}
void ACsAIPawn::StopAimAt(){}

#pragma endregion AimAt

	// Shoot
#pragma region

void ACsAIPawn::StartShoot()
{
	ACsAIPlayerState* MyPlayerState = Cast<ACsAIPlayerState>(PlayerState);
	MyPlayerState->QueuedGameEventsForNextFrame.Add(StartShootEvent);
}

void ACsAIPawn::StartShootForCount(const int32 &Count)
{
	// Clear StartShootForCount
	if (StartShootForCount_Internal_Routine && StartShootForCount_Internal_Routine->IsValid())
		StartShootForCount_Internal_Routine->End(ECsCoroutineEndReason::Manual);
	// Clear StartShootForDuration
	if (StartShootForDuration_Internal_Routine && StartShootForDuration_Internal_Routine->IsValid())
		StartShootForDuration_Internal_Routine->End(ECsCoroutineEndReason::UniqueInstance);

	ACsAIPlayerState* MyPlayerState = Cast<ACsAIPlayerState>(PlayerState);
	MyPlayerState->QueuedGameEventsForNextFrame.Add(StartShootEvent);

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();
	FCsCoroutinePayload* Payload = Scheduler->AllocatePayload();

	const TCsCoroutineSchedule Schedule = ECsCoroutineSchedule::Tick;

	Payload->Schedule		= Schedule;
	Payload->Function		= &ACsAIPawn::StartShootForCount_Internal;
	Payload->Actor			= this;
	Payload->Stop			= &UCsCommon::CoroutineStopCondition_CheckActor;
	Payload->Add			= &ACsAIPawn::AddRoutine;
	Payload->Remove			= &ACsAIPawn::RemoveRoutine;
	Payload->Type			= ECsPawnRoutine::StartShootForCount_Internal.Value;
	Payload->DoInit			= true;
	Payload->PerformFirstRun = false;
	Payload->Name			= ECsAIPawnCached::Name::StartShootForCount_Internal;
	Payload->NameAsString	= ECsAIPawnCached::Str::StartShootForCount_Internal;

	FCsRoutine* R = Scheduler->Allocate(Payload);

	ACsWeapon* CurrentWeapon = GetCurrentWeapon();

	R->counters[0] = Count;
	R->counters[1] = CurrentWeapon->FireCount;

	Scheduler->StartRoutine(Schedule, R);
}

CS_COROUTINE(ACsAIPawn, StartShootForCount_Internal)
{
	ACsAIPawn* p			 = r->GetActor<ACsAIPawn>();
	UCsCoroutineScheduler* s = UCsCoroutineScheduler::Get();

	const int32& Count		= r->counters[0];
	const int32& StartCount = r->counters[1];

	ACsWeapon* CurrentWeapon = p->GetCurrentWeapon();

	CS_COROUTINE_BEGIN(r);

	CS_COROUTINE_WAIT_UNTIL(r, CurrentWeapon->FireCount - StartCount >= Count);

	p->StopShoot();

	CS_COROUTINE_END(r);
}

void ACsAIPawn::StartShootForDuration(const float &Duration)
{
	// Clear StartShootForDuration
	if (StartShootForDuration_Internal_Routine && StartShootForDuration_Internal_Routine->IsValid())
		StartShootForDuration_Internal_Routine->End(ECsCoroutineEndReason::Manual);
	// Clear StartShootForCount
	if (StartShootForCount_Internal_Routine && StartShootForCount_Internal_Routine->IsValid())
		StartShootForCount_Internal_Routine->End(ECsCoroutineEndReason::UniqueInstance);

	ACsAIPlayerState* MyPlayerState = Cast<ACsAIPlayerState>(PlayerState);
	MyPlayerState->QueuedGameEventsForNextFrame.Add(StartShootEvent);

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();
	FCsCoroutinePayload* Payload	 = Scheduler->AllocatePayload();

	const TCsCoroutineSchedule Schedule = ECsCoroutineSchedule::Tick;

	Payload->Schedule		= Schedule;
	Payload->Function		= &ACsAIPawn::StartShootForDuration_Internal;
	Payload->Actor			= this;
	Payload->Stop			= &UCsCommon::CoroutineStopCondition_CheckActor;
	Payload->Add			= &ACsAIPawn::AddRoutine;
	Payload->Remove			= &ACsAIPawn::RemoveRoutine;
	Payload->Type			= ECsPawnRoutine::StartShootForDuration_Internal.Value;
	Payload->DoInit			= true;
	Payload->PerformFirstRun = false;
	Payload->Name			= ECsAIPawnCached::Name::StartShootForDuration_Internal;
	Payload->NameAsString	= ECsAIPawnCached::Str::StartShootForDuration_Internal;

	FCsRoutine* R = Scheduler->Allocate(Payload);

	R->floats[0] = Duration;

	Scheduler->StartRoutine(Schedule, R);
}

CS_COROUTINE(ACsAIPawn, StartShootForDuration_Internal)
{
	ACsAIPawn* p			 = r->GetActor<ACsAIPawn>();
	UCsCoroutineScheduler* s = UCsCoroutineScheduler::Get();

	const float& Duration	 = r->floats[0];
	const float& ElapsedTime = r->elapsedTime;

	CS_COROUTINE_BEGIN(r);

	CS_COROUTINE_WAIT_UNTIL(r, ElapsedTime >= Duration);

	p->StopShoot();

	CS_COROUTINE_END(r);
}

void ACsAIPawn::StopShoot()
{
	// Clear StartShootForCount
	if (StartShootForCount_Internal_Routine && StartShootForCount_Internal_Routine->IsValid())
		StartShootForCount_Internal_Routine->End(ECsCoroutineEndReason::Manual);
	// Clear StartShootForDuration
	if (StartShootForDuration_Internal_Routine && StartShootForDuration_Internal_Routine->IsValid())
		StartShootForDuration_Internal_Routine->End(ECsCoroutineEndReason::Manual);

	ACsAIPlayerState* MyPlayerState = Cast<ACsAIPlayerState>(PlayerState);
	MyPlayerState->QueuedGameEventsForNextFrame.Add(StopShootEvent);
}

bool ACsAIPawn::IsShooting()
{
	ACsWeapon* CurrentWeapon = GetCurrentWeapon();

	const int32& Count = EMCsWeaponFireMode::Get().Num();

	for (int32 I = 0; I < Count; ++I)
	{
		const FECsWeaponFireMode& FireMode = EMCsWeaponFireMode::Get().GetEnumAt(I);

		if (CurrentWeapon->IsFirePressed[FireMode])
			return true;
	}
	return false;
}

#pragma endregion Shoot

#pragma endregion Behavior Tree
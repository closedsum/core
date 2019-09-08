// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
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
	CSCORE_API const FECsPawnRoutine SyncCurrentViewFromBone_Internal = EMCsPawnRoutine::Get().Create(TEXT("SyncCurrentViewFromBone_Internal"));
}

#pragma endregion Enums

// Cache
#pragma region

namespace NCsAIPawnCached
{
	namespace Name
	{
		// Functions
		const FName StartShootForCount_Internal = FName("ACsAIPawn::StartShootForCount_Internal");
		const FName StartShootForDuration_Internal = FName("ACsAIPawn::StartShootForDuration_Internal");
		const FName SyncCurrentViewFromBone_Internal = FName("ACsAIPawn::SyncCurrentViewFromBone_Internal");
	}

	namespace Str
	{
		// Functions
		const FString StartShootForCount_Internal = TEXT("ACsAIPawn::StartShootForCount_Internal");
		const FString StartShootForDuration_Internal = TEXT("ACsAIPawn::StartShootForDuration_Internal");
		const FString SyncCurrentViewFromBone_Internal = TEXT("ACsAIPawn::SyncCurrentViewFromBone_Internal");
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

		// Jump
	StartJumpEventInfo.Clear();
		// Shoot
	StartShootEvent = EMCsGameEvent::Get().GetMAX();
	StopShootEvent = EMCsGameEvent::Get().GetMAX();
}

void ACsAIPawn::Init(const int32 &Index, const FECsAIType &InType)
{
	Cache.Set(Index, this, InType);

	if (bPlacedInWorld)
	{
		SpawnLocation = GetActorLocation();
		SpawnRotation = GetActorRotation();
	}
}

void ACsAIPawn::OnCreatePool()
{
	SetActorHiddenInGame(true);
}

void ACsAIPawn::OnPostCreatePool(){}

void ACsAIPawn::Allocate(FCsAIPawnPayload* Payload)
{
	Cache.Init(Payload, GetWorld()->GetTimeSeconds(), GetWorld()->GetRealTimeSeconds(), UCsCommon::GetCurrentFrame(GetWorld()));

	Allocate_Internal(Payload);
}

void ACsAIPawn::Allocate_Internal(FCsAIPawnPayload* Payload)
{
	if (Payload->bLocation || Payload->bRotation)
	{
		SpawnLocation = Payload->bLocation ? Payload->Location : GetActorLocation();
		SpawnRotation = Payload->bRotation ? Payload->Rotation : GetActorRotation();

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
	ACsAIPlayerState* MyPlayerState = GetPlayerState<ACsAIPlayerState>();

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
	// SyncCurrentViewFromBone_Internal
	if (RoutineType == ECsPawnRoutine::SyncCurrentViewFromBone_Internal)
	{
		SyncCurrentViewFromBone_Internal_Routine = Routine;
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
	// SyncCurrentViewFromBone_Internal
	if (RoutineType == ECsPawnRoutine::SyncCurrentViewFromBone_Internal)
	{
		check(SyncCurrentViewFromBone_Internal_Routine == Routine);
		SyncCurrentViewFromBone_Internal_Routine = nullptr;
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

void ACsAIPawn::SyncCurrentViewFromBone(const FName &Bone)
{
	// Clear SyncCurrentViewFromBone
	if (SyncCurrentViewFromBone_Internal_Routine && SyncCurrentViewFromBone_Internal_Routine->IsValid())
		SyncCurrentViewFromBone_Internal_Routine->End(ECsCoroutineEndReason::UniqueInstance);

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();
	FCsCoroutinePayload* Payload	 = Scheduler->AllocatePayload();

	const ECsCoroutineSchedule& Schedule = NCsCoroutineSchedule::Ref::Tick;

	Payload->Schedule		= Schedule;
	Payload->Function		= &ACsAIPawn::SyncCurrentViewFromBone_Internal;
	Payload->Actor			= this;
	Payload->Stop.Add(&UCsCommon::CoroutineStopCondition_CheckActor);
	Payload->Add			= &ACsAIPawn::AddRoutine;
	Payload->Remove			= &ACsAIPawn::RemoveRoutine;
	Payload->Type			= ECsPawnRoutine::SyncCurrentViewFromBone_Internal.Value;
	Payload->bDoInit		= true;
	Payload->bPerformFirstRun = false;
	Payload->Name			= NCsAIPawnCached::Name::SyncCurrentViewFromBone_Internal;
	Payload->NameAsString	= NCsAIPawnCached::Str::SyncCurrentViewFromBone_Internal;

	FCsRoutine* R = Scheduler->Allocate(Payload);

	R->names[0] = Bone;

	bSyncCurrentViewFromBone = true;

	Scheduler->StartRoutine(Schedule, R);
}

CS_COROUTINE(ACsAIPawn, SyncCurrentViewFromBone_Internal)
{
	ACsAIPawn* p			 = r->GetActor<ACsAIPawn>();
	UCsCoroutineScheduler* s = UCsCoroutineScheduler::Get();

	const FName& Bone		= r->names[0];
	const FRotator Rotation	= p->GetMesh()->GetBoneQuaternion(Bone).Rotator();

	p->CurrentAimPitch	= Rotation.Pitch;
	p->CurrentAimYaw	= Rotation.Yaw;

	CS_COROUTINE_BEGIN(r);

	/** Waittill StopSyncCurrentViewFromBone is called. Forever. */
	CS_COROUTINE_WAIT_UNTIL(r, false);

	CS_COROUTINE_END(r);
}

void ACsAIPawn::StopSyncCurrentViewFromBone()
{
	// Clear SyncCurrentViewFromBone
	if (SyncCurrentViewFromBone_Internal_Routine && SyncCurrentViewFromBone_Internal_Routine->IsValid())
		SyncCurrentViewFromBone_Internal_Routine->End(ECsCoroutineEndReason::Manual);

	bSyncCurrentViewFromBone = false;
}

#pragma endregion View

// Behavior Tree
#pragma region

	// Jump
#pragma region

void ACsAIPawn::SetStartJumpEventInfoConstrainedByTime(const FVector &Direction, const float &Distance)
{
	StartJumpEventInfo.Direction = Direction == FVector::ZeroVector ? CurrentRootDirXY : Direction;

	ACsData_Character* Data = GetMyData_Character();
	const float Time		= 2.0f * Data->GetGroundToJumpPeakTime();
	StartJumpEventInfo.Time = Time;
	const float SpeedXY		= Distance / Time;

	StartJumpEventInfo.JumpZVelocity	= Data->GetJumpZVelocity();
	StartJumpEventInfo.Height			= Data->GetGroundToJumpPeakTime() * StartJumpEventInfo.JumpZVelocity;
	StartJumpEventInfo.SpeedXYAsPercent = SpeedXY / Data->GetMaxWalkSpeed();
}

void ACsAIPawn::SetStartJumpEventInfoConstrainedBySpeedXY(const FVector &Direction, const float &Distance)
{
	StartJumpEventInfo.Direction = Direction == FVector::ZeroVector ? CurrentRootDirXY : Direction;

	ACsData_Character* Data = GetMyData_Character();
	const float& SpeedXY    = Data->GetMaxWalkSpeed();
	const float Time		= Distance / SpeedXY;
	StartJumpEventInfo.Time = Time;

	// V0 = -a*t;
	const float& GravityScale			= Data->GetGravityScale();
	StartJumpEventInfo.JumpZVelocity	= GravityScale * 980.0f * Time * 0.5f;
	StartJumpEventInfo.Height			= 0.5f * Time * StartJumpEventInfo.JumpZVelocity;
	StartJumpEventInfo.SpeedXYAsPercent = 1.0f;
}

void ACsAIPawn::SetStartJumpEventInfo(const FVector &Direction, const float &SpeedXYAsPercent /*=1.0f*/)
{
	StartJumpEventInfo.Direction = Direction == FVector::ZeroVector ? CurrentRootDirXY : Direction;

	ACsData_Character* Data				= GetMyData_Character();
	const float Time					= 2.0f * Data->GetGroundToJumpPeakTime();
	StartJumpEventInfo.Time				= Time;
	StartJumpEventInfo.Height			= Data->GetJumpHeight();
	StartJumpEventInfo.JumpZVelocity	= Data->GetJumpZVelocity();
	StartJumpEventInfo.SpeedXYAsPercent = SpeedXYAsPercent;
}

void ACsAIPawn::SetStartJumpEventInfoByTime(const FVector &Direction, const float &Time, const float &SpeedXYAsPercent /*=1.0f*/)
{
	StartJumpEventInfo.Direction = Direction == FVector::ZeroVector ? CurrentRootDirXY : Direction;

	ACsData_Character* Data			 = GetMyData_Character();
	const float& GravityScale		 = Data->GetGravityScale();
	// V0 = -a*t;
	StartJumpEventInfo.JumpZVelocity = GravityScale * 980.0f * Time * 0.5f;

	StartJumpEventInfo.Time				= Time;
	StartJumpEventInfo.Height			= 0.5f * Time * StartJumpEventInfo.JumpZVelocity;
	StartJumpEventInfo.SpeedXYAsPercent = SpeedXYAsPercent;
}

void ACsAIPawn::SetStartJumpEventInfoByHeight(const FVector &Direction, const float &Height, const float &SpeedXYAsPercent /*=1.0f*/)
{
	StartJumpEventInfo.Direction = Direction == FVector::ZeroVector ? CurrentRootDirXY : Direction;

	ACsData_Character* Data		= GetMyData_Character();
	const float& GravityScale	= Data->GetGravityScale();
	// V0 = Sqrt(2*a*s);
	StartJumpEventInfo.JumpZVelocity = FMath::Sqrt(1960.0f * GravityScale * Height);

	StartJumpEventInfo.Time				= 2.0f * (Height / StartJumpEventInfo.JumpZVelocity);
	StartJumpEventInfo.Height			= Height;
	StartJumpEventInfo.SpeedXYAsPercent = SpeedXYAsPercent;
}

void ACsAIPawn::StartJump()
{
	ACsAIPlayerState* MyPlayerState = GetPlayerState<ACsAIPlayerState>();
	MyPlayerState->AddQueuedGameEvent(StartJumpEventInfo.Event);

	bJumpFinished = false;
}

#pragma endregion Jump

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
void ACsAIPawn::ResetLookAt(const float &BlendOutRate){}
void ACsAIPawn::StopLookAt(){}

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
	ACsAIPlayerState* MyPlayerState = GetPlayerState<ACsAIPlayerState>();
	MyPlayerState->AddQueuedGameEvent(StartShootEvent);
}

void ACsAIPawn::StartShootForCount(const int32 &Count)
{
	// Clear StartShootForCount
	if (StartShootForCount_Internal_Routine && StartShootForCount_Internal_Routine->IsValid())
		StartShootForCount_Internal_Routine->End(ECsCoroutineEndReason::Manual);
	// Clear StartShootForDuration
	if (StartShootForDuration_Internal_Routine && StartShootForDuration_Internal_Routine->IsValid())
		StartShootForDuration_Internal_Routine->End(ECsCoroutineEndReason::UniqueInstance);

	ACsAIPlayerState* MyPlayerState = GetPlayerState<ACsAIPlayerState>();
	MyPlayerState->AddQueuedGameEvent(StartShootEvent);

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();
	FCsCoroutinePayload* Payload = Scheduler->AllocatePayload();

	const ECsCoroutineSchedule& Schedule = NCsCoroutineSchedule::Ref::Tick;

	Payload->Schedule		= Schedule;
	Payload->Function		= &ACsAIPawn::StartShootForCount_Internal;
	Payload->Actor			= this;
	Payload->Stop.Add(&UCsCommon::CoroutineStopCondition_CheckActor);
	Payload->Add			= &ACsAIPawn::AddRoutine;
	Payload->Remove			= &ACsAIPawn::RemoveRoutine;
	Payload->Type			= ECsPawnRoutine::StartShootForCount_Internal.Value;
	Payload->bDoInit		= true;
	Payload->bPerformFirstRun = false;
	Payload->Name			= NCsAIPawnCached::Name::StartShootForCount_Internal;
	Payload->NameAsString	= NCsAIPawnCached::Str::StartShootForCount_Internal;

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

	ACsAIPlayerState* MyPlayerState = GetPlayerState<ACsAIPlayerState>();
	MyPlayerState->AddQueuedGameEvent(StartShootEvent);

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();
	FCsCoroutinePayload* Payload	 = Scheduler->AllocatePayload();

	const ECsCoroutineSchedule& Schedule = NCsCoroutineSchedule::Ref::Tick;

	Payload->Schedule		= Schedule;
	Payload->Function		= &ACsAIPawn::StartShootForDuration_Internal;
	Payload->Actor			= this;
	Payload->Stop.Add(&UCsCommon::CoroutineStopCondition_CheckActor);
	Payload->Add			= &ACsAIPawn::AddRoutine;
	Payload->Remove			= &ACsAIPawn::RemoveRoutine;
	Payload->Type			= ECsPawnRoutine::StartShootForDuration_Internal.Value;
	Payload->bDoInit		= true;
	Payload->bPerformFirstRun = false;
	Payload->Name			= NCsAIPawnCached::Name::StartShootForDuration_Internal;
	Payload->NameAsString	= NCsAIPawnCached::Str::StartShootForDuration_Internal;

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

	ACsAIPlayerState* MyPlayerState = GetPlayerState<ACsAIPlayerState>();
	MyPlayerState->AddQueuedGameEvent(StopShootEvent);
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
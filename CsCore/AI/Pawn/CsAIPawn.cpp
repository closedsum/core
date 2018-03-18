// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "AI/Pawn/CsAIPawn.h"
#include "CsCore.h"
#include "Coroutine/CsCoroutineScheduler.h"

#include "AI/CsAIController.h"
#include "AI/CsAIPlayerState.h"

// Data
#include "Data/CsData_Character.h"

// Cache
#pragma region

namespace ECsAIPawnCachedName
{
	namespace Name
	{
		// Functions
		const FName HandleRespawnTimer_Internal = FName("ACsAIPawn::HandleRespawnTimer_Internal");
	};
}

namespace ECsAIPawnCachedString
{
	namespace Str
	{
		// Functions
		const FString HandleRespawnTimer_Internal = TEXT("ACsAIPawn::HandleRespawnTimer_Internal");
	};
}

#pragma endregion Cache

ACsAIPawn::ACsAIPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bUseControllerRotationYaw = true;

	AutoPossessPlayer = EAutoReceiveInput::Disabled;
	AutoPossessAI	  = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ACsAIController::StaticClass();

	OnHandleRespawnTimerFinished_Event.AddUObject(this, &ACsAIPawn::OnHandleRespawnTimerFinished);
}


void ACsAIPawn::Init(const int32 &Index, const TCsAIType &InType)
{
	PoolIndex	= Index;
	Type		= InType;
	Type_Script = (uint8)Type;

	Cache.Set(Index, this);
}

void ACsAIPawn::OnCreatePool()
{
	SetActorHiddenInGame(true);
}

void ACsAIPawn::OnPostCreatePool(){}

template<typename T>
void ACsAIPawn::Allocate(const uint16 &ActiveIndex, FCsAIPawnPayload* Payload, const float &Time, const float &RealTime, const uint64 &Frame, UObject* InOwner, UObject* InParent, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&))
{
	Cache.Init<T>(ActiveIndex, Time, RealTime, Frame, InOwner, InParent, InObject, OnDeAllocate);

	Allocate_Internal(Payload);
}

template<typename T>
void ACsAIPawn::Allocate(const uint16 &ActiveIndex, FCsAIPawnPayload* Payload, const float &Time, const float &RealTime, const uint64 &Frame, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&))
{
	Allocate<T>(ActiveIndex, Payload, Time, RealTime, Frame, nullptr, nullptr, InObject, OnDeAllocate);
}

void ACsAIPawn::Allocate(const uint16 &ActiveIndex, FCsAIPawnPayload* Payload, const float &Time, const float &RealTime, const uint64 &Frame, UObject* InOwner, UObject* InParent)
{
	Cache.Init(ActiveIndex, Time, RealTime, Frame, InOwner, InParent);

	Allocate_Internal(Payload);
}

void ACsAIPawn::Allocate(const uint16 &ActiveIndex, FCsAIPawnPayload* Payload, const float &Time, const float &RealTime, const uint64 &Frame)
{
	Allocate(ActiveIndex, Payload, Time, RealTime, Frame, nullptr, nullptr);
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

void ACsAIPawn::HandleRespawnTimer()
{
	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();
	FCsCoroutinePayload* Payload	 = Scheduler->AllocatePayload();

	const TCsCoroutineSchedule Schedule = ECsCoroutineSchedule::Tick;

	Payload->Schedule		= Schedule;
	Payload->Function		= &ACsAIPawn::HandleRespawnTimer_Internal;
	Payload->Actor			= this;
	Payload->Stop			= &UCsCommon::CoroutineStopCondition_CheckActor;
	Payload->Add			= &ACsPawn::AddRoutine;
	Payload->Remove			= &ACsPawn::RemoveRoutine;
	Payload->Type			= (uint8)ECsAIPawnRoutine::HandleRespawnTimer_Internal;
	Payload->DoInit			= true;
	Payload->PerformFirstRun = false;
	Payload->Name			= ECsAIPawnCachedName::Name::HandleRespawnTimer_Internal;
	Payload->NameAsString	= ECsAIPawnCachedString::Str::HandleRespawnTimer_Internal;

	FCsRoutine* R = Scheduler->Allocate(Payload);

	Scheduler->StartRoutine(Schedule, R);
}

CS_COROUTINE(ACsAIPawn, HandleRespawnTimer_Internal)
{
	ACsAIPawn* p			 = r->GetActor<ACsAIPawn>();
	UCsCoroutineScheduler* s = r->scheduler;
	UWorld* w				 = p->GetWorld();
	ACsAIPlayerState* ps	 = Cast<ACsAIPlayerState>(p->PlayerState);

	ACsData_Character* Data_Character = p->GetMyData_Character();

	const float CurrentTime = w->GetTimeSeconds();
	const float& StartTime  = r->startTime;
	const float RespawnTime = Data_Character->GetRespawnTime();

	CS_COROUTINE_BEGIN(r);

	CS_COROUTINE_WAIT_UNTIL(r, CurrentTime - StartTime >= RespawnTime);

	p->OnHandleRespawnTimerFinished_Event.Broadcast(ps->UniqueMappingId);

	CS_COROUTINE_END(r);
}

void ACsAIPawn::OnHandleRespawnTimerFinished(const uint8 &MappingId){}

#pragma endregion State

// Routines
#pragma region

bool ACsAIPawn::AddRoutine_Internal(struct FCsRoutine* Routine, const uint8 &Type)
{
	if (Super::AddRoutine_Internal(Routine, Type))
		return true;

	const TCsAIPawnRoutine RoutineType = (TCsAIPawnRoutine)Type;

	// HandleRespawnTimer_Internal
	if (RoutineType == ECsAIPawnRoutine::HandleRespawnTimer_Internal)
	{
		HandleRespawnTimer_Internal_Routine = Routine;
		return true;
	}
	return false;
}

bool ACsAIPawn::RemoveRoutine_Internal(struct FCsRoutine* Routine, const uint8 &Type)
{
	if (Super::RemoveRoutine_Internal(Routine, Type))
		return false;

	const TCsAIPawnRoutine RoutineType = (TCsAIPawnRoutine)Type;

	// HandleRespawnTimer_Internal
	if (RoutineType == ECsAIPawnRoutine::HandleRespawnTimer_Internal)
	{
		check(HandleRespawnTimer_Internal_Routine == Routine);
		HandleRespawnTimer_Internal_Routine = nullptr;
		return true;
	}
	return false;
}

#pragma endregion Routines
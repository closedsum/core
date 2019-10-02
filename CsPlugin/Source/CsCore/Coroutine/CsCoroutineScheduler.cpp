// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Coroutine/CsCoroutineScheduler.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Game/CsGameState.h"

// static initializations
UCsCoroutineScheduler* UCsCoroutineScheduler::s_coroutineSchedulerSingleton;
bool UCsCoroutineScheduler::s_bCoroutineSchedulerHasShutdown = false;

// Enums
#pragma region

	// CoroutineTransaction
namespace NCsCoroutineTransaction
{
	namespace Ref
	{
		CSCORE_API const Type Allocate = EMCsCoroutineTransaction::Get().Add(Type::Allocate, TEXT("Allocate"));
		CSCORE_API const Type Start = EMCsCoroutineTransaction::Get().Add(Type::Start, TEXT("Start"));
		CSCORE_API const Type End = EMCsCoroutineTransaction::Get().Add(Type::End, TEXT("End"));
		CSCORE_API const Type ECsCoroutineTransaction_MAX = EMCsCoroutineTransaction::Get().Add(Type::ECsCoroutineTransaction_MAX, TEXT("ECsCoroutineTransaction_MAX"), TEXT("MAX"));
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsCoroutineTransaction_MAX;

	namespace Str
	{
		CSCORE_API const TCsString Allocate = TCsString(TEXT("Allocate"), TEXT("allocate"), TEXT("Allocating"));
		CSCORE_API const TCsString Start = TCsString(TEXT("Start"), TEXT("start"), TEXT("Starting"));
		CSCORE_API const TCsString End = TCsString(TEXT("End"), TEXT("end"), TEXT("Ending"));
	}
}

#pragma endregion Enums

// Cache
#pragma region

namespace NCsCoroutineCached
{
	namespace Str
	{
		const FString Allocate = TEXT("UCsCoroutineScheduler::Allocate");
		const FString Start = TEXT("UCsCoroutineScheduler::Start");
		const FString Update = TEXT("UCsCoroutineScheduler::Update");
		const FString OnTick_Update = TEXT("UCsCoroutineScheduler::OnTick_Update");
		const FString OnCacCamera_Update = TEXT("UCsCoroutineScheduler::OnCacCamera_Update");
		const FString OnLastTick_Update = TEXT("UCsCoroutineScheduler::OnLastTick_Update");
	}
}

#pragma endregion Cache

UCsCoroutineScheduler::UCsCoroutineScheduler(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	for (int32 I = 0; I < ECS_COROUTINE_SCHEDULE_MAX; ++I)
	{
		RoutinePoolIndices.Add(0);
		RoutinesToInit.AddDefaulted();
		RoutinesToRun.AddDefaulted();

		for (int32 J = 0; J < CS_ROUTINE_POOL_SIZE; ++J)
		{
			RoutinePools[I][J].Init((ECsCoroutineSchedule)I, J);
		}
	}
}

/*static*/ UCsCoroutineScheduler* UCsCoroutineScheduler::Get()
{
	if (s_bCoroutineSchedulerHasShutdown)
		return nullptr;

	if (!s_coroutineSchedulerSingleton)
	{
		s_coroutineSchedulerSingleton = NewObject<UCsCoroutineScheduler>(GetTransientPackage(), UCsCoroutineScheduler::StaticClass(), TEXT("Coroutine_Scheduler_Singleton"), RF_Transient | RF_Public);
		s_coroutineSchedulerSingleton->AddToRoot();
		s_coroutineSchedulerSingleton->Initialize();
	}

	return s_coroutineSchedulerSingleton;
}

/*static*/ void UCsCoroutineScheduler::Init()
{
	s_bCoroutineSchedulerHasShutdown = false;
	UCsCoroutineScheduler::Get();
}

/*static*/ void UCsCoroutineScheduler::Shutdown()
{
	if (!s_coroutineSchedulerSingleton)
		return;

	s_coroutineSchedulerSingleton->CleanUp();
	s_coroutineSchedulerSingleton->RemoveFromRoot();
	s_coroutineSchedulerSingleton = nullptr;
	s_bCoroutineSchedulerHasShutdown = true;
}

void UCsCoroutineScheduler::Initialize()
{
	// Register delegate for ticker callback
	TickDelegate	   = FTickerDelegate::CreateUObject(this, &UCsCoroutineScheduler::Tick);
	TickDelegateHandle = FTicker::GetCoreTicker().AddTicker(TickDelegate);
}

void UCsCoroutineScheduler::CleanUp()
{
	// Unregister ticker delegate
	FTicker::GetCoreTicker().RemoveTicker(TickDelegateHandle);
}

bool UCsCoroutineScheduler::Tick(float DeltaSeconds)
{
	return true;
}

UObject* UCsCoroutineScheduler::GetMyOwner()
{
	return MyOwner.IsValid() ? MyOwner.Get() : nullptr;
}

// Allocate
#pragma region

struct FCsRoutine* UCsCoroutineScheduler::Allocate(const ECsCoroutineSchedule& ScheduleType, CsCoroutine InCoroutine, AActor* InActor, const bool& DoInit, const bool& PerformFirstRun)
{
	return Allocate(ScheduleType, InCoroutine, nullptr, InActor, nullptr, nullptr, nullptr, CS_ROUTINE_MAX_TYPE, DoInit, PerformFirstRun);
}

struct FCsRoutine* UCsCoroutineScheduler::Allocate(const ECsCoroutineSchedule& ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, const bool& DoInit, const bool& PerformFirstRun)
{
	return Allocate(ScheduleType, InCoroutine, InStopCondition, InActor, nullptr, nullptr, nullptr, CS_ROUTINE_MAX_TYPE, DoInit, PerformFirstRun);
}

struct FCsRoutine* UCsCoroutineScheduler::Allocate(const ECsCoroutineSchedule& ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, struct FCsRoutine** InOwnerMemberRoutine, const bool& DoInit, const bool& PerformFirstRun)
{
	return Allocate(ScheduleType, InCoroutine, InStopCondition, InActor, nullptr, InOwnerMemberRoutine, DoInit, PerformFirstRun);
}

struct FCsRoutine* UCsCoroutineScheduler::Allocate(const ECsCoroutineSchedule& ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, CsAddRoutine InAddRoutine, CsRemoveRoutine InRemoveRoutine, const uint8& RoutineType, const bool& DoInit, const bool& PerformFirstRun)
{
	return Allocate(ScheduleType, InCoroutine, InStopCondition, InActor, nullptr, InAddRoutine, InRemoveRoutine, RoutineType, DoInit, PerformFirstRun);
}

struct FCsRoutine* UCsCoroutineScheduler::Allocate(const ECsCoroutineSchedule& ScheduleType, CsCoroutine InCoroutine, UObject* InObject, const bool& DoInit, const bool& PerformFirstRun)
{
	return Allocate(ScheduleType, InCoroutine, nullptr, nullptr, InObject, nullptr, nullptr, CS_ROUTINE_MAX_TYPE, DoInit, PerformFirstRun);
}

struct FCsRoutine* UCsCoroutineScheduler::Allocate(const ECsCoroutineSchedule& ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject, const bool& DoInit, const bool& PerformFirstRun)
{
	return Allocate(ScheduleType, InCoroutine, InStopCondition, nullptr, InObject, nullptr, nullptr, CS_ROUTINE_MAX_TYPE, DoInit, PerformFirstRun);
}

struct FCsRoutine* UCsCoroutineScheduler::Allocate(const ECsCoroutineSchedule& ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject, struct FCsRoutine** InOwnerMemberRoutine, const bool& DoInit, const bool& PerformFirstRun)
{
	return Allocate(ScheduleType, InCoroutine, InStopCondition, nullptr, InObject, InOwnerMemberRoutine, DoInit, PerformFirstRun);
}

struct FCsRoutine* UCsCoroutineScheduler::Allocate(const ECsCoroutineSchedule& ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject, CsAddRoutine InAddRoutine, CsRemoveRoutine InRemoveRoutine, const uint8& RoutineType, const bool& DoInit, const bool& PerformFirstRun)
{
	return Allocate(ScheduleType, InCoroutine, InStopCondition, nullptr, InObject, InAddRoutine, InRemoveRoutine, RoutineType, DoInit, PerformFirstRun);
}

struct FCsRoutine* UCsCoroutineScheduler::Allocate(const ECsCoroutineSchedule& ScheduleType, CsCoroutine InCoroutine, AActor* InActor, UObject* InObject, const bool& DoInit, const bool& PerformFirstRun)
{
	return Allocate(ScheduleType, InCoroutine, nullptr, InActor, InObject, nullptr, nullptr, CS_ROUTINE_MAX_TYPE, DoInit, PerformFirstRun);
}

struct FCsRoutine* UCsCoroutineScheduler::Allocate(const ECsCoroutineSchedule& ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject, const bool& DoInit, const bool& PerformFirstRun)
{
	return Allocate(ScheduleType, InCoroutine, nullptr, InActor, InObject, nullptr, nullptr, CS_ROUTINE_MAX_TYPE, DoInit, PerformFirstRun);
}

struct FCsRoutine* UCsCoroutineScheduler::Allocate(const ECsCoroutineSchedule& ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject, struct FCsRoutine** InOwnerMemberRoutine, const bool& DoInit, const bool& PerformFirstRun)
{
	FCsCoroutinePayload* Payload = AllocatePayload();

	Payload->Schedule = ScheduleType;
	Payload->Function = InCoroutine;
	Payload->Stop.Add(InStopCondition);
	Payload->Actor = InActor;
	Payload->Object = InObject;
	Payload->Routine = InOwnerMemberRoutine;
	Payload->bDoInit = DoInit;
	Payload->bPerformFirstRun = PerformFirstRun;

	return Allocate(Payload);
}

struct FCsRoutine* UCsCoroutineScheduler::Allocate(const ECsCoroutineSchedule& ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject, CsAddRoutine InAddRoutine, CsRemoveRoutine InRemoveRoutine, const uint8& RoutineType, const bool& DoInit, const bool& PerformFirstRun)
{
	FCsCoroutinePayload* Payload = AllocatePayload();

	Payload->Schedule = ScheduleType;
	Payload->Function = InCoroutine;
	Payload->Stop.Add(InStopCondition);
	Payload->Actor = InActor;
	Payload->Object = InObject;
	Payload->Add = InAddRoutine;
	Payload->Remove = InRemoveRoutine;
	Payload->Type = RoutineType;
	Payload->bDoInit = DoInit;
	Payload->bPerformFirstRun = PerformFirstRun;

	return Allocate(Payload);
}

struct FCsRoutine* UCsCoroutineScheduler::Allocate(FCsCoroutinePayload* Payload)
{
	const uint8 Schedule = (uint8)Payload->Schedule;

	for (int32 I = 0; I < CS_ROUTINE_POOL_SIZE; ++I)
	{
		RoutinePoolIndices[Schedule] = (RoutinePoolIndices[Schedule] + 1) % CS_ROUTINE_POOL_SIZE;

		FCsRoutine* R = &(RoutinePools[Schedule][RoutinePoolIndices[Schedule]]);

		if (R->index == CS_ROUTINE_FREE)
		{
			R->name			= Payload->Name;
			R->nameAsString = Payload->NameAsString;

			UWorld* World = nullptr;

			if (Payload->Actor)
				World = Payload->Actor->GetWorld();
			if (Payload->Object)
				World = Payload->Object->GetWorld();
			
			const float CurrentTime = World ? World->GetTimeSeconds() : UCsCommon::GetCurrentDateTimeSeconds();

			if (Payload->Routine)
				R->Start(Payload->Function, Payload->Stop, Payload->Actor, Payload->Object, CurrentTime, Payload->Routine);
			else
				R->Start(Payload->Function, Payload->Stop, Payload->Actor, Payload->Object, CurrentTime, Payload->Add, Payload->Remove, Payload->Type);

			if (Payload->bDoInit)
			{
				CS_COROUTINE_INIT(R);
				R->index = RoutinesToRun[Schedule].Num();
				RoutinesToRun[Schedule].Add(R);

				if (Payload->bPerformFirstRun)
				{
					R->Run(0.0f);
				}
			}
			else
			{
				RoutinesToInit[Schedule].Add(R);
			}
			LogTransaction(NCsCoroutineCached::Str::Allocate, (Payload->bDoInit && Payload->bPerformFirstRun) ? ECsCoroutineTransaction::Start : ECsCoroutineTransaction::Allocate, R);
			Payload->Reset();
			return R;
		}
	}
	Payload->Reset();
	UE_LOG(LogCs, Warning, TEXT("UCsCoroutineScheduler::Allocate: No free Routines. Look for Runaway Coroutines or consider raising the pool size."));
	return nullptr;
}

#pragma endregion Allocate

// Start
#pragma region

struct FCsRoutine* UCsCoroutineScheduler::Start(const ECsCoroutineSchedule& ScheduleType, CsCoroutine InCoroutine, AActor* InActor)
{
	return Allocate(ScheduleType, InCoroutine, nullptr, InActor, nullptr, nullptr, nullptr, CS_ROUTINE_MAX_TYPE, true, true);
}

struct FCsRoutine* UCsCoroutineScheduler::Start(const ECsCoroutineSchedule& ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor)
{
	return Allocate(ScheduleType, InCoroutine, InStopCondition, InActor, nullptr, nullptr, nullptr, CS_ROUTINE_MAX_TYPE, true, true);
}

struct FCsRoutine* UCsCoroutineScheduler::Start(const ECsCoroutineSchedule& ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, struct FCsRoutine** InOwnerMemberRoutine)
{
	return Allocate(ScheduleType, InCoroutine, InStopCondition, InActor, nullptr, InOwnerMemberRoutine, true, true);
}

struct FCsRoutine* UCsCoroutineScheduler::Start(const ECsCoroutineSchedule& ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, CsAddRoutine InAddRoutine, CsRemoveRoutine InRemoveRoutine, const uint8& RoutineType)
{
	return Allocate(ScheduleType, InCoroutine, InStopCondition, InActor, nullptr, InAddRoutine, InRemoveRoutine, RoutineType, true, true);
}

struct FCsRoutine* UCsCoroutineScheduler::Start(const ECsCoroutineSchedule& ScheduleType, CsCoroutine InCoroutine, UObject* InObject)
{
	return Allocate(ScheduleType, InCoroutine, nullptr, nullptr, InObject, nullptr, nullptr, CS_ROUTINE_MAX_TYPE, true, true);
}

struct FCsRoutine* UCsCoroutineScheduler::Start(const ECsCoroutineSchedule& ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject)
{
	return Allocate(ScheduleType, InCoroutine, InStopCondition, nullptr, InObject, nullptr, nullptr, CS_ROUTINE_MAX_TYPE, true, true);
}

struct FCsRoutine* UCsCoroutineScheduler::Start(const ECsCoroutineSchedule& ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject, struct FCsRoutine** InOwnerMemberRoutine)
{
	return Allocate(ScheduleType, InCoroutine, InStopCondition, nullptr, InObject, InOwnerMemberRoutine, true, true);
}

struct FCsRoutine* UCsCoroutineScheduler::Start(const ECsCoroutineSchedule& ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject, CsAddRoutine InAddRoutine, CsRemoveRoutine InRemoveRoutine, const uint8& RoutineType)
{
	return Allocate(ScheduleType, InCoroutine, InStopCondition, nullptr, InObject, InAddRoutine, InRemoveRoutine, RoutineType, true, true);
}

struct FCsRoutine* UCsCoroutineScheduler::Start(const ECsCoroutineSchedule& ScheduleType, CsCoroutine InCoroutine, AActor* InActor, UObject* InObject)
{
	return Allocate(ScheduleType, InCoroutine, nullptr, InActor, InObject, nullptr, nullptr, CS_ROUTINE_MAX_TYPE, true, true);
}

struct FCsRoutine* UCsCoroutineScheduler::Start(const ECsCoroutineSchedule& ScheduleType, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject)
{
	return Allocate(ScheduleType, InCoroutine, InStopCondition, InActor, InObject, nullptr, nullptr, CS_ROUTINE_MAX_TYPE, true, true);
}

struct FCsRoutine* UCsCoroutineScheduler::Start(FCsCoroutinePayload* Payload)
{
	return Allocate(Payload);
}

#pragma endregion // Start

// StartChild
#pragma region

struct FCsRoutine* UCsCoroutineScheduler::StartChild(const ECsCoroutineSchedule& ScheduleType, struct FCsRoutine* Parent, CsCoroutine InCoroutine, AActor* InActor)
{
	return StartChild(ScheduleType, Parent, InCoroutine, nullptr, InActor, nullptr, nullptr, nullptr, CS_ROUTINE_MAX_TYPE);
}

struct FCsRoutine* UCsCoroutineScheduler::StartChild(const ECsCoroutineSchedule& ScheduleType, struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor)
{
	return StartChild(ScheduleType, Parent, InCoroutine, InStopCondition, InActor, nullptr, nullptr, nullptr, CS_ROUTINE_MAX_TYPE);
}

struct FCsRoutine* UCsCoroutineScheduler::StartChild(const ECsCoroutineSchedule& ScheduleType, struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, struct FCsRoutine** InOwnerMemberRoutine)
{
	return StartChild(ScheduleType, Parent, InCoroutine, InStopCondition, InActor, nullptr, InOwnerMemberRoutine);
}

struct FCsRoutine* UCsCoroutineScheduler::StartChild(const ECsCoroutineSchedule& ScheduleType, struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, CsAddRoutine InAddRoutine, CsRemoveRoutine InRemoveRoutine, const uint8& RoutineType)
{
	return StartChild(ScheduleType, Parent, InCoroutine, InStopCondition, InActor, nullptr, InAddRoutine, InRemoveRoutine, RoutineType);
}

struct FCsRoutine* UCsCoroutineScheduler::StartChild(const ECsCoroutineSchedule& ScheduleType, struct FCsRoutine* Parent, CsCoroutine InCoroutine, UObject* InObject)
{
	return StartChild(ScheduleType, Parent, InCoroutine, nullptr, nullptr, InObject, nullptr, nullptr, CS_ROUTINE_MAX_TYPE);
}

struct FCsRoutine* UCsCoroutineScheduler::StartChild(const ECsCoroutineSchedule& ScheduleType, struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject)
{
	return StartChild(ScheduleType, Parent, InCoroutine, InStopCondition, nullptr, InObject, nullptr, nullptr, CS_ROUTINE_MAX_TYPE);
}

struct FCsRoutine* UCsCoroutineScheduler::StartChild(const ECsCoroutineSchedule& ScheduleType, struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject, struct FCsRoutine** InOwnerMemberRoutine)
{
	return StartChild(ScheduleType, Parent, InCoroutine, InStopCondition, nullptr, InObject, InOwnerMemberRoutine);
}

struct FCsRoutine* UCsCoroutineScheduler::StartChild(const ECsCoroutineSchedule& ScheduleType, struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, UObject* InObject, CsAddRoutine InAddRoutine, CsRemoveRoutine InRemoveRoutine, const uint8& RoutineType)
{
	return StartChild(ScheduleType, Parent, InCoroutine, InStopCondition, nullptr, InObject, InAddRoutine, InRemoveRoutine, RoutineType);
}

struct FCsRoutine* UCsCoroutineScheduler::StartChild(const ECsCoroutineSchedule& ScheduleType, struct FCsRoutine* Parent, CsCoroutine InCoroutine, AActor* InActor, UObject* InObject)
{
	return StartChild(ScheduleType, Parent, InCoroutine, nullptr, InActor, InObject, nullptr, nullptr, CS_ROUTINE_MAX_TYPE);
}

struct FCsRoutine* UCsCoroutineScheduler::StartChild(const ECsCoroutineSchedule& ScheduleType, struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject)
{
	return StartChild(ScheduleType, Parent, InCoroutine, InStopCondition, InActor, InObject, nullptr, nullptr, CS_ROUTINE_MAX_TYPE);
}

struct FCsRoutine* UCsCoroutineScheduler::StartChild(const ECsCoroutineSchedule& ScheduleType, struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject, struct FCsRoutine** InOwnerMemberRoutine)
{
	FCsCoroutinePayload* Payload = AllocatePayload();

	Payload->Schedule = ScheduleType;
	Payload->Parent = Parent;
	Payload->Function = InCoroutine;
	Payload->Stop.Add(InStopCondition);
	Payload->Actor = InActor;
	Payload->Object = InObject;
	Payload->Routine = InOwnerMemberRoutine;

	return StartChild(Payload);
}

struct FCsRoutine* UCsCoroutineScheduler::StartChild(const ECsCoroutineSchedule& ScheduleType, struct FCsRoutine* Parent, CsCoroutine InCoroutine, CsCoroutineStopCondition InStopCondition, AActor* InActor, UObject* InObject, CsAddRoutine InAddRoutine, CsRemoveRoutine InRemoveRoutine, const uint8& RoutineType)
{
	FCsCoroutinePayload* Payload = AllocatePayload();

	Payload->Schedule = ScheduleType;
	Payload->Parent = Parent;
	Payload->Function = InCoroutine;
	Payload->Stop.Add(InStopCondition);
	Payload->Actor = InActor;
	Payload->Object = InObject;
	Payload->Add = InAddRoutine;
	Payload->Remove = InRemoveRoutine;
	Payload->Type = RoutineType;

	return StartChild(Payload);
}

struct FCsRoutine* UCsCoroutineScheduler::StartChild(FCsCoroutinePayload* Payload)
{
	const uint8 Schedule = (uint8)Payload->Schedule;

	for (int32 I = 0; I < CS_ROUTINE_POOL_SIZE; ++I)
	{
		RoutinePoolIndices[Schedule] = (RoutinePoolIndices[Schedule] + 1) % CS_ROUTINE_POOL_SIZE;

		FCsRoutine* R = &(RoutinePools[Schedule][RoutinePoolIndices[Schedule]]);

		if (R->index == CS_ROUTINE_FREE)
		{
			R->name			= Payload->Name;
			R->nameAsString = Payload->NameAsString;

			UWorld* World = nullptr;

			if (Payload->Actor)
				World = Payload->Actor->GetWorld();
			if (Payload->Object)
				World = Payload->Object->GetWorld();

			const float CurrentTime = World ? World->GetTimeSeconds() : UCsCommon::GetCurrentDateTimeSeconds();

			FCsRoutine* Parent = Payload->Parent;

			Parent->AddChild(R);

			if (Payload->Routine)
				R->Start(Payload->Function, Payload->Stop, Payload->Actor, Payload->Object, CurrentTime, Payload->Routine);
			else
				R->Start(Payload->Function, Payload->Stop, Payload->Actor, Payload->Object, CurrentTime, Payload->Add, Payload->Remove, Payload->Type);

			CS_COROUTINE_INIT(R);

			bool InsertedAtLastChild = Parent->children.Num() > 0 && Parent->children.Last() && Parent->children.Last() != R;
			FCsRoutine* Element		 = InsertedAtLastChild ? Parent->children.Last() : Parent;
			R->index				 = RoutinesToRun[Schedule].Find(Element);
			RoutinesToRun[Schedule].Insert(R, R->index);

			const int32 ParentIndex = Parent->index;

			for (int32 J = R->index + 1; J <= ParentIndex; ++J)
			{
				R->index++;
			}

			R->Run(0.0f);
			Payload->Reset();
			return R;
		}
	}
	Payload->Reset();
	UE_LOG(LogCs, Warning, TEXT("UCsCoroutineScheduler::StartChild: No free Routines. Look for Runaway Coroutines or consider raising the pool size."));
	return nullptr;
}

#pragma endregion // StartChild

struct FCsRoutine* UCsCoroutineScheduler::StartRoutine(const ECsCoroutineSchedule& ScheduleType, struct FCsRoutine* R)
{
	const uint8 Schedule = (uint8)ScheduleType;

	// TODO: This should never happen. If it does, need to trace how and fix it.
	// HACK: Index should never be greater than the RoutinesToRun Count.
	if (R->index < 0 ||
		R->index >= RoutinesToRun[Schedule].Num())
	{
		FString State = R->index == CS_ROUTINE_END ? TEXT("END") : TEXT("FREE");

		UE_LOG(LogCs, Warning, TEXT("UCsCoroutineScheduler::StartRoutine: Attempting to start a Routine marked %s"), *State);

		// Check if the Routine is in the list of RoutinesToExecute
		const int32 Count = RoutinesToRun[Schedule].Num();

		for (int32 Index = Count - 1; Index >= 0; Index--)
		{
			if (R == RoutinesToRun[Schedule][Index])
			{
				RoutinesToRun[Schedule].RemoveAt(Index);

				UE_LOG(LogCs, Warning, TEXT("UCsCoroutineScheduler::StartRoutine: Removing Routine marked %s at index %d in RoutinesToExecute"), *State, Index);
				break;
			}
		}
		check(0);
		R->Reset();
		return R;
	}
	RoutinesToRun[Schedule][R->index]->Run(0.0f);
	return R;
}

void UCsCoroutineScheduler::EndAll(const ECsCoroutineSchedule& ScheduleType /*= ECsCoroutineSchedule::ECsCoroutineSchedule_MAX*/)
{
	const uint8 Start = ScheduleType == ECsCoroutineSchedule::ECsCoroutineSchedule_MAX ? 0 : (uint8)ScheduleType;
	const uint8 End   = ScheduleType == ECsCoroutineSchedule::ECsCoroutineSchedule_MAX ? ECS_COROUTINE_SCHEDULE_MAX : Start + 1;

	for (int32 I = Start; I < End; ++I)
	{
		int32 Count = RoutinesToInit[I].Num();

		for (int32 Index = 0; Index < Count; ++Index)
		{
			FCsRoutine* R = RoutinesToInit[I][Index];

			R->End(ECsCoroutineEndReason::Shutdown);
			R->Reset();
		}

		RoutinesToInit[I].Reset();

		Count = RoutinesToRun[I].Num();

		for (int32 Index = 0; Index < Count; ++Index)
		{
			FCsRoutine* R = RoutinesToRun[I][Index];

			R->End(ECsCoroutineEndReason::Shutdown);
			R->Reset();
		}
		RoutinesToRun[I].Reset();
	}
}

void UCsCoroutineScheduler::BroadcastMessage(const ECsCoroutineSchedule& ScheduleType, const ECsCoroutineMessage& MessageType, const FName& Message, UObject* InOwner)
{
	const uint8 Schedule = (uint8)ScheduleType;

	int32 Count = RoutinesToInit[Schedule].Num();

	for (int32 I = 0; I < Count; ++I)
	{
		if (InOwner && InOwner != RoutinesToInit[Schedule][I]->GetOwner())
			continue;

		if (MessageType == ECsCoroutineMessage::Stop)
			RoutinesToInit[Schedule][I]->ReceiveMessage(MessageType, Message);
	}

	Count = RoutinesToRun[Schedule].Num();

	for (int32 I = 0; I < Count; ++I)
	{
		if (InOwner && InOwner != RoutinesToRun[Schedule][I]->GetOwner())
			continue;

		if (MessageType == ECsCoroutineMessage::Stop)
			RoutinesToRun[Schedule][I]->ReceiveMessage(MessageType, Message);
	}
}

void UCsCoroutineScheduler::BroadcastMessage(const ECsCoroutineSchedule& ScheduleType, const ECsCoroutineMessage& MessageType, const FName& Message)
{
	BroadcastMessage(ScheduleType, MessageType, Message, nullptr);
}

void UCsCoroutineScheduler::Update(const ECsCoroutineSchedule& ScheduleType, const float& DeltaSeconds)
{
	const uint8 Schedule = (uint8)ScheduleType;

	// Init
	int32 Count = RoutinesToInit[Schedule].Num();

	for (int32 Index = 0; Index < Count; ++Index)
	{
		FCsRoutine* R = RoutinesToInit[Schedule][Index];

		CS_COROUTINE_INIT(R);
		R->index = RoutinesToRun[Schedule].Num();
		RoutinesToRun[Schedule].Add(R);
	}

	RoutinesToInit[Schedule].Reset();

	// Remove any Routines executed previous to tick
	Count = RoutinesToRun[Schedule].Num();

	for (int32 Index = Count - 1; Index >= 0; --Index)
	{
		FCsRoutine* R = RoutinesToRun[Schedule][Index];

		if (R->index == CS_ROUTINE_END)
		{
			LogTransaction(NCsCoroutineCached::ToUpdate(ScheduleType), ECsCoroutineTransaction::End, R);

			R->Reset();
			RoutinesToRun[Schedule].RemoveAt(Index);
		}
	}
	// Execute
	LogRunning(ScheduleType);

	Count = RoutinesToRun[Schedule].Num();

	for (int32 Index = 0; Index < Count; ++Index)
	{
		RoutinesToRun[Schedule][Index]->Run(DeltaSeconds);
	}
	// Remove any Routines executed end of tick
	for (int32 Index = Count - 1; Index >= 0; --Index)
	{
		FCsRoutine* R = RoutinesToRun[Schedule][Index];

		if (R->index == CS_ROUTINE_END)
		{
			LogTransaction(NCsCoroutineCached::ToUpdate(ScheduleType), ECsCoroutineTransaction::End, R);

			R->Reset();
			RoutinesToRun[Schedule].RemoveAt(Index);
		}
	}
}

// Run on Tick
#pragma region 

void UCsCoroutineScheduler::OnTick_Update(const float& DeltaSeconds)
{
	Update(ECsCoroutineSchedule::Tick, DeltaSeconds);
	OnTickUpdate_Event.Broadcast(DeltaSeconds);
}

#pragma endregion Run on Tick

// Run on CalcCamera
#pragma region

void UCsCoroutineScheduler::OnCalcCamera_Update(const float& DeltaSeconds)
{
	Update(ECsCoroutineSchedule::CalcCamera, DeltaSeconds);
}

#pragma endregion Run on CalcCamera

// Run on LastTick
#pragma region

void UCsCoroutineScheduler::OnLastTick_Update(const float& DeltaSeconds)
{
	Update(ECsCoroutineSchedule::LastTick, DeltaSeconds);
}

#pragma endregion Run on LastTick

void UCsCoroutineScheduler::LogTransaction(const FString& FunctionName, const ECsCoroutineTransaction& Transaction, FCsRoutine* R)
{
	if (CsCVarLogCoroutineTransactions->GetInt() == CS_CVAR_SHOW_LOG)
	{
		FString TransactionAsString = NCsCoroutineTransaction::ToActionString(Transaction);
			
		if (Transaction == ECsCoroutineTransaction::End)
			TransactionAsString = NCsCoroutineTransaction::ToActionString(Transaction) + TEXT("(Reason=") + EMCsCoroutineEndReason::Get().ToString(R->endReason) + TEXT(")");

		const FString& ScheduleTypeAsString = EMCsCoroutineSchedule::Get().ToString(R->scheduleType);

		AActor* Actor			= R->GetActor();
		const FString ActorName = Actor ? Actor->GetName() : NCsCached::Str::Empty;
		UObject* Object			= R->GetRObject();
		const FString ObjectName = Object ? Object->GetName() : NCsCached::Str::Empty;
		UObject* Owner			= R->GetOwner();
		const FString OwnerName	= Owner ? Owner->GetName() : NCsCached::Str::Empty;

		UWorld* World = nullptr;

		if (Actor)
			World = Actor->GetWorld();
		if (Object)
			World = Object->GetWorld();

		const float CurrentTime = World ? World->GetTimeSeconds() : UCsCommon::GetCurrentDateTimeSeconds();

		const FString CoroutineName = R->name == NAME_None ? NCsCached::Str::None : R->nameAsString;

		FString Elapsed = NCsCached::Str::None;

		if (Transaction == ECsCoroutineTransaction::End)
		{
			const float Duration = CurrentTime - R->startTime;
			Elapsed = TEXT("Ran for ") + FString::FromInt(R->tickCount) + TEXT(" Ticks and  ") + UCsCommon::GetFloatAsStringWithPrecision(Duration, 2) + TEXT(" Seconds.");
		}

		if (Actor && Object)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: On%s %s Routine with Coroutine: %s at %f. Owner: %s using Actor: %s and Object: %s. %s"), *FunctionName, *ScheduleTypeAsString, *TransactionAsString, *CoroutineName, CurrentTime, *ActorName, *ObjectName, *Elapsed);
		}
		else
		if (Actor)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: On%s %s Routine with Coroutine: %s at %f. Using Owner: %s. %s"), *FunctionName, *ScheduleTypeAsString, *TransactionAsString, *CoroutineName, CurrentTime, *ActorName, *Elapsed);
		}
		else
		if (Object)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: On%s %s Routine with Coroutine: %s at %f. Using Owner: %s. %s"), *FunctionName, *ScheduleTypeAsString, *TransactionAsString, *CoroutineName, CurrentTime, *ObjectName, *Elapsed);
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("%s: On%s %s Routine with Coroutine: %s at %f. %s"), *FunctionName, *ScheduleTypeAsString, *TransactionAsString, *CoroutineName, CurrentTime, *Elapsed);
		}
	}
}

void UCsCoroutineScheduler::LogRunning(const ECsCoroutineSchedule& ScheduleType)
{
	if (CsCVarLogCoroutineRunning->GetInt() != CS_CVAR_SHOW_LOG)
		return;

	const uint8 Schedule = (uint8)ScheduleType;
	const int32 Count    = RoutinesToRun[Schedule].Num();

	if (Count == CS_EMPTY)
		return;

	UWorld* World = nullptr;

	if (UObject* Object = GetMyOwner())
		World = Object->GetWorld();

	float CurrentTime = World ? World->GetTimeSeconds() : UCsCommon::GetCurrentDateTimeSeconds();

	const FString& FunctionName		    = NCsCoroutineCached::Str::Update;
	const FString& ScheduleTypeAsString = EMCsCoroutineSchedule::Get().ToString(ScheduleType);

	UE_LOG(LogCs, Warning, TEXT("%s: On%s. Running %d Coroutines at %f."), *FunctionName, *ScheduleTypeAsString, Count, CurrentTime);

	for (int32 Index = 0; Index < Count; ++Index)
	{
		FCsRoutine* R = RoutinesToRun[Schedule][Index];

		AActor* Actor			= R->GetActor();
		const FString ActorName = Actor ? Actor->GetName() : NCsCached::Str::Empty;
		UObject* Object			= R->GetRObject();
		const FString ObjectName = Object ? Object->GetName() : NCsCached::Str::Empty;
		UObject* Owner			= R->GetOwner();
		const FString OwnerName = Owner ? Owner->GetName() : NCsCached::Str::Empty;

		const FString CoroutineName = R->name == NAME_None ? NCsCached::Str::None : R->name.ToString();

		const float Duration = CurrentTime - R->startTime;

		if (Actor && Object)
		{
			UE_LOG(LogCs, Warning, TEXT("-- Routine with Coroutine: %s. Owner: %s using Actor: %s and Object: %s. Running for %d Ticks and %f Seconds."), *CoroutineName, *ActorName, *ObjectName, R->tickCount, Duration);
		}
		else
		if (Actor)
		{
			UE_LOG(LogCs, Warning, TEXT("-- Routine with Coroutine: %s. Using Owner: %s. Running for %d Ticks and %f Seconds."), *CoroutineName, *ActorName, R->tickCount, Duration);
		}
		else
		if (Object)
		{
			UE_LOG(LogCs, Warning, TEXT("-- Routine with Coroutine: %s. Using Owner: %s. Running for %d Ticks and %f Seconds."), *CoroutineName, *ObjectName, R->tickCount, Duration);
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("-- Routine with Coroutine: %s. Running for %d Ticks and %f Seconds."), *CoroutineName, R->tickCount, Duration);
		}
	}
}

// Payload
#pragma region

FCsCoroutinePayload* UCsCoroutineScheduler::AllocatePayload()
{
	for (int32 I = 0; I < CS_ROUTINE_POOL_SIZE; ++I)
	{
		PayloadIndex = (PayloadIndex + 1) % CS_ROUTINE_POOL_SIZE;

		if (!Payloads[PayloadIndex].bAllocated)
		{
			return &(Payloads[PayloadIndex]);
		}
	}
	UE_LOG(LogCs, Warning, TEXT("UCsCoroutineScheduler::AllocatePayload: No free Payloads. Look for Runaway Coroutines or consider raising the pool size."));
	return nullptr;
}

#pragma endregion Payload